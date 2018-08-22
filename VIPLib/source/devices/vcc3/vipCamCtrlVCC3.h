/**
 *  @class   vipCamCtrlVCC3
 *
 *  @brief   vipCamCtrl implementation for Sony VCC3 Camera, based on
 *           VC-C3 SDK by Eric Chasanoff
 *
 *  @bug
 *  @warning WINDOWS32 ONLY
 *  @todo
 *
 *  @see
 *
 *  @example
 *
 *  @version 1.0.0
 *  @date    2007-10-08
 *  @author  Alessandro Polo
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

#ifndef __VIPLIB_VIPCAMCONTROL_VCC3_H__
 #define __VIPLIB_VIPCAMCONTROL_VCC3_H__

#include "../vipCamCtrl.h"

#include <windows.h>

#include "VCC3_Defs.h"


#define	_VCC3_DRIVER_NAME	"VCC3"
#define	_VCC3_DRIVER_VER	"1.0"
#define	_VCC3_FOCUS_DELAY	10 // MILLISECONDS



class vipCamCtrlVCC3 : public vipCamCtrl
{
	protected:

		HWND hWndApp;			// for ErrorMessage

		VCC3INFO		vcc3Info;				// Driver control structure

		bool fPreset;		// Preset button state
		bool fOperate;		// Operate Button state
		char *szAppName;


	public:

		vipCamCtrlVCC3();
		~vipCamCtrlVCC3();

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////// INITIALIZATION

		virtual void Init( HWND hWnd );

		void Connect(int port = DEFAULT_PORT, int baud = DEFAULT_BAUD);
		void Disconnect();
		bool Reset();

		bool isConnected( ) { return fDriverInit; };

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////// CONTROLS

		int setPTZ(cPTZ& value);


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////// PAN & TILT RELATED CALLS


	int Home();

	int PanRight();
	int PanLeft();

	int TiltUp();
	int TiltDown();

	int Stop();

	int getPos(int& pan, int& tilt);
	int setPos(int& pan, int& tilt);

	void getPosPanRange( int& min, int& max );
	void getPosTiltRange( int& min, int& max );

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////// FOCUS RELATED CALLS

	int	FocusAuto( );
	int	FocusNear( );
	int	FocusFar( );
	int	FocusStop( );
//int	DoManualFocus( LPVCC3INFO lpVCC3 );

	int getFocusDelay( ) { return _VCC3_FOCUS_DELAY; };// MILLISECONDS


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////// ZOOM RELATED CALLS


	inline int ZoomIn( );
	int	ZoomOut( );
	int	ZoomStop( );

	int	setZoom( int& value );
	int getZoom( int& value );
	void getZoomRange( int& min, int& max );

	//----------------------------

///////////// EXPOSURE RELATED CALLS (pag 46)
/*
	int	DoExposureAE( LPVCC3INFO lpVCC3, BOOL fEnable );
	int	DoExposureAEType( LPVCC3INFO lpVCC3, int iMode, int iParam );
	int	DoExposureAELock( LPVCC3INFO lpVCC3, BOOL fEnable );
	int	DoExposureSetRef( LPVCC3INFO lpVCC3, WORD wRef );
	int	DoExposureGetRef( LPVCC3INFO lpVCC3, LPWORD lpwRef );
*/
	//----------------------------

	const char* getDriverName() { return _VCC3_DRIVER_NAME; };
	const char* getDriverVer() { return _VCC3_DRIVER_VER; };

	//----------------------------

	void DisplayVCC3Error( int );

	void ErrorMessage( LPSTR fmt,... );
};


#endif //__VIPLIB_VIPCAMCONTROL_VCC3_H__
