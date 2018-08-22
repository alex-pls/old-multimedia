/** @file %FILENAME%.cpp
 *
 * File containing methods for the '%CLASSNAME%' class.
 * The header for this class can be found in %FILENAME%.h, check that file
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



#include "%FILENAME%.h"


%CLASSNAME%::%CLASSNAME%( %CLASSNAME%Parameters* initParams ) : vipCodec()
 {
	DEBUGMSG("%CLASSNAME%::%CLASSNAME%(%CLASSNAME%Parameters* initParams) : vipCodec() [CONTRUCTOR] ", *filename)


	setParameters(initParams);
	reset();
 }


%EFI_START%
%DOCFUN%/**
 * @brief  Initialize parameters and load image/video stream from file.
 *         vipFrameRGB constructor.
 *
 * @param[in] filename Input BMP filename.
 * @param[in] format BMP Encoding Format, default auto-selection.
 */
%CLASSNAME%::%CLASSNAME%(char *filename, int stream) : vipCodec()
 {
	DEBUGMSG("%CLASSNAME%::%CLASSNAME%(char *filename, FileFormat format) : vipCodec() [CONTRUCTOR] ", *filename)


	setParameters(NULL);
	reset();

 	load( filename, stream );

 }
%EFI_END%


VIPRESULT %CLASSNAME%::reset()
 {
	INFO("int %CLASSNAME%::reset() [SET DEFAULT PARAMETERS]")

%EFI_START%
	width  = 0;
	height = 0;
%EFI_END%

	if (myParams != NULL)
		myParams->reset();

	setName("");
	setDescription("");
	setVersion(0.0);

	return VIPRET_OK;
 }


%CLASSNAME%::~%CLASSNAME%()
 {
	if (myParams != NULL)
		delete myParams; //BUG

 }



int %CLASSNAME%::setParameters (%CLASSNAME%Parameters* initParams)
 {

	if ( initParams == NULL )
		myParams = new %CLASSNAME%Parameters();
	else
		myParams = initParams;

	return VIPRET_OK;
 }




%VFI_START%
%DOCFUN%/**
 * @brief get movie's audio streams count.
 *
 * @return number of audio streams.
 */
int %CLASSNAME%::getAudioStreamCount()
 {
	 return -1;
 };
%VFI_END%

%VFI_START%
%DOCFUN%/**
 * @brief get movie's video streams count.
 *
 * @return number of video streams.
 */
int %CLASSNAME%::getVideoStreamCount()
 {
	 return -1;
 };
%VFI_END%

%VFI_START%
/**
 * @brief get movie's video frame rate.
 *
 * @param[in] stream select stream index.
 *                   default is -1: current active stream.
 *
 * @return number of frame per second.
 */
float %CLASSNAME%::getVideoFrameRate(int stream)
 {
	return 0.0;
 }
%VFI_END%

%VFI_START%
/**
 * @brief  Get movie's video stream frame count.
 *
 * @param[in] stream select stream, default is current stream.
 *
 * @return number of frames in selected video stream.
 */
long %CLASSNAME%::getVideoStreamLength(int stream)
 {
	return 0;
 }
%VFI_END%


%VFI_START%
%DOCFUN%/**
 * @brief  Get movie's audio stream sample count.
 *
 * @param[in] stream select stream, default is current stream.
 *
 * @return number of samples in selected audio stream.
 */
long %CLASSNAME%::getAudioStreamLength(int stream)
 {
	return 0;
 }
%VFI_END%

%VFI_START%
%DOCFUN%/**
 * @brief  Close current movie (close file access).
 *
 * @return VIPRET_ILLEGAL_USE if movie was not loaded, VIPRET_OK else.
 */
VIPRESULT %CLASSNAME%::close()
 {
	return VIPRET_NOT_IMPLEMENTED;
 }
%VFI_END%




%VFI_START%
%DOCFUN%/**
 * @brief  Load a movie from a file.
 *
 * @param[in] filename input movie filename
 * @param[in] stream video stream to load (default is first: 0)
 *
 * @return VIPRET_ILLEGAL_USE if file is not correctly loaded, VIPRET_OK else.
 */
VIPRESULT %CLASSNAME%::load(char *filename, int stream)
 {
	DEBUGMSG("int %CLASSNAME%::load(char *filename, FileFormat format) [loading data]", filename)

 	myParams->setFileName(filename);
 	myParams->setStream(stream);

	return VIPRET_NOT_IMPLEMENTED;
 }

%VFI_END%

%VFI_START%
%DOCFUN%/**
 * @brief  Save current movie to file.
 *
 * @param[in] filenameoutput movie filename
 * @param[in] stream video stream to load (default is first: 0)
 *
 * @return VIPRET_ILLEGAL_USE if file is not correctly loaded, VIPRET_OK else.
 */
VIPRESULT %CLASSNAME%::save(char *filename, int stream)
 {
	return VIPRET_NOT_IMPLEMENTED;
 }

%VFI_END%










%VFI_START%
%DOCFUN%/**
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
VIPRESULT %CLASSNAME%::extractTo(vipFrameYUV420& img)
 {
	DEBUGMSG("int %CLASSNAME%::extractTo(vipFrameYUV420& img) [pushing data]", doBuffering)

%EFI_START%
	if (width != img.width || height != img.height)
		img.reAllocCanvas(width, height);
%EFI_END%

	return VIPRET_NOT_IMPLEMENTED;
 }
%VFI_END%


%VFI_START%
%DOCFUN%/**
 * @brief  Load data into passed image, move current index to next frame.
 *
 * @param[out] img VIPLib Cache Frame to store data.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
 *
 * @note   Ouput operator (>>) call directly this function.
 * @see    operator >> (vipFrameYUV444&)
 * @see    AutoInput
 */
