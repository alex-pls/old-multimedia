/** @file vipCamCtrlVCC3
 *
 * File containing methods for the 'vipCamCtrlVCC3' class.
 * The header for this class can be found in vipCamCtrlVCC3.h, check
 * that file for class description.
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


#include "stdafx.h"
/////#include <memory.h>


#include "vipCamCtrlVCC3.h"


#include "VCC3_Defs.h"
#include "VCC3_Command.h"

#define	WM_VCC3_NOTIFY	(WM_USER+100)		// VC-C3 Notification Message






vipCamCtrlVCC3::vipCamCtrlVCC3()
{
	fDriverInit = false;
	hWndApp = NULL;


	fPreset = false;		// Preset button state
	fOperate = true;		// Operate Button state

	//szAppName = { "EXAMPLE" };

	iCommPort = DEFAULT_PORT;
	iCommBaud = DEFAULT_BAUD;

}

vipCamCtrlVCC3::~vipCamCtrlVCC3()
{
	Disconnect();
}


void vipCamCtrlVCC3::Init( HWND hWnd )
{
	hWndApp = hWnd;
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////


void vipCamCtrlVCC3::Connect(int port, int baud)
{

	this->iCommPort = port;
	this->iCommBaud = baud;

	this->Reset();
}

void vipCamCtrlVCC3::Disconnect()
{
	if ( fDriverInit )
	{
		// Disable host notification
		DoModeSelect( &vcc3Info, VCC3_HOST_DISABLE );
		VCC3_Close( &vcc3Info );
		fDriverInit = false;
	}

}

bool vipCamCtrlVCC3::Reset()
{

	int	nErrorCode = VCC3_ERR_NONE;

//	StartWait();

	if ( fDriverInit )
	{
		// Disable host notification
		DoModeSelect( &vcc3Info, VCC3_HOST_DISABLE );
		VCC3_Close( &vcc3Info );
		fDriverInit = FALSE;
	}

	fPreset = FALSE;
	fOperate = TRUE;

	nErrorCode = VCC3_Open( &vcc3Info, hWndApp, WM_VCC3_NOTIFY, iCommPort, iCommBaud );

	if ( nErrorCode == VCC3_ERR_NONE )
	{
		// Enable Host Notification mode
		nErrorCode = DoModeSelect( &vcc3Info, VCC3_HOST_ENABLE );

		if ( nErrorCode != VCC3_ERR_NONE )
			VCC3_Close( &vcc3Info );
		else
			fDriverInit = true;
	}

//	EndWait();

	if ( nErrorCode != VCC3_ERR_NONE )
		DisplayVCC3Error( nErrorCode );

	return fDriverInit;
}



////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////


int vipCamCtrlVCC3::setPTZ(cPTZ& value)
{
	int ret = 0;
	ret += setPos(value.Pan, value.Tilt);
	ret += setZoom(value.Zoom);
	return ret;
}


////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////


int vipCamCtrlVCC3::Home()
{
	return DoHome( &vcc3Info );
}

int vipCamCtrlVCC3::getPos(int& pan, int& tilt)
{
	WORD wPan = 0;
	WORD wTilt = 0;

	int ret = DoPanTiltRead( &vcc3Info, &wPan, &wTilt );

	if (ret != 0)
		return ret;

	pan = (int)wPan - 32768;
	tilt = (int)wTilt - 32768;

	return 0;
}

int vipCamCtrlVCC3::setPos(int& pan, int& tilt)
{
	WORD wPan = pan + 32768;
	WORD wTilt = tilt + 32768;

	return DoPanTiltWrite( &vcc3Info, wPan, wTilt );
}

void vipCamCtrlVCC3::getPosPanRange( int& min, int& max )
{
	min = -800;
	max = 800;
}

void vipCamCtrlVCC3::getPosTiltRange( int& min, int& max )
{
	min = -266;
	max = 222;
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// PAN & TILT RELATED CALLS
////////////////////////////////////////////////////////////////////////////////////


int vipCamCtrlVCC3::PanRight()
{
	return DoPanRight( &vcc3Info );
}

int vipCamCtrlVCC3::PanLeft()
{
	return DoPanLeft( &vcc3Info );
}

int vipCamCtrlVCC3::TiltUp()
{
	return DoTiltUp( &vcc3Info );
}

int vipCamCtrlVCC3::TiltDown()
{
	return DoTiltDown( &vcc3Info );
}

int vipCamCtrlVCC3::Stop()
{
	return DoPanTiltStop( &vcc3Info );
}

//int	DoPanLeftTiltUp( LPVCC3INFO lpVCC3 );
//int	DoPanRightTiltUp( LPVCC3INFO lpVCC3 );
//int	DoPanLeftTiltDown( LPVCC3INFO lpVCC3 );
//int	DoPanRightTiltDown( LPVCC3INFO lpVCC3 );

////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////// ZOOM RELATED CALLS
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

int vipCamCtrlVCC3::getZoom( int& value )
{
	WORD wZoom = 0;
	int	ret = DoZoomRead( &vcc3Info, &wZoom );
	value = (int)wZoom;
	return ret;
}

int	vipCamCtrlVCC3::setZoom( int& value )
{
	WORD wZoom = (unsigned short)value;
	return DoZoomWrite( &vcc3Info, wZoom );
}
void vipCamCtrlVCC3::getZoomRange( int& min, int& max )
{
	min = 0;
	max = 1128;
}


int	vipCamCtrlVCC3::ZoomIn( )
{
	return DoZoomTele( &vcc3Info );
}

int	vipCamCtrlVCC3::ZoomOut( )
{
	return DoZoomWide( &vcc3Info );
}

int	vipCamCtrlVCC3::ZoomStop( )
{
	return DoZoomStop( &vcc3Info );
}


//int	DoZoomRead( LPVCC3INFO lpVCC3, LPWORD lpwZoom );
//int	DoZoomWrite( LPVCC3INFO lpVCC3, WORD wZoom );


////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////// FOCUS RELATED CALLS
////////////////////////////////////////////////////////////////////////////////////

//int	DoManualFocus( LPVCC3INFO lpVCC3 );
int vipCamCtrlVCC3::FocusAuto( )
{
	return DoFocusAuto( &vcc3Info );
}


int vipCamCtrlVCC3::FocusNear( )
{
	return DoFocusNear( &vcc3Info );
}

int vipCamCtrlVCC3::FocusFar( )
{
	return DoFocusFar( &vcc3Info );
}

int vipCamCtrlVCC3::FocusStop( )
{
	return DoFocusStop( &vcc3Info );
}

//int	DoManualFocus( LPVCC3INFO lpVCC3 );
////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////// FOCUS RELATED CALLS
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////













/***************************************************************************

	Display VC-C3 error messages

***************************************************************************/

