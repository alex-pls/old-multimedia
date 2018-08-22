/** @file    ws_plugin_func.h
 *
 *  @brief
 *
 *
 *  @see     vipInputSample
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
#include <string.h>


typedef int __vipPlugInFuncParam_ID;

struct __vipPlugInParams
 {
	int int_value;
	bool bool_value;
	double double_value;
	char* charP_value;
	void* voidP_value;

	void* result;

	void init()
	 {
		charP_value = NULL;
		voidP_value = NULL;
		result = NULL;
	 }

	int setParam(int value)
	 {
		int_value = value;
		return 0;
	 }
	int setParam(bool value)
	 {
		bool_value = value;
		return 0;
	 }
	int setParam(double value)
	 {
		double_value = value;
		return 0;
	 }
	int setParam(char* value)
	 {
		charP_value = value;
		return 0;
	 }
	int setParam(void* value)
	 {
		voidP_value = value;
		return 0;
	 }

	void dispose()
	 {
		if (charP_value == NULL)
			delete charP_value;
		if (voidP_value == NULL)
			delete voidP_value;
		if (result == NULL)
			delete result;
	 }
 };

struct __vipPlugInFuncInfo
 {
	__vipPlugInFuncParam_ID id;
	char* name;
	char* param1;
	char* result;

	char* c_decl;


	void init()
	 {
		id = -1;
		name = NULL;
		param1 = NULL;
		result = NULL;
		c_decl = NULL;
	 }

	void init(__vipPlugInFuncParam_ID id_v, char* name_v, char* param1_v, char* result_v, char* c_decl_v)
	 {
		id = id_v;

		if ( name_v != NULL && strlen(name_v) )
		 {
			name = new char[strlen(name_v)];
			strcpy(name, name_v);
		 }
		else
			name = NULL;

		if ( param1_v != NULL && strlen(param1_v) )
		 {
			param1 = new char[strlen(param1_v)];
			strcpy(param1, param1_v);
		 }
		else
			param1 = NULL;

		if ( result_v != NULL && strlen(result_v) )
		 {
			result = new char[strlen(result_v)];
			strcpy(result, result_v);
		 }
		else
			result = NULL;

		if ( c_decl_v != NULL && strlen(c_decl_v) )
		 {
			c_decl = new char[strlen(c_decl_v)];
			strcpy(c_decl, c_decl_v);
		 }
		else
			c_decl = NULL;

	 }

	void dispose()
	 {
		if (name == NULL)
			delete name;
		if (param1 == NULL)
			delete param1;
		if (result == NULL)
			delete result;
		if (c_decl == NULL)
			delete c_decl;
	 }
 };
