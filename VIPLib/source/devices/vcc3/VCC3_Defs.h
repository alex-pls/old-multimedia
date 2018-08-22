/***************************************************************************

	FILE:		vcc3.h

	AUTHOR:		Eric Chasanoff

	REVISIONS:	05.01.97	Written

	DESCRIPTION:
		
		  Windows '95 32 bit VC-C3 driver definitions

	DISCLAIMER:

		Raster Builders Inc. and Eric Chasanoff make no representations
		about the correctness or suitability of this software for
		any purpose. It is provided without express or implied
		warranty.

***************************************************************************/

#ifndef _VCC3_DEFINED_
#define _VCC3_DEFINED_

//#define	VCC3_LIBNAME	"VCC3.DLL"

// --------------------------------------
//	Driver control structure
// --------------------------------------

typedef struct tagVCC3INFO
{
	HANDLE		hComm;
	BOOL		fConnected;

	OVERLAPPED	osWrite;
	OVERLAPPED	osRead;
	HANDLE		hEventThread;
	DWORD		dwThreadID;

	HWND		hWndNotify;
	UINT		uMsgNotify;
	BOOL		fRecvBusy;

	int			nErrorCode;
	int			nRespErrorCode;

	BYTE		response[256];
	BYTE		notify[256];

} VCC3INFO, * LPVCC3INFO;

// --------------------------------------------
//	Error codes
// --------------------------------------------

// nErrorCode constants
#define	VCC3_ERR_NONE						(0)
#define	VCC3_ERR_FORMAT						(-1)
#define	VCC3_ERR_CREATE						(-2)
#define	VCC3_ERR_SET						(-3)
#define	VCC3_ERR_PARAM						(-4)
#define	VCC3_ERR_MEMORY						(-5)
#define	VCC3_ERR_NAK						(-6)
#define	VCC3_ERR_LENGTH						(-7)
#define	VCC3_ERR_CABLE						(-8)
#define	VCC3_ERR_RECV_TMO					(-9)
#define	VCC3_ERR_RECV_IO					(-10)
#define	VCC3_ERR_SEND_IO					(-11)
#define	VCC3_ERR_UNKNOWN					(-12)

// nRespErrorCode constants
#define	VCC3_NAK_ERR_BUFFERBUSY				(-100)
#define	VCC3_NAK_ERR_LENGTH					(-101)
#define	VCC3_NAK_ERR_SEQUENCE				(-102)
#define	VCC3_NAK_ERR_COMMUNICATIONS			(-103)
#define	VCC3_NAK_ERR_CHECKSUM				(-104)
#define	VCC3_NAK_ERR_UNKNOWN				(-105)

#define	VCC3_RESP_ERR_CABLE					(-200)
#define	VCC3_RESP_ERR_CAMERA_COMM			(-201)
#define	VCC3_RESP_ERR_PANTILTER_NAK			(-202)
#define	VCC3_RESP_ERR_PANTILTER_TMO			(-203)
#define	VCC3_RESP_ERR_PANTILTER_CHECKSUM	(-204)
#define	VCC3_RESP_ERR_PANTILTER_UNKNOWN		(-205)
#define	VCC3_RESP_ERR_VIDEOADAPTER_NAK		(-206)
#define	VCC3_RESP_ERR_VIDEOADAPTER_TMO		(-207)
#define	VCC3_RESP_ERR_VIDEOADAPTER_CHECKSUM	(-208)
#define	VCC3_RESP_ERR_VIDEOADAPTER_UNKNOWN	(-209)
#define	VCC3_RESP_ERR_UNCONNECTED			(-210)
#define	VCC3_RESP_ERR_UNDEFINED_COMMAND		(-211)
#define	VCC3_RESP_ERR_UNDEFINED_PARAMETER	(-212)
#define	VCC3_RESP_ERR_COMMAND_STATUS		(-213)
#define	VCC3_RESP_ERR_PARAMETER_STATUS		(-214)
#define	VCC3_RESP_ERR_TIMEOUT				(-215)
#define	VCC3_RESP_ERR_WHITEBALANCE			(-216)
#define	VCC3_RESP_ERR_ADJUSTMENT			(-217)
#define	VCC3_RESP_ERR_UNKNOWN				(-218)

// ------------------------------------------
//	VC-C3 general definitions
// ------------------------------------------

#define	VCC3_MSG_CTSLO			100		// NOTIFY Messages
#define	VCC3_MSG_CTSHI			102
#define	VCC3_MSG_RECV			104

#define	MIN_VCC3_MSGLEN			3		// Message dimensions
#define	MAX_VCC3_MSGLEN			32

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



// ------------------------------------------
//	VC-C3 Modules
// ------------------------------------------

#define	VCC3_FRAME_MASK			0x0F

#define	VCC3_CAMERAHEAD_FRAME	1
#define	VCC3_PANTILTER_FRAME	5
#define	VCC3_VIDEOADAPTER_FRAME	8

// ------------------------------------------
//	Command codes
// ------------------------------------------

#define	VCC3_COMMAND_MASK		0x1F

// General
#define	VCC3_STATE_REQUEST		0x04
#define	VCC3_ERROR_NOTIFY		0x03
#define	VCC3_DISPLAY_NOTIFY		0x0F

