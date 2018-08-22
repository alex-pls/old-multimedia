/***************************************************************************

	FILE:		vcc3.c

	AUTHOR:		Eric Chasanoff

	REVISIONS:	05.01.97	Written

				09.15.97

				1. Eliminated VCC3_BAUD19200.

				2. Added CloseHandle(os.hEvent) if SetCommMask() fails in
				   CommEventThread().

				3. Changed ComCount > 0 in CommEventThread().

				4. Added IdleWindows() to VCC3_Recv() and DelayMSecs().


	DESCRIPTION:

		  Windows '95 32-bit VC-C3 driver.

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

#define	EVENT_MASK			(EV_RXCHAR|EV_CTS)

#define	COMM_BYTE_TMO		500		// ms timeout for received characters
#define	COMM_RECV_TMO		3000	// ms timeout for response packet
#define	COMM_NOTIFY_TMO		1000	// ms timeout for notification packet
#define	COMM_CLOSE_DELAY	3000		// ms delay before closing driver

#define	COMM_QSIZE			1024	// transmit/receive queue size

// ------------------------------------------------------------
//	Forward Declarations
// ------------------------------------------------------------

DWORD	ComEventThread( LPSTR );

int		ComGetc( LPVCC3INFO, DWORD );
int		ComPutc( LPVCC3INFO, BYTE );
int		ComCount( LPVCC3INFO );
int		SendPacket( LPVCC3INFO, LPBYTE );
int		RecvPacket( LPVCC3INFO, LPBYTE, LPINT, DWORD );

int		TranslateResponseError( LPBYTE );

VOID	DelayMSecs( DWORD );
DWORD	ReadMSecs( VOID );
VOID	IdleWindows( VOID );

/***************************************************************************

	Initialize library

***************************************************************************/

