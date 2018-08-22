/** @file vipFrameRGB96.cpp
 *
 * File containing methods for the 'vipFrameRGB96' class.
 * The header for this class can be found in vipFrameRGB96.h, check
 * that file for class description.
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



#include "vipFrameRGB96.h"
#include "vipUtility.h"
#include <math.h>

vipFrameRGB96::vipFrameRGB96() : vipFrame()
 {
	INFO("vipFrameRGB96::vipFrameRGB96() : vipFrame() [CONTRUCTOR]")
	data = NULL;
	width = 0;
	height = 0;
 }

vipFrameRGB96::vipFrameRGB96(unsigned int w, unsigned int h)
/**
 * Allocates an array of size width*height for storage of red, green and
 * blue data.
 * Sets the parameters Width and Height to the inputs width and height.
 *
 * @param w The Width  of the image.
 * @param h The Height of the image.
 */
 {
	data = NULL;
	reAllocCanvas(w, h);

	INFO("vipFrameRGB96::vipFrameRGB96(unsigned int w, unsigned int h) [CONTRUCTOR]")
	DEBUG(width)
	DEBUG(height)
 }


vipFrameRGB96::vipFrameRGB96(vipFrameRGB96& img)
/**
 * Initialise to a new RGBImage identical to the specified image
 *
 * @param img The RGBImage to copy
 */
 {
	data = NULL;
	reAllocCanvas(img.width, img.height);

	*this = img;

	INFO("vipFrameRGB96::vipFrameRGB96(vipFrameRGB96& img) [CONTRUCTOR]")
	DEBUG(width)
	DEBUG(height)
 }


vipFrameRGB96::vipFrameRGB96(vipFrameRGB24& img)
/**
 * Initialise to a new RGBImage identical to the specified image
 *
 * @param img The RGBImage to copy
 */
 {
	data = NULL;
	reAllocCanvas(img.width, img.height);

	*this << img;

	INFO("vipFrameRGB96::vipFrameRGB96(vipFrameRGB96& img) [CONTRUCTOR]")
	DEBUG(width)
	DEBUG(height)
 }




/**
 * Destructor for vipFrameRGB96 class. Frees memory allocated to array:
 */
vipFrameRGB96::~vipFrameRGB96()
{
	INFO("vipFrameRGB96::~vipFrameRGB96() [DESTRUCTOR]")

	if ( autoFreeData && data != NULL )
		delete [] data;
}

VIPRESULT vipFrameRGB96::reAllocCanvas(unsigned int w, unsigned int h)
 {

	if (data != NULL)
		delete [] data;

	height = h;
	width = w;
	data = NULL;

	if ( width == 0 || height == 0)
		return VIPRET_PARAM_ERR;

	data = new PixelRGB96[width * height];

	return VIPRET_OK;
 }

VIPRESULT vipFrameRGB96::setBlack()
 {
	if (width == 0 || height == 0 || data == NULL)
		return VIPRET_ILLEGAL_USE;

	memset(data, '\0', width * height * sizeof(PixelRGB96) );

	return VIPRET_OK;
 }

VIPRESULT vipFrameRGB96::setWhite()
 {
	if (width == 0 || height == 0 || data == NULL)
		return VIPRET_ILLEGAL_USE;

	memset(data, 255, width * height  * sizeof(PixelRGB96) );

	return VIPRET_OK;
 }


VIPRESULT vipFrameRGB96::extractBrightness(unsigned char* buffer, unsigned int* size)
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

VIPRESULT vipFrameRGB96::setPixel(unsigned int x, unsigned int y, PixelRGB96 p)
/**
 * Method sets the pixel at (x,y) from the Pixel specified.
 *
 * @param x,y The coordinates of the pixel
 * @param p   The Pixel with values red, green and blue
 */
{
	// Check that co-ords are valid.
	if ( x >= width || y >= height )
		throw "Invalid Coordinates in method vipFrameRGB96::setPixel(unsigned int x, unsigned int y, PixelRGB96 p)";

	data[y * width + x] = p;

	return VIPRET_OK;
}


