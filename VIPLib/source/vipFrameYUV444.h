/**
 *  @class   vipFrameYUV444
 *
 *  @brief   This Class implements the YUV444 frame.
 *           An image consisting of red, green and blue pixels.
 *           PixelRGB24 Array [width*height] (raster scan)
 *           Currently PixelRGB24 is difined as 3 char (3 * 8 = 24bits)
 *
 *
 *  @see     PixelRGB24
 *  @see     vipFrame
 *
 *  @version 0.1
 *  @date    05/03/2008 - //2005
 *  @author  Marco Verza
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


//http://www.fourcc.org

#ifndef __VIPLIB_VIPFRAMEYUV444_H__
 #define __VIPLIB_VIPFRAMEYUV444_H__

 #define _VIPFRAMECACHE24_SLOWMODE

 #include "vipDefs.h"

 #include "vipFrame.h"


class vipFrameHSV;
class vipFrameRGB24;
#include "vipFrameHSV.h"
  #include "vipFrameRGB24.h"

//	PLANAR	PLANAR	PLANAR	PLANAR	PLANAR	PLANAR	PLANAR	PLANAR	PLANAR	PLANAR	PLANAR

class vipFrameYUV444 : public virtual vipFrame
 {

	public:


		bool autoFreeData;

		/**
		 * @var   PLANAR YUV data array pointer. Size is width * height * 3.
		 */
		unsigned char *data;

		unsigned char *Y; // = data[0]
		unsigned char *U; // = data[ width*height* ]
		unsigned char *V; // = data[ width*height*2 ]


	public:

		/**
		 * @var   Enumerate available Channels.
		 */
		enum ChannelYUV { Lum, Cb, Cr }; // YUV

		/**
		 * @brief Default constructor, initialize height and width to 0.
		 */
		vipFrameYUV444();

		/**
		 * @brief Create an image with the given dimensions, allocates (random) data.
		 * @param width Width of the image.
		 * @param height Height of the image.
		 */
		vipFrameYUV444(unsigned int width, unsigned int height);

		/**
		 * @brief Copy Constructor, create an image from another image, copying memory.
		 * @param img source image.
		 */
		vipFrameYUV444(vipFrameYUV444& img);

		/**
		 * @brief Destructor currenly clear pixel data (array).
		 */
		~vipFrameYUV444();


		void* dump_buffer() { return static_cast<void*>(data); };

		VIPRESULT reAllocCanvas(unsigned int w, unsigned int h);


		//width*height*3 * 8bit / width/height = 3*8bit = 24bit
		unsigned int getBpp() { return 24; };
		VIPRESULT setBlack();
		VIPRESULT setWhite();

		VIPRESULT extractBrightness(unsigned char* buffer, unsigned int* size = NULL );

		unsigned int getBufferSize() { return (unsigned int)( width * height * 3); };


		/**
		 * @brief Clear all pixel to the specified value.
		 *
		 * @param bg a PixelRGB to overwrite on all image.
		 *
		 * @return current instance address.
		 */
		vipFrameYUV444& clearWith(unsigned char* bg, ChannelYUV channel);


		/**
		 * @brief Set pixel (x, y) to the specified value.
		 *
		 * @param x x position of the pixel.
		 * @param y y position of the pixel.
		 * @param p new value for the selected coords.
		 *
		 * @note No check is made that x and y are in range.
		 */
		VIPRESULT setPixel(unsigned int x, unsigned int y, unsigned char& value, ChannelYUV channel);


		/**
		 * @brief Get pixel (x, y) value and store it to p.
		 *
		 * @param x x position of the pixel.
		 * @param y y position of the pixel.
		 * @param p address to store selected pixel's value.
		 *
		 * @note No check is made that x and y are in range.
		 */
		VIPRESULT getPixel(unsigned int x, unsigned int y, unsigned char& value, ChannelYUV channel);



		/**
		 * @brief Copies all pixel data from img.
		 *        Throws an exception if images are of different size.
		 *
		 * @param img The image to copy the data from.
		 *
		 * @return current instance.
		 */
		vipFrameYUV444& operator = (vipFrameYUV444& img);

		/**
		 * @brief Overload equals-add (+=) operator for two images (pixel += loop)
		 *        Throws an exception if images are of different size.
		 *
		 * @param img The image to add to current data.
		 *
		 * @return current instance.
		 */
		vipFrameYUV444& operator += (vipFrameYUV444& img);

		/**
		 * @brief Overload equals-add (+=) operator for two images (pixel += loop)
		 *        Throws an exception if images are of different size.
		 *
		 * @param img The image to add to current data.
		 *
		 * @return current instance.
		 */
		vipFrameYUV444& operator *= (vipFrameYUV444& img);


		void operator << (const vipFrameRGB24& img);

		vipFrameYUV444& operator >> (vipFrameRGB24& img);

		vipFrameYUV444& operator >> (vipFrameYUV420& img);
		vipFrameYUV444& operator << (vipFrameYUV420& img);

		vipFrameYUV444& operator >> (vipFrameHSV& img);

		VIPFRAME_PROFILE getProfile() { return vipFrame::VIPFRAME_I444; };
		VIPFRAME_CHANNEL_TYPE getChannelType() { return vipFrame::VIPFRAME_CT_PLANAR; };

		int getFOURCC() { return 0x00000000; };	// Not found on http://www.fourcc.org/yuv.php 
 };



#endif //__VIPLIB_VIPFRAMEYUV444_H__