DllExport int WINAPI	VCC3_Open( LPVCC3INFO lpVCC3, HWND hWndNotify,
								UINT uMsgNotify, int iPort, int iBaud )
{
	DCB				dcb;
	DWORD			dwStatus;
	COMMTIMEOUTS	CommTimeOuts;
	char			szPort[16];

	lpVCC3->fConnected			= FALSE;
	lpVCC3->nErrorCode			= VCC3_ERR_NONE;
	lpVCC3->nRespErrorCode		= VCC3_ERR_NONE;

	lpVCC3->hWndNotify			= hWndNotify;
	lpVCC3->uMsgNotify			= uMsgNotify;
	lpVCC3->fRecvBusy			= FALSE;

	lpVCC3->hComm				= NULL;
	lpVCC3->osWrite.Offset		= 0;
	lpVCC3->osWrite.OffsetHigh	= 0;
	lpVCC3->osRead.Offset		= 0;
	lpVCC3->osRead.OffsetHigh	= 0;

	lpVCC3->hEventThread		= NULL;
	lpVCC3->dwThreadID			= 0;

	switch( iPort )
	{
		case	VCC3_COM1:
		case	VCC3_COM2:
		case	VCC3_COM3:
		case	VCC3_COM4:
			break;

		default:
			return( lpVCC3->nErrorCode = VCC3_ERR_FORMAT );
	}

	wsprintf( szPort, "COM%d", iPort+1 );

	switch( iBaud )
	{
		case	VCC3_BAUD4800:
		case	VCC3_BAUD9600:
		case	VCC3_BAUD14400:
			break;

		default:
			return( lpVCC3->nErrorCode = VCC3_ERR_FORMAT );
	}

	// create I/O event used for overlapped reads / writes
	lpVCC3->osRead.hEvent = CreateEvent(
				NULL,	// no security
				TRUE,	// explicit reset req
				FALSE,	// initial event reset
				NULL ); // no name

	if ( lpVCC3->osRead.hEvent == NULL )
		return( lpVCC3->nErrorCode = VCC3_ERR_CREATE );

	lpVCC3->osWrite.hEvent = CreateEvent(
				NULL,	// no security
				TRUE,	// explicit reset req
				FALSE,	// initial event reset
				NULL ); // no name

	if ( lpVCC3->osWrite.hEvent == NULL )
	{
		CloseHandle( lpVCC3->osRead.hEvent );
		return( lpVCC3->nErrorCode = VCC3_ERR_CREATE );
	}

	lpVCC3->hComm = CreateFile(
			szPort,
			GENERIC_READ | GENERIC_WRITE,
			0,				// exclusive access
			NULL,			// no security attrs
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
			NULL );

	if ( lpVCC3->hComm == (HANDLE) -1 )
	{
		CloseHandle( lpVCC3->osRead.hEvent );
		CloseHandle( lpVCC3->osWrite.hEvent );
		return( lpVCC3->nErrorCode = VCC3_ERR_CREATE );
	}

	SetCommMask( lpVCC3->hComm, 0 );	// default

	SetupComm( lpVCC3->hComm, COMM_QSIZE, COMM_QSIZE );

	PurgeComm( lpVCC3->hComm, PURGE_TXABORT | PURGE_RXABORT |
			PURGE_TXCLEAR | PURGE_RXCLEAR );

	CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
	CommTimeOuts.ReadTotalTimeoutConstant = 1000;
	CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
	CommTimeOuts.WriteTotalTimeoutConstant = 1000;
	SetCommTimeouts( lpVCC3->hComm, &CommTimeOuts );

	dcb.DCBlength = sizeof( DCB );

	GetCommState( lpVCC3->hComm, &dcb );

	dcb.BaudRate = iBaud;
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;
	dcb.fBinary = TRUE;

	dcb.fOutxDsrFlow = 0;
	dcb.fDtrControl = DTR_CONTROL_DISABLE;
	dcb.fDsrSensitivity = 0;
	dcb.fOutX = dcb.fInX = 0;
	dcb.fErrorChar = 0;
	dcb.fRtsControl = RTS_CONTROL_HANDSHAKE;

	if ( !SetCommState( lpVCC3->hComm, &dcb ) )
	{
		CloseHandle( lpVCC3->osRead.hEvent );
		CloseHandle( lpVCC3->osWrite.hEvent );
		CloseHandle( lpVCC3->hComm );

		return( lpVCC3->nErrorCode = VCC3_ERR_SET );
	}

	lpVCC3->fConnected = TRUE;

	if ( (lpVCC3->hEventThread = CreateThread(
		(LPSECURITY_ATTRIBUTES) NULL,
		0,
		(LPTHREAD_START_ROUTINE) ComEventThread,
		(LPVOID) lpVCC3,
		0,
		&lpVCC3->dwThreadID )) == NULL )
	{
		lpVCC3->fConnected = FALSE;
		CloseHandle( lpVCC3->osRead.hEvent );
		CloseHandle( lpVCC3->osWrite.hEvent );
		CloseHandle( lpVCC3->hComm );

		return( lpVCC3->nErrorCode = VCC3_ERR_CREATE );
	}

	// Establish and verify handshakes
	EscapeCommFunction( lpVCC3->hComm, SETRTS );	// assert RTS

	GetCommModemStatus( lpVCC3->hComm, &dwStatus );

	if (( dwStatus & MS_CTS_ON ) != MS_CTS_ON )
	{
		EscapeCommFunction( lpVCC3->hComm, CLRRTS );
		CloseHandle( lpVCC3->osRead.hEvent );
		CloseHandle( lpVCC3->osWrite.hEvent );
		CloseHandle( lpVCC3->hComm );
		lpVCC3->fConnected = FALSE;

		return( lpVCC3->nErrorCode = VCC3_ERR_CABLE );
	}

	return( lpVCC3->nErrorCode = VCC3_ERR_NONE );
}

/***************************************************************************

	Close library

***************************************************************************/