VIPRESULT vipFrameRGB96::setRGB(unsigned int x, unsigned int y, int red, int green, int blue)
/**
 * Method sets the red, green and blue values of a pixel specified by (x,y).
 * Throws an exception if coordinates are not valid.
 *
 * @param x,y   The coordinates of the pixel
 * @param red   The value of the RED field
 * @param green The value of the GREEN field
 * @param blue  The value of the BLUE field
 */
{
	// Check that co-ords are valid.
	if ( x >= width || y >= height )
		throw "Invalid Coordinates in method vipFrameRGB96::setRGB(unsigned int x, unsigned int y, int red, int green, int blue)";

	unsigned int offset = y * width + x;

	data[offset][RED]   = red;
	data[offset][GREEN] = green;
	data[offset][BLUE]  = blue;

	return VIPRET_OK;
 }


VIPRESULT vipFrameRGB96::setChannel(unsigned int x, unsigned int y, ChannelRGB fs, int value)
/**
 * Method sets the selected fields value of a pixel specified by (x,y).
 * Throws an exception if coordinates are not valid.
 *
 * @param x,y   The coordinates of the pixel.
 * @param fs    The selected Field.
 * @param value The value to set the field to.
 */
{
	// Check that co-ords are valid.
	if ( x >= width || y >= height )
		throw "Invalid Coordinates in method vipFrameRGB96::setChannel(unsigned int x, unsigned int y, ChannelRGB fs, int value)";

	unsigned int offset = y * width + x;
	data[offset][fs] = value;

	return VIPRET_OK;
 }



VIPRESULT vipFrameRGB96::getPixel(unsigned int x, unsigned int y, PixelRGB96& p) const
/**
 * Method to return values for pixel (x,y) in RGB Pixel p.
 *
 * @note No check is made that x and y are in range.
 *
 * @param x,y The coordinates of the pixel.
 * @param p   A Reference to the pixel to store the values in.
 */
{
	// Check that co-ords are valid.
	if ( x >= width || y >= height )
		throw "Invalid Coordinates in method vipFrameRGB96::setChannel(unsigned int x, unsigned int y, ChannelRGB fs, int value)";

	unsigned int offset = y * width + x;

	p[ RED ] = data[offset][RED];
	p[GREEN] = data[offset][GREEN];
	p[ BLUE] = data[offset][BLUE];

	return VIPRET_OK;
 }

const PixelRGB96& vipFrameRGB96::getPixel(unsigned int x, unsigned int y) const
{
	// Check that co-ords are valid.
	if ( x >= width || y >= height )
		throw "Invalid Coordinates in method vipFrameRGB96::setChannel(unsigned int x, unsigned int y, ChannelRGB fs, int value)";

	return data[y * width + x];

}



VIPRESULT vipFrameRGB96::getChannel(unsigned int x, unsigned int y, ChannelRGB fs) const
/**
 * Method to return slected fields value for pixel (x,y).
 * \note No check is made that x and y are in range.
 *
 * @param x,y The coordinates of the pixel.
 *
 * @return The selected fields value.
 */
{
	// Check that co-ords are valid.
	if ( x >= width || y >= height )
		throw "Invalid Coordinates in method vipFrameRGB96::setChannel(unsigned int x, unsigned int y, ChannelRGB fs, int value)";

	unsigned int offset = y * width + x;
	return data[offset][fs];

	return VIPRET_OK;
 }


vipFrameRGB96& vipFrameRGB96::clear(int k)
/**
 * Method sets values of all three colour fields to the specified colour.
 *
 * @param k Value to clear the field to.
 */
{
	DEBUGMSG("vipFrameRGB96& vipFrameRGB96::clear(int k)", k)

	int *start = data[0];
	int *end   = start + width * height * 3;

	for (int *d = start; d < end; d++)
		*d = k;

	return *this;
}


