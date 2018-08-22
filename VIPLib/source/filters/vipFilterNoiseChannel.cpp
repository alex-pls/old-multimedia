/** @file vipFilterNoiseChannel.cpp
 *
 * File containing methods for the 'vipFilterNoiseChannel' class.
 * The header for this class can be found in vipFilterNoiseChannel.h,
 * check that file for class description.
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


#include "vipFilterNoiseChannel.h"

#include <time.h>	// time()
#include <stdlib.h>	// rand()


/**
 * @brief  Default constructor, initialize parameters and superclasses.
 * @param[in] initParams parameters for this module or NULL for defaults.
 */
vipFilterNoiseChannel::vipFilterNoiseChannel(vipFilterNoiseChannelParameters* initParams) : vipFilter()
 {
	INFO("vipFilterNoiseChannel::vipFilterNoiseChannel(..* initParams) : vipFilter() [CONTRUCTOR]")

	zeroRGB[0] = 0;
	zeroRGB[1] = 0;
	zeroRGB[2] = 0;

	oneRGB[0] = 1;
	oneRGB[1] = 1;
	oneRGB[2] = 1;

	zeroChar = '0';
	oneChar = '1';

	setParameters(initParams);
	reset();

	setName("Noise Channel Simulator Filter");
	setDescription("Additive noise or others..");
	setVersion(1.0);

  }

/**
 * @brief Default destructor, free buffer.
 */
vipFilterNoiseChannel::~vipFilterNoiseChannel()
 {
	INFO("vipFilterNoiseChannel::~vipFilterNoiseChannel() [DESTRUCTOR]")

	if (myParams != NULL)
		delete myParams;//BUG
	myParams = NULL;

 }

/**
 * @brief  Set parameters for this filter.
 *
 * @param[in] initParams Instance of vipFilterNoiseChannelParameters or NULL,
 *                       NULL argument make function to create a new
 *                       instance with default parameters.
 *
 * @return VIPRET_OK
 */
VIPRESULT vipFilterNoiseChannel::setParameters (vipFilterNoiseChannelParameters* initParams)
 {
	if ( initParams == NULL )
		myParams = new vipFilterNoiseChannelParameters();
	else
		myParams = initParams;

	allocateBuffer(myParams->currentBuffer);

	return VIPRET_OK;
 }

/**
 * @brief  Reset buffers and parameters.
 *
 * @return VIPRET_OK
 */
VIPRESULT vipFilterNoiseChannel::reset()
 {
	INFO("VIPRESULT vipFilterNoiseChannel::reset() [SET DEFAULT PARAMETERS]")

	releaseBuffers();

	if (myParams != NULL)
	 {
		myParams->reset();
		allocateBuffer(myParams->currentBuffer);
	 }
	else
		setParameters(NULL);

	resetNoiseSource();
	externalSource = NULL;

	return VIPRET_OK;
 }



void vipFilterNoiseChannel::generateNoise(vipFrameYUV420& img, unsigned char zero)
 {
	unsigned int size = img.getBufferSize();
	unsigned int perc = (unsigned int)( (float)size * myParams->spread);
	int noiseco = 0;
	int norm = myParams->normalize_value;

	for ( unsigned int i = 0; i < size; i++ )
		img.data[i] = zero;

	if ( myParams->normalized )
	 {
		for ( unsigned int i = 0; i < perc; i++ )
		 {
       			img.data[ noiseco = rand()*rand() % size ] = rand() % norm;
  		 }
	 }
	else
	 {
		for ( unsigned int i = 0; i < perc; i++ )
		 {
			img.data[ rand()*rand() % size ] = (unsigned char)rand();
		 }
	 }
 }

void vipFilterNoiseChannel::generateNoise(vipFrameRGB24& img,  PixelRGB24 zero)
 {
	unsigned int size = img.getBufferSize();
	unsigned int perc = (unsigned int)( (float)size * myParams->spread);
	unsigned int noiseco = 0;
        int norm = myParams->normalize_value;

	for ( unsigned int i = 0; i < size; i++ )
		img.data[i] = zero;

	if ( myParams->normalized )
	 {
		for ( unsigned int i = 0; i < perc; i++ )
		 {
			noiseco = rand()*rand() % size;
			img.data[noiseco][0] = (unsigned char)( rand() % norm);
			noiseco = rand()*rand() % size;
			img.data[noiseco][1] = (unsigned char)( rand() % norm);
			noiseco = rand()*rand() % size;
			img.data[noiseco][2] = (unsigned char)( rand() % norm);
		 }
	 }
	else
	 {
		for ( unsigned int i = 0; i < perc; i++ )
		 {
			noiseco = rand()*rand() % size;
			img.data[noiseco][0] = (unsigned char)rand();
			noiseco = rand()*rand() % size;
			img.data[noiseco][1] = (unsigned char)rand();
			noiseco = rand()*rand() % size;
			img.data[noiseco][2] = (unsigned char)rand();
		 }
	 }
 }

