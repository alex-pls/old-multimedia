/**
 *  @class   vipThread
 *
 *  @brief   Class for Multi-threading processes in VIPLib, simplify the
 *           use of threads and it's implemented for Linux and Windows both,
 *           developer doesn't need to implement os-dependent code.
 *
 *
 *  @bug     NOT FULLY IMPLEMENTED
 *
 *  @warning NOT FULLY IMPLEMENTED
 *
 *  @todo    NOT FULLY IMPLEMENTED
 *
 *
 *  @see
 *  @example ../tests/test_vipThread.cpp
 *
 *  @version 0.45
 *  @date    18/09/2005
 *  @author  Alessandro Polo
 *
 *
 ****************************************************************************
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.disi.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DISI - University of Trento
 *
 ****************************************************************************/


 #include "vipDefs.h"

#ifndef __VIPLIB_VIPTHREAD_H__
 #define __VIPLIB_VIPTHREAD_H__

#pragma warning(disable:4065) // warning C4065 @ line 653: switch statement contains 'default' but no 'case' labels

 #define VIPTHREAD_ARRAYSIZE 24

	 #define VIPTHREAD_DONE 0
	 #define VIPTHREAD_HALT1 3
	 #define VIPTHREAD_HALT2 6


	#define VIPTHREAD_TIMEOUT      		5000L	// 5 seconds
	#define VIPTHREAD_INFINITE     		INFINITE	// windows definition


	#define VIPRET_THREAD_WAIT_TIMEOUT	15011	//timed out
	#define VIPRET_THREAD_ABANDONED		15012	//object abandoned (check msdn)

	#define VIPTHREAD_DEFAULT			0200L

	#define VIPTHREAD_INITIALIZED           15030
	#define VIPTHREAD_UNINITIALIZED         15031

//	#define VIPRET_THREAD_
//	#define VIPRET_THREAD_





#if defined(sun)        || defined(__sun)       || defined(linux)       || defined(__linux)    \
 || defined(__CYGWIN__) || defined(__FreeBSD__) || defined(__OPENBSD__) || defined(__MACOSX__) \
 || defined(__APPLE__)  || defined(sgi)         || defined(__sgi)
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////// Unix (Linux,BSD,Irix,...)

