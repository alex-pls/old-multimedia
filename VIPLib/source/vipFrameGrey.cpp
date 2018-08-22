/** @file vipFrameGrey.cpp
 *
 * File containing methods for the 'vipFrameGrey' class.
 * The header for this class can be found in vipFrameGrey.h, check
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


#include "vipFrameGrey.h"
#include <math.h>

/**
 * @brief Default constructor, initialize height and width to 0.
 */
vipFrameGrey::vipFrameGrey() : vipFrame()
 {
	data = NULL;
	width = 0;
	height = 0;

	INFO("vipFrameGrey::vipFrameGrey() : vipFrame() [CONTRUCTOR]")
 }

/**
 * @brief Create an image with the given dimensions, allocates empty data.
 * @param width Width of the image
 * @param height Height of the image
 */
vipFrameGrey::vipFrameGrey(unsigned int w, unsigned int h)
{
	data = NULL;
	reAllocCanvas(w, h);

	INFO("vipFrameGrey::vipFrameGrey(unsigned int w, unsigned int h) [CONTRUCTOR]")
	DEBUG(width)
	DEBUG(height)
 }

/**
 * @brief Copy Constructor, create an image from another image, copying memory.
 * @param img source grey image.
 */
vipFrameGrey::vipFrameGrey(vipFrameGrey& img)

{
	data = NULL;
	reAllocCanvas(img.width, img.height);

	if ( width != 0 && height != 0 )
		memcpy(data, img.data, width * height * sizeof(PixelGrey));

	INFO("vipFrameGrey::vipFrameGrey(vipFrameGrey& img) [CONTRUCTOR]")
	DEBUG(width)
	DEBUG(height)
 }


/**
 * @brief Copy Constructor, create an image from another image, copying memory.
 * @param img source cache image (will be converted to greyscale).
 */
vipFrameGrey::vipFrameGrey(vipFrameYUV420& img)
 {
	INFO("vipFrameGrey::vipFrameGrey(vipFrameYUV420& img) [CONTRUCTOR]")

	data = NULL;
	reAllocCanvas(img.width, img.height);
	*this << img;

	DEBUG(width)
	DEBUG(height)
 }

/**
 * @brief Copy Constructor, create an image from another image, copying memory.
 * @param img source color image (will be converted to greyscale).
 */
vipFrameGrey::vipFrameGrey(vipFrameRGB24& img)
 {
	INFO("vipFrameGrey::vipFrameGrey(vipFrameRGB24& img) [CONTRUCTOR]")

	data = NULL;
	reAllocCanvas(img.width, img.height);
	*this << img;

	DEBUG(width)
	DEBUG(height)
 }

/**
 * @brief Copy Constructor, create an image from another image, copying memory.
 * @param img source color image (will be converted to greyscale).
 */
vipFrameGrey::vipFrameGrey(vipFrameRGB96& img)
 {
	INFO("vipFrameGrey::vipFrameGrey(vipFrameRGB96& img) [CONTRUCTOR]")

	data = NULL;
	reAllocCanvas(img.width, img.height);
	*this << img;

	DEBUG(width)
	DEBUG(height)
 }




/**
 * @brief Destructor currenly clear pixel data (array).
 */
vipFrameGrey::~vipFrameGrey()
{
	if ( data != NULL )
	    delete [] data;

	INFO("vipFrameGrey::~vipFrameGrey() [DESTRUCTOR]")
}

VIPRESULT vipFrameGrey::reAllocCanvas(unsigned int w, unsigned int h)
 {
	if (data != NULL)
		delete [] data;

	height = h;
	width = w;
	data = NULL;

	if ( width == 0 || height == 0)
		return VIPRET_PARAM_ERR;

	data = new PixelGrey[w * h];

	return VIPRET_OK;
 }

VIPRESULT vipFrameGrey::extractBrightness(unsigned char* buffer, unsigned int* size)
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

	memcpy (data, buffer, width*height);
	return VIPRET_OK;
 }

