/** @file    WS_DLL_13.cpp
 *
 *  @brief   Defines the entry point for the DLL application.
 *
 *
 *  @see     vipVisionSample
 *
 *  @version 1.0
 *  @date    19/05/2006 7.26.23
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

#include "WS_DLL_13.h"
#include "../ws_plugin_def.h"
#include "../ws_plugin_func.h"

VIPPLUGIN_CLASSNAME* vipClassHistance;




//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////// SETUP MODULE HERE
//////////////////////////////////////////////////////////// SETUP MODULE HERE
//////////////////////////////////////////////////////////////////////////////


WS_DLL_13_API  int __callback_function(__vipPlugInFuncParam_ID f_ID,
								   __vipPlugInParams* f_param,
								   __vipPlugInParams** f_param_xtra = NULL )
 {
/*	switch ( f_ID )
	{
	case 0:

		break;

	case 1:

		break;

	case 2:

		break;

	case 3:

		break;

	default:
		return 1;
	}
*/

	return 0;

 }

WS_DLL_13_API  int __callback_function_list_count()
 {
	return 0;
 }

WS_DLL_13_API  int __callback_function_list_info(__vipPlugInFuncInfo** infoPArray)
 {
/*	infoPArray[0]->init(	0,	//id
							"",	//name
							"",	//param1
							"",	//result
							""	//c_decl
						);
*/
	return 0;
 }




WS_DLL_13_API  HRESULT openSetupDialog(HWND hParentWnd = NULL)
{
	//add your setup dialog here


	MessageBox( hParentWnd, "Sorry, Setup dialog has not been implemented jet.", "vipVisionSample PlugIn", MB_OK | MB_ICONWARNING);



	return 1;
}
