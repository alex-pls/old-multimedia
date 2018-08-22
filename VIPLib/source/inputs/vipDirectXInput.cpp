/** @file vipDirectXInput.cpp
 *
 * File containing methods for the 'vipDirectXInput' class.
 * The header for this class can be found in vipDirectXInput.h,
 * check that file for class description.
 *
 *
 ****************************************************************************
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.disi.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DISI - University of Trento
 *
 ****************************************************************************/

// cercare @ microsoft :  isamplegrabber !!!

#include "vipDirectXInput.h"


#include <dshow.h>
#include <qedit.h>


#define _WIN32_WINNT 0x0500   // Because of TryEnterCriticalSection ???????????????????????




#define SafeRelease(p) { if( (p) != 0 ) { (p)->Release(); (p)= NULL; } }

/*
  The Direct Show Graph is composed by 3 components:
    capture source, sample grabber and null renderer.

  Filters are connected:
    capture_filter(out)->(in)grabber_filter(out)->(in)null_filter

  But when the graph is rendered other transform filters
  can be inserted to connect the capture and the grabber.

  We do not use MFC, ATL and the Direct Show Base Classes.
  This module only needs the library "strmiids.lib".
  If the extra error functions were used, you will need to link with "quartz.lib" or "dxerr9.lib".

  We use the buffer of the ISampleGrabber. But this can not be done in a user callback,
  so we leave the grab loop for the application, it can also be done in the idle function.

  If you use the idle function the WDM Source Dialog is not "live"
  just because it is a modal dialog and
  it does not use the application message loop.
  It can be live using a timer.

  Since there is no gray format, bpp is always 24bpp.
*/




/**************************************************************************
                       imTrackingGrabberCB
***************************************************************************/

// This is better than using the sample grabber internal buffer
// because we have a more precise control of the data flow.

class imTrackingGrabberCB :	public ISampleGrabberCB
 {
	protected:
		int  m_Width, m_Height;
		bool	m_newImageFlag;
		unsigned char *m_ImageData;
		CRITICAL_SECTION m_sect;
		HANDLE m_imageReady;

	public:

		imTrackingGrabberCB();
		~imTrackingGrabberCB();

		STDMETHODIMP SampleCB(double SampleTime, IMediaSample *pSample);
		STDMETHODIMP BufferCB(double SampleTime, BYTE *pBuffer, long BufferLen) {return E_NOTIMPL;}
		STDMETHODIMP_(ULONG) AddRef() {return 2;}
		STDMETHODIMP_(ULONG) Release() {return 1;}
		STDMETHODIMP QueryInterface(REFIID riid, void ** ppv);

		void SetImageSize(int width, int height);
		int GetImage(unsigned char* data, int color_mode, int timeout);

 };

imTrackingGrabberCB::imTrackingGrabberCB()
 {
	InitializeCriticalSection(&m_sect);
	m_newImageFlag = 0;
	m_ImageData = NULL;
	m_imageReady = CreateEvent(NULL, FALSE, TRUE, NULL);
 }

imTrackingGrabberCB::~imTrackingGrabberCB()
 {
	CloseHandle(m_imageReady);
	EnterCriticalSection(&m_sect);
	DeleteCriticalSection(&m_sect);
	if (m_ImageData)
		delete m_ImageData;
 }

STDMETHODIMP imTrackingGrabberCB::QueryInterface(REFIID riid, void ** ppv)
 {
	if( riid == IID_ISampleGrabberCB || riid == IID_IUnknown )
	 {
		*ppv = (void *) static_cast<ISampleGrabberCB*> (this);
		return NOERROR;
	 }

	return E_NOINTERFACE;
 }

void imTrackingGrabberCB::SetImageSize(int width, int height)
 {
	EnterCriticalSection(&m_sect);

	// This can be done because the capture system always returns
	// images that are a multiple of 4.
	int new_size = width * height * 3;

	if (!m_ImageData)
	 {
		m_ImageData = (BYTE*)calloc(new_size, 1);
		m_Width = width;
		m_Height = height;
	 }

	if (m_Width*m_Height < new_size)
	m_ImageData = (BYTE*)realloc(m_ImageData, new_size);

	m_Width = width;
	m_Height = height;

	LeaveCriticalSection(&m_sect);
}

STDMETHODIMP imTrackingGrabberCB::SampleCB(double, IMediaSample *pSample)
{
  if (!m_ImageData) return S_OK;

  EnterCriticalSection(&m_sect);

  int size = pSample->GetSize();
  if (size > m_Width*m_Height*3)
  {
    LeaveCriticalSection(&m_sect);
    return S_OK;
  }

  BYTE *pData;
  pSample->GetPointer(&pData);
  CopyMemory(m_ImageData, pData, size);
  m_newImageFlag = 1;

  LeaveCriticalSection(&m_sect);

  SetEvent(m_imageReady);

  return S_OK;
}

