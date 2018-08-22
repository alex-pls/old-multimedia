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


//------------------------------------------------------------------------------
// File: AMCap.cpp
//
// Desc: Audio/Video Capture sample for DirectShow
//UpdateStatus
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------



//#define _WIN32_DCOM // needed by VC6 for OLE..


#include <streams.h>


#include <windows.h>

#include <dbt.h>
#include <mmreg.h>
#include <msacm.h>

//#include <dshow.h>
#include <Qedit.h>

#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <commdlg.h>
#include <atlbase.h>

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//#include "StdAfx.h"
// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__08E7CDC6_7F58_11D2_8CF1_00A0C9441E20__INCLUDED_)
#define AFX_STDAFX_H__08E7CDC6_7F58_11D2_8CF1_00A0C9441E20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef WIN32_LEAN_AND_MEAN
#undef WIN32_LEAN_AND_MEAN
#endif

#define _ATL_APARTMENT_THREADED
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <atlbase.h>
extern CComModule _Module;
#include <atlcom.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__08E7CDC6_7F58_11D2_8CF1_00A0C9441E20__INCLUDED)

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

// device notification definitions
#if (WINVER < 0x0500)

#define DBT_DEVTYP_DEVICEINTERFACE      0x00000005  // device interface class
#define DEVICE_NOTIFY_WINDOW_HANDLE     0x00000000

typedef PVOID   HDEVNOTIFY;

#endif

extern "C"
{
    typedef BOOL (/* WINUSERAPI */ WINAPI *PUnregisterDeviceNotification)(
        IN HDEVNOTIFY Handle
        );

    typedef HDEVNOTIFY (/* WINUSERAPI */ WINAPI *PRegisterDeviceNotificationA)(
        IN HANDLE hRecipient,
        IN LPVOID NotificationFilter,
        IN DWORD Flags
        );

    typedef HDEVNOTIFY (/* WINUSERAPI */ WINAPI *PRegisterDeviceNotificationW)(
        IN HANDLE hRecipient,
        IN LPVOID NotificationFilter,
        IN DWORD Flags
        );
}

#ifdef UNICODE
#define PRegisterDeviceNotification  PRegisterDeviceNotificationW
#else
#define PRegisterDeviceNotification  PRegisterDeviceNotificationA
#endif // !UNICODE

#if (WINVER < 0x0500)

typedef struct _DEV_BROADCAST_DEVICEINTERFACE_A {
    DWORD       dbcc_size;
    DWORD       dbcc_devicetype;
    DWORD       dbcc_reserved;
    GUID        dbcc_classguid;
    char        dbcc_name[1];
} DEV_BROADCAST_DEVICEINTERFACE_A, *PDEV_BROADCAST_DEVICEINTERFACE_A;

typedef struct _DEV_BROADCAST_DEVICEINTERFACE_W {
    DWORD       dbcc_size;
    DWORD       dbcc_devicetype;
    DWORD       dbcc_reserved;
    GUID        dbcc_classguid;
    wchar_t     dbcc_name[1];
} DEV_BROADCAST_DEVICEINTERFACE_W, *PDEV_BROADCAST_DEVICEINTERFACE_W;

#ifdef UNICODE
typedef DEV_BROADCAST_DEVICEINTERFACE_W   DEV_BROADCAST_DEVICEINTERFACE;
typedef PDEV_BROADCAST_DEVICEINTERFACE_W  PDEV_BROADCAST_DEVICEINTERFACE;
#else
typedef DEV_BROADCAST_DEVICEINTERFACE_A   DEV_BROADCAST_DEVICEINTERFACE;
typedef PDEV_BROADCAST_DEVICEINTERFACE_A  PDEV_BROADCAST_DEVICEINTERFACE;
#endif // UNICODE
#endif // WINVER


// window messages
#define WM_FGNOTIFY WM_USER+1


#include "vipDirectXInput2.h"

//#include "status.h"
//#include "crossbar.h"
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
//include "SampleCGB.h"
//------------------------------------------------------------------------------
// File: SampleCGB.h
//
// Desc: DirectShow sample code - definition of sample capture graph builder
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------
#include <ks.h>

#ifndef KSCATEGORY_ENCODER
#define STATIC_KSCATEGORY_ENCODER\
    0x19689bf6, 0xc384, 0x48fd, 0xad, 0x51, 0x90, 0xe5, 0x8c, 0x79, 0xf7, 0xb
DEFINE_GUIDSTRUCT("19689BF6-C384-48fd-AD51-90E58C79F70B", KSCATEGORY_ENCODER);
#define KSCATEGORY_ENCODER DEFINE_GUIDNAMED(KSCATEGORY_ENCODER)
#endif

#ifndef KSCATEGORY_MULTIPLEXER
#define STATIC_KSCATEGORY_MULTIPLEXER\
    0x236C9559, 0xADCE, 0x4736, 0xBF, 0x72, 0xBA, 0xB3, 0x4E, 0x39, 0x21, 0x96
DEFINE_GUIDSTRUCT("236C9559-ADCE-4736-BF72-BAB34E392196", KSCATEGORY_MULTIPLEXER);
#define KSCATEGORY_MULTIPLEXER DEFINE_GUIDNAMED(KSCATEGORY_MULTIPLEXER)
#endif

#ifndef MEDIASUBTYPE_Mpeg2
#define STATIC_MEDIASUBTYPE_Mpeg2\
    0x7DC2C665, 0x4033, 0x4CAF, 0x92, 0x73, 0xF7, 0xD7, 0x97, 0xFB, 0x24, 0x5C
DEFINE_GUIDSTRUCT("7DC2C665-4033-4CAF-9273-F7D797FB245C", MEDIASUBTYPE_Mpeg2);
#define MEDIASUBTYPE_Mpeg2 DEFINE_GUIDNAMED(MEDIASUBTYPE_Mpeg2)
#endif

#ifndef CLSID_Dump
#define STATIC_CLSID_Dump\
    0x36a5f770, 0xfe4c, 0x11ce, 0xa8, 0xed, 0x00, 0xaa, 0x00, 0x2f, 0xea, 0xb5
DEFINE_GUIDSTRUCT("36a5f770-fe4c-11ce-a8ed-00aa002feab5", CLSID_Dump);
#define CLSID_Dump DEFINE_GUIDNAMED(CLSID_Dump)
#endif



class ISampleCaptureGraphBuilder
{
public:

public:
    ISampleCaptureGraphBuilder()
    {
        AudPID_ = 0xC0;
        VidPID_ = 0xE0;
        HRESULT hr = graphBuilder2_.CoCreateInstance( CLSID_CaptureGraphBuilder2 );
        ASSERT( S_OK == hr );
    }

    //
    //  OnFinalConstruct build the ICaptureGraphBuilder2
    //
    void ReleaseFilters( )
    {
        pMultiplexer_.Release();
        pEncoder_.Release();
        pMPEG2Demux_.Release();
        pMediaControl_.Release();
        pAudioPin_.Release();
        pVideoPin_.Release();

    }

public:

    STDMETHOD(AllocCapFile)( LPCOLESTR lpwstr, DWORDLONG dwlSize );

    STDMETHOD(ControlStream)( const GUID *pCategory,
                          const GUID *pType,
                          IBaseFilter *pFilter,
                          REFERENCE_TIME *pstart,
                          REFERENCE_TIME *pstop,
                          WORD wStartCookie,
                          WORD wStopCookie
                          );

    STDMETHOD(CopyCaptureFile)(  LPOLESTR lpwstrOld,
                              LPOLESTR lpwstrNew,
                              int fAllowEscAbort,
                              IAMCopyCaptureFileProgress *pCallback
                              );

    STDMETHOD(FindInterface)(const GUID *pCategory,
                          const GUID *pType,
                          IBaseFilter *pf,
                          REFIID riid,
                          void **ppint
                          );

    STDMETHOD(FindPin)( IUnknown *pSource,
                      PIN_DIRECTION pindir,
                      const GUID *pCategory,
                      const GUID *pType,
                      BOOL fUnconnected,
                      int num,
                      IPin **ppPin
                      );


    STDMETHOD(GetFiltergraph)( IGraphBuilder **ppfg );

    STDMETHOD(RenderStream)( const GUID *pCategory,
                          const GUID *pType,
                          IUnknown *pSource,
                          IBaseFilter *pIntermediate,
                          IBaseFilter *pSink
                          );


    STDMETHOD(SetFiltergraph)( IGraphBuilder *pfg );


    STDMETHOD(SetOutputFileName)(
                                const GUID *pType,
                                LPCOLESTR lpwstrFile,
                                IBaseFilter **ppf,
                                IFileSinkFilter **pSink
                                );


protected:

    HRESULT CreateVideoPin( CComPtr<IMpeg2Demultiplexer> pIMpeg2Demux );
    HRESULT CreateAudioPin( CComPtr<IMpeg2Demultiplexer> pIMpeg2Demux );


    HRESULT ConfigureMPEG2Demux( CComPtr<IBaseFilter> pFilter);

    HRESULT FindMPEG2Pin( CComPtr<IBaseFilter> pFilter, CComPtr<IPin>& pPin );
    HRESULT FindPin(
                CComPtr<IBaseFilter> pFilter,
                const REGPINMEDIUM& regPinMedium,
                PIN_DIRECTION direction,
                BOOL video,
                CComPtr<IPin>& pPin);

    HRESULT GetMedium( CComPtr<IPin> pPin, REGPINMEDIUM& regPinMedium );
    HRESULT AddMPEG2Demux( );

    HRESULT FindEncoder( CComPtr<IEnumMoniker> pEncoders, REGPINMEDIUM pinMedium,
                         CComPtr<IBaseFilter>& pEncoder );

    BOOL IsMPEG2Pin( CComPtr<IPin> pPin );
    BOOL IsVideoPin( CComPtr<IPin> pPin );
    BOOL IsAudioPin( CComPtr<IPin> pPin );

    BOOL HasMediaType( CComPtr<IPin> pPin, REFGUID majorType );

    HRESULT FindAudioPin( CComPtr<IBaseFilter> pFilter, CComPtr<IPin>& pPin  );
    HRESULT FindVideoPin( CComPtr<IBaseFilter> pFilter, CComPtr<IPin>& pPin  );

    //
    //  tries to build MPEG2 segment for pFilter capture filter
    //
    HRESULT BuildMPEG2Segment( CComPtr<IBaseFilter> pFilter );
    //
    //  renders pPin to a MPEG2 demux
    //
    HRESULT RenderToMPEG2Demux( CComPtr<IPin> pPin );
    //
    //  renders pin pPin with pinMedium to an encoder
    //
    HRESULT RenderToMPEG2Demux( CComPtr<IPin> pPin, const REGPINMEDIUM& pinMedium,
                                CComPtr<IEnumMoniker> pEncoders );
    //
    //  renders pPin to a MPEG2 demux; there is no special medium, the encoder will be
    //  serched in the encoder category
    //
    HRESULT RenderToMPEG2Demux( CComPtr<IPin> pPin, CComPtr<IEnumMoniker> pEncoders  );
    //
    //  renders the encoder to a MPEG2 demux
    //
    HRESULT ConnectEncoderToMPEG2Demux( CComPtr< IBaseFilter > pEncoder,
                                        const REGPINMEDIUM& pinMedium );
    //
    //  renders the demux to a MPEG2 demux
    //
    HRESULT ConnectMultiplexerToMPEG2Demux( CComPtr<IBaseFilter> pEncoder,
                                            CComPtr< IEnumMoniker > pMultiplexers );
  public:
  	//
    //  helper methods; connects a pin to a filter and a filter to another one
    //
    HRESULT ConnectPin( CComPtr<IPin>, CComPtr< IBaseFilter > );


    HRESULT ConnectFilters(CComPtr<IBaseFilter> pUpFilter,
                           CComPtr<IBaseFilter> pDownFilter);
protected:
    //
    //  for audio pin; the multiplexer has already beem chosen
    //  if there is no encoder, the method fails
    //
    HRESULT ConnectAudioPinToMultiplexer( CComPtr<IPin> pPin,
                                          CComPtr<IBaseFilter> pMultiplexer);


    //
    //  helper methods - get the encoders using SystemDeviceEnum or IFilterMapper2
    //
    HRESULT GetEncodersByCategory( CComPtr<IEnumMoniker>& pEncoders );
    HRESULT GetEncodersByEnumerating( CComPtr<IPin> pPin, const REGPINMEDIUM& pinMedium,
                                      CComPtr<IEnumMoniker>& pEncoders );

    //
    //  helper methods - get the multiplexers using SystemDeviceEnum or IFilterMapper2
    //
    HRESULT GetMultiplexersByCategory( CComPtr<IEnumMoniker>& pMultiplexers);
    HRESULT GetMultiplexersByFilterMapper( CComPtr<IEnumMoniker>& pMultiplexers,
                                           const REGPINMEDIUM& pinMedium );

    CComPtr<IBaseFilter> pMultiplexer_;
    CComPtr<IBaseFilter> pEncoder_;
    CComPtr<IBaseFilter> pMPEG2Demux_;

protected:

    CComPtr<ICaptureGraphBuilder2> graphBuilder2_;
    CComPtr<IGraphBuilder> graph_;
    CComPtr<IMediaControl> pMediaControl_;

    ULONG   VidPID_,
            AudPID_;

private:
    CComPtr<IPin>   pAudioPin_;
    CComPtr<IPin>   pVideoPin_;

};



//------------------------------------------------------------------------------
// File: SampleCGB.cpp
//
// Desc: DirectShow sample code - Sample capture graph builder class
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


//#include <streams.h>
//#include "ks.h"
#include "ksproxy.h"
//#include <atlbase.h>
//#include  "SampleCGB.h"


//
//  ISampleCaptureGraphBuilder is trying to connect the video pin to the MPEG2 demux.
//  The possible configurations are:
//
//
//
// 1. capture filter- > audio / video encoder & multiplexer -> MPEG2 demux
//
// ----------------------         ---------------------------------------    ---------------
// |                   v|   --->  |                                     |    |             |
// | Capture Filter     |         | Audio / video encoder & Multiplexer |  ->| MPEG2 demux |
// |                   a|   --->  |                                     |    |             |
// ----------------------         ---------------------------------------    ---------------
//
//
//
//
//
//                        -> audio encoder ->
//  2. capture filter                           multiplexer -> MPEG2 demux
//                        -> video encoder ->
//
//  -----------------------     -----------------    ----------------     ---------------
//  |                    a|  -> | audio encoder | -> |              |     |             |
//  |                     |     -----------------    |              |     |             |
//  | capture filter      |                          |  multiplexer |  -> | MPEG2 demux |
//  |                     |     -----------------    |              |     |             |
//  |                    v|  -> | video encoder | -> |              |     |             |
//  -----------------------     -----------------    ----------------     ---------------
//
//
//
//
//
//                      a
//  3.  capture filter      - audio & video encoder -> multiplexer -> MPEG2 demux
//                      v
//
//  -----------------------     -----------------    ----------------     ---------------
//  |                    a|  -> | audio encoder | -> |              |     |             |
//  |                     |     |               |    |              |     |             |
//  | capture filter      |     |               |    |  multiplexer |  -> | MPEG2 demux |
//  |                     |     |               |    |              |     |             |
//  |                    v|  -> | video encoder | -> |              |     |             |
//  -----------------------     -----------------    ----------------     ---------------
//
//
//
//
//  4. capture filter -> MPEG2 demux
//
// ------------------------------       ----------------
// |                   MPEG2 PS | --->  |              |
// | Capture Filter             |       | MPEG2 demux  |
// |                            |       |              |
// ------------------------------       ----------------
//
//


//
//  How the algorithm works:
//      1. the video pin doesn't stream MPEG2
//          1. tries to connect the pin to an encoder
//          2. tries to connect the encoder directly to the MPEG2 demux
//          3. if not possible, tries to find a multiplexor that can be connected to the
//             encoder and MPEG2 demux
//          4. connect audio pin to the MPEG2 demux using the same algorithm as in
//             video pin case
//
//      2. if pin streams MPEG2 PS, then connect it to the MPEG2 demux
//      3. program the MPEG2 demux
//      4. render the video and the audio pin from the MPEG2 demux
//


static
BYTE
Mpeg2ProgramVideo [] = {
    0x00, 0x00, 0x00, 0x00,                         //  .hdr.rcSource.left              = 0x00000000
    0x00, 0x00, 0x00, 0x00,                         //  .hdr.rcSource.top               = 0x00000000
    0xD0, 0x02, 0x00, 0x00,                         //  .hdr.rcSource.right             = 0x000002d0
    0xE0, 0x01, 0x00, 0x00,                         //  .hdr.rcSource.bottom            = 0x000001e0
    0x00, 0x00, 0x00, 0x00,                         //  .hdr.rcTarget.left              = 0x00000000
    0x00, 0x00, 0x00, 0x00,                         //  .hdr.rcTarget.top               = 0x00000000
    0x00, 0x00, 0x00, 0x00,                         //  .hdr.rcTarget.right             = 0x00000000
    0x00, 0x00, 0x00, 0x00,                         //  .hdr.rcTarget.bottom            = 0x00000000
    0x00, 0x09, 0x3D, 0x00,                         //  .hdr.dwBitRate                  = 0x003d0900
    0x00, 0x00, 0x00, 0x00,                         //  .hdr.dwBitErrorRate             = 0x00000000
    0x63, 0x17, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, //  .hdr.AvgTimePerFrame            = 0x0000000000051763
    0x00, 0x00, 0x00, 0x00,                         //  .hdr.dwInterlaceFlags           = 0x00000000
    0x00, 0x00, 0x00, 0x00,                         //  .hdr.dwCopyProtectFlags         = 0x00000000
    0x04, 0x00, 0x00, 0x00,                         //  .hdr.dwPictAspectRatioX         = 0x00000004
    0x03, 0x00, 0x00, 0x00,                         //  .hdr.dwPictAspectRatioY         = 0x00000003
    0x00, 0x00, 0x00, 0x00,                         //  .hdr.dwReserved1                = 0x00000000
    0x00, 0x00, 0x00, 0x00,                         //  .hdr.dwReserved2                = 0x00000000
    0x28, 0x00, 0x00, 0x00,                         //  .hdr.bmiHeader.biSize           = 0x00000028
    0xD0, 0x02, 0x00, 0x00,                         //  .hdr.bmiHeader.biWidth          = 0x000002d0
    0xE0, 0x01, 0x00, 0x00,                         //  .hdr.bmiHeader.biHeight         = 0x00000000
    0x00, 0x00,                                     //  .hdr.bmiHeader.biPlanes         = 0x0000
    0x00, 0x00,                                     //  .hdr.bmiHeader.biBitCount       = 0x0000
    0x00, 0x00, 0x00, 0x00,                         //  .hdr.bmiHeader.biCompression    = 0x00000000
    0x00, 0x00, 0x00, 0x00,                         //  .hdr.bmiHeader.biSizeImage      = 0x00000000
    0xD0, 0x07, 0x00, 0x00,                         //  .hdr.bmiHeader.biXPelsPerMeter  = 0x000007d0
    0x27, 0xCF, 0x00, 0x00,                         //  .hdr.bmiHeader.biYPelsPerMeter  = 0x0000cf27
    0x00, 0x00, 0x00, 0x00,                         //  .hdr.bmiHeader.biClrUsed        = 0x00000000
    0x00, 0x00, 0x00, 0x00,                         //  .hdr.bmiHeader.biClrImportant   = 0x00000000
    0x98, 0xF4, 0x06, 0x00,                         //  .dwStartTimeCode                = 0x0006f498
    0x56, 0x00, 0x00, 0x00,                         //  .cbSequenceHeader               = 0x00000056
    0x02, 0x00, 0x00, 0x00,                         //  .dwProfile                      = 0x00000002
    0x02, 0x00, 0x00, 0x00,                         //  .dwLevel                        = 0x00000002
    0x00, 0x00, 0x00, 0x00,                         //  .Flags                          = 0x00000000
                                                    //  .dwSequenceHeader [1]
    0x00, 0x00, 0x01, 0xB3, 0x2D, 0x01, 0xE0, 0x24,
    0x09, 0xC4, 0x23, 0x81, 0x10, 0x11, 0x11, 0x12,
    0x12, 0x12, 0x13, 0x13, 0x13, 0x13, 0x14, 0x14,
    0x14, 0x14, 0x14, 0x15, 0x15, 0x15, 0x15, 0x15,
    0x15, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16,
    0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17,
    0x18, 0x18, 0x18, 0x19, 0x18, 0x18, 0x18, 0x19,
    0x1A, 0x1A, 0x1A, 0x1A, 0x19, 0x1B, 0x1B, 0x1B,
    0x1B, 0x1B, 0x1C, 0x1C, 0x1C, 0x1C, 0x1E, 0x1E,
    0x1E, 0x1F, 0x1F, 0x21, 0x00, 0x00, 0x01, 0xB5,
    0x14, 0x82, 0x00, 0x01, 0x00, 0x00
} ;


static
BYTE
MPEG1AudioFormat [] = {
    0x50, 0x00, 0x02, 0x00, 0x80, 0xBB, 0x00, 0x00,
    0x00, 0x7D, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00,
    0x16, 0x00, 0x02, 0x00, 0x00, 0xE8, 0x03, 0x00,
    0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x1C, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
} ;



HRESULT
ISampleCaptureGraphBuilder::AllocCapFile( LPCOLESTR lpwstr, DWORDLONG dwlSize )
{
    return graphBuilder2_->AllocCapFile( lpwstr, dwlSize );
}


