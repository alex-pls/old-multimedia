/** @file vipFilterColor.cpp
 *
 * File containing methods for the 'vipFilterColor' class.
 * The header for this class can be found in vipFilterColor.h, check that file
 * for class description.
 *
 *
 *
 ****************************************************************************
 *  Class based on Package Studio template: vipFilterTemplate version 0.9.12
 ****************************************************************************
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.disi.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DISI - University of Trento
 *
 ****************************************************************************/



#include "vipFilterColor.h"



/**
 * @brief  Default constructor, initialize parameters and superclasses.
 * @param[in] initParams parameters for this module or NULL for defaults.
 */
vipFilterColor::vipFilterColor(vipFilterColorParameters* initParams) : vipFilter()
 {
	INFO("vipFilterColor::vipFilterColor(..* initParams) : vipFilter() [CONTRUCTOR]")

	setParameters(initParams);
	reset();

	setName("Colors Editing Filter");
	setDescription("Posterize, Nagative....");
	setVersion(1.0);

 }

/**
 * @brief Default destructor, free buffer.
 */
vipFilterColor::~vipFilterColor()
 {
	INFO("vipFilterColor::~vipFilterColor() [DESTRUCTOR]")

	if (myParams != NULL)
		delete myParams;//BUG
	myParams = NULL;

 }

/**
 * @brief  Set parameters for this filter.
 *
 * @param[in] initParams Instance of vipFilterColorParameters or NULL,
 *                       NULL argument make function to create a new
 *                       instance with default parameters.
 *
 * @return VIPRET_OK
 */
VIPRESULT vipFilterColor::setParameters (vipFilterColorParameters* initParams)
 {

	if ( initParams == NULL )
		myParams = new vipFilterColorParameters();
	else
		myParams = initParams;

	allocateBuffer(myParams->currentBuffer);

	return VIPRET_OK;
 }

/**
 * @brief  Get parameters for this filter.
 *
 * @return pointer to vipFilterColorParameters instance.
 */
VIPRESULT vipFilterColor::reset()
 {
	INFO("VIPRESULT vipFilterColor::reset() [SET DEFAULT PARAMETERS]")

	releaseBuffers();

	if (myParams != NULL)
	 {
		myParams->reset();
		allocateBuffer(myParams->currentBuffer);
	 }
	else
		setParameters(NULL);

	return VIPRET_OK;
 }


/**
 * @brief Process the frame with current settings and store in buffer.
 *
 * @param[in] img VIPLibb Cache Frame to be processed.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 *
 * @note  Input operator (<<) call directly this function.
 * @see   operator << (vipFrameYUV420&)
 */
VIPRESULT vipFilterColor::importFrom(vipFrameYUV420& img)
 {
	DEBUGMSG("VIPRESULT vipFilterColor::importFrom(vipFrameYUV420& img) [reading data]", myParams->runMode)

	switch ( myParams->runMode )
	 {
	 case vipFilterColorParameters::DO_NOTHING:
			if ( !isBufferYUV() )
			 {
				useBufferYUV(img.width, img.height);
				*bufferYUV = img;
				return VIPRET_OK_DEPRECATED;
			 }
			else
			 {
				*bufferYUV = img;
				return VIPRET_OK;
			 }
	 case vipFilterColorParameters::CLIPPING:
			useBufferYUV(img.width, img.height);
			return clipping(img, *bufferYUV, myParams->lowerThreshold,myParams->upperThreshold);

	case vipFilterColorParameters::EQUALIZER:
			useBufferYUV(img.width, img.height);
			return equalizer(img, *bufferYUV);

	 case vipFilterColorParameters::CLAMP:
			return clamp(img, myParams->currBpp);

	 case vipFilterColorParameters::INVERT:
			return invert(img, myParams->currBpp);

	 case vipFilterColorParameters::EXTRACTBITPLANE:
			return extractBitPlane(img, myParams->currBits);
	 
	 case vipFilterColorParameters::SEPIA:
			return sepia(img, *bufferYUV);

	 default:
		  return VIPRET_PARAM_ERR;
	 }
 }