int imTrackingGrabberCB::GetImage(unsigned char* data, int color_mode, int timeout)
{
	unsigned char* src_data = m_ImageData + m_Width * m_Height * 3;
	unsigned char* dst_data = data;

	EnterCriticalSection(&m_sect);

	for (int i = 0; i < m_Width*m_Height; i++)
	 {
		*(dst_data+2) = *src_data--;
		*dst_data = *src_data--;
		*(dst_data+1) = *src_data--;
		dst_data += 3;
	 }

	LeaveCriticalSection(&m_sect);

	return VIPRET_OK;
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////







//DX RELATED

//defined here so application DOES NOT NEED DX headers (and libs)
struct vipDXCapture
{
  int registered_graph,
      live,
      device;                     /* current connected device. -1 if not connected. */

//  char* dialog_desc[6];
//  vcDialogFunc dialog_func[6];
//  int dialog_count;                /* number of available configuration dialogs for the current connection. */

  IGraphBuilder* filter_builder;  /* The Filter Graph Manager */
  ICaptureGraphBuilder2* capture_graph_builder; /* Helps the Filter Graph Manager */
  IBaseFilter* capture_filter;    /* the capture device (can vary), it's a source filter. */
  IBaseFilter* grabber_filter;    /* returns the capture data, it's a transform filter */
  IBaseFilter* null_filter;       /* does nothing, act as a terminator, it's a rendering filter */
  ISampleGrabber* sample_grabber; /* Used to access the ISampleGrabber interface, since grabber_filter is a generic IBaseFilter interface based on ISampleGrabber. */
  IMediaControl* media_control;   /* Used to Run and Stop the graph flow. */
  IBaseFilter* overlay_renderer;  /* Used when there is a video port without a preview */
  IBaseFilter *overlay_mixer;

  IAMVideoProcAmp* video_prop;    /* Used to set/get video properties */
  IAMCameraControl* camera_prop;  /* Used to set/get camera properties */
  IAMVideoControl* videoctrl_prop; /* Used to set/get video properties */

  imTrackingGrabberCB* sample_callback; /* Used to intercept the samples. */

  int format_count;   /* number of supported formats */
  int format_current; /* current format */
  int format_map[50]; /* table to map returned formats to direct X formats */


  ISpecifyPropertyPages *pSpec;	//capture filter property page





/*
    IAMStreamConfig *pVSC;      // for video cap


    double FrameRate;
    BOOL fWantPreview;
    long lCapStartTime;
    long lCapStopTime;


    BOOL fUseTimeLimit;
    BOOL fUseFrameRate;
    DWORD dwTimeLimit;

    BOOL fCapturing;
    BOOL fPreviewing;


    long lDroppedBase;
    long lNotBase;
*/
};






/*

used in:

*/

#ifdef INCLUDE_VFW_DEVICES
#define CATEGORY_FLAG 0
#else
#define CATEGORY_FLAG CDEF_DEVMON_FILTER|CDEF_DEVMON_PNP_DEVICE
#endif

IBaseFilter* vipGetDevice(int device)
{
  // Selecting a Capture Device
  ICreateDevEnum *pDevEnum = NULL;
  IEnumMoniker *pEnum = NULL;

  // Create the System Device Enumerator.
  HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL,
                                CLSCTX_INPROC_SERVER, IID_ICreateDevEnum,
                                reinterpret_cast<void**>(&pDevEnum));
  if (FAILED(hr)) return NULL;

  // Create an enumerator for the video capture category.
  hr = pDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEnum, CATEGORY_FLAG);
  if (FAILED(hr) || !pEnum)
  {
    pDevEnum->Release();
    return NULL;
  }

  IMoniker *pMoniker = NULL;
  int d = 0;
  while (pEnum->Next(1, &pMoniker, NULL) == S_OK)
  {
    if (d == device)
    {
      //create the capture filter for the device
      //add the filter to the filter graph
      IBaseFilter *capture_filter = NULL;
      hr = pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void**)&capture_filter);
      if (SUCCEEDED(hr))
      {
        pMoniker->Release();
        pEnum->Release();
        pDevEnum->Release();
        return capture_filter;
      }
      else
      {
        pMoniker->Release();
        break;
      }
    }

    pMoniker->Release();
    d++;
  }

  pEnum->Release();
  pDevEnum->Release();
  return NULL;
}


IPin* vipGetPin(IBaseFilter* pFilter, PIN_DIRECTION dir)
{
  IEnumPins*  pEnumPins = NULL;
  IPin*       pPin = NULL;

  pFilter->EnumPins(&pEnumPins);
  if(!pEnumPins)
    return NULL;

  for(;;)
  {
    ULONG  cFetched = 0;
    PIN_DIRECTION pinDir = PIN_DIRECTION(-1);
    pPin = 0;

    if (FAILED(pEnumPins->Next(1, &pPin, &cFetched)))
    {
      pEnumPins->Release();
      return NULL;
    }

    if(cFetched == 1 && pPin != 0)
    {
      pPin->QueryDirection(&pinDir);
      if(pinDir == dir) break;
      pPin->Release();
    }
  }

  pEnumPins->Release();
  return pPin;
}

void vipNukeDownstream(IGraphBuilder* filter_builder, IBaseFilter *filter)
{
  IPin *pPin=0, *pPinTo=0;
  IEnumPins *pEnumPins = NULL;
  PIN_INFO pininfo;

  HRESULT hr = filter->EnumPins(&pEnumPins);
  if (FAILED(hr)) return;

  pEnumPins->Reset();

  while(hr == NOERROR)
  {
    hr = pEnumPins->Next(1, &pPin, NULL);
    if(hr == S_OK && pPin)
    {
      pPin->ConnectedTo(&pPinTo);
      if(pPinTo)
      {
        hr = pPinTo->QueryPinInfo(&pininfo);
        if(hr == NOERROR)
        {
          if(pininfo.dir == PINDIR_INPUT)
          {
            vipNukeDownstream(filter_builder, pininfo.pFilter);
            filter_builder->Disconnect(pPinTo);
            filter_builder->Disconnect(pPin);
            filter_builder->RemoveFilter(pininfo.pFilter);
          }

          pininfo.pFilter->Release();
        }

        pPinTo->Release();
      }

      pPin->Release();
    }
  }

  pEnumPins->Release();

}

int vipDisconnectFilters(IGraphBuilder* filter_builder, IBaseFilter* source, IBaseFilter* destiny)
 {
	IPin *pOut = vipGetPin(source, PINDIR_OUTPUT);
	IPin *pIn = vipGetPin(destiny, PINDIR_INPUT);
	HRESULT hr = filter_builder->Disconnect(pOut);
	hr = filter_builder->Disconnect(pIn);
	pOut->Release();
	pIn->Release();

	if (FAILED(hr))	//  if (HARDFAILED(hr))
		return VIPRET_INTERNAL_ERR;

	return VIPRET_OK;
 }

