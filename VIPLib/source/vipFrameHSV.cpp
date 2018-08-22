/** @file vipFrameHSV.cpp
 *
 * File containing methods for the 'vipFrameHSV' class.
 * The header for this class can be found in vipFrameHSV.h, check
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



#include "vipFrameHSV.h"
#include <math.h>

vipFrameHSV::vipFrameHSV() : vipFrame()
 {
	INFO("vipFrameHSV::vipFrameHSV() : vipFrame() [CONTRUCTOR]")
	data = NULL;
	width = 0;
	height = 0;
 }

vipFrameHSV::vipFrameHSV(vipFrameHSV& img)
/**
 * Initialise to a new HSVImage identical to the specified image
 *
 * @param img The HSVImage to copy
 */
 {
	data = NULL;
	reAllocCanvas(img.width, img.height);

	if ( width != 0 && height != 0 )
		memcpy(data, img.data, width * height * sizeof(PixelHSV));

	INFO("vipFrameHSV::vipFrameHSV(vipFrameHSV& img) [CONTRUCTOR]")
	DEBUG(width)
	DEBUG(height)
 }


vipFrameHSV::vipFrameHSV(vipFrameRGB96& img)
/**
 * Initialise to a new HSVImage identical to the specified image
 *
 * @param img The RGBImage to copy
 */
 {
	data = NULL;
	reAllocCanvas(img.width, img.height);

	*this << img;

	INFO("vipFrameHSV::vipFrameHSV(vipFrameRGB96& img) [CONTRUCTOR]")
	DEBUG(width)
	DEBUG(height)
 }

vipFrameHSV::vipFrameHSV(vipFrameGrey & img)
/**
 * Initialise to a new HSVImage identical to the specified image
 *
 * @param img The RGBImage to copy
 */
 {
	data = NULL;
	reAllocCanvas(img.width, img.height);

	*this << img;

	INFO("vipFrameHSV::vipFrameHSV(vipFrameRGB96& img) [CONTRUCTOR]")
	DEBUG(width)
	DEBUG(height)
 }


vipFrameHSV::vipFrameHSV(unsigned int w, unsigned int h)
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

	INFO("vipFrameHSV::vipFrameHSV(unsigned int w, unsigned int h) [CONTRUCTOR]")
	DEBUG(width)
	DEBUG(height)
 }


vipFrameHSV::~vipFrameHSV()
/**
 * Destructor for vipFrameHSV class. Frees memory allocated to array:
 */
{
	if ( data != NULL )
	    delete [] data;

	INFO("vipFrameHSV::~vipFrameHSV() [DESTRUCTOR]")
}

VIPRESULT vipFrameHSV::reAllocCanvas(unsigned int w, unsigned int h)
 {
	if (data != NULL)
		delete [] data;

	height = h;
	width = w;
	data = NULL;

	if ( width == 0 || height == 0)
		return VIPRET_PARAM_ERR;

	data = new PixelHSV[width * height];

	return VIPRET_OK;
 }

VIPRESULT vipFrameHSV::setBlack()
 {
	if (width == 0 || height == 0 || data == NULL)
		return VIPRET_ILLEGAL_USE;

	memset(data, '\0', width * height * sizeof(PixelHSV) );

	return VIPRET_OK;
 }

VIPRESULT vipFrameHSV::setWhite()
 {
	if (width == 0 || height == 0 || data == NULL)
		return VIPRET_ILLEGAL_USE;

//	memset(data, 255, width * height  * sizeof(PixelHSV) );

	return VIPRET_NOT_IMPLEMENTED;
 }


VIPRESULT vipFrameHSV::extractBrightness(unsigned char* buffer, unsigned int* size)
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

	// by Marco Verza - UNTESTED
	for( int i=0; i<width*height; i++)
		buffer[i] = data[i].val;

	return VIPRET_OK;
 }

VIPRESULT vipFrameHSV::setPixel(unsigned int x, unsigned int y, PixelHSV p)
/**
 * Method sets the pixel at (x,y) from the Pixel specified.
 *
 * @param x,y The coordinates of the pixel
 * @param p   The Pixel with values red, green and blue
 */
{
	// Check that co-ords are valid.
	if ( x >= width || y >= height )
		throw "Invalid Coordinates in method vipFrameHSV::setPixel(unsigned int x, unsigned int y, PixelHSV p)";

	data[y * width + x] = p;

	return VIPRET_OK;
}