HRESULT
ISampleCaptureGraphBuilder::ControlStream( const GUID *pCategory,
                                          const GUID *pType,
                                          IBaseFilter *pFilter,
                                          REFERENCE_TIME *pstart,
                                          REFERENCE_TIME *pstop,
                                          WORD wStartCookie,
                                          WORD wStopCookie )
{
    return graphBuilder2_->ControlStream( pCategory, pType, pFilter,
                                          pstart, pstop, wStartCookie, wStopCookie );
}


HRESULT
ISampleCaptureGraphBuilder::CopyCaptureFile(  LPOLESTR lpwstrOld,
                                              LPOLESTR lpwstrNew,
                                              int fAllowEscAbort,
                                              IAMCopyCaptureFileProgress *pCallback)
{
    return graphBuilder2_->CopyCaptureFile( lpwstrOld, lpwstrNew,
                                            fAllowEscAbort, pCallback );
}

HRESULT ISampleCaptureGraphBuilder::FindInterface(const GUID *pCategory,
                                                  const GUID *pType,
                                                  IBaseFilter *pf,
                                                  REFIID riid,
                                                  void **ppint
                                                  )
{
    return graphBuilder2_->FindInterface( pCategory, pType, pf, riid, ppint );
}

HRESULT
ISampleCaptureGraphBuilder::FindPin( IUnknown *pSource,
                                      PIN_DIRECTION pindir,
                                      const GUID *pCategory,
                                      const GUID *pType,
                                      BOOL fUnconnected,
                                      int num,
                                      IPin **ppPin)
{
    return graphBuilder2_->FindPin( pSource, pindir, pCategory, pType,
                                    fUnconnected, num, ppPin );
}


HRESULT ISampleCaptureGraphBuilder::GetFiltergraph( IGraphBuilder **ppfg )
{
    return graphBuilder2_->GetFiltergraph( ppfg );
}

HRESULT
ISampleCaptureGraphBuilder::RenderStream( const GUID *pCategory,
                                          const GUID *pType,
                                          IUnknown *pSource,
                                          IBaseFilter *pIntermediate,
                                          IBaseFilter *pSink)
{
    if( !pType ||  !::IsEqualGUID( MEDIATYPE_Stream, *pType ) )
    {
        return graphBuilder2_->RenderStream( pCategory, pType, pSource,
                                             pIntermediate, pSink );
    }


    HRESULT hr;
    if( !graph_ )
    {
        hr = GetFiltergraph( &graph_ );
        if( FAILED( hr ) )
        {
            return hr;
        }
    }

    //
    //  try to build MPEG2 graph
    //
    CComPtr< IBaseFilter > captureFilter;

    hr = pSource->QueryInterface( & captureFilter );
    if( FAILED( hr ) )
    {
        return E_INVALIDARG;
    }

    hr = BuildMPEG2Segment( captureFilter );
    if( pSink || FAILED( hr ) )
    {
        return hr;
    }

    hr = ConfigureMPEG2Demux( pMPEG2Demux_ );
    if( FAILED( hr ) )
    {
        return hr;
    }

// original code:
//    hr = RenderStream(NULL, &MEDIATYPE_Video, pMPEG2Demux_, NULL, NULL );
//    if( FAILED( hr ) )
//    {
//        return hr;
//    }
//
// ________________________________________________
// edited by Alessandro Polo 2006 - eWorld Research

    hr = RenderStream(NULL, &MEDIATYPE_Video, pMPEG2Demux_, NULL, NULL );
//    hr = RenderStream(NULL, NULL, pMPEG2Demux_, NULL, pSink);

    if( FAILED( hr ) )
    {
        return hr;
    }


// ________________________________________________

    hr = RenderStream(NULL, &MEDIATYPE_Audio, pMPEG2Demux_, NULL, NULL );
    if( FAILED( hr ) )
    {
        return hr;
    }

    return S_OK;
}


HRESULT
ISampleCaptureGraphBuilder::SetFiltergraph( IGraphBuilder *pfg )
{
    return graphBuilder2_->SetFiltergraph( pfg );
}


HRESULT
ISampleCaptureGraphBuilder::SetOutputFileName(  const GUID *pType,
                                                LPCOLESTR lpwstrFile,
                                                IBaseFilter **ppf,
                                                IFileSinkFilter **pSink )
{
    if( ! pType || ! lpwstrFile || !ppf || !pSink )
    {
        return E_INVALIDARG;
    }

    if( !::IsEqualGUID( *pType, MEDIASUBTYPE_Mpeg2 ) )
    {
        return graphBuilder2_->SetOutputFileName(pType, lpwstrFile, ppf, pSink );
    }

    HRESULT hr;
    if( !graph_ )
    {
        hr = GetFiltergraph( &graph_ );
        if( FAILED( hr ) )
        {
            return hr;
        }
    }

    //
    //  Configure the dump filter
    //
    CComPtr< IFileSinkFilter > pDump;
    hr = pDump.CoCreateInstance( CLSID_Dump );
    if( FAILED( hr ) )
    {
        return hr;
    }

    hr = pDump->SetFileName( lpwstrFile, NULL );
    if( FAILED( hr ) )
    {
        return hr;
    }

    hr = pDump.QueryInterface( &pMPEG2Demux_ );
    if( FAILED( hr ) )
    {
        return hr;
    }

    hr = graph_->AddFilter( pMPEG2Demux_, L"Dump" );
    if( FAILED( hr ) )
    {
        pMPEG2Demux_ = NULL;
        return hr;
    }


    *pSink = pDump;
    return S_OK;
}



//
//  A device can stream directly MPEG2 stream,
//  or it can be linked with a video codec and multiplexer
//
//

//
//  Loop through every media type supported by this pin
//  to see if there is one which can be considered MPEG2
//
BOOL ISampleCaptureGraphBuilder::IsMPEG2Pin( CComPtr<IPin> pPin )
{
    if( !pPin )
    {
        return FALSE;   // NULL pointer
    }

    CComPtr<IEnumMediaTypes> pMediaTypes;
    HRESULT hr = pPin->EnumMediaTypes( &pMediaTypes );
    if( FAILED( hr ) )
    {
        return FALSE;
    }

    hr = pMediaTypes->Reset();
    if( FAILED( hr ) )
    {
        return FALSE;
    }

    ULONG           fetched;
    AM_MEDIA_TYPE   *mediaType;
    while( S_OK == pMediaTypes->Next( 1, &mediaType, &fetched ) )
    {
        if(
            (
                ::IsEqualGUID( mediaType->majortype, MEDIATYPE_Video ) ||
                ::IsEqualGUID( mediaType->majortype, MEDIATYPE_Stream )
            )
            &&
            (
                ::IsEqualGUID( mediaType->subtype, MEDIASUBTYPE_MPEG2_VIDEO ) ||
                ::IsEqualGUID( mediaType->subtype,  MEDIASUBTYPE_MPEG2_PROGRAM )
            )
        )
        {
            DeleteMediaType( mediaType );
            return TRUE;
        }
        DeleteMediaType( mediaType );
    }

    return FALSE;
}

BOOL ISampleCaptureGraphBuilder::IsVideoPin( CComPtr<IPin> pPin )
{
    return HasMediaType( pPin, MEDIATYPE_Video );
}



HRESULT ISampleCaptureGraphBuilder::GetEncodersByCategory( CComPtr<IEnumMoniker>& pEncoders )
{
    CComPtr<ICreateDevEnum> pDeviceEnum;

    HRESULT hr = pDeviceEnum.CoCreateInstance( CLSID_SystemDeviceEnum );
    if( FAILED( hr ) )
    {
        return hr;
    }

    return pDeviceEnum->CreateClassEnumerator( KSCATEGORY_ENCODER, &pEncoders, 0 );
}



HRESULT
ISampleCaptureGraphBuilder::GetEncodersByEnumerating(
                                        CComPtr< IPin > pPin,
                                        const REGPINMEDIUM& pinMedium,
                                        CComPtr<IEnumMoniker>& pEncoders )
{
    CComPtr<IFilterMapper2> pFilterMapper2;
    HRESULT hr = pFilterMapper2.CoCreateInstance( CLSID_FilterMapper2 );
    if( FAILED( hr ) )
    {
        return hr;
    }

    hr = pFilterMapper2->EnumMatchingFilters(
                                &pEncoders,
                                NULL,
                                FALSE,
                                0,          //any merit
                                TRUE,
                                0,
                                NULL,
                                &pinMedium,
                                NULL,
                                FALSE,
                                TRUE,
                                0,
                                NULL,
                                NULL,
                                NULL );


    return hr;
}


//
//  looks for an MPEG2 pin
//
HRESULT
ISampleCaptureGraphBuilder::FindMPEG2Pin(
                        CComPtr<IBaseFilter> pFilter,
                        CComPtr<IPin>& pPin )
{
    if( !pFilter )
    {
        return E_POINTER;
    }


    CComPtr<IEnumPins> pEnumPins;
    HRESULT hr = pFilter->EnumPins( &pEnumPins );
    if( FAILED( hr ) )
    {
        return hr;
    }

    CComPtr<IPin>   pTempPin;
    ULONG           fetched;
    PIN_DIRECTION   dir;

    hr = pEnumPins->Reset( );
    while( pTempPin.Release(), S_OK == pEnumPins->Next( 1, &pTempPin, &fetched ) )
    {
        hr = pTempPin->QueryDirection( &dir );
        if( FAILED( hr ) || PINDIR_INPUT == dir )
        {
            continue;
        }
        if( IsMPEG2Pin( pTempPin ) )
        {
            pPin = pTempPin;
            return S_OK;
        }
    }
    return E_FAIL;
}

//
//  search the encoder that has this special medium
//  video == TRUE -- look for a video pin
//  video == FALSE -- look for a audio pin
//
HRESULT ISampleCaptureGraphBuilder::FindPin(
            CComPtr<IBaseFilter> pFilter,
            const REGPINMEDIUM& regPinMedium,
            PIN_DIRECTION direction,
            BOOL video,
            CComPtr<IPin>& pPin)
{
    if( !pFilter )
    {
        return E_POINTER;
    }

    CComPtr<IEnumPins> pEnumPins;
    HRESULT hr = pFilter->EnumPins( &pEnumPins );
    if( FAILED( hr ) )
    {
        return hr;
    }

    CComPtr<IPin>   pTempPin;
    ULONG           fetched;
    REGPINMEDIUM    regPinMediumTemp;
    PIN_DIRECTION   dir;

    hr = pEnumPins->Reset( );
    while( pTempPin.Release(), S_OK == pEnumPins->Next( 1, &pTempPin, &fetched ) )
    {
        ASSERT( pTempPin );

        hr = pTempPin->QueryDirection( &dir );
        if( FAILED( hr ) || dir != direction )
        {
            continue;
        }

        hr = GetMedium( pTempPin, regPinMediumTemp );
        if( FAILED( hr ) )
        {
            continue;
        }

        if( !IsVideoPin( pTempPin ) )
        {
            continue;
        }

        if( ::IsEqualGUID( regPinMediumTemp.clsMedium, regPinMedium.clsMedium  ) &&
            regPinMediumTemp.dw1 == regPinMedium.dw1 )
        {
            pPin = pTempPin;
            return S_OK;
        }
    }

    return E_FAIL;
}

//
//  Get a special medium from this pin.
//  If there is not one, return GUID_NULL.
//  Returns the first one it finds special
//

HRESULT
ISampleCaptureGraphBuilder::GetMedium(
                        CComPtr<IPin> pPin,
                        REGPINMEDIUM& regPinMedium )
{
    if( !pPin )
    {
        return E_POINTER;
    }

    CComPtr<IKsPin> pKsPin;
    HRESULT hr = pPin.QueryInterface( &pKsPin );
    if( FAILED( hr ) )
    {
        return hr;
    }

    PKSMULTIPLE_ITEM pmi;
    hr = pKsPin->KsQueryMediums( &pmi );
    if( FAILED( hr ) )
    {
        return hr;
    }

    REGPINMEDIUM *pMedium = (REGPINMEDIUM *)(pmi + 1);
    for( ULONG i  = 0; i < pmi->Count; i++ )
    {
        if( !::IsEqualGUID( pMedium->clsMedium, GUID_NULL ) &&
            !::IsEqualGUID( pMedium->clsMedium, KSMEDIUMSETID_Standard )
        )
        {
            regPinMedium.clsMedium = pMedium->clsMedium;
            regPinMedium.dw1 = pMedium->dw1;
            regPinMedium.dw2 = pMedium->dw2;
            CoTaskMemFree( pmi );
            return S_OK;
        }
    }

    regPinMedium.clsMedium = GUID_NULL;
    regPinMedium.dw1 = 0;
    regPinMedium.dw2 = 0;
    CoTaskMemFree( pmi );
    return S_OK;
}



//
//  Adds the MPEG2 demux and renders
//  the audio and video pin until the end (until the renderers)
//

HRESULT ISampleCaptureGraphBuilder::AddMPEG2Demux( )
{
    if( pMPEG2Demux_ )
    {
        //
        //  Instead of a MPEG2 demux there is a
        //  dump filter in which the file will be dumped
        //
        return S_OK;
    }

    HRESULT hr = pMPEG2Demux_.CoCreateInstance(CLSID_MPEG2Demultiplexer);
    if( FAILED( hr ) )
    {
        return hr;
    }
    return graph_->AddFilter( static_cast<IBaseFilter *>( pMPEG2Demux_ ), L"MPEG2 Demux" );
}



HRESULT
ISampleCaptureGraphBuilder::FindVideoPin(
                                CComPtr<IBaseFilter> pFilter,
                                CComPtr<IPin>& pPin  )
{
    if( !pFilter )
    {
        return E_POINTER;
    }

    CComPtr<IEnumPins> pEnumPins;
    HRESULT hr = pFilter->EnumPins( &pEnumPins );
    if( FAILED( hr ) )
    {
        return hr;
    }

    CComPtr<IPin>   pTempPin;
    ULONG           fetched;
    hr = pEnumPins->Reset( );

    while( pTempPin.Release(), S_OK == pEnumPins->Next( 1, &pTempPin, &fetched ) )
    {
        if( IsVideoPin( pTempPin ) )
        {
#ifdef DEBUG
            USES_CONVERSION;
            PIN_INFO info;
            pTempPin->QueryPinInfo( &info );
            info.pFilter->Release( );
#endif
            pPin = pTempPin;
            return S_OK;
        }
    }
    return E_FAIL;
}

BOOL ISampleCaptureGraphBuilder::IsAudioPin( CComPtr<IPin> pPin )
{
    if( !pPin )
    {
        return FALSE;   // NULL pointer
    }

    return HasMediaType( pPin, MEDIATYPE_Audio) ;
}


BOOL ISampleCaptureGraphBuilder::HasMediaType(CComPtr<IPin> pPin,  REFGUID majorType )
{
    if( !pPin )
    {
        return FALSE;
    }

    CComPtr<IEnumMediaTypes> pMediaTypes;
    HRESULT hr = pPin->EnumMediaTypes( &pMediaTypes );
    if( FAILED( hr ) )
    {
        return FALSE;
    }

    hr = pMediaTypes->Reset();
    if( FAILED( hr ) )
    {
        return FALSE;
    }

    ULONG           fetched;
    AM_MEDIA_TYPE   *mediaType;

    while( S_OK == pMediaTypes->Next( 1, &mediaType, &fetched ) )
    {
        if( ::IsEqualGUID( mediaType->majortype, majorType ) )
        {
            DeleteMediaType( mediaType );
            return TRUE;
        }
        DeleteMediaType( mediaType );
    }

    return FALSE;

}


HRESULT
ISampleCaptureGraphBuilder::FindAudioPin(
                                CComPtr<IBaseFilter> pFilter,
                                CComPtr<IPin>& pPin  )
{
    if( !pFilter )
    {
        return E_POINTER;
    }

    CComPtr<IEnumPins> pEnumPins;
    HRESULT hr = pFilter->EnumPins( &pEnumPins );
    if( FAILED( hr ) )
    {
        return hr;
    }

    CComPtr<IPin>   pTempPin;
    ULONG           fetched;
    hr = pEnumPins->Reset( );

    while( pTempPin.Release(), S_OK == pEnumPins->Next( 1, &pTempPin, &fetched ) )
    {
        if( IsAudioPin( pTempPin ) )
        {
#ifdef DEBUG
            USES_CONVERSION;
            PIN_INFO info;
            pTempPin->QueryPinInfo( &info );
            info.pFilter->Release( );
#endif
            pPin = pTempPin;
            return S_OK;
        }
    }
    return E_FAIL;
}



HRESULT ISampleCaptureGraphBuilder::FindEncoder(
                CComPtr<IEnumMoniker> pEncoders,
                REGPINMEDIUM pinMedium,
                CComPtr<IBaseFilter>& pEncoder  )
{
    if( ! pEncoders )
    {
        return E_INVALIDARG;
    }

    if( IsEqualGUID( pinMedium.clsMedium, GUID_NULL ) ||
        IsEqualGUID( pinMedium.clsMedium, KSMEDIUMSETID_Standard ) )
    {
        return E_INVALIDARG;
    }

    HRESULT                 hr;
    CComPtr<IBaseFilter>    pFilter;
    CComPtr<IMoniker>       pMoniker;
    ULONG                   fetched;
    CComPtr<IPin>           pPin;

    while( pFilter.Release(), pMoniker.Release(),
           S_OK == pEncoders->Next( 1, &pMoniker, &fetched ) )
    {
        hr = pMoniker->BindToObject(
            0, 0, IID_IBaseFilter, reinterpret_cast<void **>( &pFilter ) );
        if( FAILED( hr ) )
        {
            continue;
        }

        hr = FindPin( pFilter, pinMedium, PINDIR_INPUT, TRUE, pPin );
        if( SUCCEEDED( hr ) )
        {
            pEncoder = pFilter;
            return hr;
        }
    }

    return E_FAIL;
}



HRESULT
ISampleCaptureGraphBuilder::RenderToMPEG2Demux(
                            CComPtr<IPin> pPin,
                            CComPtr<IEnumMoniker> pEncoders)
{
    if( !pPin || !pEncoders )
    {
        return E_INVALIDARG;
    }

    REGPINMEDIUM pinMedium ;
    pinMedium.clsMedium = GUID_NULL;
    pinMedium.dw1 = 0;
    pinMedium.dw2 = 0;

    CComPtr<IBaseFilter> pFilter;
    CComPtr<IMoniker>    pMoniker;
    ULONG                fetched;
    HRESULT              hr;

    while( pFilter.Release(), pMoniker.Release(), S_OK == pEncoders->Next( 1, &pMoniker, &fetched ) )
    {
        hr = pMoniker->BindToObject(
            0, 0, IID_IBaseFilter, reinterpret_cast<void **>( &pFilter ) );
        if( FAILED( hr ) )
        {
            continue;
        }

        hr = graph_->AddFilter( pFilter, L"Encoder" );
        if( FAILED( hr ) )
        {
            continue;
        }

        hr = ConnectPin( pPin, pFilter );
        if( FAILED( hr ) )
        {
            graph_->RemoveFilter( pFilter );
            continue;
        }

        hr = ConnectEncoderToMPEG2Demux( pFilter, pinMedium );
        if( SUCCEEDED( hr ) )
        {
            pEncoder_ = pFilter;
            return S_OK;
        }
        graph_->RemoveFilter( pFilter );
    }

    return E_FAIL;
}


//
//  Loop through every encoder available on system.
//  Look first after the one that has a special medium if
//  there is a special one on pPin.
//  Otherwise, try to render using ICaptureGrapBuilder2
//  and the encoder that matches this will be the chosen one/
//  If the encoder is found, then this will be rendered to the
//  MPEG2 demux.
//

HRESULT
    ISampleCaptureGraphBuilder::RenderToMPEG2Demux(
        CComPtr<IPin> pPin,
        const REGPINMEDIUM& pinMedium,
        CComPtr<IEnumMoniker> pEncoders
)
{
    //
    //  The pin has a special medium,
    //  there shold be an encoder with the same
    //  medium
    //
    CComPtr< IBaseFilter > pEncoder;
    HRESULT hr = FindEncoder( pEncoders, pinMedium, pEncoder );
    if( FAILED( hr ) )
    {
        return hr;
    }

    hr = graph_->AddFilter( pEncoder, L"Encoder" );
    if( FAILED( hr ) )
    {
        return hr;
    }

    hr = ConnectPin( pPin, pEncoder );
    if( FAILED(  hr ) )
    {
        hr = graph_->RemoveFilter( pEncoder );
        return hr;
    }

    //
    //  the video pin was rendered to the same
    //  ( hardware? ) encoder with the same mediu
    //
    hr = ConnectEncoderToMPEG2Demux( pEncoder, pinMedium );
    if( FAILED( hr ) )
    {
        hr = graph_->RemoveFilter( pEncoder );
        return hr;
    }

    pEncoder_ = pEncoder;
    return S_OK;
}



