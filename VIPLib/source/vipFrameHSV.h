/**
 *  @class   vipFrameHSV
 *
 *  @brief   This Class implements standard VIPLib Color Frame format.
 *           PixelHSV Array [width*height] (raster scan)
 *           Currently PixelHSV is difined as 3 integer (3 * 32 = 96bits)
 *
 *
 *  @bug     too much memory for common uses and real-time streaming
 *  @warning
 *  @todo
 *
 *  @see     PixelHSV
 *  @see     vipFrame
 *  @see     vipFrameYUV420
 *  @see     vipFrameGrey
 *  @example ../tests/test_vipFrameHSV.cpp
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

/**
 * ImageHSV is simply an extension of ImageRGB. HSV Data is stored in THE SAME
 * MEMORY as RGB (so RGB and HSV data is not present simultaneously). Additional
 * methods convert one format to the other.
 * Note: Hue is an angle (0-360) and Sat and Val are on a scale 0-255 (not
 * 0-100 as used in GIMP etc.)
 */

#ifndef __VIPLIB_VIPFRAMEHSV_H__
 #define __VIPLIB_VIPFRAMEHSV_H__

 #include "vipFrame.h"



 #include "PixelHSV.h"
/*
 struct PixelHSV {
	 unsigned short int hue;	//16bit	|
	 unsigned char sat;			//8bit	|> 32bit
	 unsigned char vat;			//8bit	|
 }
*/


 #include "vipFrameRGB96.h"
 #include "vipFrameGrey.h"
class vipFrameHSV;
 #include "vipFrameYUV444.h"
 #include "vipFrameRGB24.h"


