/** @file    vipOutputSample.h
 *  @class   vipOutputSample
 *
 *  @brief
 *
 *
 *
 *
 *  @bug
 *  @warning
 *  @todo
 *
 *  @see     vipOutput
 *
 *  @version 1.0
 *  @date    19/05/2006 7.25.31
 *  @author  Alessandro Polo
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



#ifndef __VIPLIB_VIPOUTPUTSAMPLE_H__
 #define __VIPLIB_VIPOUTPUTSAMPLE_H__


//respect ./source/motion or ./packages/filters directory
 #include "I:\Projects\Software\VIPLib\source\vipDefs.h"
 #include "I:\Projects\Software\VIPLib\source\vipOutput.h"
 #include "I:\Projects\Software\VIPLib\source\vipFrameYUV420.h"
 #include "I:\Projects\Software\VIPLib\source\vipFrameRGB24.h"
 #include "I:\Projects\Software\VIPLib\source\vipFrameT.h"

 #include "I:\Projects\Software\VIPLib\source\vipFrameRGB96.h"



 /**
  * @brief  Deafult window's width.
  */
 #define VIPOUTPUTSAMPLE_DEF_WIDTH	320
 /**
  * @brief  Deafult window's height.
  */
 #define VIPOUTPUTSAMPLE_DEF_HEIGHT	240



class vipOutputSample :  public vipOutput
 {

	protected:


		/**
		 * @brief  Canvas' width.
		 */
		unsigned int width;
		/**
		 * @brief  Canvas' height.
		 */
		unsigned int height;

		/**
		 * @brief  Milliseconds to wait after frame (re)drawing.
		 */
		long v_sleeptime;

		/**
		 * @brief  Initialize canvas.
		 * @return VIPRET_OK
		 */
		VIPRESULT init();



	public:


		/**
		 * @brief  Default constructor initializes variables and canvas.
		 *
		 */
		vipOutputSample();



		/**
		 * @brief  Default constructor initializes variables.
		 *
		 * @param[in] width Canvas' width.
		 * @param[in] height Canvas' height.
		 *
		 */
		vipOutputSample(unsigned int width, unsigned int height);



		/**
		 * @brief  Default destructor, wait for pending events and flush.
		 */
		~vipOutputSample();




		/**
		 * @brief  Show canvas.
		 *
		 * @return VIPRET_OK
		 */
		VIPRESULT show();



		/**
		 * @brief  Hide canvas.
		 *
		 * @return VIPRET_OK
		 */
		VIPRESULT hide();



		/**
		 * @brief  Set display frame rate (elaboration time is not subtracted).
		 *
		 * @param[in] frames per second (default is 0, no sleep)
		 *
		 * @return VIPRET_PARAM_ERR if fps is lower than 0, VIPRET_OK else.
		 */
		int setFrameRate(float fps = 0);




		/**
		 * @brief  Set current canvas' height.
		 *
		 * @return height in pixel.
		 */
		VIPRESULT setHeight(unsigned int value)
		 {

			height = value;

			return VIPRET_NOT_IMPLEMENTED;
		 };



		/**
		 * @brief  Set current canvas' width.
		 *
		 * @return width in pixel.
		 */
		VIPRESULT setWidth(unsigned int value)
		 {

			width = value;

			 return VIPRET_NOT_IMPLEMENTED;
		 };




		/**
		 * @brief  Get current canvas' width.
		 *
		 * @return width in pixel.
		 */
		unsigned int getWidth() const { return width; };



		/**
		 * @brief  Get current canvas' height.
		 *
		 * @return height in pixel.
		 */
		unsigned int getHeight() const { return height; };



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
		int importFrom(vipFrameYUV420& img);




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
		VIPRESULT importFrom(vipFrameRGB24& img);




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
		VIPRESULT importFrom(vipFrameRGB96& img);




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
		VIPRESULT importFrom(vipFrameT<unsigned char>& img);




		/**
		 * @brief  Input operator, import standard VIPLib frame formats,
		 *         current implementation calls directly importFrom() method.
		 *
		 * @param[in] img VIPLib Cache Frame to be displayed.
		 *
		 * @note   Overloaded because we add vipFrameRGB support and all
		 *         operators need to (re)defined.
		 * @see    importFrom(vipFrameYUV420&)
		 */
		void operator << (vipFrameYUV420& img) { importFrom(img); };

		/**
		 * @brief  Input operator, import standard VIPLib frame formats,
		 *         current implementation calls directly importFrom() method.
		 *
		 * @param[in] img VIPLib Cache24 Frame to be displayed.
		 *
		 * @note   Overloaded because we add vipFrameRGB support and all
		 *         operators need to (re)defined.
		 * @see    importFrom(vipFrameRGB24&)
		 */
		void operator << (vipFrameRGB24& img) { importFrom(img); };

		/**
		 * @brief  Input operator, import standard VIPLib frame formats,
		 *         current implementation calls directly importFrom() method.
		 *
		 * @param[in] img VIPLib RGB Frame to be displayed.
		 *
		 * @note   Overloaded because we add vipFrameRGB96 support and all
		 *         operators need to (re)defined.
		 * @see    importFrom(vipFrameRGB96&)
		 */
		void operator << (vipFrameRGB96& img) { importFrom(img); };

		/**
		 * @brief  Input operator, import standard VIPLib frame formats,
		 *         current implementation calls directly importFrom() method.
		 *
		 * @param[in] img VIPLib Grey Frame to be displayed.
		 *
		 * @note   Overloaded because we add vipFrameRGB support and all
		 *         operators need to (re)defined.
		 * @see    importFrom(vipFrameT<unsigned char>&)
		 */
		void operator << (vipFrameT<unsigned char>& img) { importFrom(img); };


};

#endif //__VIPLIB_VIPOUTPUTSAMPLE_H__
