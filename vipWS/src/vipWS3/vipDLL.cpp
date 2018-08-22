

#include "vipDLL.h"



using namespace std;

extern "C"
BOOL WINAPI DllEntryPoint(HINSTANCE hinst, DWORD dwReason, LPVOID /*lpReserved*/)
 {
	switch (dwReason)
	 {
		case DLL_PROCESS_ATTACH:
			// Code to run when the DLL is loaded

			break;

		case DLL_PROCESS_DETACH:
			// Code to run when the DLL is freed
			break;

		case DLL_THREAD_ATTACH:
			// Code to run when a thread is created during the DLL's lifetime
			break;

		case DLL_THREAD_DETACH:
			// Code to run when a thread ends normally.
			break;
	 }


	return TRUE;
}



extern "C" HRESULT __declspec(dllexport) WINAPI DllGetVersion(dllversioninfo* Release)
 {
	Release->dwmajorversion = 1;
	Release->dwminorversion = 0;
	Release->dwbuildnumber = 10;
	return 1;
 }









extern "C" void __declspec(dllexport) WINAPI YourFunctionNumberOne()
	{
//		GetModuleFileName( NULL,FileName, sizeof (FileName) );
		MessageBox ( NULL, "UU", "Message", MB_OK );

}
