/** @file    ws_plugin_src.cpp
 *
 *  @brief   Defines the entry point for the DLL application.
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

/*
	DLL NATIVE & PLUGIN SYSTEM FUNCTIONS
*/

//#include <WS_DLL_13.h>

#include "WS_DLL_13.h"

#include "ws_plugin_def.h"
#include "ws_plugin_func.h"


extern VIPPLUGIN_CLASSNAME* vipClassHistance;



WS_DLL_13_API void* constructInstance(void)
{
	vipClassHistance = NULL;
	vipClassHistance = new VIPPLUGIN_CLASSNAME();
	return static_cast<void*>(vipClassHistance);
}


WS_DLL_13_API void destructInstance(void)
{
	if (vipClassHistance)
		delete vipClassHistance;
}




#define VIPPLUGINSYSTEM_VERSION		0x000000001
#define VIPPLUGINSYSTEM_REVISION	0x000000003


WS_DLL_13_API void getVIPPlugInInternalName(char* string)
 {
	strcpy(string, VIPPLUGIN_CLASSNAMEq);
 }

WS_DLL_13_API void getVIPPlugInFullName(char* string)
 {
	strcpy(string, VIPPLUGIN_FULLNAME);
 }

WS_DLL_13_API DWORD getVIPPlugInClassType()
 {
	return VIPPLUGIN_CLASSNAME::vipClassType;
 }



WS_DLL_13_API DWORD getVIPPlugInSystemVersion()
 {
	return VIPPLUGINSYSTEM_VERSION;
 }
WS_DLL_13_API DWORD getVIPPlugInSystemRevision()
 {
	return  VIPPLUGINSYSTEM_REVISION;
 }


typedef struct _dllversioninfo
{
    DWORD dwmajorversion;
    DWORD dwminorversion;
    DWORD dwbuildnumber;
    DWORD dwplatformid;
}dllversioninfo;


WS_DLL_13_API HRESULT DllGetVersion(dllversioninfo* Release)
 {
	Release->dwmajorversion = VIPPLUGIN_MAJORVERSION;
	Release->dwminorversion = VIPPLUGIN_MINORVERSION;
	Release->dwbuildnumber = VIPPLUGIN_BUILDNUMBER;
	Release->dwplatformid = 0x00000002;

	return 1;
 }


BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
 {
	switch (ul_reason_for_call)
	 {
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
		break;
	 }
	return TRUE;
 }
