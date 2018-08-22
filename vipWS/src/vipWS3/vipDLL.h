


#include <windows.h>


//////////////////////////////////////////////////////////
/*
typedef int (*MYPROC)(LPTSTR)


///////////


MYPROC ProcAdd = (MYPROC) GetProcAddress(hIst, TEXT("function name") );

int ret = (ProcAdd)( TEXT("message") );
*/






////////////////////////////////////////////////////////////


#ifdef __BUILDING_THE_DLL

#define __EXPORT_TYPE __export
	#else
	#define __EXPORT_TYPE __import
	#endif

#ifndef _MYDLL_H
#define _MYDLL_H

typedef struct _dllversioninfo
{
    DWORD dwmajorversion;
    DWORD dwminorversion;
    DWORD dwbuildnumber;
    DWORD dwplatformid;
}dllversioninfo;

typedef LONG		HRESULT;

extern "C" void __declspec(dllexport) WINAPI YourFunctionNumberOne();
extern "C" HRESULT __declspec(dllexport) WINAPI DllGetVersion(dllversioninfo* Release);


extern "C" bool __declspec(dllexport) WINAPI  FingerUser(AnsiString ip, int port, TMemo* Report);
extern "C" bool __declspec(dllexport) WINAPI  LameFinger(AnsiString ip, int port, AnsiString user, TMemo* Report);

#endif

