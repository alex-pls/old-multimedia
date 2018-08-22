/** @file    vipPlugIn_.cpp
 *
 *  @brief   Defines the entry point for the DLL application.
 *
 *
 *  @see     %CLASSNAME%
 *
 *  @version 1.0.
 *  @date    28/10/2005
 *  @author  Alessandro Polo
 *
 *
 ****************************************************************************
 * VIPLib Framework 1.0.2
 *  Copyright (C) Alessandro Polo 2006
 *  http://www.ewgate.net/viplib
 *
 ****************************************************************************/


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////// SETUP MODULE HERE
//////////////////////////////////////////////////////////// SETUP MODULE HERE
//////////////////////////////////////////////////////////////////////////////

// include your class header here

#define NULL 0

#include "..\..\..\..\..\source\buffers\vipBufferLink.h"
#include "..\..\..\..\..\source\vipFrameRGB24.h"

#define VIPPLUGIN_CLASSNAME		vipBufferLink<vipFrameRGB24>
#define VIPPLUGIN_CLASSNAMEq	"vipBufferLink<vipFrameRGB24>"
#define VIPPLUGIN_FULLNAME		"Double Linked List Buffer of vipFrameRGB24"


#define VIPPLUGIN_MAJORVERSION	0x00000001
#define VIPPLUGIN_MINORVERSION	0x00000000
#define VIPPLUGIN_BUILDNUMBER	0x00000002


// almost done, just add source code or library to project and build.