HRESULT
ISampleCaptureGraphBuilder::RenderToMPEG2Demux( CComPtr<IPin> pPin )
{
    if( !pPin )
    {
        return E_INVALIDARG;
    }

    REGPINMEDIUM pinMedium;
    HRESULT hr = GetMedium( pPin, pinMedium );
    if( FAILED( hr ) )
    {
        return hr;
    }


    CComPtr< IEnumMoniker > pEncoders;
    if( ::IsEqualGUID( pinMedium.clsMedium, GUID_NULL ) )
    {
        //
        //  Search throgh the codec category
        //
        hr = GetEncodersByCategory( pEncoders );
        if( FAILED( hr ) )
        {
                return hr;
        }

        hr = RenderToMPEG2Demux( pPin, pEncoders );
        if( SUCCEEDED( hr ) )
        {
            return S_OK;
        }
    }
    else
    {
        //
        //  search through encoders category; identify
        //  the encoder using the medium
        //
        hr = GetEncodersByCategory( pEncoders );
        if( FAILED( hr ) )
        {
            return hr;
        }

        hr = RenderToMPEG2Demux( pPin, pinMedium, pEncoders  );
        if( SUCCEEDED( hr ) )
        {
            return S_OK;
        }

        pEncoders = NULL;
        hr = GetEncodersByEnumerating( pPin, pinMedium, pEncoders );
        if( FAILED( hr ) )
        {
            return hr;
        }

        hr = RenderToMPEG2Demux( pPin, pinMedium, pEncoders );
        if( FAILED( hr ) )
        {
            return hr;
        }
    }
    return S_OK;
}


//
//  pEncoder - the encoder to be connected using a multiplexer
//
//
HRESULT
ISampleCaptureGraphBuilder::ConnectEncoderToMPEG2Demux(
                CComPtr< IBaseFilter > pEncoder,
                const REGPINMEDIUM& pinMedium )
{

    REGPINMEDIUM regPinMedium ;
    regPinMedium.clsMedium = GUID_NULL;
    regPinMedium.dw1 = 0;
    regPinMedium.dw2 = 0;
    //
    //  try a direct connection between
    //  codec and MPEG2Demux
    //
    HRESULT hr = ConnectFilters(
                        pEncoder,
                        pMPEG2Demux_ );
    if( SUCCEEDED( hr ) )
    {
        return S_OK;
    }

    //
    //  no luck
    //  maybe I need a multiplexer
    //
    CComPtr< IEnumMoniker > pMultiplexers;
    hr = GetMultiplexersByCategory( pMultiplexers );
    if( FAILED( hr ) )
    {
        return hr;
    }
    hr = ConnectMultiplexerToMPEG2Demux( pEncoder, pMultiplexers );
    if( SUCCEEDED( hr ) )
    {
        return S_OK;
    }

    if( FALSE == ::IsEqualGUID( pinMedium.clsMedium, GUID_NULL ) )
    {
        //
        //  get the multiplexers using IFilterMapper2
        //  assuming that the encoder and the multiplexer have the same medium
        //
        pMultiplexers = NULL;
        hr = GetMultiplexersByFilterMapper( pMultiplexers, pinMedium );
        if( FAILED( hr ) )
        {
            return hr;
        }
        hr = ConnectMultiplexerToMPEG2Demux( pEncoder, pMultiplexers );
        if( SUCCEEDED( hr ) )
        {
            return S_OK;
        }
    }
    return E_FAIL;
}


HRESULT
ISampleCaptureGraphBuilder::GetMultiplexersByCategory( CComPtr<IEnumMoniker>& pMultiplexers )
{
    CComPtr<ICreateDevEnum> pDeviceEnum;

    HRESULT hr = pDeviceEnum.CoCreateInstance( CLSID_SystemDeviceEnum );
    if( FAILED( hr ) )
    {
        return hr;
    }

    return pDeviceEnum->CreateClassEnumerator( KSCATEGORY_MULTIPLEXER, &pMultiplexers, 0 );
}

HRESULT
ISampleCaptureGraphBuilder::GetMultiplexersByFilterMapper(
                                    CComPtr<IEnumMoniker>& pMultiplexers,
                                    const REGPINMEDIUM& pinMedium  )
{
    return E_NOTIMPL;
}


HRESULT
ISampleCaptureGraphBuilder::ConnectMultiplexerToMPEG2Demux(
                                        CComPtr<IBaseFilter> pEncoder,
                                        CComPtr< IEnumMoniker > pMultiplexers )
{
    if( !pEncoder || !pMultiplexers )
    {
        return E_INVALIDARG;
    }

    CComPtr<IBaseFilter> pFilter;
    CComPtr<IMoniker>   pMoniker;
    ULONG               fetched;
    HRESULT             hr;

    while( pFilter.Release(), pMoniker.Release(),
           S_OK == pMultiplexers->Next( 1, &pMoniker, &fetched ) )
    {
        hr = pMoniker->BindToObject(
            0, 0, IID_IBaseFilter, reinterpret_cast<void **>( &pFilter ) );
        if( FAILED( hr ) )
        {
            continue;
        }

        hr = graph_->AddFilter( pFilter, NULL );
        if( FAILED( hr ) )
        {
            continue;
        }

        //
        //  connect the encoder to the multiplexer
        //
        hr = ConnectFilters( pEncoder, pFilter );
        if( FAILED( hr ) )
        {
            graph_->RemoveFilter( pFilter );
            continue;
        }

        //
        //  connect the multiplexer to the encoder
        //
        hr = ConnectFilters( pFilter, pMPEG2Demux_ );
        if( SUCCEEDED( hr ) )
        {
            pMultiplexer_ = pFilter;
            return S_OK;
        }

    }

    return E_FAIL;
}


HRESULT
ISampleCaptureGraphBuilder::BuildMPEG2Segment(CComPtr<IBaseFilter> pFilter)
{

    if( ! pFilter )
    {
        return E_FAIL;
    }


    HRESULT hr = AddMPEG2Demux( );
    if( FAILED( hr ) )
    {
        return hr;
    }

    //
    //  Search a MPEG2 pin on the
    //  filter
    //
    CComPtr<IPin> pPin;
    hr = FindMPEG2Pin( pFilter, pPin );
    if( SUCCEEDED( hr ) )
    {
        hr = ConnectPin( pPin, pMPEG2Demux_ );
        if( FAILED( hr ) )
        {
            graph_->RemoveFilter( pMPEG2Demux_ );
            return E_FAIL;
        }
        return S_OK;
    }

    //
    //  no pins that streams directly MPEG2 stream
    //
    hr = FindVideoPin( pFilter, pPin );
    if( FAILED( hr ) )
    {
        graph_->RemoveFilter( pMPEG2Demux_ );
        return hr; // no video pin
    }

    hr = RenderToMPEG2Demux( pPin );
    if( FAILED( hr ) )
    {
        graph_->RemoveFilter( pMPEG2Demux_ );
        return hr;
    }

    CComPtr<IPin> pAudioPin;
    hr = FindAudioPin( pFilter, pAudioPin );
    if( FAILED( hr ) )
    {
        //
        //  don't bother with audio
        //
        return S_OK;
    }

    //
    //  try to connect the audio pin directly to encoder
    //  if this is not possible, then try to find an encoder
    //  and connect it to the multiplexer
    //
    ASSERT( pEncoder_ );
    hr = ConnectPin( pAudioPin, pEncoder_ );
    if( FAILED( hr ) )
    {
        hr = ConnectAudioPinToMultiplexer( pAudioPin, pMultiplexer_ );
    }

    return S_OK;
}


HRESULT
ISampleCaptureGraphBuilder::ConnectAudioPinToMultiplexer(
                                            CComPtr<IPin> pPin,
                                            CComPtr<IBaseFilter> pMultiplexer)
{
    if( !pPin || !pMultiplexer )
    {
        return E_INVALIDARG;
    }

    REGPINMEDIUM pinMedium;
    HRESULT hr = GetMedium( pPin, pinMedium );
    if( FAILED( hr ) )
    {
        return hr;
    }

    CComPtr<IBaseFilter> pEncoder;
    CComPtr<IEnumMoniker> pEncoders;

    if( FALSE == ::IsEqualGUID( pinMedium.clsMedium, GUID_NULL ) )
    {
        //
        //  search through encoders category; identify
        //  the encoder using the medium
        //
        hr = GetEncodersByCategory( pEncoders );
        if( FAILED( hr ) )
        {
            return hr;
        }

        hr = FindEncoder( pEncoders, pinMedium, pEncoder );
        if( SUCCEEDED( hr ) )
        {
            hr = graph_->AddFilter( pEncoder, L"Audio Encoder" );
            if( SUCCEEDED( hr ) &&
                SUCCEEDED( ConnectPin( pPin, pEncoder ) ) &&
                SUCCEEDED( ConnectFilters( pEncoder, pMultiplexer ) )
            )
            {
                return S_OK;
            }
        }


        pEncoders = NULL;
        hr = GetEncodersByEnumerating( pPin, pinMedium, pEncoders );
        if( FAILED( hr ) )
        {
            return hr;
        }

        hr = FindEncoder( pEncoders, pinMedium, pEncoder );
        if( SUCCEEDED( hr ) )
        {
            hr = graph_->AddFilter( pEncoder, L"Audio Encoder" );
            if( SUCCEEDED( hr ) &&
                SUCCEEDED( ConnectPin( pPin, pEncoder ) ) &&
                SUCCEEDED( ConnectFilters( pEncoder, pMultiplexer ) )
            )
            {
                return S_OK;
            }
        }
        return E_FAIL;
    }


    //
    //  Search throgh the codec category
    //
    hr = GetEncodersByCategory( pEncoders );
    if( FAILED( hr ) )
    {
        return hr;
    }


    CComPtr<IBaseFilter>    pFilter;
    CComPtr<IMoniker>       pMoniker;
    ULONG                   fetched;
    while( pFilter.Release(), pMoniker.Release(), S_OK == pEncoders->Next( 1, &pMoniker, &fetched ) )
    {
        hr = pMoniker->BindToObject(
            0, 0, IID_IBaseFilter, reinterpret_cast<void **>( &pFilter ) );
        if( FAILED( hr ) )
        {
            continue;
        }

        hr = graph_->AddFilter( pFilter, L"Audio Encoder" );
        if( FAILED( hr ) )
        {
            continue;
        }

        hr = ConnectPin( pPin, pFilter );
        if( FAILED( hr ) )
        {
            graph_->RemoveFilter( pFilter );
            continue;
        }

        hr = ConnectFilters( pFilter, pMultiplexer );
        if( SUCCEEDED( hr ) )
        {
            return S_OK;
        }
        graph_->RemoveFilter( pFilter );
    }

    return E_FAIL;

}


HRESULT
ISampleCaptureGraphBuilder::CreateVideoPin(
        CComPtr<IMpeg2Demultiplexer> pIMpeg2Demux )
{
    if( !pIMpeg2Demux )
    {
        return E_INVALIDARG;
    }

    AM_MEDIA_TYPE amTypeVideo;
    amTypeVideo.majortype = MEDIATYPE_Video;
    amTypeVideo.subtype = MEDIASUBTYPE_MPEG2_VIDEO;
    amTypeVideo.bFixedSizeSamples = TRUE;
    amTypeVideo.bTemporalCompression = 0;
    amTypeVideo.formattype = FORMAT_MPEG2Video;
    amTypeVideo.pUnk = NULL;
    amTypeVideo.cbFormat = sizeof( Mpeg2ProgramVideo );
    amTypeVideo.pbFormat = Mpeg2ProgramVideo;

    //
    // Create video pin
    //

    CComPtr<IPin> pVideoOutPin;
    HRESULT hr = pIMpeg2Demux->CreateOutputPin( &amTypeVideo, L"MpegVideo", &pVideoOutPin );
    if( FAILED( hr ) )
    {
        return hr;
    }


    CComPtr<IMPEG2StreamIdMap> pIVideoPIDMap;
    hr = pVideoOutPin->QueryInterface( &pIVideoPIDMap );
    if( FAILED( hr ) )
    {
        return hr;
    }

    hr = pIVideoPIDMap->MapStreamId(VidPID_, MPEG2_PROGRAM_ELEMENTARY_STREAM , 0, 0);
    if( FAILED( hr ) )
    {
        return hr;
    }


#ifdef USE_VMR
    //
    //  Get the VMR interface and add it to the graph
    //
    CComPtr<IBaseFilter> pVMR;
    hr = pVMR.CoCreateInstance( CLSID_VideoMixingRenderer );
    if( FAILED( hr ) )
    {
        return hr;
    }

    hr = graph_->AddFilter( pVMR, L"VMR" );
    if( FAILED( hr ) )
    {
        return hr;
    }

    //
    //before rendering the VMR, make the number of streams 1
    //
    CComPtr<IVMRFilterConfig> pConfig;
    hr = pVMR.QueryInterface( &pConfig );
    if( FAILED( hr ) )
    {
        return hr;
    }
    hr = pConfig->SetNumberOfStreams( 1 );
    if( FAILED( hr ) )
    {
        return hr;
    }


    //
    //  Get the input pin from the VMR
    //
    CComPtr<IPin> pInputPin;
    hr = graphBuilder2_->FindPin(
            static_cast<IBaseFilter *>( pVMR ),
            PINDIR_INPUT,
            NULL,
            NULL,
            TRUE,
            0,
            &pInputPin
        );
    if( FAILED( hr ) )
    {

        hr = pIMpeg2Demux->DeleteOutputPin(L"MpegVideo");
        graph_->RemoveFilter( pVMR );
        return hr;
    }

    return graph_->Connect( pVideoOutPin, pInputPin );
#endif

    return hr;
}



HRESULT
ISampleCaptureGraphBuilder::CreateAudioPin(
            CComPtr<IMpeg2Demultiplexer> pIMpeg2Demux
    )
{
    if( !pIMpeg2Demux )
    {
        return E_INVALIDARG;
    }

    //
    // for audio: could be Mpeg1, Mpeg2, AC3: if Mpeg1 failed (connect failed) try Mpeg2.if failed tried AC3
    // Audio struct of AC3 can be copied from dev code.
    //
    AM_MEDIA_TYPE amTypeAudio;
    amTypeAudio.majortype   = MEDIATYPE_Audio;
    amTypeAudio.subtype     = MEDIASUBTYPE_MPEG2_AUDIO;
    amTypeAudio.bFixedSizeSamples = TRUE;
    amTypeAudio.bTemporalCompression = 0;
    amTypeAudio.formattype  = FORMAT_WaveFormatEx;
    amTypeAudio.pUnk        = NULL;
    amTypeAudio.cbFormat    = sizeof( MPEG1AudioFormat );
    amTypeAudio.pbFormat    = MPEG1AudioFormat;


    CComPtr<IPin> pAudioOutPin;
    HRESULT hr = pIMpeg2Demux->CreateOutputPin(&amTypeAudio, L"MpegAudio", &pAudioOutPin);
    if( FAILED( hr ) )
    {
        return hr;
    }

    CComPtr<IMPEG2StreamIdMap> pIAudioPIDMap;
    hr = pAudioOutPin->QueryInterface( &pIAudioPIDMap );
    if( FAILED( hr ) )
    {
        return hr;
    }

    hr = pIAudioPIDMap->MapStreamId(AudPID_, MPEG2_PROGRAM_ELEMENTARY_STREAM, 0, 0);
    if( FAILED( hr ) )
    {
        return hr;
    }

    /*
    //
    //  Get the audio renderer
    //
    CComPtr<IBaseFilter> pAudioRenderer;
    hr = pAudioRenderer.CoCreateInstance( CLSID_AudioRender );
    if( FAILED( hr ) )
    {
        return hr;
    }

    hr = graph_->AddFilter( pAudioRenderer, L"Audio renderer" );
    if( FAILED( hr ) )
    {
        return hr;
    }

    CComPtr<IPin> pInputPin;
    hr = graphBuilder2_->FindPin(
            static_cast<IBaseFilter *>( pAudioRenderer ),
            PINDIR_INPUT,
            NULL,
            NULL,
            TRUE,
            0,
            &pInputPin
        );

    hr = graph_->Connect( pAudioOutPin, pInputPin );
    if(FAILED( hr ))
    {
        hr = pIMpeg2Demux->DeleteOutputPin(L"MpegAudio");
        graph_->RemoveFilter( pAudioRenderer );
    }
*/

    return hr;
}



HRESULT ISampleCaptureGraphBuilder::ConfigureMPEG2Demux( CComPtr<IBaseFilter> pFilter)
{

    if( ! pFilter )
    {
        return E_INVALIDARG;
    }

    //
    // Create video pin and render it
    //
    CComPtr<IMpeg2Demultiplexer> pIMpeg2Demux;
    HRESULT hr = pFilter.QueryInterface( &pIMpeg2Demux );
    if( FAILED( hr ) )
    {
        return hr;
    }

    hr = CreateVideoPin( pIMpeg2Demux );
    if( FAILED( hr ) )
    {
        return hr;
    }

    hr = CreateAudioPin( pIMpeg2Demux );
    if( FAILED( hr ) )
    {
        return hr;
    }

    return S_OK;
}


HRESULT
ISampleCaptureGraphBuilder::ConnectFilters(CComPtr<IBaseFilter> pUpFilter, CComPtr<IBaseFilter> pDownFilter)
{
    if( !pUpFilter || !pDownFilter )
    {
        return E_INVALIDARG;
    }

    // All the need pin & pin enumerator pointers
    CComPtr<IEnumPins>  pEnumUpFilterPins ,
                        pEnumDownFilterPins;

    CComPtr<IPin>   pUpFilterPin ,
                    pDownFilterPin;

    HRESULT hr = S_OK;

    // Get the pin enumerators for both the filtera
    hr = pUpFilter->EnumPins(&pEnumUpFilterPins);
    if( FAILED( hr ) )
    {
        return hr;
    }

    hr= pDownFilter->EnumPins(&pEnumDownFilterPins);
    if( FAILED( hr ) )
    {
        return hr;
    }


    // Loop on every pin on the Upstream Filter
    BOOL bConnected = FALSE;
    PIN_DIRECTION pinDir;
    ULONG nFetched = 0;
    while(pUpFilterPin.Release( ), S_OK == pEnumUpFilterPins->Next(1, &pUpFilterPin, &nFetched) )
    {
        // Make sure that we have the output pin of the upstream filter
        hr = pUpFilterPin->QueryDirection( &pinDir );
        if( FAILED( hr ) || PINDIR_INPUT == pinDir )
        {
            continue;
        }

        //
        // I have an output pin; loop on every pin on the Downstream Filter
        //
        while(pDownFilterPin.Release( ), S_OK == pEnumDownFilterPins->Next(1, &pDownFilterPin, &nFetched) )
        {
            hr = pDownFilterPin->QueryDirection( &pinDir );
            if( FAILED( hr ) || PINDIR_OUTPUT == pinDir )
            {
                continue;
            }

            // Try to connect them and exit if u can else loop more until you can
            if(SUCCEEDED(graph_->ConnectDirect(pUpFilterPin, pDownFilterPin, NULL)))
            {
                bConnected = TRUE;
                break;
            }
        }

        hr = pEnumDownFilterPins->Reset();
        if( FAILED( hr ) )
        {
            return hr;
        }
    }

    if( !bConnected )
    {
        return E_FAIL;
    }

    return S_OK;
}


HRESULT
ISampleCaptureGraphBuilder::ConnectPin(
                    CComPtr<IPin> pPin,
                    CComPtr< IBaseFilter > pDownFilter )
{
    if( !pPin || !pDownFilter )
    {
        return E_INVALIDARG;
    }

    PIN_DIRECTION   pinDirection;
    HRESULT hr = pPin->QueryDirection( &pinDirection );
    if( FAILED( hr ) || PINDIR_INPUT == pinDirection )
    {
        return E_FAIL;
    }

    //
    //  Add the filter to the graph
    //
    BOOL bConnected = FALSE;
    ULONG nFetched = 0;
    CComPtr<IPin> pDownFilterPin;

    //
    //  Loop through every input pin from downstream filter
    //  and try to connect the pin
    //
    CComPtr< IEnumPins > pEnumDownFilterPins;
    hr= pDownFilter->EnumPins( &pEnumDownFilterPins );
    if( FAILED( hr ) )
    {
        return hr;
    }

    while(pDownFilterPin.Release( ), S_OK == pEnumDownFilterPins->Next(1, &pDownFilterPin, &nFetched) )
    {
        hr = pDownFilterPin->QueryDirection( &pinDirection );
        if( FAILED( hr ) )
        {
            continue;
        }
        if( PINDIR_OUTPUT == pinDirection )
        {
            continue;
        }

        hr = graph_->ConnectDirect(pPin, pDownFilterPin, NULL);
        if(SUCCEEDED(hr))
        {
            bConnected = TRUE;
            break;
        }
    }

    if( !bConnected )
    {
        graph_->RemoveFilter( pDownFilter );
        return E_FAIL;
    }

    return S_OK;
}

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
//include "SampleGrabber.h"
class SampleGrabberCB : public ISampleGrabberCB
 {

	public:

		// These will get set by the main thread below. We need to
		// know this in order to write out the bmp
		long bufferSize;
		unsigned char *buffer;
		int frameId;
		bool frameWanted;
		HANDLE event;

		// Fake out any COM ref counting
		//
		STDMETHODIMP_(ULONG) AddRef() { return 2; }
		STDMETHODIMP_(ULONG) Release() { return 1; }

		// Fake out any COM QI'ing
		//
		STDMETHODIMP QueryInterface(REFIID riid, void ** ppv)
		 {
			if (!ppv) return E_POINTER;

			if( riid == IID_ISampleGrabberCB || riid == IID_IUnknown )
			 {
				*ppv = (void *) static_cast<ISampleGrabberCB*> ( this );
				return NOERROR;
			 }

			return E_NOINTERFACE;
		 }


		// We don't implement this one
		//
		STDMETHODIMP SampleCB( double SampleTime, IMediaSample * pSample )
		 {
			return 0;
		 }


		// The sample grabber is calling us back on its deliver thread.
		// This is NOT the main app thread!
		//
		STDMETHODIMP BufferCB( double SampleTime, BYTE * pBuffer, long realBufferSize )
		 {
			//frameId++;
			if ( !frameWanted )
				return 0;

			if (realBufferSize > bufferSize)
			 {
				fprintf(stderr, __FILE__ ": error ! image size too big !!\n");
				return 0;
			 }

			memcpy(buffer, pBuffer, bufferSize);

			frameWanted=false;

			SetEvent(event);

			return 0;
		 }
 };














