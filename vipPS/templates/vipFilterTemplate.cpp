/** @file %FILENAME%.cpp
 *
 * File containing methods for the '%CLASSNAME%' class.
 * The header for this class can be found in %FILENAME%.h, check that file
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



#include "%FILENAME%.h"



%DOCFUN%/**
 * @brief  Default constructor, initialize parameters and superclasses.
 * @param[in] initParams parameters for this module or NULL for defaults.
 */
%CLASSNAME%::%CLASSNAME%(%CLASSNAME%Parameters* initParams) : vipFilter()
 {
	INFO("%CLASSNAME%::%CLASSNAME%(..* initParams) : vipFilter() [CONTRUCTOR]")

%EFI_START%
	myParams = NULL;
	setParameters(initParams);

	setName("Geometric Editing Filter");
	setDescription("Resize, Crop, Rotation, Flip");
	setVersion(1.0);
%EFI_END%
	reset();
 }

%DOCFUN%/**
 * @brief Default destructor, free buffer.
 */
%CLASSNAME%::~%CLASSNAME%()
 {
	INFO("%CLASSNAME%::~%CLASSNAME%() [DESTRUCTOR]")
%EFI_START%
	if (myParams != NULL)
		delete myParams;
 %EFI_END%

 }

%VFI_START%
%DOCFUN%/**
 * @brief  Reset buffers and parameters.
 *
 * @return VIPRET_OK
 */
VIPRESULT %CLASSNAME%::reset()
 {
	INFO("int %CLASSNAME%::reset() [SET DEFAULT PARAMETERS]")

%EFI_START%
	releaseBuffers();

	if (myParams != NULL)
	 {
		myParams->reset();
		allocateBuffer(myParams->currentBuffer);
	 }
	else
		setParameters(NULL);
%EFI_END%

	return VIPRET_OK;
 }
%VFI_END%

%VFI_START%
%DOCFUN%/**
 * @brief  Set parameters for this filter.
 *
 * @param[in] initParams Instance of %CLASSNAME%Parameters or NULL,
 *                       NULL argument make function to create a new
 *                       instance with default parameters.
 *
 * @return VIPRET_OK
 */
VIPRESULT %CLASSNAME%::setParameters (%CLASSNAME%Parameters* initParams)
 {
%EFI_START%
	if (initParams != NULL && myParams == initParams)
		return VIPRET_PARAM_ERR;

	if ( initParams == NULL )
	 {
		if ( myParams != NULL )
			reset();
		else
			myParams = new %CLASSNAME%Parameters();
	 }
	else
	 {
		if ( myParams != NULL )
			delete myParams;

		myParams = initParams;
	 }

	allocateBuffer(myParams->currentBuffer);
%EFI_END%

	return VIPRET_OK;
 }
%VFI_END%

