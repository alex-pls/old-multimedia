/** @file vipFrameRGB24.cpp
 *
 * File containing methods for the 'vipFrameRGB24' class.
 * The header for this class can be found in vipFrameRGB24.h, check
 * that file for class description.
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



#include "vipFrameRGB24.h"

vipFrameRGB24::vipFrameRGB24()  : vipFrame()
 {
	height = 0;
	width = 0;
	data = NULL;
	autoFreeData = true;
 }

/**
 * @brief Create an image with the given dimensions, allocates empty data.
 * @param width Width of the image
 * @param height Height of the image
 */
vipFrameRGB24::vipFrameRGB24(unsigned int w, unsigned int h)
 {
	data = NULL;
	reAllocCanvas(w, h);
	autoFreeData = true;
 }


/**
 * @brief Create an image from another image, copying memory.
 */
vipFrameRGB24::vipFrameRGB24(vipFrameRGB24& img)
 {
	data = NULL;
	reAllocCanvas(img.width, img.height);

	*this = img;

	autoFreeData = true;
 }

/**
 * @brief Copy Constructor, create an image from another image, copying memory.
 * @param img source image.
 */
vipFrameRGB24::vipFrameRGB24(vipFrameRGB96& img)
 {
	data = NULL;
	reAllocCanvas(img.width, img.height);

	*this << img;

	autoFreeData = true;
 }



/**
 * @brief Destructor currenly clear pixel data (array).
 */
vipFrameRGB24::~vipFrameRGB24()
 {
	if ( autoFreeData && data != NULL )
            delete [] data;
 }


VIPRESULT vipFrameRGB24::reAllocCanvas(unsigned int w, unsigned int h)
 {
	if (data != NULL)
		delete [] data;

	height = h;
	width = w;
	data = NULL;

	if ( width == 0 || height == 0)
		return VIPRET_PARAM_ERR;

	data = new PixelRGB24[width * height];

	return VIPRET_OK;
 }

VIPRESULT vipFrameRGB24::setBlack()
 {
	if (width == 0 || height == 0 || data == NULL)
		return VIPRET_ILLEGAL_USE;

	memset(data, '\0', width * height * sizeof(PixelRGB24) );

	return VIPRET_OK;
 }

VIPRESULT vipFrameRGB24::setWhite()
 {
	if (width == 0 || height == 0 || data == NULL)
		return VIPRET_ILLEGAL_USE;

	memset(data, 255, width * height  * sizeof(PixelRGB24) );

	return VIPRET_OK;
 }

VIPRESULT vipFrameRGB24::extractBrightness(unsigned char* buffer, unsigned int* size)
 {
	if (width == 0 || height == 0 || data == NULL)
		return VIPRET_ILLEGAL_USE;

	if (buffer == NULL)
	 {
		 if ( size == NULL)
		 	return VIPRET_PARAM_ERR;

		 *size = width*height;
		 return VIPRET_OK;
	 }

	return VIPRET_NOT_IMPLEMENTED;
 }


/**
 * @brief Get pixel (x, y) value and store it to p.
 *
 * @param x x position of the pixel.
 * @param y y position of the pixel.
 * @param p address to store selected pixel's value.
 *
 * @note No check is made that x and y are in range.
 */
VIPRESULT vipFrameRGB24::getPixel(unsigned int x, unsigned int y, PixelRGB24& p)
 {
	#ifdef _vipFrameRGB24_SLOWMODE
		if ( x >= width || y >= height )
			throw "Invalid Coordinates in method vipFrameRGB24::getPixel(unsigned int x, unsigned int y, PixelRGB& p)";
	#endif //_vipFrameRGB24_SLOWMODE

	unsigned int offset = y * width + x;

	p[RED]	= data[offset][RED];
	p[GREEN]= data[offset][GREEN];
	p[BLUE]	= data[offset][BLUE];

	return VIPRET_OK;
 }

/**
 * @brief Set pixel (x, y) to the specified value.
 *
 * @param x x position of the pixel.
 * @param y y position of the pixel.
 * @param p new value for the selected coords.
 *
 * @note No check is made that x and y are in range.
 */
VIPRESULT vipFrameRGB24::setPixel(unsigned int x, unsigned int y, PixelRGB24 p)
 {
	#ifdef _vipFrameRGB24_SLOWMODE
		if ( x >= width || y >= height )
			throw "Invalid Coordinates in method vipFrameRGB24::setPixel(unsigned int x, unsigned int y, PixelRGB p)";
	#endif //_vipFrameRGB24_SLOWMODE

	data[y * width + x] = p;

	return VIPRET_OK;
 }


/**
 * @brief Clear all pixel to the specified value.
 *
 * @param bg a PixelRGB to overwrite on all image.
 *
 * @return current instance address.
 */