/*


	default PTHREAD:

		- unbounded
		- nondetached
		- default stack (alsi default size)
		- inheris priority






*/
	#include <stdlib.h>
	#include <unistd.h>	// void usleep(long);
	#include <pthread.h>

	#include <signal.h>



	class vipThread
	 {


		protected:

			pthread_t* osThread;

			pthread_attr_t* osThreadAttr;

			bool secureMode;

			int status;

			void exit() {	pthread_exit(NULL);	 }


		public:

			vipThread()
			 {
				INFO("vipThread::vipThread() [CONSTRUCTOR]")

				secureMode = true;

				//segmentation fault:	if ( pthread_attr_init(osThreadAttr) )
				osThreadAttr = NULL;

				status = VIPTHREAD_UNINITIALIZED;
			 }


			vipThread( void* (*functionCall)(void*), void* ArgumentStructure = NULL)
			 {
				DEBUGMSG("vipThread::vipThread(..) [CONSTRUCTOR]", functionCall)

				secureMode = true;
				status = VIPTHREAD_UNINITIALIZED;

				//segmentation fault:	if ( pthread_attr_init(osThreadAttr) )
				osThreadAttr = NULL;

				if ( !pthread_create(osThread, osThreadAttr, functionCall, ArgumentStructure) )
					status = VIPTHREAD_INITIALIZED;

			 }



			~vipThread()
			 {
				INFO("vipThread::~vipThread() [DECONSTRUCTOR]")

				if ( status == VIPTHREAD_UNINITIALIZED )
					return;

				if (secureMode);
				 {
					if ( waitProcessEnd(true) == VIPRET_OK)
						delete osThread;
				 }

				//BUG?				delete osThread;
			 }



			inline pthread_t* dump_PTHREAD() { return osThread; };


			VIPRESULT run( void* (*functionCall)(void*), void* ArgumentStructure = NULL)
			 {
				DEBUGMSG("int vipThread::run(..)", functionCall)

				int ret;
				ret = pthread_create(osThread, osThreadAttr, functionCall, ArgumentStructure);

				if ( ret == 0 )
					status = VIPTHREAD_INITIALIZED;

				return ret;// compatible with VIPRET_OK !
			 }



			VIPRESULT pause()
			 {
				INFO("int vipThread::pause()")

				INFO("int vipThread::pause() is NOT AVAILABLE!")

				return VIPRET_INTERNAL_ERR;
			 }

			VIPRESULT resume()
			 {
				INFO("int vipThread::resume()")

				INFO("int vipThread::resume() is NOT AVAILABLE!")

				return VIPRET_INTERNAL_ERR;
			 }

			VIPRESULT terminate(bool cancel = false)
			 {
				DEBUGMSG("int vipThread::terminate(bool cancel)", cancel)

				if ( status == VIPTHREAD_UNINITIALIZED )
					return VIPRET_ILLEGAL_USE;

				pthread_exit(osThread);

				if (cancel)
					pthread_cancel(*osThread);

				return VIPRET_OK;
			 }

			VIPRESULT waitProcessEnd(bool closeThread = false)
			 {
				DEBUGMSG("int vipThread::waitProcessEnd(bool closeThread)", closeThread)

				if (status == VIPTHREAD_UNINITIALIZED)
					return VIPRET_ILLEGAL_USE;

				if ( !pthread_join(*osThread, NULL) )
					return VIPRET_INTERNAL_ERR;

				if ( closeThread )
				 {
					int status;
					pthread_exit(&status);
					return status;
				 }
				else
					return VIPRET_OK;

			 }



			void sleep(int millisec)
			 {
				usleep(millisec);
			 }



			int getPriority()
			 {
				sched_param param;
				int policy;

				pthread_getschedparam(*osThread, &policy, &param);
				return param.sched_priority;
			 }

			VIPRESULT setPriority(int priority)
			 {
				sched_param param;
				param.sched_priority = priority;
				return pthread_setschedparam(*osThread, SCHED_OTHER, &param);
			 }


			bool isSameAs(vipThread* dst)
			 {
				if ( pthread_equal(*osThread, *dst->dump_PTHREAD()) )
					return true;
				return false;
			 }



			void setSecureMode(bool val = true)
			 {
				secureMode = val;
			 }

			bool getSecureMode() { return secureMode; };




///////////////////////////////////////////////////////////////////////////
//CURRENT IMPLEMENTATION ONLY FUNCTIONS

			VIPRESULT sendSignal(int signal = 0)
			 {
				DEBUGMSG("int vipThread::sendSignal(int signal)", signal);

				return pthread_kill(*osThread, signal);
			 }
//
///////////////////////////////////////////////////////////////////////////



	};



	static pthread_mutex_t myCounterMutex = PTHREAD_MUTEX_INITIALIZER;
//	static pthread_mutex_t myConditionMutex = PTHREAD_MUTEX_INITIALIZER;
//	static pthread_cond_t myConditionConditioner = PTHREAD_COND_INITIALIZER;
	static long globalThreadCount = 0;


	class vipThreadManager
	 {

		protected:

			vipThread** myThreads;
			int* threadsID;

			int threadCount;

			bool secureMode;



		public:

			vipThreadManager()
			 {
				myThreads = new vipThread*[VIPTHREAD_ARRAYSIZE];
				for (int i = 0; i < VIPTHREAD_ARRAYSIZE; i++)
					myThreads[i] = NULL;

				secureMode = true;
				threadCount = 0;
			 }


			~vipThreadManager()
			 {
				if ( secureMode )
				 {
					waitThreadCompletition();
					delete [] myThreads;
					return;
				 }
				delete myThreads;
			 }

			vipThread* newThread(void * (* functionCall)(void *), void* ArgumentStructure = NULL)
			 {
				if ( threadCount >= VIPTHREAD_ARRAYSIZE )
					return NULL;

				myThreads[threadCount] = new vipThread(functionCall,  ArgumentStructure);

				pthread_mutex_lock( &myCounterMutex);
				++globalThreadCount;
				++threadCount;
				pthread_mutex_unlock( &myCounterMutex);

				return myThreads[threadCount];
			 }




			VIPRESULT waitThreadCompletition(int threadID = -1)
			 {
				if (threadID == -1)
				 {
					for (int i = 0; i < VIPTHREAD_ARRAYSIZE; i++)
						if (myThreads[i] != NULL)
							pthread_join( *myThreads[i]->dump_PTHREAD(), NULL);
					return VIPRET_OK;
				 }

				if ( threadID < 0 || threadID >= threadCount )
					return VIPRET_PARAM_ERR;

				pthread_join( *myThreads[threadID]->dump_PTHREAD(), NULL);
				return VIPRET_OK;
			 }


			int getCurrentThreadCount() { return threadCount; };

			long getGlobalThreadCount() { return globalThreadCount; };

			vipThread* getThread(int index)
			 {
				if ( index < 0 || index >= threadCount )
					return NULL;

				return myThreads[index];
			 }


	 };




