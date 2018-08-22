/**
 *  @class   vipFrameGrey
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
 *
 ****************************************************************************
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.disi.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DISI - University of Trento
 *
 ****************************************************************************/


#ifndef __VIPLIB_VIPFRAMEGREY_H__
 #define __VIPLIB_VIPFRAMEGREY_H__



 #include "vipDefs.h"


 #include "vipFrame.h"
class vipFrameGrey; // cos of "double-face" type definitions in operators
 #include "vipFrameYUV420.h"
 #include "vipFrameRGB24.h"
 #include "vipFrameRGB96.h"
 

/// Single pixel constsisting of an u char.
 typedef unsigned char 	 PixelGrey;

// Define Coefficients for RGB to Brightness relationship, already definded in vipDefs!
 #define RED_COEF .2989961801
 #define GREEN_COEF .5869947588
 #define BLUE_COEF .1139912943


class vipFrameGrey : public virtual vipFrame
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
		vipFrameGrey();

		/**
		 * @brief Create an image with the given dimensions, allocates empty data.
		 * @param width Width of the image
		 * @param height Height of the image
		 */
		vipFrameGrey(unsigned int width, unsigned int height);

		/**
		 * @brief Copy Constructor, create an image from another image, copying memory.
		 * @param img source grey image.
		 */
		vipFrameGrey(vipFrameGrey& img);

		/**
		 * @brief Copy Constructor, create an image from another image, copying memory.
		 * @param img source cache image (will be converted to greyscale).
		 */
		vipFrameGrey(vipFrameYUV420& img);

		/**
		 * @brief Copy Constructor, create an image from another image, copying memory.
		 * @param img source color image (will be converted to greyscale).
		 */
		vipFrameGrey(vipFrameRGB24& img);

		/**
		 * @brief Copy Constructor, create an image from another image, copying memory.
		 * @param img source color image (will be converted to greyscale).
		 */
		vipFrameGrey(vipFrameRGB96& img);


		/**
		 * @brief Destructor currenly clear pixel data (array).
		 */
		~vipFrameGrey();


		int setWidth(unsigned int newWidth);
		int setHeight(unsigned int newHeight);



		void* dump_buffer() { return static_cast<void*>(data); };

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
		vipFrameGrey& clearWith(PixelGrey bg = 0);

		/// Copy data from image data from img.
		vipFrameGrey& copy(vipFrameGrey& img);


		/// Absolute value of brightness
		VIPRESULT invert();

		/// Threshold brightness
		VIPRESULT threshold(PixelGrey thresh) ;


		/* Operators overloading */

		/**
		 * @brief Copies all pixel data from img using copy method.
		 *        Throws an exception if images are of different size.
		 *
		 * @param img The image to copy the data from.
		 *
		 * @return current instance.
		 */
		vipFrameGrey& operator = (vipFrameGrey& img) { return this->copy(img); };

		/// Overload equals (+=) operator for two images.
		vipFrameGrey& operator += (vipFrameGrey& img) ;

		/// Overload equals (-=) operator for two images.
		vipFrameGrey& operator -= (vipFrameGrey& img) ;

		/// Overload equals (+=) operator for Image and constant
		vipFrameGrey& operator += (PixelGrey offset) ;

		/// Overload equals (-=) operator for Image and constant
		vipFrameGrey& operator -= (PixelGrey offset) ;

		/// Overload equals (/=) operator for Image and constant
		vipFrameGrey& operator /= (float factor) ;

		/// Overload equals (*=) operator for Image and constant
		vipFrameGrey& operator *= (float factor) ;


		vipFrameGrey& operator >> (vipFrameYUV420& img);
		vipFrameGrey& operator >> (vipFrameRGB24& img);
		vipFrameGrey& operator >> (vipFrameRGB96& img);

		void operator << (const vipFrameYUV420& img);
		void operator << (const vipFrameRGB24& img);
		void operator << (const vipFrameRGB96& img);

		VIPFRAME_PROFILE getProfile() { return vipFrame::VIPFRAME_MONO; };

		VIPFRAME_CHANNEL_TYPE getChannelType() { return vipFrame::VIPFRAME_CT_PACKED; };

		int getFOURCC() { return 0;};
 };


#endif	// __VIPLIB_VIPFRAMEGREY_H__

