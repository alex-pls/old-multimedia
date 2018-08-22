/**
 *  @class   vipFrameRGB96
 *
 *  @brief   This Class implements standard VIPLib Color Frame format.
 *           PixelRGB Array [width*height] (raster scan)
 *           Currently PixelRGB is difined as 3 integer (3 * 32 = 96bits)
 *
 *
 *  @bug     too much memory for common uses and real-time streaming
 *  @warning
 *  @todo
 *
 *  @see     PixelRGB
 *  @see     vipFrame
 *  @see     vipFrameYUV420
 *  @see     vipFrameGrey
 *  @example ../tests/test_vipFrameRGB96.cpp
 *
 *  @version 0.9
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



#ifndef __VIPLIB_VIPFRAMERGB96_H__
 #define __VIPLIB_VIPFRAMERGB96_H__

 #include "vipFrame.h"
 #include "PixelRGB96.h"

class vipFrameRGB96; // cos of "double-face" type definitions in operators
 #include "vipFrameYUV420.h"
 #include "vipFrameRGB24.h"
 #include "vipFrameGrey.h"


class vipFrameRGB96 : public virtual vipFrame
/**
 * An image consisting of red, green and blue pixels.
 *
 * The image is stored as an array of ints, each pixel spanning three ints
 * (one for each of its red, green and blue values).
 */
{
	public:

		/**
		 * @var   This value is used only by destructor, if true array will be deleted.
		 */
		bool autoFreeData;

		/**
		 * @var   RGB data array pointer. Size is width * height.
		 */
		PixelRGB96 *data;



	public:

		/**
		 * @var   Enumerate available Channels.
		 */
		enum ChannelRGB { RED, GREEN, BLUE };



	public:


		/**
		 * @brief Default constructor, initialize height and width to 0.
		 */
		vipFrameRGB96();

		/**
		 * @brief Create an image with the given dimensions, allocates empty data.
		 * @param width Width of the image
		 * @param height Height of the image
		 */
		vipFrameRGB96(unsigned int width, unsigned int height);

		/**
		 * @brief Copy Constructor, create an image from another image, copying memory.
		 * @param img source color image.
		 */
		vipFrameRGB96(vipFrameRGB96& img);

		/**
		 * @brief Copy Constructor, create an image from another image, copying memory.
		 * @param img source color image.
		 */
		vipFrameRGB96(vipFrameRGB24& img);



		/**
		 * @brief Copy Constructor, create an image from another image, copying memory.
		 * @param img source grey image.
		 */
		vipFrameRGB96(vipFrameGrey& img);

		/**
		 * @brief Destructor currenly clear pixel data (array).
		 */
		~vipFrameRGB96();


		VIPRESULT setWidth(unsigned int newWidth);
		VIPRESULT setHeight(unsigned int newHeight);

		void* dump_buffer() { return static_cast<void*>(data); };

		VIPRESULT reAllocCanvas(unsigned int w, unsigned int h);


		unsigned int getBufferSize() { return (unsigned int)( width * height * 4); };


		unsigned int getBpp() { return sizeof(PixelRGB96) * 8; };
		VIPRESULT setBlack();
		VIPRESULT setWhite();

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
		VIPRESULT setPixel(unsigned int x, unsigned int y, PixelRGB96 p);

		/**
		 * @brief Set pixel (x, y) to the specified values: Red, Green, Blue.
		 *
		 * @param x x position of the pixel.
		 * @param y y position of the pixel.
		 * @param red red channel's value of the selected pixel.
		 * @param green green channel's value of the selected pixel.
		 * @param blue blue channel's value of the selected pixel.
		 */
		VIPRESULT setRGB(unsigned int x, unsigned int y, int red, int green, int blue);

		/**
		 * @brief Set pixel (x, y) to the specified values: Red, Green, Blue.
		 *
		 * @param x x position of the pixel.
		 * @param y y position of the pixel.
		 * @param ch  selected channel (R, G, B enumeration).
		 * @param value selected channel's value of the selected pixel.
		 */
		VIPRESULT setChannel(unsigned int x, unsigned int y, ChannelRGB ch, int value);

		/**
		 * @brief Get pixel (x, y) value and store it to p.
		 *
		 * @param x x position of the pixel.
		 * @param y y position of the pixel.
		 * @param p address to store selected pixel's value.
		 */
		VIPRESULT getPixel(unsigned int x, unsigned int y, PixelRGB96& p) const;

		const PixelRGB96& getPixel(unsigned int x, unsigned int y) const;

		/**
		 * @brief Get pixel's channel value (x, y).
		 *
		 * @param x x position of the pixel.
		 * @param y y position of the pixel.
		 * @param ch  selected channel (R, G, B enumeration).
		 *
		 * @return value of the selected channel in position (x, y)
		 */
		int getChannel(unsigned int x, unsigned int y, ChannelRGB ch) const;

		/**
		 * @brief Clear all pixel to the specified value.
		 *
		 * @param bg a PixelRGB to overwrite on all image.
		 *
		 * @return current instance address.
		 */
		vipFrameRGB96& clear(int = 0);

		/**
		 * @brief Clear all pixel to the specified value.
		 *
		 * @param bg a PixelRGB to overwrite on all image.
		 *
		 * @return current instance address.
		 */
		vipFrameRGB96& clearWith(PixelRGB96& bg);

		/**
		 * @brief Clear all pixel to the specified value in specified channel.
		 *
		 * @param ch the channel to clear.
		 * @param bg pixel color to overwrite on the channel.
		 *
		 * @return current instance address.
		 */
		vipFrameRGB96& clearChannel(ChannelRGB ch, int bg = 0);




		/**
		 * @brief Copies all pixel data from img
		 *        Throws an exception if images are of different size.
		 *
		 * @param img The image to copy the data from.
		 *
		 * @return current instance.
		 */
		vipFrameRGB96& copy(vipFrameRGB96& img);


		/* Operators overloading */

		/**
		 * @brief Copies all pixel data from img using copy method.
		 *        Throws an exception if images are of different size.
		 *
		 * @param img The image to copy the data from.
		 *
		 * @return current instance.
		 */
		vipFrameRGB96& operator = (vipFrameRGB96& img) { return this->copy(img); };


		/**
		 * @brief Overload equals-add (+=) operator for two images (pixel += loop)
		 *        Throws an exception if images are of different size.
		 *
		 * @param img The image to add to current data.
		 *
		 * @return current instance.
		 */
		vipFrameRGB96& operator += (vipFrameRGB96& img) ;

		/**
		 * @brief Overload equals-sub (-=) operator for two images (pixel -= loop)
		 *        Throws an exception if images are of different size.
		 *
		 * @param img The image to subtract to current data.
		 *
		 * @return current instance.
		 */
		vipFrameRGB96& operator -= (vipFrameRGB96& img) ;



		/**
		 * @brief Ouput operator, export to standard VIPLib frame formats,
		 *        export image data, it's like a copy constructor by parameter side.
		 *
		 * @param[out] img VIPLib Cache Frame to store data.
		 *
		 * @return Address of current instance.
		 */
		//vipFrameRGB96& operator >> (vipFrameYUV420& img);

		/**
		 * @brief Ouput operator, export to standard VIPLib frame formats,
		 *        export image data, it's like a copy constructor by parameter side.
		 *
		 * @param[out] img VIPLib Cache24 Frame to store data.
		 *
		 * @return Address of current instance.
		 */
		vipFrameRGB96& operator >> (vipFrameRGB24& img);


		/**
		 * @brief Ouput operator, export to standard VIPLib frame formats,
		 *        export image data, it's like a copy constructor by parameter side.
		 *
		 * @param[out] img Greyscale VIPLib Frame to store data.
		 *
		 * @return Address of current instance.
		 */
		vipFrameRGB96& operator >> (vipFrameGrey& img);


		/**
		 * @brief Input operator, import standard VIPLib frame formats,
		 *        load image data, it's like a copy constructor.
		 *
		 * @param[in] img VIPLib Cache Frame to be loaded.
		 */
		void operator << (const vipFrameYUV420& img);

		/**
		 * @brief Input operator, import standard VIPLib frame formats,
		 *        load image data, it's like a copy constructor.
		 *
		 * @param[in] img VIPLib Cache24 Frame to be loaded.
		 */
		void operator << (const vipFrameRGB24& img);


		/**
		 * @brief Input operator, import standard VIPLib frame formats,
		 *        load image data, it's like a copy constructor.
		 *
		 * @param[in] img Greyscale VIPLib Frame to be loaded.
		 */
		void operator << (const vipFrameGrey& img);

		VIPFRAME_PROFILE getProfile() { return vipFrame::VIPFRAME_RGB96; };
		VIPFRAME_CHANNEL_TYPE getChannelType() { return vipFrame::VIPFRAME_CT_PACKED; };

		int getFOURCC() { return 0x32424752; };	// same as RGB24

 };


#endif	// __VIPLIB_VIPFRAMERGB96_H__

