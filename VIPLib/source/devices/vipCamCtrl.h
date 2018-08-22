/**
 *  @class   vipCamCtrl
 *
 *  @brief   Base interface for all Camera drivers, it will control classic
 *           camera movements (Pan, Tilt, Zoom) and some common settings.
 *
 *  @bug
 *  @warning
 *  @todo
 *
 *  @see
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

#ifndef __VIPLIB_VIPCAMCONTROL_H__
 #define __VIPLIB_VIPCAMCONTROL_H__


// typedef
struct cPos
{
	int X;
	int Y;
};


struct cSize
{
	int Height;
	int Width;
};

struct cPTZ		// range is defined by the implementation !
{
	int Pan;	// 0 center (home); <0 left; >0 right;
	int Tilt;	// 0 center (home); <0 down; >0 up;
	int Zoom;	// 0 default; usually zoom out = 0, > 0 zoom in
};

struct cPTZS
{
	double Pan;		// 0 SLOW ; 1 FAST
	double Tilt;	// 0 SLOW ; 1 FAST
	double Zoom;	// 0 SLOW ; 1 FAST
};


// ------------------------------------------
//	VCC3_Open Parameters
// ------------------------------------------

#define	VCC3_COM1				0
#define	VCC3_COM2				1
#define	VCC3_COM3				2
#define	VCC3_COM4				3

#define	VCC3_BAUD4800			4800
#define	VCC3_BAUD9600			9600
#define	VCC3_BAUD14400			14400

#define	DEFAULT_PORT	VCC3_COM1
#define	DEFAULT_BAUD	VCC3_BAUD9600


class vipCamCtrl
{
	protected:

		/**
		 * @var   current Serial Port
		 */
		int	iCommPort;

		/**
		 * @var   current Baudb Rate
		 */
		int	iCommBaud;

		/**
		 * @var   flag, true when driver has been initialized
		 */
		bool fDriverInit;


	public:

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////// INITIALIZATION

		virtual void Connect(	int port = DEFAULT_PORT,
								int baud = DEFAULT_BAUD		) = 0;

		virtual void Disconnect() = 0;

		virtual bool Reset() = 0;



		virtual bool isConnected( ) = 0;


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////// CONTROLS

		virtual int setPTZ(cPTZ& value) = 0;



////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////// PAN & TILT RELATED CALLS

		virtual int Home() = 0;

		virtual int PanRight() = 0;
		virtual int PanLeft() = 0;

		virtual int TiltUp() = 0;
		virtual int TiltDown() = 0;

		virtual int Stop() = 0;

		virtual int getPos(int& pan, int& tilt) = 0;
		virtual int setPos(int& pan, int& tilt) = 0;

		virtual void getPosPanRange( int& min, int& max ) = 0;
		virtual void getPosTiltRange( int& min, int& max ) = 0;



////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////// FOCUS RELATED CALLS

		virtual int	FocusAuto( ) = 0;
		virtual int	FocusNear( ) = 0;
		virtual int	FocusFar( ) = 0;
		virtual int	FocusStop( ) = 0;

		virtual int getFocusDelay( ) = 0;// MILLISECONDS



////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////// ZOOM RELATED CALLS

		virtual int	ZoomIn( ) = 0;
		virtual int	ZoomOut( ) = 0;
		virtual int	ZoomStop( ) = 0;

		virtual int	setZoom( int& value ) = 0;
		virtual int getZoom( int& value ) = 0;
		virtual void getZoomRange( int& min, int& max ) = 0;



////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////// VARIOUS

		virtual const char* getDriverName() = 0;
		virtual const char* getDriverVer() = 0;



};

#endif //__VIPLIB_VIPCAMCONTROL_H__