////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////






















//------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------
#define ABS(x) (((x) > 0) ? (x) : -(x))


// Macros
#define SAFE_RELEASE(x) { if (x) x->Release(); x = NULL; }




// An application can advertise the existence of its filter graph
// by registering the graph with a global Running Object Table (ROT).
// The GraphEdit application can detect and remotely view the running
// filter graph, allowing you to 'spy' on the graph with GraphEdit.
//
// To enable registration in this sample, define REGISTER_FILTERGRAPH.
//
#ifdef  DEBUG
#define REGISTER_FILTERGRAPH
#endif


//------------------------------------------------------------------------------
// Global data
//------------------------------------------------------------------------------

HDEVNOTIFY ghDevNotify=0;

PUnregisterDeviceNotification gpUnregisterDeviceNotification=0;
PRegisterDeviceNotification gpRegisterDeviceNotification=0;



struct vipDXCapture2
{
    HWND ghwndApp;

    TCHAR szCaptureFile[_MAX_PATH];
    WORD wCapFileSize;  // size in Meg
    ISampleCaptureGraphBuilder *pBuilder;
    IVideoWindow *pVW;
    IMediaEventEx *pME;
    IAMDroppedFrames *pDF;
    IAMVideoCompression *pVC;
    IAMVfwCaptureDialogs *pDlg;
    IAMStreamConfig *pASC;      // for audio cap
    IAMStreamConfig *pVSC;      // for video cap
    IBaseFilter *pRender;
    IBaseFilter *pVCap, *pACap;
    IGraphBuilder *pFg;
    IFileSinkFilter *pSink;
    IConfigAviMux *pConfigAviMux;

    ISampleGrabber* pSampleGrabber;
	IBaseFilter* pGrabberBaseFilter;
	bool GrabbingEnabled;
	SampleGrabberCB* pCallbackGrabber;
	IBaseFilter* null_filter;
	IBaseFilter* pSmartTeeFilter;

	IMediaControl* pMC; // not used now

    int  iMasterStream;
    bool fCaptureGraphBuilt;
    bool fPreviewGraphBuilt;
    bool fCapturing;
    bool fPreviewing;
    bool fMPEG2;
    bool fCapAudio;
    bool fCapCC;
    bool fCCAvail;
    bool fCapAudioIsRelevant;

    IMoniker *rgpmVideoMenu[10];
    IMoniker *rgpmAudioMenu[10];
    IMoniker *pmVideo;
    IMoniker *pmAudio;

	int pmAudioIndex;
	int pmVideoIndex;

    double FrameRate;
    bool fWantPreview;
    long lCapStartTime;
    long lCapStopTime;
    WCHAR wachVideoFriendlyName[256];
	WCHAR wachAudioFriendlyName[256];
    bool fUseTimeLimit;
    bool fUseFrameRate;
    DWORD dwTimeLimit;
    int iFormatDialogPos;
    int iSourceDialogPos;
    int iDisplayDialogPos;
    int iVCapDialogPos;
    int iVCrossbarDialogPos;
    int iTVTunerDialogPos;
    int iACapDialogPos;
    int iACrossbarDialogPos;
    int iTVAudioDialogPos;
    int iVCapCapturePinDialogPos;
    int iVCapPreviewPinDialogPos;
    int iACapCapturePinDialogPos;
    long lDroppedBase;
    long lNotBase;
    long lDroppedCurrent;
    long lNotCurrent;
	long lAvgFrameSizeCurrent;
    double flFrameCurrent;     // acheived frame rate
    long lDataCurrent;         // acheived data rate

    bool fPreviewFaked;
//    CCrossbar *pCrossbar;
    int iVideoInputMenuPos;
    LONG NumberOfVideoInputs;

    int iNumVCapDevices;
    int iNumACapDevices;

    bool displayErrorMessages;
    bool autoUpdateWindow;

	vipDirectXInput2::FORMAT_CSP format_CSP;

    DWORD VideoBitRate;
    DWORD AudioBitRate;
};




//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------
typedef LONG(PASCAL *LPWNDPROC)(HWND, UINT, WPARAM, LPARAM); // pointer to a window procedure

/*
int FAR PASCAL AllocCapFileProc(HWND hDlg, UINT Message, UINT wParam, LONG lParam);
int FAR PASCAL FrameRateProc(HWND hDlg, UINT Message, UINT wParam, LONG lParam);
int FAR PASCAL TimeLimitProc(HWND hDlg, UINT Message, UINT wParam, LONG lParam);
int FAR PASCAL PressAKeyProc(HWND hDlg, UINT Message, UINT wParam, LONG lParam);
*/







//
// This function can be used when loading libraries in the Windows System
// folder.  It queries for the system folder and prepends the path to the
// name of the target library.  This helps to prevent spoofing of system DLLs.
//
// NOTE: Using this function may break apps who use Windows Fusion or who
// explicitly replace Windows DLLs in the application's local folder.
// If security is paramount, you can use this as a replacement for LoadLibrary().
//
static HMODULE UtilLoadLibrary(LPCTSTR lpFileName);


static DWORDLONG GetSize(LPCTSTR tach);

void ErrMsg(HWND ghwndApp, bool show, LPTSTR szFormat,...);

static long GetFreeDiskSpaceInKB(LPTSTR pFile);

void IMonRelease(IMoniker *&pm);

void NukeDownstream(vipDXCapture2* cCap, IBaseFilter *pf);


		// Adds/removes a DirectShow filter graph from the Running Object Table,
		// allowing GraphEdit to "spy" on a remote filter graph if enabled.
HRESULT AddGraphToRot(IUnknown *pUnkGraph, DWORD *pdwRegister);



static char* Wide2Char(WCHAR* wstr);


static void ResizeWindow(HWND ghwndApp, int w, int h);




// make sure the preview window inside our window is as big as the
// dimensions of captured video, or some capture cards won't show a preview.
// (Also, it helps people tell what size video they're capturing)
// We will resize our app's window big enough so that once the status bar
// is positioned at the bottom there will be enough room for the preview
// window to be w x h
//
int gnRecurse = 0;











////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////



vipDirectXInput2::vipDirectXInput2(int device)
 {

	CoInitialize(NULL);

	g_dwGraphRegister = 0;

	cCap = (vipDXCapture2*)malloc(sizeof(vipDXCapture2));
	memset(cCap, 0, sizeof(vipDXCapture2));


	cCap->ghwndApp = 0;

    cCap->fCapAudio = TRUE;
    cCap->fCapCC    = FALSE;
	cCap->fCapAudioIsRelevant = FALSE;

	cCap->fCapturing = FALSE;
	cCap->fPreviewing = FALSE;
	cCap->fWantPreview = FALSE;
    cCap->iMasterStream = 1;
    cCap->GrabbingEnabled = false;

	cCap->pmAudioIndex = -1;
	cCap->pmVideoIndex = -1;

    ZeroMemory(cCap->rgpmAudioMenu, sizeof(cCap->rgpmAudioMenu));
    ZeroMemory(cCap->rgpmVideoMenu, sizeof(cCap->rgpmVideoMenu));
    cCap->pmVideo = 0;
    cCap->pmAudio = 0;
    cCap->fMPEG2  = FALSE;
	cCap->fPreviewFaked = FALSE;

	cCap->wCapFileSize = 10; // 10 mb

    // get the frame rate from win.ini before making the graph
	cCap->fUseFrameRate = TRUE;

    int units_per_frame = 666667;  // 15fps
    cCap->FrameRate = 10000000. / units_per_frame;
    cCap->FrameRate = (int)(cCap->FrameRate * 100) / 100.;

    // reasonable default
	cCap->FrameRate = 15.0;

    cCap->fUseTimeLimit = 0;
    cCap->dwTimeLimit   = 100;


    cCap->iNumVCapDevices = 0;
    cCap->iNumACapDevices = 0;

	cCap->displayErrorMessages = true;
	cCap->autoUpdateWindow = true;

	width = 0;
	height = 0;

 }


vipDirectXInput2::~vipDirectXInput2()
 {

	Close();

    // Unregister device notifications
    if(ghDevNotify != NULL)
    {
        ASSERT(gpUnregisterDeviceNotification);
        gpUnregisterDeviceNotification(ghDevNotify);
        ghDevNotify = NULL;
    }

	IMonRelease(cCap->pmVideo);
	IMonRelease(cCap->pmAudio);

	for(int i = 0; i < NUMELMS(cCap->rgpmVideoMenu); i++)
	 {
		IMonRelease(cCap->rgpmVideoMenu[i]);
	 }

	for(i = 0; i < NUMELMS(cCap->rgpmAudioMenu); i++)
	 {
		IMonRelease(cCap->rgpmAudioMenu[i]);
	 }


	delete cCap;


	CoUninitialize( );
 }




////////////////////////////////////////////////////////////////////////////////////////////


void vipDirectXInput2::Close()
{

    if(cCap->fPreviewing)
    	StopPreview();

    if(cCap->fCapturing)
	    StopCapture();


    // Destroy the filter graph and cleanup
    TearDownGraph();
    FreeCapFilters();

}



////////////////////////////////////////////////////////////////////////////////////////////


// Make a graph builder object we can use for capture graph building
//
int vipDirectXInput2::MakeBuilder()
 {
    // we have one already
    if(cCap->pBuilder)
        return VIPRET_OK;

    cCap->pBuilder = new ISampleCaptureGraphBuilder( );

    if( cCap->pBuilder == NULL )
     {
		ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Error: Cannot create capture Graph Builder (SampleCGB)"));
		return VIPRET_INTERNAL_ERR;
	 }

    return VIPRET_OK;
 }

////////////////////////////////////////////////////////////////////////////////////////////
// Make a graph object we can use for capture graph building
//
int vipDirectXInput2::MakeGraph()
 {
    // we have one already
    if(cCap->pFg)
        return VIPRET_OK;

    HRESULT hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC,
                                  IID_IGraphBuilder, (LPVOID *)&cCap->pFg);

	if ( hr == NOERROR )
		return VIPRET_OK;

	else if ( hr == E_NOINTERFACE )
	 {
		ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Error: Cannot find filter IID_IGraphBuilder.\r\nIs DirectX installed and running?"));
		return VIPRET_INTERNAL_ERR;
	 }

	return VIPRET_OK;
 }



////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////



// Tear down everything downstream of the capture filters, so we can build
// a different capture graph.  Notice that we never destroy the capture filters
// and WDM filters upstream of them, because then all the capture settings
// we've set would be lost.
//
void vipDirectXInput2::TearDownGraph()
{
    SAFE_RELEASE(cCap->pSink);
    SAFE_RELEASE(cCap->pConfigAviMux);
    SAFE_RELEASE(cCap->pRender);
    SAFE_RELEASE(cCap->pME);
    SAFE_RELEASE(cCap->pDF);

    if(cCap->pVW)
    {
        // stop drawing in our window, or we may get wierd repaint effects
        cCap->pVW->put_Owner(NULL);
        cCap->pVW->put_Visible(OAFALSE);
        cCap->pVW->Release();
        cCap->pVW = NULL;
    }

    // destroy the graph downstream of our capture filters
    if(cCap->pVCap)
        NukeDownstream(cCap, cCap->pVCap);
    if(cCap->pACap)
        NukeDownstream(cCap, cCap->pACap);
    if(cCap->pVCap)
        cCap->pBuilder->ReleaseFilters();

    // potential debug output - what the graph looks like
    // if (cCap->pFg) DumpGraph(cCap->pFg, 1);

#ifdef REGISTER_FILTERGRAPH
    // Remove filter graph from the running object table
    if(g_dwGraphRegister)
    {
        RemoveGraphFromRot(g_dwGraphRegister);
        g_dwGraphRegister = 0;
    }
#endif

    cCap->fCaptureGraphBuilt = FALSE;
    cCap->fPreviewGraphBuilt = FALSE;
    cCap->fPreviewFaked = FALSE;
}


////////////////////////////////////////////////////////////////////////////////////////////



// Removes a filter graph from the Running Object Table
int vipDirectXInput2::RemoveGraphFromRot(DWORD pdwRegister)
 {
	IRunningObjectTable *pROT;

	if( SUCCEEDED(GetRunningObjectTable(0, &pROT)) )
	 {
		pROT->Revoke(pdwRegister);
		pROT->Release();
		return VIPRET_OK;
	 }

	ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Error: Falied to remove graph from the Running Object Table.\r\nCan't get current ROT."));
	return VIPRET_INTERNAL_ERR;
 }


////////////////////////////////////////////////////////////////////////////////////////////






////////////////////////////////////////////////////////////////////////////////////////////


// Adds a DirectShow filter graph to the Running Object Table,
// allowing GraphEdit to "spy" on a remote filter graph.
HRESULT AddGraphToRot(IUnknown *pUnkGraph, DWORD *pdwRegister)
 {
	IMoniker * pMoniker;
	IRunningObjectTable *pROT;
	WCHAR wsz[128];
	HRESULT hr;

	if (!pUnkGraph || !pdwRegister)
		return E_POINTER;

	if(FAILED(GetRunningObjectTable(0, &pROT)))
		return E_FAIL;

	wsprintfW( wsz, L"FilterGraph %08x pid %08x\0", (DWORD_PTR)pUnkGraph, GetCurrentProcessId() );

	hr = CreateItemMoniker(L"!", wsz, &pMoniker);
	if( SUCCEEDED(hr) )
	 {
		// Use the ROTFLAGS_REGISTRATIONKEEPSALIVE to ensure a strong reference
		// to the object.  Using this flag will cause the object to remain
		// registered until it is explicitly revoked with the Revoke() method.
		//
		// Not using this flag means that if GraphEdit remotely connects
		// to this graph and then GraphEdit exits, this object registration
		// will be deleted, causing future attempts by GraphEdit to fail until
		// this application is restarted or until the graph is registered again.
		hr = pROT->Register(ROTFLAGS_REGISTRATIONKEEPSALIVE, pUnkGraph, pMoniker, pdwRegister);
		pMoniker->Release();
	 }

	pROT->Release();
	return hr;
 }















////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

// create the capture filters of the graph.  We need to keep them loaded from
// the beginning, so we can set parameters on them and have them remembered
//
int vipDirectXInput2::InitCapFilters()
{
	HRESULT hr=S_OK;

	cCap->fCCAvail = FALSE;  // assume no closed captioning support

	if( MakeBuilder() )
	 {
		ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Cannot instantiate graph builder"));
		return VIPRET_INTERNAL_ERR;
	 }

	//
	// First, we need a Video Capture filter, and some interfaces
	//
	cCap->pVCap = NULL;

    if(cCap->pmVideo != 0)
    {
        IPropertyBag *pBag;
        cCap->wachVideoFriendlyName[0] = 0;

        hr = cCap->pmVideo->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
        if(SUCCEEDED(hr))
        {
            VARIANT var;
            var.vt = VT_BSTR;

            hr = pBag->Read(L"FriendlyName", &var, NULL);
            if(hr == NOERROR)
            {
                lstrcpyW(cCap->wachVideoFriendlyName, var.bstrVal);
                SysFreeString(var.bstrVal);
            }

            pBag->Release();
        }

        hr = cCap->pmVideo->BindToObject(0, 0, IID_IBaseFilter, (void**)&cCap->pVCap);
    }

	if(cCap->pVCap == NULL)
	 {
		ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Error %x: Cannot create video capture filter"), hr);
		goto InitCapFiltersFail;
	 }

	//
	// make a filtergraph, give it to the graph builder and put the video
	// capture filter in the graph
	//

	if( MakeGraph() )
	 {
		ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Cannot instantiate filtergraph"));
		goto InitCapFiltersFail;
	 }

	hr = cCap->pBuilder->SetFiltergraph(cCap->pFg);
	if(hr != NOERROR)
	 {
		ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Cannot give graph to builder"));
		goto InitCapFiltersFail;
	 }

	// Add the video capture filter to the graph with its friendly name
	hr = cCap->pFg->AddFilter(cCap->pVCap, cCap->wachVideoFriendlyName);
	if(hr != NOERROR)
	 {
		ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Error %x: Cannot add vidcap to filtergraph"), hr);
		goto InitCapFiltersFail;
	 }

	// Calling FindInterface below will result in building the upstream
	// section of the capture graph (any WDM TVTuners or Crossbars we might
	// need).

	// we use this interface to get the name of the driver
	// Don't worry if it doesn't work:  This interface may not be available
	// until the pin is connected, or it may not be available at all.
	// (eg: interface may not be available for some DV capture)
    hr = cCap->pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,
                                      &MEDIATYPE_Interleaved, cCap->pVCap,
                                      IID_IAMVideoCompression, (void **)&cCap->pVC);
    if(hr != S_OK)
    {
        hr = cCap->pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,
                                          &MEDIATYPE_Video, cCap->pVCap,
                                          IID_IAMVideoCompression, (void **)&cCap->pVC);
    }

    // !!! What if this interface isn't supported?
    // we use this interface to set the frame rate and get the capture size
    hr = cCap->pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,
                                      &MEDIATYPE_Interleaved,
                                      cCap->pVCap, IID_IAMStreamConfig, (void **)&cCap->pVSC);

    if(hr != NOERROR)
    {
        hr = cCap->pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,
                                          &MEDIATYPE_Video, cCap->pVCap,
                                          IID_IAMStreamConfig, (void **)&cCap->pVSC);
        if(hr != NOERROR)
        {
            // this means we can't set frame rate (non-DV only)
            ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Error %x: Cannot find VCapture:IAMStreamConfig"), hr);
        }
    }

    cCap->fCapAudioIsRelevant = TRUE;

    AM_MEDIA_TYPE *pmt;

    // default capture format
    if(cCap->pVSC && cCap->pVSC->GetFormat(&pmt) == S_OK)
    {
        // DV capture does not use a VIDEOINFOHEADER
        if(pmt->formattype == FORMAT_VideoInfo)
        {

			width = HEADER(pmt->pbFormat)->biWidth;
			height = abs(HEADER(pmt->pbFormat)->biHeight);

//TODO			cCap->VideoBitRate = HEADER(pmt->pbFormat)->biWidth;

            // resize our window to the default capture size
			if ( cCap->autoUpdateWindow )
				ResizeWindow(cCap->ghwndApp, width, height);

        }
        if(pmt->majortype != MEDIATYPE_Video)
        {
            // This capture filter captures something other that pure video.
            // Maybe it's DV or something?  Anyway, chances are we shouldn't
            // allow capturing audio separately, since our video capture
            // filter may have audio combined in it already!
            cCap->fCapAudioIsRelevant = FALSE;
            cCap->fCapAudio = FALSE;
        }

        if (pmt->subtype == MEDIASUBTYPE_RGB24)
         {
			cCap->format_CSP = VETFRAMET_CS_RGB;
		 }

        DeleteMediaType(pmt);
    }

    // we use this interface to bring up the 3 dialogs
    // NOTE:  Only the VfW capture filter supports this.  This app only brings
    // up dialogs for legacy VfW capture drivers, since only those have dialogs
    hr = cCap->pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,
                                      &MEDIATYPE_Video, cCap->pVCap,
                                      IID_IAMVfwCaptureDialogs, (void **)&cCap->pDlg);

    // Use the crossbar class to help us sort out all the possible video inputs
    // The class needs to be given the capture filters ANALOGVIDEO input pin
    {
        IPin        *pP = 0;
        IEnumPins   *pins=0;
        ULONG        n;
        PIN_INFO     pinInfo;
        bool         Found = false;
        IKsPropertySet *pKs=0;
        GUID guid;
        DWORD dw;
        bool fMatch = false;

//        cCap->pCrossbar = NULL;

        if(SUCCEEDED(cCap->pVCap->EnumPins(&pins)))
        {
            while(!Found && (S_OK == pins->Next(1, &pP, &n)))
            {
                if(S_OK == pP->QueryPinInfo(&pinInfo))
                {
                    if(pinInfo.dir == PINDIR_INPUT)
                    {
                        // is this pin an ANALOGVIDEOIN input pin?
                        if(pP->QueryInterface(IID_IKsPropertySet,
                            (void **)&pKs) == S_OK)
                        {
                            if(pKs->Get(AMPROPSETID_Pin,
                                AMPROPERTY_PIN_CATEGORY, NULL, 0,
                                &guid, sizeof(GUID), &dw) == S_OK)
                            {
                                if(guid == PIN_CATEGORY_ANALOGVIDEOIN)
                                    fMatch = TRUE;
                            }
                            pKs->Release();
                        }

                        if(fMatch)
                        {
                            HRESULT hrCreate=S_OK;
//                            cCap->pCrossbar = new CCrossbar(pP, &hrCreate);
  //                          if (!cCap->pCrossbar || FAILED(hrCreate))
                                break;

//                            hr = cCap->pCrossbar->GetInputCount(&cCap->NumberOfVideoInputs);
                            Found = TRUE;
                        }
                    }
                    pinInfo.pFilter->Release();
                }
                pP->Release();
            }
            pins->Release();
        }
    }

	cCap->wachAudioFriendlyName[0] = 0;

    // there's no point making an audio capture filter
    if(cCap->fCapAudioIsRelevant == FALSE)
        goto SkipAudio;

    // create the audio capture filter, even if we are not capturing audio right
    // now, so we have all the filters around all the time.

    //
    // We want an audio capture filter and some interfaces
    //

    if(cCap->pmAudio == 0)
    {
        // there are no audio capture devices. We'll only allow video capture
        cCap->fCapAudio = FALSE;
        goto SkipAudio;
    }
    cCap->pACap = NULL;


    hr = cCap->pmAudio->BindToObject(0, 0, IID_IBaseFilter, (void**)&cCap->pACap);

    if(cCap->pACap == NULL)
    {
        // there are no audio capture devices. We'll only allow video capture
        cCap->fCapAudio = FALSE;
        ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Cannot create audio capture filter"));
        goto SkipAudio;
    }

    //
    // put the audio capture filter in the graph
    //
    {
        IPropertyBag *pBag;

        cCap->wachAudioFriendlyName[0] = 0;

        // Read the friendly name of the filter to assist with remote graph
        // viewing through GraphEdit
        hr = cCap->pmAudio->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
        if(SUCCEEDED(hr))
        {
            VARIANT var;
            var.vt = VT_BSTR;

            hr = pBag->Read(L"FriendlyName", &var, NULL);
            if(hr == NOERROR)
            {
                lstrcpyW(cCap->wachAudioFriendlyName, var.bstrVal);
                SysFreeString(var.bstrVal);
            }

            pBag->Release();
        }

        // We'll need this in the graph to get audio property pages
        hr = cCap->pFg->AddFilter(cCap->pACap, cCap->wachAudioFriendlyName);
        if(hr != NOERROR)
        {
            ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Error %x: Cannot add audio capture filter to filtergraph"), hr);
            goto InitCapFiltersFail;
        }
    }

    // Calling FindInterface below will result in building the upstream
    // section of the capture graph (any WDM TVAudio's or Crossbars we might
    // need).

    // !!! What if this interface isn't supported?
    // we use this interface to set the captured wave format
    hr = cCap->pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Audio, cCap->pACap,
                                      IID_IAMStreamConfig, (void **)&cCap->pASC);

    if(hr != NOERROR)
    {
        ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Cannot find ACapture:IAMStreamConfig"));
    }