VIPRESULT vipFrameHSV::setHSV(unsigned int x, unsigned int y, unsigned short int hue, float sat, float val)
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
		throw "Invalid Coordinates in method vipFrameHSV::setHSV(unsigned int x, unsigned int y, int hue, int sat, int val)";

	unsigned int offset = y * width + x;

	data[offset].hue = hue;
	data[offset].sat = sat;
	data[offset].val = val;

	return VIPRET_OK;
}


VIPRESULT vipFrameHSV::setChannel(unsigned int x, unsigned int y, ChannelHSV fs, unsigned int value)
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
		throw "Invalid Coordinates in method vipFrameHSV::setChannel(unsigned int x, unsigned int y, ChannelHSV fs, int value)";

/*
	if (fs == HUE)
		data[y * width + x].hue = value;
	else if (fs == SAT)
		data[y * width + x].sat = (unsigned char)value;
	else if (fs == VAL)
		data[y * width + x].val = (unsigned char)value;
	else
		return VIPRET_PARAM_ERR;
*/
	return VIPRET_NOT_IMPLEMENTED;
}


VIPRESULT vipFrameHSV::getPixel(unsigned int x, unsigned int y, PixelHSV& p)
/**
 * Method to return values for pixel (x,y) in HSV Pixel p.
 *
 * @note No check is made that x and y are in range.
 *
 * @param x,y The coordinates of the pixel.
 * @param p   A Reference to the pixel to store the values in.
 */
{
	// Check that co-ords are valid.
	if ( x >= width || y >= height )
		throw "Invalid Coordinates in method vipFrameHSV::setChannel(unsigned int x, unsigned int y, ChannelHSV fs, int value)";

	p = data[y * width + x];

	return VIPRET_OK;
}


unsigned int vipFrameHSV::getChannel(unsigned int x, unsigned int y, ChannelHSV fs)
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
		throw "Invalid Coordinates in method vipFrameHSV::setChannel(unsigned int x, unsigned int y, ChannelHSV fs, int value)";

	if (fs == HUE)
		return (unsigned int)data[y * width + x].hue;
	else if (fs == SAT)
		return (unsigned int)data[y * width + x].sat;
	else if (fs == VAL)
		return (unsigned int)data[y * width + x].val;

	throw "Unknown Channel in method vipFrameHSV::setChannel(unsigned int x, unsigned int y, ChannelHSV fs, int value)";
}


vipFrameHSV& vipFrameHSV::clearWith(PixelHSV& p)
/**
 * Method sets all pixels to the specified pixel.
 *
 * @param p Pixel to set to.
 */
{
	DEBUGMSG("vipFrameHSV& vipFrameHSV::clearWith(PixelHSV& p)", p)

	for (unsigned int i=0; i < width * height; i++)
		data[i] = p;

	return *this;
}


vipFrameHSV& vipFrameHSV::clearChannel(ChannelHSV fs, unsigned int value)
/**
 * Method sets all pixels of currently selected field to specified value
 *
 * @param channel The field so clear, one of (RED, GREEN, BLUE).
 * @param value  Value to clear the field to.
 */
{
	INFO("vipFrameHSV& vipFrameHSV::clearChannel(ChannelHSV channel, unsigned int value)")
	DEBUG(channel)
	DEBUG(color)


	if (fs == HUE)
	{
		for (unsigned int i = 0; i<width*height; i++)
			data[i].hue = value;
	}
	else if (fs == SAT)
	{
		for (unsigned int i = 0; i<width*height; i++)
			data[i].sat = (unsigned char)value;
	}
	else if (fs == VAL)
	{
		for (unsigned int i = 0; i<width*height; i++)
			data[i].val = (unsigned char)value;
	}

	return *this;
}



int vipFrameHSV::setWidth(unsigned int newWidth)
 {
	if ( width != 0)
		return VIPRET_ILLEGAL_USE;

	width = newWidth;

	return VIPRET_OK;
 }

int vipFrameHSV::setHeight(unsigned int newHeight)
 {
	if ( height != 0)
		return VIPRET_ILLEGAL_USE;

	height = newHeight;

	return VIPRET_OK;
 }


vipFrameHSV& vipFrameHSV::copy(vipFrameHSV& img)
/**
 * Copies all pixel data from img.
 * Throws an exception if images are of different size.
 *
 * @param img The image to copy the data from.
 */
{
	INFO("vipFrameHSV& vipFrameHSV::copy(vipFrameHSV& img)")

	/* check we're not trying to copy ourself */
	if (this == &img)
		throw "Source and Destination are same Image";

	/* First check images are the same size and valid */
	if (width != img.width || height != img.height)
		throw "Difference in vipFrameHSV Dimensions";

	/* Perform copy */
	memcpy(data, img.data, width * height * sizeof(PixelHSV));

	return *this;
}


