/***************************************************************************

	FILE:		command.c

	AUTHOR:		Eric Chasanoff

	REVISIONS:	05.01.97	Written

				09.15.97

				1. Fixed PresetWrite(): bytes 4 and 5 specify position.


	DESCRIPTION:

		  This file contains example VC-C3 commands.

	DISCLAIMER:

		Raster Builders Inc. and Eric Chasanoff make no representations
		about the correctness or suitability of this software for
		any purpose. It is provided without express or implied
		warranty.

***************************************************************************/

#include "stdafx.h"
/////#include <memory.h>
#include <windows.h>

#include "VCC3_Defs.h"
#include "VCC3_Command.h"

#define	SWAPWORD(w)			((((w)>>8)&0xFF)|(((w)<<8)&0xFF00))

/**********************************************************************

	Mode Select Request

	iMode:	0x00	Enable RS-232 interface
			0x01	Disable RS-232 interface

**********************************************************************/

int	DoModeSelect( LPVCC3INFO lpVCC3, int iMode )
{
	BYTE	cmd[8];

	cmd[0] = 5;	// length
	cmd[1] = VCC3_VIDEOADAPTER_FRAME;
	cmd[2] = VCC3_MODESELECT_REQUEST;
	cmd[3] = 0x01;	// Pan/Tilter control mode
	cmd[4] = (BYTE) iMode;

	return VCC3_Command( lpVCC3, cmd, NULL, NULL );
}

/**********************************************************************

	Mute Video Request

**********************************************************************/

int	DoMuteVideo( LPVCC3INFO lpVCC3, BOOL fEnable )
{
	BYTE	cmd[8];

	cmd[0] = 5;	// length
	cmd[1] = VCC3_VIDEOADAPTER_FRAME;
	cmd[2] = VCC3_MUTE_REQUEST;
	cmd[3] = 0x01;	// Video
	cmd[4] = (BYTE) (fEnable != 0);

	return VCC3_Command( lpVCC3, cmd, NULL, NULL );
}

/**********************************************************************

	Preset Request

**********************************************************************/

int	DoPresetWrite( LPVCC3INFO lpVCC3, WORD wPosition, WORD wAE,
		WORD wPan, WORD wTilt, WORD wZoom )
{
	LPWORD	lpwParam;
	BYTE	cmd[16];

	cmd[0] = 13;	// length
	cmd[1] = VCC3_VIDEOADAPTER_FRAME;
	cmd[2] = VCC3_PRESET_REQUEST;
	cmd[3] = 0x02;	// Write
	cmd[4] = (BYTE) wPosition;	// 1-6
	cmd[5] = (BYTE) wPosition;	// 1-6

	cmd[6] = (BYTE) wAE;

	lpwParam = (LPWORD)(cmd + 7);

	lpwParam[0] = SWAPWORD(wPan);	// PAN
	lpwParam[1] = SWAPWORD(wTilt);	// TILT
	lpwParam[2] = SWAPWORD(wZoom);	// ZOOM

	return VCC3_Command( lpVCC3, cmd, NULL, NULL );
}

/**********************************************************************

	Preset Request

**********************************************************************/

int	DoPresetRead( LPVCC3INFO lpVCC3, WORD wPosition, LPWORD lpwAE,
		LPWORD lpwPan, LPWORD lpwTilt, LPWORD lpwZoom )
{
 	int	nRetCode;
	int	iLen = 0;
	LPWORD	lpwParam;
	BYTE	cmd[8];

	cmd[0] = 5;	// length
	cmd[1] = VCC3_VIDEOADAPTER_FRAME;
	cmd[2] = VCC3_PRESET_REQUEST;
	cmd[3] = 0x01;	// Read
	cmd[4] = (BYTE)wPosition;	// 1-6

	nRetCode = VCC3_Command( lpVCC3, cmd, lpVCC3->response, &iLen );

	if ( nRetCode != VCC3_ERR_NONE )
		return nRetCode;

	if ( iLen != 14 )
		return VCC3_ERR_LENGTH;

	lpwParam = (LPWORD)(lpVCC3->response + 7);

	*lpwAE = lpVCC3->response[6];			// AE
	*lpwPan = SWAPWORD(lpwParam[0]);	// PAN
	*lpwTilt = SWAPWORD(lpwParam[1]);	// TILT
	*lpwZoom = SWAPWORD(lpwParam[2]);	// ZOOM

	return nRetCode;
}

