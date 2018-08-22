/** @file vipFrameYUV420.cpp
 *
 * File containing methods for the 'vipFrameYUV420' class.
 * The header for this class can be found in vipFrameYUV420.h, check
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



#include "vipFrameYUV420.h"

#include "vipUtility.h"


vipFrameYUV420::vipFrameYUV420()  : vipFrame()
 {
	height = 0;
	width = 0;
	data = NULL;
	Y = NULL; // = data[0]
	U = NULL; // = data[ width*height ]
	V = NULL; // = data[ width*height*2 ]

	autoFreeData = true;
 }


/**
 * @brief Create an image from another image, copying memory.
 */
vipFrameYUV420::vipFrameYUV420(vipFrameYUV420& img)
 {
	data = NULL;
	reAllocCanvas(img.width, img.height);

	if ( width != 0 && height != 0 )
	 {
		memcpy(data, img.data, (int)(width * height * 1.5 * sizeof(unsigned char)));
	 }
	autoFreeData = true;
 }


/**
 * @brief Create an image with the given dimensions, allocates empty data.
 * @param width Width of the image
 * @param height Height of the image
 */
vipFrameYUV420::vipFrameYUV420(unsigned int w, unsigned int h)
 {
	data = NULL;
	reAllocCanvas(w, h);
	autoFreeData = true;
 }


/**
 * @brief Destructor currenly clear pixel data (array).
 */
vipFrameYUV420::~vipFrameYUV420()
 {
	if ( autoFreeData && data != NULL )
            delete [] data;
 }


VIPRESULT vipFrameYUV420::reAllocCanvas(unsigned int w, unsigned int h)
 {
	if (data != NULL)
	 {
		delete [] data;
		data = NULL;
	 }

	Y = NULL; // = data[0]
	U = NULL; // = data[ width*height ]
	V = NULL; // = data[ width*height*2 ]
	width = w;
	height = h;

	if ( width == 0 || height == 0)
		return VIPRET_PARAM_ERR;

	data = new unsigned char[ (int)(width * height * 1.5) ];
	Y = data;
	U = data + width * height;
	V = data + (int)(width * height * 1.25);

	return VIPRET_OK;
 }


VIPRESULT vipFrameYUV420::setBlack()
 {
	if (width == 0 || height == 0 || data == NULL)
		return VIPRET_ILLEGAL_USE;

	memset(data, '\0', (int)(width * height * 1.5) );

	return VIPRET_OK;
 }

VIPRESULT vipFrameYUV420::setWhite()
 {
	if (width == 0 || height == 0 || data == NULL)
		return VIPRET_ILLEGAL_USE;

	memset(data, 255, width * height );
	memset(U, '\0', (int)(width * height * 0.5) );

	return VIPRET_OK;
 }

VIPRESULT vipFrameYUV420::extractBrightness(unsigned char* buffer, unsigned int* size)
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



/**
 * @brief Get pixel (x, y) value and store it to p.
 *
 * @param x x position of the pixel.
 * @param y y position of the pixel.
 * @param p address to store selected pixel's value.
 *
 * @note No check is made that x and y are in range.
 */