VIPRESULT vipFrameGrey::setWhite()
 {
	if (width == 0 || height == 0 || data == NULL)
		return VIPRET_ILLEGAL_USE;

	memset(data, 255, width * height);
	return VIPRET_OK;
 }

VIPRESULT vipFrameGrey::setBlack()
 {
	if (width == 0 || height == 0 || data == NULL)
		return VIPRET_ILLEGAL_USE;

	memset(data, 0, width * height);

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
VIPRESULT vipFrameGrey::setPixel(unsigned int x, unsigned int y, PixelGrey level)
{
	// Check that co-ords are valid.
	if ( x >= width || y >= height )
		return VIPRET_PARAM_ERR;

	data[y * width + x]  = level;

	return VIPRET_OK;
}

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
VIPRESULT vipFrameGrey::setPixel(unsigned int x, unsigned int y, PixelRGB24 p)
 {
	// Check that co-ords are valid.
	if ( x >= width || y >= height )
		return VIPRET_PARAM_ERR;


	data[y * width + x] = (PixelGrey)((RED_COEF*(float)p[0]) +
	 										(GREEN_COEF*(float)p[1]) +
											(BLUE_COEF*(float)p[2]) 	);
	return VIPRET_OK;
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
VIPRESULT vipFrameGrey::getPixel(unsigned int x, unsigned int y, PixelGrey& p) const
{
	// Check that co-ords are valid.
	if ( x >= width || y >= height )
		return VIPRET_PARAM_ERR;

	p = data[y * width + x];
	return VIPRET_OK;
}


const PixelGrey& vipFrameGrey::getPixel(unsigned int x, unsigned int y) const
{
	// Check that co-ords are valid.
	if ( x >= width || y >= height )
		throw "Invalid Coordinates in method vipFrameRGB::getPixel(unsigned int x, unsigned int y, PixelGrey p)";

	return data[y * width + x];
}


/**
 * @brief Clear all pixel to the specified value.
 *
 * @param bg a PixelRGB to overwrite on all image, default is black.
 *
 * @return current instance address.
 */
vipFrameGrey& vipFrameGrey::clearWith(PixelGrey p)
{
	DEBUGMSG("vipFrameGrey& vipFrameGrey::clearWith(PixelGrey p)", p)

    PixelGrey *piter = data;

    for(unsigned int i=0; i < width * height; i++, piter++)
		*piter = p;

	return *this;
}

VIPRESULT vipFrameGrey::setWidth(unsigned int newWidth)
 {
	if ( width != 0)
		return VIPRET_ILLEGAL_USE;

	width = newWidth;

	return VIPRET_OK;
 }

VIPRESULT vipFrameGrey::setHeight(unsigned int newHeight)
 {
	if ( height != 0)
		return VIPRET_ILLEGAL_USE;

	height = newHeight;

	return VIPRET_OK;
 }

vipFrameGrey& vipFrameGrey::copy(vipFrameGrey& img)
/**
 * Copies all pixel brightness to img.
 * Throws an exception if images are of different size.
 *
 * @param img The image to copy the brightness from.
 */
{
	/* check we're not trying to copy ourself */
	if (this == &img)
		throw "Source and Destination are same Image";

	/* First check images are the same size and valid */
	if (width  != img.width || height != img.height)
		throw "Difference in image dimensions";

	/* Perform copy */
	memcpy(data, img.data, width * height * sizeof(int));

	return *this;
}


/**
 * Adds fact to each brightness value
 *
 * @param fact Addition constant
 */
vipFrameGrey& vipFrameGrey::operator += (PixelGrey offset)
{
	INFO("vipFrameGrey& vipFrameGrey::operator += (PixelGrey offset)")

    PixelGrey *piter = data;

    for(unsigned int i=0; i < width * height; i++, piter++)
		*piter += offset;

    return *this;
}

/**
 * Subtracts fact from each brightness value
 *
 * @param fact Subtraction constant
 */
vipFrameGrey& vipFrameGrey::operator -= (PixelGrey offset)
{
	INFO("vipFrameGrey& vipFrameGrey::operator -= (PixelGrey offset)")

    PixelGrey *piter = data;

    for(unsigned int i=0; i < width * height; i++, piter++)
		*piter -= offset;

    return *this;
}

/**
 * Multiplies each brightness value by fact
 *
 * @param fact Multiplication constant
 */
vipFrameGrey& vipFrameGrey::operator *= (float factor)
{
	INFO("vipFrameGrey& vipFrameGrey::operator *= (float factor)")

    PixelGrey *piter = data;

    for(unsigned int i=0; i < width * height; i++, piter++)
		*piter = (int)( ( (float) *piter ) * factor );

    return *this;
}

/**
 * Divides each brightness value by fact
 *
 * @param fact Division constant
 */
vipFrameGrey& vipFrameGrey::operator /= (float factor)
{
	INFO("vipFrameGrey& vipFrameGrey::operator /= (float factor)")

    PixelGrey *piter = data;

    for(unsigned int i=0; i < width * height; i++, piter++)
		*piter = (int)(( (float) *piter ) / factor );

    return *this;
}

/**
 * Subtracts img.brightness from brightness array
 *
 * @param img The image to be subtracted
 */
vipFrameGrey& vipFrameGrey::operator += (vipFrameGrey& img)
{
	INFO("vipFrameGrey& vipFrameGrey::operator += (vipFrameGrey& img)")

	if (width != img.width || height != img.height)
		throw "Difference in vipFrameRGB Dimensions";

    for(unsigned int i=0; i < width * height; i++)
        data[i] += img.data[i];

    return *this;
}

/**
 * Subtracts img.brightness from brightness array
 *
 * @param img The image to be subtracted
 */
vipFrameGrey& vipFrameGrey::operator -= (vipFrameGrey& img)
{
	INFO("vipFrameGrey& vipFrameGrey::operator -= (vipFrameGrey& img)")

	if (width != img.width || height != img.height)
		throw "Difference in vipFrameRGB Dimensions";

    for(unsigned int i=0; i < width * height; i++)
        data[i] -= img.data[i];

    return *this;
}


/**
 * Calculates absolute values of brightness array
 *
 */
VIPRESULT vipFrameGrey::invert()
{
	INFO("void vipFrameGrey::absolute()")

    PixelGrey *piter = data;
    for(unsigned int i=0; i < width * height; i++, piter++)
	*piter = 255 - *piter;

    return VIPRET_OK;
}

/**
 * Sets values below threshold to zero and those equal or above to 255
 *
 * @param thresh Threshold value
 */
VIPRESULT vipFrameGrey::threshold(PixelGrey thresh)
{
    PixelGrey *piter = data;

    for(unsigned int i=0; i < width * height; i++, piter++)
		if ( *piter < thresh )
			*piter = 0;
		else
			*piter = 255;

    return VIPRET_OK;
}

/**
 * Copies all pixel data from img.
 * Throws an exception if images are of different size.
 *
 * @param img The image to copy the data from.
 * @note	Tested and working by Marco Verza as of 06/03/2008
 */
vipFrameGrey& vipFrameGrey::operator >> (vipFrameYUV420& img)
{
	INFO("vipFrameGrey& vipFrameGrey::operator >> (vipFrameYUV420& img) [pushing data]")

	if ( width == 0 || height == 0 )
		throw "Cannot do that with empty image (no size)";

	if ( width != img.width || height != img.height)
		img.reAllocCanvas(width, height);

	//valid cos pixelgrey is uchar
	memcpy(img.data, data, width * height);
	memset(img.U, 128, width * height / 2); // u+v set to 0???? // Marco Verza fix: set to 128..

//	img.setBlack();
//	const unsigned int size = width * height;
//	for (unsigned int i=0; i < size; i++)
//		img.data[i] = (unsigned char)( data[i] );
	return *this;
 }

/**
 * Copies all pixel data from img.
 * Throws an exception if images are of different size.
 *
 * @param img The image to copy the data from.
 */
vipFrameGrey& vipFrameGrey::operator >> (vipFrameRGB24& img)
{
	INFO("vipFrameGrey& vipFrameGrey::operator >> (vipFrameRGB24& img) [pushing data]")

	if ( width == 0 || height == 0 )
		throw "Cannot do that with empty image (no size)";

	if ( width != img.width || height != img.height)
		img.reAllocCanvas(width, height);

	const unsigned int size = width * height;
	for (unsigned int i=0; i < size; i++)
	 {
		img.data[i][0] = data[i];
		img.data[i][1] = data[i];
		img.data[i][2] = data[i];
	 }

	return *this;
 }

/**
 * Copies all pixel data from img.
 * Throws an exception if images are of different size.
 *
 * @param img The image to copy the data from.
 */
vipFrameGrey& vipFrameGrey::operator >> (vipFrameRGB96& img)
{
	INFO("vipFrameGrey& vipFrameGrey::operator >> (vipFrameRGB& img) [pushing data]")


	if ( width == 0 || height == 0 )
		throw "Cannot do that with empty image (no size)";

	if ( width != img.width || height != img.height)
		img.reAllocCanvas(width, height);

	const unsigned int size = width * height;
	for (unsigned int i=0; i < size; i++)
	 {
		img.data[i][0] = (int) data[i];
		img.data[i][1] = (int) data[i];
		img.data[i][2] = (int) data[i];
	 }

	return *this;
 }



/**
 * Copies all pixel data from img.
 * Throws an exception if images are of different size.
 *
 * @param img The image to copy the data from.
 */
void vipFrameGrey::operator << (const vipFrameYUV420& img)
 {
	INFO("void vipFrameGrey::operator << (const vipFrameYUV420& img) [importing data]")

	if ( img.width == 0 || img.height == 0 )
		throw "Cannot do that with empty image (no size)";

	if ( width != img.width || height != img.height)
		reAllocCanvas(img.width, img.height);

	//valid cos pixelgrey is uchar

	memcpy(data, img.data, width * height);

//	const unsigned int size = width * height;
//	for (unsigned int i=0; i < size; i++)
//		data[i] = (PixelGrey)( img.data[i] );

 }

/**
 * Copies all pixel data from img.
 * Throws an exception if images are of different size.
 *
 * @param img The image to copy the data from.
 */
void vipFrameGrey::operator << (const vipFrameRGB24& img)

 {
	INFO("void vipFrameGrey::operator << (const vipFrameRGB24& img) [importing data]")

	if ( img.width == 0 || img.height == 0 )
		throw "Cannot do that with empty image (no size)";

	if ( width != img.width || height != img.height)
		reAllocCanvas(img.width, img.height);

	const unsigned int size = width * height;
	for (unsigned int i=0; i < size; i++)
		data[i]	 = (PixelGrey) (	(RED_COEF  *(float) img.data[i][0])	+
									(GREEN_COEF*(float) img.data[i][1])	+
									(BLUE_COEF *(float) img.data[i][2])	);
 }



/**
 * Copies all pixel data from img.
 * Throws an exception if images are of different size.
 *
 * @param img The image to copy the data from.
 */
void vipFrameGrey::operator << (const vipFrameRGB96& img)
 {
	INFO("void vipFrameGrey::operator << (const vipFrameRGB96& img) [importing data]")

	if ( img.width == 0 || img.height == 0 )
		throw "Cannot do that with empty image (no size)";

	if ( width != img.width || height != img.height)
		reAllocCanvas(img.width, img.height);

	const unsigned int size = width * height;
	for (unsigned int i=0; i < size; i++)
		data[i]	 = (PixelGrey) (	(RED_COEF  *(float) img.data[i][0])	+
									(GREEN_COEF*(float) img.data[i][1])	+
									(BLUE_COEF *(float) img.data[i][2])	);
 }


