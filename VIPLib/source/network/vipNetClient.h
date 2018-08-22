/** @file    vipNetClient.h
 *  @class   vipNetClient
 *
 *  @brief   This class may be very useful during filter's implementation
 *           and testing, frame rate statistics, base image analisis.
 *
 *
 *  @bug
 *  @warning
 *  @todo    image and frame statistics !
 *
 *  @see     vipOutput
 *  @example ../../tests/test_vipNetClient.cpp
 *
 *  @version 0.76
 *  @date    17/08/2005
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




/*
pure theorical
^^^^^^^^^^^^^^^

	LAN 100 Mbps	(12,5 Mb/s = 12800 Kb/s = 13107200 bytes/s)


	320*240 *3 *char	= 230400 bytes 		-> MAX 56.888 fps

	320*320 *3 *char	= 307200 bytes 		-> MAX 42.666 fps

	640*480 *3 *char	= 921600 bytes 		-> MAX 14.222 fps




*/



#ifndef __VIPLIB_VIPNETCLIENT_H__
 #define __VIPLIB_VIPNETCLIENT_H__

 #include "../vipDefs.h"
 #include "../vipOutput.h"

 #include "../vipFrameCache.h"
 #include "../vipFrameCache24.h"
 #include "../vipFrameRGB.h"
 #include "../vipFrameGrey.h"

 #include <time.h>	// clock()


