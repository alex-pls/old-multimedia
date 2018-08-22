/**
 *  @class   %CLASSNAME%
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


#ifndef __VIPLIB_%CLASSDEFINE%_H__
 #define __VIPLIB_%CLASSDEFINE%_H__


 #include "%SOURCEDIR%vipDefs.h"

 #include "%SOURCEDIR%vipFrame.h"
 #include "%SOURCEDIR%vipFrameYUV420.h"
 #include "%SOURCEDIR%vipFrameRGB24.h"
 #include "%SOURCEDIR%vipFrameRGB96.h"
 #include "%SOURCEDIR%vipFrameRGBA32.h"

/// Single pixel constsisting of an u char.
// typedef unsigned char 	 PixelGrey;


class %CLASSNAME% : public virtual vipFrame
{
	public:

		/**
		 * @var   GreyScale data array pointer. Size is width * height.
		 */
		PixelGrey *data;

	public:

%VFI_START%
		/**
		 * @brief Default constructor, initialize height and width to 0.
		 */
		%CLASSNAME%();
%VFI_END%

%VFI_START%
		/**
		 * @brief Create an image with the given dimensions, allocates empty data.
		 * @param width Width of the image
		 * @param height Height of the image
		 */
		%CLASSNAME%(unsigned int width, unsigned int height);
%VFI_END%

%VFI_START%
		/**
		 * @brief Copy Constructor, create an image from another image, copying memory.
		 * @param img source grey image.
		 */
		%CLASSNAME%(%CLASSNAME%& img);
%VFI_END%

		/**
		 * @brief Copy Constructor, create an image from another image, copying memory.
		 * @param img source color image (will be converted to greyscale).
		 */
		%CLASSNAME%(vipFrameRGB24& img);


%VFI_START%
		/**
		 * @brief Destructor currenly clear pixel data (array).
		 */
		~%CLASSNAME%();
%VFI_END%


%VFI_START%
		void* dump_buffer()
		 {
			return static_cast<void*>(data);
		 };
%VFI_END%

%VFI_START%
		VIPRESULT reAllocCanvas(unsigned int w, unsigned int h);
%VFI_END%

%VFI_START%
		unsigned int getBpp() { return sizeof(PixelGrey) * 8; };
%VFI_END%

%VFI_START%
		VIPRESULT setBlack();
%VFI_END%

%VFI_START%
		VIPRESULT setWhite();
%VFI_END%

%VFI_START%
		unsigned int getBufferSize() { return (unsigned int)( width * height); };
%VFI_END%

%VFI_START%
		VIPRESULT extractBrightness(unsigned char* buffer, unsigned int* size = NULL );
%VFI_END%



%VFI_START%
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
		%CLASSNAME%& clearWith(PixelGrey bg = 0);

		/// Copy data from image data from img.
		%CLASSNAME%& copy(%CLASSNAME%& img);


		/// Absolute value of brightness
		VIPRESULT invert();

		/// Threshold brightness
		VIPRESULT threshold(PixelGrey thresh) ;


	    %CLASSNAME%& operator >> (vipFrameYUV420& img);

		void operator << (const vipFrameYUV420& img);
		

		  %CLASSNAME%& operator >> (vipFrameRGB24& img);

		void operator << (const vipFrameRGB24& img);
		
			%CLASSNAME%& operator >> (vipFrameRGB96& img);

		void operator << (const vipFrameRGB96& img);
		
			%CLASSNAME%& operator >> (vipFrameRGBA32& img);

		void operator << (const vipFrameRGBA32& img);



%VFI_START%
		VIPFRAME_PROFILE getProfile()
		 {
			 return vipFrame::VIPFRAME_MONO;
		 };
%VFI_END%

%VFI_START%
		VIPFRAME_CHANNEL_TYPE getChannelType()
		 {
			 return vipFrame::VIPFRAME_CT_PACKED;
		 };
%VFI_END%

%VFI_START%
		int getFOURCC()
		 {
			 return 0;
		 };
%VFI_END%



 };


#endif	// __VIPLIB_%CLASSDEFINE%_H__

