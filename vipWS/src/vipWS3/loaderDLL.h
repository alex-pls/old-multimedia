#pragma once

#ifndef __loaderDLL_H__
 #define __loaderDLL_H__


#include "../vipPlugIns13/ws_plugin_func.h"
#include "../../../../source/vipDefs.h"

/* NOTES

 CANNOT DECLARE WINDOWS OBJECTS HERE BECAUSE windows.h HEADER
 RAISES CONFLICTS WITH .NET FRAMEWORK, SO WE USE A STRUCT AND
 DEFINE ALL IN CPP FILE.
*/

struct windowsData;
typedef unsigned long       DWORD;


class loaderDLL
 {

	protected:

		windowsData* winData;
		bool init;
		bool validated;

		char* fileNameDLL;

		char* internalName;//classname
		char* fullName;
		int classType;
		DWORD cbSize;
		DWORD dwMajorVersion;
		DWORD dwMinorVersion;
		DWORD dwBuildNumber;
		DWORD dwPlatformID;

		DWORD vipp_sv;
		DWORD vipp_sr;




	public:
		loaderDLL(void);

		~loaderDLL(void);

		int load(char* filename);
		int release();
		int validate(bool force = false);


		void* createInstance();
		int removeInstance();
		void* getInstance();


		int openSetupDialog();//HWND hParentWnd);

		int get__callback_function_list_count();
		int get__callback_function_list_info(__vipPlugInFuncInfo** infoPArray);
		int do__callback_function(__vipPlugInFuncParam_ID f_ID, __vipPlugInParams* f_param, __vipPlugInParams** f_param_xtra = NULL );

		char* getFileName() { return fileNameDLL; };
		char* getInternalName() { return internalName; };
		char* getFullName() { return fullName; };
		int getClassType() { return classType; };
		char* getClassTypeName() { return getClassTypeNameFromClassTypeID(classType); };


		bool isInitialized() { return init; };
		bool isValidated() { return validated; };


		DWORD getVETPlugInSystemVersion() { return vipp_sv; };
		DWORD getVETPlugInSystemRevision() { return vipp_sr; };

		static const DWORD _supported_VETPlugInSystemVersion = 0x000000001;
		static const DWORD _supported_VETPlugInSystemRevision = 0x000000003;


		DWORD getDLL_Size() { return cbSize; };
		DWORD getDLL_MajorVersion() { return dwMajorVersion; };
		DWORD getDLL_MinorVersion() { return dwMinorVersion; };
		DWORD getDLL_BuildNumber() { return dwBuildNumber; };
		DWORD getDLL_PlatformID() { return dwPlatformID; };

		bool GetDLLFileExports(unsigned int *nNoOfExports, char **&pszFunctions);

		static char* getClassTypeNameFromClassTypeID(int classType_id);
		bool static GetDLLFileExports(char *szFileName, unsigned int *nNoOfExports, char **&pszFunctions);
 };



#endif