#elif defined(_WIN32) || defined(__WIN32__)
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////// Windows 32



	#include <windows.h>
	#include <process.h>





//	#define VIPRET_THREAD_
//	#define VIPRET_THREAD_


/*
THREAD_PRIORITY_TIME_CRITICAL	15
THREAD_PRIORITY_HIGHEST			2
THREAD_PRIORITY_ABOVE_NORMAL	1
THREAD_PRIORITY_NORMAL			0
THREAD_PRIORITY_BELOW_NORMAL	-1
THREAD_PRIORITY_LOWEST			-2
THREAD_PRIORITY_IDLE			-15
thread_priority_error_return
*/



	class vipThread
	 {


		protected:

			HANDLE myThread;
			DWORD wdID;
			DWORD flags;

			int priority;
			int status;
			bool secureMode;

		public:

			vipThread()
			 {
				INFO("vipThread::vipThread() [CONSTRUCTOR]")

				secureMode = true;
				myThread = NULL;
				flags = CREATE_DEFAULT_ERROR_MODE;
				wdID = -1;
				status = VIPTHREAD_UNINITIALIZED;
			 };

/*
			vipThread(DWORD WINAPI (* functionCall)(LPVOID), void* ArgumentStructure = NULL)
			 {
				DEBUGMSG("vipThread::vipThread(..) [CONSTRUCTOR]", functionCall)

				secureMode = true;
				flags = CREATE_DEFAULT_ERROR_MODE;
				wdID = -1;

				myThread = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE)functionCall, ArgumentStructure, flags, &wdID);

				if ( myThread != NULL)
					status = VIPTHREAD_INITIALIZED;
				else
					status = VIPTHREAD_UNINITIALIZED;
			 };
*/


			~vipThread()
			 {
				INFO("vipThread::~vipThread() [DECONSTRUCTOR]")

				if (secureMode)
				 {
					if ( waitProcessEnd(VIPTHREAD_TIMEOUT, true) != VIPRET_OK )
						terminate();
				 }
			 };



			HANDLE dump_HANDLE() { return myThread; };

/*
			VIPRESULT run(DWORD WINAPI (* functionCall)(LPVOID arg), void* ArgumentStructure = NULL)
			 {
				DEBUGMSG("int vipThread::run(..)", functionCall)

				if (functionCall == NULL)
					return VIPRET_OK;

				myThread = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE)functionCall, NULL, flags, &wdID);

				if ( myThread != NULL)
					status = VIPTHREAD_INITIALIZED;
				else
					status = VIPTHREAD_UNINITIALIZED;

				return VIPRET_OK;
			 };
*/

			VIPRESULT pause()
			 {
				INFO("int vipThread::pause()")

				if ( myThread== NULL )
					return VIPRET_ILLEGAL_USE;

				if ( SuspendThread(myThread) != (DWORD)-1 )
					return VIPRET_OK;
				else
					return VIPRET_INTERNAL_ERR;
			 };

			VIPRESULT resume()
			 {
				INFO("int vipThread::resume()")

				if ( myThread== NULL )
					return VIPRET_ILLEGAL_USE;

				if ( ResumeThread(myThread) != (DWORD)-1 )
					return VIPRET_OK;
				else
					return VIPRET_INTERNAL_ERR;
			 };

			// for extreme case, dangerous
			VIPRESULT terminate(bool closeThread = false)
			 {
				DEBUGMSG("int vipThread::terminate(bool closeThread)", closeThread)

				if ( myThread == NULL )
					return VIPRET_ILLEGAL_USE;

				if ( myThread!= NULL )
				 {
					DWORD exitcode = 0;

					if ( GetExitCodeThread(myThread, &exitcode) )
						if ( TerminateThread(myThread, exitcode) )
							return VIPRET_OK;

					return VIPRET_INTERNAL_ERR;
				 }

				if (closeThread)
					if ( CloseHandle(myThread) )
					 {

						myThread = NULL;
						return VIPRET_OK;
					 }


				return VIPRET_ILLEGAL_USE;
			 };

			VIPRESULT waitProcessEnd(DWORD millisec = VIPTHREAD_TIMEOUT, bool closeThread = false)
			 {
				DEBUGMSG("int vipThread::waitProcessEnd(..,bool closeThread)", closeThread)

				if ( myThread == NULL )
					return VIPRET_ILLEGAL_USE;

				DWORD res = WaitForSingleObject(myThread, VIPTHREAD_TIMEOUT);

				if ( res == WAIT_OBJECT_0 )
					if ( closeThread )
					 {
						DWORD exitcode = 0;

						if ( GetExitCodeThread(myThread, &exitcode) )
							ExitThread(exitcode);
						else
							return VIPRET_INTERNAL_ERR;

						return VIPRET_OK;
					 }
					else
						return VIPRET_OK;

				else if ( res == WAIT_TIMEOUT )
					return VIPRET_THREAD_WAIT_TIMEOUT;

				else if ( res == WAIT_ABANDONED )
					return VIPRET_THREAD_ABANDONED;

				return VIPRET_INTERNAL_ERR;
			 };



			int getPriority()
			 {
				if ( myThread== NULL )
					return VIPRET_ILLEGAL_USE;

				return GetThreadPriority(myThread);
			 };

			VIPRESULT setPriority(int priority)
			 {
				if ( myThread== NULL )
					return VIPRET_ILLEGAL_USE;

				if ( SetThreadPriority(myThread, priority) )
					return VIPRET_OK;

				return VIPRET_INTERNAL_ERR;
			 };

			void sleep(int millisec)
			 {
				Sleep(millisec);
			 };

			bool isSameAs(vipThread* dst)
			 {
				if ( myThread != NULL && myThread == dst->dump_HANDLE() )
					return true;
				return false;
			 };



			void setSecureMode(bool val = true)
			 {
				secureMode = val;
			 };

			bool getSecureMode() { return secureMode; };

			DWORD getID() { return wdID; };

			DWORD getFlags() { return flags; }

			VIPRESULT setFlags(int vipThreadFlags = VIPTHREAD_DEFAULT)
			 {
				if ( myThread != NULL )
					return VIPRET_ILLEGAL_USE;

				switch (vipThreadFlags)
				 {
					default:
							flags = CREATE_DEFAULT_ERROR_MODE;
							break;
				 }
				return VIPRET_OK;
			 };



///////////////////////////////////////////////////////////////////////////
//CURRENT IMPLEMENTATION ONLY FUNCTIONS

//
///////////////////////////////////////////////////////////////////////////


	};



	static HANDLE hThrd;
	static HANDLE hMutexCounter;
	static long globalThreadCount = -1;


	class vipThreadManager
	 {

		protected:

			vipThread** myThreads;
			int* threadsID;

			int threadCount;

			bool secureMode;



		public:

			vipThreadManager()
			 {
				myThreads = new vipThread*[VIPTHREAD_ARRAYSIZE];
				for (int i = 0; i < VIPTHREAD_ARRAYSIZE; i++)
					myThreads[i] = NULL;

				hMutexCounter = NULL;
				hMutexCounter = CreateMutex(NULL, 0, NULL);

				secureMode = true;
				threadCount = 0;
			 }


			~vipThreadManager()
			 {
				ReleaseMutex(hMutexCounter);

				if ( secureMode )
				 {
					waitThreadCompletition();
					delete [] myThreads;
					return;
				 }
				delete myThreads;
			 }
/*
			vipThread* newThread(DWORD WINAPI (* functionCall)(LPVOID), void* ArgumentStructure = NULL)
			 {
				if ( threadCount >= VIPTHREAD_ARRAYSIZE )
					return NULL;

				myThreads[threadCount] = new vipThread(functionCall,  ArgumentStructure);

//				pthread_mutex_lock( &myCounterMutex);
				++globalThreadCount;
				++threadCount;
//				pthread_mutex_unlock( &myCounterMutex);

				return myThreads[threadCount];
			 }

*/


			VIPRESULT waitThreadCompletition(int threadID = -1)
			 {
				DWORD retVal = 0;

				if (threadID == -1)
				 {
					for (int i = 0; i < VIPTHREAD_ARRAYSIZE; i++)
						if (myThreads[i] != NULL)
							retVal += WaitForSingleObject(myThreads[i]->dump_HANDLE(), VIPTHREAD_TIMEOUT); //??
// == WAIT_TIMEOUT
					return VIPRET_OK;
				 }

				if ( threadID < 0 || threadID >= threadCount )
					return VIPRET_PARAM_ERR;

				retVal = WaitForSingleObject(myThreads[threadID]->dump_HANDLE(), VIPTHREAD_TIMEOUT);
				return VIPRET_OK;
			 }


			int getCurrentThreadCount() { return threadCount; };

			static long getGlobalThreadCount() { return globalThreadCount; };

			vipThread* getThread(int index)
			 {
				if ( index < 0 || index >= threadCount )
					return NULL;

				return myThreads[index];
			 }



			static int getPriority(vipThread* thr)
			 {
				if ( thr == NULL )
					return VIPRET_ILLEGAL_USE;

				return GetThreadPriority(thr->dump_HANDLE());
			 }

			static VIPRESULT setPriority(vipThread* thr, int priority)
			 {
				if ( thr== NULL )
					return VIPRET_ILLEGAL_USE;

				if ( SetThreadPriority(thr->dump_HANDLE(), priority) )
					return VIPRET_OK;

				return VIPRET_INTERNAL_ERR;
			 }



	 };




