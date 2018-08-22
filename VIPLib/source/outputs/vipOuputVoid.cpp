/** @file vipOuputVoid.cpp
 *
 * File containing methods for the 'vipDoctor' class.
 * The header for this class can be found in vipDoctor.h, check that file
 * for class description.
 *
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



#include "vipOuputVoid.h"
#include "../vipUtility.h"



/**
 * @brief Default constructor initializes variables.
 *
 * @param deleteFrames if true, frames are deleted, nothing is done else.
 */
vipOutputVoid::vipOutputVoid(bool deleteFrames) : vipOutput()
 {
	DEBUGMSG("vipOutputVoid::vipOutputVoid(bool deleteFrames) : vipOutput() [CONTRUCTOR]", deleteFrames)

	clearMemory = deleteFrames;
	v_sleeptime = 0;
 }


/**
 * @brief  Set display frame rate (elaboration time is not subtracted).
 *
 * @param[in] frames per second (default is 0, no sleep)
 *
 * @return VIPRET_PARAM_ERR if fps is lower than 0, VIPRET_OK else.
 * @see    v_sleeptime
 */
VIPRESULT vipOutputVoid::setInputFrameRate(float fps)
 {
	if (fps < 0.)
		return VIPRET_PARAM_ERR;

	if ( fps == 0 )
		v_sleeptime = 0;
	else
		v_sleeptime = (long)( (float)1000 / fps ); // milliseconds

	return VIPRET_OK;
 }



/**
 * @brief  Display frame, conversion to vipFrameRGB24 and data-copy routine.
 *
 * @param[in] img VIPLibb Cache Frame to be imported.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 *
 * @note   Input operator (<<) call directly this function.
 * @see    operator << (vipFrameYUV420&)
 */
VIPRESULT vipOutputVoid::importFrom(vipFrameYUV420& img)
 {
	DEBUGMSG("int vipOutputVoid::importFrom(vipFrameYUV420& img) [reading data]", clearMemory)

	if (clearMemory)
		delete &img;

	if ( v_sleeptime )
		vipUtility::vipSleep( v_sleeptime );    // milliseconds

	return VIPRET_OK;
 }

/**
 * @brief  Display frame, data-copy routine. (optimized)
 *
 * @param[in] img VIPLibb Cache24 Frame to be imported.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 *
 * @note   Input operator (<<) call directly this function.
 * @see    operator << (vipFrameRGB24&)
 */
VIPRESULT vipOutputVoid::importFrom(vipFrameRGB24& img)
 {
	DEBUGMSG("int vipOutputVoid::importFrom(vipFrameRGB24& img) [reading data]", clearMemory)

	if (clearMemory)
		delete &img;
//BUG autofreedata !
	if ( v_sleeptime )
		vipUtility::vipSleep( v_sleeptime );    // milliseconds

	return VIPRET_OK;
 }

/**
 * @brief  Display frame, conversion to vipFrameRGB24
 *         and single channel data-copy routine.
 *
 * @param[in] img VIPLibb Grey Frame to be imported.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 *
 * @note   Input operator (<<) call directly this function.
 * @see    operator << (vipFrameT&)
 */
VIPRESULT vipOutputVoid::importFrom(vipFrameT<unsigned char>& img)
 {
	DEBUGMSG("int vipOutputVoid::importFrom(vipFrameT& img) [reading data]", clearMemory)

	if (clearMemory)
		delete &img;

	if ( v_sleeptime )
		vipUtility::vipSleep( v_sleeptime );    // milliseconds

	return VIPRET_OK;
 }