int vipDisconnectFilterPin(IGraphBuilder* filter_builder, IBaseFilter* filter, PIN_DIRECTION dir)
 {
	IPin *pIn = vipGetPin(filter, dir);
	IPin *pOut;
	pIn->ConnectedTo(&pOut);

	HRESULT hr = filter_builder->Disconnect(pIn);
	pIn->Release();

	if (FAILED(hr))	//  if (HARDFAILED(hr))
	 {
		if (pOut)
			pOut->Release();
		return VIPRET_INTERNAL_ERR;
	 }

	if (pOut)
	 {
		hr = filter_builder->Disconnect(pOut);
		pOut->Release();

		if (FAILED(hr))	//  if (HARDFAILED(hr))
			return VIPRET_INTERNAL_ERR;
	 }

	return VIPRET_OK;
}

int vipConnectFilters(IGraphBuilder* filter_builder, IBaseFilter* source, IBaseFilter* destiny, int direct)
 {
	HRESULT hr;

	IPin *pOut = vipGetPin(source, PINDIR_OUTPUT);
	IPin *pIn = vipGetPin(destiny, PINDIR_INPUT);

	if (direct)
		hr = filter_builder->ConnectDirect(pOut, pIn, NULL);
	else
		hr = filter_builder->Connect(pOut, pIn);

	pOut->Release();
	pIn->Release();

	if (FAILED(hr))	//  if (HARDFAILED(hr))
		return VIPRET_INTERNAL_ERR;

	return VIPRET_OK;
 }

DWORD vipAddGraphToRot(IUnknown *pUnkGraph)
{
  IMoniker * pMoniker;
  IRunningObjectTable *pROT;
  WCHAR wsz[128];
  HRESULT hr;

  if (FAILED(GetRunningObjectTable(0, &pROT)))
    return 0;

  wsprintfW(wsz, L"FilterGraph %08x pid %08x\0", (DWORD_PTR)pUnkGraph, GetCurrentProcessId());

  hr = CreateItemMoniker(L"!", wsz, &pMoniker);
  if (SUCCEEDED(hr))
  {
    DWORD dwRegister;
    hr = pROT->Register(ROTFLAGS_REGISTRATIONKEEPSALIVE, pUnkGraph, pMoniker, &dwRegister);
    pROT->Release();

    pMoniker->Release();

    if (SUCCEEDED(hr))
      return dwRegister;
  }

  pROT->Release();
  return 0;
}

void vipRemoveGraphFromRot(DWORD pdwRegister)
{
  IRunningObjectTable *pROT;

  if (SUCCEEDED(GetRunningObjectTable(0, &pROT)))
  {
    pROT->Revoke(pdwRegister);
    pROT->Release();
  }
}






IAMStreamConfig* vipGetStreamConfig(vipDXCapture* vc)
{
  IAMStreamConfig *pSC = NULL;
  if (FAILED(vc->capture_graph_builder->FindInterface(&PIN_CATEGORY_CAPTURE,
        &MEDIATYPE_Video, vc->capture_filter, IID_IAMStreamConfig, (void **)&pSC)))
    return NULL;

  return pSC;
}


void vipDeleteMediaType(AM_MEDIA_TYPE *pmt)
{
  CoTaskMemFree((PVOID)pmt->pbFormat);
  CoTaskMemFree(pmt);
}







static void vipGetFormatName(GUID subtype, char* desc)
{
#define NUM_FORM 7
  typedef struct _guid2name {
    char* name;
    const GUID* subtype;
  } guid2name;
  static guid2name map_table[NUM_FORM] = {
    {"RGB1",&MEDIASUBTYPE_RGB1},
    {"RGB4",&MEDIASUBTYPE_RGB4},
    {"RGB8",&MEDIASUBTYPE_RGB8},
    {"RGB565",&MEDIASUBTYPE_RGB565},
    {"RGB555",&MEDIASUBTYPE_RGB555},
    {"RGB24",&MEDIASUBTYPE_RGB24},
    {"RGB32",&MEDIASUBTYPE_RGB32}
  };

  for (int i = 0; i < NUM_FORM; i++)
  {
    if (*(map_table[i].subtype) == subtype)
    {
      strcpy(desc, map_table[i].name);
      return;
    }
  }

  desc[0] = (char)(subtype.Data1);
  desc[1] = (char)(subtype.Data1 >> 8);
  desc[2] = (char)(subtype.Data1 >> 16);
  desc[3] = (char)(subtype.Data1 >> 32);
  desc[4] = 0;
}