DllExport int WINAPI	VCC3_Close( LPVCC3INFO lpVCC3 )
{
	if ( lpVCC3->fConnected )
	{
		// this busts us out of ComEventThread()

		lpVCC3->fConnected = FALSE;

		SetCommMask( lpVCC3->hComm, 0 );

		while ( lpVCC3->dwThreadID != 0 )
			;

		EscapeCommFunction( lpVCC3->hComm, CLRRTS );

		PurgeComm( lpVCC3->hComm, PURGE_TXABORT | PURGE_RXABORT |
			PURGE_TXCLEAR | PURGE_RXCLEAR );

		CloseHandle( lpVCC3->hComm );
		CloseHandle( lpVCC3->osRead.hEvent );
		CloseHandle( lpVCC3->osWrite.hEvent );
	}

	return( VCC3_ERR_NONE );
}

/******************************************************************************

	Return number of characters in receive queue.

******************************************************************************/

DllExport int WINAPI	VCC3_RecvCount( LPVCC3INFO lpVCC3 )
{
	return( (int) ComCount( lpVCC3 ) );
}

/***************************************************************************

	Send command - Wait for response

***************************************************************************/

DllExport int WINAPI VCC3_Command( LPVCC3INFO lpVCC3, LPBYTE lpCmd,
						LPBYTE lpResp, LPINT lpiRespLen )
{
	BOOL	fResp = FALSE;
	BOOL	fAck = FALSE;

	// ----------------------------------------------------------
	//	Disable rx event so we don't collide with ComEventThread
	// ----------------------------------------------------------

	SetCommMask( lpVCC3->hComm, EV_CTS );

	if ( lpiRespLen )
		*lpiRespLen = '\0';

	// ----------------------------------------------------------
	//	Send request
	// ----------------------------------------------------------

	if ( VCC3_Send( lpVCC3, lpCmd ) != VCC3_ERR_NONE )
		goto EndFunc;

	// ----------------------------------------------------------
	//	Loop until both ACK and RESPONSE packets are received.
	//	This routine does not assume any order although ACK
	//   seems to come first.
	// ----------------------------------------------------------

	for ( ;; )
	{
		int	iLen;

		// ---------------------------------------------------
		//	Wait for a complete packet
		// ---------------------------------------------------

		if ( VCC3_Recv( lpVCC3, lpVCC3->response, &iLen, COMM_RECV_TMO ) != VCC3_ERR_NONE )
			goto EndFunc;

		// ---------------------------------------------------
		//	Command may be echoed if no device is attached
		// ---------------------------------------------------

		if ( memcmp( lpCmd, lpVCC3->response, iLen ) == 0 )
			continue;

		// -----------------------------------------------
		// ACK response - NAK is trapped by VCC3_Recv
		// -----------------------------------------------

		if ( lpVCC3->response[1] & 0x80 )
		{
			fAck = TRUE;

			if ( fResp )
				goto EndFunc;
		}

		// ----------------------------------
		//	NOTIFY response
		// ----------------------------------
		else if ( lpVCC3->response[2] & 0x20 )
		{
			if ( lpVCC3->hWndNotify )
				SendMessage( lpVCC3->hWndNotify, lpVCC3->uMsgNotify, VCC3_MSG_RECV, (LPARAM)(LPSTR)lpVCC3->response );
		}

		// ----------------------------------
		//	NORMAL response
		// ----------------------------------

		else
		{
			fResp = TRUE;

			if ( lpResp )
			{
				memcpy( lpResp, lpVCC3->response, lpVCC3->response[0]+1 );

				if ( lpiRespLen )
					*lpiRespLen = lpVCC3->response[0]+1;
			}

			if ( fAck )
				goto EndFunc;
		}
	}

EndFunc:
	// ----------------------------------------------------------
	//	Re-enable rx event
	// ----------------------------------------------------------

	SetCommMask( lpVCC3->hComm, EVENT_MASK );

	return lpVCC3->nErrorCode;
}

/***************************************************************************

	Send command
		lpCmd contains [length byte + message].
		Checksum is calculated and appended.

***************************************************************************/