void vipFilterNoiseChannel::generateNoise(vipFrameT<unsigned char>& img, unsigned char zero)
 {
	unsigned int size = img.getBufferSize();
	unsigned int perc = (unsigned int)( (float)size * myParams->spread);
	int noiseco = 0;
	int norm = myParams->normalize_value;

	for ( unsigned int i = 0; i < size; i++ )
		img.data[i] = zero;

	if ( myParams->normalized )
	 {
		for ( unsigned int i = 0; i < perc; i++ )
		 {
       			img.data[ noiseco = rand()*rand() % size ] = rand() % norm;
  		 }
	 }
	else
	 {
		for ( unsigned int i = 0; i < perc; i++ )
		 {
			img.data[ rand()*rand() % size ] = rand();
		 }
	 }
 }


VIPRESULT vipFilterNoiseChannel::AddNoise(vipFrameYUV420& img)
 {
	INFO("VIPRESULT vipFilterNoiseChannel::AddNoise(vipFrameYUV420& img)")

	if ( !isBufferYUV() )
	 {
		useBufferYUV(img.width, img.height);
		//ret = VIPRET_OK_DEPRECATED;
	 }

	if ( externalSource == NULL )
		generateNoise(*bufferYUV,  zeroChar);
	else
		*externalSource >> *bufferYUV;

	*bufferYUV += img;

	return VIPRET_OK;
 }


VIPRESULT vipFilterNoiseChannel::AddNoise(vipFrameRGB24& img)
 {
	INFO("VIPRESULT vipFilterNoiseChannel::AddNoise(vipFrameRGB24& img)")

	if ( !isBufferRGB() )
	 {
		useBufferRGB(img.width, img.height);
		//ret = VIPRET_OK_DEPRECATED;
	 }

	if ( externalSource == NULL )
		generateNoise(*bufferRGB,  zeroRGB);
	else
		*externalSource >> *bufferRGB;

	*bufferRGB += img;

	return VIPRET_OK;
 }


VIPRESULT vipFilterNoiseChannel::AddNoise(vipFrameT<unsigned char>& img)
 {
	INFO("VIPRESULT vipFilterNoiseChannel::AddNoise(vipFrameT<unsigned char>& img)")

	if ( !isBufferTuC() )
	 {
		useBufferTuC(img.width, img.height, img.profile);
		//ret = VIPRET_OK_DEPRECATED;
	 }

	if ( externalSource == NULL )
		generateNoise(*bufferTuC,  zeroChar);
	else
		*externalSource >> *bufferTuC;

	*bufferTuC += img;

	return VIPRET_OK;
 }

VIPRESULT vipFilterNoiseChannel::MultiplyNoise(vipFrameYUV420& img)
 {
	INFO("VIPRESULT vipFilterNoiseChannel::MultiplyNoise(vipFrameYUV420& img)")

	if ( !isBufferYUV() )
	 {
		useBufferYUV(img.width, img.height);
		//ret = VIPRET_OK_DEPRECATED;
	 }

	if ( externalSource == NULL )
		generateNoise(*bufferYUV,  oneChar);
	else
		*externalSource >> *bufferYUV;

	*bufferYUV *= img;

	return VIPRET_OK;
 }


VIPRESULT vipFilterNoiseChannel::MultiplyNoise(vipFrameRGB24& img)
 {
	INFO("VIPRESULT vipFilterNoiseChannel::MultiplyNoise(vipFrameRGB24& img)")

	if ( !isBufferRGB() )
	 {
		useBufferRGB(img.width, img.height);
		//ret = VIPRET_OK_DEPRECATED;
	 }

	if ( externalSource == NULL )
		generateNoise(*bufferRGB,  oneRGB);
	else
		*externalSource >> *bufferRGB;

//BUG BUG BUG BUG BUG BUG
//	*bufferRGB *= img;

	return VIPRET_OK;
 }

VIPRESULT vipFilterNoiseChannel::MultiplyNoise(vipFrameT<unsigned char>& img)
 {
	INFO("VIPRESULT vipFilterNoiseChannel::MultiplyNoise(vipFrameT<unsigned char>& img)")

	if ( !isBufferTuC() )
	 {
		useBufferTuC(img.width, img.height, img.profile);
		//ret = VIPRET_OK_DEPRECATED;
	 }

	if ( externalSource == NULL )
		generateNoise(*bufferTuC,  oneChar);
	else
		*externalSource >> *bufferTuC;

//BUG
//*bufferTuC *= img;

	return VIPRET_OK;
 }