//used in:  VIPRESULT vipDirectXInput::setImageSize(int width, int height)
static IIPDVDec* vipGetDVDecoder(vipDXCapture* vc)
{
  IIPDVDec *pDV = NULL;
  HRESULT hr = vc->capture_graph_builder->FindInterface(NULL,
            &MEDIATYPE_Video, vc->capture_filter, IID_IIPDVDec, (void **)&pDV);
  if(FAILED(hr))
    return NULL;

  return pDV;
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////




/**
 * @brief  Default costructor, initialize variables and connect to
 *         device if requested.
 *
 * @param  device device id:  [0, getDeviceCount()[
 * @param  fps frame rate value (0 = max possible)
 */
vipDirectXInput::vipDirectXInput(int device) : vipInput(0)
 {
	INFO("vipDirectXInput::vipDirectXInput(float fps) : vipInput(fps) [CONTRUCTOR]")

	deviceCount = 0;
	enumerateDevices();

	cCap = (vipDXCapture*)malloc(sizeof(vipDXCapture));
	memset(cCap, 0, sizeof(vipDXCapture));

	cCap->sample_callback = NULL;
	cCap->device = -1;

	connectTo(device);
 }


vipDirectXInput::vipDirectXInput(int device, float fps) : vipInput(fps)
 {
	INFO("vipDirectXInput::vipDirectXInput(float fps) : vipInput(fps) [CONTRUCTOR]")

	deviceCount = 0;
	enumerateDevices();

	cCap = (vipDXCapture*)malloc(sizeof(vipDXCapture));
	memset(cCap, 0, sizeof(vipDXCapture));

	cCap->sample_callback = NULL;
	cCap->device = -1;

	connectTo(device);
 }

/**
 * @brief  Default destructor, release objects and buffers
 *         and destroy the imVideoCapture object.
 */
vipDirectXInput::~vipDirectXInput()
 {

#ifdef REGISTER_FILTERGRAPH
	if (vc->registered_graph)
		vc_RemoveGraphFromRot(vc->registered_graph);
#endif

	disconnect();

	if (cCap->sample_callback != NULL)
		delete cCap->sample_callback;

	SafeRelease(cCap->overlay_mixer);
	SafeRelease(cCap->overlay_renderer);
	SafeRelease(cCap->media_control);
	SafeRelease(cCap->sample_grabber);

	if (cCap->null_filter != NULL)
		cCap->null_filter->Release();

	if (cCap->grabber_filter != NULL)
		cCap->grabber_filter->Release();

	if (cCap->filter_builder != NULL)
		cCap->filter_builder->Release();

	if (cCap->capture_graph_builder != NULL)
		cCap->capture_graph_builder->Release();

	free(cCap);
 }

///////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////// filter and graph initialization

VIPRESULT vipDirectXInput::initCaptureGraphBuilder(vipDXCapture* vdx)
 {
  HRESULT hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC_SERVER,
                                IID_ICaptureGraphBuilder2, reinterpret_cast<void**>(&vdx->capture_graph_builder));
  if (FAILED(hr))
  	return VIPRET_INTERNAL_ERR;

  hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
                        IID_IGraphBuilder, reinterpret_cast<void**>(&vdx->filter_builder));
  if (FAILED(hr))
  	return VIPRET_INTERNAL_ERR;

  hr = CoCreateInstance(CLSID_SampleGrabber, NULL, CLSCTX_INPROC_SERVER,
                        IID_IBaseFilter, reinterpret_cast<void**>(&vdx->grabber_filter));
  if (FAILED(hr))
  	return VIPRET_INTERNAL_ERR;

  hr = CoCreateInstance(CLSID_NullRenderer, NULL, CLSCTX_INPROC_SERVER,
                        IID_IBaseFilter, reinterpret_cast<void**>(&vdx->null_filter));
  if (FAILED(hr))
  	return VIPRET_INTERNAL_ERR;

  // Initialize the Capture Graph Builder.
  vdx->capture_graph_builder->SetFiltergraph(vdx->filter_builder);

  hr = vdx->filter_builder->QueryInterface(IID_IMediaControl,(void**)&vdx->media_control);
  hr = vdx->grabber_filter->QueryInterface(IID_ISampleGrabber, (void **)&vdx->sample_grabber);

//  if (FAILED(hr))
//  	return VIPRET_INTERNAL_ERR;

  AM_MEDIA_TYPE mt;
  ZeroMemory(&mt, sizeof(AM_MEDIA_TYPE));

  mt.majortype = MEDIATYPE_Video;
  mt.subtype = MEDIASUBTYPE_RGB24;  // Force 24 bpp

  vdx->sample_grabber->SetMediaType(&mt);
  vdx->sample_grabber->SetOneShot(FALSE);
  vdx->sample_grabber->SetBufferSamples(FALSE);// WAS FALSE or TRUE

  vdx->sample_callback = new imTrackingGrabberCB();

  hr = vdx->filter_builder->AddFilter(vdx->grabber_filter, L"imSampleGrabber");
  hr = vdx->filter_builder->AddFilter(vdx->null_filter, L"imNullRenderer");

  // Remove clock to speed up things
  IMediaFilter* pMediaFilter = NULL;
  vdx->filter_builder->QueryInterface(IID_IMediaFilter, (void**)&pMediaFilter);
  pMediaFilter->SetSyncSource(NULL);
  pMediaFilter->Release();

#ifdef REGISTER_FILTERGRAPH
  vdx->registered_graph = vc_AddGraphToRot(vdx->filter_builder);
#endif


  return VIPRET_OK;
 }

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////// devices (dis)connection functions

/**
 * @brief  Connect to device.
 *
 * @return VIPRET_PARAMS_ERR if device is not valid, VET_ILLEGAL_USE
 *         if a device is already connected, VIPRET_INTERNAL_ERR
 *         if any error occured, VIPRET_OK else.
 */
VIPRESULT vipDirectXInput::connect()
 {
	if (deviceCount == 0)
	 {
		enumerateDevices();
		if (deviceCount == 0)
			return VIPRET_ILLEGAL_USE;
	 }

	if (cCap->device == -1 || cCap->device >= deviceCount)
		return VIPRET_ILLEGAL_USE;

	return connectTo(cCap->device);
 }


/**
 * @brief  Connect to current device.
 *
 * @return VET_ILLEGAL_USE if a device is already connected,
 *         VIPRET_INTERNAL_ERR if any error occured, VIPRET_OK else.
 *
 * @see    setDevice(int device);
 */
VIPRESULT vipDirectXInput::connectTo(int device)
 {
	if (cCap->device == device)
		return VIPRET_PARAM_ERR;

	if (cCap->device != -1 && cCap->device != device)
		disconnect();

	if (setDevice(device))
		return VIPRET_PARAM_ERR;

	if (initCaptureGraphBuilder(cCap))
	 {
		SafeRelease(cCap->grabber_filter);
		SafeRelease(cCap->filter_builder);
		SafeRelease(cCap->capture_graph_builder);
		SafeRelease(cCap->null_filter);
		free(cCap);
		return VIPRET_INTERNAL_ERR;
	 }

	cCap->capture_filter = vipGetDevice(device);
	if (!cCap->capture_filter)
		return VIPRET_INTERNAL_ERR;

	cCap->filter_builder->AddFilter(cCap->capture_filter, L"VIPLibbCaptureSource");

	vipCheckVideoPort(cCap);

//	if (vipCheckVideoPort(cCap))
//		return VIPRET_INTERNAL_ERR;

	if (vipConnectFilters(cCap->filter_builder, cCap->capture_filter, cCap->grabber_filter, 0))
	 {
		cCap->filter_builder->RemoveFilter(cCap->capture_filter);

		SafeRelease(cCap->capture_filter);
		SafeRelease(cCap->video_prop);
		SafeRelease(cCap->camera_prop);
		SafeRelease(cCap->videoctrl_prop);

		cCap->live = 0;
		cCap->device = -1;

		return VIPRET_INTERNAL_ERR;
	 }

	vipConnectFilters(cCap->filter_builder, cCap->grabber_filter, cCap->null_filter, 1);

	vipUpdateFormatList(cCap);

	getImageSize(&width, &height);
	cCap->sample_callback->SetImageSize(width, height);

	cCap->sample_grabber->SetCallback(cCap->sample_callback, 0);

//CHECK !!	cCap->sample_grabber->SetBufferSamples(TRUE);




	return VIPRET_OK;
 }