DllExport int WINAPI	VCC3_Send( LPVCC3INFO lpVCC3, LPBYTE lpCmd )
{
	return( lpVCC3->nErrorCode = SendPacket( lpVCC3, lpCmd ) );
}

/*****************************************************************************

	Receive Response within dwTimeout milleseconds
		lpResp contains [length byte + message + checksum] if not NULL
		lpiResp contains the complete length of the response including
		 Length, Frame Id, Command Id, Parameters and Checksum.

****************************************************************************/

DllExport int WINAPI	VCC3_Recv( LPVCC3INFO lpVCC3, LPBYTE lpResp,
								  LPINT lpiRespLen, DWORD dwTimeout )
{
	lpVCC3->nErrorCode = VCC3_ERR_NONE;
	lpVCC3->nRespErrorCode = VCC3_ERR_NONE;

	if ( lpiRespLen )
		*lpiRespLen = 0;

	while ( lpVCC3->fRecvBusy )
		IdleWindows();

	lpVCC3->fRecvBusy = TRUE;

	lpVCC3->nErrorCode = RecvPacket( lpVCC3, lpResp, lpiRespLen, dwTimeout );
	lpVCC3->nRespErrorCode = TranslateResponseError( lpResp );

	lpVCC3->fRecvBusy = FALSE;

	return( lpVCC3->nErrorCode );
}

/***************************************************************************

	Event Handler - This thread sends a message to the host application
	on received characters and change in CTS if hWndNotify was specified.

***************************************************************************/

static DWORD ComEventThread( LPSTR lpData )
{
	OVERLAPPED	os;
	DWORD		dwEvtMask;
	LPARAM		lParam = 0;
	DWORD		dwStatus;
	LPVCC3INFO	lpVCC3;

	lpVCC3 = (LPVCC3INFO) lpData;

	memset( &os, 0, sizeof( OVERLAPPED ) );

	if ( (os.hEvent = CreateEvent(	NULL, TRUE, FALSE, NULL )) == NULL )
	{
		return FALSE;
	}

	if ( !SetCommMask( lpVCC3->hComm, EVENT_MASK ))
	{
		CloseHandle( os.hEvent );
		return FALSE;
	}

	while( lpVCC3->fConnected )
	{
		dwEvtMask = 0;

		WaitCommEvent( lpVCC3->hComm, &dwEvtMask, NULL );

		if ( (dwEvtMask & EV_CTS) == EV_CTS )
		{
			GetCommModemStatus( lpVCC3->hComm, &dwStatus );

			if ( lpVCC3->hWndNotify )
			{
				if (( dwStatus & MS_CTS_ON ) != MS_CTS_ON )
					SendMessage( lpVCC3->hWndNotify, lpVCC3->uMsgNotify, VCC3_MSG_CTSLO, 0 );
				else
					SendMessage( lpVCC3->hWndNotify, lpVCC3->uMsgNotify, VCC3_MSG_CTSHI, 0 );
			}
		}

		if ( (dwEvtMask & EV_RXCHAR) == EV_RXCHAR && !lpVCC3->fRecvBusy )
		{
			// -----------------------------------------------------------------
			//	Process Notification and post message to host if specified
			// -----------------------------------------------------------------

			if ( ComCount( lpVCC3 ) > 0 )
			{
				lpVCC3->fRecvBusy = TRUE;

				if ( RecvPacket( lpVCC3, lpVCC3->notify, NULL, COMM_NOTIFY_TMO ) == VCC3_ERR_NONE )
				{
					lpVCC3->fRecvBusy = FALSE;

					if ( lpVCC3->hWndNotify )
						SendMessage( lpVCC3->hWndNotify, lpVCC3->uMsgNotify, VCC3_MSG_RECV, (LPARAM)(LPSTR)lpVCC3->notify );
				}
				lpVCC3->fRecvBusy = FALSE;
			}
		}
	}

	CloseHandle( os.hEvent );

	lpVCC3->dwThreadID = 0;
	lpVCC3->hEventThread = NULL;

	return TRUE;
}