void vipCamCtrlVCC3::DisplayVCC3Error( int nErrorCode )
{
	switch( nErrorCode )
	{
	case	VCC3_ERR_NONE:
		break;

	case	VCC3_ERR_CREATE:
		ErrorMessage( (LPSTR)"Error initializing communications" );
		break;

	case	VCC3_ERR_SET:
		ErrorMessage( (LPSTR)"Error setting driver parameters" );
		break;

	case	VCC3_ERR_FORMAT:
		ErrorMessage( (LPSTR)"Error initializing driver parameters" );
		break;

	case	VCC3_ERR_RECV_TMO:
		ErrorMessage( (LPSTR)"Receive character timeout" );
		break;

	case	VCC3_ERR_RECV_IO:
		ErrorMessage( (LPSTR)"Receive character I/O error" );
		break;

	case	VCC3_ERR_SEND_IO:
		ErrorMessage( (LPSTR)"Send character I/O error" );
		break;

	case	VCC3_ERR_PARAM:
		ErrorMessage( (LPSTR)"Driver parameter error" );
		break;

	case	VCC3_ERR_LENGTH:
		ErrorMessage( (LPSTR)"Invalid response length" );
		break;

	case	VCC3_ERR_MEMORY:
		ErrorMessage( (LPSTR)"Out of memory" );
		break;

	case	VCC3_ERR_NAK:
		ErrorMessage( (LPSTR)"NAK response received" );
		break;

	case	VCC3_ERR_CABLE:
		ErrorMessage( (LPSTR)"VC-C3 is not connected" );
		break;

	case	VCC3_ERR_UNKNOWN:
		ErrorMessage( (LPSTR)"Unknown driver error [%d]", nErrorCode );
		break;

	default:
		ErrorMessage( (LPSTR)"Unknown error [%d]", nErrorCode );
		break;
	}
}

