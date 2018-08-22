/** @file    ws_plugin_def.h
 *
 *  @brief
 *
 *
 *  @see     vipFilterSample
 *
 *  @version 1.0.
 *  @date    28/10/2005
 *  @author  Alessandro Polo
 *
 *
 ****************************************************************************
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.science.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DIT - University of Trento
 *
 ****************************************************************************/


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////// DO NOT EDIT FOLLOWING
//////////////////////////////////////////////////////// DO NOT EDIT FOLLOWING
//////////////////////////////////////////////////////////////////////////////

// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the WS_DLL_13_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// WS_DLL_13_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.


#ifdef WS_DLL_13_EXPORTS
	#define WS_DLL_13_API __declspec(dllexport)
#else
	#define WS_DLL_13_API __declspec(dllimport)
#endif


#include <windows.h>