/***************************************************************************

	Translate negative response errors

***************************************************************************/

static int TranslateResponseError( LPBYTE lpResp )
{
	int	nRespErrorCode = VCC3_ERR_NONE;

	// ----------------------------------
	//	ACK/NAK response
	// ----------------------------------

	if ( lpResp[1] & 0x80 )
	{
		switch( lpResp[2] )
		{
			case	0x00:
				break;

			case	0x01:
				nRespErrorCode = VCC3_NAK_ERR_BUFFERBUSY;
				break;

			case	0x02:
				nRespErrorCode = VCC3_NAK_ERR_LENGTH;
				break;

			case	0x03:
				nRespErrorCode = VCC3_NAK_ERR_SEQUENCE;
				break;

			case	0x04:
				nRespErrorCode = VCC3_NAK_ERR_COMMUNICATIONS;
				break;

			case	0x10:
				nRespErrorCode = VCC3_NAK_ERR_CHECKSUM;
				break;

			default:
				nRespErrorCode = VCC3_NAK_ERR_UNKNOWN;
				break;
		}
	}

	// ----------------------------------
	//	NOTIFY response
	// ----------------------------------

	else
	{
		if ( lpResp[2] & 0x40 )
		{
			switch( lpResp[3] )
			{
				case	0x00:
					nRespErrorCode = VCC3_RESP_ERR_CABLE;
					break;

				case	0x01:
					nRespErrorCode = VCC3_RESP_ERR_CAMERA_COMM;
					break;

				case	0x03:
					switch( lpResp[4] )
					{
						case	0x00:
							nRespErrorCode = VCC3_RESP_ERR_PANTILTER_NAK;
							break;

						case	0x01:
							nRespErrorCode = VCC3_RESP_ERR_PANTILTER_TMO;
							break;

						case	0x02:
							nRespErrorCode = VCC3_RESP_ERR_PANTILTER_CHECKSUM;
							break;

						default:
							nRespErrorCode = VCC3_RESP_ERR_PANTILTER_UNKNOWN;
							break;
					}
					break;

				case	0x04:
					switch( lpResp[4] )
					{
						case	0x00:
							nRespErrorCode = VCC3_RESP_ERR_VIDEOADAPTER_NAK;
							break;

						case	0x01:
							nRespErrorCode = VCC3_RESP_ERR_VIDEOADAPTER_TMO;
							break;

						case	0x02:
							nRespErrorCode = VCC3_RESP_ERR_VIDEOADAPTER_CHECKSUM;
							break;

						default:
							nRespErrorCode = VCC3_RESP_ERR_VIDEOADAPTER_UNKNOWN;
							break;
					}
					break;

				case	0x10:
					nRespErrorCode = VCC3_RESP_ERR_UNCONNECTED;
					break;

				case	0x11:
					nRespErrorCode = VCC3_RESP_ERR_UNDEFINED_COMMAND;
					break;

				case	0x12:
					nRespErrorCode = VCC3_RESP_ERR_UNDEFINED_PARAMETER;
					break;

				case	0x13:
					nRespErrorCode = VCC3_RESP_ERR_COMMAND_STATUS;
					break;

				case	0x14:
					nRespErrorCode = VCC3_RESP_ERR_PARAMETER_STATUS;
					break;

				case	0x16:
					nRespErrorCode = VCC3_RESP_ERR_TIMEOUT;
					break;

				case	0x18:
					nRespErrorCode = VCC3_RESP_ERR_WHITEBALANCE;
					break;

				case	0x20:
					nRespErrorCode = VCC3_RESP_ERR_ADJUSTMENT;
					break;

 				default:
					nRespErrorCode = VCC3_RESP_ERR_UNKNOWN;
					break;
			}
		}
	}
	return nRespErrorCode;
}