vipFrameHSV& vipFrameHSV::operator += (vipFrameHSV& img)
{
	INFO("vipFrameHSV& vipFrameHSV::operator += (vipFrameHSV& img)")

	if (width != img.width || height != img.height)
		throw "Difference in vipFrameHSV Dimensions";

    for(unsigned int i=0; i < width * height; i++)
        data[i] += img.data[i];

    return *this;
}


vipFrameHSV& vipFrameHSV::operator -= (vipFrameHSV& img)
{
	INFO("vipFrameHSV& vipFrameHSV::operator -= (vipFrameHSV& img)")

	if (width != img.width || height != img.height)
		throw "Difference in vipFrameHSV Dimensions";

    for(unsigned int i=0; i < width * height; i++)
        data[i] -= img.data[i];

    return *this;
}


vipFrameHSV& vipFrameHSV::operator /= (vipFrameHSV& img)
{
	INFO("vipFrameHSV& vipFrameHSV::operator /= (vipFrameHSV& img)")

	if (width != img.width || height != img.height)
		throw "Difference in vipFrameHSV Dimensions";

    for(unsigned int i=0; i < width * height; i++)
        data[i] /= img.data[i];

    return *this;
}


vipFrameHSV& vipFrameHSV::operator *= (vipFrameHSV& img)
{
	INFO("vipFrameHSV& vipFrameHSV::operator *= (vipFrameHSV& img)")

	if (width != img.width || height != img.height)
		throw "Difference in vipFrameHSV Dimensions";

    for(unsigned int i=0; i < width * height; i++)
        data[i] *= img.data[i];

    return *this;
}



vipFrameHSV& vipFrameHSV::operator >> (vipFrameRGB24& img)
/**
 * Copies all pixel data to img.
 * Throws an exception if images are of different size.
 *
 * @param img The image to copy the data from.
 */
{
	INFO("vipFrameHSV& vipFrameHSV::operator >> (vipFrameRGB24& img) [pushing data]")

	if ( width == 0 || height == 0 )
		throw "Cannot do that with empty image (no size)";


	if ( width != img.width || height != img.height )
		img.reAllocCanvas(width, height);


	// Substituted by Marco Verza...
  //  for(unsigned int cnt=0 ; cnt<width*height ; cnt++)
		//convPixel_HSVtoRGB24(data[cnt], img.data[cnt]);

	// with:
	vipUtility::conv_PixelHSVtoPixelRGB24( (PixelHSV*)data, (unsigned char*)img.data, width, height );
//CHECKBUGS


	return *this;
}

vipFrameHSV& vipFrameHSV::operator >> (vipFrameHSV& img)
/**
 * Copies all pixel data from img.
 * Throws an exception if images are of different size.
 *
 * @param img The image to copy the data from.
 */
{
	INFO("vipFrameHSV& vipFrameHSV::operator >> (vipFrameHSV& img) [pushing data]")

	/* check we're not trying to copy ourself */
	if (this == &img)
		throw "Source and Destination are same Image";

	if ( width == 0 || height == 0 )
		throw "Cannot do that with empty image (no size)";


	if ( width != img.width || height != img.height )
		img.reAllocCanvas(width, height);

	memcpy(img.data, data, width * height * sizeof(PixelHSV));

	return *this;
}

//// Commented out by Marco Verza while cleaning up conversion methods
/**
 * Copies all pixel data from img.
 * Throws an exception if images are of different size.
 *
 * @param img The image to copy the data from.
 */
//vipFrameHSV& vipFrameHSV::operator >> (vipFrameRGB96& img)
//{
//	INFO("vipFrameHSV& vipFrameHSV::operator >> (vipFrameRGB96& img) [pushing data]")
//
//	if ( width == 0 || height == 0 )
//		throw "Cannot do that with empty image (no size)";
//
//	if ( width != img.width || height != img.height )
//		img.reAllocCanvas(width, height);
//
//	// Changed by Marco Verza...
//	//const unsigned int size= height*width;
//	//for (unsigned int i=0; i < size; i++)
// //   	convPixel_HSVtoRGB32(data[i], img.data[i]);
//
//	// with:
//	//vipUtility::conv_
//
//	return *this;
//}

/**
 * Copies all pixel data from img.
 * Throws an exception if images are of different size.
 *
 * @param img The image to copy the data from.
 */