/**********************************************************************

	Preset Request

**********************************************************************/

int	DoPresetSet( LPVCC3INFO lpVCC3, WORD wPosition )
{
	int	nErrorCode;
	WORD	wAE, wPan, wTilt, wZoom;

	if ( (nErrorCode = DoZoomRead( lpVCC3, &wZoom )) != VCC3_ERR_NONE )
		return( nErrorCode );

	if ( (nErrorCode = DoExposureGetRef( lpVCC3, &wAE )) != VCC3_ERR_NONE )
		return( nErrorCode );

	if ( (nErrorCode = DoPanTiltRead( lpVCC3, &wPan, &wTilt )) != VCC3_ERR_NONE )
		return( nErrorCode );

	if ( (nErrorCode = DoPresetWrite( lpVCC3, wPosition, wAE, wPan, wTilt, wZoom )) != VCC3_ERR_NONE )
		return( nErrorCode );

	return( nErrorCode );
}

/**********************************************************************

	Preset Request

**********************************************************************/

int	DoPresetMove( LPVCC3INFO lpVCC3, WORD wPosition )
{
	int		nErrorCode;
	WORD	wAE, wPan, wTilt, wZoom;

	if ( (nErrorCode = DoPresetRead( lpVCC3, wPosition, &wAE, &wPan, &wTilt, &wZoom )) == VCC3_ERR_NONE )
	if ( (nErrorCode = DoPanTiltWrite( lpVCC3, wPan, wTilt )) == VCC3_ERR_NONE )
	if ( (nErrorCode = DoZoomWrite( lpVCC3, wZoom )) == VCC3_ERR_NONE )
	if ( (nErrorCode = DoExposureSetRef( lpVCC3, wAE )) == VCC3_ERR_NONE )
		;

	return( nErrorCode );
}

/**********************************************************************

	Focus Request

**********************************************************************/

int	DoFocusAuto( LPVCC3INFO lpVCC3 )
{
	BYTE	cmd[8];

	cmd[0] = 5;	// length
	cmd[1] = VCC3_CAMERAHEAD_FRAME;
	cmd[2] = VCC3_FOCUS_REQUEST;
	cmd[3] = 0x01;
	cmd[4] = 0x00;	// AF

	return VCC3_Command( lpVCC3, cmd, NULL, NULL );
}

/**********************************************************************

	Focus Request

**********************************************************************/

int	DoManualFocus( LPVCC3INFO lpVCC3 )
{
	BYTE	cmd[8];

	cmd[0] = 5;	// length
	cmd[1] = VCC3_CAMERAHEAD_FRAME;
	cmd[2] = VCC3_FOCUS_REQUEST;
	cmd[3] = 0x01;
	cmd[4] = 0x01;	// MF

	return VCC3_Command( lpVCC3, cmd, NULL, NULL );
}

/**********************************************************************

	Focus Request

**********************************************************************/

int	DoFocusNear( LPVCC3INFO lpVCC3 )
{
	BYTE	cmd[8];

	cmd[0] = 5;	// length
	cmd[1] = VCC3_CAMERAHEAD_FRAME;
	cmd[2] = VCC3_FOCUS_REQUEST;
	cmd[3] = 0x02;	// MF Start
	cmd[4] = 0x01;	// NEAR

	return VCC3_Command( lpVCC3, cmd, NULL, NULL );
}

/**********************************************************************

	Focus Request

**********************************************************************/

