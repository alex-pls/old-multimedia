/**
 *  @class   vipPlainFrameGenerator
 *
 *  @brief   Plain image (same value for all pixel) generator.
 *
 *
 *  @bug
 *  @warning
 *  @todo
 *
 *  @see     vipInput
 *  @example ../../tests/test_vipPlainFrameGenerator.cpp
 *
 *  @version 0.8
 *  @date    30/07/2005
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



#ifndef __VIPLIB_VIPPLAINFRAMEGENERATOR_H__
 #define __VIPLIB_VIPPLAINFRAMEGENERATOR_H__

 #include "../vipDefs.h"
 #include "../vipInput.h"

 #include "../vipFrameYUV420.h"
 #include "../vipFrameRGB24.h"
 #include "../vipFrameT.h"
 #include "../vipFrameGrey.h"

 #define VETPFG_DEF_COLOR_GREY	0 //  black
 #define VETPFG_DEF_COLOR_R		0 // |
 #define VETPFG_DEF_COLOR_G		0 // |>black
 #define VETPFG_DEF_COLOR_B		0 // |
 #define VETPFG_DEF_COLOR_Y		0 // |
 #define VETPFG_DEF_COLOR_U		0 // |>black
 #define VETPFG_DEF_COLOR_V		0 // |



class vipPlainFrameGenerator : public vipInput
 {

 protected:

		/**
		 * @brief Our YUV buffer.
		 */
		vipFrameYUV420* bufferYUV;

		/**
		 * @brief Our RGB buffer.
		 */
		vipFrameRGB24* bufferRGB;

		/**
		 * @brief Our "Template" buffer.
		 */
		vipFrameT<unsigned char>* bufferTuC;



		void releaseBuffers();

 public:

		/**
		 * @brief  Default constructor, frame rate
		 *         is managed by vipInput class.
		 *
		 * @param[in] fps frame rate, default is 0: max possible
		 */
		vipPlainFrameGenerator(float fps = 0);

		/**
		 * @brief  Default constructor initialize background, frame rate
		 *         is managed by vipInput class.
		 *
		 * @param[in] background RGB pixel
		 * @param[in] fps frame rate, default is 0: max possible
		 */
		vipPlainFrameGenerator(PixelRGB96& background, float fps = 0);

		/**
		 * @brief  Default constructor initialize variables and connect.
		 *         to device if asked.
		 *
		 * @param[in] background greyscale pixel
		 * @param[in] fps frame rate, default is 0: max possible
		 */
		vipPlainFrameGenerator(PixelGrey& background, float fps = 0);




		~vipPlainFrameGenerator();




		/**
		 * @brief  Reset current background pixels to defaults.
		 */
		VIPRESULT reset();





		/**
		 * @brief  Update and set current buffer (vipFrameYUV420) to new size.
		 * @param[in] width new buffer's width.
		 * @param[in] height new buffer's height.
		 */
		void useBufferYUV(unsigned int width, unsigned int height);

		/**
		 * @brief  Update and set current buffer (vipFrameRGB24) to new size.
		 * @param[in] width new buffer's width.
		 * @param[in] height new buffer's height.
		 */
		void useBufferRGB(unsigned int width, unsigned int height);

		/**
		 * @brief  Update and set current buffer (vipFrameT<uchar>) to new size.
		 * @param[in] width new buffer's width.
		 * @param[in] height new buffer's height.
		 */
		void useBufferTuC(unsigned int width, unsigned int height, vipFrame::VIPFRAME_PROFILE profile);

		/**
		 * @brief  Evaluate is current buffer is a vipFrameYUV420.
		 *
		 * @return true is this is the current buffer, false else.
		 */
		bool isBufferYUV() { if ( bufferYUV != NULL ) return true; return false; };

		/**
		 * @brief  Evaluate is current buffer is a vipFrameRGB24.
		 *
		 * @return true is this is the current buffer, false else.
		 */
		bool isBufferRGB() { if ( bufferRGB != NULL ) return true; return false; };

		/**
		 * @brief  Evaluate is current buffer is a vipFrameT<uchar>.
		 *
		 * @return true is this is the current buffer, false else.
		 */
		bool isBufferTuC() { if ( bufferTuC != NULL ) return true; return false; };







		/**
		 * @brief  Set current RGB background.
		 *
		 * @param[in] background RGB pixel
		 */
//		void setFrameColor(PixelRGB96& background) { bgRGB = background; };

		/**
		 * @brief  Read current RGB background.
		 *
		 * @param[out] background RGB pixel
		 */
//		void getFrameColor(PixelRGB96& background) { background = bgRGB; };


		/**
		 * @brief  Set current greyscale background.
		 *
		 * @param[in] background greyscale pixel
		 */
//		void setFrameColor(PixelGrey& background) { bgGrey = background; };

		/**
		 * @brief  Read current greyscale background.
		 *
		 * @param[out] background greyscale pixel
		 */
//		void getFrameColor(PixelGrey& background) const { background = bgGrey; };





		/**
		 * @brief  Set current canvas' height.
		 *
		 * @return height in pixel.
		 */
		VIPRESULT setHeight(unsigned int value);

		/**
		 * @brief  Set current canvas' width.
		 *
		 * @return width in pixel.
		 */
		VIPRESULT setWidth(unsigned int value);



		unsigned int getWidth() const;

		unsigned int getHeight() const;


		/**
		 * @brief  Get the state of current data source.
		 *
		 * @return false, always.
		 */
		bool EoF() { return false; };

		/**
		 * @brief  Clear the frame with background pixel.
		 *
		 * @param[out] img VIPLibb Cache Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid.
		 *
		 * @note   Ouput operator (>>) call directly this function.
		 * @see    operator >> (vipFrameYUV420&)
		 */
		VIPRESULT extractTo(vipFrameYUV420& img);

		/**
		 * @brief  Clear the frame with background pixel.
		 *
		 * @param[out] img VIPLibb Cache24 Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid.
		 *
		 * @note   Ouput operator (>>) call directly this function.
		 * @see    operator >> (vipFrameRGB24&)
		 */
		VIPRESULT extractTo(vipFrameRGB24& img);

		/**
		 * @brief  Clear the frame with background pixel.
		 *
		 * @param[out] img Greyscale VIPLibb Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid.
		 *
		 * @note   Ouput operator (>>) call directly this function.
		 * @see    operator >> (vipFrameT&)
		 */
		VIPRESULT extractTo(vipFrameT<unsigned char>& img);

};


#endif	//__VIPLIB_VIPPLAINFRAMEGENERATOR_H__