vipFrameHSV& vipFrameHSV::operator >> (vipFrameGrey& img)
{
	INFO("vipFrameHSV& vipFrameHSV::operator >> (vipFrameGrey& img) [pushing data]")

	if ( width == 0 || height == 0 )
		throw "Cannot do that with empty image (no size)";

	if ( width != img.width || height != img.height )
		img.reAllocCanvas(width, height);

	// Changed by Marco Verza ...
	//const unsigned int size= height*width;
	//for (unsigned int i=0; i < size; i++)
 //   	convPixel_HSVtoGREY( data[i], img.data[i] );

	// to new conv procedures: // UNTESTED
	unsigned int* size = new unsigned int[1];
	this->extractBrightness( img.data, size );
	delete size;

	return *this;
}



void vipFrameHSV::operator << (const vipFrameRGB24& img)
/**
 * Copies all pixel data from img.
 * Throws an exception if images are of different size.
 *
 * @param img The image to copy the data from.
 */
{
	INFO("void vipFrameHSV::operator << (const vipFrameRGB24& img) [importing data]")

	if ( img.width == 0 || img.height == 0 )
		throw "Cannot do that with empty image (no size)";

	if ( width != img.width || height != img.height )
		reAllocCanvas(img.width, img.height);

	//Changed by Marco Verza to match new conversion procedures
	//const unsigned int size= height*width;
	//for (unsigned int i=0; i < size; i++)
 //   	convPixel_RGB24toHSV(img.data[i], data[i]);

	double sat_range=0, sat_average=0;
	vipUtility::conv_PixelRGB24toPixelHSV( (unsigned char*)img.data, (PixelHSV*)data, width, height, &sat_range, &sat_average );

}


void vipFrameHSV::operator << (const vipFrameHSV& img)
/**
 * Copies all pixel data from img.
 * Throws an exception if images are of different size.
 *
 * @param img The image to copy the data from.
 */
{
	INFO("void vipFrameHSV::operator << (const vipFrameHSV& img) [importing data]")

	/* check we're not trying to copy ourself */
	if (this == &img)
		throw "Source and Destination are same Image";

	if ( img.width == 0 || img.height == 0 )
		throw "Cannot do that with empty image (no size)";

	if ( width != img.width || height != img.height )
		reAllocCanvas(img.width, img.height);

	memcpy(data, img.data, width * height * sizeof(PixelHSV));
}

/**
 * Copies all pixel data from img.
 * Throws an exception if images are of different size.
 *
 * @param img The image to copy the data from.
 */

void vipFrameHSV::operator << (const vipFrameRGB96& img)
{
	INFO("void vipFrameHSV::operator << (const vipFrameRGB96& img) [importing data]")

	if ( img.width == 0 || img.height == 0 )
		throw "Cannot do that with empty image (no size)";

	if ( width != img.width || height != img.height )
		reAllocCanvas(img.width, img.height);

	// Commented out by Marco Verza while cleaning up conversion procedures, not implemented
	//const unsigned int size= height*width;
	//for (unsigned int i=0; i < size; i++)
 //   	convPixel_RGB32toHSV(img.data[i], data[i]);
	throw("Not implemented.");

 }

/**
 * Copies all pixel data from img.
 * Throws an exception if images are of different size.
 *
 * @param img The image to copy the data from.
 */

void vipFrameHSV::operator << (const vipFrameGrey& img)
{
	INFO("void vipFrameHSV::operator << (const vipFrameGrey& img) [importing data]")

	if ( width == 0 || height == 0 || width != img.width || height != img.height )
	 {
		reAllocCanvas(img.width, img.height);
	 }

	// Commented out by Marco Verza while cleaning up conversion procedures, changed
	//const unsigned int size= height*width;
	//for (unsigned int i=0; i < size; i++)
 //   	convPixel_GREYtoHSV( img.data[i], data[i] );

	// ...to:
	unsigned char* tmp = new unsigned char[width*height*3];

	for( int i=0; i<width*height*3; i+=3)
	{
		tmp[i] = img.data[i/3];
		tmp[i+1] = img.data[i/3];
		tmp[i+2] = img.data[i/3];
	}

	double sat_range=0, sat_average=0;
	vipUtility::conv_PixelRGB24toPixelHSV( tmp, (PixelHSV*)data, width, height, &sat_range, &sat_average );

	delete tmp;

 }
















