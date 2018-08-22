/** @file    vipDefs.h
 *
 *  @brief   This header contains VIPLib shared definitions:
 *
 *            - VIPRESULT definition and standard return codes;
 *            - VIPLib Class types definition;
 *            - Some MACROs and a DEBUG utility.
 *
 *  @version 1.0.2
 *  @date    23/12/2005
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



#ifndef __VIPLIB_VIPDEFINITIONS_H__
 #define __VIPLIB_VIPDEFINITIONS_H__



/**
 * @brief  Short way to call unsigned char, useful with vipFrameT<>
 */
 typedef unsigned char uchar;


#if defined(sun)        || defined(__sun)       || defined(linux)       || defined(__linux)    \
 || defined(__CYGWIN__) || defined(__FreeBSD__) || defined(__OPENBSD__) || defined(__MACOSX__) \
 || defined(__APPLE__)  || defined(sgi)         || defined(__sgi)

	#include <unistd.h>

#endif
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////


 ///////////////////////////////////////////////////////////////////////////////////////////////////////
 // Define Return Codes (integers)

/**
 * @brief  Standard return type for VIPLib methods is defined as an integer,
 *         but in future it may be updated as a long, in your code you should
 *         define always VIPRESULT, not int:
 *         Sample: VIPRESULT myMethod() { return VIPRET_OK; }
 */
 typedef int VIPRESULT;


/**
 * @brief  Standard return codes are defined as pow of 2, so you may add result
 *         and still be able to extract each original error from the sum (15=8+4+2+1)
 */
 #define VIPRET_OK					0     /* no errors found */
 #define VIPRET_PARAM_ERR			1     /* illegal parameter(s) */
 #define VIPRET_INTERNAL_ERR		2     /* internal routine error */
 #define VIPRET_ILLEGAL_USE			4     /* illegal use of function (forbidden, empty video/frame, ..) */
 #define VIPRET_DEPRECATED_ERR		8     /*  */

 #define VIPRET_OK_DEPRECATED		16     /*  */

 #define VIPRET_NOT_IMPLEMENTED		666     /*  */






 ///////////////////////////////////////////////////////////////////////////////////////////////////////
 // Define class types

/**
 * @brief  Here we define main class types of VIPLib objects, referrer is
 *         classType enumeration of main iterfaces (vipInput, vipFrame, ..).
 */
 #define VIPCLASS_TYPE_UNKNOWN		0
 #define VIPCLASS_TYPE_OBJECT		10
 #define VIPCLASS_TYPE_EXCEPTION	20
 #define VIPCLASS_TYPE_FRAME		1000
 #define VIPCLASS_TYPE_BUFFER		2000
 #define VIPCLASS_TYPE_INPUT		4000
 #define VIPCLASS_TYPE_OUTPUT		8000
 #define VIPCLASS_TYPE_FILTER		1600
 #define VIPCLASS_TYPE_CODEC		3200
 #define VIPCLASS_TYPE_VISION		6400



//#define __VIPLIB_DEBUGMODE__

 // define DEBUG utility, use: DEBUG('variablename')
 #ifdef __VIPLIB_DEBUGMODE__

	#include <stdio.h>

	#define INFO(x) printf("_NFO: %s\n");
	#define DEBUG(x) printf("_DBG: %s = %p \n", #x, x);
	#define DEBUGMSG(msg, x) printf("_DBG: %s %s = %p \n", msg, #x, x);

 #else

	#define INFO(x) ;
	#define DEBUG(x) ;
	#define DEBUGMSG(msg, x) ;

 #endif //__VIPLIB_DEBUGMODE__







#endif //__VIPLIB_VIPDEFINITIONS_H__
