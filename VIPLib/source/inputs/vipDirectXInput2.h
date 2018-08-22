/**
 *  @class   vipDirectXInput2
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

/*
libs required:

quartz.lib kernel32.lib user32.lib gdi32.lib winspool.lib
comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib
uuid.lib odbc32.lib odbccp32.lib quartz.lib kernel32.lib
user32.lib gdi32.lib comdlg32.lib ole32.lib winmm.lib msacm32.lib
olepro32.lib oleaut32.lib advapi32.lib uuid.lib strmiids.lib

*/


#ifndef __VIPLIB_VIPDIRECTXINPUT2_H__
 #define __VIPLIB_VIPDIRECTXINPUT2_H__

 #include "../../source/vipDefs.h"
 #include "../../source/vipInput.h"

 #include "../../source/vipFrameRGB24.h"
 #include "../../source/vipFrameYUV420.h"
 #include "../../source/vipFrameT.h"






 // just for HWND
// #include <windows.h>



 typedef unsigned long       DWORD;








 #define VETDX_MAXDEVICES	20

 struct vipDXCapture2;	//defined in vipDirectXInput2.cpp


class vipDirectXInput2 : public vipInput
 {

 protected:

		vipDXCapture2* cCap;

		DWORD g_dwGraphRegister;//=0


		unsigned int width;
		unsigned int height;

		/**
		 * @brief  DirectX compatible devices' description.
		 */
		char deviceVideoDesc[VETDX_MAXDEVICES][160];

		/**
		 * @brief  DirectX compatible devices' description.
		 */
		char deviceAudioDesc[VETDX_MAXDEVICES][160];


		int InitCapFilters(void);
		void FreeCapFilters(void);

		void TearDownGraph(void);
		int BuildCaptureGraph(void);
		int BuildPreviewGraph(void);
		int BuildGrabberGraph(bool mpeg2 = false);

		int MakeBuilder(void);
		int MakeGraph(void);


		void RegisterDevicesNotification(void);




		int RemoveGraphFromRot(DWORD pdwRegister);





 public:

		enum FORMAT_CSP	{
							UNKNOWN,
							VETFRAMET_CS_MONO,		//grayscale
							VETFRAMET_CS_RGB,		//standard
							VETFRAMET_CS_BGR,		//also standard
							VETFRAMET_CS_ARGB,		//alpha + .
							VETFRAMET_CS_ABGR,		//alpha + .
							VETFRAMET_CS_RGBA,		//. + alpha
							VETFRAMET_CS_BGRA,		//. + alpha
							VETFRAMET_CS_RGB565,	//pixel must be 16bit!
							VETFRAMET_CS_BGR565,	//pixel must be 16bit!
							VETFRAMET_CS_RGB555,	//pixel must be 16bit!
							VETFRAMET_CS_BGR555,	//pixel must be 16bit!
							VETFRAMET_CS_I420,		//4:2:0 planar
							VETFRAMET_CS_YV12,		//4:2:0 planar
							VETFRAMET_CS_YUY2,		//4:2:2 packed
							VETFRAMET_CS_UYVY,		//4:2:2 packed
							VETFRAMET_CS_YVYU,		//4:2:2 packed
							VETFRAMET_CS_CUSTOM,	//not listed here..
		} ;

		vipDirectXInput2(int device = -1);

		vipDirectXInput2(int device, float fps);

		/**
		 * @brief  Default destructor, release objects and buffers
		 *         and destroy the imVideoCapture object.
		 */
		~vipDirectXInput2();

		void Close(void);

		bool EoF();

		int reset() { return 666; };


////////////////////////////////////////////////////////////////////////////////////////////
// device setup/info

		/**
		 * @brief  Returns the device description. Returns NULL in the last device.
		 *
		 * @see    enumerateDevices(void);
		 * @see    getDeviceCount(void);
		 */
		const char* getDeviceDescription(int device);

		void enumerateDevices(void);

		/**
		 * @brief  Return current device count, call enumerateDevices(void) first.
		 *
		 * @see    enumerateDevices(void);
		 */
		int getDeviceVideoCount(void);

		/**
		 * @brief  Return current device count, call enumerateDevices(void) first.
		 *
		 * @see    enumerateDevices(void);
		 */
		int getDeviceAudioCount(void);

		/**
		 * @brief  Returns the device description. Returns NULL in the last device.
		 *
		 * @see    enumerateDevices(void);
		 * @see    getDeviceCount(void);
		 */
		const char* getDeviceVideoDescription(int device);

		/**
		 * @brief  Returns the device description. Returns NULL in the last device.
		 *
		 * @see    enumerateDevices(void);
		 * @see    getDeviceCount(void);
		 */
		const char* getDeviceAudioDescription(int device);

		/**
		 * @brief  Get current device id.
		 * @return current device id, if disconnected return -1
		 * @see    enumerateDevices(void);
		 * @see    getDeviceCount(void);
		 */
		int getCurrentDeviceVideo();

		/**
		 * @brief  Get current device id.
		 * @return current device id, if disconnected return -1
		 * @see    enumerateDevices(void);
		 * @see    getDeviceCount(void);
		 */
		int getCurrentDeviceAudio();


		int getVideoFriendlyName(char* buffer);
		int getAudioFriendlyName(char* buffer);


		int setCurrentDevices(int szVideo, int szAudio);

////////////////////////////////////////////////////////////////////////////////////////////
// run

		int StartPreview();
		int StopPreview();

		int StartCapture();
		int StopCapture();

//		int getFormat(int format, int *width, int *height, char* desc);


////////////////////////////////////////////////////////////////////////////////////////////
// setup
		void setPreviewEnabled(bool value = true);

		int showPreviewWindow(bool show = true);

		int setPreviewWindow(void* HWND_Owner);
		void doUpdatePreviewWindow();
		void setAutoUpdatePreviewWindowEnabled(bool enable = true);



		int AllocCaptureFile(unsigned short fileSize_mb = 10);

		int setFrameRate(double rate = 0.0);


		int setCaptureFile(char* pszName);


		int setFrameRateControlEnabled( bool enable = true);


		int setCaptureAudioEnabled( bool enable = true);

		int setMPEG2Encode(bool enable = true);

		void setErrorMessagesEnabled(bool enable = true);


		int showCaptureVideoForWindowPropertyPage();

		int showCaptureVideoFilterPropertyPage();
		int showCaptureAudioFilterPropertyPage();

		int showGraphFilterPropertyPage();
		int showVideoRendererPropertyPage();

		int showSampleGrabberPropertyPage();


		unsigned long getVideoBitRate();
		unsigned long getAudioBitRate();

int setFrameGrabbingEnabled(bool enable = true);
bool isFrameGrabbingEnabled();


FORMAT_CSP getCurrentFormat();
int getCurrentFormatDescription(char* buffer);
////////////////////////////////////////////////////////////////////////////////////////////
// stream informations

		bool isPreviewing();
		bool isCapturing();

		bool isPreviewFaked();
		bool isAutoUpdatePreviewWindowEnabled();

		bool isCapturingAudio();

		void UpdateStatus(bool fAllStats = false);

		bool isUncompressed();
		bool isMPEG2Encoded();

		double getFrameRate();
		double getFrameRateCurrent();

		long getCapturedElapsedTime();

		unsigned short getFileSize(bool forceUpdate = false);


		long getDroppedFramesCount(bool forceUpdate = false);
		long getCapturedFramesCount(bool forceUpdate = false);
		long getAverageFrameSize(bool forceUpdate = false);
		long getCapturedDataRate(bool forceUpdate = false);
		double getCapturedFrameRate(bool forceUpdate = false);


		/**
		 * @brief  Get current canvas' width.
		 *
		 * @return width in pixel.
		 */
		unsigned int getWidth() const { return width; };

		/**
		 * @brief  Get current canvas' height.
		 *
		 * @return height in pixel.
		 */
		unsigned int getHeight() const { return height; };



		long getFreeSpaceLeft();

////////////////////////////////////////////////////////////////////////////////////////////

		int extractTo(vipFrameRGB24& img);

		int extractTo(vipFrameYUV420& img);

		int extractTo(vipFrameT<unsigned char>& img);

 };













#endif	//__VIPLIB_VIPDIRECTXINPUT2_H__