// Video Adapter
#define	VCC3_END_REQUEST		0x01
#define	VCC3_WHITEBALANCE_REQUEST	0x10
#define	VCC3_FADE_REQUEST		0x11
#define	VCC3_MUTE_REQUEST		0x12
#define	VCC3_MODESELECT_REQUEST	0x17
#define	VCC3_PRESET_REQUEST		0x18

// Camera Head
#define	VCC3_FOCUS_REQUEST		0x10
#define	VCC3_FOCUS_NOTIFY		0x11
#define	VCC3_ZOOM_REQUEST		0x12
#define	VCC3_ZOOM_NOTIFY		0x13
#define	VCC3_EXPOSURE_REQUEST	0x14
#define	VCC3_SWITCH_NOTIFY		0x18

// Pan Tilter
#define	VCC3_INIT_REQUEST		0x00
#define	VCC3_MEMORY_REQUEST		0x07
#define	VCC3_SETUP_REQUEST		0x10
#define	VCC3_HOME_REQUEST		0x11
#define	VCC3_PANTILT_REQUEST	0x12
#define	VCC3_LIMIT_NOTIFY		0x16
#define	VCC3_REMOTE_REQUEST		0x17
#define	VCC3_REMOTE_NOTIFY		0x18
#define	VCC3_LED_REQUEST		0x19
#define	VCC3_POWER_NOTIFY		0x1B

// ------------------------------------------
//	STATE types
// ------------------------------------------

#define	VCC3_STATE_SYSTEM		0

// Video Adapter
#define	VCC3_STATE_WHITEBALANCE	1
#define	VCC3_STATE_FADE			2
#define	VCC3_STATE_VASWITCH		3

// CameraHead
#define	VCC3_STATE_FOCUS		1
#define	VCC3_STATE_ZOOM			2
#define	VCC3_STATE_EXPOSURE		3
#define	VCC3_STATE_PP			4

// PanTilter
#define	VCC3_STATE_PTSWITCH		1
#define	VCC3_STATE_PANTILT		2
#define	VCC3_STATE_REMOTEID		3
	
// ----------------------------------------
//	VCC Function Parameter definitions
// ----------------------------------------

// VCC3_ExposureAEType
#define	VCC3_EXPOSURE_FULL		0x00
#define	VCC3_EXPOSURE_SHUTTER	0x01
#define	VCC3_EXPOSURE_APERTURE	0x02

// Remote control brightness constants
#define	VCC3_AE_NORMAL			0x48
#define	VCC3_AE_MEDIUM			0x60
#define	VCC3_AE_BRIGHT			0x90

// VCC3_MODESELECT_REQUEST parameters
#define	VCC3_HOST_ENABLE		0x00
#define	VCC3_HOST_DISABLE		0x01

// ----------------------------------------
//	Remote control notification codes
// ----------------------------------------

#define	VCC3_REMOTE_AUTO		0x70
#define	VCC3_REMOTE_MANUAL		0x00
#define	VCC3_REMOTE_NEAR		0x80
#define	VCC3_REMOTE_FAR			0x90
#define	VCC3_REMOTE_WIDE		0xA0
#define	VCC3_REMOTE_ID			0x11
#define	VCC3_REMOTE_LEFT		0xE0
#define	VCC3_REMOTE_PRESET		0x51
#define	VCC3_REMOTE_1			0x10
#define	VCC3_REMOTE_2			0x20
#define	VCC3_REMOTE_3			0x30
#define	VCC3_REMOTE_UP			0xC0
#define	VCC3_REMOTE_HOME		0x01
#define	VCC3_REMOTE_DOWN		0xD0
#define	VCC3_REMOTE_OPERATE		0x41
#define	VCC3_REMOTE_4			0x40
#define	VCC3_REMOTE_5			0x50
#define	VCC3_REMOTE_6			0x60
#define	VCC3_REMOTE_TELE		0xB0
#define	VCC3_REMOTE_BRIGHTNESS	0x91
#define	VCC3_REMOTE_RIGHT		0xF0
#define	VCC3_REMOTE_OPTION		0xA1


// --------------------------------------------
//	Forward declarations
// --------------------------------------------

#define	DllExport	__declspec( dllexport )

DllExport int WINAPI	VCC3_Open( LPVCC3INFO lpVCC3, HWND hWndNotify, UINT uMsgNotify, int iPort, int iBaud );
DllExport int WINAPI	VCC3_Close( LPVCC3INFO lpVCC3 );

DllExport int WINAPI	VCC3_Send( LPVCC3INFO lpVCC3, LPBYTE lpCmd );
DllExport int WINAPI	VCC3_Recv( LPVCC3INFO lpVCC3, LPBYTE lpResp, LPINT lpiRespLen, DWORD dwTimeout );
DllExport int WINAPI	VCC3_Command( LPVCC3INFO lpVCC3, LPBYTE lpCmd, LPBYTE lpResp, LPINT lpiRespLen );
DllExport int WINAPI	VCC3_RecvCount( LPVCC3INFO lpVCC3 );

#endif

/* end of file : vcc3.h */
