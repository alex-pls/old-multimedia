/** @file vipOutputSample.cpp
 *
 * File containing methods for the 'vipOutputSample' class.
 * The header for this class can be found in vipOutputSample.h, check that file
 * for class description.
 *
 *
 ****************************************************************************
 *  Class based on Package Studio template: vipOutputTemplate version 0.9.12
 ****************************************************************************
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.science.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DIT - University of Trento
 *
 ****************************************************************************/



#include "vipOutputSample.h"


#include "I:\Projects\Software\VIPLib\source\vipUtility.h"



/**
 * @brief  Default constructor initializes variables and canvas.
 *
 * @param[in]  mainWindow Main window's handle, if not NULL, it will be created.
 */
vipOutputSample::vipOutputSample() : vipOutput()
 {
	INFO("vipOutputSample::vipOutputSample() : vipOutput() [CONTRUCTOR]")


	height = VIPOUTPUTSAMPLE_DEF_HEIGHT;
	width = VIPOUTPUTSAMPLE_DEF_WIDTH;
	v_sleeptime = 0;

	init();


 }


/**
 * @brief  Default constructor initializes variables.
 *
 * @param width Canvas' width.
 * @param height Canvas' height.
 *
 * @param[in]  mainWindow Main window's handle, if not NULL, it will be created.
 */
vipOutputSample::vipOutputSample(unsigned int w, unsigned int h) : vipOutput()
 {
	INFO("vipOutputSample::vipOutputSample() : vipOutput() [CONTRUCTOR]")


	height = h;
	width = w;
	v_sleeptime = 0;

	init();
 }


/**
 * @brief  Default destructor, wait for pending events and flush.
 */
vipOutputSample::~vipOutputSample()
 {

 }


/**
 * @brief  Initialize canvas, create window if necessary.
 * @return VIPRET_OK
 */
VIPRESULT vipOutputSample::init()
 {
	return VIPRET_NOT_IMPLEMENTED;
 }



/**
 * @brief  Set display frame rate (elaboration time is not subtracted).
 *
 * @param[in] frames per second (default is 0, no sleep)
 *
 * @return VIPRET_PARAM_ERR if fps is lower than 0, VIPRET_OK else.
 */
VIPRESULT vipOutputSample::setFrameRate(float fps)
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
 * @brief  Show canvas and if selected also main window.
 *
 * @return VIPRET_OK
 */
VIPRESULT vipOutputSample::show()
 {
	return VIPRET_NOT_IMPLEMENTED;
 }



/**
 * @brief  Hide canvas and if selected also main window.
 *
 * @return VIPRET_OK
 */
VIPRESULT vipOutputSample::hide()
 {
	return VIPRET_NOT_IMPLEMENTED;
 }



/**
 * @brief  Display frame, conversion to vipFrameRGB24 and data-copy routine.
 *
 * @param[in] img VIPLib Cache Frame to be displayed.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 *
 * @note   Input operator (<<) call directly this function.
 * @see    operator << (vipFrameYUV420&)
 */
VIPRESULT vipOutputSample::importFrom(vipFrameYUV420& img)
 {
	INFO("int vipOutputSample::importFrom(vipFrameYUV420& img) [reading data]")

// image displaying routine

	//	if ( v_sleeptime && v_sleeptime > (long)getElaborationTime())
	//		vipUtility::vipSleep( v_sleeptime - (long)getElaborationTime() );
	vipUtility::vipSleep( v_sleeptime );    // milliseconds


	return VIPRET_NOT_IMPLEMENTED;
 }



/**
 * @brief  Display frame, data-copy routine. (optimized)
 *
 * @param[in] img VIPLib Cache24 Frame to be displayed.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 *
 * @note   Input operator (<<) call directly this function.
 * @see    operator << (vipFrameRGB24&)
 */
VIPRESULT vipOutputSample::importFrom(vipFrameRGB24& img)
 {
	INFO("int vipOutputSample::importFrom(vipFrameRGB24& img) [reading data]")

// image displaying routine


	//	if ( v_sleeptime && v_sleeptime > (long)getElaborationTime())
	//		vipUtility::vipSleep( v_sleeptime - (long)getElaborationTime() );
	vipUtility::vipSleep( v_sleeptime );    // milliseconds


	return VIPRET_NOT_IMPLEMENTED;
 }



/**
 * @brief  Display frame, conversion to vipFrameRGB24
 *         and single channel data-copy routine.
 *
 * @param[in] img VIPLib RGB Frame to be displayed.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 *
 * @note   Input operator (<<) call directly this function.
 * @see    operator << (vipFrameRGB96&)
 */
VIPRESULT vipOutputSample::importFrom(vipFrameRGB96& img)
 {
	INFO("int vipOutputSample::importFrom(vipFrameRGB96& img) [reading data]")

// image displaying routine
	//	if ( v_sleeptime && v_sleeptime > (long)getElaborationTime())
	//		vipUtility::vipSleep( v_sleeptime - (long)getElaborationTime() );
	vipUtility::vipSleep( v_sleeptime );    // milliseconds

	return VIPRET_NOT_IMPLEMENTED;
 }



/**
 * @brief  Display frame, conversion to vipFrameRGB24
 *         and single channel data-copy routine.
 *
 * @param[in] img VIPLib Grey Frame to be displayed.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 *
 * @note   Input operator (<<) call directly this function.
 * @see    operator << (vipFrameT<unsigned char>&)
 */
VIPRESULT vipOutputSample::importFrom(vipFrameT<unsigned char>& img)
 {
	INFO("int vipOutputSample::importFrom(vipFrameT<unsigned char>& img) [reading data]")

// image displaying routine


	//	if ( v_sleeptime && v_sleeptime > (long)getElaborationTime())
	//		vipUtility::vipSleep( v_sleeptime - (long)getElaborationTime() );
	vipUtility::vipSleep( v_sleeptime );    // milliseconds


	return VIPRET_NOT_IMPLEMENTED;
 }