/*****************************************************************************

	Receive Response within dwTimeout milleseconds
		lpResp contains [length byte + message + checksum] if not NULL
		lpiResp contains the complete length of the response including
		 Length, Frame Id, Command Id, Parameters and Checksum.

****************************************************************************/

static int RecvPacket( LPVCC3INFO lpVCC3, LPBYTE lpResp,
						LPINT lpiRespLen, DWORD dwTimeout )
{
	int		i,c;
	int		iLen;
	BYTE	cSum;
	DWORD	startTime;
	BYTE	respACK[4] = { 0x03, 0x88, 0x00, 0x00 };
	BYTE	respSUM[4] = { 0x03, 0x88, 0x10, 0x00 };

	if ( lpiRespLen )
		*lpiRespLen = 0;

	startTime = ReadMSecs();

	for ( ;; )
	{
		for ( ;; )
		{
			// ----------------------------------------------------
			//	Wait for valid length byte or timeout
			// ----------------------------------------------------

			if ( ComCount( lpVCC3 ) > 0 )
			{
				if ( (iLen = ComGetc( lpVCC3, COMM_BYTE_TMO )) < 0 )
					return( iLen );
				else if ( iLen >= MIN_VCC3_MSGLEN && iLen <= MAX_VCC3_MSGLEN )
					break;
			}

			if ( ReadMSecs() - startTime >= dwTimeout )
				return( VCC3_ERR_RECV_TMO );
		}

		// ------------------------------------------------------
		//	Receive packet and calculate checksum
		// ------------------------------------------------------

		lpResp[0] = (BYTE) iLen;

		for ( i=0; i < iLen; i++ )
		{
			if ( (c = ComGetc( lpVCC3, COMM_BYTE_TMO )) < 0 )
				return( c );

			lpResp[i+1] = (BYTE) c;
		}

		cSum = 0;

		for ( i=0; i < iLen; i++ )
			cSum += lpResp[i];

		if ( (BYTE) -cSum == lpResp[iLen] )
			break;

		// ----------------------------------------------
		// Return CHECKSUM error to VC-C3 and continue
		// ----------------------------------------------

		SendPacket( lpVCC3, respSUM );
	}

	if ( lpiRespLen )
		*lpiRespLen = iLen+1;

	// -------------------------------------
	//	Process ACK/NAK Response
	// -------------------------------------

	if ( lpResp[1] & 0x80 )
	{
		if ( lpResp[2] == 0x00 )
			return( VCC3_ERR_NONE );
		else
			return( VCC3_ERR_NAK );
	}

	// -------------------------------------
	//	Return ACK to VC-C3
	// -------------------------------------

	SendPacket( lpVCC3, respACK );

	return( VCC3_ERR_NONE );
}

/***************************************************************************

	Send packet with checksum

***************************************************************************/

static int SendPacket( LPVCC3INFO lpVCC3, LPBYTE lpCmd )
{
	int		i;
	int		nErrorCode = VCC3_ERR_NONE;
	int		iCmdLen = (int) lpCmd[0];
	BYTE	cSum = 0;

	for ( i=0; i < iCmdLen; i++ )
	{
		if ( (nErrorCode = ComPutc( lpVCC3, lpCmd[i] )) != VCC3_ERR_NONE )
			return( nErrorCode );

		cSum += lpCmd[i];
	}

	nErrorCode = ComPutc( lpVCC3, (BYTE) -cSum );

	return nErrorCode;
}

/***************************************************************************

	Returns the number of chars in receive queue

***************************************************************************/

static int ComCount( LPVCC3INFO lpVCC3 )
{
	COMSTAT		ComStat;
	DWORD		dwErrorFlags;

	ClearCommError( lpVCC3->hComm, &dwErrorFlags, &ComStat );

	return ComStat.cbInQue;
}

/**************************************************************************

	Read character from receive queue for maximum dwMSecs

***************************************************************************/

