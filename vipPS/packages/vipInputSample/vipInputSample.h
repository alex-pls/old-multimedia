/** @file    vipInputSample.h
 *  @class   vipInputSample
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
 *  @see     vipInput
 *
 *  @version 1.0
 *  @date    19/05/2006 7.25.41
 *  @author  Alessandro Polo
 *
 ****************************************************************************
 *  Class based on Package Studio template: vipInputTemplate version 0.9.12
 ****************************************************************************
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.science.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DIT - University of Trento
 *
 ****************************************************************************/



#ifndef __VIPLIB_VIPINPUTSAMPLE_H__
 #define __VIPLIB_VIPINPUTSAMPLE_H__

//respect ./source/inputs or ./packages/inputs directory
 #include "I:\Projects\Software\VIPLib\source\vipDefs.h"
 #include "I:\Projects\Software\VIPLib\source\vipInput.h"

 #include "I:\Projects\Software\VIPLib\source\vipFrameRGB24.h"
 #include "I:\Projects\Software\VIPLib\source\vipFrameYUV420.h"
 #include "I:\Projects\Software\VIPLib\source\vipFrameT.h"


 #define VIPPFG_DEF_COLOR_R		0 // |
 #define VIPPFG_DEF_COLOR_G		0 // |>black
 #define VIPPFG_DEF_COLOR_B		0 // |



class vipInputSample : public vipInput
 {
	protected:


		/**
		 * @brief  Background RGB pixel color.
		 */
		PixelRGB bgRGB;

		/**
		 * @brief  Canvas' width.
		 */
		unsigned int width;
		/**
		 * @brief  Canvas' height.
		 */
		unsigned int height;




	public:


		/**
		 * @brief  Default constructor, frame rate
		 *         is managed by vipInput class.
		 *
		 * @param[in] fps frame rate, default is 0: max possible
		 */
		vipInputSample(float fps = 0);




		/**
		 * @brief  Default constructor initialize background, frame rate
		 *         is managed by vipInput class.
		 *
		 * @param[in] background RGB pixel
		 * @param[in] fps frame rate, default is 0: max possible
		 */
		vipInputSample::vipInputSample(PixelRGB& background, float fps) : vipInput(fps)
		 {
			DEBUGMSG("vipInputSample::vipInputSample(PixelRGB& background, float fps) : vipInput(fps) [CONTRUCTOR]", background)
			reset();
			bgRGB  = background;
		 }



		/**
		 * @brief  Default destructor, disconnect device and delete buffer.
		 */
		~vipInputSample();



		/**
		 * @brief  Reset current background pixels to defaults.
		 */
		VIPRESULT reset();




		/**
		 * @brief  Get the state of current data source.
		 *
		 * @return true is there are no more frames to load, false else.
		 */
		bool EoF();




		/**
		 * @brief  Read current image's width.
		 *
		 * @return Width in pixel.
		 */
		unsigned int getWidth() const
		 {

			return width;

		 };



		/**
		 * @brief  Read current image's height.
		 *
		 * @return Height in pixel.
		 */
		unsigned int getHeight() const
		 {

			return height;

		 };





		/**
		 * @brief  Set current RGB background.
		 *
		 * @param[in] background RGB pixel
		 */
		void setFrameColor(PixelRGB& background) { bgRGB = background; };




		/**
		 * @brief  Create/capture a new frame with current settings.
		 *
		 * @param[out] img VIPLib Cache Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid.
		 *
		 * @note   Ouput operator (>>) call directly this function.
		 * @see    operator >> (vipFrameYUV420&)
		 */
		VIPRESULT extractTo(vipFrameYUV420& img);



		/**
		 * @brief  Create/capture a new frame with current settings.
		 *
		 * @param[out] img VIPLib Cache24 Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid.
		 *
		 * @note   Ouput operator (>>) call directly this function.
		 * @see    operator >> (vipFrameRGB24&)
		 */
		VIPRESULT extractTo(vipFrameRGB24& img);



		/**
		 * @brief  Create/capture a new frame with current settings.
		 *
		 * @param[out] img Greyscale VIPLib Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid.
		 *
		 * @note   Ouput operator (>>) call directly this function.
		 * @see    operator >> (vipFrameT<unsigned char>&)
		 */
		VIPRESULT extractTo(vipFrameT<unsigned char>& img);



 };



#endif	// __VIPLIB_VIPINPUTSAMPLE_H__
