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
	switch ( f_ID )
	{
	case 0:
		vipClassHistance->getParameters().setRunMode((vipFilterGeometricParameters::RUNMODE)f_param->int_value);
		break;

	case 1:
		vipClassHistance->getParameters().setRotationDegree( (float) f_param->double_value );
		break;

	case 2:
		vipClassHistance->getParameters().forceOutputSize(f_param->bool_value);
		break;

	case 3:
		{
		vipFilterGeometricParameters::RUNMODE ret = vipClassHistance->getParameters().getRunMode();
		int* retReal = new int;
		*retReal = (int) ret;
		f_param->result = static_cast<void*>(retReal);
		break;
		}

	default:
		return 1;
	}


	return 0;

 }

WS_DLL_13_API  int __callback_function_list_count()
{
	return 4;
}

WS_DLL_13_API  int __callback_function_list_info(__vipPlugInFuncInfo** infoPArray)
{
	infoPArray[0]->init(	0,	//id
							"setRunMode",	//name
							"INT",	//param1
							"VOID",	//result
							"void setRunMode(RUNMODE mode);"	//c_decl
						);

	infoPArray[1]->init(	1,	//id
							"setRotationDegree",	//name
							"DOUBLE",	//param1
							"VOID",	//result
							"void setRotationDegree(float degree);"	//c_decl
						);

	infoPArray[2]->init(	2,	//id
							"forceOutputSize",	//name
							"BOOL",	//param1
							"VOID",	//result
							"void forceOutputSize(bool value = true);"	//c_decl
						);

	infoPArray[3]->init(	3,	//id
							"getRunMode",	//name
							"VOID",	//param1
							"INT",	//result
							"RUNMODE getRunMode();"	//c_decl
						);


	return 0;
}




WS_DLL_13_API  HRESULT openSetupDialog(HWND hParentWnd = NULL)
{
	//add your setup dialog here


	MessageBox( hParentWnd, "Sorry, Setup dialog has not been implemented jet.", "veTFilterGeometric PlugIn", MB_OK | MB_ICONWARNING);



	return 1;
}