static int ComGetc( LPVCC3INFO lpVCC3, DWORD dwMSecs )
{
	BYTE		c;
	DWORD		dwTimeout;
	BOOL		fReadStat;
	COMSTAT		ComStat;
	DWORD		dwErrorFlags;
	DWORD		dwLength;

	dwTimeout = ReadMSecs() + dwMSecs;

	while ( ReadMSecs() < dwTimeout )
	{
		ClearCommError( lpVCC3->hComm, &dwErrorFlags, &ComStat );

		if ( ComStat.cbInQue )
		{
			ClearCommError( lpVCC3->hComm, &dwErrorFlags, &ComStat );
			dwLength = min( (DWORD)1, ComStat.cbInQue );

			if ( dwLength > 0 )
			{
				fReadStat = ReadFile( lpVCC3->hComm, (LPSTR)&c,
						dwLength, &dwLength, &lpVCC3->osRead );

				if ( !fReadStat )
				{
					if (GetLastError() == ERROR_IO_PENDING)
					{
						while( !GetOverlappedResult( lpVCC3->hComm,
							&lpVCC3->osRead, &dwLength, TRUE ))
						{
							if ( GetLastError() == ERROR_IO_INCOMPLETE )
								continue;
							else
							{
								// an error occurred, try to recover
								ClearCommError( lpVCC3->hComm, &dwErrorFlags, &ComStat );
								break;
							}

						}
					}
					else
					{
						// some other error occurred
						dwLength = 0;
						ClearCommError( lpVCC3->hComm, &dwErrorFlags, &ComStat );
					}
				}
			}

			if ( dwLength == 1 )
				return( c & 255 );

			return VCC3_ERR_RECV_IO;
		}
	}

	return VCC3_ERR_RECV_TMO;
}

/***************************************************************************

	Write character to transmit queue

***************************************************************************/

static int ComPutc( LPVCC3INFO lpVCC3, BYTE cByte )
{
	BOOL		fWriteStat;
	DWORD		dwBytesWritten;
	DWORD		dwErrorFlags;
	COMSTAT		ComStat;

	fWriteStat = WriteFile( lpVCC3->hComm, (LPSTR)&cByte, 1,
				&dwBytesWritten, &lpVCC3->osWrite );

	if ( !fWriteStat )
	{
		if ( GetLastError() == ERROR_IO_PENDING )
		{
			while ( !GetOverlappedResult( lpVCC3->hComm,
				&lpVCC3->osWrite, &dwBytesWritten, TRUE ))
			{
				if ( GetLastError() == ERROR_IO_INCOMPLETE )
					continue;
				else
				{
					ClearCommError( lpVCC3->hComm, &dwErrorFlags, &ComStat );
					break;
				}
			}
		}
		else
		{
			ClearCommError( lpVCC3->hComm, &dwErrorFlags, &ComStat );
			return ( VCC3_ERR_SEND_IO );
		}
	}
	return VCC3_ERR_NONE;
}


/******************************************************************************

	Return current time in msecs

******************************************************************************/

static DWORD	ReadMSecs( VOID )
{
	return( (DWORD) GetCurrentTime() );
}

/******************************************************************************

	delay number of msecs

******************************************************************************/

static VOID	DelayMSecs( DWORD dwMSecs )
{
	DWORD dwTimeout;

	if ( dwMSecs )
	{
		dwTimeout = ReadMSecs() + dwMSecs;

		while ( ReadMSecs() < dwTimeout )
			IdleWindows();
	}
}

/**************************************************************************

	Wait for message queue to idle

**************************************************************************/

static VOID	IdleWindows( VOID )
{
	MSG		msg;
	DWORD	dwCount = 0L;

	Sleep(10);	// save CPU time

	while ( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
	{
		if ( GetMessage( &msg, NULL, 0, 0 ) )
		{
			TranslateMessage (&msg);
			DispatchMessage (&msg);
		}

		if ( ++dwCount > 100 )
			break;

		Sleep(10);
	}
}

/* end of file : vcc3.c */
