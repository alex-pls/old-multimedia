/** @file    VIPLib.h
 *
 *  @brief   This header contains all current VIPLib classes and methods.
 *
 *
 *  @warning Including this header in your project may waste some compiling time,
 *           in fact all classes and method are (sub)included too.
 *
 *  @bug
 *  @todo
 *
 *
 *  @version 1.02
 *  @date    28/08/2005 - //2005
 *  @author  Alessandro Polo
 *
 *
 ****************************************************************************
 * VIPLib Framework 1.02
 *  Copyright (C) Alessandro Polo 2005
 *  http://www.ewgate.net/viplib
 *
 ****************************************************************************/


/*
#include "../include/VIPLib.h"

main ()
 {
	 using namespace VIPLib;
	 [..]

	 vipFrameCache* ..
 }

main ()
 {

	 [..]

	 VIPLib::vipFrameCache* ..
 }

*/

#ifndef __VIPLIB_VIPLIB_H__
 #define __VIPLIB_VIPLIB_H__

//using namespace std

namespace VIPLib
 {



 // common shared definitions
 #include "../source/vipDefs.h"


#define VIPLIB_WITH_MPEG_SUPPORT	//only on nix system, need libmpeg3 library
#define VIPLIB_WITH_QUICKTIME_SUPPORT	//only on nix system, need quicktime4linux library
#define VIPLIB_WITH_XVID_SUPPORT

 // frames abstract and implementations
 #include "../source/vipFrame.h"

	#include "../source/vipFrameRGB32.h"
	#include "../source/vipFrameRGB24.h"
	#include "../source/vipFrameYUV420.h"
	#include "../source/vipFrameYUV444.h"
	#include "../source/vipFrameHSV.h"
	#include "../source/vipFrameGrey.h"
	#include "../source/vipFrameT.h"


 //utilities
 #include "../source/vipMatrix.h"
 #include "../source/vipDFMatrix.h"
 #include "../source/vipHist.h"
 #include "../source/vipUtility.h"
 #include "../source/vipThread.h"

 // buffers
 #include "../source/vipBuffer.h"

	#include "../source/buffers/vipBufferArray.h" // TEMPLATE
	#include "../source/buffers/vipBufferLink.h" // TEMPLATE
//	#include "../source/buffers/vipBufferSeq.h"


//////////////////////////////////////////////////////////////////// #include "../source/vipProcess.h"


 // data sources
 #include "../source/vipInput.h"

	#include "../source/inputs/vipNoiseGenerator.h"
	#include "../source/inputs/vipPlainFrameGenerator.h"

//	#include "../source/inputs/vipVideo4Linux.h"
//	#include "../source/inputs/vipDirectXInput.h"


 // data outputs
 #include "../source/vipOutput.h"

	#include "../source/outputs/vipDoctor.h"
	#include "../source/outputs/vipOuputVoid.h"

//	#include "../source/outputs/vipWindow32.h"
//	#include "../source/outputs/vipWindowQT.h"
//	#include "../source/outputs/vipWindowGTK.h"


 // filters
 #include "../source/vipFilter.h"

	#include "../source/filters/vipDigitalFilter.h"
	#include "../source/filters/vipMultiplexer.h"
	#include "../source/filters/vipFilterGeometric.h"
	#include "../source/filters/vipFilterNoiseChannel.h"
	#include "../source/filters/vipFilterEdge.h"


 // motion dectection suite
 #include "../source/vipVision.h"

	#include "../source/vision/vipMotionLame.h"
	#include "../source/vision/vipMotionIlluminationInvariant.h"


 // encoders and decoders
 #include "../source/vipCoder.h"

	#include "../source/coders/vipCoder_BMP.h"

	#if defined(VIPLIB_WITH_XVID_SUPPORT)

		#include "../source/coders/vipCoder_XVID.h"

	#endif

	#if defined(VIPLIB_WITH_MPEG_SUPPORT)

		#if defined(sun)        || defined(__sun)       || defined(linux)       || defined(__linux)    \
		 || defined(__CYGWIN__) || defined(__FreeBSD__) || defined(__OPENBSD__) || defined(__MACOSX__) \
		 || defined(__APPLE__)  || defined(sgi)         || defined(__sgi)
		// ok...Unix (Linux,Solaris,BSD,Irix,...)

			#include "../source/coders/vipCoder_MPEG.h"

		#endif

	#endif

	#if defined(VIPLIB_WITH_QUICKTIME_SUPPORT)

		#if defined(sun)        || defined(__sun)       || defined(linux)       || defined(__linux)    \
		 || defined(__CYGWIN__) || defined(__FreeBSD__) || defined(__OPENBSD__) || defined(__MACOSX__) \
		 || defined(__APPLE__)  || defined(sgi)         || defined(__sgi)
		// ok...Unix (Linux,Solaris,BSD,Irix,...)

			#include "../source/coders/vipCoder_MOV.h"

		#endif

	#endif


}








#endif //__VIPLIB_VIPLIB_H__