/**
 * @brief Process the frame with current settings and store in buffer.
 *
 * @param[in] img VIPLib Cache Frame (YUV444) to be processed.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 *
 * @note  Input operator (<<) call directly this function.
 * @see   operator << (vipFrameYUV444&)
 */
VIPRESULT vipFilterColor::importFrom(vipFrameYUV444& img)
 {
	DEBUGMSG("VIPRESULT vipFilterColor::importFrom(vipFrameYUV444& img) [reading data]", myParams->runMode)

	switch ( myParams->runMode )
	 {
	 case vipFilterColorParameters::DO_NOTHING:
			if ( !isBufferYUV444() )
			 {
				useBufferYUV444(img.width, img.height);
				*bufferYUV444 = img;
				return VIPRET_OK_DEPRECATED;
			 }
			else
			 {
				*bufferYUV444 = img;
				return VIPRET_OK;
			 }
	 case vipFilterColorParameters::CLIPPING:
			useBufferYUV444(img.width, img.height);
			return clipping(img, *bufferYUV444, myParams->lowerThreshold,myParams->upperThreshold);

	case vipFilterColorParameters::EQUALIZER:
			useBufferYUV444(img.width, img.height);
			return equalizer(img, *bufferYUV444);

	 case vipFilterColorParameters::CLAMP:
			return clamp(img, myParams->currBpp);

	 case vipFilterColorParameters::INVERT:
			return invert(img, myParams->currBpp);

	 case vipFilterColorParameters::EXTRACTBITPLANE:
			return extractBitPlane(img, myParams->currBits);
	 
	 case vipFilterColorParameters::SEPIA:
		 	//useBufferYUV444(img.width, img.height);
			return sepia(img, *bufferYUV444);

	 default:
		  return VIPRET_PARAM_ERR;
	 }
 }

/**
 * @brief Process the frame with current settings and store in buffer.
 *
 * @param[in] img VIPLib Cache24 Frame to be processed.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 *
 * @note  Input operator (<<) call directly this function.
 * @see   operator << (vipFrameRGB24&)
 */
VIPRESULT vipFilterColor::importFrom(vipFrameRGB24& img)
 {
	DEBUGMSG("VIPRESULT vipFilterColor::importFrom(vipFrameRGB24& img) [reading data]", myParams->runMode)

	switch ( myParams->runMode )
	 {
	 case vipFilterColorParameters::DO_NOTHING:
			if ( !isBufferRGB() )
			 {
				useBufferRGB(img.width, img.height);
				*bufferRGB = img;
				return VIPRET_OK_DEPRECATED;
			 }
			else
			 {
				*bufferRGB = img;

				return VIPRET_OK;
			 }
	 case vipFilterColorParameters::CLIPPING:
			useBufferRGB(img.width, img.height);
			return clipping(img, *bufferRGB, myParams->lowerThreshold,myParams->upperThreshold);

	 case vipFilterColorParameters::EQUALIZER:
			useBufferRGB(img.width, img.height);
			return equalizer(img, *bufferRGB);

	 case vipFilterColorParameters::CLAMP:
			return clamp(img, myParams->currBpp);

	 case vipFilterColorParameters::INVERT:
			return invert(img, myParams->currBpp);

	 case vipFilterColorParameters::EXTRACTBITPLANE:
			return extractBitPlane(img, myParams->currBits);
	 
	 case vipFilterColorParameters::SEPIA:
			return sepia(img, *bufferRGB);

	 default:
		  return VIPRET_PARAM_ERR;
	 }
 }

/**
 * @brief Process the frame with current settings and store in buffer.
 *
 * @param[in] img VIPLibb Grayscale Frame to be processed.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 *
 * @note  Input operator (<<) call directly this function.
 * @see   operator << (vipFrameT&)
 */
