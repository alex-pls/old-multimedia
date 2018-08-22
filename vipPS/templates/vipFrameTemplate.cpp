/** @file %FILENAME%.cpp
 *
 * File containing methods for the '%CLASSNAME%' class.
 * The header for this class can be found in %FILENAME%.h, check that file
 * for class description.
 *
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


#include "%FILENAME%.h"
//#include <math.h>

%VFI_START%
%CLASSNAME%::%CLASSNAME%() : vipFrame()
 {
	data = NULL;
	width = 0;
	height = 0;

	INFO("%CLASSNAME%::%CLASSNAME%() : vipFrame() [CONTRUCTOR]")
 }
%VFI_END%

%VFI_START%
%CLASSNAME%::%CLASSNAME%(unsigned int w, unsigned int h): vipFrame()
/**
 * Allocates an array of size width*height for storage of brightness.
 *
 * @param w The width  of the image.
 * @param h The height of the image.
 */
{
	data = NULL;
	reAllocCanvas(w, h);

	INFO("%CLASSNAME%::%CLASSNAME%(unsigned int w, unsigned int h) [CONTRUCTOR]")
	DEBUG(width)
	DEBUG(height)
 }
%VFI_END%

/**
 * @brief Copy Constructor, create an image from another image, copying memory.
 * @param img source color image (will be converted to greyscale).
 */
%CLASSNAME%::%CLASSNAME%(vipFrameRGB24& img): vipFrame()
 {
	INFO("%CLASSNAME%::%CLASSNAME%(vipFrameRGB24& img) [CONTRUCTOR]")

	data = NULL;
	reAllocCanvas(img.width, img.height);
	*this << img;

	DEBUG(width)
	DEBUG(height)
 }

%VFI_START%
/**
 * @brief Destructor currenly clear pixel data (array).
 */
%CLASSNAME%::~%CLASSNAME%()
{
	if ( data != NULL )
	    delete [] data;

	INFO("%CLASSNAME%::~%CLASSNAME%() [DESTRUCTOR]")
}
%VFI_END%


%VFI_START%
VIPRESULT %CLASSNAME%::reAllocCanvas(unsigned int w, unsigned int h)
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
%VFI_END%

%VFI_START%
VIPRESULT %CLASSNAME%::extractBrightness(unsigned char* buffer, unsigned int* size)
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
%VFI_END%

%VFI_START%
VIPRESULT %CLASSNAME%::setWhite()
 {
	if (width == 0 || height == 0 || data == NULL)
		return VIPRET_ILLEGAL_USE;

	memset(data, 255, width * height);
	return VIPRET_OK;
 }
%VFI_END%

%VFI_START%
VIPRESULT %CLASSNAME%::setBlack()
 {
	if (width == 0 || height == 0 || data == NULL)
		return VIPRET_ILLEGAL_USE;

	memset(data, 0, width * height);

	return VIPRET_OK;
 }
%VFI_END%


VIPRESULT %CLASSNAME%::setPixel(unsigned int x, unsigned int y, PixelGrey level)
/**
 * Method sets the brighness of a pixel specified by (x,y).
 * Throws an exception if coordinates are not valid.
 *
 * @param x,y   The coordinates of the pixel
 * @param level The brightness of the pixel
 */
{
	// Check that co-ords are valid.
	if ( x >= width || y >= height )
		return VIPRET_PARAM_ERR;

	data[y * width + x]  = level;

	return VIPRET_OK;
}

VIPRESULT %CLASSNAME%::setPixel(unsigned int x, unsigned int y, PixelRGB24 p)
 {
	// Check that co-ords are valid.
	if ( x >= width || y >= height )
		return VIPRET_PARAM_ERR;


	data[y * width + x] = (PixelGrey)((RED_COEF*(float)p[0]) +
	 										(GREEN_COEF*(float)p[1]) +
											(BLUE_COEF*(float)p[2]) 	);
	return VIPRET_OK;
 }


VIPRESULT %CLASSNAME%::getPixel(unsigned int x, unsigned int y, PixelGrey& p) const
/**
 * Method to return the brightness for pixel (x,y).
 * \note No check is made that x and y are in range.
 *
 * @param x,y The coordinates of the pixel.
 * @param p   Reference to the Pixel to store the pixels value in.
 */
{
	// Check that co-ords are valid.
	if ( x >= width || y >= height )
		return VIPRET_PARAM_ERR;

	p = data[y * width + x];
	return VIPRET_OK;
}


const PixelGrey& %CLASSNAME%::getPixel(unsigned int x, unsigned int y) const
/**
 * Method to return the brightness for pixel (x,y).
 * \note No check is made that x and y are in range.
 *
 * @param x,y The coordinates of the pixel.
 * @param p   Reference to the Pixel to store the pixels value in.
 */
{
	// Check that co-ords are valid.
	if ( x >= width || y >= height )
		throw "Invalid Coordinates in method vipFrameRGB::getPixel(unsigned int x, unsigned int y, PixelGrey p)";

	return data[y * width + x];
}