SkipAudio:

    // Can this filter do closed captioning?
    IPin *pPin;
    hr = cCap->pBuilder->FindPin(cCap->pVCap, PINDIR_OUTPUT, &PIN_CATEGORY_VBI,
                                NULL, FALSE, 0, &pPin);
    if(hr != S_OK)
        hr = cCap->pBuilder->FindPin(cCap->pVCap, PINDIR_OUTPUT, &PIN_CATEGORY_CC,
                                    NULL, FALSE, 0, &pPin);
    if(hr == S_OK)
    {
        pPin->Release();
        cCap->fCCAvail = TRUE;
    }
    else
    {
        cCap->fCapCC = FALSE;    // can't capture it, then
    }

    // potential debug output - what the graph looks like
    // DumpGraph(cCap->pFg, 1);

    return VIPRET_OK;

InitCapFiltersFail:
    FreeCapFilters();
    return VIPRET_INTERNAL_ERR;
}

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

// all done with the capture filters and the graph builder
//
void vipDirectXInput2::FreeCapFilters()
 {
	SAFE_RELEASE(cCap->pFg);

	if( cCap->pBuilder )
	 {
		delete cCap->pBuilder;
		cCap->pBuilder = NULL;
	 }

	SAFE_RELEASE(cCap->pVCap);
	SAFE_RELEASE(cCap->pACap);
	SAFE_RELEASE(cCap->pASC);
	SAFE_RELEASE(cCap->pVSC);
	SAFE_RELEASE(cCap->pVC);
	SAFE_RELEASE(cCap->pDlg);

	SAFE_RELEASE(cCap->pGrabberBaseFilter);

	SAFE_RELEASE(cCap->pCallbackGrabber);

	SAFE_RELEASE(cCap->pSmartTeeFilter);

 }

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

// build the capture graph
//
int vipDirectXInput2::BuildCaptureGraph()
{
    USES_CONVERSION;

	HRESULT hr;
    AM_MEDIA_TYPE *pmt=0;

    // we have one already
    if(cCap->fCaptureGraphBuilt)
        return VIPRET_OK; // mmh bad

    // No rebuilding while we're running
    if(cCap->fCapturing || cCap->fPreviewing)
        return VIPRET_ILLEGAL_USE;

    // We don't have the necessary capture filters
    if(cCap->pVCap == NULL)
        return VIPRET_ILLEGAL_USE;
    if(cCap->pACap == NULL && cCap->fCapAudio)
        return VIPRET_ILLEGAL_USE;

    // we already have another graph built... tear down the old one
    if( cCap->fPreviewGraphBuilt )
        TearDownGraph();

    //
    // We need a rendering section that will write the capture file out in AVI
    // file format
    //

    GUID guid;
    if( cCap->fMPEG2 )
    {
        guid = MEDIASUBTYPE_Mpeg2;
    }
    else
    {
        guid = MEDIASUBTYPE_Avi;
    }

    hr = cCap->pBuilder->SetOutputFileName(&guid, T2W(cCap->szCaptureFile),
                                          &cCap->pRender, &cCap->pSink);
    if(hr != NOERROR)
    {
		if (hr == E_FAIL)
	        ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("FAILIED: Setting file name\r\nFailure."));
		else if (hr == E_INVALIDARG)
	        ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("FAILIED: Setting file name\r\nAVI is the only supported output format. (try to update directx?)"));
		else if (hr == E_UNEXPECTED)
	        ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("FAILIED: Setting file name\r\nUnexpected error occurred."));
		else if (hr == E_OUTOFMEMORY)
	        ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("FAILIED: Setting file name\r\nOut of Memory."));
		else
        	ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("FAILIED: Setting file name\r\nUnknown ErrorCode."));

        goto SetupCaptureFail;
    }

    // Now tell the AVIMUX to write out AVI files that old apps can read properly.
    // If we don't, most apps won't be able to tell where the keyframes are,
    // slowing down editing considerably
    // Doing this will cause one seek (over the area the index will go) when
    // you capture past 1 Gig, but that's no big deal.
    // NOTE: This is on by default, so it's not necessary to turn it on

    // Also, set the proper MASTER STREAM

    if( !cCap->fMPEG2 )
    {
        hr = cCap->pRender->QueryInterface(IID_IConfigAviMux, (void **)&cCap->pConfigAviMux);
        if(hr == NOERROR && cCap->pConfigAviMux)
        {
            cCap->pConfigAviMux->SetOutputCompatibilityIndex(TRUE);
            if(cCap->fCapAudio)
            {
                hr = cCap->pConfigAviMux->SetMasterStream(cCap->iMasterStream);
                if(hr != NOERROR)
                    ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("SetMasterStream failed!"));
            }
        }
    }


//to add here: cCap->pBuilder->RenderFile(wFile, NULL);

    //
    // Render the video capture and preview pins - even if the capture filter only
    // has a capture pin (and no preview pin) this should work... because the
    // capture graph builder will use a smart tee filter to provide both capture
    // and preview.  We don't have to worry.  It will just work.
    //

    // NOTE that we try to render the interleaved pin before the video pin, because
    // if BOTH exist, it's a DV filter and the only way to get the audio is to use
    // the interleaved pin.  Using the Video pin on a DV filter is only useful if
    // you don't want the audio.

    if( !cCap->fMPEG2 )
    {
        hr = cCap->pBuilder->RenderStream(&PIN_CATEGORY_CAPTURE,
                                         &MEDIATYPE_Interleaved,
                                         cCap->pVCap, NULL, cCap->pRender);
        if(hr != NOERROR)
        {
            hr = cCap->pBuilder->RenderStream(&PIN_CATEGORY_CAPTURE,
                                             &MEDIATYPE_Video,
                                             cCap->pVCap, NULL, cCap->pRender);
            if(hr != NOERROR)
            {
                ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Cannot render video capture stream"));
                goto SetupCaptureFail;
            }
        }

        if(cCap->fWantPreview)
        {
            hr = cCap->pBuilder->RenderStream(&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Interleaved,
                                            cCap->pVCap, NULL, NULL);
            if(hr == VFW_S_NOPREVIEWPIN)
            {
                // preview was faked up for us using the (only) capture pin
                cCap->fPreviewFaked = TRUE;
            }
            else if(hr != S_OK)
            {
                hr = cCap->pBuilder->RenderStream(&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video,
                                                 cCap->pVCap, NULL, NULL);
                if(hr == VFW_S_NOPREVIEWPIN)
                {
                    // preview was faked up for us using the (only) capture pin
                    cCap->fPreviewFaked = TRUE;
                }
                else if(hr != S_OK)
                {
                    ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Cannot render video preview stream"));
                    goto SetupCaptureFail;
                }
            }
        }
    }
    else
    {
        CComPtr< IBaseFilter > sink;
        if( &cCap->pSink )
        {
            cCap->pSink->QueryInterface( IID_IBaseFilter, reinterpret_cast<void **>( &sink ) );
        }

        hr = cCap->pBuilder->RenderStream(NULL,
                                         &MEDIATYPE_Stream,
                                         cCap->pVCap, NULL, sink);
    }

    //
    // Render the audio capture pin?
    //

    if(!cCap->fMPEG2 && cCap->fCapAudio)
    {
        hr = cCap->pBuilder->RenderStream(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Audio,
                                         cCap->pACap, NULL, cCap->pRender);
        if(hr != NOERROR)
        {
            ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Cannot render audio capture stream"));
            goto SetupCaptureFail;
        }
    }

    //
    // Render the closed captioning pin? It could be a CC or a VBI category pin,
    // depending on the capture driver
    //

    if(!cCap->fMPEG2  && cCap->fCapCC)
    {
        hr = cCap->pBuilder->RenderStream(&PIN_CATEGORY_CC, NULL,
                                         cCap->pVCap, NULL, cCap->pRender);
        if(hr != NOERROR)
        {
            hr = cCap->pBuilder->RenderStream(&PIN_CATEGORY_VBI, NULL,
                                             cCap->pVCap, NULL, cCap->pRender);
            if(hr != NOERROR)
            {
                ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Cannot render closed captioning"));
                // so what? goto SetupCaptureFail;
            }
        }
        // To preview and capture VBI at the same time, we can call this twice
        if(cCap->fWantPreview)
        {
            hr = cCap->pBuilder->RenderStream(&PIN_CATEGORY_VBI, NULL,
                                             cCap->pVCap, NULL, NULL);
        }
    }

    //
    // Get the preview window to be a child of our app's window
    //

    // This will find the IVideoWindow interface on the renderer.  It is
    // important to ask the filtergraph for this interface... do NOT use
    // ICaptureGraphBuilder2::FindInterface, because the filtergraph needs to
    // know we own the window so it can give us display changed messages, etc.

    if(!cCap->fMPEG2 && cCap->fWantPreview)
    {
        hr = cCap->pFg->QueryInterface(IID_IVideoWindow, (void **)&cCap->pVW);
        if(hr != NOERROR && cCap->fWantPreview)
        {
            ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("This graph cannot preview"));
        }
        else if(hr == NOERROR)
        {
//autoUpdateWindow

            RECT rc;
            cCap->pVW->put_Owner((OAHWND)cCap->ghwndApp);    // We own the window now
            cCap->pVW->put_WindowStyle(WS_CHILD);    // you are now a child

        GetClientRect(cCap->ghwndApp, &rc);
//        cyBorder = GetSystemMetrics(SM_CYBORDER);
//        cy = statusGetHeight() + cyBorder;
//        rc.bottom -= cy;

        cCap->pVW->SetWindowPosition(0, 0, rc.right, rc.bottom); // be this big

            // give the preview window all our space but where the status bar is
//            GetClientRect(cCap->ghwndApp, &rc);
//            cyBorder = GetSystemMetrics(SM_CYBORDER);
//            cy = statusGetHeight() + cyBorder;
//            rc.bottom -= cy;

//            cCap->pVW->SetWindowPosition(40, 50, rc.right, rc.bottom); // be this big
            cCap->pVW->put_Visible(OATRUE);

        }
    }

    // now tell it what frame rate to capture at.  Just find the format it
    // is capturing with, and leave everything alone but change the frame rate
    if( !cCap->fMPEG2 )
    {
        hr = cCap->fUseFrameRate ? E_FAIL : NOERROR;
        if(cCap->pVSC && cCap->fUseFrameRate)
        {
            hr = cCap->pVSC->GetFormat(&pmt);

            // DV capture does not use a VIDEOINFOHEADER
            if(hr == NOERROR)
            {
                if(pmt->formattype == FORMAT_VideoInfo)
                {
                    VIDEOINFOHEADER *pvi = (VIDEOINFOHEADER *)pmt->pbFormat;
                    pvi->AvgTimePerFrame = (LONGLONG)(10000000 / cCap->FrameRate);
                    hr = cCap->pVSC->SetFormat(pmt);
                }
                DeleteMediaType(pmt);
            }
        }
        if(hr != NOERROR)
            ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Cannot set frame rate for capture"));
    }

    // now ask the filtergraph to tell us when something is completed or aborted
    // (EC_COMPLETE, EC_USERABORT, EC_ERRORABORT).  This is how we will find out
    // if the disk gets full while capturing
    hr = cCap->pFg->QueryInterface(IID_IMediaEventEx, (void **)&cCap->pME);
    if(hr == NOERROR)
    {
//!        cCap->pME->SetNotifyWindow((OAHWND)cCap->ghwndApp, WM_FGNOTIFY, 0);
    }

    // potential debug output - what the graph looks like
    // DumpGraph(cCap->pFg, 1);

    // Add our graph to the running object table, which will allow
    // the GraphEdit application to "spy" on our graph
#ifdef REGISTER_FILTERGRAPH
    hr = AddGraphToRot(cCap->pFg, &g_dwGraphRegister);
    if(FAILED(hr))
    {
        ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Failed to register filter graph with ROT!  hr=0x%x"), hr);
        g_dwGraphRegister = 0;
    }
#endif

    // All done.
    cCap->fCaptureGraphBuilt = TRUE;
    return VIPRET_OK;

SetupCaptureFail:
    TearDownGraph();
	return VIPRET_INTERNAL_ERR;
}


////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////


int vipDirectXInput2::BuildGrabberGraph(bool mpeg2)
 {
	if ( !cCap->GrabbingEnabled )
		return VIPRET_ILLEGAL_USE;

	HRESULT hr;

	if ( !cCap->pCallbackGrabber )
	 {
		cCap->pCallbackGrabber = new SampleGrabberCB();
	 }


	hr = CoCreateInstance(CLSID_SampleGrabber, NULL, CLSCTX_INPROC_SERVER,
							IID_IBaseFilter, (LPVOID *)&cCap->pGrabberBaseFilter);

	if (FAILED(hr))
	 {
		ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Error %x: Cannot find CLSID_SampleGrabber"), hr);
		cCap->GrabbingEnabled = false;
		return VIPRET_INTERNAL_ERR;
	 }

	cCap->pGrabberBaseFilter->QueryInterface(IID_ISampleGrabber, (void**)&cCap->pSampleGrabber);

	hr = CoCreateInstance(CLSID_NullRenderer, NULL, CLSCTX_INPROC_SERVER,
						IID_IBaseFilter, reinterpret_cast<void**>(&cCap->null_filter));
	hr = cCap->pFg->AddFilter(cCap->null_filter,L"Null Renderer");

	if (cCap->pSampleGrabber == NULL)
	 {
	//E_NOINTERFACE;
		cCap->GrabbingEnabled = false;
		ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Error %x: Cannot create grabber"), hr);
		return VIPRET_INTERNAL_ERR;
	 }


	hr = cCap->pFg->AddFilter(cCap->pGrabberBaseFilter,L"Grabber");
	if (FAILED(hr))
	 {
	//E_NOINTERFACE;
		cCap->GrabbingEnabled = false;
		ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Error %x: Cannot Add Grabber to graph."), hr);
		return VIPRET_INTERNAL_ERR;
	 }


	hr = cCap->pSampleGrabber->SetBufferSamples(FALSE);

	hr = cCap->pSampleGrabber->SetOneShot(FALSE);

	hr = cCap->pSampleGrabber->SetCallback( cCap->pCallbackGrabber, 1);

	AM_MEDIA_TYPE mt;
	ZeroMemory(&mt,sizeof(AM_MEDIA_TYPE));

	mt.majortype = MEDIATYPE_Video;
	mt.subtype = MEDIASUBTYPE_RGB24;
	mt.formattype = FORMAT_VideoInfo;

	hr = cCap->pSampleGrabber->SetMediaType(&mt);
	if (FAILED(hr))
	 {
		cCap->GrabbingEnabled = false;
		ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Error %x: set requested format"), hr);
		return VIPRET_INTERNAL_ERR;
	 }


	IBaseFilter* pAviDecFilter = NULL;
	hr = CoCreateInstance(CLSID_AVIDec, NULL, CLSCTX_INPROC_SERVER,
								IID_IBaseFilter, (LPVOID *)&pAviDecFilter);

	hr = cCap->pFg->AddFilter(pAviDecFilter,L"Avi Decompressor (2)");

	if ( !mpeg2 )	// it's NOT an MPEG2 device
	 {
		// dshow uses smart tee by itself...

		hr = cCap->pBuilder->RenderStream(&PIN_CATEGORY_CAPTURE,
											 &MEDIATYPE_Video, cCap->pVCap, pAviDecFilter, cCap->pGrabberBaseFilter);

	 }
	else // MPEG2 device
	 {
		hr = cCap->pBuilder->RenderStream(&PIN_CATEGORY_CAPTURE,
											 NULL, cCap->pSmartTeeFilter, pAviDecFilter, cCap->pGrabberBaseFilter);


//		hr = CoCreateInstance(CLSID_SmartTee, NULL, CLSCTX_INPROC_SERVER,
//									IID_IBaseFilter, (LPVOID *)&cCap->pSmartTeeFilter);

//		hr = cCap->pFg->AddFilter(cCap->pSmartTeeFilter ,L"Smart Tee (2)");

//		hr = cCap->pBuilder->RenderStream(&PIN_CATEGORY_CAPTURE,
//										NULL, cCap->pSmartTeeFilter, pAviDecFilter, cCap->pGrabberBaseFilter);

	 }

	hr = cCap->pBuilder->RenderStream(NULL,
									  NULL, cCap->pGrabberBaseFilter, NULL, cCap->null_filter);

	return VIPRET_OK;
 }


