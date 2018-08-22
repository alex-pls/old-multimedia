/** @file vipFilterMorphological.cpp
 *
 * File containing methods for the 'vipFilterMorphological' class.
 * The header for this class can be found in vipFilterMorphological.h, check that file
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



#include "vipFilterMorphological.h"



/**
 * @brief  Default constructor, initialize parameters and superclasses.
 * @param[in] initParams parameters for this module or NULL for defaults.
 */
vipFilterMorphological::vipFilterMorphological(vipFilterMorphologicalParameters* initParams) : vipFilter()
 {
	INFO("vipFilterMorphological::vipFilterMorphological(..* initParams) : vipFilter() [CONTRUCTOR]")


	myParams = NULL;
	setParameters(initParams);

	setName("Morphological Filter");
	setDescription("Erode, Dilate, Open, Close");
	setVersion(1.0);
	//reset();
 }

/**
 * @brief Default destructor, free buffer.
 */
vipFilterMorphological::~vipFilterMorphological()
 {
	INFO("vipFilterMorphological::~vipFilterMorphological() [DESTRUCTOR]")

	if (myParams != NULL)
		delete myParams;
 

 }


/**
 * @brief  Reset buffers and parameters.
 *
 * @return VIPRET_OK
 */
VIPRESULT vipFilterMorphological::reset()
 {
	INFO("int vipFilterMorphological::reset() [SET DEFAULT PARAMETERS]")


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
 * @param[in] initParams Instance of vipFilterMorphologicalParameters or NULL,
 *                       NULL argument make function to create a new
 *                       instance with default parameters.
 *
 * @return VIPRET_OK
 */

 



 VIPRESULT vipFilterMorphological::setParameters (vipFilterMorphologicalParameters* initParams)
 {
	
	if (initParams != NULL && myParams == initParams)
		return VIPRET_PARAM_ERR;

	if ( initParams == NULL )
	 {
		if ( myParams != NULL )
			reset();
		else {
			
			myParams = new vipFilterMorphologicalParameters();
		}
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
 VIPRESULT vipFilterMorphological::importFrom(vipFrameYUV420& img)
  {
 	DEBUGMSG("int vipFilterMorphological::importFrom(vipFrameYUV420& img) [reading data]", myParams->runMode)


 	switch ( myParams->runMode )
 	 {
 	 case vipFilterMorphologicalParameters::DO_NOTHING:
 			useBufferYUV(img.width, img.height);
 			*bufferYUV = img;
 			return VIPRET_OK_DEPRECATED;


 	 case vipFilterMorphologicalParameters::ERODE:
 	 	  return VIPRET_NOT_IMPLEMENTED;

 	 case vipFilterMorphologicalParameters::DILATE:
 	 	  return VIPRET_NOT_IMPLEMENTED;

 	 case vipFilterMorphologicalParameters::OPEN:
 	 	  return VIPRET_NOT_IMPLEMENTED;

 	 case vipFilterMorphologicalParameters::CLOSE:
 	 	  return VIPRET_NOT_IMPLEMENTED;

 	 default:
 		  return VIPRET_PARAM_ERR;
  	 }


 	return VIPRET_NOT_IMPLEMENTED;
  }


/**
 * @brief Process the frame with current settings and store in buffer.
 *
 * @param[in] img VIPLib Frame YUV444 to be processed.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if runmode is unknown,
 *         VIPRET_NOT_IMPLEMENTED if this function is not enabled jet, VIPRET_INTERNAL_ERR else.
 *
 * @note  Input operator (<<) call directly this function.
 * @see   operator << (vipFrameYUV444&)
 */
VIPRESULT vipFilterMorphological::importFrom(vipFrameYUV444& img)
 {
	DEBUGMSG("int vipFilterMorphological::importFrom(vipFrameYUV444& img) [reading data]", myParams->runMode)


	switch ( myParams->runMode )
	 {
	 case vipFilterMorphologicalParameters::DO_NOTHING:
			useBufferYUV444(img.width, img.height);
			*bufferYUV444 = img;
			return VIPRET_OK_DEPRECATED;


	 case vipFilterMorphologicalParameters::ERODE:
	 	  return VIPRET_NOT_IMPLEMENTED;

	 case vipFilterMorphologicalParameters::DILATE:
	 	  return VIPRET_NOT_IMPLEMENTED;

	 case vipFilterMorphologicalParameters::OPEN:
	 	  return VIPRET_NOT_IMPLEMENTED;

	 case vipFilterMorphologicalParameters::CLOSE:
	 	  return VIPRET_NOT_IMPLEMENTED;

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
VIPRESULT vipFilterMorphological::importFrom(vipFrameRGB24& img)
 {
	DEBUGMSG("int vipFilterMorphological::importFrom(vipFrameRGB24& img) [reading data]", myParams->runMode)

	vipFrameRGB24 temp;
	myParams->setStructElem();

	switch ( myParams->runMode )
	 {
	 case vipFilterMorphologicalParameters::DO_NOTHING:
			useBufferRGB(img.width, img.height);
			*bufferRGB = img;
			return VIPRET_OK_DEPRECATED;

	 case vipFilterMorphologicalParameters::ERODE:
	 		useBufferRGB(img.width, img.height);
			return erode(*bufferRGB, img);

	 case vipFilterMorphologicalParameters::DILATE:
	 		useBufferRGB(img.width, img.height);
			return dilate(*bufferRGB, img);
	
	 case vipFilterMorphologicalParameters::OPEN:
	 		useBufferRGB(img.width, img.height);
			erode(temp, img);
			return dilate(*bufferRGB, temp);
	 
	 case vipFilterMorphologicalParameters::CLOSE:
	 		useBufferRGB(img.width, img.height);
			dilate (temp, img);
			return erode(*bufferRGB, temp);

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
VIPRESULT vipFilterMorphological::importFrom(vipFrameT<unsigned char>& img)
 {
	DEBUGMSG("int vipFilterMorphological::importFrom(vipFrameT<unsigned char>& img) [reading data]", myParams->runMode)
	

	switch ( myParams->runMode )
	 {
	 case vipFilterMorphologicalParameters::DO_NOTHING:
			useBufferTuC(img.width, img.height, img.profile);
			*bufferTuC = img;
			return VIPRET_OK_DEPRECATED;

	 case vipFilterMorphologicalParameters::ERODE:
	 		
			return VIPRET_NOT_IMPLEMENTED;
	 
	 case vipFilterMorphologicalParameters::DILATE:
	 		
			return VIPRET_NOT_IMPLEMENTED;
	
	case vipFilterMorphologicalParameters::OPEN:
	 		
			return VIPRET_NOT_IMPLEMENTED;
	 
	 case vipFilterMorphologicalParameters::CLOSE:
	 		
			return VIPRET_NOT_IMPLEMENTED;

	 default:
		  return VIPRET_PARAM_ERR;
	 }


	return VIPRET_NOT_IMPLEMENTED;
 }


///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Erodes source image and puts the result into dest.
 *
 * @param[out] dest VIPLib Frame RGB24 processed.
 * @param[in]  source VIPLib Frame RGB24 to be processed.
 *
 * @return VIPRET_OK
 *
 * @note  This is not a static function.
 */

VIPRESULT vipFilterMorphological::erode(vipFrameRGB24& dest, vipFrameRGB24& source)
 { 
	int i, j;
	int x, y;
	int maskElem;
	int minWidth, minHeight;
	int maxWidth, maxHeight;
	int Radius;
	float Lum;
	float CurrentLum;
	float minLum;
	int imin, jmin;

	if (dest.width != source.width || dest.height != source.height)
		dest.reAllocCanvas(source.width, source.height);
	Radius = myParams->getRadius();
	//A luminance matrix is created: it is a grey-level image:
	setLuminanceMatrix(source);
	for (i = 0; i < (int) source.height; i++) {
		for (j = 0; j < (int) source.width; j++) {
			//These controls are inserted to prevent analysing pixels
			//outside the matrix:
			minHeight = (i-Radius < 0) ? 0 :(i-Radius);
			minWidth =(j-Radius < 0) ? 0 : (j-Radius);
			maxHeight = (i+Radius > (int) source.height - 1) ? (source.height - 1) : i+Radius;
			maxWidth = (j+Radius > (int) source.width - 1) ? (source.width - 1) : j+Radius;
			minLum = CurrentLum = LuminanceMatrix[i][j];
			imin = i;
			jmin = j;
			//First, all the elements inside a square or reptangle are considered
			for ( x = minHeight; x <= maxHeight; x++) {
				for (y = minWidth; y <= maxWidth; y++) {
					maskElem = myParams ->getStructElem(x-i+Radius,y-j+Radius);
					//Then luminance is calculated only for those pixels which
					//belong to the structural element:
					if (maskElem == 1) {
						Lum = LuminanceMatrix[x][y];
						//If a pixel is darker than the "darkest" currently found, 
						//luminance and coordinates of that pixel are stored:
						if ((Lum < minLum) && (Lum >= 0)) {
							minLum = Lum;
							imin = x;
							jmin = y;
						}
					}
				}
			}
			//If the darkest pixel is not the current one (i,j), the new value
			//overwrites the old one:
			if (minLum < CurrentLum) {
				dest.data[i*dest.width+j] = source.data[imin*source.width+jmin];
			} else {
				dest.data[i*dest.width+j] = source.data[i*source.width+j];
			}
		}
	}
	//Finally, luminance matrix is deleted:
	deleteLuminanceMatrix((int)(source.height));
	 
	return VIPRET_OK;
 }

VIPRESULT vipFilterMorphological::erode(vipFrameYUV420& dest, vipFrameYUV420& source)
 { 
	return VIPRET_NOT_IMPLEMENTED;
	
 }

VIPRESULT vipFilterMorphological::erode(vipFrameYUV444& dest, vipFrameYUV444& source)
 { 
	return VIPRET_NOT_IMPLEMENTED;
	
 }

VIPRESULT vipFilterMorphological::erode(vipFrameT<unsigned char>& dest, vipFrameT<unsigned char>& source)
 { 
	return VIPRET_NOT_IMPLEMENTED;
	
 }


/**
 * @brief Dilates source image and puts the result into dest.
 *
 * @param[out] dest VIPLib Frame RGB24 processed.
 * @param[in]  source VIPLib Frame RGB24 to be processed.
 *
 * @return VIPRET_OK
 *
 * @note  This is not a static function.
 */
 
 VIPRESULT vipFilterMorphological::dilate(vipFrameRGB24& dest, vipFrameRGB24& source)
 { 
	int i, j;
	int x, y;
	int maskElem;
	int minWidth, minHeight;
	int maxWidth, maxHeight;
	int Radius;
	float Lum;
	float CurrentLum;
	float maxLum;
	int iMax, jMax;

	if (dest.width != source.width || dest.height != source.height)
		dest.reAllocCanvas(source.width, source.height);
	Radius = myParams->getRadius();
	//A luminance matrix is created: it is a grey-level image:
	setLuminanceMatrix(source);
	for (i = 0; i < (int) source.height; i++) {
		for (j = 0; j < (int) source.width; j++) {
			//These controls are inserted to prevent analysing pixels
			//outside the matrix:
			minHeight = (i-Radius < 0) ? 0 :(i-Radius);
			minWidth =(j-Radius < 0) ? 0 : (j-Radius);
			maxHeight = (i+Radius > (int) source.height - 1) ? (source.height - 1) : i+Radius;
			maxWidth = (j+Radius > (int) source.width - 1) ? (source.width - 1) : j+Radius;
			maxLum = CurrentLum = LuminanceMatrix[i][j];
			iMax = i;
			jMax = j;
			//First, all the elements inside a square or reptangle are considered
			for ( x = minHeight; x <= maxHeight; x++) {
				for (y = minWidth; y <= maxWidth; y++) {
					maskElem = myParams ->getStructElem(x-i+Radius,y-j+Radius);
					//Then luminance is calculated only for those pixels which
					//belong to the structural element:
					if (maskElem == 1) {
						Lum = LuminanceMatrix[x][y];
						//If a pixel is whiter than the "whitest" currently found, 
						//luminance and coordinates of that pixel are stored:
						if (Lum > maxLum) {
							maxLum = Lum;
							iMax = x;
							jMax = y;
						}
					}
				}
			}
			//If the whitest pixel is not the current one (i,j), the new value
			//overwrites the old one:
			if (maxLum > CurrentLum) {
				dest.data[i*dest.width+j] = source.data[iMax*source.width+jMax];
			} else {
				dest.data[i*dest.width+j] = source.data[i*source.width+j];
			}
		}
	}
	//Finally, luminance matrix is deleted:
	deleteLuminanceMatrix((int)(source.height));
	 
	return VIPRET_OK;
 }

 VIPRESULT vipFilterMorphological::dilate(vipFrameYUV420& dest, vipFrameYUV420& source)
  { 
 	return VIPRET_NOT_IMPLEMENTED;
 	
  }

 VIPRESULT vipFilterMorphological::dilate(vipFrameYUV444& dest, vipFrameYUV444& source)
  { 
 	return VIPRET_NOT_IMPLEMENTED;
 	
  }

 VIPRESULT vipFilterMorphological::dilate(vipFrameT<unsigned char>& dest, vipFrameT<unsigned char>& source)
  { 
 	return VIPRET_NOT_IMPLEMENTED;
 	
  }

 /**
 * @brief Creates a matrix containing the luminance of each pixel of the source image.
 *
 * @param[in] source VIPLib Frame RGB24 to be processed.
 *
 */
 
 void vipFilterMorphological::setLuminanceMatrix(vipFrameRGB24 source) {
	unsigned int i, j;
	PixelRGB24 CurrentPixel;
	LuminanceMatrix = new float * [source.height];
	for (i = 0; i < source.height; i++){
		LuminanceMatrix[i] = new float [source.width];
		for (j = 0; j < source.width; j++) {
			source.getPixel(j,i,CurrentPixel);
			//Luminance is calculated for every pixel:			
			LuminanceMatrix[i][j] = (float)(0.2125*CurrentPixel[0]+0.7154*CurrentPixel[1]+0.0721*CurrentPixel[2]);
		}
	}
 }

 /**
 * @brief Deletes the matrix containing the luminance of each pixel of the source image.
 *
 * @param[in] height Numbers of lines in the matrix.
 *
 */

 void vipFilterMorphological::deleteLuminanceMatrix(int height) {
	int i;
	for (i = 0; i < height; i++){
		delete LuminanceMatrix[i];
	}
	delete LuminanceMatrix;
 }


///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////


/**
 * @brief  Default constructor.
 */

vipFilterMorphologicalParameters::vipFilterMorphologicalParameters()
 {
	StructElem = NULL;
 }


 /**
 * @brief Default destructor, if necessary deletes the structural element.
 */

 vipFilterMorphologicalParameters::~vipFilterMorphologicalParameters() {
	if (StructElem != NULL) {
		for (int x = 0; x < 2*StructElemRadius; x++) {
			delete StructElem[x];
		 }
		 delete StructElem;
	}
 }

 /**
 * @brief Sets the structural element radius.
 * 
 * @param[in] radius Structural element radius
 */
 void vipFilterMorphologicalParameters::setRadius(int radius){
	 StructElemRadius = radius;
 }
 
 /**
 * @brief Initializes the structural element.
 */
 void vipFilterMorphologicalParameters::setStructElem()
{
	int dim;
	int centre;
	int SquareDistance;

	dim = 2 * StructElemRadius + 1;
	centre = StructElemRadius;
	
	StructElem = new int * [dim];
	for (int x = 0; x < dim; x++) {
		StructElem[x] = new int [dim];
	}

	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			SquareDistance = (i-centre)*(i-centre)+(j-centre)*(j-centre);
			//The structural element is round: the square distance from the centre
			//is calculated to create the mask. A "+1" factor is added to improve
			//results:
			if (SquareDistance <= (StructElemRadius*StructElemRadius)+1) {
				StructElem[i][j] = 1;
			} else {
				StructElem[i][j] = -1;
			}
		}
	}
}

/**
 * @brief Sets the structural element radius.
 * 
 * @param[in] i Structural element row
 * @param[in] j Structural element column
 * @return Element in position (i,j)
 */

int  vipFilterMorphologicalParameters::getStructElem(int i, int j){
	return (StructElem[i][j]);
}

/**
 * @brief Resets the object.
 */

void vipFilterMorphologicalParameters::reset()
 {

	runMode = vipFilterMorphologicalParameters::DO_NOTHING;
	
	StructElemRadius = 0;

	currentBuffer = vipFilterParameters::NONE;


	if (StructElem != NULL) {
		for (int x = 0; x < StructElemRadius; x++) {
			delete StructElem[x];
		 }
		 delete StructElem;
	}
 }
 /**
 * @brief Gives the structural element radius.
 *
 * @return Structural element radius
 */
 int vipFilterMorphologicalParameters::getRadius() {
	 return StructElemRadius;
 }

 /**
  * @brief  Serialize class to XML format.
  *         Class' tag is <vipCoder_MOVParameters>
  *
  * @param[in] fp output stream's pointer
  *
  * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
  */
 int vipFilterMorphologicalParameters::saveToStreamXML(FILE *fp)
 {

	if ( fp == NULL )
		return VIPRET_PARAM_ERR;

	if( fprintf(fp, "<vipFilterMorphologicalParameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	// add your variables here
	if ( fprintf(fp, "  <structural element radius value=\"%i\" />\n", (int)StructElemRadius) == EOF)
		return VIPRET_INTERNAL_ERR;
	// end of my varables

	if ( fprintf(fp, "  <runmode value=\"%i\" />\n", (int)runMode) == EOF)
		return VIPRET_INTERNAL_ERR;



	if ( fprintf(fp, "  <internalBufferType value=\"%u\" />\n", (int)currentBuffer) == EOF)
		return VIPRET_INTERNAL_ERR;


	if( fprintf(fp, "</vipFilterMorphologicalParameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	return VIPRET_OK;
 }

 /**
  * @brief  Deserialize class from XML format.
  *         Class' tag must be <vipCoder_MOVParameters>
  *
  * @param[in] fp input stream's pointer
  *
  * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
  */

int vipFilterMorphologicalParameters::loadFromStreamXML(FILE *fp)
 {
	if ( fscanf(fp, "<vipFilterMorphologicalParameters>\n") == EOF )
		throw "error in XML file, unable to import data.";

	// add your variables here
	
	int radiusTmp = 0;
	if ( fscanf(fp, "  <structural element radius value=\"%i\" />\n", &radiusTmp) == EOF )
		throw "error in XML file, unable to import data.";
	else
		StructElemRadius = (int)radiusTmp;


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
