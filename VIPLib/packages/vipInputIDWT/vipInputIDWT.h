/** @file    vipInputIDWT.h
 *  @class   vipInputIDWT
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
 *  @date    28/02/2008 10.17.35
 *  @author  Valentina Pasqualino
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



#ifndef __VIPLIB_VIPINPUT_TEST_H__
 #define __VIPLIB_VIPINPUT_TEST_H__

//respect ./source/inputs or ./packages/inputs directory
 #include "../../source/vipDefs.h"
 #include "../../source/vipInput.h"

 #include "../../source/vipFrameRGB24.h"
 #include "../../source/vipFrameYUV420.h"
 #include "../../source/vipFrameT.h"
 #include "../../source/math/vipMatrix.h"

 #define VIPPFG_DEF_COLOR_R		0 // |
 #define VIPPFG_DEF_COLOR_G		0 // |>black
 #define VIPPFG_DEF_COLOR_B		0 // |



class vipInputIDWT : public vipInput
 {
	protected:


		/**
		 * @brief  Background RGB pixel color.
		 */
		PixelRGB24 bgRGB;

		/**
		 * @brief  Dest Image.
		 */
		vipFrameRGB24 *source;
		
		/**
		 * @brief  Canvas' width.
		 */
		unsigned int width;
		/**
		 * @brief  Canvas' height.
		 */
		unsigned int height;
		/**
		* @number of iterations to be performed
		*/
		unsigned int iteration;

		/**
		 * @brief filter to be used in the IDWT transform.
		 *  0 = 3(low filter),5(height filter) and 1 = 7(low filter),9(height filter)
		 */
		unsigned int filter;




	public:


		/**
		 * @brief  Default constructor, frame rate
		 *         is managed by vipInput class.
		 *
		 * @param[in] fps frame rate, default is 0: max possible
		 */
		vipInputIDWT(float fps = 0);




		/**
		 * @brief  Default constructor initialize background, frame rate
		 *         is managed by vipInput class.
		 *
		 * @param[in] background RGB pixel
		 * @param[in] fps frame rate, default is 0: max possible
		 */
		/*vipInputIDWT::vipInputIDWT(PixelRGB24& background, float fps) : vipInput(fps)
		 {
			DEBUGMSG("vipInputIDWT::vipInputIDWT(PixelRGB24& background, float fps) : vipInput(fps) [CONTRUCTOR]", background)
			reset();
			bgRGB  = background;
		 }*/

		vipInputIDWT::vipInputIDWT(vipFrameRGB24 *src, float fps) : vipInput(fps)
		 {
			DEBUGMSG("vipInputIDWT::vipInputIDWT(PixelRGB24& background, float fps) : vipInput(fps) [CONTRUCTOR]", background)
			reset();
			source  = src;
			
		 }

		/**
		 * @brief  Default destructor, disconnect device and delete buffer.
		 */
		~vipInputIDWT();



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
		 * @brief set number of iterations to perform.
		 * 
		 * @param[in] number of iterations
		 */
		void setIteration(unsigned int iter)
		{
			
			iteration= iter;

		};



		/**
		 * @brief  number of the filters to use in the DWT transform.
		 * 
		 * @param[in] filter code:
		 *  0 = 3(low filter),5(height filter) and 1 = 7(low filter),9(height filter) 
		 */
		void setFilter(unsigned int f)
		{

			filter = f;

		};



		/**
		 * @brief  Set current RGB background.
		 *
		 * @param[in] background RGB pixel
		 */
		void setFrameColor(PixelRGB24& background) { bgRGB = background; };




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
		 * @param[out] img VIPLib Cache Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid.
		 *
		 * @note   Ouput operator (>>) call directly this function.
		 * @see    operator >> (vipFrameYUV444&)
		 */
		VIPRESULT extractTo(vipFrameYUV444& img);

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
		 * @brief  Create a new frame from DWT Coefficients.
		 *
		 * @param[out] img Greyscale VIPLib Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid.
		 *
		 * @note   Ouput operator (>>) call directly this function.
		 * @see    operator >> (vipMatrix<double>&)
		 */
		VIPRESULT extractTo(vipFrameT<unsigned char>& img);



 };



#endif	// __VIPLIB_VIPINPUT_TEST_H__
