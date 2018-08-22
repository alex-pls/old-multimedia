/** @file    test_vipThread.cpp
 *
 *  @brief   Testing code for class vipThread.
 *
 *           vipThread class is defined for
 *
 *  @bug
 *  @warning
 *  @todo    debug and update
 *
 *  @see     vipThread
 *
 *  @version 0.1
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
#include <stdio.h>

#include "../source/vipThread.h"


// sample for global access. (same scope!)
static int globalValue = 0;


#pragma argsused

#if defined(sun)        || defined(__sun)       || defined(linux)       || defined(__linux)    \
 || defined(__CYGWIN__) || defined(__FreeBSD__) || defined(__OPENBSD__) || defined(__MACOSX__) \
 || defined(__APPLE__)  || defined(sgi)         || defined(__sgi)
/////////////////////////////////////////////////////////////////////////////////////// LNX

	void* myFunction(void* myArgumentStruct)
	 {
		globalValue++;
		printf("Typing from the thread...\n");
		return NULL;
	 }

#elif defined(_WIN32) || defined(__WIN32__)
/////////////////////////////////////////////////////////////////////////////////////// WIN

	DWORD WINAPI myFunction(LPVOID lpParam)
	 {
		globalValue++;
       	printf("       Typing from the thread...\n");
		return VETRET_OK;
	 }

#endif



/////////////////////////////////////////////////////////////////////////////////////// MAIN


int main(int argc, char* argv[])
 {
	printf("Testing vipThread Development...\n");

	printf("\nCreating Instances...\n");
	vipThread myThread;

	printf(".\n");

	myThread.run(myFunction);


	printf("vipThread direct thread creation...\n");

	vipThread myThread2(myFunction);



	printf("Waiting for Threads...");

	myThread2.waitProcessEnd();

	printf("DONE\n");



	printf("globalValue = %d\n", globalValue);

	printf("Test Completed. Type something to continue...\n");
	getchar();

 }
//---------------------------------------------------------------------------



