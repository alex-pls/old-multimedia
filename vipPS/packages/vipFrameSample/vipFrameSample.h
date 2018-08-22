/**
 *  @class   vipFrameSample
 *
 *  @brief   This Class implements standard VIPLib GreyScale Frame format.
 *           PixelGrey Array [width*height] (raster sequence)
 *           Currently PixelGrey is currently defined as 1 unsigned char (8bits)
 *
 *
 *  @bug
 *  @warning
 *  @todo
 *
 *  @example ../tests/test_vipFramGrey.cpp
 *
 *  @version 1.0.2
 *  @date    24/12/2005
 *  @author  Alessandro Polo
 *
 ****************************************************************************
 *  Class based on Package Studio template: vipFrameTemplate version 0.9.12
 ****************************************************************************
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.science.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DIT - University of Trento
 *
 ****************************************************************************/


#ifndef __VIPLIB_VIPFRAMESAMPLE_H__
 #define __VIPLIB_VIPFRAMESAMPLE_H__


 #include "I:\Projects\Software\VIPLib\source\vipDefs.h"

 #include "I:\Projects\Software\VIPLib\source\vipFrame.h"
 #include "I:\Projects\Software\VIPLib\source\vipFrameYUV420.h"
 #include "I:\Projects\Software\VIPLib\source\vipFrameRGB24.h"
 #include "I:\Projects\Software\VIPLib\source\vipFrameRGB96.h"
 #include "I:\Projects\Software\VIPLib\source\vipFrameRGBA32.h"

/// Single pixel constsisting of an u char.
// typedef unsigned char 	 PixelGrey;


class vipFrameSample : public virtual vipFrame
{
	public:

		/**
		 * @var   GreyScale data array pointer. Size is width * height.
		 */
		PixelGrey *data;

	public:


		/**
		 * @brief Default constructor, initialize height and width to 0.
		 */
		vipFrameSample();



		/**
		 * @brief Create an image with the given dimensions, allocates empty data.
		 * @param width Width of the image
		 * @param height Height of the image
		 */
		vipFrameSample(unsigned int width, unsigned int height);



		/**
		 * @brief Copy Constructor, create an image from another image, copying memory.
		 * @param img source grey image.
		 */
		vipFrameSample(vipFrameSample& img);


		/**
		 * @brief Copy Constructor, create an image from another image, copying memory.
		 * @param img source color image (will be converted to greyscale).
		 */
		vipFrameSample(vipFrameRGB24& img);



		/**
		 * @brief Destructor currenly clear pixel data (array).
		 */
		~vipFrameSample();




		void* dump_buffer()
		 {
			return static_cast<void*>(data);
		 };



		VIPRESULT reAllocCanvas(unsigned int w, unsigned int h);



		unsigned int getBpp() { return sizeof(PixelGrey) * 8; };



		VIPRESULT setBlack();



		VIPRESULT setWhite();



		unsigned int getBufferSize() { return (unsigned int)( width * height); };



		VIPRESULT extractBrightness(unsigned char* buffer, unsigned int* size = NULL );





		/**
		 * @brief Set pixel (x, y) to the specified value,
		 *        conversion to PixelGrey is implemented.
		 *
		 * @param x x position of the pixel.
		 * @param y y position of the pixel.
		 * @param p new value for the selected coords.
		 *
		 * @note No check is made that x and y are in range.
		 */
		VIPRESULT setPixel(unsigned int x, unsigned int y, PixelRGB24 p);

		/**
		 * @brief Set pixel (x, y) to the specified value.
		 *
		 * @param x x position of the pixel.
		 * @param y y position of the pixel.
		 * @param p new value for the selected coords.
		 *
		 * @note No check is made that x and y are in range.
		 */
		VIPRESULT setPixel(unsigned int x, unsigned int y, PixelGrey level);

		/**
		 * @brief Get pixel (x, y) value and store it to p.
		 *
		 * @param x x position of the pixel.
		 * @param y y position of the pixel.
		 * @param p address to store selected pixel's value.
		 *
		 * @note No check is made that x and y are in range.
		 */
		VIPRESULT getPixel(unsigned int x, unsigned int y, PixelGrey& p) const;

		const PixelGrey& getPixel(unsigned int x, unsigned int y) const;


		/**
		 * @brief Clear all pixel to the specified value.
		 *
		 * @param bg a PixelRGB to overwrite on all image, default is black.
		 *
		 * @return current instance address.
		 */
		vipFrameSample& clearWith(PixelGrey bg = 0);

		/// Copy data from image data from img.
		vipFrameSample& copy(vipFrameSample& img);


		/// Absolute value of brightness
		VIPRESULT invert();

		/// Threshold brightness
		VIPRESULT threshold(PixelGrey thresh) ;



		vipFrameSample& operator >> (vipFrameRGB24& img);

		void operator << (const vipFrameRGB24& img);




		VIPFRAME_PROFILE getProfile()
		 {
			 return vipFrame::VIPFRAME_MONO;
		 };



		VIPFRAME_CHANNEL_TYPE getChannelType()
		 {
			 return vipFrame::VIPFRAME_CT_PACKED;
		 };



		int getFOURCC()
		 {
			 return 0;
		 };




 };


#endif	// __VIPLIB_VIPFRAMESAMPLE_H__