int	DoFocusFar( LPVCC3INFO lpVCC3 )
{
	BYTE	cmd[8];

	cmd[0] = 5;	// length
	cmd[1] = VCC3_CAMERAHEAD_FRAME;
	cmd[2] = VCC3_FOCUS_REQUEST;
	cmd[3] = 0x02;	// MF Start
	cmd[4] = 0x00;	// FAR

	return VCC3_Command( lpVCC3, cmd, NULL, NULL );
}

/**********************************************************************

	Focus Request

**********************************************************************/

int	DoFocusStop( LPVCC3INFO lpVCC3 )
{
	BYTE	cmd[8];

	cmd[0] = 4;	// length
	cmd[1] = VCC3_CAMERAHEAD_FRAME;
	cmd[2] = VCC3_FOCUS_REQUEST;
	cmd[3] = 0x04;

	return VCC3_Command( lpVCC3, cmd, NULL, NULL );
}

/**********************************************************************

	Zoom Request

**********************************************************************/

int	DoZoomTele( LPVCC3INFO lpVCC3 )
{
	BYTE	cmd[8];

	cmd[0] = 5;	// length
	cmd[1] = VCC3_CAMERAHEAD_FRAME;
	cmd[2] = VCC3_ZOOM_REQUEST;
	cmd[3] = 0x01;	// Start
	cmd[4] = 0x00;	// Tele

	return VCC3_Command( lpVCC3, cmd, NULL, NULL );
}

/**********************************************************************

	Zoom Request

**********************************************************************/

int	DoZoomWide( LPVCC3INFO lpVCC3 )
{
	BYTE	cmd[8];

	cmd[0] = 5;	// length
	cmd[1] = VCC3_CAMERAHEAD_FRAME;
	cmd[2] = VCC3_ZOOM_REQUEST;
	cmd[3] = 0x01;	// Start
	cmd[4] = 0x01;	// Tele

	return VCC3_Command( lpVCC3, cmd, NULL, NULL );
}

/**********************************************************************

	Zoom Request

**********************************************************************/

int	DoZoomStop( LPVCC3INFO lpVCC3 )
{
	BYTE	cmd[8];

	cmd[0] = 5;	// length
	cmd[1] = VCC3_CAMERAHEAD_FRAME;
	cmd[2] = VCC3_ZOOM_REQUEST;
	cmd[3] = 0x03;	// Stop
	cmd[4] = 0x00;	// n/a

	return VCC3_Command( lpVCC3, cmd, NULL, NULL );
}

/**********************************************************************

	Zoom Request

**********************************************************************/

int	DoZoomRead( LPVCC3INFO lpVCC3, LPWORD lpwZoom )
{
	int	iLen = 0;
	BYTE	cmd[8];
	int	nRetCode;
	LPWORD	lpwParam;

	cmd[0] = 4;	// length
	cmd[1] = VCC3_CAMERAHEAD_FRAME;
	cmd[2] = VCC3_STATE_REQUEST;
	cmd[3] = VCC3_STATE_ZOOM;
	nRetCode = VCC3_Command( lpVCC3, cmd, lpVCC3->response, &iLen );

	if ( nRetCode != VCC3_ERR_NONE )
		return nRetCode;

	if ( iLen != 8 )
		return VCC3_ERR_LENGTH;

	lpwParam = (LPWORD)(lpVCC3->response + 5);
	*lpwZoom = SWAPWORD(lpwParam[0]);	// ZOOM

	return nRetCode;
}

/**********************************************************************

	Zoom Request

**********************************************************************/

int	DoZoomWrite( LPVCC3INFO lpVCC3, WORD wZoom )
{
	BYTE	cmd[16];
	LPWORD	lpwParam;

	cmd[0] = 7;	// length
	cmd[1] = VCC3_CAMERAHEAD_FRAME;
	cmd[2] = VCC3_ZOOM_REQUEST;
	cmd[3] = 0x02;	// Position Specification
	cmd[4] = 0x02;	// Set (write)

	lpwParam = (LPWORD)(cmd + 5);
	lpwParam[0] = SWAPWORD(wZoom);

	return VCC3_Command( lpVCC3, cmd, NULL, NULL );
}

