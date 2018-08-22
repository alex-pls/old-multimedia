/** @file vipFilterSample.cpp
 *
 * File containing methods for the 'vipFilterSample' class.
 * The header for this class can be found in vipFilterSample.h, check that file
 * for class description.
 *
 *
 *
 ****************************************************************************
 *  Class based on Package Studio template: vipFilterTemplate version 0.9.12
 ****************************************************************************
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.science.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DIT - University of Trento
 *
 ****************************************************************************/



#include "vipFilterSample.h"



/**
 * @brief  Default constructor, initialize parameters and superclasses.
 * @param[in] initParams parameters for this module or NULL for defaults.
 */
vipFilterSample::vipFilterSample(vipFilterSampleParameters* initParams) : vipFilter()
 {
	INFO("vipFilterSample::vipFilterSample(..* initParams) : vipFilter() [CONTRUCTOR]")


	myParams = NULL;
	setParameters(initParams);

	setName("Geometric Editing Filter");
	setDescription("Resize, Crop, Rotation, Flip");
	setVersion(1.0);

	reset();
 }

/**
 * @brief Default destructor, free buffer.
 */
vipFilterSample::~vipFilterSample()
 {
	INFO("vipFilterSample::~vipFilterSample() [DESTRUCTOR]")

	if (myParams != NULL)
		delete myParams;
 

 }


/**
 * @brief  Reset buffers and parameters.
 *
 * @return VIPRET_OK
 */