vipFrameRGB96& vipFrameRGB96::clearWith(PixelRGB96& p)
/**
 * Method sets all pixels to the specified pixel.
 *
 * @param p Pixel to set to.
 */
{
	DEBUGMSG("vipFrameRGB96& vipFrameRGB96::clearWith(PixelRGB96& p)", p)

	int *start = data[0];
	int *end   = start + width * height * 3;

	for (int *d = start; d < end; d += 3) {
		d[ RED ] = p[ RED ];
		d[GREEN] = p[GREEN];
		d[ BLUE] = p[ BLUE];
	}

	return *this;
}


vipFrameRGB96& vipFrameRGB96::clearChannel(ChannelRGB channel, int color)
/**
 * Method sets all pixels of currently selected field to specified colour
 *
 * @param color  Value to clear the field to.
 * @param channel The field so clear, one of (RED, GREEN, BLUE).
 */
{
	INFO("vipFrameRGB96& vipFrameRGB96::clearChannel(ChannelRGB channel, int color)")
	DEBUG(channel)
	DEBUG(color)

	int *start = data[0];
	int *end   = start + width * height * 3;

	for (int *d = start + channel; d < end; d += 3)
		*d = color;

	return *this;
}

VIPRESULT vipFrameRGB96::setWidth(unsigned int newWidth)
 {
	if ( width != 0)
		return VIPRET_ILLEGAL_USE;

	width = newWidth;

	return VIPRET_OK;
 }

VIPRESULT vipFrameRGB96::setHeight(unsigned int newHeight)
 {
	if ( height != 0)
		return VIPRET_ILLEGAL_USE;

	height = newHeight;

	return VIPRET_OK;
 }


vipFrameRGB96& vipFrameRGB96::copy(vipFrameRGB96& img)
/**
 * Copies all pixel data from img.
 * Throws an exception if images are of different size.
 *
 * @param img The image to copy the data from.
 */
{
	INFO("vipFrameRGB96& vipFrameRGB96::copy(vipFrameRGB96& img)")

	/* check we're not trying to copy ourself */
	if (this == &img)
		throw "Source and Destination are same Image";

	/* First check images are the same size and valid */
	if (width != img.width || height != img.height)
		throw "Difference in vipFrameRGB96 Dimensions";

	/* Perform copy */
	memcpy(data, img.data, width * height * sizeof(PixelRGB96));

	return *this;
}


vipFrameRGB96& vipFrameRGB96::operator += (vipFrameRGB96& img)
{
	INFO("vipFrameRGB96& vipFrameRGB96::operator += (vipFrameRGB96& img)")

	if (width != img.width || height != img.height)
		throw "Difference in vipFrameRGB96 Dimensions";

    for(unsigned int i=0; i < width * height; i++)
        data[i] += img.data[i];

    return *this;
}


vipFrameRGB96& vipFrameRGB96::operator -= (vipFrameRGB96& img)
{
	INFO("vipFrameRGB96& vipFrameRGB96::operator -= (vipFrameRGB96& img)")

	if (width != img.width || height != img.height)
		throw "Difference in vipFrameRGB96 Dimensions";

    for(unsigned int i=0; i < width * height; i++)
        data[i] -= img.data[i];

    return *this;
}

//vipFrameRGB96& vipFrameRGB96::operator >> (vipFrameYUV420& img)
///**
// * Copies all pixel data to img.
// * Throws an exception if images are of different size.
// *
// * @param img The image to copy the data from.
// */
//{
//	INFO("vipFrameRGB96& vipFrameRGB96::operator >> (vipFrameYUV420& img) [pushing data]")
//
//	if ( width == 0 || height == 0 )
//		throw "Cannot do that with empty image (no size)";
//
//	if (width != img.width || height != img.height)
//		img.reAllocCanvas(width, height);
//
////BUG
//	vipUtility::conv_PixelRGB96toPlanarYUV420((int*)data[0], img.data, width, height, 2);
//	return *this;
//}

/**
 * Copies all pixel data to img.
 * Throws an exception if images are of different size.
 *
 * @param img The image to copy the data from.
 */