%CLASSNAME%& %CLASSNAME%::clearWith(PixelGrey p)
/**
 * Method sets the value of the brightness field to the specified intensity.
 *
 * @param k Value to clear the field to.
 */
{
	DEBUGMSG("%CLASSNAME%& %CLASSNAME%::clearWith(PixelGrey p)", p)

    PixelGrey *piter = data;

    for(unsigned int i=0; i < width * height; i++, piter++)
		*piter = p;

	return *this;
}


%CLASSNAME%& %CLASSNAME%::copy(%CLASSNAME%& img)
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



VIPRESULT %CLASSNAME%::invert()
/**
 * Calculates absolute values of brightness array
 *
 */
{
	INFO("void %CLASSNAME%::absolute()")

    PixelGrey *piter = data;
    for(unsigned int i=0; i < width * height; i++, piter++)
	*piter = 255 - *piter;

    return VIPRET_OK;
}

VIPRESULT %CLASSNAME%::threshold(PixelGrey thresh)
/**
 * Sets values below threshold to zero and those equal or above to 255
 *
 * @param thresh Threshold value
 */
{
    PixelGrey *piter = data;

    for(unsigned int i=0; i < width * height; i++, piter++)
		if ( *piter < thresh )
			*piter = 0;
		else
			*piter = 255;

    return VIPRET_OK;
}


%CLASSNAME%& %CLASSNAME%::operator >> (vipFrameYUV420& img)
/**
 * Copies all pixel data from img.
 * Throws an exception if images are of different size.
 *
 * @param img The image to copy the data from.
 */
{
	INFO("%CLASSNAME%& %CLASSNAME%::operator >> (vipFrameYUV420& img) [pushing data]")

	if ( width == 0 || height == 0 )
		throw "Cannot do that with empty image (no size)";

	if ( width != img.width || height != img.height)
		img.reAllocCanvas(width, height);

	//valid cos pixelgrey is uchar
	memcpy(img.data, data, width * height);
	memset(img.U, '\0', width * height / 2); // u+v set to 0

//	img.setBlack();
//	const unsigned int size = width * height;
//	for (unsigned int i=0; i < size; i++)
//		img.data[i] = (PixelGrey)( img.data[i] );
	return *this;
 }


%CLASSNAME%& %CLASSNAME%::operator >> (vipFrameRGB24& img)
/**
 * Copies all pixel data from img.
 * Throws an exception if images are of different size.
 *
 * @param img The image to copy the data from.
 */
{
	INFO("%CLASSNAME%& %CLASSNAME%::operator >> (vipFrameRGB24& img) [pushing data]")

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


%CLASSNAME%& %CLASSNAME%::operator >> (vipFrameRGB96& img)
/**
 * Copies all pixel data from img.
 * Throws an exception if images are of different size.
 *
 * @param img The image to copy the data from.
 */
{
	INFO("%CLASSNAME%& %CLASSNAME%::operator >> (vipFrameRGB& img) [pushing data]")


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

%CLASSNAME%& %CLASSNAME%::operator >> (vipFrameRGBA32& img)
/**
 * Copies all pixel data from img.
 * Throws an exception if images are of different size.
 *
 * @param img The image to copy the data from.
 */
{
	INFO("%CLASSNAME%& %CLASSNAME%::operator >> (vipFrameRGB& img) [pushing data]")


	if ( width == 0 || height == 0 )
		throw "Cannot do that with empty image (no size)";

	if ( width != img.width || height != img.height)
		img.reAllocCanvas(width, height);

//BUG

	return *this;
 }


void %CLASSNAME%::operator << (const vipFrameYUV420& img)
/**
 * Copies all pixel data from img.
 * Throws an exception if images are of different size.
 *
 * @param img The image to copy the data from.
 */
 {
	INFO("void %CLASSNAME%::operator << (const vipFrameYUV420& img) [importing data]")

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

void %CLASSNAME%::operator << (const vipFrameRGB24& img)
/**
 * Copies all pixel data from img.
 * Throws an exception if images are of different size.
 *
 * @param img The image to copy the data from.
 */
 {
	INFO("void %CLASSNAME%::operator << (const vipFrameRGB24& img) [importing data]")

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


void %CLASSNAME%::operator << (const vipFrameRGB96& img)
 {
	INFO("void %CLASSNAME%::operator << (const vipFrameRGB96& img) [importing data]")

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

void %CLASSNAME%::operator << (const vipFrameRGBA32& img)
/**
 * Copies all pixel data from img.
 * Throws an exception if images are of different size.
 *
 * @param img The image to copy the data from.
 */
 {
	INFO("void %CLASSNAME%::operator << (const vipFrameRGB24& img) [importing data]")

	if ( img.width == 0 || img.height == 0 )
		throw "Cannot do that with empty image (no size)";

	if ( width != img.width || height != img.height)
		reAllocCanvas(img.width, img.height);

//BUG
 }