VIPRESULT vipFilterColor::importFrom(vipFrameT<unsigned char>& img)
 {
	DEBUGMSG("VIPRESULT vipFilterColor::importFrom(vipFrameT<unsigned char>& img) [reading data]", myParams->runMode)

	switch ( myParams->runMode )
	 {
	 case vipFilterColorParameters::DO_NOTHING:
			if ( !isBufferTuC() )
			 {
				useBufferTuC(img.width, img.height, img.profile);
				*bufferTuC = img;
				return VIPRET_OK_DEPRECATED;
			 }
			else
			 {
				*bufferTuC = img;
				return VIPRET_OK;
			 }

	 case vipFilterColorParameters::CLIPPING:
			useBufferTuC(img.width, img.height, img.profile);
			return clipping(img,*bufferTuC, myParams->lowerThreshold,myParams->upperThreshold);

	 case vipFilterColorParameters::EQUALIZER:
			useBufferTuC(img.width, img.height, img.profile);
			return equalizer(img, *bufferTuC);

	 case vipFilterColorParameters::CLAMP:
			return clamp(img, myParams->currBpp);

	 case vipFilterColorParameters::INVERT:
			return invert(img, myParams->currBpp);

	 case vipFilterColorParameters::EXTRACTBITPLANE:
			return extractBitPlane(img, myParams->currBits);
	 
	 case vipFilterColorParameters::SEPIA:
			return sepia(img, *bufferTuC);

	 default:
		  return VIPRET_PARAM_ERR;
	 }
 }


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



//taglia tutti i valori saturi e negativi
VIPRESULT vipFilterColor::clamp(vipFrameYUV420& img, unsigned int bpp)//=sizeof(int)*3
 {

	return VIPRET_NOT_IMPLEMENTED;
 }


//taglia tutti i valori saturi e negativi
VIPRESULT vipFilterColor::clamp(vipFrameYUV444& img, unsigned int bpp)//=sizeof(int)*3
 {

	return VIPRET_NOT_IMPLEMENTED;
 }

//taglia tutti i valori saturi
VIPRESULT vipFilterColor::clamp(vipFrameRGB24& img, unsigned int bpp)
 {
//CHECKBUGS
	if ( bpp >= sizeof(unsigned char)*3 )
		return VIPRET_PARAM_ERR;

	useBufferRGB(img.width, img.height);

	for (unsigned int i=0; i < img.width * img.height; i++ )
	 {
		if ( img.data[i][0] > (unsigned char)( (1<<bpp)/3) )
			bufferRGB->data[i][0] = (unsigned char)( (1<<bpp)/3);
		else
			bufferRGB->data[i][0] = img.data[i][0];

		if ( img.data[i][1] > (unsigned char)( (1<<bpp)/3) )
			bufferRGB->data[i][1] = (unsigned char)( (1<<bpp)/3);
		else
			bufferRGB->data[i][1] = img.data[i][1];

		if ( img.data[i][1] > (unsigned char)( (1<<bpp)/3) )
			bufferRGB->data[i][1] = (unsigned char)( (1<<bpp)/3);
		else
			bufferRGB->data[i][2] = img.data[i][2];

	 }
	return VIPRET_OK;
 }

//taglia tutti i valori saturi e negativi
VIPRESULT vipFilterColor::clamp(vipFrameT<unsigned char>& img, unsigned int bpp)//=sizeof(int)*3
 {

	return VIPRET_NOT_IMPLEMENTED;
 }

/////////////////////////////////////////////////////////////////////////////////

VIPRESULT vipFilterColor::invert(vipFrameYUV420& img, unsigned int bpp)//=sizeof(int)*3
 {

	return VIPRET_NOT_IMPLEMENTED;
 }

