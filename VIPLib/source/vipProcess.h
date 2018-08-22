/**
 *  @class   vipProcess
 *
 *  @brief   Class for manage complex processes (as multiple filters), and
 *           performance tests.
 *
 *
 *  @bug
 *  @warning
 *  @todo    Almost everything.
 *
 *  @see     vipFilter
 *
 *  @example ../tests/vt_vipProcess.cpp
 *
 *  @version 0.2
 *  @date    12/07/2005 - //2005
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



/**

	O       threading è dipendente dalla piattaforma !!
	O       come fare a chiamare (linkare funzione a un thread)? -> si usano i puntatori a funzioni
	O       se un filtro usa altri filtri.. crea subProcess ?? e come viene gestito!?

 * @brief Source class for processing video, has a source video, a list of filters to execute,
 *	parameters can be saved as XML (general parameters + each filter config subcall).
 *	May be upgraded for full multithreading support (real problem is syncronization!).
 *
 *
 */


#ifndef __VIPLIB_VIPPROCESS_H__
 #define __VIPLIB_VIPPROCESS_H__

 #include "vipDefs.h"
 #include "vipObject.h"
 #include "vipInput.h"
 #include "vipOutput.h"
 #include "vipFilter.h"

 #include "vipFrameYUV420.h"
 #include "vipFrameRGB24.h"
 #include "vipFrameT.h"


 #define VIPDEF_THREADs_MAX      		100  /*  */
 #define VIPDEF_MULITHREAD_ENABLED		false  /*  */


class vipProcess: public vipObject
 {

	protected:


		vipInput* v_source;
		vipOutput* v_out;

		vipFilter** v_Filters;

		unsigned int width;
		unsigned int height;

		bool v_isMultiThreadingEnabled;
		int v_MaxSimultaneousThread;

		int v_currentThreads;


	public:

		vipProcess();
		~vipProcess();

		void setInput(vipInput& sourceVideo) { v_source = &sourceVideo; };
		vipInput* getInput() { return v_source; };

		void setOutput(vipOutput& outputVideo) { v_out = &outputVideo; };
		vipOutput* getOutput() { return v_out; };

		VIPRESULT addFilter(vipFilter& aFilter);
		VIPRESULT removeFilter(vipFilter& oldFilter);

//		int addFunction(function pointer);

		VIPRESULT run();
		VIPRESULT runOnce();


		/**
		 * @brief Return current process setting about MultiThreading.
		 *
		 * @return true is MultiThreading is enabled, false else.
		 */
		bool isMultiThreadingEnabled() const { return v_isMultiThreadingEnabled; };

		/**
		 * @brief Return max simultaneuos thread
		 *
		 * @return
		 */
		int getMaxThreads() const { return v_MaxSimultaneousThread; };

		/**
		 * @brief
		 *
		 * @return
		 */
		int getCurrentThreads() const { return v_currentThreads; };




/*
		[..]
		[..]

		loadFromXML();
		saveToXML();
*/



 };



#endif /* __VIPLIB_VIPPROCESS_H__ */
