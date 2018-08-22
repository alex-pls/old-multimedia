/**
 *  @class   vipOuputVoid
 *
 *  @brief   A simple class that emulate NULL output of Linux (/dev/null).
 *
 *
 *  @bug
 *  @warning
 *  @todo
 *
 *  @see     vipOutput
 *
 *  @version 1.0.0
 *  @date    02/08/2005
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



#ifndef __VIPLIB_VIPOUTPUTVOID_H__
 #define __VIPLIB_VIPOUTPUTVOID_H__

 #include "../vipDefs.h"
 #include "../vipOutput.h"

 #include "../vipFrameYUV420.h"
 #include "../vipFrameRGB24.h"
 #include "../vipFrameT.h"


class vipOutputVoid :  public vipOutput
 {

	protected:

		/**
		 * @brief If true frames are deleted after importing.
		 *        default is false.
		 */
		bool clearMemory;

		/**
		 * @brief millisec to wait before returning program control.
		 */
		long v_sleeptime;

	public:


		/**
		 * @brief Default constructor initializes variables.
		 *
		 * @param deleteFrames if true, frames are deleted, nothing is done else.
		 */
		vipOutputVoid(bool deleteFrames = false);


		/**
		 * @brief  Currently not used.
		 * @return VIPRET_NOT_IMPLEMENTED
		 */
		VIPRESULT run() { return VIPRET_NOT_IMPLEMENTED; };


		/**
		 * @brief  Set cleaning mode on/off.
		 *
		 * @param[in] value if true, frames are deleted, nothing is done else.
		 */
		void setFrameMemoryClearEnabled(bool value = true) { clearMemory = true; };

		/**
		 * @brief  check if frames are cleaned (deleted).
		 *
		 * @return true if after importing frames are cleared (deleted).
		 */
		bool isFrameMemoryClearEnabled() { return clearMemory; };

		/**
		 * @brief  Set display frame rate (elaboration time is not subtracted).
		 *
		 * @param[in] frames per second (default is 0, no sleep)
		 *
		 * @return VIPRET_PARAM_ERR if fps is lower than 0, VIPRET_OK else.
		 * @see    v_sleeptime
		 */
		VIPRESULT setInputFrameRate(float fps = 0);

		/**
		 * @brief  Read current input frame delay.
		 *
		 * @return delay time in milliseconds.
		 * @see    v_sleeptime
		 */
		long getInputFrameRateDelay() { return v_sleeptime; };


		/**
		 * @brief  Set current canvas' height.
		 *
		 * @return height in pixel.
		 */
		VIPRESULT setHeight(unsigned int value) { return VIPRET_NOT_IMPLEMENTED; };

		/**
		 * @brief  Set current canvas' width.
		 *
		 * @return width in pixel.
		 */
		VIPRESULT setWidth(unsigned int value) { return VIPRET_NOT_IMPLEMENTED; };



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
		VIPRESULT importFrom(vipFrameYUV420& img);

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
		VIPRESULT importFrom(vipFrameRGB24& img);


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
		VIPRESULT importFrom(vipFrameT<unsigned char>& img);


};

#endif //__VIPLIB_VIPOUTPUTVOID_H__