/**********************************************************************

	Exposure Request

**********************************************************************/

int	DoExposureAE( LPVCC3INFO lpVCC3, BOOL fEnable )
{
	BYTE	cmd[8];

	cmd[0] = 5;	// length
	cmd[1] = VCC3_CAMERAHEAD_FRAME;
	cmd[2] = VCC3_EXPOSURE_REQUEST;
	cmd[3] = 0x01;	// Exposure Mode
			// 0=AE mode, 1=Manual Mode
	cmd[4] = (BYTE) fEnable ? 0x00 : 0x01;

	return VCC3_Command( lpVCC3, cmd, NULL, NULL );
}

/**********************************************************************

	Exposure Request

**********************************************************************/

int	DoExposureAEType( LPVCC3INFO lpVCC3, int iType, int iParam )
{
	BYTE	cmd[8];

	cmd[0] = 5;	// length
	cmd[1] = VCC3_CAMERAHEAD_FRAME;
	cmd[2] = VCC3_EXPOSURE_REQUEST;
	cmd[3] = 0x02;	// type
	cmd[4] = iType;	// 0=full auto, 1=shutter priority, 2=aperture priority

	if ( iType != VCC3_EXPOSURE_FULL )
	{
		cmd[0] = 6;
		cmd[5] = (BYTE) iParam;
	}

	return VCC3_Command( lpVCC3, cmd, NULL, NULL );
}

/**********************************************************************

	Exposure Request

**********************************************************************/

int	DoExposureAELock( LPVCC3INFO lpVCC3, BOOL fEnable )
{
	BYTE	cmd[8];

	cmd[0] = 5;	// length
	cmd[1] = VCC3_CAMERAHEAD_FRAME;
	cmd[2] = VCC3_EXPOSURE_REQUEST;
	cmd[3] = 0x03;	// Exposure Lock
	cmd[4] = (BYTE) fEnable;

	return VCC3_Command( lpVCC3, cmd, NULL, NULL );
}

/**********************************************************************

	Exposure Request

**********************************************************************/

int	DoExposureSetRef( LPVCC3INFO lpVCC3, WORD wRef )
{
	BYTE	cmd[8];

	cmd[0] = 5;	// length
	cmd[1] = VCC3_CAMERAHEAD_FRAME;
	cmd[2] = VCC3_EXPOSURE_REQUEST;
	cmd[3] = 0x04;	// AE Reference Correction
	cmd[4] = (BYTE) wRef;

	return VCC3_Command( lpVCC3, cmd, NULL, NULL );
}

/**********************************************************************

	Exposure Request

**********************************************************************/

int	DoExposureGetRef( LPVCC3INFO lpVCC3, LPWORD lpwRef )
{
	int	iLen;
	int	nRetCode;
	BYTE	cmd[8];

	cmd[0] = 4;	// length
	cmd[1] = VCC3_CAMERAHEAD_FRAME;
	cmd[2] = VCC3_STATE_REQUEST;
	cmd[3] = VCC3_STATE_EXPOSURE;

	nRetCode = VCC3_Command( lpVCC3, cmd, lpVCC3->response, &iLen );

	if ( nRetCode != VCC3_ERR_NONE )
		return nRetCode;

	if ( iLen != 10 )
		return VCC3_ERR_LENGTH;

	*lpwRef = lpVCC3->response[5];	// AE reference

	return nRetCode;
}

/**********************************************************************

	Home Request

**********************************************************************/

int	DoHome( LPVCC3INFO lpVCC3 )
{
	BYTE	cmd[8];

	cmd[0] = 3;	// length
	cmd[1] = VCC3_PANTILTER_FRAME;
	cmd[2] = VCC3_HOME_REQUEST;

	return VCC3_Command( lpVCC3, cmd, NULL, NULL );
}