class vipFrameHSV : public virtual vipFrame
/**
 * An image consisting of red, green and blue pixels.
 *
 * The image is stored as an array of ints, each pixel spanning three ints
 * (one for each of its red, green and blue values).
 */
{
	public:

		/**
		 * @var   HSV data array pointer. Size is width * height.
		 */
		PixelHSV *data;


	public:

		/**
		 * @var   Enumerate available Channels.
		 */
		enum ChannelHSV { HUE, SAT, VAL };



	public:


		/**
		 * @brief Default constructor, initialize height and width to 0.
		 */
		vipFrameHSV();

		/**
		 * @brief Create an image with the given dimensions, allocates empty data.
		 * @param width Width of the image
		 * @param height Height of the image
		 */
		vipFrameHSV(unsigned int width, unsigned int height);


		/**
		 * @brief Copy Constructor, create an image from another image, copying memory.
		 * @param img source color image.
		 */
		vipFrameHSV(vipFrameHSV& img);

		/**
		 * @brief Copy Constructor, create an image from another image, copying memory.
		 * @param img source grey image.
		 */
		vipFrameHSV(vipFrameRGB96& img);

		/**
		 * @brief Copy Constructor, create an image from another image, copying memory.
		 * @param img source grey image.
		 */
		vipFrameHSV(vipFrameGrey& img);


		/**
		 * @brief Destructor currenly clear pixel data (array).
		 */
		~vipFrameHSV();


		VIPRESULT setWidth(unsigned int newWidth);
		VIPRESULT setHeight(unsigned int newHeight);

		void* dump_buffer() { return static_cast<void*>(data); };

		VIPRESULT reAllocCanvas(unsigned int w, unsigned int h);

		unsigned int getBufferSize() { return (unsigned int)( width * height * sizeof(PixelHSV) * 8); };

		unsigned int getBpp() { return sizeof(PixelHSV) * 8; };
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
		VIPRESULT setPixel(unsigned int x, unsigned int y, PixelHSV p);

		/**
		 * @brief Set pixel (x, y) to the specified values: Red, Green, Blue.
		 *
		 * @param x x position of the pixel.
		 * @param y y position of the pixel.
		 * @param red red channel's value of the selected pixel.
		 * @param green green channel's value of the selected pixel.
		 * @param blue blue channel's value of the selected pixel.
		 */
		VIPRESULT setHSV(unsigned int x, unsigned int y, unsigned short int hue, float sat, float val);

		/**
		 * @brief Set pixel (x, y) to the specified values: Red, Green, Blue.
		 *
		 * @param x x position of the pixel.
		 * @param y y position of the pixel.
		 * @param ch  selected channel (R, G, B enumeration).
		 * @param value selected channel's value of the selected pixel.
		 */
		VIPRESULT setChannel(unsigned int x, unsigned int y, ChannelHSV ch, unsigned int value);

		/**
		 * @brief Get pixel (x, y) value and store it to p.
		 *
		 * @param x x position of the pixel.
		 * @param y y position of the pixel.
		 * @param p address to store selected pixel's value.
		 */
		VIPRESULT getPixel(unsigned int x, unsigned int y, PixelHSV& p);

		/**
		 * @brief Get pixel's channel value (x, y).
		 *
		 * @param x x position of the pixel.
		 * @param y y position of the pixel.
		 * @param ch  selected channel (R, G, B enumeration).
		 *
		 * @return value of the selected channel in position (x, y)
		 */
		unsigned int getChannel(unsigned int x, unsigned int y, ChannelHSV ch);

		/**
		 * @brief Clear all pixel to the specified value.
		 *
		 * @param bg a PixelHSV to overwrite on all image.
		 *
		 * @return current instance address.
		 */
		vipFrameHSV& clearWith(PixelHSV& bg);

		/**
		 * @brief Clear all pixel to the specified value in specified channel.
		 *
		 * @param ch the channel to clear.
		 * @param bg pixel color to overwrite on the channel.
		 *
		 * @return current instance address.
		 */
		vipFrameHSV& clearChannel(ChannelHSV ch, unsigned int value = 0);

		/**
		 * @brief Copies all pixel data from img
		 *        Throws an exception if images are of different size.
		 *
		 * @param img The image to copy the data from.
		 *
		 * @return current instance.
		 */
		vipFrameHSV& copy(vipFrameHSV& img);


		/* Operators overloading */

		/**
		 * @brief Copies all pixel data from img using copy method.
		 *        Throws an exception if images are of different size.
		 *
		 * @param img The image to copy the data from.
		 *
		 * @return current instance.
		 */
		vipFrameHSV& operator = (vipFrameHSV& img) { return this->copy(img); };


		/**
		 * @brief Overload equals-add (+=) operator for two images (pixel += loop)
		 *        Throws an exception if images are of different size.
		 *
		 * @param img The image to add to current data.
		 *
		 * @return current instance.
		 */
		vipFrameHSV& operator += (vipFrameHSV& img) ;


		/**
		 * @brief Overload equals-sub (-=) operator for two images (pixel -= loop)
		 *        Throws an exception if images are of different size.
		 *
		 * @param img The image to subtract to current data.
		 *
		 * @return current instance.
		 */
		vipFrameHSV& operator -= (vipFrameHSV& img) ;

		/**
		 * @brief Overload equals-div (-=) operator for two images (pixel /= loop)
		 *        Throws an exception if images are of different size.
		 *
		 * @param img The image to divide to current data.
		 *
		 * @return current instance.
		 */
		vipFrameHSV& operator /= (vipFrameHSV& img) ;

		/**
		 * @brief Overload equals-mul (-=) operator for two images (pixel *= loop)
		 *        Throws an exception if images are of different size.
		 *
		 * @param img The image to multiply to current data.
		 *
		 * @return current instance.
		 */
		vipFrameHSV& operator *= (vipFrameHSV& img) ;



		/**
		 * @brief Ouput operator, export to standard VIPLib frame formats,
		 *        export image data, it's like a copy constructor by parameter side.
		 *
		 * @param[out] img VIPLib Cache24 Frame to store data.
		 *
		 * @return Address of current instance.
		 */
		vipFrameHSV& operator >> (vipFrameRGB24& img);

		/**
		 * @brief Ouput operator, export to standard VIPLib frame formats,
		 *        export image data, it's like a copy constructor by parameter side.
		 *
		 * @param[out] img Color VIPLib Frame to store data.
		 *
		 * @return Address of current instance.
		 */
		vipFrameHSV& operator >> (vipFrameHSV& img);

		/**
		 * @brief Ouput operator, export to standard VIPLib frame formats,
		 *        export image data, it's like a copy constructor by parameter side.
		 *
		 * @param[out] img Color VIPLib Frame to store data.
		 *
		 * @return Address of current instance.
		 */
		vipFrameHSV& operator >> (vipFrameRGB96& img);

		/**
		 * @brief Ouput operator, export to standard VIPLib frame formats,
		 *        export image data, it's like a copy constructor by parameter side.
		 *
		 * @param[out] img Greyscale VIPLib Frame to store data.
		 *
		 * @return Address of current instance.
		 */
		vipFrameHSV& operator >> (vipFrameGrey& img);



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
		 * @param[in] img Color VIPLib Frame to be loaded.
		 */
		void operator << (const vipFrameHSV& img);

		/**
		 * @brief Input operator, import standard VIPLib frame formats,
		 *        load image data, it's like a copy constructor.
		 *
		 * @param[in] img Color VIPLib Frame to be loaded.
		 */
		void operator << (const vipFrameRGB96& img);

		/**
		 * @brief Input operator, import standard VIPLib frame formats,
		 *        load image data, it's like a copy constructor.
		 *
		 * @param[in] img Greyscale VIPLib Frame to be loaded.
		 */
		void operator << (const vipFrameGrey& img);

		/**
		 * @brief Input operator, import standard VIPLib frame formats,
		 *        load image data, it's like a copy constructor.
		 *
		 * @param[in] img YUV 4:2:0 VIPLib Frame to be loaded.
		 */
		void operator << (const vipFrameYUV420& img);



        // Pixel conversion routines // commented out by Marco Verza 
        //static void convPixel_RGB32toHSV (const PixelRGB96&, PixelHSV&);
        //static void convPixel_HSVtoRGB32 (const PixelHSV&, PixelRGB96&);

        //static void convPixel_RGB24toHSV (const PixelRGB24&, PixelHSV&);
        //static void convPixel_HSVtoRGB24 (const PixelHSV&, PixelRGB24&);

        //static void convPixel_GREYtoHSV (const PixelGrey&, PixelHSV&);
        //static void convPixel_HSVtoGREY (const PixelHSV&, PixelGrey&);


		VIPFRAME_PROFILE getProfile() { return vipFrame::VIPFRAME_CUSTOM; };
		VIPFRAME_CHANNEL_TYPE getChannelType() { return vipFrame::VIPFRAME_CT_PACKED; };

		int getFOURCC() { return 0;};


 };


#endif	// __VIPLIB_VIPFRAMEHSV_H__