vipFrameRGB96& vipFrameRGB96::operator >> (vipFrameRGB24& img)
{
	INFO("vipFrameRGB96& vipFrameRGB96::operator >> (vipFrameYUV420& img) [pushing data]")

	if ( width == 0 || height == 0 )
		throw "Cannot do that with empty image (no size)";

	if (width != img.width || height != img.height)
		img.reAllocCanvas(width, height);

	for (unsigned int i = 0; i < width*height; i++)
	 {
		img.data[i][RED] = (unsigned char)data[i][RED];
		img.data[i][GREEN] = (unsigned char)data[i][GREEN];
		img.data[i][BLUE] = (unsigned char)data[i][BLUE];
	 }

	return *this;
}


/**
 * Copies all pixel data from img.
 * Throws an exception if images are of different size.
 *
 * @param img The image to copy the data from.
 */
vipFrameRGB96& vipFrameRGB96::operator >> (vipFrameGrey& img)
{
	INFO("vipFrameRGB96& vipFrameRGB96::operator >> (vipFrameGrey& img) [pushing data]")

	if ( width == 0 || height == 0 )
		throw "Cannot do that with empty image (no size)";

	if (width != img.width || height != img.height)
		img.reAllocCanvas(width, height);

//BUG

	return *this;
}


/**
 * Copies all pixel data from img.
 * Throws an exception if images are of different size.
 *
 * @param img The image to copy the data from.
 */
void vipFrameRGB96::operator << (const vipFrameYUV420& img)
{
	INFO("void vipFrameRGB96::operator << (const vipFrameYUV420& img) [importing data]")

	if ( img.width == 0 || img.height == 0 )
		throw "Cannot do that with empty image (no size)";

	if (width != img.width || height != img.height)
		reAllocCanvas(img.width, img.height);

//BUG
//	vipUtility::conv_PlanarYUVtoPixelRGB(img.data, (int*)data[0], width, height);

}


/**
 * Copies all pixel data from img.
 * Throws an exception if images are of different size.
 *
 * @param img The image to copy the data from.
 */
void vipFrameRGB96::operator << (const vipFrameRGB24& img)
{
	INFO("void vipFrameRGB96::operator << (const vipFrameRGB24& img) [importing data]")

	if ( img.width == 0 || img.height == 0 )
		throw "Cannot do that with empty image (no size)";

	if (width != img.width || height != img.height)
		reAllocCanvas(img.width, img.height);

	/* Perform copy */
	for (unsigned int i = 0; i < width*height; i++)
	 {
		data[i][RED] = (int)img.data[i][RED];
		data[i][GREEN] = (int)img.data[i][GREEN];
		data[i][BLUE] = (int)img.data[i][BLUE];
	 }
}



/**
 * Copies all pixel data from img.
 * Throws an exception if images are of different size.
 *
 * @param img The image to copy the data from.
 */
void vipFrameRGB96::operator << (const vipFrameGrey& img)
{
	INFO("void vipFrameRGB96::operator << (const vipFrameGrey& img) [importing data]")

	if ( width == 0 || height == 0 || width != img.width || height != img.height )
	 {
		reAllocCanvas(img.width, img.height);
	 }

	float cp;
	for (unsigned int i=0; i< width*height; i++)
	 {
		cp = (float)img.data[i];
		data[i][0] = (int)(cp / RED_COEF );
		data[i][1] = (int)(cp / GREEN_COEF );
		data[i][2] = (int)(cp / BLUE_COEF );
	 }
//CHECKBUG

 }




/****************************************************************************\
 *       Extra doxygen comments and information relating to this file       *
\****************************************************************************/

/** @enum vipFrameRGB96::FieldSelector
 *
 * The FieldSelector selects the field (one of red, green and blue) for
 * the operation to be performed on.
 *
 ***** @var vipFrameRGB96::FieldSelector vipFrameRGB96::RED
 * Select the red field so the operation is only performed on the red
 * values of the image data.
 *
 ***** @var vipFrameRGB96::FieldSelector vipFrameRGB96::GREEN
 * Select the green field so the opertion is only performed on the green
 * values of the image data.
 *
 ***** @var vipFrameRGB96::FieldSelector vipFrameRGB96::BLUE
 * Select the blue field so the operation is only performed on the blue
 * values of the image data
 *
 */

