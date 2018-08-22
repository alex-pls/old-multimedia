#include "StdAfx.h"
#include ".\loaderdll.h"

#include <string.h>

#include <windows.h>
#include <shlwapi.h>

#include "dbghelp.h" //for  GetDLLFileExports

//#include "vipDLL.h"




struct windowsData
{
	HINSTANCE hDLL;


	void* hIst;

};





loaderDLL::loaderDLL(void)
{
	winData = new windowsData;
	ZeroMemory(winData, sizeof(winData));
	winData->hIst = NULL;

	init = false;
	validated = false;
	classType = 0;

	fileNameDLL = NULL;
	internalName = NULL;
	fullName = NULL;

    cbSize = 0;
    dwMajorVersion = 0;
    dwMinorVersion = 0;
    dwBuildNumber = 0;
    dwPlatformID = 0;
	vipp_sv = 0;
	vipp_sr = 0;

}


loaderDLL::~loaderDLL(void)
{
	removeInstance();

	release();

	if (fileNameDLL)
		delete fileNameDLL;

	if (internalName)
		delete internalName;

	if (fullName)
		delete fullName;

	delete winData;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////



int loaderDLL::load(char* filename)
 {
	if (init)
		return 10;

	fileNameDLL = new char[strlen(filename)];
	strcpy(fileNameDLL, filename);

	winData->hDLL = LoadLibrary( fileNameDLL );

    if (winData->hDLL)
	 {
		init = true;

		//just dll info, NOT NEEDED BUT..
		DLLGETVERSIONPROC getVersion = (DLLGETVERSIONPROC)GetProcAddress(winData->hDLL, "DllGetVersion");
		if (getVersion)
		 {
			DLLVERSIONINFO info;
			ZeroMemory(&info, sizeof(info));
			info.cbSize = sizeof(info);
			HRESULT result = (getVersion)(&info);

			cbSize = info.cbSize;
			dwMajorVersion = info.dwMajorVersion;
			dwMinorVersion = info.dwMinorVersion;
			dwBuildNumber = info.dwBuildNumber;
			dwPlatformID = info.dwPlatformID;
		 }
	 }


	return 0;
}

int loaderDLL::release()
 {
	if (winData->hDLL)
	 {
		if (FreeLibrary(winData->hDLL) )
		 {
			winData->hDLL = NULL;
			return 0;
		 }
		 return 1;
	 }
	 return 0;
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////


typedef DWORD (*GETVETPLUGININFO)();
typedef (*GETVETPLUGINNAME)(char*);
typedef int (*GETVETPLUGINTYPE)();

int loaderDLL::validate(bool force)
 {
	if (!init)
		return 10;

	 if (validated)
		 return 0;

	GETVETPLUGININFO versionProc = (GETVETPLUGININFO)GetProcAddress(winData->hDLL, "getVETPlugInSystemVersion");

	if (versionProc)
		vipp_sv = (versionProc)();

	GETVETPLUGININFO revisionProc = (GETVETPLUGININFO)GetProcAddress(winData->hDLL, "getVETPlugInSystemRevision");

	if (revisionProc)
		vipp_sr = (revisionProc)();

	if (force)
		validated = true;

	if (vipp_sv == 0)
		return 100;

	if (vipp_sv > _supported_VETPlugInSystemVersion)
		return 1;

	if (vipp_sr > _supported_VETPlugInSystemRevision)
		return 1;

	 validated = true;


	GETVETPLUGINNAME inameProc = (GETVETPLUGINNAME)GetProcAddress(winData->hDLL, "getVETPlugInInternalName");

	if (inameProc)
	{
		internalName = new char[64];
		(inameProc)(internalName);
	}

	GETVETPLUGINNAME fnameProc = (GETVETPLUGINNAME)GetProcAddress(winData->hDLL, "getVETPlugInFullName");

	if (fnameProc)
	{
		fullName = new char[128];
		(fnameProc)(fullName);
	}

	GETVETPLUGINTYPE typeProc = (GETVETPLUGINTYPE)GetProcAddress(winData->hDLL, "getVETPlugInClassType");

	if (typeProc)
		classType = (typeProc)();

	 return 0;
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

typedef void* (*MYCONSTRUCTOR)();

void* loaderDLL::createInstance()
 {
	if ( validate() )
		return NULL;

	MYCONSTRUCTOR constructor = (MYCONSTRUCTOR)GetProcAddress(winData->hDLL, "constructInstance");

	if (constructor)
	 {
		winData->hIst = (constructor)();//void*
		if (winData->hIst)
			return winData->hIst;
	 }

	return NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////


typedef void (*MYDESTRUCTOR)();

int loaderDLL::removeInstance()	// DONE AUTOMATIC!! NO?
{

	if (winData->hIst)
	 {
		MYDESTRUCTOR destructor = (MYDESTRUCTOR)GetProcAddress(winData->hDLL, "constructInstance");

		if (destructor)
		 {
			(destructor)();

			//HRESULT result = (destructor)(winData->hIst);// serve passare puntatore o gestito intenamente?
			//if (result)
				return 0;
		 }

		return 1;
	 }

	//return 10;

	return 0;
 }


void* loaderDLL::getInstance() { return winData->hIst; };

typedef HRESULT (*MYSETUPDIALOGOPENF)(HWND);

int loaderDLL::openSetupDialog()//HWND hParentWnd);
{
	if ( validate() )
		return -2;

	MYSETUPDIALOGOPENF openDialogFunction = (MYSETUPDIALOGOPENF)GetProcAddress(winData->hDLL, "openSetupDialog");

	if (openDialogFunction)
	 {
		HRESULT res = (openDialogFunction)(NULL);
		if (res)
			return (int)res;
		return 0;
	 }

	return -1;
}

typedef int (*MY_CALLBACK_FUNCTION_COUNT)();

int loaderDLL::get__callback_function_list_count()
{
	if ( validate() )
		return -2;

	MY_CALLBACK_FUNCTION_COUNT get_function_count = (MY_CALLBACK_FUNCTION_COUNT)GetProcAddress(winData->hDLL, "__callback_function_list_count");

	if (get_function_count)
	 {
		int res = (get_function_count)();
		return res;
	 }
	return -1;
}

typedef int (*MY_CALLBACK_FUNCTION_INFO)(__vipPlugInFuncInfo** infoPArray);

int loaderDLL::get__callback_function_list_info(__vipPlugInFuncInfo** infoPArray)
{
	if ( validate() )
		return -2;

	MY_CALLBACK_FUNCTION_INFO get_function_info = (MY_CALLBACK_FUNCTION_INFO)GetProcAddress(winData->hDLL, "__callback_function_list_info");

	if (get_function_info)
	 {
		int res = (get_function_info)(infoPArray);
		return res;
	 }
	return -1;
}


typedef int (*MY_CALLBACK_CALL)(__vipPlugInFuncParam_ID f_ID, __vipPlugInParams* f_param, __vipPlugInParams** f_param_xtra);

int loaderDLL::do__callback_function(__vipPlugInFuncParam_ID f_ID, __vipPlugInParams* f_param, __vipPlugInParams** f_param_xtra)
{
	if ( validate() )
		return -2;

	MY_CALLBACK_CALL do_function = (MY_CALLBACK_CALL)GetProcAddress(winData->hDLL, "__callback_function");

	if (do_function)
	 {
		int res = (do_function)(f_ID, f_param, f_param_xtra);
		return res;
	 }
	return -1;


}
/*
HGLOBAL laoderDLL::getDLLResource()
{
	HRSRC hResInfo;



	return LoadResource(winData->hDLL, hResInfo);

loadicon
}
*/

char* loaderDLL::getClassTypeNameFromClassTypeID(int classType_id)
 {
	char* ret = new char[32];

	switch( classType_id )
	 {
		case VIPCLASS_TYPE_FRAME	: strcpy(ret, "vipFrame");	break;
		case VIPCLASS_TYPE_BUFFER	: strcpy(ret, "vipBuffer");	break;
		case VIPCLASS_TYPE_INPUT	: strcpy(ret, "vipInput");	break;
		case VIPCLASS_TYPE_OUTPUT	: strcpy(ret, "vipOutput");	break;
		case VIPCLASS_TYPE_FILTER	: strcpy(ret, "vipFilter");	break;
		case VIPCLASS_TYPE_CODEC	: strcpy(ret, "vipCodec");	break;
		case VIPCLASS_TYPE_VISION	: strcpy(ret, "vipVision");	break;
		default						: strcpy(ret, "UNKNOWN");	break;
	 }
	return ret;
 }
//should use vipUtility::getTypeNameFromClassTypeID(int classType_id);



bool loaderDLL::GetDLLFileExports(unsigned int *nNoOfExports, char **&pszFunctions)
{
	return GetDLLFileExports(fileNameDLL, nNoOfExports, pszFunctions);
}



// Desc: Author: Ramanan.T
//       You must include this if you distribute this code in any form
//       This function passes the exported function names within a DLL file
bool loaderDLL::GetDLLFileExports(char *szFileName, unsigned int *nNoOfExports, char **&pszFunctions)
{
	HANDLE hFile;
	HANDLE hFileMapping;
	LPVOID lpFileBase;
	PIMAGE_DOS_HEADER pImg_DOS_Header;
	PIMAGE_NT_HEADERS pImg_NT_Header;
	PIMAGE_EXPORT_DIRECTORY pImg_Export_Dir;

	hFile = CreateFile(szFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,        FILE_ATTRIBUTE_NORMAL, 0);
	if(hFile == INVALID_HANDLE_VALUE)
		return false;

	hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
	if(hFileMapping == 0)
	{
		CloseHandle(hFile);
		return false;
	}

	lpFileBase = MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0);
	if(lpFileBase == 0)
	{
		CloseHandle(hFileMapping);
		CloseHandle(hFile);
		return false;
	}

	pImg_DOS_Header = (PIMAGE_DOS_HEADER)lpFileBase;

	pImg_NT_Header = (PIMAGE_NT_HEADERS)((LONG)pImg_DOS_Header + (LONG)pImg_DOS_Header->e_lfanew);


	if(IsBadReadPtr(pImg_NT_Header, sizeof(IMAGE_NT_HEADERS))||pImg_NT_Header->Signature != IMAGE_NT_SIGNATURE)
	{
		UnmapViewOfFile(lpFileBase);
		CloseHandle(hFileMapping);
		CloseHandle(hFile);
		return false;
	}

	pImg_Export_Dir = (PIMAGE_EXPORT_DIRECTORY)pImg_NT_Header->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
	if(!pImg_Export_Dir)
	{
		UnmapViewOfFile(lpFileBase);
		CloseHandle(hFileMapping);
		CloseHandle(hFile);
		return false;
	}

	pImg_Export_Dir= (PIMAGE_EXPORT_DIRECTORY)ImageRvaToVa(pImg_NT_Header,pImg_DOS_Header, (DWORD)pImg_Export_Dir, 0);

	DWORD **ppdwNames = (DWORD **)pImg_Export_Dir->AddressOfNames;

	ppdwNames = (PDWORD*)ImageRvaToVa(pImg_NT_Header, pImg_DOS_Header, (DWORD)ppdwNames, 0);
	if(!ppdwNames)
	{
		UnmapViewOfFile(lpFileBase);
		CloseHandle(hFileMapping);
		CloseHandle(hFile);
		return false;
	}

	*nNoOfExports = pImg_Export_Dir->NumberOfNames;

	pszFunctions = new char*[*nNoOfExports];

	for(unsigned i=0; i < *nNoOfExports; i++)
	{
		char *szFunc=(PSTR)ImageRvaToVa(pImg_NT_Header, pImg_DOS_Header, (DWORD)*ppdwNames, 0);

		pszFunctions[i] = new char[strlen(szFunc)+1];
		strcpy(pszFunctions[i],szFunc);

		ppdwNames++;
	}
	UnmapViewOfFile(lpFileBase);
	CloseHandle(hFileMapping);
	CloseHandle(hFile);
	return true;
};