/**
 * @brief  Disconnect from current capture device.
 *
 * @return VIPRET_ILLEGAL_USE if no device is connected, VIPRET_OK else.
 */
VIPRESULT vipDirectXInput::disconnect()
 {
	if (cCap->device == -1)
		return VIPRET_ILLEGAL_USE;

	doStopLive();

	cCap->sample_grabber->SetCallback(NULL, 0);

	if (cCap->overlay_mixer)
		doReleaseMixer(cCap);

	vipDisconnectFilters(cCap->filter_builder, cCap->grabber_filter, cCap->null_filter);

	// Disconnect the grabber to preserve it
	if (vipDisconnectFilterPin(cCap->filter_builder, cCap->grabber_filter, PINDIR_INPUT))
		return VIPRET_INTERNAL_ERR;

	// Remove everything downstream the capture filter, except the null renderer
	vipNukeDownstream(cCap->filter_builder, cCap->capture_filter);

	cCap->filter_builder->RemoveFilter(cCap->capture_filter);

	SafeRelease(cCap->capture_filter);
	SafeRelease(cCap->video_prop);
	SafeRelease(cCap->camera_prop);
	SafeRelease(cCap->videoctrl_prop);

	cCap->live = 0;
	cCap->device = -1;

	height = 0;
	width = 0;

	return VIPRET_OK;
 }




/**
 * @brief  Get the state of current data source.
 *
 * @return true is there are no more frames to load, false else.
 */
bool vipDirectXInput::EoF()
 {
	 if ( getCurrentDevice() == -1 )
	 	return true;

	 return isLive();
 }


/**
 * @brief  Disconnect and reset the module.
 *
 * @return VIPRET_INTERNAL_ERR if any error occur, VIPRET_OK else.
 */
VIPRESULT vipDirectXInput::reset()
 {
	 return disconnect();

 }


///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////// stream size, format, functions

VIPRESULT vipDirectXInput::openPropertyPage(void* ghwndApp)
 {


    CAUUID cauuid;

    // 1. the video capture filter itself
	HRESULT hr;


	hr = cCap->capture_filter->QueryInterface(IID_ISpecifyPropertyPages, (void **)&cCap->pSpec);

	if(hr == S_OK)
	{
		hr = cCap->pSpec->GetPages(&cauuid);

		hr = OleCreatePropertyFrame(static_cast<HWND>(ghwndApp), 30, 30, NULL, 1,
			(IUnknown **)&cCap->capture_filter, cauuid.cElems,
			(GUID *)cauuid.pElems, 0, 0, NULL);

		CoTaskMemFree(cauuid.pElems);
		cCap->pSpec->Release();
	}
	else
		return VIPRET_INTERNAL_ERR;

	return VIPRET_OK;

 }



/**
 * @brief  Set current device
 *
 * @param[in] device id:  [0, getDeviceCount()[
 *
 * @return VIPRET_ILLEGAL_USE if stream is playing, VIPRET_PARAM_ERR
 *         if device id is not valid, VIPRET_OK else.
 */
VIPRESULT vipDirectXInput::setDevice(int device)
 {
	if (device == -1)
		return VIPRET_PARAM_ERR;

	if (cCap->live)
		return VIPRET_ILLEGAL_USE;

	if (device == cCap->device)
		return VIPRET_OK;

	if (deviceCount == 0)
	 {
		enumerateDevices();
		if (deviceCount == 0)
			return 1;
	 }

	if (device >= deviceCount)
		return VIPRET_PARAM_ERR;

	cCap->device = device;
	return VIPRET_OK;
 }

/**
 * @brief  Read current image size and store to passed arguments.
 *
 * @param[out] width image's width in pixel
 * @param[out] height image's height in pixel
 */
void vipDirectXInput::getImageSize(int *width, int *height)
 {
//  assert(cCap);
//////////////  assert(cCap->device != -1);

  AM_MEDIA_TYPE mt;
  ZeroMemory(&mt, sizeof(AM_MEDIA_TYPE));
  HRESULT hr = cCap->sample_grabber->GetConnectedMediaType(&mt);

  if ( SUCCEEDED(hr) &&
      (mt.majortype == MEDIATYPE_Video) &&
      (mt.formattype == FORMAT_VideoInfo) &&
      (mt.cbFormat >= sizeof (VIDEOINFOHEADER)) &&
      (mt.pbFormat != NULL))
  {
    VIDEOINFOHEADER *pVih = (VIDEOINFOHEADER*)mt.pbFormat;
    *width = pVih->bmiHeader.biWidth;
    *height = abs(pVih->bmiHeader.biHeight);
    CoTaskMemFree((PVOID)mt.pbFormat);
  }
  else
  {
    *width = 0;
    *height = 0;
  }
 }


/**
 * @brief  Set capture stream size.
 *
 * @return VIPRET_INTERNAL_ERR if any error occured, VIPRET_OK else.
 */