/**********************************************************************

	PanTilt Request

**********************************************************************/

int	DoPanLeft( LPVCC3INFO lpVCC3 )
{
	BYTE	cmd[16];

	cmd[0] = 6;	// length
	cmd[1] = VCC3_PANTILTER_FRAME;
	cmd[2] = VCC3_PANTILT_REQUEST;
	cmd[3] = 0x01;	// Start
	cmd[4] = 0x02;	// PanLeft
	cmd[5] = 0x00;	// Tilt Fixed

	return VCC3_Command( lpVCC3, cmd, NULL, NULL );
}

/**********************************************************************

	PanTilt Request

**********************************************************************/

int	DoPanRight( LPVCC3INFO lpVCC3 )
{
	BYTE	cmd[16];

	cmd[0] = 6;	// length
	cmd[1] = VCC3_PANTILTER_FRAME;
	cmd[2] = VCC3_PANTILT_REQUEST;
	cmd[3] = 0x01;	// Start
	cmd[4] = 0x01;	// PanLeft
	cmd[5] = 0x00;	// Tilt Fixed

	return VCC3_Command( lpVCC3, cmd, NULL, NULL );
}

/**********************************************************************

	PanTilt Request

**********************************************************************/

int	DoTiltUp( LPVCC3INFO lpVCC3 )
{
	BYTE	cmd[16];

	cmd[0] = 6;	// length
	cmd[1] = VCC3_PANTILTER_FRAME;
	cmd[2] = VCC3_PANTILT_REQUEST;
	cmd[3] = 0x01;	// Start
	cmd[4] = 0x00;	// PanFixed
	cmd[5] = 0x01;	// TiltUp

	return VCC3_Command( lpVCC3, cmd, NULL, NULL );
}

/**********************************************************************

	PanTilt Request

**********************************************************************/

int	DoTiltDown( LPVCC3INFO lpVCC3 )
{
	BYTE	cmd[16];

	cmd[0] = 6;	// length
	cmd[1] = VCC3_PANTILTER_FRAME;
	cmd[2] = VCC3_PANTILT_REQUEST;
	cmd[3] = 0x01;	// Start
	cmd[4] = 0x00;	// PanFixed
	cmd[5] = 0x02;	// TiltDown

	return VCC3_Command( lpVCC3, cmd, NULL, NULL );
}

/**********************************************************************

	PanTilt Request

**********************************************************************/

int	DoPanLeftTiltUp( LPVCC3INFO lpVCC3 )
{
	BYTE	cmd[16];

	cmd[0] = 6;	// length
	cmd[1] = VCC3_PANTILTER_FRAME;
	cmd[2] = VCC3_PANTILT_REQUEST;
	cmd[3] = 0x01;	// Start
	cmd[4] = 0x02;	// PanLeft
	cmd[5] = 0x01;	// Tilt Up

	return VCC3_Command( lpVCC3, cmd, NULL, NULL );
}

/**********************************************************************

	PanTilt Request

**********************************************************************/

int	DoPanRightTiltUp( LPVCC3INFO lpVCC3 )
{
	BYTE	cmd[16];

	cmd[0] = 6;	// length
	cmd[1] = VCC3_PANTILTER_FRAME;
	cmd[2] = VCC3_PANTILT_REQUEST;
	cmd[3] = 0x01;	// Start
	cmd[4] = 0x01;	// PanLeft
	cmd[5] = 0x01;	// Tilt Up

	return VCC3_Command( lpVCC3, cmd, NULL, NULL );
}

/**********************************************************************

	PanTilt Request

**********************************************************************/

int	DoPanLeftTiltDown( LPVCC3INFO lpVCC3 )
{
	BYTE	cmd[16];

	cmd[0] = 6;	// length
	cmd[1] = VCC3_PANTILTER_FRAME;
	cmd[2] = VCC3_PANTILT_REQUEST;
	cmd[3] = 0x01;	// Start
	cmd[4] = 0x02;	// PanLeft
	cmd[5] = 0x02;	// TiltDown

	return VCC3_Command( lpVCC3, cmd, NULL, NULL );
}