VIPRESULT %CLASSNAME%::extractTo(vipFrameYUV444& img)
 {
	DEBUGMSG("int %CLASSNAME%::extractTo(vipFrameYUV444& img) [pushing data]", doBuffering)

%EFI_START%
	if (width != img.width || height != img.height)
		img.reAllocCanvas(width, height);
%EFI_END%

	return VIPRET_NOT_IMPLEMENTED;
 }
%VFI_END%



%VFI_START%
%DOCFUN%/**
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
VIPRESULT %CLASSNAME%::extractTo(vipFrameRGB24& img)
 {
	DEBUGMSG("int %CLASSNAME%::extractTo(vipFrameRGB24& img) [pushing data]", doBuffering)

%EFI_START%
	if (width != img.width || height != img.height)
		img.reAllocCanvas(width, height);
%EFI_END%

	return VIPRET_NOT_IMPLEMENTED;
 }
%VFI_END%


%VFI_START%
%DOCFUN%/**
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
VIPRESULT %CLASSNAME%::extractTo(vipFrameT<unsigned char>& img)
 {
	DEBUGMSG("int %CLASSNAME%::extractTo(vipFrameT<unsigned char>& img) [pushing data]", doBuffering)

%EFI_START%
	if (width != img.width || height != img.height)
		img.reAllocCanvas(width, height);
%EFI_END%


	return VIPRET_NOT_IMPLEMENTED;
 }
%VFI_END%


%VFI_START%
%DOCFUN%/**
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
VIPRESULT %CLASSNAME%::importFrom(vipFrameYUV420& img)
 {
	DEBUGMSG("int %CLASSNAME%::importFrom(vipFrameYUV420& img) [reading data]", doBuffering)

	return VIPRET_NOT_IMPLEMENTED;
 }
%VFI_END%

%VFI_START%
%DOCFUN%/**
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
VIPRESULT %CLASSNAME%::importFrom(vipFrameRGB24& img)
 {
	DEBUGMSG("int %CLASSNAME%::importFrom(vipFrameRGB24& img) [reading data]", doBuffering)

	return VIPRET_NOT_IMPLEMENTED;
 }
%VFI_END%


%VFI_START%
%DOCFUN%/**
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
VIPRESULT %CLASSNAME%::importFrom(vipFrameT<unsigned char>& img)
 {
	DEBUGMSG("int %CLASSNAME%::importFrom(vipFrameYUV420& img) [reading data]", doBuffering)

	return VIPRET_NOT_IMPLEMENTED;
 }
%VFI_END%










%CLASSNAME%Parameters::%CLASSNAME%Parameters()
 {
	reset();
 }

%CLASSNAME%Parameters::%CLASSNAME%Parameters(const char* filename, int stream, long frameIndex)
 {
	reset();
	setFileName(filename);
	setStream(stream);
	setFrameIndex(frameIndex);
 }

void %CLASSNAME%Parameters::reset()
 {
	strcpy(fileName, (const char*)"input.\0");
	frameIndex = 0;
	stream = 0;
 }


%EFI_START%
void %CLASSNAME%Parameters::setFileName(const char *filename)
 {
	strncpy(fileName, filename, 64);
 }
%EFI_END%

%EFI_START%
void %CLASSNAME%Parameters::setFrameIndex(long index)
 {
	frameIndex = index;
 }
%EFI_END%

%EFI_START%
void %CLASSNAME%Parameters::setStream(int s)
 {
	stream = s;
 }
%EFI_END%

%VFI_START%
%DOCFUN%/**
 * @brief  Serialize class to XML format.
 *         Class' tag is <%CLASSNAME%Parameters>
 *
 * @param[in] fp output stream's pointer
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 */
VIPRESULT %CLASSNAME%Parameters::saveToStreamXML(FILE *fp)
 {
	if ( fp == NULL )
		return VIPRET_PARAM_ERR;

	if( fprintf(fp, "<%CLASSNAME%Parameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <filename value=\"%s\" />\n", fileName) == EOF)
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <stream value=\"%d\" />\n", stream) == EOF)
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <frameIndex value=\"%ld\" />\n", frameIndex) == EOF)
		return VIPRET_INTERNAL_ERR;

	if( fprintf(fp, "</%CLASSNAME%Parameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	return VIPRET_OK;
 }
%VFI_END%


%VFI_START%
%DOCFUN%/**
 * @brief  Deserialize class from XML format.
 *         Class' tag must be <%CLASSNAME%Parameters>
 *
 * @param[in] fp input stream's pointer
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 */
VIPRESULT %CLASSNAME%Parameters::loadFromStreamXML(FILE *fp)
 {
	if ( fscanf(fp, "<%CLASSNAME%Parameters>\n") == EOF )
		throw "error in XML file, unable to import data.";

	if ( fscanf(fp, "  <filename value=\"%s\" />\n", fileName) == EOF )
		throw "error in XML file, unable to import data.";

	if ( fscanf(fp, "  <stream value=\"%d\" />\n", &stream) == EOF )
		throw "error in XML file, unable to import data.";

	if ( fscanf(fp, "  <frameIndex value=\"%ld\" />\n", &frameIndex) == EOF )
		throw "error in XML file, unable to import data.";

	return VIPRET_OK;
 }
%VFI_END%