VIPRESULT vipFilterSample::reset()
 {
	INFO("int vipFilterSample::reset() [SET DEFAULT PARAMETERS]")


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
 * @brief  Set parameters for this filter.
 *
 * @param[in] initParams Instance of vipFilterSampleParameters or NULL,
 *                       NULL argument make function to create a new
 *                       instance with default parameters.
 *
 * @return VIPRET_OK
 */
VIPRESULT vipFilterSample::setParameters (vipFilterSampleParameters* initParams)
 {

	if (initParams != NULL && myParams == initParams)
		return VIPRET_PARAM_ERR;

	if ( initParams == NULL )
	 {
		if ( myParams != NULL )
			reset();
		else
			myParams = new vipFilterSampleParameters();
	 }
	else
	 {
		if ( myParams != NULL )
			delete myParams;

		myParams = initParams;
	 }

	allocateBuffer(myParams->currentBuffer);


	return VIPRET_OK;
 }



/**
 * @brief Process the frame with current settings and store in buffer.
 *
 * @param[in] img VIPLib Frame YUV420 to be processed.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if runmode is unknown,
 *         VIPRET_NOT_IMPLEMENTED if this function is not enabled jet, VIPRET_INTERNAL_ERR else.
 *
 * @note  Input operator (<<) call directly this function.
 * @see   operator << (vipFrameYUV420&)
 */
VIPRESULT vipFilterSample::importFrom(vipFrameYUV420& img)
 {
	DEBUGMSG("int vipFilterSample::importFrom(vipFrameYUV420& img) [reading data]", myParams->runMode)


	switch ( myParams->runMode )
	 {
	 case vipFilterSampleParameters::DO_NOTHING:
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

	 case vipFilterSampleParameters::ROTATE90:
	 		useBufferYUV(img.height, img.width);
			return rotate90(*bufferYUV, img);

	 default:
		  return VIPRET_PARAM_ERR;
 	 }


	return VIPRET_NOT_IMPLEMENTED;
 }



/**
 * @brief Process the frame with current settings and store in buffer.
 *
 * @param[in] img VIPLib Frame RGB24 to be processed.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if runmode is unknown,
 *         VIPRET_NOT_IMPLEMENTED if this function is not enabled jet, VIPRET_INTERNAL_ERR else.
 *
 * @note  Input operator (<<) call directly this function.
 * @see   operator << (vipFrameRGB24&)
 */
VIPRESULT vipFilterSample::importFrom(vipFrameRGB24& img)
 {
	DEBUGMSG("int vipFilterSample::importFrom(vipFrameRGB24& img) [reading data]", myParams->runMode)


	switch ( myParams->runMode )
	 {
	 case vipFilterSampleParameters::DO_NOTHING:
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

	 case vipFilterSampleParameters::ROTATE90:
	 		useBufferRGB(img.height, img.width);
			return rotate90(*bufferRGB, img);

	 default:
		  return VIPRET_PARAM_ERR;
	 }


	return VIPRET_NOT_IMPLEMENTED;
 }



/**
 * @brief Process the frame with current settings and store in buffer.
 *
 * @param[in] img VIPLib Frame Template to be processed.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if runmode is unknown,
 *         VIPRET_NOT_IMPLEMENTED if this function is not enabled jet, VIPRET_INTERNAL_ERR else.
 *
 * @note  Input operator (<<) call directly this function.
 * @see   operator << (vipFrameT<unsigned char>&)
 */
VIPRESULT vipFilterSample::importFrom(vipFrameT<unsigned char>& img)
 {
	DEBUGMSG("int vipFilterSample::importFrom(vipFrameT<unsigned char>& img) [reading data]", myParams->runMode)


	switch ( myParams->runMode )
	 {
	 case vipFilterSampleParameters::DO_NOTHING:
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

	 case vipFilterSampleParameters::ROTATE90:
	 		useBufferTuC(img.height, img.width, img.profile);
			return rotate90(*bufferTuC, img);

	 default:
		  return VIPRET_PARAM_ERR;
	 }


	return VIPRET_NOT_IMPLEMENTED;
 }


///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////


VIPRESULT vipFilterSample::rotate90(vipFrameYUV420& dest, vipFrameYUV420& source)
 {
	if (dest.width != source.height || dest.height != source.width)
		dest.reAllocCanvas(source.height, source.width);

	return VIPRET_OK;
 }



VIPRESULT vipFilterSample::rotate90(vipFrameRGB24& dest, vipFrameRGB24& source)
 {
	if (dest.width != source.height || dest.height != source.width)
		dest.reAllocCanvas(source.height, source.width);

	for ( unsigned int y=0; y < dest.height; y++ ) // single pixel copy routine
	  for ( unsigned int x=0; x < dest.width; x++ )
		dest.data[(dest.height-1-y)*dest.width+x] = source.data[x*source.width + y];

	return VIPRET_OK;
 }



VIPRESULT vipFilterSample::rotate90(vipFrameT<unsigned char>& dest, vipFrameT<unsigned char>& source)
 {
	if (dest.width != source.height || dest.height != source.width)
		dest.reAllocCanvas(source.height, source.width);

	return VIPRET_NOT_IMPLEMENTED;
 }





///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////








vipFilterSampleParameters::vipFilterSampleParameters()
 {
	reset();
 }

void vipFilterSampleParameters::reset()
 {

	runMode = vipFilterSampleParameters::DO_NOTHING;


	currentBuffer = vipFilterParameters::NONE;
 }

int vipFilterSampleParameters::saveToStreamXML(FILE *fp)
 {

	if ( fp == NULL )
		return VIPRET_PARAM_ERR;

	if( fprintf(fp, "<vipFilterSampleParameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	// add your variables here


	if ( fprintf(fp, "  <runmode value=\"%i\" />\n", (int)runMode) == EOF)
		return VIPRET_INTERNAL_ERR;



	if ( fprintf(fp, "  <internalBufferType value=\"%u\" />\n", (int)currentBuffer) == EOF)
		return VIPRET_INTERNAL_ERR;


	if( fprintf(fp, "</vipFilterSampleParameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	return VIPRET_OK;
 }


int vipFilterSampleParameters::loadFromStreamXML(FILE *fp)
 {
	if ( fscanf(fp, "<vipFilterSampleParameters>\n") == EOF )
		throw "error in XML file, unable to import data.";

	// add your variables here



	int runTmp = 0;
	if ( fscanf(fp, "  <runmode value=\"%i\" />\n", &runTmp) == EOF )
		throw "error in XML file, unable to import data.";
	else
		runMode = (RUNMODE)runTmp;



	int cB = (int)currentBuffer;
	if ( fscanf(fp, "  <internalBufferType value=\"%u\" />\n", &cB) == EOF )
		throw "error in XML file, unable to import data.";
	currentBuffer = (BUFFER_TYPE)cB;



	return VIPRET_OK;
 }