VIPRESULT vipFilterColor::invert(vipFrameYUV444& img, unsigned int bpp)//=sizeof(int)*3
 {

	return VIPRET_NOT_IMPLEMENTED;
 }


VIPRESULT vipFilterColor::invert(vipFrameRGB24& img, unsigned int bpp)//=sizeof(int)*3
 {
//CHECKBUGS

	int maxVal = (1<<bpp)/3-1;

	useBufferRGB(img.width, img.height);

	for (unsigned int i=0; i < img.width * img.height; i++ )
	 {
		bufferRGB->data[i][0] = maxVal - img.data[i][0];
		bufferRGB->data[i][1] = maxVal - img.data[i][1];
		bufferRGB->data[i][2] = maxVal - img.data[i][2];
	 }

	return VIPRET_OK;
 }
VIPRESULT vipFilterColor::invert(vipFrameT<unsigned char>& img, unsigned int bpp)//=sizeof(int)*3
 {

	return VIPRET_NOT_IMPLEMENTED;
 }


VIPRESULT vipFilterColor::extractBitPlane(vipFrameRGB24& img, unsigned int bits)//=1
 {
//CHECKBUGS

	int mask = (1<<bits)/3-1;

	useBufferRGB(img.width, img.height);

	for (unsigned int i=0; i < img.width * img.height; i++ )
	 {
		bufferRGB->data[i][0] = (img.data[i][0] & mask) != 0;
		bufferRGB->data[i][1] = (img.data[i][1] & mask) != 0;
		bufferRGB->data[i][2] = (img.data[i][2] & mask) != 0;
	 }

	return VIPRET_OK;
 }

/////////////////////////////////////////////////////////////////////////////////


VIPRESULT vipFilterColor::extractBitPlane(vipFrameYUV420& img, unsigned int bits)//=1
 {
	return VIPRET_NOT_IMPLEMENTED;
 }

VIPRESULT vipFilterColor::extractBitPlane(vipFrameYUV444& img, unsigned int bits)//=1
 {
	return VIPRET_NOT_IMPLEMENTED;
 }

VIPRESULT vipFilterColor::extractBitPlane(vipFrameT<unsigned char>& img, unsigned int bits)//=1
 {
	return VIPRET_NOT_IMPLEMENTED;
 }


/**
 * @brief Apply sepia filter to input buffer and return output buffer
 *
 * @param[in] img VIPLib FrameRGB24 to be processed.
 * @param[out] img VIPLib FrameRGB24 to be processed.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 *
 * @note  Input operator (<<) call directly this function.
 * @see   operator << vipFrameRGB24
 * @author Nicola Conci
 */
VIPRESULT vipFilterColor::sepia(vipFrameRGB24& source, vipFrameRGB24& dest)
 {


	for ( unsigned int x=0; x < dest.width*dest.height; x++ ){
		dest.data[x][0] = (source.data[x][0]*0.393 +
								 source.data[x][1]*0.769 +
								 source.data[x][2]*0.189 )/1.351f;
		dest.data[x][1] = (source.data[x][0]*0.349 +
								 source.data[x][1]*0.686 +
								 source.data[x][2]*0.168 )/1.203f;
		dest.data[x][2] = (source.data[x][0]*0.272 +
								 source.data[x][1]*0.534 +
								 source.data[x][2]*0.131 )/2.140f;
		
		}

	return VIPRET_OK;
 }


VIPRESULT vipFilterColor::sepia(vipFrameYUV420& img, vipFrameYUV420& dest)
 {
	return VIPRET_NOT_IMPLEMENTED;
 }


VIPRESULT vipFilterColor::sepia(vipFrameYUV444& img, vipFrameYUV444& dest)
 {
	return VIPRET_NOT_IMPLEMENTED;
 }

VIPRESULT vipFilterColor::sepia(vipFrameT<unsigned char>& img, vipFrameT<unsigned char>& dest)
 {
	return VIPRET_NOT_IMPLEMENTED;
 }