// Commented out by Marco Verza while cleaning up conversion methods
//
//int conv_PlanarYUVtoPixelHSV(unsigned char* YUV_Planar_ptr, double* HSV_Packet_ptr, unsigned int width, unsigned int height)
//{
// unsigned char* y = YUV_Planar_ptr;
// unsigned char* u = YUV_Planar_ptr+width*height;
// unsigned char* v = YUV_Planar_ptr+width*height*2;
//
// int* rgb = new int[3];
// double min, max, delta;
// double R,G,B;
// double H,S,V;
//
// int tmp;
// double temp=0;
// double S_min = 0;   //need to calculate the saturation range in the frame
// double S_max = 0;
//
// //calculation of RGB values from YUV
// for (unsigned int i=0; i < width*height*3; i+=3, y++, u++, v++)
// {
//  R = (double)( (298*(*y-16)                + 409*(*v-128) + 128) >> 8);
//  G = (double)( (298*(*y-16) - 100*(*u-128) - 208*(*v-128) + 128) >> 8);
//  B = (double)( (298*(*y-16) + 516*(*u-128)                + 128) >> 8);
//
//
//  //clipping of the value in the range 0-255
//
//  if(R<0)R=0;
//  if(R>255)R=255;
//  if(G<0)G=0;
//  if(G>255)G=255;
//  if(B<0) B=0;
//  if(B>255) B=255;
//
//  rgb[0] = (int)R;
//  rgb[1] = (int)G;
//  rgb[2] = (int)B;
//
//
//  //calculation from RGB to HSV
//
//  //calculation of min & max in rgb
//  for(int j = 0; j < 2; j++)
//
//   if(rgb[j] >= rgb[j+1])
//   {
//	tmp = rgb[j];
//	rgb[j] = rgb[j+1];
//	rgb[j+1] = tmp;
//   }
//
//   max = (double)rgb[2];
//
//   if(rgb[0] >= rgb[1])
//
//	min = (double)rgb[1];
//
//   else
//	min = (double)rgb[0];
//
//   V = max;
//   delta = max - min;
//
//   // Calculate saturation: saturation is 0 if r, g and b are all 0
//   if (V == 0.0)
//
//	S = 0.0;
//
//   else
//	S = delta / V;
//
//   if (S==0.0)
//	H = 0.0;    // should be Achromatic: When s = 0, h is undefined but..
//   else       // Chromatic
//	if (R == V)  // between yellow and magenta [degrees]
//
//	 H=60.0*(G-B)/delta;
//
//	else
//
//	 if (G == V)  // between cyan and yellow
//
//	  H = 120.0+60.0*(B-R)/delta;
//
//	 else // between magenta and cyan
//
//	  H = 240.0+60.0*(R-G)/delta;
//
//   if((int)H<0) H +=360.0;
//   if((int)H>=360) H-=360.0;
//
//   //memorize value in out buffer..
//   HSV_Packet_ptr[i] = H;
//   HSV_Packet_ptr[i+1] = S;
//   HSV_Packet_ptr[i+2] = V/255;
//
//   //computing average value and variation range for the saturation..
//   //used as threshold for shadow&highlight detection
//
//   if(S < S_min) S_min = S;
//   if(S > S_max) S_max = S;
//   temp+=S;
//
// }
//
//// range_S = S_max - S_min;
//// average_S = temp / (width*height);
//
//
// return VIPRET_OK;
//}
//
//




//funzionante..
/*int conv_PixelRGBtoPixelHSV(unsigned char* RGB_Packet_ptr, double* HSV_Packet_ptr, unsigned int width, unsigned int height)
{
 int* rgb=new int[3];
 int tmp;
 double temp=0;
 double S_min = 0;   //need to calculate the saturation range inthe frame
 double S_max = 0;
 double H,S,V;

 double R,G,B;
 double min, max, delta;

 for(int i = 0; i < width * height * 3; i+=3)
 {


  rgb[0] = (int)RGB_Packet_ptr[i];     //red
  rgb[1] = (int)RGB_Packet_ptr[i+1];	 //green
  rgb[2] = (int)RGB_Packet_ptr[i+2];//blue

  R = rgb[0];
  G = rgb[1];
  B = rgb[2];

  //calculation of min & max in rgb
  for(int j = 0; j < 2; j++)

   if(rgb[j] >= rgb[j+1])
   {
	tmp = rgb[j];
	rgb[j] = rgb[j+1];
	rgb[j+1] = tmp;
   }

   max = (double)rgb[2];

   if(rgb[0] >= rgb[1])

	min = (double)rgb[1];

   else
	min = (double)rgb[0];

   V = max;
   delta = max - min;

   // Calculate saturation: saturation is 0 if r, g and b are all 0
   if (V == 0.0)

	S = 0.0;

   else
	S = delta / V;

   if (S==0.0)
	H = 0.0;    // should be Achromatic: When s = 0, h is undefined but..
   else       // Chromatic
	if (R == V)  // between yellow and magenta [degrees]

	 H=60.0*(G-B)/delta;

	else

	 if (G == V)  // between cyan and yellow

	  H = 120.0+60.0*(B-R)/delta;

	 else // between magenta and cyan

	  H = 240.0+60.0*(R-G)/delta;

   //if ((int)H < 0) H = H+360.0;
   if((int)H<0) H +=360.0;
   if((int)H>=360) H-=360.0;

   HSV_Packet_ptr[i] = H;
   HSV_Packet_ptr[i+1] = S;
   HSV_Packet_ptr[i+2] = V/255;


   if(S < S_min) S_min = S;
   if(S > S_max) S_max = S;
   temp+=S;  //to compute average S in the frame, used as threshold for shadow&highlight detection

 }
 range_S = S_max - S_min;
 average_S = temp/(width*height);


 return VIPRET_OK;
}*/

