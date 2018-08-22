/** @file vipCodec_Sample.cpp
 *
 * File containing methods for the 'vipCodec_Sample' class.
 * The header for this class can be found in vipCodec_Sample.h, check that file
 * for class description.
 *
 *
 ****************************************************************************
 *  Class based on Package Studio template: vipCodec_Template version 0.9.12
 ****************************************************************************
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.science.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DIT - University of Trento
 *
 ****************************************************************************/



#include "vipCodec_Sample.h"


vipCodec_Sample::vipCodec_Sample( vipCodec_SampleParameters* initParams ) : vipCodec()
 {
	DEBUGMSG("vipCodec_Sample::vipCodec_Sample(vipCodec_SampleParameters* initParams) : vipCodec() [CONTRUCTOR] ", *filename)


	setParameters(initParams);
	reset();
 }



/**
 * @brief  Initialize parameters and load image/video stream from file.
 *         vipFrameRGB constructor.
 *
 * @param[in] filename Input BMP filename.
 * @param[in] format BMP Encoding Format, default auto-selection.
 */
vipCodec_Sample::vipCodec_Sample(char *filename, int stream) : vipCodec()
 {
	DEBUGMSG("vipCodec_Sample::vipCodec_Sample(char *filename, FileFormat format) : vipCodec() [CONTRUCTOR] ", *filename)


	setParameters(NULL);
	reset();

 	load( filename, stream );

 }



VIPRESULT vipCodec_Sample::reset()
 {
	INFO("int vipCodec_Sample::reset() [SET DEFAULT PARAMETERS]")


	width  = 0;
	height = 0;


	if (myParams != NULL)
		myParams->reset();

	setName("");
	setDescription("");
	setVersion(0.0);

	return VIPRET_OK;
 }


vipCodec_Sample::~vipCodec_Sample()
 {
	if (myParams != NULL)
		delete myParams; //BUG

 }



int vipCodec_Sample::setParameters (vipCodec_SampleParameters* initParams)
 {

	if ( initParams == NULL )
		myParams = new vipCodec_SampleParameters();
	else
		myParams = initParams;

	return VIPRET_OK;
 }





/**
 * @brief get movie's audio streams count.
 *
 * @return number of audio streams.
 */
int vipCodec_Sample::getAudioStreamCount()
 {
	 return -1;
 };



/**
 * @brief get movie's video streams count.
 *
 * @return number of video streams.
 */
int vipCodec_Sample::getVideoStreamCount()
 {
	 return -1;
 };



/**
 * @brief get movie's video frame rate.
 *
 * @param[in] stream select stream index.
 *                   default is -1: current active stream.
 *
 * @return number of frame per second.
 */
float vipCodec_Sample::getVideoFrameRate(int stream)
 {
	return 0.0;
 }



/**
 * @brief  Get movie's video stream frame count.
 *
 * @param[in] stream select stream, default is current stream.
 *
 * @return number of frames in selected video stream.
 */
long vipCodec_Sample::getVideoStreamLength(int stream)
 {
	return 0;
 }




/**
 * @brief  Get movie's audio stream sample count.
 *
 * @param[in] stream select stream, default is current stream.
 *
 * @return number of samples in selected audio stream.
 */
long vipCodec_Sample::getAudioStreamLength(int stream)
 {
	return 0;
 }



/**
 * @brief  Close current movie (close file access).
 *
 * @return VIPRET_ILLEGAL_USE if movie was not loaded, VIPRET_OK else.
 */
VIPRESULT vipCodec_Sample::close()
 {
	return VIPRET_NOT_IMPLEMENTED;
 }






/**
 * @brief  Load a movie from a file.
 *
 * @param[in] filename input movie filename
 * @param[in] stream video stream to load (default is first: 0)
 *
 * @return VIPRET_ILLEGAL_USE if file is not correctly loaded, VIPRET_OK else.
 */
VIPRESULT vipCodec_Sample::load(char *filename, int stream)
 {
	DEBUGMSG("int vipCodec_Sample::load(char *filename, FileFormat format) [loading data]", filename)

 	myParams->setFileName(filename);
 	myParams->setStream(stream);

	return VIPRET_NOT_IMPLEMENTED;
 }




/**
 * @brief  Save current movie to file.
 *
 * @param[in] filenameoutput movie filename
 * @param[in] stream video stream to load (default is first: 0)
 *
 * @return VIPRET_ILLEGAL_USE if file is not correctly loaded, VIPRET_OK else.
 */
VIPRESULT vipCodec_Sample::save(char *filename, int stream)
 {
	return VIPRET_NOT_IMPLEMENTED;
 }













/**
 * @brief  Load data into passed image, move current index to next frame.
 *
 * @param[out] img VIPLib Cache Frame to store data.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
 *
 * @note   Ouput operator (>>) call directly this function.
 * @see    operator >> (vipFrameYUV420&)
 * @see    AutoInput
 */
VIPRESULT vipCodec_Sample::extractTo(vipFrameYUV420& img)
 {
	DEBUGMSG("int vipCodec_Sample::extractTo(vipFrameYUV420& img) [pushing data]", doBuffering)


	if (width != img.width || height != img.height)
		img.reAllocCanvas(width, height);


	return VIPRET_NOT_IMPLEMENTED;
 }