VIPRESULT vipDirectXInput::setImageSize(int width, int height)
 {
	//  assert(vc);
	//  assert(vc->device != -1);
	int state = cCap->live;

	doStopLive();

	// must be disconnected to change size or format
	disconnect();

	IIPDVDec* pDV = vipGetDVDecoder(cCap);
	if (pDV)
	 {
		int size = 0;

		switch(width)
		{
			case 720:
					  size = DVRESOLUTION_FULL;
					  break;
			case 360:
					  size = DVRESOLUTION_HALF;
					  break;
			case 180:
					  size = DVRESOLUTION_QUARTER;
					  break;
			case 88:
				  size = DVRESOLUTION_DC;
				  break;
		 }

		if (!size)
			return 0;

		int ret = SUCCEEDED(pDV->put_IPDisplay(size));
		if (ret)
		  cCap->sample_callback->SetImageSize(width, height);

		return ret;
	 }

	IAMStreamConfig *pSC = vipGetStreamConfig(cCap);
	if (!pSC)
		return VIPRET_INTERNAL_ERR;

	AM_MEDIA_TYPE *pmt;
	HRESULT hr = pSC->GetFormat(&pmt);
	if (FAILED(hr))
		return VIPRET_INTERNAL_ERR;

	VIDEOINFOHEADER* vih = (VIDEOINFOHEADER*)pmt->pbFormat;
	BITMAPINFOHEADER* bih = &vih->bmiHeader;

	/* dibs are DWORD aligned */
	int data_size = height * ((width * bih->biBitCount + 31) / 32) * 4;   /* 4 bytes boundary */

	bih->biSize = sizeof(BITMAPINFOHEADER);
	bih->biHeight = height;
	bih->biWidth = width;
	bih->biSizeImage = data_size;

	int fps = 30;  // desired frame rate
	vih->dwBitRate = fps * data_size;
	vih->AvgTimePerFrame = 10000000 / fps;

	pmt->cbFormat = sizeof(VIDEOINFOHEADER);
	pmt->lSampleSize = data_size;

	hr = pSC->SetFormat(pmt);
	pSC->Release();

	vipDeleteMediaType(pmt);

	int ret = SUCCEEDED(hr);

	if (ret)
	 {
		cCap->sample_callback->SetImageSize(width, height);

		if (state)
			if (connect() || doStartLive())
				return VIPRET_INTERNAL_ERR;
			else
				return VIPRET_OK;

		return VIPRET_OK;
	 }
	else
		return VIPRET_INTERNAL_ERR;
 }


/**
 * @brief  Read format's informations.
 *
 * @param[in] format's id
 * @param[out] width selected format's width
 * @param[out] height selected format's height
 * @param[out] desc selected format's description
 *
 * @return VIPRET_PARAM_ERR if format id is not valid,
 *         VIPRET_INTERNAL_ERR if an error occured, VIPRET_OK else.
 */
int vipDirectXInput::getFormat(int format, int *width, int *height, char* desc)
 {
//  assert(vc);
//  assert(vc->device != -1);
//  assert(vc->format_count);

  if (format >= cCap->format_count)
    return VIPRET_PARAM_ERR;

  IAMStreamConfig *pSC = vipGetStreamConfig(cCap);
  if (!pSC)
  	return VIPRET_INTERNAL_ERR;

  VIDEO_STREAM_CONFIG_CAPS scc;
  AM_MEDIA_TYPE *pmt;
  if (SUCCEEDED(pSC->GetStreamCaps(cCap->format_map[format], &pmt, (BYTE*)&scc)))
  {
    *width = scc.InputSize.cx;
    *height = scc.InputSize.cy;
    vipGetFormatName(pmt->subtype, desc);

    pSC->Release();
    vipDeleteMediaType(pmt);
    return VIPRET_OK;
  }

  pSC->Release();
  return VIPRET_INTERNAL_ERR;
 }

/**
 * @brief  Set current format's id.
 *
 * @param[in] format format's id
 *
 * @return VIPRET_PARAM_ERR if format id is not valid,
 *         VIPRET_INTERNAL_ERR if an error occured, VIPRET_OK else.
 */
VIPRESULT vipDirectXInput::setFormat(int format)
 {
//  assert(cCap);
//  assert(cCap->device != -1);

  if (format == -1)
    return VIPRET_PARAM_ERR;

  if (format >= cCap->format_count)
    return VIPRET_PARAM_ERR;

  doStopLive();

  // must be disconnected to change size or format
  disconnect();

  IAMStreamConfig *pSC = vipGetStreamConfig(cCap);
  if (!pSC)
    return VIPRET_INTERNAL_ERR;

  VIDEO_STREAM_CONFIG_CAPS scc;
  AM_MEDIA_TYPE *pmt;
  if (FAILED(pSC->GetStreamCaps(cCap->format_map[format], &pmt, (BYTE*)&scc)))
   {
    pSC->Release();
    return VIPRET_INTERNAL_ERR;
   }

  pSC->SetFormat(pmt);
  pSC->Release();

  cCap->sample_callback->SetImageSize(scc.InputSize.cx, scc.InputSize.cy);

  vipDeleteMediaType(pmt);

  cCap->format_current = format;

//  doStartLive();

  return VIPRET_OK;
 }




///////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////// inline functions

/**
 * @brief  Return current media control state.
 *
 * @return true is stream is playing live.
 */
bool vipDirectXInput::isLive()
 {
	if ( cCap->live == 0)
		return false;

	return true;
 }

/**
 * @brief  Returns current device id.
 *
 * @see    enumerateDevices(void);
 * @see    getDeviceCount(void);
 */
int vipDirectXInput::getCurrentDevice()
 {
	return cCap->device;
 }

/**
 * @brief  Read support format's count.
 *
 * @return valid format's count
 */
int vipDirectXInput::getFormatCount()
 {
  return cCap->format_count;
 }

/**
 * @brief  Read current format's id.
 *
 * @return format's id
 */
int vipDirectXInput::getFormat()
 {
  return cCap->format_current;
 }


///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////// live media control

/**
 * @brief  Start stream media control.
 *
 * @return VIPRET_ILLEGAL_USE if stream is already playing,
 *         VIPRET_INTERNAL_ERR if an error occured, VIPRET_OK else.
 */
VIPRESULT vipDirectXInput::doStartLive()
 {
	if (cCap->live)
		return VIPRET_ILLEGAL_USE;

	HRESULT hr = cCap->media_control->Run();

	if (FAILED(hr))	//  if (HARDFAILED(hr))
	 {
		cCap->live = 0;
		return VIPRET_INTERNAL_ERR;
	 }

	cCap->live = 1;

	Sleep(200);

	return VIPRET_OK;
 }