// build the preview graph!
//
// !!! PLEASE NOTE !!!  Some new WDM devices have totally separate capture
// and preview settings.  An application that wishes to preview and then
// capture may have to set the preview pin format using IAMStreamConfig on the
// preview pin, and then again on the capture pin to capture with that format.
// In this sample app, there is a separate page to set the settings on the
// capture pin and one for the preview pin.  To avoid the user
// having to enter the same settings in 2 dialog boxes, an app can have its own
// UI for choosing a format (the possible formats can be enumerated using
// IAMStreamConfig) and then the app can programmatically call IAMStreamConfig
// to set the format on both pins.
//
int vipDirectXInput2::BuildPreviewGraph()
{
    HRESULT hr;
    AM_MEDIA_TYPE *pmt;

    // we have one already
    if(cCap->fPreviewGraphBuilt)
        return VIPRET_OK;	//mmh bad

    // No rebuilding while we're running
    if(cCap->fCapturing || cCap->fPreviewing)
        return VIPRET_ILLEGAL_USE;

    // We don't have the necessary capture filters
    if(cCap->pVCap == NULL)
        return VIPRET_ILLEGAL_USE;
    if(cCap->pACap == NULL && cCap->fCapAudio)
        return VIPRET_ILLEGAL_USE;


    // we already have another graph built... tear down the old one
    if( cCap->fCaptureGraphBuilt )
        TearDownGraph();

    //
    // Render the preview pin - even if there is not preview pin, the capture
    // graph builder will use a smart tee filter and provide a preview.
    //
    // !!! what about latency/buffer issues?

    // NOTE that we try to render the interleaved pin before the video pin, because
    // if BOTH exist, it's a DV filter and the only way to get the audio is to use
    // the interleaved pin.  Using the Video pin on a DV filter is only useful if
    // you don't want the audio.

    if( cCap->fMPEG2 )
     {
		if ( !cCap->GrabbingEnabled )
		 {

	        hr = cCap->pBuilder->RenderStream(&PIN_CATEGORY_PREVIEW,
	                                         &MEDIATYPE_Stream, cCap->pVCap, NULL, NULL);

		 }
		else
		 {

		hr = CoCreateInstance(CLSID_SmartTee, NULL, CLSCTX_INPROC_SERVER,
									IID_IBaseFilter, (LPVOID *)&cCap->pSmartTeeFilter);

			hr = cCap->pFg->AddFilter(cCap->pSmartTeeFilter ,L"Smart Tee (GRAB)");

	        hr = cCap->pBuilder->RenderStream(&PIN_CATEGORY_PREVIEW,
	                                         &MEDIATYPE_Stream, cCap->pVCap, NULL, cCap->pSmartTeeFilter);

	        // video renderer


//	        hr = cCap->pBuilder->RenderStream(&PIN_CATEGORY_PREVIEW,
//	                                         NULL, cCap->pSmartTeeFilter, NULL, NULL);

//			BuildGrabberGraph(true);
		 }


        if( FAILED( hr ) )
        {
            ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Cannot build MPEG2 preview graph!"));
        }


     }
    else
     {
		hr = cCap->pBuilder->RenderStream(&PIN_CATEGORY_PREVIEW,
										 &MEDIATYPE_Interleaved, cCap->pVCap, NULL, NULL);
		if(hr == VFW_S_NOPREVIEWPIN)
		 {
			// preview was faked up for us using the (only) capture pin
			cCap->fPreviewFaked = TRUE;
		 }
		else if(hr != S_OK)
		 {
			// maybe it's DV?
			hr = cCap->pBuilder->RenderStream(&PIN_CATEGORY_PREVIEW,
											 &MEDIATYPE_Video, cCap->pVCap, NULL, NULL);
			if(hr == VFW_S_NOPREVIEWPIN)
			 {
				// preview was faked up for us using the (only) capture pin
				cCap->fPreviewFaked = TRUE;
			 }
			else if(hr != S_OK)
			 {
				ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("This graph cannot preview!"));
				cCap->fPreviewGraphBuilt = FALSE;
				return false;
			 }
		 }

		//
		// Render the closed captioning pin? It could be a CC or a VBI category pin,
		// depending on the capture driver
		//

		if(cCap->fCapCC)
		 {
			hr = cCap->pBuilder->RenderStream(&PIN_CATEGORY_CC, NULL,
											 cCap->pVCap, NULL, NULL);
			if(hr != NOERROR)
			 {
				hr = cCap->pBuilder->RenderStream(&PIN_CATEGORY_VBI, NULL,
												 cCap->pVCap, NULL, NULL);
				if(hr != NOERROR)
				 {
					ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Cannot render closed captioning"));
				 }
			 }
		 }

		//
		// add sample grabber if requested
		//
		if ( cCap->GrabbingEnabled )
			BuildGrabberGraph(false);

	  }



    //
    // Get the preview window to be a child of our app's window
    //

    // This will find the IVideoWindow interface on the renderer.  It is
    // important to ask the filtergraph for this interface... do NOT use
    // ICaptureGraphBuilder2::FindInterface, because the filtergraph needs to
    // know we own the window so it can give us display changed messages, etc.

    hr = cCap->pFg->QueryInterface(IID_IVideoWindow, (void **)&cCap->pVW);
    if(hr != NOERROR)
    {
        ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("This graph cannot preview properly"));
    }
    else
    {
        //Find out if this is a DV stream
        AM_MEDIA_TYPE * pmtDV;

        if(cCap->pVSC && SUCCEEDED(cCap->pVSC->GetFormat(&pmtDV)))
        {
            if(pmtDV->formattype == FORMAT_DvInfo)
            {
                // in this case we want to set the size of the parent window to that of
                // current DV resolution.
                // We get that resolution from the IVideoWindow.
                CComQIPtr <IBasicVideo, &IID_IBasicVideo> pBV(cCap->pVW);

                if(pBV != NULL)
                {
                    HRESULT hr1, hr2;
                    long lWidth, lHeight;

                    hr1 = pBV->get_VideoHeight(&lHeight);
                    hr2 = pBV->get_VideoWidth(&lWidth);
                    if(SUCCEEDED(hr1) && SUCCEEDED(hr2))
                    {
						width = (unsigned int)lWidth;
						height = (unsigned int)lHeight;

						// resize our window to the default capture size
						if ( cCap->autoUpdateWindow )
							ResizeWindow(cCap->ghwndApp, width, height);

                    }
                }
            }
        }

        RECT rc;
        cCap->pVW->put_Owner((OAHWND)cCap->ghwndApp);    // We own the window now
        cCap->pVW->put_WindowStyle(WS_CHILD);    // you are now a child

        // give the preview window all our space but where the status bar is
        GetClientRect(cCap->ghwndApp, &rc);
//        cyBorder = GetSystemMetrics(SM_CYBORDER);
//        cy = statusGetHeight() + cyBorder;
//        rc.bottom -= cy;

        cCap->pVW->SetWindowPosition(0, 0, rc.right, rc.bottom); // be this big
        cCap->pVW->put_Visible(OATRUE);
    }

    // now tell it what frame rate to capture at.  Just find the format it
    // is capturing with, and leave everything alone but change the frame rate
    // No big deal if it fails.  It's just for preview
    // !!! Should we then talk to the preview pin?
    if(cCap->pVSC && cCap->fUseFrameRate)
    {
        hr = cCap->pVSC->GetFormat(&pmt);

        // DV capture does not use a VIDEOINFOHEADER
        if(hr == NOERROR)
        {
            if(pmt->formattype == FORMAT_VideoInfo)
            {
                VIDEOINFOHEADER *pvi = (VIDEOINFOHEADER *)pmt->pbFormat;
                pvi->AvgTimePerFrame = (LONGLONG)(10000000 / cCap->FrameRate);

                hr = cCap->pVSC->SetFormat(pmt);
                if(hr != NOERROR)
                    ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("%x: Cannot set frame rate for preview"), hr);
            }
            DeleteMediaType(pmt);
        }
    }

    // make sure we process events while we're previewing!
    hr = cCap->pFg->QueryInterface(IID_IMediaEventEx, (void **)&cCap->pME);
    if(hr == NOERROR)
    {
        cCap->pME->SetNotifyWindow((OAHWND)cCap->ghwndApp, WM_FGNOTIFY, 0);
    }

    // potential debug output - what the graph looks like
    // DumpGraph(cCap->pFg, 1);

    // Add our graph to the running object table, which will allow
    // the GraphEdit application to "spy" on our graph
#ifdef REGISTER_FILTERGRAPH
    hr = AddGraphToRot(cCap->pFg, &g_dwGraphRegister);
    if(FAILED(hr))
    {
        ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Failed to register filter graph with ROT!  hr=0x%x"), hr);
        g_dwGraphRegister = 0;
    }
#endif

    // All done.
    cCap->fPreviewGraphBuilt = TRUE;
    return VIPRET_OK;
}

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

// Start previewing
//
int vipDirectXInput2::StartPreview()
 {
    // way ahead of you
    if(cCap->fPreviewing)
        return VIPRET_ILLEGAL_USE;

    if(!cCap->fPreviewGraphBuilt)
	{
		BuildPreviewGraph();

		if(!cCap->fPreviewGraphBuilt)
	        return VIPRET_INTERNAL_ERR;
	}

    // run the graph
    IMediaControl *pMC = NULL;
    HRESULT hr = cCap->pFg->QueryInterface(IID_IMediaControl, (void **)&pMC);
    if(SUCCEEDED(hr))
    {
        hr = pMC->Run();
        if(FAILED(hr))
        {
            // stop parts that ran
            pMC->Stop();
        }
        pMC->Release();
    }
    if(FAILED(hr))
    {
        ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Error %x: Cannot run preview graph"), hr);
        return VIPRET_INTERNAL_ERR;
    }

    cCap->fPreviewing = TRUE;
    return VIPRET_OK;
 }

////////////////////////////////////////////////////////////////////////////////////////////

// stop the preview graph
//
int vipDirectXInput2::StopPreview()
{
    // way ahead of you
    if(!cCap->fPreviewing)
        return VIPRET_ILLEGAL_USE;

    // stop the graph
    IMediaControl *pMC = NULL;
    HRESULT hr = cCap->pFg->QueryInterface(IID_IMediaControl, (void **)&pMC);
    if(SUCCEEDED(hr))
    {
        hr = pMC->Stop();
        pMC->Release();
    }
    if(FAILED(hr))
    {
        ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Error %x: Cannot stop preview graph"), hr);
        return VIPRET_INTERNAL_ERR;
    }

    cCap->fPreviewing = FALSE;

    // get rid of menu garbage
    InvalidateRect(cCap->ghwndApp, NULL, TRUE);

    return VIPRET_OK;
}

void vipDirectXInput2::setPreviewEnabled(bool value)
 {
	cCap->fWantPreview = value;
 }


////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

// start the capture graph
//
int vipDirectXInput2::StartCapture()
{
    bool fHasStreamControl;
    HRESULT hr;

    // way ahead of you
    if(cCap->fCapturing)
    {
        ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Error: Already Capturing!"));
        return VIPRET_ILLEGAL_USE;
    }

    // or we'll get confused
	bool didPreview = cCap->fPreviewing;
    if(cCap->fPreviewing)
        StopPreview();


	if(cCap->fPreviewGraphBuilt)
		TearDownGraph();

	BuildCaptureGraph();

    // or we'll crash
    if(!cCap->fCaptureGraphBuilt)
    {
        ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Error: Cannot create graph, capture falied!"));
        return VIPRET_INTERNAL_ERR;
    }

    // This amount will be subtracted from the number of dropped and not
    // dropped frames reported by the filter.  Since we might be having the
    // filter running while the pin is turned off, we don't want any of the
    // frame statistics from the time the pin is off interfering with the
    // statistics we gather while the pin is on
    cCap->lDroppedBase = 0;
    cCap->lNotBase = 0;

    REFERENCE_TIME start = MAX_TIME, stop = MAX_TIME;

    // don't capture quite yet...
    hr = cCap->pBuilder->ControlStream(&PIN_CATEGORY_CAPTURE, NULL,
                                      NULL, &start, NULL, 0, 0);

    // Do we have the ability to control capture and preview separately?
    fHasStreamControl = SUCCEEDED(hr);

    // prepare to run the graph
    IMediaControl *pMC = NULL;
    hr = cCap->pFg->QueryInterface(IID_IMediaControl, (void **)&pMC);
    if(FAILED(hr))
    {
        ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Error %x: Cannot get IMediaControl"), hr);
        return VIPRET_INTERNAL_ERR;
    }

    // If we were able to keep capture off, then we can
    // run the graph now for frame accurate start later yet still showing a
    // preview.   Otherwise, we can't run the graph yet without capture
    // starting too, so we'll pause it so the latency between when they
    // press a key and when capture begins is still small (but they won't have
    // a preview while they wait to press a key)

    if(fHasStreamControl)
        hr = pMC->Run();
    else
        hr = pMC->Pause();
    if(FAILED(hr))
    {
        // stop parts that started
        pMC->Stop();
        pMC->Release();
        ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Error %x: Cannot start graph"), hr);
        return VIPRET_INTERNAL_ERR;
    }


    if(fHasStreamControl)
    {
        // we may not have this yet
        if(!cCap->pDF)
        {
            hr = cCap->pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,
                                              &MEDIATYPE_Interleaved, cCap->pVCap,
                                              IID_IAMDroppedFrames, (void **)&cCap->pDF);
            if(hr != NOERROR)
                hr = cCap->pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,
                                                  &MEDIATYPE_Video, cCap->pVCap,
                                                  IID_IAMDroppedFrames, (void **)&cCap->pDF);
        }

        // turn the capture pin on now!
        hr = cCap->pBuilder->ControlStream(&PIN_CATEGORY_CAPTURE, NULL,
            NULL, NULL, &stop, 0, 0);
        // make note of the current dropped frame counts

        if(cCap->pDF)
        {
            cCap->pDF->GetNumDropped(&cCap->lDroppedBase);
            cCap->pDF->GetNumNotDropped(&cCap->lNotBase);
        }
    }
    else
    {
        hr = pMC->Run();
        if(FAILED(hr))
        {
            // stop parts that started
            pMC->Stop();
            pMC->Release();
            ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Error %x: Cannot run graph"), hr);
            return VIPRET_INTERNAL_ERR;
        }
    }

    pMC->Release();

    // when did we start capture?
    cCap->lCapStartTime = timeGetTime();
	cCap->lCapStopTime = 0;

    // update status bar 30 times per second - #captured, #dropped
//    SetTimer(cCap->ghwndApp, 1, 33, NULL);
    UpdateStatus(true);

    cCap->fCapturing = TRUE;

    return VIPRET_OK;
}

////////////////////////////////////////////////////////////////////////////////////////////

// stop the capture graph
//
int vipDirectXInput2::StopCapture()
{
    // way ahead of you
    if(!cCap->fCapturing)
    {
        ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Error: Start Capturing first!"));
        return VIPRET_INTERNAL_ERR;
    }

    // stop the graph
    IMediaControl *pMC = NULL;
    HRESULT hr = cCap->pFg->QueryInterface(IID_IMediaControl, (void **)&pMC);
    if(SUCCEEDED(hr))
    {
        hr = pMC->Stop();
        pMC->Release();
    }
    if(FAILED(hr))
    {
        ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Error %x: Cannot stop graph"), hr);
        return VIPRET_INTERNAL_ERR;
    }

    // when the graph was stopped
    cCap->lCapStopTime = timeGetTime();

    // no more status bar updates
//    KillTimer(cCap->ghwndApp, 1);

    // one last time for the final count and all the stats
    UpdateStatus(true);

    cCap->fCapturing = FALSE;

    // get rid of menu garbage
//    InvalidateRect(cCap->ghwndApp, NULL, TRUE);

	if (cCap->fPreviewing && cCap->fWantPreview)
	{
		BuildPreviewGraph();
		StartPreview();
	}


    return VIPRET_OK;
}

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////




void vipDirectXInput2::enumerateDevices()
{
	cCap->iNumVCapDevices = 0;

    UINT    uIndex = 0;
    HRESULT hr;

    // enumerate all video capture devices
    ICreateDevEnum *pCreateDevEnum=0;
    hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
                          IID_ICreateDevEnum, (void**)&pCreateDevEnum);
    if(hr != NOERROR)
    {
        ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Error Creating Device Enumerator"));
        return;
    }

    IEnumMoniker *pEm=0;
    hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEm, 0);
    if(hr != NOERROR)
    {
        ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Sorry, you have no video capture hardware.\r\n\r\n")
               TEXT("Video capture will not function properly."));
        goto EnumAudio;
    }

    pEm->Reset();
    ULONG cFetched;
    IMoniker *pM;

    while(hr = pEm->Next(1, &pM, &cFetched), hr==S_OK)
    {

        IPropertyBag *pBag=0;

        hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
        if(SUCCEEDED(hr))
        {
            VARIANT var;
            var.vt = VT_BSTR;
            hr = pBag->Read(L"FriendlyName", &var, NULL);
            if(hr == NOERROR)
            {


      char* str = Wide2Char(var.bstrVal);
      sprintf(deviceVideoDesc[uIndex], "%d - %s", uIndex, str);
      free(str);


                SysFreeString(var.bstrVal);

                ASSERT(cCap->rgpmVideoMenu[uIndex] == 0);
                cCap->rgpmVideoMenu[uIndex] = pM;
                pM->AddRef();
            }
            pBag->Release();
        }

        pM->Release();
        uIndex++;
    }
    pEm->Release();

    cCap->iNumVCapDevices = uIndex;



EnumAudio:

    // enumerate all audio capture devices
    uIndex = 0;

    ASSERT(pCreateDevEnum != NULL);

    hr = pCreateDevEnum->CreateClassEnumerator(CLSID_AudioInputDeviceCategory, &pEm, 0);
    pCreateDevEnum->Release();
    if(hr != NOERROR)
        return;
    pEm->Reset();

    while(hr = pEm->Next(1, &pM, &cFetched), hr==S_OK)
    {

        IPropertyBag *pBag;
        hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
        if(SUCCEEDED(hr))
        {
            VARIANT var;
            var.vt = VT_BSTR;
            hr = pBag->Read(L"FriendlyName", &var, NULL);
            if(hr == NOERROR)
            {

      char* str = Wide2Char(var.bstrVal);
      sprintf(deviceAudioDesc[uIndex], "%d - %s", uIndex, str);
      free(str);

                SysFreeString(var.bstrVal);

                ASSERT(cCap->rgpmAudioMenu[uIndex] == 0);
                cCap->rgpmAudioMenu[uIndex] = pM;
                pM->AddRef();
            }
            pBag->Release();
        }
        pM->Release();
        uIndex++;
    }

    pEm->Release();

    cCap->iNumACapDevices = uIndex;

}

////////////////////////////////////////////////////////////////////////////////////////////


void vipDirectXInput2::RegisterDevicesNotification()
{
    // Register for device add/remove notifications
    DEV_BROADCAST_DEVICEINTERFACE filterData;
    ZeroMemory(&filterData, sizeof(DEV_BROADCAST_DEVICEINTERFACE));

    filterData.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
    filterData.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
    filterData.dbcc_classguid = AM_KSCATEGORY_CAPTURE;

    gpUnregisterDeviceNotification = NULL;
    gpRegisterDeviceNotification = NULL;
    // dynload device removal APIs
    {
        HMODULE hmodUser = GetModuleHandle(TEXT("user32.dll"));
        ASSERT(hmodUser);       // we link to user32
        gpUnregisterDeviceNotification = (PUnregisterDeviceNotification)
        GetProcAddress(hmodUser, "UnregisterDeviceNotification");

        // m_pRegisterDeviceNotification is prototyped differently in unicode
        gpRegisterDeviceNotification = (PRegisterDeviceNotification)
            GetProcAddress(hmodUser,
#ifdef UNICODE
            "RegisterDeviceNotificationW"
#else
            "RegisterDeviceNotificationA"
#endif
        );

        // failures expected on older platforms.
        ASSERT(gpRegisterDeviceNotification && gpUnregisterDeviceNotification ||
              !gpRegisterDeviceNotification && !gpUnregisterDeviceNotification);
    }

    ghDevNotify = NULL;

    if(gpRegisterDeviceNotification)
    {
        ghDevNotify = gpRegisterDeviceNotification(cCap->ghwndApp, &filterData, DEVICE_NOTIFY_WINDOW_HANDLE);
        ASSERT(ghDevNotify != NULL);
    }


}



////////////////////////////////////////////////////////////////////////////////////////////

int vipDirectXInput2::showCaptureVideoForWindowPropertyPage()
 {
	// they want the VfW format dialog
	if (!cCap->pDlg)
	 {
		 return VIPRET_ILLEGAL_USE;
	 }

	// this dialog will not work while previewing
	bool didPreview = false;

	if(cCap->fPreviewing)
	 {
		StopPreview();
		didPreview = true;
	 }

	HRESULT hrD;
	hrD = cCap->pDlg->ShowDialog(VfwCaptureDialog_Format, cCap->ghwndApp);

	// Sometimes bringing up the FORMAT dialog can result
	// in changing to a capture format that the current graph
	// can't handle.  It looks like that has happened and we'll
	// have to rebuild the graph.
	if(hrD == VFW_E_CANNOT_CONNECT)
	{
		DbgLog((LOG_TRACE,1,TEXT("DIALOG CORRUPTED GRAPH!")));
		TearDownGraph();    // now we need to rebuild
		// !!! This won't work if we've left a stranded h/w codec
		return VIPRET_INTERNAL_ERR;
	}

	// Resize our window to be the same size that we're capturing
	if(cCap->pVSC)
	{
		AM_MEDIA_TYPE *pmt;
		// get format being used NOW
		hrD = cCap->pVSC->GetFormat(&pmt);

		// DV capture does not use a VIDEOINFOHEADER
		if(hrD == NOERROR)
		{
			if(pmt->formattype == FORMAT_VideoInfo)
			{
				width = HEADER(pmt->pbFormat)->biWidth;
				height = abs(HEADER(pmt->pbFormat)->biHeight);

				// resize our window to the default capture size
				if ( cCap->autoUpdateWindow )
					ResizeWindow(cCap->ghwndApp, width, height);
			}
			DeleteMediaType(pmt);
		}
		else
		{
			return VIPRET_INTERNAL_ERR;
		}
	}

	if(didPreview)
	{
		BuildPreviewGraph();
		StartPreview();
	}
	return VIPRET_OK;
 }


HRESULT showFilterPropertyPage(IBaseFilter* target, HWND ghwndApp)
 {
	HRESULT hr;

	ISpecifyPropertyPages *pSpec;
	CAUUID cauuid;

	hr = target->QueryInterface(IID_ISpecifyPropertyPages, (void **)&pSpec);

	if(hr == S_OK)
	 {
		hr = pSpec->GetPages(&cauuid);

		hr = OleCreatePropertyFrame(	ghwndApp, 30, 30, NULL, 1,
										(IUnknown **)&target, cauuid.cElems,
										(GUID *)cauuid.pElems, 0, 0, NULL		);

		CoTaskMemFree(cauuid.pElems);
		pSpec->Release();

	 }
	return hr;
 }

////////////////////////////////////////////////////////////////////////////////////////////
int vipDirectXInput2::showCaptureVideoFilterPropertyPage()
 {
	if ( !cCap->pVCap )
		return VIPRET_ILLEGAL_USE;

	HRESULT hr;

	hr = showFilterPropertyPage(cCap->pVCap, cCap->ghwndApp);

 	if(hr == S_OK)
 		return VIPRET_OK;

 	else
		return VIPRET_INTERNAL_ERR;
 }
////////////////////////////////////////////////////////////////////////////////////////////
int vipDirectXInput2::showCaptureAudioFilterPropertyPage()
 {
	if ( !cCap->pACap )
		return VIPRET_ILLEGAL_USE;

	HRESULT hr;

	hr = showFilterPropertyPage(cCap->pACap, cCap->ghwndApp);

 	if(hr == S_OK)
 		return VIPRET_OK;

 	else
		return VIPRET_INTERNAL_ERR;
 }
