/**
 *  @class   vipNoiseGenerator
 *
 *  @brief   A noise VIPLibb source, no internal buffering
 *           (operates on output frames)
 *
 *  @bug     very very slow
 *  @warning
 *  @todo    optimize, multi-threading, SNR & stats support.
 *
 *  @see     vipInput
 *  @example ../../tests/test_vipNoiseGenerator.cpp
 *
 *  @version 0.4.5
 *  @date    24/08/2005
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


#ifndef __VIPLIB_VIPNOISEGENERATOR_H__
 #define __VIPLIB_VIPNOISEGENERATOR_H__

 #include "../vipDefs.h"
 #include "../vipInput.h"

 #include "../PixelRGB96.h"
 #include "../PixelRGB24.h"
 #include "../PixelHSV.h"
 #include "../vipFrameGrey.h"

 #include "../vipFrameYUV420.h"
 #include "../vipFrameRGB24.h"
 #include "../vipFrameT.h"


class vipNoiseGenerator : public vipInput
 {

 protected:

		/**
		 * @brief  Current run mode.
		 */
		int v_runmode;

		/**
		 * @brief  do noise-value normalization
		 */
		bool normalized;

		/**
		 * @brief  number of pixel involved in operation [0,1]
		 */
		float spread;

		/**
		 * @brief  normalization value [rand() % normalize_value]
		 */
		int normalize_value;


 public:

		/**
		 * @brief  Available run modes.
		 */
		enum RUNMODE	{	TIMEBASED,
							BOOH		};


		/**
		 * @brief  Default constructor, frame rate
		 *         is managed by vipInput class.
		 *
		 * @param[in] fps frame rate, default is 0: max possible
		 */
		vipNoiseGenerator(float fps = 0);

		/**
		 * @brief  Default constructor initialize background, frame rate
		 *         is managed by vipInput class.
		 *
		 * @param[in] runm current runmode.
		 * @param[in] fps frame rate, default is 0: max possible
		 */
		vipNoiseGenerator(RUNMODE runm, float fps);

		/**
		 * @brief  Reset variables and noise source.
		 *
		 * @return VIPRET_OK
		 */
		VIPRESULT reset();

		/**
		 * @brief  Reset current random generator source.
		 */
		void resetNoiseSource();

		/**
		 * @brief  Create a random RGB pixel
		 *
		 * @return VIPLibb RGB pixel [int rand, int rand, int rand].
		 */
		static PixelRGB96 getRandomPixelRGB96();

		/**
		 * @brief  Create a random RGB24 pixel
		 *
		 * @return VIPLibb RGB24 pixel [unsigned char rand,
		 *         unsigned char rand, unsigned char rand].
		 */
		static PixelRGB24 getRandomPixelRGB24();

		/**
		 * @brief  Create a random HSV pixel
		 *
		 * @return VIPLibb HSV pixel [int rand, int rand, int rand].
		 */
		static PixelHSV getRandomPixelHSV();

		/**
		 * @brief  Create a random greyscale pixel
		 *
		 * @return VIPLibb greyscale pixel [int rand].
		 */
		static PixelGrey getRandomPixelGrey();


		/**
		 * @brief  Pixel are generated directly into output image!
		 * @return 0
		 */
		unsigned int getWidth() const { return 0; };

		/**
		 * @brief  Pixel are generated directly into output image!
		 * @return 0
		 */
		unsigned int getHeight() const { return 0; };

		/**
		 * @brief  Get the state of current data source.
		 *
		 * @return false, always.
		 */
		bool EoF() { return false; };

		/**
		 * @brief  Create a new noise frame with current settings.
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
		 * @brief  Create a new noise frame with current settings.
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
		 * @brief  Create a new noise frame with current settings.
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


#endif	//__VIPLIB_VIPNOISEGENERATOR_H__