////////////////////////////////////////////////////////////////////////////////////


 /**
* @brief applies clipping process on the frame in income.
*
* @param[in] img VIPLib FrameRGB24 to be processed, lower threshold and upper threshold.
* @param[out] dest destination FrameRGB24.
*
* @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if runmode is unknown,
*         VIPRET_NOT_IMPLEMENTED if this function is not enabled jet.
*
*/
 VIPRESULT vipFilterColor::clipping(vipFrameRGB24& img, vipFrameRGB24& dest, unsigned int inf, unsigned int sup) 
 {	
	 if (inf < 0 || sup > 255 || inf > sup) {
		return VIPRET_PARAM_ERR;
	 }
	
	unsigned int valR;
	unsigned int valG;
	unsigned int valB;

	for ( unsigned int y=0; y < img.height; y++ ) {
			for ( unsigned int x=0; x < img.width; x++ ) {
				valR = img.data[y*img.width + x][vipFrameRGB24::RED];
				valG = img.data[y*img.width + x][vipFrameRGB24::GREEN];
				valB = img.data[y*img.width + x][vipFrameRGB24::BLUE];

				if (valR > inf && valR < sup) {
					dest.data[y*dest.width + x][vipFrameRGB24::RED] = 255*(valR-inf)/(sup-inf);
				} else {
					if (valR <= inf) dest.data[y*dest.width + x][vipFrameRGB24::RED] = 0;

					if (valR >= sup) dest.data[y*dest.width + x][vipFrameRGB24::RED] = 255;
				}
				

				if (valG > inf && valG < sup) {
					dest.data[y*dest.width + x][vipFrameRGB24::GREEN] = 255*(valG-inf)/(sup-inf);
				} else {
					if (valG <= inf) dest.data[y*dest.width + x][vipFrameRGB24::GREEN] = 0;

					if (valG >= sup) dest.data[y*dest.width + x][vipFrameRGB24::GREEN] = 255;
				}
				
				if (valB > inf && valB < sup) {
					dest.data[y*dest.width + x][vipFrameRGB24::BLUE] = 255*(valB-inf)/(sup-inf);
				} else {
					if (valB <= inf) dest.data[y*dest.width + x][vipFrameRGB24::BLUE] = 0;

					if (valB >= sup) dest.data[y*dest.width + x][vipFrameRGB24::BLUE] = 255;
				}
			}
	}

	 return VIPRET_OK;
 }

 
VIPRESULT vipFilterColor::clipping(vipFrameYUV420& img, vipFrameYUV420& dest, unsigned int inf,unsigned int sup)
{
	return VIPRET_NOT_IMPLEMENTED;
}

VIPRESULT vipFilterColor::clipping(vipFrameYUV444& img, vipFrameYUV444& dest, unsigned int inf,unsigned int sup)
{
	return VIPRET_NOT_IMPLEMENTED;
}

VIPRESULT vipFilterColor::clipping(vipFrameT<unsigned char>& img, vipFrameT<unsigned char>& dest, unsigned int inf,unsigned int sup)
{
	return VIPRET_NOT_IMPLEMENTED;
}


////////////////////////////////////////////////////////////////////////////////////




VIPRESULT vipFilterColor::equalizer(vipFrameYUV420& source, vipFrameYUV420& dest)
 {
	
	return VIPRET_NOT_IMPLEMENTED;
 }

VIPRESULT vipFilterColor::equalizer(vipFrameYUV444& source, vipFrameYUV444& dest)
 {
	
	return VIPRET_NOT_IMPLEMENTED;
 }

/**
* @brief applies equalization process on the frame in income.
*
* @param[in] img VIPLib FrameRGB24 to be processed.
* @param[out] dest destination FrameRGB24.
*
* @return VIPRET_OK if everything is fine, VIPRET_NOT_IMPLEMENTED if this function is not enabled jet.
*
*/