%VFI_START%
%DOCFUN%/**
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
VIPRESULT %CLASSNAME%::importFrom(vipFrameYUV420& img)
 {
	DEBUGMSG("int %CLASSNAME%::importFrom(vipFrameYUV420& img) [reading data]", myParams->runMode)

%EFI_START%
	switch ( myParams->runMode )
	 {
	 case %CLASSNAME%Parameters::DO_NOTHING:
			useBufferYUV(img.width, img.height);
			*bufferYUV = img;
			return VIPRET_OK_DEPRECATED;


	 case %CLASSNAME%Parameters::ROTATE90:
	 		useBufferYUV(img.height, img.width);
			return rotate90(*bufferYUV, img);

	 default:
		  return VIPRET_PARAM_ERR;
 	 }
%EFI_END%

	return VIPRET_NOT_IMPLEMENTED;
 }
%VFI_END%

%VFI_START%
%DOCFUN%/**
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
VIPRESULT %CLASSNAME%::importFrom(vipFrameRGB24& img)
 {
	DEBUGMSG("int %CLASSNAME%::importFrom(vipFrameRGB24& img) [reading data]", myParams->runMode)

%EFI_START%
	switch ( myParams->runMode )
	 {
	 case %CLASSNAME%Parameters::DO_NOTHING:
			useBufferRGB(img.width, img.height);
			*bufferRGB = img;
			return VIPRET_OK_DEPRECATED;

	 case %CLASSNAME%Parameters::ROTATE90:
	 		useBufferRGB(img.height, img.width);
			return rotate90(*bufferRGB, img);

	 default:
		  return VIPRET_PARAM_ERR;
	 }
%EFI_END%

	return VIPRET_NOT_IMPLEMENTED;
 }
%VFI_END%

%VFI_START%
%DOCFUN%/**
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
VIPRESULT %CLASSNAME%::importFrom(vipFrameT<unsigned char>& img)
 {
	DEBUGMSG("int %CLASSNAME%::importFrom(vipFrameT<unsigned char>& img) [reading data]", myParams->runMode)

%EFI_START%
	switch ( myParams->runMode )
	 {
	 case %CLASSNAME%Parameters::DO_NOTHING:
			useBufferTuC(img.width, img.height, img.profile);
			*bufferTuC = img;
			return VIPRET_OK_DEPRECATED;

	 case %CLASSNAME%Parameters::ROTATE90:
	 		useBufferTuC(img.height, img.width, img.profile);
			return rotate90(*bufferTuC, img);

	 default:
		  return VIPRET_PARAM_ERR;
	 }
%EFI_END%

	return VIPRET_NOT_IMPLEMENTED;
 }
%VFI_END%

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

%EFI_START%
VIPRESULT %CLASSNAME%::rotate90(vipFrameYUV420& dest, vipFrameYUV420& source)
 {
	if (dest.width != source.height || dest.height != source.width)
		dest.reAllocCanvas(source.height, source.width);

	return VIPRET_NOT_IMPLEMENTED;
 }
%EFI_END%

%EFI_START%
VIPRESULT %CLASSNAME%::rotate90(vipFrameRGB24& dest, vipFrameRGB24& source)
 {
	if (dest.width != source.height || dest.height != source.width)
		dest.reAllocCanvas(source.height, source.width);

	for ( unsigned int y=0; y < dest.height; y++ ) // single pixel copy routine
	  for ( unsigned int x=0; x < dest.width; x++ )
		dest.data[(dest.height-1-y)*dest.width+x] = source.data[x*source.width + y];

	return VIPRET_OK;
 }
%EFI_END%

%EFI_START%
VIPRESULT %CLASSNAME%::rotate90(vipFrameT<unsigned char>& dest, vipFrameT<unsigned char>& source)
 {
	if (dest.width != source.height || dest.height != source.width)
		dest.reAllocCanvas(source.height, source.width);

	return VIPRET_NOT_IMPLEMENTED;
 }
%EFI_END%




///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////








%CLASSNAME%Parameters::%CLASSNAME%Parameters()
 {
	reset();
 }

void %CLASSNAME%Parameters::reset()
 {
%EFI_START%
	runMode = %CLASSNAME%Parameters::DO_NOTHING;
%EFI_END%

	currentBuffer = vipFilterParameters::NONE;
 }

int %CLASSNAME%Parameters::saveToStreamXML(FILE *fp)
 {

	if ( fp == NULL )
		return VIPRET_PARAM_ERR;

	if( fprintf(fp, "<%CLASSNAME%Parameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	// add your variables here

%EFI_START%
	if ( fprintf(fp, "  <runmode value=\"%i\" />\n", (int)runMode) == EOF)
		return VIPRET_INTERNAL_ERR;
%EFI_END%

%VFI_START%
	if ( fprintf(fp, "  <internalBufferType value=\"%u\" />\n", (int)currentBuffer) == EOF)
		return VIPRET_INTERNAL_ERR;
%VFI_END%

	if( fprintf(fp, "</%CLASSNAME%Parameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	return VIPRET_OK;
 }


int %CLASSNAME%Parameters::loadFromStreamXML(FILE *fp)
 {
	if ( fscanf(fp, "<%CLASSNAME%Parameters>\n") == EOF )
		throw "error in XML file, unable to import data.";

	// add your variables here


%EFI_START%
	int runTmp = 0;
	if ( fscanf(fp, "  <runmode value=\"%i\" />\n", &runTmp) == EOF )
		throw "error in XML file, unable to import data.";
	else
		runMode = (RUNMODE)runTmp;
%EFI_END%

%VFI_START%
	int cB = (int)currentBuffer;
	if ( fscanf(fp, "  <internalBufferType value=\"%u\" />\n", &cB) == EOF )
		throw "error in XML file, unable to import data.";
	currentBuffer = (BUFFER_TYPE)cB;
%VFI_END%


	return VIPRET_OK;
 }