vipFrameRGB24& vipFrameRGB24::clearWith(PixelRGB24& p)
 {
	if ( data == NULL )
		throw "Image is empty.";

	for ( unsigned int i=0; i < width * height; i++)
		data[i] = p;

	return *this;
 }

/**
 * @brief Copies all pixel data from img.
 *        Throws an exception if images are of different size.
 *
 * @param img The image to copy the data from.
 *
 * @return current instance.
 */
vipFrameRGB24& vipFrameRGB24::operator = (vipFrameRGB24& img)
 {
	/* check we're not trying to copy ourself */
	if (this == &img)
        	return *this;

	/* First check images are the same size and valid */
	if (width != img.width || height != img.height)
		reAllocCanvas(img.width, img.height);

	if ( width == 0 || height == 0 )
		throw "Cannot do that with empty image (no size)";

	/* Perform copy */
	memcpy(data, img.data, width * height * sizeof(PixelRGB24));

	return *this;
 }


vipFrameRGB24& vipFrameRGB24::operator += (vipFrameRGB24& img)
{
	INFO("vipFrameRGB24& vipFrameRGB24::operator += (vipFrameRGB24& img)")

	if (width != img.width || height != img.height)
		throw "Difference in vipFrameYUV420 Dimensions";

    for(unsigned int i=0; i < width * height; i++)
        data[i] += img.data[i];

    return *this;
}



vipFrameRGB24& vipFrameRGB24::operator -= (vipFrameRGB24& img)
{
	INFO("vipFrameRGB24& vipFrameRGB24::operator += (vipFrameRGB24& img)")

	if (width != img.width || height != img.height)
		throw "Difference in vipFrameYUV420 Dimensions";

    for(unsigned int i=0; i < width * height; i++)
        data[i] -= img.data[i];

    return *this;
}






vipFrameRGB24& vipFrameRGB24::operator >> (vipFrameYUV420& img)
 {
	INFO("vipFrameRGB24& vipFrameRGB24::operator >> (vipFrameYUV420& img) [pushing data]")

	if ( width == 0 || height == 0 )
		throw "Cannot do that with empty image (no size)";

	if ( width != img.width || height != img.height )
		img.reAllocCanvas(width, height);

	unsigned char* tmpdata = new unsigned char[width*height*3];
	vipUtility::conv_PixelRGB24toPlanarYUV444( img.data, tmpdata, width, height );
	vipUtility::conv_PlanarYUV444toPlanarYUV420( tmpdata, img.data, width, height );

	delete tmpdata;
	return *this;
 }


vipFrameRGB24& vipFrameRGB24::operator >> (vipFrameYUV444& img)
 {
	INFO("vipFrameRGB24& vipFrameRGB24::operator >> (vipFrameYUV444& img) [pushing data]")

	if ( width == 0 || height == 0 )
		throw "Cannot do that with empty image (no size)";

	if ( width != img.width || height != img.height )
		img.reAllocCanvas(width, height);

	vipUtility::conv_PixelRGB24toPlanarYUV444( (unsigned char*)data, img.data, width, height );

	return *this;
 }

vipFrameRGB24& vipFrameRGB24::operator >> (vipFrameRGB96& img)
 {
	INFO("vipFrameRGB24& vipFrameRGB24::operator >> (vipFrameRGB96& img) [pushing data]")

	if ( width == 0 || height == 0 )
		throw "Cannot do that with empty image (no size)";

	if ( width != img.width || height != img.height )
		img.reAllocCanvas(width, height);

	unsigned char* dataPtr = static_cast<unsigned char*>( data[0] );
	int* destPtr = static_cast<int*>( img.data[0] );

    for(unsigned int i=0; i < width * height * 3; i++)
        *(destPtr++) = (int) (*dataPtr++);

	return *this;
 }




void vipFrameRGB24::operator << (const vipFrameYUV420& img)
{
	INFO("void vipFrameRGB24::operator << (const vipFrameYUV420& img) [importing data]")

	if ( img.width == 0 || img.height == 0 )
		throw "Cannot do that with empty image (no size)";

	if ( width != img.width || height != img.height )
		reAllocCanvas(img.width, img.height);

//BUG

 }


void vipFrameRGB24::operator << (const vipFrameRGB96& img)
{
	INFO("void vipFrameRGB24::operator << (const vipFrameRGB32& img) [importing data]")

	if ( img.width == 0 || img.height == 0 )
		throw "Cannot do that with empty image (no size)";

	if ( width != img.width || height != img.height )
		reAllocCanvas(img.width, img.height);

	unsigned char* dataPtr = static_cast<unsigned char*>( data[0] );
	int* srcPtr = static_cast<int*>( img.data[0] );

    for(unsigned int i=0; i < width * height * 3; i++)
        *(dataPtr++) = (unsigned char) (*srcPtr++);

 }









