/** @file vipFrameYUV444.cpp
 *
 * File containing methods for the 'vipFrameYUV444' class.
 * The header for this class can be found in vipFrameYUV444.h, check
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



#include "vipFrameYUV444.h"

#include "vipUtility.h"


vipFrameYUV444::vipFrameYUV444()  : vipFrame()
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
vipFrameYUV444::vipFrameYUV444(vipFrameYUV444& img)
 {
	data = NULL;
	reAllocCanvas(img.width, img.height);

	if ( width != 0 && height != 0 )
	 {
		memcpy(data, img.data, (int)(width * height * 3 * sizeof(unsigned char)));
	 }
	autoFreeData = true;
 }


/**
 * @brief Create an image with the given dimensions, allocates empty data.
 * @param width Width of the image
 * @param height Height of the image
 */
vipFrameYUV444::vipFrameYUV444(unsigned int w, unsigned int h)
 {
	data = NULL;
	reAllocCanvas(w, h);
	autoFreeData = true;
 }


/**
 * @brief Destructor currenly clear pixel data (array).
 */
vipFrameYUV444::~vipFrameYUV444()
 {
	if ( autoFreeData && data != NULL )
            delete [] data;
 }


VIPRESULT vipFrameYUV444::reAllocCanvas(unsigned int w, unsigned int h)
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

	data = new unsigned char[ (int)(width * height * 3) ];
	Y = data;
	U = data + width * height;
	V = data + (int)(width * height * 2);

	return VIPRET_OK;
 }


VIPRESULT vipFrameYUV444::setBlack()
 {
	if (width == 0 || height == 0 || data == NULL)
		return VIPRET_ILLEGAL_USE;

	memset(data, '\0', (int)(width * height * 3) );

	return VIPRET_OK;
 }

VIPRESULT vipFrameYUV444::setWhite()
 {
	if (width == 0 || height == 0 || data == NULL)
		return VIPRET_ILLEGAL_USE;

	memset(data, 255, width * height );
	memset(U, '\0', (int)(width * height * 2) );

	return VIPRET_OK;
 }