/****************************************************************************

	Display error message

****************************************************************************/

void vipCamCtrlVCC3::ErrorMessage( LPSTR szFmt,... )
{
	char szMsg[128];

	wvsprintf( (LPSTR)szMsg, szFmt, (LPSTR)(&szFmt+1) );
//	MessageBox( hWndApp, (LPSTR)szMsg, (LPSTR)szAppName, MB_OK|MB_APPLMODAL );

	MessageBox( hWndApp, (LPSTR)szMsg, (LPSTR)"asd", MB_OK|MB_APPLMODAL );
}





// questo file mappa i valori normalizzati PTZ ai/dai valori della VCC3
// e le velocità


//_____________________________________________________________________
// CONVERT NORMALIZED PTZ TO CUSTOM PTZ
void NormalizedPTZ2VCC3PTZ(cPTZ* data)
{
	//if ( data == null )
	//	return;

	// PAN: [-1,1] => [-800,800]
	data->Pan = data->Pan * 800;

	// TILT [-1;1] => [-266,222]
	if ( data->Tilt < 0 )
		data->Tilt = data->Tilt * 266;
	else
		data->Tilt = data->Tilt * 222;

	// ZOOM [0,1] => [0,1116]
	data->Zoom = data->Zoom * 1116;
}



//_____________________________________________________________________
// CONVERT CUSTOM PTZ TO NORMALIZED PTZ
void VCC3PTZ2NormalizedPTZ(cPTZ* data)
{
	//if ( data == null )
	//	return;

	// PAN: [-800,800] => [-1,1]
	data->Pan = data->Pan / 800;

	// TILT [-266,222] => [-1;1]
	if ( data->Tilt < 0 )
		data->Tilt = data->Tilt / 266;
	else
		data->Tilt = data->Tilt / 222;

	// ZOOM [0,1116] => [0,1]
	data->Zoom = data->Zoom / 1116;
}




/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////




//_____________________________________________________________________
// CONVERT NORMALIZED PTZ SPEED TO CUSTOM PTZ SPEED
void NormalizedPTZS2VCC3PTZS(cPTZS* data)
{
	// PAN Speed: [0,1] => [1,76]
	data->Pan = (data->Pan) * 75 + 1;

	// TILT Speed: [0,1] => [1,70]
	data->Tilt = data->Tilt * 69 + 1;

	// ZOOM Speed: [0,1] => [0,7]
	data->Zoom = data->Zoom * 7;
}


//_____________________________________________________________________
// CONVERT CUSTOM PTZ SPEED TO NORMALIZED PTZ SPEED
void VCC3PTZS2NormalizedPTZS(cPTZS* data)
{
	//if ( data == null )
	//	return;

	// PAN Speed: [0,1] => [1,76]
	data->Pan = (data->Pan - 1) * 75;

	// TILT Speed: [0,1] => [1,70]
	data->Tilt = (data->Tilt - 1) / 69;

	// ZOOM Speed: [0,7] => [0,1]
	data->Zoom = data->Zoom / 7;
}