class vipNetClient :  public vipOutput
 {

	protected:

		/**
		 * @var   Stores current Run Mode as index in RUNMODE enum.
		 * @see   RUNMODE;
		 */
		int runmode;

		/**
		 * @var   Stores time to wait after processing when using input operators.
		 * @see   operator << ()
		 * @see   setInputFrameRateDelay(long)
		 */
		long v_sleeptime;

		/**
		 * @var   Stores frame count.
		 * @see   updateFps()
		 */
		long frameCount;

		/**
		 * @var   Stores last frame time offset, used for calculating interval.
		 * @see   updateFps()
		 * @see   updateExtime()
		 */
		clock_t lastFrameTime;

		/**
		 * @var   Stores last frame rate.
		 * @see   updateFps()
		 */
		float lastFps;

		/**
		 * @var   Stores average frame rate.
		 * @see   updateFps()
		 */
		float mediumFps;

		/**
		 * @var   Stores last frame processing time in milliseconds.
		 * @see   updateExtime()
		 */
		long lastExTime;

		/**
		 * @var   Stores average processing time in milliseconds.
		 * @see   updateExtime()
		 */
		long mediumExTime;

		/**
		 * @brief Updates last frame rate time and average.
		 */
		void updateFps();

		/**
		 * @brief Updates last processing (analyzing) time and average.
		 */
		void updateExtime();

	public:

		/**
		 * @var   Enumerate available run-modes.
		 */
		enum RUNMODE { FPS_STAT, IMG_STAT };

		/**
		 * @brief Default constructor initializes variables.
		 *
		 * @param mode set current processing mode, default is frame rate stats only.
		 */
		vipNetClient(RUNMODE mode = vipNetClient::FPS_STAT);


		/**
		 * @brief  Currently not used.
		 * @return VIPRET_NOT_IMPLEMENTED
		 */
		int run() { return VIPRET_NOT_IMPLEMENTED; };

		/**
		 * @brief  Set current canvas' height.
		 *
		 * @return height in pixel.
		 */
		int setHeight(unsigned int value) { return VIPRET_NOT_IMPLEMENTED; };

		/**
		 * @brief  Set current canvas' width.
		 *
		 * @return width in pixel.
		 */
		int setWidth(unsigned int value) { return VIPRET_NOT_IMPLEMENTED; };



		/**
		 * @brief Reset class variables for new statistics, by default it doesn't
		 *        start frame rate counter.
		 *
		 * @param[in] startTimers if true start the frame rate counter, useful
		 *                        for single frame processing performace test.
		 * @see   lastFrameTime, lastExTime, lastFps, mediumFps, mediumExTime
		 */
		int reset(bool startTimers = false);

		/**
		 * @brief  Set display frame rate (elaboration time is not subtracted).
		 *
		 * @param[in] frames per second (default is 0, no sleep)
		 *
		 * @return VIPRET_PARAM_ERR if fps is lower than 0, VIPRET_OK else.
		 * @see    v_sleeptime
		 */
		int setInputFrameRate(float fps = 0);

		/**
		 * @brief Read current input frame delay.
		 *
		 * @return delay time in milliseconds.
		 * @see   sleeptime
		 */
		long getInputFrameRateDelay() { return v_sleeptime; };

		/**
		 * @brief Read last frame rate.
		 *
		 * @return frame rate as floating point value.
		 * @see   lastFps
		 */
		float getInputFrameRateCurrent() const { return lastFps; };

		/**
		 * @brief Read average frame rate. ( SUM(frames) / framecount )
		 *
		 * @return frame rate as floating point value.
		 * @see   mediumFps
		 */
		float getInputFrameRateAverage() const { return mediumFps; };

		/**
		 * @brief Read last processing time in milliseconds, it's execution time
		 *        of importFrom() method, if current RUNMODE is FPS_STAT return
		 *        zero because frames are not processed.
		 *
		 * @return last processing time in milliseconds
		 * @see   lastExTime
		 */
		long getExecutionTimeCurrent() const { return lastExTime; };

		/**
		 * @brief Read average processing time in milliseconds, it's execution time
		 *        of importFrom() method, if current RUNMODE is FPS_STAT return
		 *        zero because frames are not processed.
		 *
		 * @return last processing time in milliseconds ( SUM(exTimes) / framecount )
		 * @see   mediumExTime
		 */
		long getExecutionTimeAverage() const { return mediumExTime; };



		long getElapsedTime() const;


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
		int importFrom(vipFrameCache& img);

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
		int importFrom(vipFrameCache24& img);

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
		int importFrom(vipFrameRGB& img);

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
		int importFrom(vipFrameGrey& img);



		/**
		 * @brief Input operator, import standard VIPLibb frame formats,
		 *        current implementation calls directly importFrom() method
		 *        or gather only frame statistics if RUNMODE is FPS_STAT.
		 *
		 * @param[in] img VIPLibb Cache Frame to be processed (analyzed)
		 *
		 * @see   importFrom(vipFrameCache&)
		 */
		void operator << (vipFrameCache& img);
		/**
		 * @brief Input operator, import standard VIPLibb frame formats,
		 *        current implementation calls directly importFrom() method
		 *        or gather only frame statistics if RUNMODE is FPS_STAT.
		 *
		 * @param[in] img VIPLibb Cache24 Frame to be processed (analyzed)
		 *
		 * @see   importFrom(vipFrameCache24&)
		 */
		void operator << (vipFrameCache24& img);
		/**
		 * @brief Input operator, import standard VIPLibb frame formats,
		 *        current implementation calls directly importFrom() method.
		 *        or gather only frame statistics if RUNMODE is FPS_STAT.
		 *
		 * @param[in] img VIPLibb RGB Frame to be processed (analyzed)
		 *
		 * @see   importFrom(vipFrameRGB&)
		 */
		void operator << (vipFrameRGB& img);
		/**
		 * @brief Input operator, import standard VIPLibb frame formats,
		 *        current implementation calls directly importFrom() method.
		 *        or gather only frame statistics if RUNMODE is FPS_STAT.
		 *
		 * @param[in] img Greyscale VIPLibb Frame to be processed (analyzed)
		 *
		 * @see   importFrom(vipFrameGrey&)
		 */
		void operator << (vipFrameGrey& img);



};

#endif //__VIPLIB_VIPNETCLIENT_H__
