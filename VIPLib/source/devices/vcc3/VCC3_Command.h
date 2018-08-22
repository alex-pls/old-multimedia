/***************************************************************************

	FILE:		command.h

	AUTHOR:		Eric Chasanoff

	REVISIONS:	05.01.97	Written

	DESCRIPTION:
		
		  The file contains example VC-C3 command definitions

	DISCLAIMER:

		Raster Builders Inc. and Eric Chasanoff make no representations
		about the correctness or suitability of this software for
		any purpose. It is provided without express or implied
		warranty.

***************************************************************************/

#ifndef _COMMAND_DEFINED_
#define _COMMAND_DEFINED_

int	DoModeSelect( LPVCC3INFO lpVCC3, int iMode );
int	DoMuteVideo( LPVCC3INFO lpVCC3, BOOL fEnable );

int	DoPresetRead( LPVCC3INFO lpVCC3, WORD wPosition, LPWORD lpwAE, 
		LPWORD lpwPan, LPWORD lpwTilt, LPWORD lpwZoom );
int	DoPresetWrite( LPVCC3INFO lpVCC3, WORD wPosition, WORD wAE, 
		WORD wPan, WORD wTilt, WORD wZoom );
int	DoPresetSet( LPVCC3INFO lpVCC3, WORD wPosition );
int	DoPresetMove( LPVCC3INFO lpVCC3, WORD wPosition );

int	DoFocusAuto( LPVCC3INFO lpVCC3 );
int	DoManualFocus( LPVCC3INFO lpVCC3 );
int	DoFocusNear( LPVCC3INFO lpVCC3 );
int	DoFocusFar( LPVCC3INFO lpVCC3 );
int	DoFocusStop( LPVCC3INFO lpVCC3 );

int	DoZoomTele( LPVCC3INFO lpVCC3 );
int	DoZoomWide( LPVCC3INFO lpVCC3 );
int	DoZoomStop( LPVCC3INFO lpVCC3 );
int	DoZoomRead( LPVCC3INFO lpVCC3, LPWORD lpwZoom );
int	DoZoomWrite( LPVCC3INFO lpVCC3, WORD wZoom );

int	DoExposureAE( LPVCC3INFO lpVCC3, BOOL fEnable );
int	DoExposureAEType( LPVCC3INFO lpVCC3, int iMode, int iParam );
int	DoExposureAELock( LPVCC3INFO lpVCC3, BOOL fEnable );
int	DoExposureSetRef( LPVCC3INFO lpVCC3, WORD wRef );
int	DoExposureGetRef( LPVCC3INFO lpVCC3, LPWORD lpwRef );

int	DoHome( LPVCC3INFO lpVCC3 );
int	DoPanLeft( LPVCC3INFO lpVCC3 );
int	DoPanRight( LPVCC3INFO lpVCC3 );
int	DoTiltUp( LPVCC3INFO lpVCC3 );
int	DoTiltDown( LPVCC3INFO lpVCC3 );
int	DoPanTiltStop( LPVCC3INFO lpVCC3 );
int	DoPanLeftTiltUp( LPVCC3INFO lpVCC3 );
int	DoPanRightTiltUp( LPVCC3INFO lpVCC3 );
int	DoPanLeftTiltDown( LPVCC3INFO lpVCC3 );
int	DoPanRightTiltDown( LPVCC3INFO lpVCC3 );
int	DoPanTiltSpeed( LPVCC3INFO lpVCC3, int iPanSpeed, int iTiltSpeed );
int	DoPanTiltRead( LPVCC3INFO lpVCC3, LPWORD lpwPan, LPWORD lpwTilt );
int	DoPanTiltWrite( LPVCC3INFO lpVCC3, WORD wPan, WORD wTilt );

#endif

/* end of file : command.h */
