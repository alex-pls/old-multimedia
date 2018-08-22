/**
 *  @class   vipFrameRGB24
 *
 *  @brief   This Class implements standard VIPLib I/O Frame format.
 *           An image consisting of red, green and blue pixels.
 *           PixelRGB24 Array [width*height] (raster scan)
 *           Currently PixelRGB24 is difined as 3 char (3 * 8 = 24bits)
 *
 *
 *  @see     PixelRGB24
 *  @see     vipFrame
 *
 *  @version 0.6
 *  @date    12/07/2005 - //2005
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




#ifndef __VIPLIBVIPFRAMERGB24_H__
 #define __VIPLIBVIPFRAMERGB24_H__

 #define VIPFRAMERGB24_SLOWMODE

 #include "vipDefs.h"

 #include "PixelRGB24.h"
 #include "vipFrame.h"

 class vipFrameRGB24;
 class vipFrameYUV444;
  #include "vipFrameYUV420.h"
  #include "vipFrameRGB96.h"
  #include "vipFrameYUV444.h"
  #include "vipUtility.h"



class vipFrameRGB24 : public virtual vipFrame
 {

	public:

		/**
		 * @var   This value is used only by destructor, if true array will be deleted.
		 */
		bool autoFreeData;

		/**
		 * @var   RGB data array pointer. Size is width * height.
		 */
		PixelRGB24 *data;


	public:

		/**
		 * @var   Enumerate available Channels.
		 */
		enum ChannelRGB { RED, GREEN, BLUE };

		/**
		 * @brief Default constructor, initialize height and width to 0.
		 */
		vipFrameRGB24();

		/**
		 * @brief Create an image with the given dimensions, allocates empty data.
		 * @param width Width of the image.
		 * @param height Height of the image.
		 */
		vipFrameRGB24(unsigned int width, unsigned int height);

		/**
		 * @brief Copy Constructor, create an image from another image, copying memory.
		 * @param img source image.
		 */
		vipFrameRGB24(vipFrameRGB24& img);

		/**
		 * @brief Copy Constructor, create an image from another image, copying memory.
		 * @param img source image.
		 */
		vipFrameRGB24(vipFrameRGB96& img);


		/**
		 * @brief Destructor currenly clear pixel data (array).
		 */
		~vipFrameRGB24();


		void* dump_buffer() { return static_cast<void*>(data); };

		unsigned int getBufferSize() { return (unsigned int)( width * height * 3); };


		VIPRESULT reAllocCanvas(unsigned int w, unsigned int h);

		unsigned int getBpp() { return sizeof(PixelRGB24) * 8; };
		VIPRESULT setBlack();
		VIPRESULT setWhite();

		VIPRESULT extractBrightness(unsigned char* buffer, unsigned int* size = NULL );

		/**
		 * @brief Clear all pixel to the specified value.
		 *
		 * @param bg a PixelRGB to overwrite on all image.
		 *
		 * @return current instance address.
		 */
		vipFrameRGB24& clearWith(PixelRGB24& bg);


		/**
		 * @brief Set pixel (x, y) to the specified value.
		 *
		 * @param x x position of the pixel.
		 * @param y y position of the pixel.
		 * @param p new value for the selected coords.
		 *
		 * @note No check is made that x and y are in range.
		 */
		VIPRESULT setPixel(unsigned int x, unsigned int y, PixelRGB24 p);


		/**
		 * @brief Get pixel (x, y) value and store it to p.
		 *
		 * @param x x position of the pixel.
		 * @param y y position of the pixel.
		 * @param p address to store selected pixel's value.
		 *
		 * @note No check is made that x and y are in range.
		 */
		VIPRESULT getPixel(unsigned int x, unsigned int y, PixelRGB24& p);



		/**
		 * @brief Copies all pixel data from img.
		 *        Throws an exception if images are of different size.
		 *
		 * @param img The image to copy the data from.
		 *
		 * @return current instance.
		 */
		vipFrameRGB24& operator = (vipFrameRGB24& img);

		/**
		 * @brief Overload equals-add (+=) operator for two images (pixel += loop)
		 *        Throws an exception if images are of different size.
		 *
		 * @param img The image to add to current data.
		 *
		 * @return current instance.
		 */
		vipFrameRGB24& operator += (vipFrameRGB24& img);

		/**
		 * @brief Overload equals-sub (-=) operator for two images (pixel -= loop)
		 *        Throws an exception if images are of different size.
		 *
		 * @param img The image to add to current data.
		 *
		 * @return current instance.
		 */
		vipFrameRGB24& operator -= (vipFrameRGB24& img);



		void operator << (const vipFrameYUV420& img);
		void operator << (const vipFrameRGB96& img);

		vipFrameRGB24& operator >> (vipFrameYUV420& img);
		vipFrameRGB24& operator >> (vipFrameYUV444& img);
		vipFrameRGB24& operator >> (vipFrameRGB96& img);


		VIPFRAME_PROFILE getProfile() { return vipFrame::VIPFRAME_RGB24; };
		VIPFRAME_CHANNEL_TYPE getChannelType() { return vipFrame::VIPFRAME_CT_PACKED; };

		int getFOURCC() { return 0x32424752; };	// same as RGB32

 };



#endif //__VIPLIBVIPFRAMERGB24_H__