void vipFilterNoiseChannel::resetNoiseSource()
 {
	INFO("void vipFilterNoiseChannel::resetNoiseSource()")

	// initialise random sunber generator
	time_t t;
	srand((unsigned) time(&t));

 }

VIPRESULT vipFilterNoiseChannel::setNoiseSource(vipInput& frameSource)
 {
	DEBUGMSG("VIPRESULT vipFilterNoiseChannel::setNoiseSource(vipInput& frameSource)", &frameSource)

	externalSource = &frameSource;

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
VIPRESULT vipFilterNoiseChannel::importFrom(vipFrameYUV420& img)
 {
	INFO("VIPRESULT vipFilterNoiseChannel::importFrom(vipFrameYUV420& img) [reading data]")

	if ( myParams->operation == vipFilterNoiseChannelParameters::ADDITIVE )
		AddNoise(img);
	else if ( myParams->operation == vipFilterNoiseChannelParameters::MULTIPLICATIVE )
		MultiplyNoise(img);

	return VIPRET_OK;
 }

/**
 * @brief Process the frame with current settings and store in buffer.
 *
 * @param[in] img VIPLibb Cache24 Frame to be processed.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 *
 * @note  Input operator (<<) call directly this function.
 * @see   operator << (vipFrameRGB24&)
 */
VIPRESULT vipFilterNoiseChannel::importFrom(vipFrameRGB24& img)
 {
	INFO("VIPRESULT vipFilterNoiseChannel::importFrom(vipFrameYUV420& img) [reading data]")

	if ( myParams->operation == vipFilterNoiseChannelParameters::ADDITIVE )
		AddNoise(img);
	else if ( myParams->operation == vipFilterNoiseChannelParameters::MULTIPLICATIVE )
		MultiplyNoise(img);

	return VIPRET_OK;
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
VIPRESULT vipFilterNoiseChannel::importFrom(vipFrameT<unsigned char>& img)
 {
	INFO("VIPRESULT vipFilterNoiseChannel::importFrom(vipFrameT<unsigned char>& img) [reading data]")

	if ( myParams->operation == vipFilterNoiseChannelParameters::ADDITIVE )
		AddNoise(img);
	else if ( myParams->operation == vipFilterNoiseChannelParameters::MULTIPLICATIVE )
		MultiplyNoise(img);

	return VIPRET_OK;
 }







vipFilterNoiseChannelParameters::vipFilterNoiseChannelParameters(NOISEOPER mode)
 {
	reset();
	operation = mode;
 }

void vipFilterNoiseChannelParameters::reset()
 {
	operation = vipFilterNoiseChannelParameters::ADDITIVE;
	normalized = false;
	normalize_value = 255;
	spread = 1.;
	currentBuffer = vipFilterParameters::NONE;
 }



int vipFilterNoiseChannelParameters::saveToStreamXML(FILE *fp)
 {

	if ( fp == NULL )
		return VIPRET_PARAM_ERR;

	if( fprintf(fp, "<vipFilterNoiseChannelParameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <operation value=\"%i\" />\n", (int)operation) == EOF)
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <spread value=\"%f\" />\n", spread) == EOF)
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <normalized enabled=\"%u\" value=\"%u\" />\n", (int)normalized, normalize_value) == EOF)
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <internalBufferType value=\"%u\" />\n", (int)currentBuffer) == EOF)
		return VIPRET_INTERNAL_ERR;

	if( fprintf(fp, "</vipFilterNoiseChannelParameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	return VIPRET_OK;
 }



int vipFilterNoiseChannelParameters::loadFromStreamXML(FILE *fp)
 {
	if ( fscanf(fp, "<vipFilterNoiseChannelParameters>\n") == EOF )
		throw "error in XML file, unable to import data.";

	int runTmp = 0;
	if ( fscanf(fp, "  <operation value=\"%i\" />\n", &runTmp) == EOF )
		throw "error in XML file, unable to import data.";
	else
		operation = (NOISEOPER)runTmp;

	if ( fscanf(fp, "  <spread value=\"%f\" />\n", &spread) == EOF )
		throw "error in XML file, unable to import data.";

	int boolTmp = 0;
	if ( fscanf(fp, "  <normalized enabled=\"%u\" value=\"%u\" />\n", &boolTmp, &normalize_value) == EOF )
		throw "error in XML file, unable to import data.";

	if (boolTmp == 0)
		normalized = false;
	else
		normalized = true;

	int cB = (int)currentBuffer;
	if ( fscanf(fp, "  <internalBufferType value=\"%u\" />\n", &cB) == EOF )
		throw "error in XML file, unable to import data.";

	return VIPRET_OK;
 }

