/** @file vipNetClient.cpp
 *
 * File containing methods for the 'vipNetClient' class.
 * The header for this class can be found in vipNetClient.h, check that file
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



#include "vipNetClient.h"
#include "../vipUtility.h"


/**
 * @brief Default constructor initializes runmode and stats variables.
 *
 * @param mode set current processing mode, default is frame rate stats only.
 */
vipNetClient::vipNetClient(RUNMODE mode) : vipOutput()
 {
	DEBUGMSG("vipNetClient::vipNetClient(RUNMODE mode) : vipOutput() [CONTRUCTOR]", mode)

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
int vipNetClient::reset(bool startTimers)
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
int vipNetClient::setInputFrameRate(float fps)
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
void vipNetClient::updateFps()
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
void vipNetClient::updateExtime()
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


long vipNetClient::getElapsedTime() const
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
 * @see   operator << (vipFrameCache&)
 */
int vipNetClient::importFrom(vipFrameCache& img)
 {
	INFO("int vipNetClient::importFrom(vipFrameCache& img) [reading data]")

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
 * @see   operator << (vipFrameCache24&)
 */
int vipNetClient::importFrom(vipFrameCache24& img)
 {
	INFO("int vipNetClient::importFrom(vipFrameCache24& img) [reading data]")

        return VIPRET_NOT_IMPLEMENTED;
 }

/**
 * @brief Analyze frame and store statistics, elaboration time is saved.
 *
 * @param[in] img VIPLibb RGB Frame to be processed (analyzed)
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
 *
 * @note  Input operator (<<) call directly this function.
 * @see   operator << (vipFrameRGB&)
 */
int vipNetClient::importFrom(vipFrameRGB& img)
 {
	INFO("int vipNetClient::importFrom(vipFrameRGB& img) [reading data]")

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
 * @see   operator << (vipFrameGrey&)
 */
int vipNetClient::importFrom(vipFrameGrey& img)
 {
	INFO("int vipNetClient::importFrom(vipFrameGrey& img) [reading data]")

	return VIPRET_NOT_IMPLEMENTED;
 }


/**
 * @brief Input operator, import standard VIPLibb frame formats,
 *        current implementation calls directly importFrom() method
 *        or gather only frame statistics if RUNMODE is FPS_STAT.
 *
 * @param[in] img VIPLibb Cache Frame to be processed (analyzed)
 *
 * @see   importFrom(vipFrameCache&)
 */
void vipNetClient::operator << (vipFrameCache& img)
 {
	INFO("void vipNetClient::operator << (vipFrameCache& img) [importing data]")

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
 * @see   importFrom(vipFrameCache24&)
 */
void vipNetClient::operator << (vipFrameCache24& img)
 {
	INFO("void vipNetClient::operator << (vipFrameCache24& img) [importing data]")

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
 * @param[in] img VIPLibb RGB Frame to be processed (analyzed)
 *
 * @see   importFrom(vipFrameRGB&)
 */
void vipNetClient::operator << (vipFrameRGB& img)
 {
	INFO("void vipNetClient::operator << (vipFrameRGB& img) [importing data]")

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
 * @see   importFrom(vipFrameGrey&)
 */
void vipNetClient::operator << (vipFrameGrey& img)
 {
	INFO("void vipNetClient::operator << (vipFrameGrey& img) [importing data]")

	updateFps();

	if ( runmode )
		importFrom(img);

	updateExtime();

	if ( v_sleeptime )
		vipUtility::vipSleep(v_sleeptime);
 }




















