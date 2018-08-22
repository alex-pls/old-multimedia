/**
 *  @class   vipInput
 *
 *  @brief   Abstract class for all data input, implementations should
 *           decode stream from a device (capture or storage for example)
 *           and convert to VIPLib standard formats, inherited classes must
 *           implement data extraction throw extractTo() methods, base
 *           extraction operators (>>) call these functions for output,
 *           if frameRate is different from 0, after extractTo() call, process
 *           will stop for (1/fps)-(extractTo() execution time) seconds.
 *           This base implementation of operators and timer managment has
 *           been coded for low-complex data sources, inherited classes may
 *           obviously override current operators behaviour.
 *
 *  @bug
 *  @warning
 *  @todo
 *
 *  @see
 *
 *  @version 1.0.2
 *  @date    24/12/2005
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


#ifndef __VIPLIB_VIPINPUT_H__
 #define __VIPLIB_VIPINPUT_H__

 #include "vipDefs.h"
 #include "vipFrameYUV420.h"
 #include "vipFrameYUV444.h" // added by Marco Verza
 #include "vipFrameRGB24.h"
 #include "vipFrameT.h"

/**
 * @brief Included for clock() method, used to syncronize frame rate.
 * @see   getElaborationTime()
 * @see   setElaborationTime()
 */
#include <time.h>

//CLK_TCK
//CLOCKS_PER_SEC