/**********************************************************************

	PanTilt Request

**********************************************************************/

int	DoPanRightTiltDown( LPVCC3INFO lpVCC3 )
{
	BYTE	cmd[16];

	cmd[0] = 6;	// length
	cmd[1] = VCC3_PANTILTER_FRAME;
	cmd[2] = VCC3_PANTILT_REQUEST;
	cmd[3] = 0x01;	// Start
	cmd[4] = 0x01;	// PanRight
	cmd[5] = 0x02;	// TiltDown

	return VCC3_Command( lpVCC3, cmd, NULL, NULL );
}

/**********************************************************************

	PanTilt Request

**********************************************************************/

int	DoPanTiltStop( LPVCC3INFO lpVCC3 )
{
	BYTE	cmd[16];

	cmd[0] = 4;	// length
	cmd[1] = VCC3_PANTILTER_FRAME;
	cmd[2] = VCC3_PANTILT_REQUEST;
	cmd[3] = 0x02;	// Stop

	return VCC3_Command( lpVCC3, cmd, NULL, NULL );
}

/**********************************************************************

	PanTilt Request

**********************************************************************/

int	DoPanTiltRead( LPVCC3INFO lpVCC3, LPWORD lpwPan, LPWORD lpwTilt )
{
	int	iLen;
	int	nRetCode;
	BYTE	cmd[8];
	LPWORD	lpwParam;

	cmd[0] = 4;	// length
	cmd[1] = VCC3_PANTILTER_FRAME;
	cmd[2] = VCC3_STATE_REQUEST;
	cmd[3] = VCC3_STATE_PANTILT;	// Pan/Tilt

	nRetCode = VCC3_Command( lpVCC3, cmd, lpVCC3->response, &iLen );

	if ( nRetCode != VCC3_ERR_NONE )
		return nRetCode;

	if ( iLen != 11 )
		return VCC3_ERR_LENGTH;

	lpwParam = (LPWORD)(lpVCC3->response + 5);
	*lpwPan = SWAPWORD(lpwParam[0]);

	lpwParam = (LPWORD)(lpVCC3->response + 8);
	*lpwTilt = SWAPWORD(lpwParam[0]);

	return nRetCode;
}

/**********************************************************************

	PanTilt Request

**********************************************************************/

int	DoPanTiltWrite( LPVCC3INFO lpVCC3, WORD wPan, WORD wTilt )
{
	BYTE	cmd[16];
	LPWORD	lpwParam;

	cmd[0] = 9;	// length
	cmd[1] = VCC3_PANTILTER_FRAME;
	cmd[2] = VCC3_PANTILT_REQUEST;
	cmd[3] = 0x05;	// Absolute Position
	cmd[4] = 0x02;	// Write

	lpwParam = (LPWORD)(cmd + 5);
	lpwParam[0] = SWAPWORD(wPan);
	lpwParam[1] = SWAPWORD(wTilt);

	return VCC3_Command( lpVCC3, cmd, NULL, NULL );
}

/**********************************************************************

	PanTilt Request

	iSpeed	1-80 (deg/sec)

**********************************************************************/

int	DoPanTiltSpeed( LPVCC3INFO lpVCC3, int iPanSpeed, int iTiltSpeed )
{
	BYTE	cmd[16];

	cmd[0] = 7;	// length
	cmd[1] = VCC3_PANTILTER_FRAME;
	cmd[2] = VCC3_PANTILT_REQUEST;
	cmd[3] = 0x03;	// Speed
	cmd[4] = 0x02;	// Write
	cmd[5] = (BYTE)iPanSpeed;
	cmd[6] = (BYTE)iTiltSpeed;

	return VCC3_Command( lpVCC3, cmd, NULL, NULL );
}

/* end of file : command.c */