////////////////////////////////////////////////////////////////////////////////////////////
int vipDirectXInput2::showVideoRendererPropertyPage()
{
	if ( !cCap->pRender )
		return VIPRET_ILLEGAL_USE;

	HRESULT hr;

	hr = showFilterPropertyPage(cCap->pRender, cCap->ghwndApp);

 	if(hr == S_OK)
 		return VIPRET_OK;

 	else
		return VIPRET_INTERNAL_ERR;
 }
////////////////////////////////////////////////////////////////////////////////////////////
int vipDirectXInput2::showSampleGrabberPropertyPage()
{
	if ( !cCap->pGrabberBaseFilter )
		return VIPRET_ILLEGAL_USE;

	HRESULT hr;

	hr = showFilterPropertyPage(cCap->pGrabberBaseFilter, cCap->ghwndApp);

 	if(hr == S_OK)
 		return VIPRET_OK;

 	else
		return VIPRET_INTERNAL_ERR;
 }
////////////////////////////////////////////////////////////////////////////////////////////


int vipDirectXInput2::showGraphFilterPropertyPage()
{
                // You can change this pin's output format in these dialogs.
                // If the capture pin is already connected to somebody who's
                // fussy about the connection type, that may prevent using
                // this dialog(!) because the filter it's connected to might not
                // allow reconnecting to a new format. (EG: you switch from RGB
                // to some compressed type, and need to pull in a decoder)
                // I need to tear down the graph downstream of the
                // capture filter before bringing up these dialogs.
                // In any case, the graph must be STOPPED when calling them.
	HRESULT hr;
//	bool didPreview = cCap->fPreviewing;

//	if(cCap->fPreviewing)
//		StopPreview();  // make sure graph is stopped

//	if(cCap->fCapturing)
//		StopCapture();  // make sure graph is stopped

                // The capture pin that we are trying to set the format on is connected if
                // one of these variable is set to TRUE. The pin should be disconnected for
                // the dialog to work properly.
                if(cCap->fCaptureGraphBuilt || cCap->fPreviewGraphBuilt)
                {
                    DbgLog((LOG_TRACE,1,TEXT("Tear down graph for dialog")));
                    TearDownGraph();    // graph could prevent dialog working
                }

                IAMStreamConfig *pSC;
                hr = cCap->pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,
                    &MEDIATYPE_Interleaved, cCap->pVCap,
                    IID_IAMStreamConfig, (void **)&pSC);

                if(hr != NOERROR)
                    hr = cCap->pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,
                        &MEDIATYPE_Video, cCap->pVCap,
                        IID_IAMStreamConfig, (void **)&pSC);

                ISpecifyPropertyPages *pSpec;
                CAUUID cauuid;

                hr = pSC->QueryInterface(IID_ISpecifyPropertyPages,
                    (void **)&pSpec);

                if(hr == S_OK)
                {
                    hr = pSpec->GetPages(&cauuid);
                    hr = OleCreatePropertyFrame(cCap->ghwndApp, 30, 30, NULL, 1,
                        (IUnknown **)&pSC, cauuid.cElems,
                        (GUID *)cauuid.pElems, 0, 0, NULL);

                    // !!! What if changing output formats couldn't reconnect
                    // and the graph is broken?  Shouldn't be possible...

                    if(cCap->pVSC)
                    {
                        AM_MEDIA_TYPE *pmt;
                        // get format being used NOW
                        hr = cCap->pVSC->GetFormat(&pmt);

                        // DV capture does not use a VIDEOINFOHEADER
                        if(hr == NOERROR)
                        {
                            if(pmt->formattype == FORMAT_VideoInfo)
                            {
								width = HEADER(pmt->pbFormat)->biWidth;
								height = abs(HEADER(pmt->pbFormat)->biHeight);

								// resize our window to the default capture size
								if ( cCap->autoUpdateWindow )
									ResizeWindow(cCap->ghwndApp, width, height);

                            }
                            DeleteMediaType(pmt);
                        }
                    }

                    CoTaskMemFree(cauuid.pElems);
                    pSpec->Release();
                }

                pSC->Release();

//              if(didPreview)
//                    StartPreview();

	return 0;
}



////////////////////////////////////////////////////////////////////////////////////////////


// pre-allocate the capture file
//
int vipDirectXInput2::AllocCaptureFile(unsigned short fileSize_mb)
 {
	USES_CONVERSION;

	// we'll get into an infinite loop in the dlg proc setting a value
	if( cCap->szCaptureFile[0] == 0 )
	 {
		ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Allocation falied:\r\nCapture file is not valid!\r\n\r\nDid you setup it?"));
		return VIPRET_ILLEGAL_USE;
	 }

	cCap->wCapFileSize = (WORD)fileSize_mb;

	// ensure repaint after dismissing dialog before
	// possibly lengthy operation
	//UpdateWindow(cCap->ghwndApp);

	if( MakeBuilder() )
	 {
		ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Allocation falied:\r\nCannot create graph Builder!"));
		return VIPRET_INTERNAL_ERR;
	 }

	if( cCap->pBuilder->AllocCapFile(T2W(cCap->szCaptureFile), (DWORDLONG)cCap->wCapFileSize * 1024L * 1024L) != NOERROR )
	 {
		ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Allocation falied:\r\nFailed to pre-allocate capture file space!"));
		return VIPRET_INTERNAL_ERR;
	 }

	return VIPRET_OK;
 }


////////////////////////////////////////////////////////////////////////////////////////////

/*
 * Put up a dialog to allow the user to select a capture file.
 */
int vipDirectXInput2::setCaptureFile(char* pszName)
{
	lstrcpyn(cCap->szCaptureFile, pszName, _MAX_PATH);

	USES_CONVERSION;

        OFSTRUCT os;

        // We have a capture file name

        // If this is a new file, then invite the user to allocate some space
#ifdef UNICODE
        // Convert Multibyte string to ANSI
        char szCaptureFile[STR_MAX_LENGTH];
        int rc = WideCharToMultiByte(CP_ACP, 0, cCap->szCaptureFile, -1,
                                     szCaptureFile, STR_MAX_LENGTH, NULL, NULL);
#else
        TCHAR *szCaptureFile = cCap->szCaptureFile;
#endif

        if(OpenFile(szCaptureFile, &os, OF_EXIST) == HFILE_ERROR)
        {
            // bring up dialog, and set new file size
            if( AllocCaptureFile() )
                return VIPRET_INTERNAL_ERR;
        }

    // tell the file writer to use the new filename
    if(cCap->pSink)
    {
        cCap->pSink->SetFileName(T2W(cCap->szCaptureFile), NULL);
    }

    return VIPRET_OK;
}


////////////////////////////////////////////////////////////////////////////////////////////

double vipDirectXInput2::getFrameRateCurrent()
 {
    HRESULT hr = E_FAIL;
	double ret = 0.0;
	if(cCap->pVSC)
	{
		AM_MEDIA_TYPE *pmt;
		hr = cCap->pVSC->GetFormat(&pmt);

		// DV capture does not use a VIDEOINFOHEADER
		if(hr == NOERROR)
		{
			if(pmt->formattype == FORMAT_VideoInfo)
			{
				VIDEOINFOHEADER *pvi = (VIDEOINFOHEADER *)pmt->pbFormat;
				ret = (double)(10000000 / pvi->AvgTimePerFrame);

			}
			DeleteMediaType(pmt);
		}
	}
	return ret;
 }


// Allow the user to choose a frame rate
//
int vipDirectXInput2::setFrameRate(double rate)
{
    if ( rate <= 0.0 )
		return VIPRET_PARAM_ERR;

	if (!cCap->fUseFrameRate)
		return VIPRET_ILLEGAL_USE;

	if (rate == cCap->FrameRate)
		return VIPRET_OK;

    HRESULT hr = E_FAIL;

    // If somebody unchecks "use frame rate" it means we will no longer
    // tell the filter what frame rate to use... it will either continue
    // using the last one, or use some default, or if you bring up a dialog
    // box that has frame rate choices, it will obey them.

	bool didPrev = cCap->fPreviewing;
	if(cCap->fPreviewing)
		StopPreview();

	// now tell it what frame rate to capture at.  Just find the format it
	// is capturing with, and leave everything else alone
	if(cCap->pVSC)
	{
		AM_MEDIA_TYPE *pmt;
		hr = cCap->pVSC->GetFormat(&pmt);

		// DV capture does not use a VIDEOINFOHEADER
		if(hr == NOERROR)
		{
			if(pmt->formattype == FORMAT_VideoInfo)
			{
				VIDEOINFOHEADER *pvi = (VIDEOINFOHEADER *)pmt->pbFormat;
				pvi->AvgTimePerFrame =(LONGLONG)(10000000 / cCap->FrameRate);

				hr = cCap->pVSC->SetFormat(pmt);
				if(hr != S_OK)
				{
					ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("%x: Cannot set new frame rate"), hr);
					return VIPRET_INTERNAL_ERR;
				}
			}
			DeleteMediaType(pmt);
		}
	}

	if(hr != NOERROR)
	{
		ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Cannot set frame rate for capture"));
		return VIPRET_INTERNAL_ERR;
	}
	if(didPrev)  // we were previewing
		StartPreview();

	return VIPRET_OK;
}


/* error in include file? msacm.h


// choose an audio capture format using ACM
//
void vipDirectXInput2::ChooseAudioFormat()
{
    ACMFORMATCHOOSE cfmt;
    DWORD dwSize;
    LPWAVEFORMATEX lpwfx;
    AM_MEDIA_TYPE *pmt;

    // there's no point if we can't set a new format
    if(cCap->pASC == NULL)
        return;

    // What's the largest format size around?
    acmMetrics(NULL, ACM_METRIC_MAX_SIZE_FORMAT, &dwSize);
    HRESULT hr = cCap->pASC->GetFormat(&pmt);
    if(hr != NOERROR)
        return;

    lpwfx = (LPWAVEFORMATEX)pmt->pbFormat;
    dwSize = (DWORD) (max(dwSize, lpwfx->cbSize + sizeof(WAVEFORMATEX)));

    // !!! This doesn't really map to the supported formats of the filter.
    // We should be using a property page based on IAMStreamConfig

    // Put up a dialog box initialized with the current format
    lpwfx = (LPWAVEFORMATEX)GlobalAllocPtr(GHND, dwSize);
    if(lpwfx)
    {
        CopyMemory(lpwfx, pmt->pbFormat, pmt->cbFormat);
        _fmemset(&cfmt, 0, sizeof(ACMFORMATCHOOSE));
        cfmt.cbStruct = sizeof(ACMFORMATCHOOSE);
        cfmt.fdwStyle = ACMFORMATCHOOSE_STYLEF_INITTOWFXSTRUCT;

        // show only formats we can capture
        cfmt.fdwEnum = ACM_FORMATENUMF_HARDWARE | ACM_FORMATENUMF_INPUT;
        cfmt.hwndOwner = cCap->ghwndApp;
        cfmt.pwfx = lpwfx;
        cfmt.cbwfx = dwSize;

        // we chose a new format... so give it to the capture filter
        if(!acmFormatChoose(&cfmt))
        {
            if(cCap->fPreviewing)
                StopPreview();  // can't call IAMStreamConfig::SetFormat

            // while streaming
            ((CMediaType *)pmt)->SetFormat((LPBYTE)lpwfx,
                lpwfx->cbSize + sizeof(WAVEFORMATEX));

            cCap->pASC->SetFormat(pmt);  // filter will reconnect
            if(cCap->fWantPreview)
                StartPreview();
        }
        GlobalFreePtr(lpwfx) ;
    }

    DeleteMediaType(pmt);
}
*/









////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////


// how many captured/dropped so far
//
void vipDirectXInput2::UpdateStatus(bool fAllStats)
{
    HRESULT hr;
//    TCHAR tach[160];

    // we use this interface to get the number of captured and dropped frames
    // NOTE:  We cannot query for this interface earlier, as it may not be
    // available until the pin is connected
    if(!cCap->pDF)
    {
        hr = cCap->pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,
                                          &MEDIATYPE_Interleaved, cCap->pVCap,
                                          IID_IAMDroppedFrames, (void **)&cCap->pDF);
        if(hr != S_OK)
            hr = cCap->pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,
                                              &MEDIATYPE_Video, cCap->pVCap,
                                              IID_IAMDroppedFrames, (void **)&cCap->pDF);
    }

    // this filter can't tell us dropped frame info.
    if(!cCap->pDF)
    {
        ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Filter cannot report capture information"), hr);
        return;
    }

    hr = cCap->pDF->GetNumDropped(&cCap->lDroppedCurrent);
    if(hr == S_OK)
        hr = cCap->pDF->GetNumNotDropped(&cCap->lNotCurrent);
    if(hr != S_OK)
        return;

    cCap->lDroppedCurrent -= cCap->lDroppedBase;
    cCap->lNotCurrent -= cCap->lNotBase;



    if(!fAllStats)
    {
//        LONG lTime = timeGetTime() - cCap->lCapStartTime;
//        wsprintf(tach, TEXT("Captured %d frames (%d dropped) %d.%dsec\0"), cCap->lNotCurrent,
//                 cCap->lDroppedCurrent, lTime / 1000,
//                 lTime / 100 - lTime / 1000 * 10);
//        statusUpdateStatus(ghwndStatus, tach);
        return;
    }

    // we want all possible stats, including capture time and actual acheived
    // frame rate and data rate (as opposed to what we tried to get).  These
    // numbers are an indication that though we dropped frames just now, if we
    // chose a data rate and frame rate equal to the numbers I'm about to
    // print, we probably wouldn't drop any frames.

    // average size of frame captured
    hr = cCap->pDF->GetAverageFrameSize(&cCap->lAvgFrameSizeCurrent);
    if(hr != S_OK)
        return;

	// how long capture lasted
	LONG lDurMS;
	if (cCap->lCapStopTime)
    	lDurMS = cCap->lCapStopTime - cCap->lCapStartTime;
	else
	    lDurMS = timeGetTime() - cCap->lCapStartTime;

    if(lDurMS > 0)
    {
        cCap->flFrameCurrent = (double)(LONGLONG)cCap->lNotCurrent * 1000. /
            (double)(LONGLONG)lDurMS;
        cCap->lDataCurrent = (long)(LONGLONG)(cCap->lNotCurrent / (double)(LONGLONG)lDurMS *
            1000. * (double)(LONGLONG)cCap->lAvgFrameSizeCurrent);
    }
    else
    {
        cCap->flFrameCurrent = 0.;
        cCap->lDataCurrent = 0;
    }
/*
    wsprintf(tach, TEXT("Captured %d frames in %d.%d sec (%d dropped): %d.%d fps %d.%d Meg/sec\0"),
             cCap->lNotCurrent, lDurMS / 1000, lDurMS / 100 - lDurMS / 1000 * 10,
             cCap->lDroppedCurrent, (int)cCap->flFrameCurrent,
             (int)(cCap->flFrameCurrent * 10.) - (int)cCap->flFrameCurrent * 10,
             cCap->lDataCurrent / 1000000,
             cCap->lDataCurrent / 1000 - (cCap->lDataCurrent / 1000000 * 1000));
*/
//    statusUpdateStatus(ghwndStatus, tach);

	cCap->wCapFileSize = (WORD)GetSize( cCap->szCaptureFile );

}



////////////////////////////////////////////////////////////////////////////////////////////


int vipDirectXInput2::setCurrentDevices(int szVideo, int szAudio)
 {
	IMoniker *pmVideo;
	IMoniker *pmAudio;

//TODO UPPER LIMIT

	if (szAudio < 0)
	 {
        IMonRelease(cCap->pmAudio);
        cCap->pmAudio = NULL;

        pmAudio = NULL;
        cCap->pmAudioIndex = -1;

	 }
	else
		pmAudio = cCap->rgpmAudioMenu[szAudio];

	if (szVideo < 0)
	 {
        IMonRelease(cCap->pmVideo);
        cCap->pmVideo = NULL;

        pmVideo = NULL;
        cCap->pmVideoIndex = -1;
	 }
	else
		pmVideo = cCap->rgpmVideoMenu[szVideo];

	#define VERSIZE 40
	#define DESCSIZE 80

	USES_CONVERSION;
	int versize = VERSIZE;
	int descsize = DESCSIZE;
	WCHAR wachVer[VERSIZE]={0}, wachDesc[DESCSIZE]={0};
	TCHAR tachStatus[VERSIZE + DESCSIZE + 5]={0};

		// they chose a new device. rebuild the graphs
	if(cCap->pmVideo != pmVideo || cCap->pmAudio != pmAudio)
	 {
		if(pmVideo)
			pmVideo->AddRef();

		if(pmAudio)
			pmAudio->AddRef();

		IMonRelease(cCap->pmVideo);
		IMonRelease(cCap->pmAudio);
		cCap->pmVideo = pmVideo;
		cCap->pmAudio = pmAudio;
		cCap->pmAudioIndex = szAudio;
        cCap->pmVideoIndex = szVideo;

		if(cCap->fPreviewing)
			StopPreview();

		if(cCap->fCaptureGraphBuilt || cCap->fPreviewGraphBuilt)
			TearDownGraph();

		FreeCapFilters();

		if ( InitCapFilters() )
		 {
			FreeCapFilters();
			ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Cannot use selected device.\r\nGraph initialization falied."));
			return VIPRET_INTERNAL_ERR;
		 }

		if(cCap->fWantPreview)   // were we previewing?
		 {
			BuildPreviewGraph();
			StartPreview();
		 }

	 }


	// Put the video driver name - if the filter supports
	// IAMVideoCompression::GetInfo, that's the best way to get the name and
	// the version.  Otherwise use the name we got from device enumeration
	// as a fallback.
	if(cCap->pVC)
	 {
		HRESULT hr = cCap->pVC->GetInfo(wachVer, &versize, wachDesc, &descsize,
							   NULL, NULL, NULL, NULL);
		if(hr == S_OK)
		 {
			// It's possible that the call succeeded without actually filling
			// in information for description and version.  If these strings
			// are empty, just display the device's friendly name.
			if(wcslen(wachDesc) && wcslen(wachVer))
			 {
				wsprintf(tachStatus, TEXT("%s - %s\0"), W2T(wachDesc), W2T(wachVer));
				ErrMsg(cCap->ghwndApp, cCap->displayErrorMessages, tachStatus);
				//                statusUpdateStatus(ghwndStatus, tachStatus);
				return VIPRET_OK;
			 }
		 }
	}
	// Since the GetInfo method failed (or the interface did not exist),
	// display the device's friendly name.
	//    statusUpdateStatus(ghwndStatus, W2T(cCap->wachVideoFriendlyName));

	return VIPRET_OK;
 }



////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief  Get current device id.
 * @return current device id, if disconnected return -1
 * @see    enumerateDevices(void);
 * @see    getDeviceCount(void);
 */
int vipDirectXInput2::getCurrentDeviceVideo()
 {
	return cCap->pmVideoIndex;
 }

/**
 * @brief  Get current device id.
 * @return current device id, if disconnected return -1
 * @see    enumerateDevices(void);
 * @see    getDeviceCount(void);
 */
