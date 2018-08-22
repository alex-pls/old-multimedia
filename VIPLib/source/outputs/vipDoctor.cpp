/** @file vipDoctor.cpp
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



#include "vipDoctor.h"
#include "../vipUtility.h"


/**
 * @brief Default constructor initializes runmode and stats variables.
 *
 * @param mode set current processing mode, default is frame rate stats only.
 */
vipDoctor::vipDoctor(RUNMODE mode) : vipOutput()
 {
	DEBUGMSG("vipDoctor::vipDoctor(RUNMODE mode) : vipOutput() [CONTRUCTOR]", mode)

	runmode = mode;
	v_sleeptime = 0;

	reset();
 }


/**
 * @brief Reset class variables for new statistics, by default it doesn't
 *        start frame rate counter.
 *
 * @param[in] startTimers if true start the frame rate counter, useful
 *                        for single frame processing performace test.
 * @see   lastFrameTime, lastExTime, lastFps, mediumFps, mediumExTime
 */
VIPRESULT vipDoctor::reset(bool startTimers)
 {
	lastFps = 0;
	mediumFps = 0;
	lastExTime = 0;
	mediumExTime = 0;
	v_sleeptime = 0;

	if ( startTimers )
	 {
		lastFrameTime = clock();
		frameCount = 1;
	 }
	else
	 {
		frameCount = 0;
		lastFrameTime = 0;
	 }
        return VIPRET_OK;
 }



/**
 * @brief  Set display frame rate (elaboration time is not subtracted).
 *
 * @param[in] frames per second (default is 0, no sleep)
 *
 * @return VIPRET_PARAM_ERR if fps is lower than 0, VIPRET_OK else.
 * @see    v_sleeptime
 */
VIPRESULT vipDoctor::setInputFrameRate(float fps)
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
 * @brief Updates last frame rate time and average.
 * @see clock()
 * @see lastFps
 * @see mediumFps
 * @see lastFrameTime
 */
void vipDoctor::updateFps()
 {
	if ( frameCount == 0 || clock() - lastFrameTime == 0)
	 {
		lastFrameTime = clock();
		frameCount++;
		return;
	 }
										//CLOCKS_PER_SEC;//CLK_TCK;
	lastFps = 1  / ( ( clock() - lastFrameTime ) / CLOCKS_PER_SEC ); // fps = 1/elapsedsecond
	mediumFps = (mediumFps * (frameCount-1) + lastFps ) / frameCount;

	lastFrameTime = clock();
	frameCount++;
 }

/**
 * @brief Updates last processing (analyzing) time and average.
 * @see clock()
 * @see lastExTime
 * @see mediumExTime
 * @see lastFrameTime
 */
void vipDoctor::updateExtime()
 {
	if ( frameCount == 0 || clock() - lastFrameTime == 0 )
	 {
		lastExTime = clock();
		return;
	 }

										//CLOCKS_PER_SEC;//CLK_TCK;
	lastExTime = 1000 * ( clock() - lastFrameTime ) / CLOCKS_PER_SEC;	//milliseconds
	mediumExTime = (mediumExTime * (frameCount-1) + lastExTime ) / frameCount;
 }


long vipDoctor::getElapsedTime() const
 {
	return (long) ( 1000 * ( clock() - lastFrameTime ) / CLOCKS_PER_SEC);	//milliseconds
 }





/**
 * @brief Analyze frame and store statistics, elaboration time is saved.
 *
 * @param[in] img VIPLibb Cache Frame to be processed (analyzed)
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
 *
 * @note  Input operator (<<) call directly this function.
 * @see   operator << (vipFrameYUV420&)
 */
VIPRESULT vipDoctor::importFrom(vipFrameYUV420& img)
 {
	INFO("int vipDoctor::importFrom(vipFrameYUV420& img) [reading data]")

        return VIPRET_NOT_IMPLEMENTED;
 }

/**
 * @brief Analyze frame and store statistics, elaboration time is saved.
 *
 * @param[in] img VIPLibb Cache24 Frame to be processed (analyzed)
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
 *
 * @note  Input operator (<<) call directly this function.
 * @see   operator << (vipFrameRGB24&)
 */
VIPRESULT vipDoctor::importFrom(vipFrameRGB24& img)
 {
	INFO("int vipDoctor::importFrom(vipFrameRGB24& img) [reading data]")

        return VIPRET_NOT_IMPLEMENTED;
 }

/**
 * @brief Analyze frame and store statistics, elaboration time is saved.
 *
 * @param[in] img Greyscale VIPLibb Frame to be processed (analyzed)
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
 *
 * @note  Input operator (<<) call directly this function.
 * @see   operator << (vipFrameT&)
 */
VIPRESULT vipDoctor::importFrom(vipFrameT<unsigned char>& img)
 {
	INFO("int vipDoctor::importFrom(vipFrameT<unsigned char>& img) [reading data]")

	return VIPRET_NOT_IMPLEMENTED;
 }


/**
 * @brief Input operator, import standard VIPLibb frame formats,
 *        current implementation calls directly importFrom() method
 *        or gather only frame statistics if RUNMODE is FPS_STAT.
 *
 * @param[in] img VIPLibb Cache Frame to be processed (analyzed)
 *
 * @see   importFrom(vipFrameYUV420&)
 */
void vipDoctor::operator << (vipFrameYUV420& img)
 {
	INFO("void vipDoctor::operator << (vipFrameYUV420& img) [importing data]")

	updateFps();

	if ( runmode )
		importFrom(img);

	updateExtime();

	if ( v_sleeptime )
		vipUtility::vipSleep(v_sleeptime);
 }

/**
 * @brief Input operator, import standard VIPLibb frame formats,
 *        current implementation calls directly importFrom() method
 *        or gather only frame statistics if RUNMODE is FPS_STAT.
 *
 * @param[in] img VIPLibb Cache24 Frame to be processed (analyzed)
 *
 * @see   importFrom(vipFrameRGB24&)
 */
void vipDoctor::operator << (vipFrameRGB24& img)
 {
	INFO("void vipDoctor::operator << (vipFrameRGB24& img) [importing data]")

	updateFps();

	if ( runmode )
		importFrom(img);

	updateExtime();

	if ( v_sleeptime )
		vipUtility::vipSleep(v_sleeptime);
 }


/**
 * @brief Input operator, import standard VIPLibb frame formats,
 *        current implementation calls directly importFrom() method.
 *        or gather only frame statistics if RUNMODE is FPS_STAT.
 *
 * @param[in] img Greyscale VIPLibb Frame to be processed (analyzed)
 *
 * @see   importFrom(vipFrameT&)
 */
void vipDoctor::operator << (vipFrameT<unsigned char>& img)
 {
	INFO("void vipDoctor::operator << (vipFrameT& img) [importing data]")

	updateFps();

	if ( runmode )
		importFrom(img);

	updateExtime();

	if ( v_sleeptime )
		vipUtility::vipSleep(v_sleeptime);
 }




