VIPRESULT vipFrameYUV420::getPixel(unsigned int x, unsigned int y, unsigned char& value, ChannelYUV channel)
 {
	#ifdef _VIPFRAMECACHE24_SLOWMODE
		if ( x >= width || y >= height )
			throw "Invalid Coordinates in method vipFrameYUV420::getPixel(unsigned int x, unsigned int y, PixelRGB& p)";
	#endif //_VIPFRAMECACHE24_SLOWMODE

	if ( channel == vipFrameYUV420::Lum)
		value = data[y * width + x];
	else if ( channel == vipFrameYUV420::Cb )
	 {

//BUG -> da verificare
		value = data[width*height + (y * width)/4 + x/4];

	 }
	else if ( channel == vipFrameYUV420::Cr )
	 {

//BUG -> da verificare
		value = data[width*height + width*height/4 + (y * width)/4 + x/4];

	 }

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
VIPRESULT vipFrameYUV420::setPixel(unsigned int x, unsigned int y, unsigned char& value, ChannelYUV channel)
 {
	#ifdef _VIPFRAMECACHE24_SLOWMODE
		if ( x >= width || y >= height )
			throw "Invalid Coordinates in method vipFrameYUV420::setPixel(unsigned int x, unsigned int y, PixelRGB p)";
	#endif //_VIPFRAMECACHE24_SLOWMODE

	if ( channel == vipFrameYUV420::Lum)
		data[y * width + x] = value;
	else if ( channel == vipFrameYUV420::Cb )
	 {

//BUG -> da verificare
		data[width*height + (y * width)/4 + x/4] = value;

	 }
	else if ( channel == vipFrameYUV420::Cr )
	 {

//BUG -> da verificare
		data[width*height + width*height/4 + (y * width)/4 + x/4] = value;

	 }

	return VIPRET_OK;
 }


/**
 * @brief Clear all pixel to the specified value.
 *
 * @param bg a PixelRGB to overwrite on all image.
 *
 * @return current instance address.
 */
vipFrameYUV420& vipFrameYUV420::clearWith(unsigned char* value, ChannelYUV channel)
 {
	if ( data == NULL )
		throw "Image is empty.";

	unsigned int start = 0;
	unsigned int end = 0;

	if ( channel == vipFrameYUV420::Lum )
	 {
		start = 0;
		end = width*height;
	 }
	else if ( channel == vipFrameYUV420::Cb )
	 {
		start = width*height;
		end = (int)(width*height*1.25);
	 }
	else if ( channel == vipFrameYUV420::Cr )
	 {
		start = (int)(width*height*1.25);
		end = (int)(width*height*1.5);
	 }


	for (unsigned int i=start; i<end; i++)
	 {
		data[i] = *value;
	 }
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
vipFrameYUV420& vipFrameYUV420::operator = (vipFrameYUV420& img)
 {
	/* check we're not trying to copy ourself */
	if (this == &img)
        	return *this;

	if ( img.width == 0 || img.height == 0 )
		throw "Cannot do that with empty image (no size)";

	if ( width != img.width || height != img.height )
		img.reAllocCanvas(img.width, img.height);

	memcpy(data, img.data, (int)(width * height * 1.5 * sizeof(unsigned char)) );

	return *this;
 }


vipFrameYUV420& vipFrameYUV420::operator += (vipFrameYUV420& img)
{
	INFO("vipFrameYUV420& vipFrameYUV420::operator += (vipFrameYUV420& img)")

	if (width != img.width || height != img.height)
		throw "Difference in vipFrameYUV420 Dimensions";

    for(unsigned int i=0; i < (unsigned int)(width * height * 1.5); i++)
        data[i] += img.data[i];

    return *this;
}

vipFrameYUV420& vipFrameYUV420::operator *= (vipFrameYUV420& img)
{
	INFO("vipFrameYUV420& vipFrameYUV420::operator += (vipFrameYUV420& img)")

	if (width != img.width || height != img.height)
		throw "Difference in vipFrameYUV420 Dimensions";

    for(unsigned int i=0; i < width * height * 1.5; i++)
        data[i] *= img.data[i];

    return *this;
}







vipFrameYUV420& vipFrameYUV420::operator >> (vipFrameRGB24& img)
 {
	INFO("vipFrameYUV420& vipFrameYUV420::operator >> (vipFrameYUV420& img) [pushing data]")

	if ( img.width == 0 || img.height == 0 || width != img.width || height != img.height )
		img.reAllocCanvas(width, height);

	// marcoverza_todo: test
	unsigned char* tmp = new unsigned char[width*height*3];
	vipUtility::conv_PlanarYUV420toPlanarYUV444(data, tmp, width, height, true);
	vipUtility::conv_PlanarYUV444toPixelRGB24(tmp, (unsigned char*)img.data, width, height);

	delete tmp;
	return *this;
 }


void vipFrameYUV420::operator << (const vipFrameRGB24& img)
{
	INFO("void vipFrameYUV420::operator << (const vipFrameYUV420& img) [importing data]")

	if ( width == 0 || height == 0 || width != img.width || height != img.height )
		reAllocCanvas(img.width, img.height);

	unsigned char* tmp = new unsigned char[width*height*3];
	vipUtility::conv_PixelRGB24toPlanarYUV444( (unsigned char*)img.data, tmp, width, height);
	vipUtility::conv_PlanarYUV444toPlanarYUV420(tmp, data, width, height);
	// marcoverza_todo: test this

	delete tmp;
 }