int vipDirectXInput2::getCurrentDeviceAudio()
 {
	return cCap->pmAudioIndex;
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
 * @see    operator >> (vipFrameCache&)
 */
int vipDirectXInput2::extractTo(vipFrameYUV420& img)
 {
	INFO("int vipDirectXInput::extractTo(vipFrameCache& img) [pushing data]")

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
 * @see    operator >> (vipFrameCache24&)
 */
int vipDirectXInput2::extractTo(vipFrameRGB24& img)
 {
	INFO("int vipDirectXInput::extractTo(vipFrameCache24& img) [pushing data]")

//	if (!cCap->GrabbingEnabled)
//		return VIPRET_ILLEGAL_USE;
 	if (!cCap->pSampleGrabber)
		return VIPRET_INTERNAL_ERR;

	if (img.width != width || img.height != height)
		img.reAllocCanvas(width, height);

	cCap->pCallbackGrabber->bufferSize = width*height*3;
	cCap->pCallbackGrabber->buffer = img.data[0];

	cCap->pCallbackGrabber->frameWanted = true;

	WaitForSingleObject(cCap->pCallbackGrabber->event, 100);

	return VIPRET_OK;
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
 * @see    operator >> (vipFrameGrey&)
 */
int vipDirectXInput2::extractTo(vipFrameT<unsigned char>& img)
 {
	INFO("int vipDirectXInput::extractTo(vipFrameGrey& img) [pushing data]")

	return VIPRET_NOT_IMPLEMENTED;
 }



/*




//Capture RAW IMAGE BITS 24bits/pixel
DWORD vipDirectXInput2::ImageCapture(LPCTSTR szFile)
{
	BYTE *pImage;
	DWORD dwSize,dwWritten;
	dwSize=this->GrabFrame ();
	this->GetFrame (&pImage);

	HANDLE hFile = CreateFile(szFile, GENERIC_WRITE, FILE_SHARE_READ, NULL,
					  CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

	if (hFile == INVALID_HANDLE_VALUE)
	return FALSE;

	WriteFile(hFile, (LPCVOID)pImage , m_nFramelen, &dwWritten, 0);
	// Close the file
	CloseHandle(hFile);

	return dwWritten;
}


DWORD vipDirectXInput2::GrabFrame()
{
	if(m_pWC )
    {
       BYTE* lpCurrImage = NULL;

        // Read the current video frame into a byte buffer.  The information
        // will be returned in a packed Windows DIB and will be allocated
        // by the VMR.
        if(m_pWC->GetCurrentImage(&lpCurrImage) == S_OK)
        {

			LPBITMAPINFOHEADER  pdib = (LPBITMAPINFOHEADER) lpCurrImage;

			if(m_pFrame==NULL || (pdib->biHeight * pdib->biWidth * 3) !=m_nFramelen )
			{
				if(m_pFrame!=NULL)
				delete []m_pFrame;

				m_nFramelen=pdib->biHeight * pdib->biWidth * 3;
				m_pFrame=new BYTE [pdib->biHeight * pdib->biWidth * 3] ;


			}

			if(pdib->biBitCount ==32)
			{
				DWORD  dwSize=0, dwWritten=0;

				BYTE *pTemp32;
				pTemp32=lpCurrImage + sizeof(BITMAPINFOHEADER);

				//change from 32 to 24 bit /pixel
				this->Convert24Image(pTemp32, m_pFrame, pdib->biSizeImage);

			}

			CoTaskMemFree(lpCurrImage);	//free the image
		}
		else
		{
			return -1;
		}

	}
	else
	{
		return -1;
	}



    return m_nFramelen;

}


DWORD vipDirectXInput2::GetFrame(BYTE **pFrame)
{
	if(m_pFrame && m_nFramelen)
	{
	*pFrame=m_pFrame;
	}


	return m_nFramelen;
}
*/

bool Convert24Image(BYTE *p32Img, BYTE *p24Img,DWORD dwSize32)
{

	if(p32Img != NULL && p24Img != NULL && dwSize32>0)
	{

		DWORD dwSize24;

		dwSize24=(dwSize32 * 3)/4;

		BYTE *pTemp,*ptr;
		//pTemp=p32Img + sizeof(BITMAPINFOHEADER); ;
		pTemp=p32Img;

		ptr=p24Img + dwSize24-1 ;

		int ival=0;
		for (DWORD index = 0; index < dwSize32/4 ; index++)
		{
			unsigned char r = *(pTemp++);
			unsigned char g = *(pTemp++);
			unsigned char b = *(pTemp++);
			(pTemp++);//skip alpha

			*(ptr--) = b;
			*(ptr--) = g;
			*(ptr--) = r;

		}
	}
	else
	{
		return false;
	}

return true;
}

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////


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
//int vipDirectXInput2::getFormat(int format, int *width, int *height, char* desc)
// {
//  assert(vc);
//  assert(vc->device != -1);
//  assert(vc->format_count);
/*
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
*/



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



////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

int vipDirectXInput2::setPreviewWindow(void* HWND_Owner)
 {
	cCap->ghwndApp = static_cast<HWND>(HWND_Owner);

	return VIPRET_OK;
 }

double vipDirectXInput2::getFrameRate()
 {
	return cCap->FrameRate;
 }

bool vipDirectXInput2::isPreviewing()
 {
	if ( cCap->fPreviewing )
		return true;
	else
		return false;
 }

bool vipDirectXInput2::isCapturing()
 {
	if ( cCap->fCapturing )
		return true;
	else
		return false;
 }


bool vipDirectXInput2::isCapturingAudio()
 {
	if ( cCap->fCapAudio )
		return true;
	else
		return false;
 }

bool vipDirectXInput2::isUncompressed()
 {
	if ( !cCap->fMPEG2 )
		return true;
	else
		return false;
 }

bool vipDirectXInput2::isMPEG2Encoded()
 {
	if ( cCap->fMPEG2 )
		return true;
	else
		return false;
 }

bool vipDirectXInput2::isPreviewFaked()
 {
	if (cCap->fPreviewFaked)
		return true;
	return false;
 }


int vipDirectXInput2::setMPEG2Encode(bool enable)
 {
	if ( cCap->fCapturing )
		return VIPRET_ILLEGAL_USE;

	cCap->fMPEG2 = enable;


	return VIPRET_OK;
 }

int vipDirectXInput2::setFrameRateControlEnabled(bool enable)
 {
	cCap->fUseFrameRate = enable;

	return VIPRET_OK;
 }

int vipDirectXInput2::setFrameGrabbingEnabled(bool enable)
 {
	if ( cCap->fCapturing )
		return VIPRET_ILLEGAL_USE;

//return VIPRET_NOT_IMPLEMENTED;

	bool didPreviewing = cCap->fPreviewing;

	HRESULT hr = 0;

	if(cCap->fCaptureGraphBuilt || cCap->fPreviewGraphBuilt)
		TearDownGraph();

	FreeCapFilters();

	cCap->GrabbingEnabled = enable;

	if (didPreviewing)   // were we previewing?
	 {
		if ( InitCapFilters() )
		 {
			FreeCapFilters();
			ErrMsg(cCap->ghwndApp,  cCap->displayErrorMessages, TEXT("Cannot enable fram grabbing.\r\nGraph initialization falied."), hr);
			cCap->GrabbingEnabled = false;
			InitCapFilters();
			return VIPRET_INTERNAL_ERR;
		 }
		BuildPreviewGraph();
		StartPreview();
	 }


	return VIPRET_OK;
 }

bool vipDirectXInput2::isFrameGrabbingEnabled()
 {
	 return cCap->GrabbingEnabled;
 }

bool vipDirectXInput2::EoF()
{
	if ( !cCap->GrabbingEnabled )
		return false;

	if ( cCap->fCapturing || cCap->fPreviewing )
		return true;

	return false;
}


int vipDirectXInput2::setCaptureAudioEnabled(bool enable)
 {

	if ( cCap->fCapturing )
		return VIPRET_ILLEGAL_USE;

	if ( cCap->fPreviewing )
	 {
		int ret = StopPreview();
		//TearDownGraph();
		cCap->fCapAudio = enable;
		//BuildPreviewGraph();
		ret += StartPreview();
		if ( ret )
			return VIPRET_INTERNAL_ERR;
		else
			return VIPRET_OK;
	 }

	cCap->fCapAudio = enable;

	return VIPRET_OK;

 }


long vipDirectXInput2::getCapturedFramesCount(bool forceUpdate)
 {
	if (forceUpdate)
		UpdateStatus();

	return cCap->lNotCurrent;
 }

long vipDirectXInput2::getDroppedFramesCount(bool forceUpdate)
 {
	if (forceUpdate)
		UpdateStatus();

	return cCap->lDroppedCurrent;
 }

long vipDirectXInput2::getCapturedElapsedTime()
 {
	if ( cCap->fCapturing )
		return (long)( timeGetTime() - cCap->lCapStartTime );
	else
		return (long)( cCap->lCapStopTime - cCap->lCapStartTime );

 }

long vipDirectXInput2::getAverageFrameSize(bool forceUpdate)
 {
	if (forceUpdate)
		UpdateStatus(true);

	return cCap->lAvgFrameSizeCurrent;
 }



double vipDirectXInput2::getCapturedFrameRate(bool forceUpdate)
 {
	if (forceUpdate)
		UpdateStatus(true);

	return (long)cCap->flFrameCurrent;
 }


long vipDirectXInput2::getCapturedDataRate(bool forceUpdate)
 {
	if (forceUpdate)
		UpdateStatus(true);

	return cCap->lDataCurrent;
 }

vipDirectXInput2::FORMAT_CSP vipDirectXInput2::getCurrentFormat() { return cCap->format_CSP; };

int vipDirectXInput2::getCurrentFormatDescription(char* buffer)
 {
	switch (cCap->format_CSP)
	 {
		 case UNKNOWN:	strcpy(buffer, "UNKNOW csp");

		 case VETFRAMET_CS_RGB:	strcpy(buffer, "RGB24 csp");

	 }


	return VIPRET_OK;

 };



unsigned short vipDirectXInput2::getFileSize(bool forceUpdate)
 {
	if (forceUpdate)
		UpdateStatus(true);

	return (unsigned short)cCap->wCapFileSize;
 }


int vipDirectXInput2::getVideoFriendlyName(char* buffer)
 {
	if ( cCap->wachVideoFriendlyName[0] == 0 )
		return VIPRET_ILLEGAL_USE;

	char* str = Wide2Char(cCap->wachVideoFriendlyName);
	sprintf(buffer, "%s", str);
	free(str);

	return VIPRET_OK;
 }

unsigned long vipDirectXInput2::getVideoBitRate()
 {
	 return (unsigned long)cCap->VideoBitRate;
 }

unsigned long vipDirectXInput2::getAudioBitRate()
 {
	 return (unsigned long)cCap->AudioBitRate;
 }

int vipDirectXInput2::getAudioFriendlyName(char* buffer)
 {
	if ( cCap->wachAudioFriendlyName[0] == 0 )
		return VIPRET_ILLEGAL_USE;

	char* str = Wide2Char(cCap->wachAudioFriendlyName);
	sprintf(buffer, "%s", str);
	free(str);

	return VIPRET_OK;
 }


/**
 * @brief  Returns the device description. Returns NULL in the last device.
 *
 * @see    enumerateDevices(void);
 * @see    getDeviceCount(void);
 */
const char* vipDirectXInput2::getDeviceVideoDescription(int device)
 {
  // List available Devices once
  if (cCap->iNumVCapDevices == 0)
  {
    enumerateDevices();

    if (cCap->iNumVCapDevices == 0)
      return NULL;
  }

  if (device >= cCap->iNumVCapDevices)
    return NULL;

  return deviceVideoDesc[device];
 }


/**
 * @brief  Returns the device description. Returns NULL in the last device.
 *
 * @see    enumerateDevices(void);
 * @see    getDeviceCount(void);
 */
const char* vipDirectXInput2::getDeviceAudioDescription(int device)
 {
  // List available Devices once
  if (cCap->iNumACapDevices == 0)
  {
    enumerateDevices();

    if (cCap->iNumACapDevices == 0)
      return NULL;
  }

  if (device >= cCap->iNumACapDevices)
    return NULL;

  return deviceAudioDesc[device];
 }


int vipDirectXInput2::getDeviceVideoCount(void)
 {
	 return cCap->iNumVCapDevices;
 }
int vipDirectXInput2::getDeviceAudioCount(void)
 {
	 return cCap->iNumACapDevices;
 }

void vipDirectXInput2::setErrorMessagesEnabled(bool enable)
 {
	 cCap->displayErrorMessages = enable;
 }

void vipDirectXInput2::doUpdatePreviewWindow()
 {
	ResizeWindow(cCap->ghwndApp, width, height);
 }

void vipDirectXInput2::setAutoUpdatePreviewWindowEnabled(bool enable)
 {
	cCap->autoUpdateWindow = enable;
 }

bool vipDirectXInput2::isAutoUpdatePreviewWindowEnabled()
 {
	return cCap->autoUpdateWindow;
 }


int vipDirectXInput2::showPreviewWindow(bool show)
 {
	if ( !cCap->pVW )
		return VIPRET_ILLEGAL_USE;

	if ( show )

		cCap->pVW->put_Visible(-1);
	else
		cCap->pVW->put_Visible(0);

	return VIPRET_OK;
 }


long vipDirectXInput2::getFreeSpaceLeft()
 {
	return GetFreeDiskSpaceInKB( cCap->szCaptureFile );
 }


/*

int vipDirectXInput2::getDShowGraphFilters(char* buffer)
 {
	IEnumFilters *pEnum = NULL;
	IBaseFilter *pFilter;
	ULONG cFetched;

	 cCap->pFg->EnumFilters(&pEnum);

  IEnumFilters *pEnum = NULL;

  IBaseFilter *pFilter;

  ULONG cFetched;

  pGraph->EnumFilters(&pEnum);


  while(pEnum->Next(1, &pFilter, &cFetched) == S_OK)

  {

    FILTER_INFO FilterInfo;

    char szName[256];

    pFilter->QueryFilterInfo(&FilterInfo);

    WideCharToMultiByte(CP_ACP, 0, FilterInfo.achName, -1, szName, 256, 0, 0);

    fname= szName;

    names.push_back(fname);


    SAFE_RELEASE(FilterInfo.pGraph);

    SAFE_RELEASE(pFilter);

  }



  SAFE_RELEASE(pEnum);



  return names;

 }

*/


////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////


// Tear down everything downstream of a given filter
void NukeDownstream(vipDXCapture2* cCap, IBaseFilter *pf)
{
    IPin *pP=0, *pTo=0;
    ULONG u;
    IEnumPins *pins = NULL;
    PIN_INFO pininfo;

    if (!pf)
        return;

    HRESULT hr = pf->EnumPins(&pins);
    pins->Reset();

    while(hr == NOERROR)
    {
        hr = pins->Next(1, &pP, &u);
        if(hr == S_OK && pP)
        {
            pP->ConnectedTo(&pTo);
            if(pTo)
            {
                hr = pTo->QueryPinInfo(&pininfo);
                if(hr == NOERROR)
                {
                    if(pininfo.dir == PINDIR_INPUT)
                    {
                        NukeDownstream(cCap, pininfo.pFilter);
                        cCap->pFg->Disconnect(pTo);
                        cCap->pFg->Disconnect(pP);
                        cCap->pFg->RemoveFilter(pininfo.pFilter);
                    }
                    pininfo.pFilter->Release();
                }
                pTo->Release();
            }
            pP->Release();
        }
    }

    if(pins)
        pins->Release();
}

////////////////////////////////////////////////////////////////////////////////////////



void IMonRelease(IMoniker *&pm)
{
    if(pm)
    {
        pm->Release();
        pm = 0;
    }
}





////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////// UTILITIES AND STATICs
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////



/*----------------------------------------------------------------------------*\
|   ErrMsg - Opens a Message box with a error message in it.  The user can     |
|            select the OK button to continue                                  |
\*----------------------------------------------------------------------------*/
void ErrMsg(HWND ghwndApp, bool show, LPTSTR szFormat,...)
{
	if ( !show )
		return;

    static TCHAR szBuffer[2048]={0};
    const size_t NUMCHARS = sizeof(szBuffer) / sizeof(szBuffer[0]);
    const int LASTCHAR = NUMCHARS - 1;

    // Format the input string
    va_list pArgs;
    va_start(pArgs, szFormat);

    // Use a bounded buffer size to prevent buffer overruns.  Limit count to
    // character size minus one to allow for a NULL terminating character.
    _vsntprintf(szBuffer, NUMCHARS - 1, szFormat, pArgs);
    va_end(pArgs);

    // Ensure that the formatted string is NULL-terminated
    szBuffer[LASTCHAR] = TEXT('\0');

    MessageBox(ghwndApp, szBuffer, NULL,
               MB_OK | MB_ICONEXCLAMATION | MB_TASKMODAL);
}


////////////////////////////////////////////////////////////////////////////////////////////



void ResizeWindow(HWND ghwndApp, int w, int h)
{

//	SetWindowPos(ghwndApp, NULL, 0, 0, w, h,  SWP_NOZORDER | SWP_NOMOVE);

    RECT rcW, rcC;
    int xExtra, yExtra;
    int cyBorder = GetSystemMetrics(SM_CYBORDER);

    gnRecurse++;

    GetWindowRect(ghwndApp, &rcW);
    GetClientRect(ghwndApp, &rcC);
    xExtra = rcW.right - rcW.left - rcC.right;
    yExtra = rcW.bottom - rcW.top - rcC.bottom + cyBorder;

    rcC.right = w;
    rcC.bottom = h;
    SetWindowPos(ghwndApp, NULL, 0, 0, rcC.right + xExtra,
        rcC.bottom + yExtra, SWP_NOZORDER | SWP_NOMOVE);

    // we may need to recurse once.  But more than that means the window cannot
    // be made the size we want, trying will just stack fault.
    //
    if(gnRecurse == 1 && ((rcC.right + xExtra != rcW.right - rcW.left && w > GetSystemMetrics(SM_CXMIN)) ||
        (rcC.bottom + yExtra != rcW.bottom - rcW.top)))
        ResizeWindow(ghwndApp, w,h);

    gnRecurse--;

}



////////////////////////////////////////////////////////////////////////////////////////////


//
// This function can be used when loading libraries in the Windows System
// folder.  It queries for the system folder and prepends the path to the
// name of the target library.  This helps to prevent spoofing of system DLLs.
//
// NOTE: Using this function may break apps who use Windows Fusion or who
// explicitly replace Windows DLLs in the application's local folder.
// If security is paramount, you can use this as a replacement for LoadLibrary().
//
HMODULE UtilLoadLibrary(LPCTSTR lpFileName)
{
    TCHAR szFullPath[MAX_PATH];
    bool fSuccess = false;

    // Prevent buffer overflow by limiting size of library name
    int nLibLength = lstrlen(lpFileName);
    if((nLibLength > MAX_PATH) || (NULL == lpFileName))
        return NULL;

    int nSpaceAllowed = MAX_PATH - nLibLength - 4; // Allow for '\' and '\0'
    int nSpaceUsed = 0;

    // Initialize to a NULL string
    szFullPath[0] = TEXT('\0');

    // Read the Windows System directory
    nSpaceUsed = GetSystemDirectory(szFullPath, nSpaceAllowed);

    // If the function fails, the return value will be zero.
    // If the buffer isn't large enough, the function will return the size
    // of the buffer required to hold the path.  Check both failures.
    if((nSpaceUsed != 0) && (nSpaceUsed <= nSpaceAllowed))
    {
        // Now we have the Windows/System path with enough space left
        // to add the libary name and a terminating NULL character
        lstrcat(szFullPath, TEXT("\\\0"));
        lstrcat(szFullPath, lpFileName);
        lstrcat(szFullPath, TEXT("\0"));
        fSuccess = TRUE;
    }

    if(!fSuccess)
    {
        // An error occurred, so fallback to the default behavior by using
        // the NULL-terminated library name provided as a parameter.
        lstrcpyn(szFullPath, lpFileName, NUMELMS(szFullPath)-1);
        szFullPath[MAX_PATH - 1] = TEXT('\0');
    }

    return ((HMODULE) LoadLibrary(szFullPath));
}







////////////////////////////////////////////////////////////////////////////////////////////



DWORDLONG GetSize(LPCTSTR tach)
{
    HANDLE hFile = CreateFile(tach, GENERIC_READ, FILE_SHARE_READ, 0,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if(hFile == INVALID_HANDLE_VALUE)
    {
        return 0;
    }

    DWORD dwSizeHigh;
    DWORD dwSizeLow = GetFileSize(hFile, &dwSizeHigh);

    DWORDLONG dwlSize = dwSizeLow + ((DWORDLONG)dwSizeHigh << 32);

    if(!CloseHandle(hFile))
    {
        dwlSize = 0;
    }

    return dwlSize;
}



////////////////////////////////////////////////////////////////////////////////////////////

//
// GetFreeDiskSpace: Function to Measure Available Disk Space
//
long GetFreeDiskSpaceInKB(LPTSTR pFile)
{
    DWORD dwFreeClusters, dwBytesPerSector, dwSectorsPerCluster, dwClusters;
    TCHAR RootName[MAX_PATH];
    LPTSTR ptmp=0;    //required arg
    ULARGE_INTEGER ulA, ulB, ulFreeBytes;

    // need to find path for root directory on drive containing this file.
    GetFullPathName(pFile, NUMELMS(RootName), RootName, &ptmp);

    // truncate this to the name of the root directory (how tedious)
    if(RootName[0] == '\\' && RootName[1] == '\\')
    {
        // path begins with  \\server\share\path so skip the first
        // three backslashes
        ptmp = &RootName[2];
        while(*ptmp && (*ptmp != '\\'))
        {
            ptmp++;
        }
        if(*ptmp)
        {
            // advance past the third backslash
            ptmp++;
        }
    }
    else
    {
        // path must be drv:\path
        ptmp = RootName;
    }

    // find next backslash and put a null after it
    while(*ptmp && (*ptmp != '\\'))
    {
        ptmp++;
    }

    // found a backslash ?
    if(*ptmp)
    {
        // skip it and insert null
        ptmp++;
        *ptmp = '\0';
    }

    // the only real way of finding out free disk space is calling
    // GetDiskFreeSpaceExA, but it doesn't exist on Win95

    HINSTANCE h = LoadLibrary(TEXT("kernel32.dll\0"));
    if(h)
    {
        typedef BOOL(WINAPI *MyFunc)(LPCTSTR RootName, PULARGE_INTEGER pulA, PULARGE_INTEGER pulB, PULARGE_INTEGER pulFreeBytes);

#ifdef UNICODE
        MyFunc pfnGetDiskFreeSpaceEx = (MyFunc)GetProcAddress(h, "GetDiskFreeSpaceExW");
#else
        MyFunc pfnGetDiskFreeSpaceEx = (MyFunc)GetProcAddress(h, "GetDiskFreeSpaceExA");
#endif
        FreeLibrary(h);

        if(pfnGetDiskFreeSpaceEx)
        {
            if(!pfnGetDiskFreeSpaceEx(RootName, &ulA, &ulB, &ulFreeBytes))
                return -1;
            else
                return (long)(ulFreeBytes.QuadPart / 1024);
        }
    }

    if(!GetDiskFreeSpace(RootName, &dwSectorsPerCluster, &dwBytesPerSector,
                         &dwFreeClusters, &dwClusters))
        return (-1);
    else
        return(MulDiv(dwSectorsPerCluster * dwBytesPerSector, dwFreeClusters, 1024));
}




char* Wide2Char(WCHAR* wstr)
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