/**
 * @brief  Stop stream media control.
 *
 * @return VIPRET_ILLEGAL_USE if stream is already stopped, VIPRET_OK else.
 */
VIPRESULT vipDirectXInput::doStopLive()
 {
	if (!cCap->live)
		return VIPRET_ILLEGAL_USE;

	cCap->media_control->Stop();
	cCap->live = 0;
//    Sleep(200);

	return VIPRET_OK;
 }








///////////////////////////////////////////////////////////////////////////////////////
// frame extraction functions


/**
 * @brief  Grab a frame and copy to VIPLibb standard format.
 *
 * @param[out] img VIPLibb Cache Frame to store data.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR if any
 *		   device reading error occurs, VIPRET_NOT_IMPLEMENTED if color
 *         format is not support.
 *
 * @note   Ouput operator (>>) call directly this function.
 * @see    operator >> (vipFrameYUV420&)
 */
VIPRESULT vipDirectXInput::extractTo(vipFrameYUV420& img)
 {

	INFO("VIPRESULT vipDirectXInput::extractTo(vipFrameYUV420& img) [pushing data]")

	return VIPRET_NOT_IMPLEMENTED;
 }


/**
 * @brief  Grab a frame and copy to VIPLibb standard format.
 *
 * @param[out] img VIPLibb Cache24 Frame to store data.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR if any
 *		   device reading error occurs, VIPRET_NOT_IMPLEMENTED if color
 *         format is not support.
 *
 * @note   Ouput operator (>>) call directly this function.
 * @see    operator >> (vipFrameRGB24&)
 */
VIPRESULT vipDirectXInput::extractTo(vipFrameRGB24& img)
 {

	INFO("VIPRESULT vipDirectXInput::extractTo(vipFrameRGB24& img) [pushing data]")

	if ( &img == NULL )
		return VIPRET_PARAM_ERR;

	if ((unsigned int)width != img.width || (unsigned int)height != img.height)
	 {
		delete [] img.data;
		img.data = new PixelRGB24[width*height];
	 }

	img.height = (unsigned int)height;
	img.width = (unsigned int)width;


	doStopLive();

	cCap->sample_grabber->SetOneShot(TRUE);

	if (doStartLive())
	 {
		cCap->sample_grabber->SetOneShot(FALSE);
		return VIPRET_INTERNAL_ERR;
	 }

	return cCap->sample_callback->GetImage((unsigned char*)img.data[0], 0, 0);

 }



/**
 * @brief  Grab a frame and copy to VIPLibb standard format.
 *
 * @param[out] img Greyscale VIPLibb Frame to store data.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR if any
 *		   device reading error occurs, VIPRET_NOT_IMPLEMENTED if color
 *         format is not support.
 *
 * @note   Ouput operator (>>) call directly this function.
 * @see    operator >> (vipFrameT&)
 */
VIPRESULT vipDirectXInput::extractTo(vipFrameT<unsigned char>& img)
 {
	INFO("VIPRESULT vipDirectXInput::extractTo(vipFrameT& img) [pushing data]")

	if ( &img == NULL )
		return VIPRET_PARAM_ERR;


	return VIPRET_NOT_IMPLEMENTED;
 }




////////////////////////////////////////////////////////////////////////////////////////

// dx utilities functions



/*
  If the video capture card supports the video port pin without a video preview pin this will not work.
  The DirectShow architecture requires that the video port pin be connected to the Overlay Mixer Filter.
  If this pin is not connected, data cannot be captured in DirectShow.
*/
VIPRESULT vipDirectXInput::vipCheckVideoPort(vipDXCapture* vdx)
 {
	HRESULT hr;

	IPin *pPreviewPin = NULL;
	hr = vdx->capture_graph_builder->FindPin(
			vdx->capture_filter,      // Pointer to the capture filter.
			PINDIR_OUTPUT,           // Look for an output pin.
			&PIN_CATEGORY_PREVIEW,   // Look for a preview pin.
			NULL,                    // Any media type.
			FALSE,                   // Pin can be connected.
			0,                       // Retrieve the first matching pin.
			&pPreviewPin             // Receives a pointer to the pin.
			);

	if (hr == S_OK)
	 {
		pPreviewPin->Release();
		return VIPRET_INTERNAL_ERR;
	 }

	IPin *pVideoPortPin = NULL;
	hr = vdx->capture_graph_builder->FindPin(
			vdx->capture_filter,      // Pointer to the capture filter.
			PINDIR_OUTPUT,           // Look for an output pin.
			&PIN_CATEGORY_VIDEOPORT, // Look for a video port pin.
			NULL,                    // Any media type.
			FALSE,                   // Pin can be connected.
			0,                       // Retrieve the first matching pin.
			&pVideoPortPin           // Receives a pointer to the pin.
			);

	if (FAILED(hr))
		return VIPRET_INTERNAL_ERR;

	// Create the overlay mixer.
	CoCreateInstance(CLSID_OverlayMixer, NULL, CLSCTX_INPROC, IID_IBaseFilter, (void **)&vdx->overlay_mixer);

	// Add it to the filter graph.
	vdx->filter_builder->AddFilter(vdx->overlay_mixer, L"Overlay Mixer");

	IPin *pOverlayPin = NULL;
	vdx->capture_graph_builder->FindPin(vdx->overlay_mixer, PINDIR_INPUT, NULL, NULL, TRUE, 0, &pOverlayPin);

	vdx->filter_builder->Connect(pVideoPortPin, pOverlayPin);
	if (FAILED(hr))// ??
		return VIPRET_INTERNAL_ERR;

	SafeRelease(pVideoPortPin);
	SafeRelease(pOverlayPin);

	CoCreateInstance(CLSID_VideoRenderer, NULL, CLSCTX_INPROC_SERVER,
				   IID_IBaseFilter, reinterpret_cast<void**>(&vdx->overlay_renderer));
	vdx->filter_builder->AddFilter(vdx->overlay_renderer, L"Overlay Renderer");

	vipConnectFilters(vdx->filter_builder, vdx->overlay_mixer, vdx->overlay_renderer, 1);

	IVideoWindow* pVideoWindow = NULL;
	vdx->overlay_renderer->QueryInterface(IID_IVideoWindow,(void**)&pVideoWindow);
	pVideoWindow->put_AutoShow(OAFALSE);
	pVideoWindow->Release();

    return VIPRET_OK;
 }

