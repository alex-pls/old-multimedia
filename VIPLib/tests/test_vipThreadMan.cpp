/** @file    test_vipThread.cpp
 *
 *  @brief   Testing code for class vipThread.
 *
 *
 *
 *  @bug
 *  @warning
 *  @todo
 *
 *  @see     vipThread
 *
 *  @version 1.0
 *  @date    26/08/2005
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


//---------------------------------------------------------------------------

#pragma hdrstop

//---------------------------------------------------------------------------

#include "../source/vipFrameRGB24.h"
#include "../source/outputs/vipDoctor.h"
#include "../source/codecs/vipCodec_BMP.h"

#include "../source/vipThread.h"

#include <stdio.h>

#pragma argsused

#if defined(sun)        || defined(__sun)       || defined(linux)       || defined(__linux)    \
 || defined(__CYGWIN__) || defined(__FreeBSD__) || defined(__OPENBSD__) || defined(__MACOSX__) \
 || defined(__APPLE__)  || defined(sgi)         || defined(__sgi)
/////////////////////////////////////////////////////////////////////////////////////// LNX
	#define VET_LNX

void* myFunction(void* myArgumentStruct)
 {
	printf("RUNNING\n");
	return NULL;
 }

#elif defined(_WIN32) || defined(__WIN32__)
/////////////////////////////////////////////////////////////////////////////////////// WIN
	#define VET_WIN

///	#include <strsafe.h>

	typedef struct _MyData {
		int val1;
		int val2;
	} MYDATA, *PMYDATA;


	DWORD WINAPI myFunction(LPVOID lpParam)
	 {
		HANDLE hStdout;
		PMYDATA pData;

		TCHAR msgBuf[255];
		size_t cchStringSize;
		DWORD dwChars;

		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		if( hStdout == INVALID_HANDLE_VALUE )
			return 1;

		// Cast the parameter to the correct data type.

		pData = (PMYDATA)lpParam;

        	printf("Typing from the thread...\n");

		// Print the parameter values using thread-safe functions.

//		StringCchPrintf(msgBuf, 255, TEXT("Parameters = %d, %d\n"), pData->val1, pData->val2);
//		StringCchLength(msgBuf, 255, &cchStringSize);
//		WriteConsole(hStdout, msgBuf, cchStringSize, &dwChars, NULL);

		// Free the memory allocated by the caller for the thread  data structure.
		HeapFree(GetProcessHeap(), 0, pData);

		return VETRET_OK;
	 }

#endif




int main(int argc, char* argv[])
 {
	printf("Testing vipThread Development...\n");

	vipFrameRGB24 img24;

        PMYDATA pData;

//WIN
	pData = (_MyData*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(MYDATA));

	vipThread myThread;
	myThread.run(myFunction, pData);

//or
//
//	vipThread myThread(myFunction, pData);


/*
	vipThreadManager thrMan;

	printf("Creating Threads..\n");

	vipThread* mythr = thrMan.newThread(myFunction);
	vipThread* mythr2 = thrMan.newThread(myFunction);

	printf("Thread Count [CurrentMan]: ...%d\n", thrMan.getCurrentThreadCount());
	printf("Thread Count [Global]: .......%d\n", thrMan.getGlobalThreadCount());
*/

	printf("Test Completed. Type something to continue...\n");
	getchar();

 }
//---------------------------------------------------------------------------