/*int conv_PixelHSVtoPixelRGB(double* HSV_Pixel_ptr, unsigned char* RGB_Packet_ptr, unsigned int width, unsigned int height)
{

 unsigned char* rgb = RGB_Packet_ptr;
 int j;
 double f, p, q, t,R,G,B;
 double H,S,V;

 for(int i = 0; i < (width*height*3); i+=3)
 {
  H = HSV_Pixel_ptr[i];
  S = HSV_Pixel_ptr[i+1];
  V = HSV_Pixel_ptr[i+2];

  //printf("%d ",i);getchar();

  if( S == 0 ) {
   // achromatic (grey)
   R =  V;
   G =  V;
   B =  V;
   //printf("HSV %f %f %f, RGB %d %d %d",H,S,V,(int)RGB_Packed_ptr[i],(int)RGB_Packed_ptr[i+1],(int)RGB_Packed_ptr[i+2]);getchar();
   //printf("achromatic\n");

   goto label;
  }

  H /= 60;			// sector 0 to 5
  j = floor( H );
  f = H - j;			// factorial part of h
  p = V * ( 1 - S );
  q = V * ( 1 - S * f );
  t = V * ( 1 - S * ( 1 - f ) );

  switch( j ) {
  case 0:
   R = V;
   G = t;
   B = p;
   //printf("case1\n");
   break;

  case 1:
   R = q;
   G = V;
   B = p;
   //printf("case2\n");
   break;

  case 2:
   R = p;
   G = V;
   B = t;
   //printf("case3\n");
   break;

  case 3:
   R = p;
   G = q;
   B = V;
   //printf("case4\n");
   break;

  case 4:
   R = t;
   G = p;
   B = V;
   //printf("case5\n");
   break;

  default:		// case 5:
   R = V;
   G = p;
   B = q;
   //printf("case6\n");


  }
  //printf("%d %d",width, height);
  //printf("HSV %f %f %f ", H*60,S,V);
  //printf("RGB %f %f %f" , R*255, G*255, B*255);getchar();
label:
  rgb[i]= (unsigned char)(R*255);
  rgb[i+1]= (unsigned char)(G*255);
  rgb[i+2]= (unsigned char)(B*255);
  //printf("RGB %d %d %d" , (int)rgb[i], (int)rgb[i+1], (int)rgb[i+2]);getchar();


 }

 return VIPRET_OK;
}*/