class vipInput
 {

	protected:

		/**
		 * @var   Stores given frame rate value, it isn't directly used by
		 *        clock routines, but converted to relative interval in milliseconds.
		 *
		 * @see   v_sleeptime
		 */
		float v_framerate;

		/**
		 * @var   Stores interval lenght in milliseconds, it's directly used by
		 *        clock routines and updated by setFrameRate().
		 *
		 * @see   setFrameRate(float)
		 */
		long v_sleeptime;

		/**
		 * @var   Stores clock tick offset, updated by setElaborationStart() and
		 *        used by getElaborationTime().
		 *
		 * @see   setElaborationStart()
		 * @see   getElaborationTime()
		 */
		clock_t v_elab_start;

		/**
		 * @brief Reset clock tick counter to current value, used as offset for
		 *        getElaborationTime() method. Must be always called before get..().
		 *
		 * @see   getElaborationTime()
		 * @see   operator >> ()
		 * @see   clock()
		 */
		inline void setElaborationStart();

		/**
		 * @brief Return time elapsed from setElaborationStart() call, uses
		 *        clock() method of <time.h>, CLK_TCK macro converts clock cycle
		 *        count to seconds. The use of this method without a previous call of
		 *        setElaborationStart() return a foolish value.
		 *
		 * @return Time elapsed in milliseconds.
		 *
		 * @see   setElaborationTime()
		 * @see   operator >> ()
		 * @see   clock()
		 */
		inline long getElaborationTime();


	public:


		/**
		 * @brief Default constructor is protected because this is an
		 *        abstract class and instance cannot be created directly.
		 *
		 * @param fps Frame per second value, default is 0, the max (hardware) rate.
		 */
		vipInput(float fps = 0);


		virtual ~vipInput() { }

		/**
		 * @brief  Get current canvas' height.
		 *
		 * @return height in pixel.
		 */
		virtual unsigned int getHeight() const = 0;

		/**
		 * @brief  Get current canvas' width.
		 *
		 * @return width in pixel.
		 */
		virtual unsigned int getWidth() const = 0;


// getPreferredFormat



		/**
		 * @brief  Reset the module.
		 *
		 * @return VIPRET_INTERNAL_ERR if any error occur, VIPRET_OK else.
		 */
		virtual VIPRESULT reset() = 0;

		/**
		 * @brief  Get the state of current data source.
		 *
		 * @return true is there are no more frames to load, false else.
		 */

		virtual bool EoF() = 0;




		/**
		 * @brief Read current frame rate (frame per second)
		 *
		 * @return Frame per second as a floating point value. (delay=1/fps)
		 *
		 * @see   v_sleeptime
		 */
		float getFrameRate() const { return v_framerate; };

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
		VIPRESULT setFrameRate(float fps);



		/**
		 * @brief Inherited class must implement this function, processing
		 *        hardware/format specific stream to standard VIPLib frame formats.
		 *
		 * @param[out] img VIPLib Cache Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note  Ouput operator (>>) call directly this function.
		 * @see   operator >> (vipFrameYUV420&)
		 */
		virtual VIPRESULT extractTo(vipFrameYUV420& img) = 0;


		/**
		 * @brief Inherited class must implement this function, processing
		 *        hardware/format specific stream to standard VIPLib frame formats.
		 *        Added by Marco Verza.
		 *
		 * @param[out] img VIPLib Cache Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note  Output operator (>>) call directly this function.
		 * @see   operator >> (vipFrameYUV444&)
		 */
		virtual VIPRESULT extractTo(vipFrameYUV444& img) = 0;


		/**
		 * @brief Inherited class must implement this function, processing
		 *        hardware/format specific stream to standard VIPLib frame formats.
		 *
		 * @param[out] img VIPLib Cache24 Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note  Ouput operator (>>) call directly this function.
		 * @see   operator >> (vipFrameRGB24&)
		 */
		virtual VIPRESULT extractTo(vipFrameRGB24& img) = 0;

		/**
		 * @brief Inherited class must implement this function, processing
		 *        hardware/format specific stream to standard VIPLib frame formats.
		 *
		 * @param[out] img Greyscale VIPLib Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note  Ouput operator (>>) call directly this function.
		 * @see   operator >> (vipFrameT&)
		 */
		virtual VIPRESULT extractTo(vipFrameT<unsigned char>& img) = 0;


		/**
		 * @brief Ouput operator, export to standard VIPLib frame formats,
		 *        current implementation calls directly extractTo() method
		 *        and if framerate isn't zero waits untill clock is syncronized,
		 *        if elaboration time is greater than sleeptime, no delay is applied.
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
		vipInput& operator >> (vipFrameYUV420& img);



		/**
		 * @brief Ouput operator, export to standard VIPLib frame formats,
		 *        current implementation calls directly extractTo() method
		 *        and if framerate isn't zero waits untill clock is syncronized,
		 *        if elaboration time is greater than sleeptime, no delay is applied.
		 *        Added by Marco Verza.
		 *
		 * @param[out] img VIPLib Cache Frame to store data.
		 *
		 * @return Address of current instance.
		 *
		 * @see   importFrom(vipFrameYUV444&)
		 * @see   vipsleep()
		 * @see   setElaborationStart()
		 * @see   getElaborationTime()
		 */
		vipInput& operator >> (vipFrameYUV444& img);


		/**
		 * @brief Ouput operator, export to standard VIPLib frame formats,
		 *        current implementation calls directly extractTo() method
		 *        and if framerate isn't zero waits untill clock is syncronized,
		 *        if elaboration time is greater than sleeptime, no delay is applied.
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
		vipInput& operator >> (vipFrameRGB24& img);

		/**
		 * @brief Ouput operator, export to standard VIPLib frame formats,
		 *        current implementation calls directly extractTo() method
		 *        and if framerate isn't zero waits untill clock is syncronized,
		 *        if elaboration time is greater than sleeptime, no delay is applied.
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
		vipInput& operator >> (vipFrameT<unsigned char>& img);



		/**
		 * @brief  Ignore this, it's a class-type definition, mostly used
		 *         by VIPLib WorkShop, sintax is a bit more complex than
		 *         usual because of a VC6 BUG, it's the same as:
		 *         const int vipClassType = VIPCLASS_TYPE_INPUT;
		 */
		enum{ vipClassType = VIPCLASS_TYPE_INPUT };

};


#endif //__VIPLIB_VIPINPUT_H__