VIPRESULT vipFilterColor::equalizer(vipFrameRGB24& source, vipFrameRGB24& dest)
 {	
	vipHist myHistR(source, vipFrameRGB24::RED);
	vipHist myHistG(source, vipFrameRGB24::GREEN);
	vipHist myHistB(source, vipFrameRGB24::BLUE);

	float* ChistR = myHistR.dumpChist();
	float* ChistG = myHistG.dumpChist();
	float* ChistB = myHistB.dumpChist();

	unsigned char valR;
	unsigned char valG;
	unsigned char valB;

	for ( unsigned int y=0; y < source.height; y++ ) {
		for ( unsigned int x=0; x < source.width; x++ ) {

			valR = source.data[y*source.width + x][vipFrameRGB24::RED];
			valG = source.data[y*source.width + x][vipFrameRGB24::GREEN];
			valB = source.data[y*source.width + x][vipFrameRGB24::BLUE];

			dest.data[y*dest.width + x][vipFrameRGB24::RED] = 255*ChistR[valR];
			dest.data[y*dest.width + x][vipFrameRGB24::GREEN] = 255*ChistG[valG];
			dest.data[y*dest.width + x][vipFrameRGB24::BLUE] = 255*ChistB[valB];
		}
	}

	return VIPRET_OK;
 }




VIPRESULT vipFilterColor::equalizer(vipFrameT<unsigned char>& source, vipFrameT<unsigned char>& dest)
 {
	
	return VIPRET_NOT_IMPLEMENTED;
 }



////////////////////////////////////////////////////////////////////////////////////////

vipFilterColorParameters::vipFilterColorParameters(RUNMODE mode)
 {
	runMode = mode;
	reset();
 }

void vipFilterColorParameters::reset()
 {
	runMode = vipFilterColorParameters::DO_NOTHING;
	currBpp = sizeof(int);
	currBits = 1;
	currentBuffer = vipFilterParameters::NONE;
	lowerThreshold = 0;
	upperThreshold = 255;
 }

int vipFilterColorParameters::saveToStreamXML(FILE *fp)
 {

	if ( fp == NULL )
		return VIPRET_PARAM_ERR;

	if( fprintf(fp, "<vipFilterColorParameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <runmode value=\"%i\" />\n", (int)runMode) == EOF)
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <currBpp value=\"%u\" />\n", currBpp) == EOF)
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <currBits value=\"%u\" />\n", currBits) == EOF)
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <internalBufferType value=\"%u\" />\n", (int)currentBuffer) == EOF)
		return VIPRET_INTERNAL_ERR;

	if( fprintf(fp, "</vipFilterColorParameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	return VIPRET_OK;
 }


int vipFilterColorParameters::loadFromStreamXML(FILE *fp)
 {
	if ( fscanf(fp, "<vipFilterColorParameters>\n") == EOF )
		throw "error in XML file, unable to import data.";

	int runTmp = 0;
	if ( fscanf(fp, "  <runmode value=\"%i\" />\n", &runTmp) == EOF )
		throw "error in XML file, unable to import data.";
	else
		runMode = (RUNMODE)runTmp;

	if ( fscanf(fp, "  <currBpp value=\"%u\" />\n", &currBpp) == EOF )
		throw "error in XML file, unable to import data.";

	if ( fscanf(fp, "  <currBits value=\"%u\" />\n", &currBits) == EOF )
		throw "error in XML file, unable to import data.";

	int cB = (int)currentBuffer;
	if ( fscanf(fp, "  <internalBufferType value=\"%u\" />\n", &cB) == EOF )
		throw "error in XML file, unable to import data.";
	currentBuffer = (BUFFER_TYPE)cB;

	return VIPRET_OK;
 }


//VIPRESULT vipFilterColor::extractTo(vipFrameYUV444 &img)
//{
//	return VIPRET_NOT_IMPLEMENTED;
//}