/**
 * @brief  Disconnect filter graph and free objects.
 *
 * @param[in] vdx vipDXCapture object to release.
 */
void vipDirectXInput::doReleaseMixer(vipDXCapture* vc)
 {
  IPin *pOverlayPin = vipGetPin(vc->overlay_mixer, PINDIR_INPUT);
  IPin *pVideoPortPin = NULL;
  pOverlayPin->ConnectedTo(&pVideoPortPin);
  vc->filter_builder->Disconnect(pOverlayPin);
  vc->filter_builder->Disconnect(pVideoPortPin);
  SafeRelease(pVideoPortPin);
  SafeRelease(pOverlayPin);

  vipDisconnectFilters(vc->filter_builder, vc->overlay_mixer, vc->overlay_renderer);

  vc->filter_builder->RemoveFilter(vc->overlay_renderer);
  vc->filter_builder->RemoveFilter(vc->overlay_mixer);
  SafeRelease(vc->overlay_renderer);
  SafeRelease(vc->overlay_mixer);
 }



//used in: VIPRESULT vipDirectXInput::connectTo(int device)
VIPRESULT vipDirectXInput::vipUpdateFormatList(vipDXCapture* vdx)
 {
	vdx->format_count = 0;
	vdx->format_current = -1;

	IAMStreamConfig *pSC = vipGetStreamConfig(vdx);
	if ( !pSC )
		return VIPRET_INTERNAL_ERR;

	int iCount = 0, iSize = 0;
	if ( FAILED(pSC->GetNumberOfCapabilities(&iCount, &iSize)) )
	 {
		pSC->Release();
		return VIPRET_INTERNAL_ERR;
	 }

	AM_MEDIA_TYPE *curr_pmt;
	HRESULT hr = pSC->GetFormat(&curr_pmt);
	if ( FAILED(hr) )
	 {
		pSC->Release();
		return VIPRET_INTERNAL_ERR;
	 }

	for (int iFormat = 0; iFormat < iCount; iFormat++)
	 {
		VIDEO_STREAM_CONFIG_CAPS scc;
		AM_MEDIA_TYPE *pmt;
		if ( SUCCEEDED(pSC->GetStreamCaps(iFormat, &pmt, (BYTE*)&scc)) )
		 {
			if (scc.guid == FORMAT_VideoInfo)
			 {
				VIDEOINFOHEADER* vih = (VIDEOINFOHEADER*)curr_pmt->pbFormat;
				BITMAPINFOHEADER* bih = &vih->bmiHeader;
				int width = bih->biWidth;
				int height = abs(bih->biHeight);

				if ( curr_pmt->subtype == pmt->subtype &&
					 width == scc.InputSize.cx &&
					 height == scc.InputSize.cy				)
				 {
					vdx->format_current = vdx->format_count;
				 }

				vdx->format_map[vdx->format_count] = iFormat;
				vdx->format_count++;
			 }

			vipDeleteMediaType(pmt);
		 }
	 }

	vipDeleteMediaType(curr_pmt);
	pSC->Release();

	return VIPRET_OK;
 }


///////////////////////////////////////////////////////////////////////////////////////

// devices enumeration functions



static char* Wide2Char(WCHAR* wstr)
 {
  if (wstr)
  {
    int n = wcslen(wstr)+1;
    char* str = (char*)malloc(n);
    WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, n, NULL, NULL);
    return str;
  }

  return NULL;
 }


/**
 * @brief  Read (update) windows' connected device list.
 *
 * @see    getDeviceCount(void);
 * @see    getDeviceDescription(int device);
 */
void vipDirectXInput::enumerateDevices(void)
 {
  // Selecting a Capture Device
  ICreateDevEnum *pDevEnum = NULL;
  IEnumMoniker *pEnum = NULL;
  deviceCount = 0;

  CoInitialize(NULL);

  // Create the System Device Enumerator.
  HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL,
                                CLSCTX_INPROC_SERVER, IID_ICreateDevEnum,
                                reinterpret_cast<void**>(&pDevEnum));
  if (FAILED(hr)) return;

  // Create an enumerator for the video capture category.
  hr = pDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEnum, CATEGORY_FLAG);
  if (FAILED(hr) || !pEnum)
  {
    pDevEnum->Release();
    return;
  }

  IMoniker *pMoniker = NULL;
  while (pEnum->Next(1, &pMoniker, NULL) == S_OK)
  {
    IPropertyBag *pPropBag;
    hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void**)(&pPropBag));
    if (FAILED(hr))
    {
      pMoniker->Release();
      continue;  // Skip this one, maybe the next one will work.
    }

    // Find the friendly name.
    VARIANT varName;
    VariantInit(&varName);

    hr = pPropBag->Read(L"FriendlyName", &varName, 0);
    if (SUCCEEDED(hr))
    {
      char* str = Wide2Char(varName.bstrVal);
      sprintf(deviceDesc[deviceCount], "%d - %s", deviceCount, str);
      free(str);
      VariantClear(&varName);
      deviceCount++;
    }

    pPropBag->Release();
    pMoniker->Release();
  }

  pEnum->Release();
  pDevEnum->Release();
 }

/**
 * @brief  Returns the device description. Returns NULL in the last device.
 *
 * @see    enumerateDevices(void);
 * @see    getDeviceCount(void);
 */
const char* vipDirectXInput::getDeviceDescription(int device)
 {
  // List available Devices once
  if (deviceCount == 0)
  {
    enumerateDevices();

    if (deviceCount == 0)
      return NULL;
  }

  if (device >= deviceCount)
    return NULL;

  return deviceDesc[device];
 }