//// Commented out by Marco Verza while cleaning up conversion methods
////
////void vipFrameHSV::convPixel_RGB32toHSV (const PixelRGB96& rgb, PixelHSV& hsv)
/////**
//// * Convert RGB pixel to HSV pixel
//// */
////{
////    float r = rgb[vipFrameRGB96::RED  ] / 255.0;
////    float g = rgb[vipFrameRGB96::GREEN] / 255.0;
////    float b = rgb[vipFrameRGB96::BLUE ] / 255.0;
////
////    float h, s, v;
////
////    float mn = r, mx = r;
////    int maxVal = 0;
////
////    if (g > mx) { mx = g; maxVal = 1; }
////    if (b > mx) { mx = b; maxVal = 2; }
////    if (g < mn) mn = g;
////    if (b < mn) mn = b;
////
////    float  delta = mx - mn;
////
////    v = mx;
////    if (mx != 0)
////        s = delta / mx;
////    else {
////        s = 0;
////        h = 0;
////        goto ass_end;
////    }
////
////    if (s == 0.0f) {
////        h = 0; // Arbritrary
////        goto ass_end;
////    } else {
////        switch (maxVal)
////        {
////            case 0: h = 0 + ( g - b ) / delta; break;     // yel  < h < mag
////            case 1: h = 2 + ( b - r ) / delta; break;     // cyan < h < yel
////            case 2: h = 4 + ( r - g ) / delta; break;     // mag  < h < cyan
////            default: h = 0 ; break ; // Should never occur
////        }
////    }
////
////    h *= 60;
////    if (h < 0) h += 360;
////
////ass_end:    // the assignments at the end of the function ;-)
////
////    hsv.hue = int (h);
////    hsv.sat = int (s * 255);
////    hsv.val = int (v * 255);
////
////}
////
////void vipFrameHSV::convPixel_HSVtoRGB32 (const PixelHSV& hsv, PixelRGB96& rgb)
/////**
//// * Convert HSV pixel to RGB pixel
//// */
////{
////    int i;
////    float f, p, q, t, hTemp;
////
////    float h = hsv.hue;
////    float s = hsv.sat / 255.0;
////    float v = hsv.val / 255.0;
////
////    float r, g, b;
////
////    if (s == 0.0 || h == -1.0) { // s==0? Totally unsaturated = grey
////        rgb[0] = rgb[1] = rgb[2] = (int) v * 255;
////    }
////    hTemp = h / 60.0f;
////    i = (int) floor(hTemp);                 // which sector
////    f = hTemp - i;                      // how far through sector
////    p = v * ( 1 - s );
////    q = v * ( 1 - s * f );
////    t = v * ( 1 - s * ( 1 - f ) );
////
////    switch (i) {
////        case 0: r = v; g = t; b = p; break;
////        case 1: r = q; g = v; b = p; break;
////        case 2: r = p; g = v; b = t; break;
////        case 3: r = p; g = q; b = v; break;
////        case 4: r = t; g = p; b = v; break;
////        case 5: r = v; g = p; b = q; break;
////        default: r=0 ; g=0 ; b=0 ; break ; // Should never occur
////    }
////
////    rgb[0] = int (r * 255);
////    rgb[1] = int (g * 255);
////    rgb[2] = int (b * 255);
////
////}
////
////
////
////
////void vipFrameHSV::convPixel_RGB24toHSV (const PixelRGB24& rgb, PixelHSV& hsv)
/////**
//// * Convert RGB pixel to HSV pixel
//// */
////{
////    float r = (int)rgb[vipFrameRGB96::RED  ] / 255.0;
////    float g = (int)rgb[vipFrameRGB96::GREEN] / 255.0;
////    float b = (int)rgb[vipFrameRGB96::BLUE ] / 255.0;
////
////    float h, s, v;
////
////    float mn = r, mx = r;
////    int maxVal = 0;
////
////    if (g > mx) { mx = g; maxVal = 1; }
////    if (b > mx) { mx = b; maxVal = 2; }
////    if (g < mn) mn = g;
////    if (b < mn) mn = b;
////
////    float  delta = mx - mn;
////
////    v = mx;
////    if (mx != 0)
////        s = delta / mx;
////    else {
////        s = 0;
////        h = 0;
////        goto ass_end;
////    }
////
////    if (s == 0.0f) {
////        h = 0; // Arbritrary
////        goto ass_end;
////    } else {
////        switch (maxVal)
////        {
////            case 0: h = 0 + ( g - b ) / delta; break;     // yel  < h < mag
////            case 1: h = 2 + ( b - r ) / delta; break;     // cyan < h < yel
////            case 2: h = 4 + ( r - g ) / delta; break;     // mag  < h < cyan
////            default: h = 0 ; break ; // Should never occur
////        }
////    }
////
////    h *= 60;
////    if (h < 0) h += 360;
////
////ass_end:    // the assignments at the end of the function ;-)
////
////    hsv.hue = int (h);
////    hsv.sat = int (s * 255);
////    hsv.val = int (v * 255);
////
////}
////
////void vipFrameHSV::convPixel_HSVtoRGB24 (const PixelHSV& hsv, PixelRGB24& rgb)
/////**
//// * Convert HSV pixel to RGB pixel
//// */
////{
////    int i;
////    float f, p, q, t, hTemp;
////
////    float h = hsv.hue;
////    float s = hsv.sat / 255.0;
////    float v = hsv.val / 255.0;
////
////    float r, g, b;
////
////    if (s == 0.0 || h == -1.0) { // s==0? Totally unsaturated = grey
////        rgb[0] = rgb[1] = rgb[2] = (int) v * 255;
////    }
////    hTemp = h / 60.0f;
////    i = (int) floor(hTemp);                 // which sector
////    f = hTemp - i;                      // how far through sector
////    p = v * ( 1 - s );
////    q = v * ( 1 - s * f );
////    t = v * ( 1 - s * ( 1 - f ) );
////
////    switch (i) {
////        case 0: r = v; g = t; b = p; break;
////        case 1: r = q; g = v; b = p; break;
////        case 2: r = p; g = v; b = t; break;
////        case 3: r = p; g = q; b = v; break;
////        case 4: r = t; g = p; b = v; break;
////        case 5: r = v; g = p; b = q; break;
////        default: r=0 ; g=0 ; b=0 ; break ; // Should never occur
////    }
////
////    rgb[0] = (unsigned char)(r * 255);
////    rgb[1] = (unsigned char)(g * 255);
////    rgb[2] = (unsigned char)(b * 255);
////
////}
////
////
////
////
////
////void vipFrameHSV::convPixel_GREYtoHSV (const PixelGrey& grey, PixelHSV& hsv)
/////**
//// * Convert RGB pixel to HSV pixel
//// */
////{
////    float r = (int)grey / RED_COEF / 255.0;
////    float g = (int)grey / GREEN_COEF / 255.0;
////    float b = (int)grey / BLUE_COEF / 255.0;
//////CHECKBUGS
////    float h, s, v;
////
////    float mn = r, mx = r;
////    int maxVal = 0;
////
////    if (g > mx) { mx = g; maxVal = 1; }
////    if (b > mx) { mx = b; maxVal = 2; }
////    if (g < mn) mn = g;
////    if (b < mn) mn = b;
////
////    float  delta = mx - mn;
////
////    v = mx;
////    if (mx != 0)
////        s = delta / mx;
////    else {
////        s = 0;
////        h = 0;
////        goto ass_end;
////    }
////
////    if (s == 0.0f) {
////        h = 0; // Arbritrary
////        goto ass_end;
////    } else {
////        switch (maxVal)
////        {
////            case 0: h = 0 + ( g - b ) / delta; break;     // yel  < h < mag
////            case 1: h = 2 + ( b - r ) / delta; break;     // cyan < h < yel
////            case 2: h = 4 + ( r - g ) / delta; break;     // mag  < h < cyan
////            default: h = 0 ; break ; // Should never occur
////        }
////    }
////
////    h *= 60;
////    if (h < 0) h += 360;
////
////ass_end:    // the assignments at the end of the function ;-)
////
////    hsv.hue = int (h);
////    hsv.sat = int (s * 255);
////    hsv.val = int (v * 255);
////
////}
////
////void vipFrameHSV::convPixel_HSVtoGREY (const PixelHSV& hsv, PixelGrey& grey)
/////**
//// * Convert HSV pixel to RGB pixel
//// */
////{
////    int i;
////    float f, p, q, t, hTemp;
////
////    float h = hsv.hue;
////    float s = hsv.sat / 255.0;
////    float v = hsv.val / 255.0;
////
////    float r, g, b;
////
////    if (s == 0.0 || h == -1.0) { // s==0? Totally unsaturated = grey
////        grey = (int) v * 255;
////    }
////    hTemp = h / 60.0f;
////    i = (int) floor(hTemp);                 // which sector
////    f = hTemp - i;                      // how far through sector
////    p = v * ( 1 - s );
////    q = v * ( 1 - s * f );
////    t = v * ( 1 - s * ( 1 - f ) );
////
////    switch (i) {
////        case 0: r = v; g = t; b = p; break;
////        case 1: r = q; g = v; b = p; break;
////        case 2: r = p; g = v; b = t; break;
////        case 3: r = p; g = q; b = v; break;
////        case 4: r = t; g = p; b = v; break;
////        case 5: r = v; g = p; b = q; break;
////        default: r=0 ; g=0 ; b=0 ; break ; // Should never occur
////    }
////
////	grey = (PixelGrey)(r * 255 * RED_COEF + g * 255 * GREEN_COEF + b * 255 * BLUE_COEF);
////
////}
////





















/****************************************************************************\
 *       Extra doxygen comments and information relating to this file       *
\****************************************************************************/

/** @enum vipFrameHSV::FieldSelector
 *
 * The FieldSelector selects the field (one of red, green and blue) for
 * the operation to be performed on.
 *
 ***** @var vipFrameHSV::FieldSelector vipFrameHSV::RED
 * Select the red field so the operation is only performed on the red
 * values of the image data.
 *
 ***** @var vipFrameHSV::FieldSelector vipFrameHSV::GREEN
 * Select the green field so the opertion is only performed on the green
 * values of the image data.
 *
 ***** @var vipFrameHSV::FieldSelector vipFrameHSV::BLUE
 * Select the blue field so the operation is only performed on the blue
 * values of the image data
 *
 */

