/** @file vipInput.cpp
 *
 * File containing methods for the 'vipInput' class.
 * The header for this class can be found in vipInput.h, check that file
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


 #include "vipInput.h"
 #include "vipUtility.h"


/**
 * @brief Included for clock() method, used to syncronize frame rate.
 * @see   getElaborationTime()
 * @see   setElaborationTime()
 */
#include <time.h>

//CLK_TCK
//CLOCKS_PER_SEC



/**
 * @brief Default constructor is protected, reset elaboration time offset
 *        and frame rate to given value (default is 0), constructor will
 *        be called from inherited class constructiors.
 *
 * @param fps Frame per second value, default is 0, the max (hardware) rate.
 */
vipInput::vipInput(float fps)
 {
	v_elab_start = 0;
	setFrameRate(fps);

	DEBUGMSG("vipInput::vipInput(float fps) [CONTRUCTOR] ", fps)
 }



/**
 * @brief Set frame rate to given value, acquisition process may be
 *        slower than theoretical frame rate.
 *
 * @param[in] fps Frame per second as a floating point value, 0 means max frame rate.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if fps is negative,
 *		   VIPRET_ILLEGAL_USE if frame rate setup is not available for this source.
 *
 * @note  Currently frame rate managment is implemented in output operators.
 *
 * @see   v_sleeptime
 * @see   v_framerate
 */
VIPRESULT vipInput::setFrameRate(float fps)
 {
	if (fps < 0.)
		return VIPRET_PARAM_ERR;

	v_framerate = fps;

	if ( fps == 0 )
		v_sleeptime = 0;
	else
		v_sleeptime = (long)( (float)1000 / fps ); // milliseconds

	DEBUGMSG("VIPRESULT vipInput::setFrameRate(float fps)", fps)

	return VIPRET_OK;
 }


/**
 * @brief Reset clock tick counter to current value, used as offset for
 *        getElaborationTime() method. Must be always called before getElaborationTime().
 *
 * @see   getElaborationTime()
 * @see   operator >> ()
 * @see   clock()
 */
inline void vipInput::setElaborationStart()
 {
	v_elab_start = clock();
 }

/**
 * @brief Return time elapsed from setElaborationStart() call, uses clock() method of <time.h>,
 *        CLK_TCK macro converts clock cycle count to seconds. (seconds * CLK_TCK = clock ticks count)
 *        The use of this method without a previous call of setElaborationStart() return a foolish value.
 *
 * @return Time elapsed in milliseconds.
 *
 * @see   setElaborationTime()
 * @see   operator >> ()
 * @see   clock()
 */
inline long vipInput::getElaborationTime()
 {
	return 1000 * (clock() - v_elab_start) / CLOCKS_PER_SEC;//CLK_TCK;
 }



/**
 * @brief Ouput operator, export to standard VIPLib frame formats, current implementation
 *        calls directly extractTo() method. If framerate (and so sleeptime) isn't zero
 *        process is stopped untile frame clock is syncronized, elaboration time is
 *        subtracted from sleeptime value, if greater no other delay is apllied.
 *
 * @param[out] img VIPLib Cache24 Frame to store data.
 *
 * @return Address of current instance.
 *
 * @see   importFrom(vipFrameRGB24&)
 * @see   vipsleep()
 * @see   setElaborationStart()
 * @see   getElaborationTime()
 */
vipInput& vipInput::operator >> (vipFrameRGB24& img)
 {
	INFO("vipInput& vipInput::operator >> (vipFrameYUV420& img) [pushing data]")

	setElaborationStart();

	extractTo(img);

	if ( v_sleeptime && v_sleeptime > (long)getElaborationTime())
		vipUtility::vipSleep( v_sleeptime - (long)getElaborationTime() );    // milliseconds

	DEBUG(getElaborationTime());
	return *this;
 }


/**
 * @brief Ouput operator, export to standard VIPLib frame formats, current implementation
 *        calls directly extractTo() method. If framerate (and so sleeptime) isn't zero
 *        process is stopped untile frame clock is syncronized, elaboration time is
 *        subtracted from sleeptime value, if greater no other delay is apllied.
 *
 * @param[out] img VIPLib Cache Frame to store data.
 *
 * @return Address of current instance.
 *
 * @see   importFrom(vipFrameYUV420&)
 * @see   vipsleep()
 * @see   setElaborationStart()
 * @see   getElaborationTime()
 */
vipInput& vipInput::operator >> (vipFrameYUV420& img)
 {
	INFO("vipInput& vipInput::operator >> (vipFrameYUV420& img) [pushing data]")

	setElaborationStart();

	extractTo(img);

	if ( v_sleeptime && v_sleeptime > (long)getElaborationTime())
		vipUtility::vipSleep( v_sleeptime - (long)getElaborationTime() );    // milliseconds

	DEBUG(getElaborationTime());
	return *this;
 }



/**
 * @brief Ouput operator, export to standard VIPLib frame formats, current implementation
 *        calls directly extractTo() method. If framerate (and so sleeptime) isn't zero
 *        process is stopped untile frame clock is syncronized, elaboration time is
 *        subtracted from sleeptime value, if greater no other delay is apllied.
 *        Added by Marco Verza.
 *
 * @param[out] img VIPLib Cache Frame to store data.
 *
 * @return Address of current instance.
 *
 * @see   importFrom(vipFrameYUV420&)
 * @see   vipsleep()
 * @see   setElaborationStart()
 * @see   getElaborationTime()
 */
vipInput& vipInput::operator >> (vipFrameYUV444& img)
 {
	INFO("vipInput& vipInput::operator >> (vipFrameYUV444& img) [pushing data]")

	setElaborationStart();

	extractTo(img);

	if ( v_sleeptime && v_sleeptime > (long)getElaborationTime())
		vipUtility::vipSleep( v_sleeptime - (long)getElaborationTime() );    // milliseconds

	DEBUG(getElaborationTime());
	return *this;
 }



/**
 * @brief Ouput operator, export to standard VIPLib frame formats, current implementation
 *        calls directly extractTo() method. If framerate (and so sleeptime) isn't zero
 *        process is stopped untile frame clock is syncronized, elaboration time is
 *        subtracted from sleeptime value, if greater no other delay is apllied.
 *
 * @param[out] img VIPLib Cache Frame to store data.
 *
 * @return Address of current instance.
 *
 * @see   importFrom(vipFrameYUV420&)
 * @see   vipsleep()
 * @see   setElaborationStart()
 * @see   getElaborationTime()
 */
vipInput& vipInput::operator >> (vipFrameT<unsigned char>& img)
 {
	INFO("vipInput& vipInput::operator >> (vipFrameT& img) [pushing data]")

	setElaborationStart();

	extractTo(img);

	if ( v_sleeptime && v_sleeptime > (long)getElaborationTime())
		vipUtility::vipSleep( v_sleeptime - (long)getElaborationTime() );    // milliseconds

	DEBUG(getElaborationTime());
	return *this;
 }