VIPRESULT vipFrameYUV444::extractBrightness(unsigned char* buffer, unsigned int* size)
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
VIPRESULT vipFrameYUV444::getPixel(unsigned int x, unsigned int y, unsigned char& value, ChannelYUV channel)
 {
	#ifdef _VIPFRAMECACHE24_SLOWMODE
		if ( x >= width || y >= height )
			throw "Invalid Coordinates in method vipFrameYUV444::getPixel(unsigned int x, unsigned int y, PixelRGB& p)";
	#endif //_VIPFRAMECACHE24_SLOWMODE

	if ( channel == vipFrameYUV444::Lum)
		value = data[y * width + x];
	else if ( channel == vipFrameYUV444::Cb )
	 {

//BUG -> da verificare
		value = data[width*height + (y * width) + x];

	 }
	else if ( channel == vipFrameYUV444::Cr )
	 {

//BUG -> da verificare
		value = data[width*height*2 + (y * width) + x];

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
VIPRESULT vipFrameYUV444::setPixel(unsigned int x, unsigned int y, unsigned char& value, ChannelYUV channel)
 {
	#ifdef _VIPFRAMECACHE24_SLOWMODE
		if ( x >= width || y >= height )
			throw "Invalid Coordinates in method vipFrameYUV444::setPixel(unsigned int x, unsigned int y, PixelRGB p)";
	#endif //_VIPFRAMECACHE24_SLOWMODE

	if ( channel == vipFrameYUV444::Lum)
		data[y * width + x] = value;
	else if ( channel == vipFrameYUV444::Cb )
	 {

//BUG -> da verificare
		data[width*height + (y * width) + x] = value;

	 }
	else if ( channel == vipFrameYUV444::Cr )
	 {

//BUG -> da verificare
		data[width*height*2 + (y * width) + x] = value;

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
vipFrameYUV444& vipFrameYUV444::clearWith(unsigned char* value, ChannelYUV channel)
 {
	if ( data == NULL )
		throw "Image is empty.";

	unsigned int start = 0;
	unsigned int end = 0;

	if ( channel == vipFrameYUV444::Lum )
	 {
		start = 0;
		end = width*height;
	 }
	else if ( channel == vipFrameYUV444::Cb )
	 {
		start = width*height;
		end = (int)(width*height*2);
	 }
	else if ( channel == vipFrameYUV444::Cr )
	 {
		start = (int)(width*height*2);
		end = (int)(width*height*3);
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
vipFrameYUV444& vipFrameYUV444::operator = (vipFrameYUV444& img)
 {
	/* check we're not trying to copy ourself */
	if (this == &img)
        	return *this;

	if ( img.width == 0 || img.height == 0 )
		throw "Cannot do that with empty image (no size)";

	if ( width != img.width || height != img.height )
		img.reAllocCanvas(img.width, img.height);

	memcpy(data, img.data, (int)(width * height * 3 * sizeof(unsigned char)) );

	return *this;
 }


vipFrameYUV444& vipFrameYUV444::operator += (vipFrameYUV444& img)
{
	INFO("vipFrameYUV444& vipFrameYUV444::operator += (vipFrameYUV444& img)")

	if (width != img.width || height != img.height)
		throw "Difference in vipFrameYUV444 Dimensions";

    for(unsigned int i=0; i < (unsigned int)(width * height * 3); i++)
        data[i] += img.data[i];

    return *this;
}

vipFrameYUV444& vipFrameYUV444::operator *= (vipFrameYUV444& img)
{
	INFO("vipFrameYUV444& vipFrameYUV444::operator += (vipFrameYUV444& img)")

	if (width != img.width || height != img.height)
		throw "Difference in vipFrameYUV444 Dimensions";

    for(unsigned int i=0; i < width * height * 3; i++)
        data[i] *= img.data[i];

    return *this;
}



vipFrameYUV444& vipFrameYUV444::operator >> (vipFrameYUV420& img)
 {
	INFO("vipFrameYUV444& vipFrameYUV444::operator >> (vipFrameYUV420& img) [pushing data]")

	if ( img.width == 0 || img.height == 0 || width != img.width || height != img.height )
		img.reAllocCanvas(width, height);

	vipUtility::conv_PlanarYUV444toPlanarYUV420(data, img.data, width, height);	// did not check if conv is correctly implemented

	return *this;
 }

vipFrameYUV444& vipFrameYUV444::operator << (vipFrameYUV420& img)
 {
	INFO("vipFrameYUV444& vipFrameYUV444::operator << (vipFrameYUV420& img) [pushing data]")

	if ( img.width == 0 || img.height == 0 || width != img.width || height != img.height )
		img.reAllocCanvas(width, height);

	vipUtility::conv_PlanarYUV420toPlanarYUV444( img.data, data, width, height);	// did not check if conv is correctly implemented

	return *this;
 }




vipFrameYUV444& vipFrameYUV444::operator >> (vipFrameRGB24& img)
 {
	INFO("vipFrameYUV444& vipFrameYUV444::operator >> (vipFrameRGB24& img) [pushing data]")

	if ( img.width == 0 || img.height == 0 || width != img.width || height != img.height )
		img.reAllocCanvas(width, height);

	vipUtility::conv_PlanarYUV444toPixelRGB24( data, (unsigned char*)img.data, width, height);	// did not check if conv is correctly implemented

	return *this;
 }


vipFrameYUV444& vipFrameYUV444::operator >> (vipFrameHSV& img)
 {
	INFO("vipFrameYUV444& vipFrameYUV444::operator >> (vipFrameHSV& img) [pushing data]")

	if ( img.width == 0 || img.height == 0 || width != img.width || height != img.height )
		img.reAllocCanvas(width, height);

	// marcoverza_todo: fix and then check this conversion
	double sat_range = 0, sat_average = 0;
	vipUtility::conv_PlanarYUV444toPixelHSV( data, img.data, width, height, &sat_range, &sat_average );	// did not check if conv is correctly implemented
	// anyway, why does conv method require a float* parameter? bug?

	return *this;
 }




void vipFrameYUV444::operator << (const vipFrameRGB24& img)
{
	INFO("void vipFrameYUV444::operator << (const vipFrameYUV444& img) [importing data]")

	if ( width == 0 || height == 0 || width != img.width || height != img.height )
		reAllocCanvas(img.width, img.height);

	vipUtility::conv_PixelRGB24toPlanarYUV444( (unsigned char *)img.data, data, width, height);	// did not check if conv is correctly implemented
 }