#else
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// Unknown configuration : compile with minimal dependencies.

/*

Solaris usa <thread.h>



*/

#endif
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////






#endif //__VIPLIB_VIPTHREAD_H__









/*****************************************************************
USE


void* myFunction(void* myArgumentStruct)
 {
	if ( myArgumentStruct->arg1 > myArgumentStruct->arg2 )
		return myArgumentStruct->data;

	return NULL;
 }

[..]

 {

	vipThread myThread;
	myThread.run(myFunction, myArgs);


 }

******************************************************************/



/*****************************************************************
USE:

typedef struct _MyData {
    int val1;
    int val2;
} MYDATA, *PMYDATA;


DWORD WINAPI myFunction(LPVOID lpParam)
 {
    PMYDATA pData;

    TCHAR msgBuf[255];
    size_t cchStringSize;
    DWORD dwChars;

    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if( hStdout == INVALID_HANDLE_VALUE )
        return 1;

    // Cast the parameter to the correct data type.

    pData = (PMYDATA)lpParam;

    // Print the parameter values using thread-safe functions.

    StringCchPrintf(msgBuf, 255, TEXT("Parameters = %d, %d\n"), pData-&gt;val1, pData-&gt;val2);
    StringCchLength(msgBuf, 255, &amp;cchStringSize);
    WriteConsole(hStdout, msgBuf, cchStringSize, &amp;dwChars, NULL);

    // Free the memory allocated by the caller for the thread  data structure.
    HeapFree(GetProcessHeap(), 0, pData);

	return VIPRET_OK;
 }

[..]
int main()
 {
    PMYDATA pData;

	// Allocate memory for thread data.

	pData = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(MYDATA));

	vipThread myThread;
	myThread.run(myFunction, pData);

//or
//
//	vipThread myThread(myFunction, pData);


 }
******************************************************************/