/**
 * @brief  Load data into passed image, move current index to next frame.
 *
 * @param[out] img VIPLib Cache24 Frame to store data.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
 *
 * @note   Ouput operator (>>) call directly this function.
 * @see    operator >> (vipFrameRGB24&)
 * @see    AutoInput
 */
VIPRESULT vipCodec_Sample::extractTo(vipFrameRGB24& img)
 {
	DEBUGMSG("int vipCodec_Sample::extractTo(vipFrameRGB24& img) [pushing data]", doBuffering)


	if (width != img.width || height != img.height)
		img.reAllocCanvas(width, height);


	return VIPRET_NOT_IMPLEMENTED;
 }




/**
 * @brief  Load data into passed image, move current index to next frame.
 *
 * @param[out] img Greyscale VIPLib Frame to store data.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
 *
 * @note   Ouput operator (>>) call directly this function.
 * @see    operator >> (vipFrameT<unsigned char>&)
 * @see    AutoInput
 */
VIPRESULT vipCodec_Sample::extractTo(vipFrameT<unsigned char>& img)
 {
	DEBUGMSG("int vipCodec_Sample::extractTo(vipFrameT<unsigned char>& img) [pushing data]", doBuffering)


	if (width != img.width || height != img.height)
		img.reAllocCanvas(width, height);



	return VIPRET_NOT_IMPLEMENTED;
 }




/**
 * @brief  Add given image to current stream.
 *
 * @param[in] img VIPLib Cache Frame to be processed (encoded for example)
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
 *
 * @note   Input operator (<<) call directly this function.
 * @see    operator << (vipFrameYUV420&)
 */
VIPRESULT vipCodec_Sample::importFrom(vipFrameYUV420& img)
 {
	DEBUGMSG("int vipCodec_Sample::importFrom(vipFrameYUV420& img) [reading data]", doBuffering)

	return VIPRET_NOT_IMPLEMENTED;
 }



/**
 * @brief  Add given image to current stream.
 *
 * @param[in] img VIPLib Cache24 Frame to be processed (encoded for example)
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
 *
 * @note   Input operator (<<) call directly this function.
 * @see    operator << (vipFrameRGB24&)
 */
VIPRESULT vipCodec_Sample::importFrom(vipFrameRGB24& img)
 {
	DEBUGMSG("int vipCodec_Sample::importFrom(vipFrameRGB24& img) [reading data]", doBuffering)

	return VIPRET_NOT_IMPLEMENTED;
 }




/**
 * @brief  Add given image to current stream.
 *
 * @param[in] img Greyscale VIPLib Frame to be processed (encoded for example)
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
 *
 * @note   Input operator (<<) call directly this function.
 * @see    operator << (vipFrameT<unsigned char>&)
 */
VIPRESULT vipCodec_Sample::importFrom(vipFrameT<unsigned char>& img)
 {
	DEBUGMSG("int vipCodec_Sample::importFrom(vipFrameYUV420& img) [reading data]", doBuffering)

	return VIPRET_NOT_IMPLEMENTED;
 }











vipCodec_SampleParameters::vipCodec_SampleParameters()
 {
	reset();
 }

vipCodec_SampleParameters::vipCodec_SampleParameters(const char* filename, int stream, long frameIndex)
 {
	reset();
	setFileName(filename);
	setStream(stream);
	setFrameIndex(frameIndex);
 }

void vipCodec_SampleParameters::reset()
 {
	strcpy(fileName, (const char*)"input.\0");
	frameIndex = 0;
	stream = 0;
 }



void vipCodec_SampleParameters::setFileName(const char *filename)
 {
	strncpy(fileName, filename, 64);
 }



void vipCodec_SampleParameters::setFrameIndex(long index)
 {
	frameIndex = index;
 }



void vipCodec_SampleParameters::setStream(int s)
 {
	stream = s;
 }



/**
 * @brief  Serialize class to XML format.
 *         Class' tag is <vipCodec_SampleParameters>
 *
 * @param[in] fp output stream's pointer
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 */
VIPRESULT vipCodec_SampleParameters::saveToStreamXML(FILE *fp)
 {
	if ( fp == NULL )
		return VIPRET_PARAM_ERR;

	if( fprintf(fp, "<vipCodec_SampleParameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <filename value=\"%s\" />\n", fileName) == EOF)
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <stream value=\"%d\" />\n", stream) == EOF)
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <frameIndex value=\"%ld\" />\n", frameIndex) == EOF)
		return VIPRET_INTERNAL_ERR;

	if( fprintf(fp, "</vipCodec_SampleParameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	return VIPRET_OK;
 }




/**
 * @brief  Deserialize class from XML format.
 *         Class' tag must be <vipCodec_SampleParameters>
 *
 * @param[in] fp input stream's pointer
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 */
VIPRESULT vipCodec_SampleParameters::loadFromStreamXML(FILE *fp)
 {
	if ( fscanf(fp, "<vipCodec_SampleParameters>\n") == EOF )
		throw "error in XML file, unable to import data.";

	if ( fscanf(fp, "  <filename value=\"%s\" />\n", fileName) == EOF )
		throw "error in XML file, unable to import data.";

	if ( fscanf(fp, "  <stream value=\"%d\" />\n", &stream) == EOF )
		throw "error in XML file, unable to import data.";

	if ( fscanf(fp, "  <frameIndex value=\"%ld\" />\n", &frameIndex) == EOF )
		throw "error in XML file, unable to import data.";

	return VIPRET_OK;
 }


