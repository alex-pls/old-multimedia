/** @file vipMotionIlluminationInvariant.cpp
 *
 * File containing methods for the 'vipMotionIlluminationInvariant' class.
 * The header for this class can be found in vipMotionIlluminationInvariant.h, check that file
 * for class description.
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



#include "vipMotionIlluminationInvariant.h"
#include <math.h>


 #define RED_COEF .2989961801
 #define GREEN_COEF .5869947588
 #define BLUE_COEF .1139912943


#include "../filters/vipDigitalFilter.h" // lowpass and average


vipDFMatrix* gaussian = vipDFMatrix::createKernel_3x3(VETDF_3x3_gaussian);
vipDFMatrix* myLowpass = vipDFMatrix::createKernel_3x3(VETDF_3x3_lowpass1);


vipMotionIlluminationInvariant::vipMotionIlluminationInvariant(vipMotionIlluminationInvariantParameters* initParams) : vipVision()
 {
	INFO("vipMotionIlluminationInvariant::vipMotionIlluminationInvariant(..* initParams)  : vipMotion() [CONTRUCTOR]")

	buffer = NULL;
	reflectance = NULL;

	setParameters(initParams);
	reset();
 }

vipMotionIlluminationInvariant::~vipMotionIlluminationInvariant()
 {
	INFO("vipMotionIlluminationInvariant::~vipMotionIlluminationInvariant() [DESTRUCTOR]")

	if (buffer != NULL)
		delete buffer;

	if (reflectance != NULL)
		delete reflectance;


	delete myParams;//BUG

 }

VIPRESULT vipMotionIlluminationInvariant::reset()
 {
	INFO("int vipMotionIlluminationInvariant::reset() [SET DEFAULT PARAMETERS]")

	if (buffer != NULL)
		delete buffer;
	buffer = NULL;

	if (reflectance != NULL)
		delete reflectance;
	reflectance = NULL;

	alertCall = NULL;
	alertCallArgument = NULL;

	lastDiffValue = 0;

	setName("Lame Motion Detection");
	setDescription("detect difference between 2 frames.");
	setVersion(1.0);

	return VIPRET_OK;
 }


VIPRESULT vipMotionIlluminationInvariant::setParameters(vipMotionIlluminationInvariantParameters* initParams)
 {
	if ( initParams == NULL )
		myParams = new vipMotionIlluminationInvariantParameters();
	else
		myParams = initParams;

	return VIPRET_OK;
 }




void vipMotionIlluminationInvariant::initFrame(vipFrameRGB24& img)
 {
	if (buffer != NULL)
		delete buffer;

	buffer = new vipFrameT<unsigned char>(img.width, img.height);

	if (reflectance != NULL)
		delete reflectance;

	reflectance = new vipFrameT<unsigned char>(img.width, img.height);
	diff = new vipFrameT<unsigned char>(img.width, img.height);

	getReflectance(*reflectance, img);

	lastDiffValue = 0;
 }






VIPRESULT vipMotionIlluminationInvariant::importFrom(vipFrameRGB24& img)
 {
	INFO("int vipMotionIlluminationInvariant::importFrom(vipFrameRGB24& img) [reading data]")

	if (buffer == NULL)
	 {
		initFrame(img);
		return VIPRET_OK;
	 }

	getReflectance(*buffer, img);
	getDifference(*diff,*buffer, *reflectance);


	if ( myParams->doEval && evalDifference(*diff) && myParams->doAlert )
		doAlert();

	vipFrameT<unsigned char>* tmp = reflectance;
	reflectance = buffer;//bug
	buffer = tmp;

	return VIPRET_OK;
 }




VIPRESULT vipMotionIlluminationInvariant::importFrom(vipFrameYUV420& img)
 {
	INFO("int vipMotionIlluminationInvariant::importFrom(vipFrameYUV420& img) [reading data]")

	return VIPRET_NOT_IMPLEMENTED;
 }



VIPRESULT vipMotionIlluminationInvariant::importFrom(vipFrameT<unsigned char>& img)
 {
	INFO("int vipMotionIlluminationInvariant::importFrom(vipFrameT<unsigned char>& img) [reading data]")

	return VIPRET_NOT_IMPLEMENTED;
 }



int vipMotionIlluminationInvariant::evalDifference(vipFrameT<unsigned char>& diff_img)
 {
	INFO("")

	unsigned char* diff_ptr = diff_img.data;
        vipFrameT<unsigned char> tmp(diff_img.width, diff_img.height);

	// LP average 5x5
	vipDigitalFilter::doProcessing(diff_img, tmp, *myLowpass);

	lastDiffValue=0;
	for (unsigned int i=0; i< diff_img.width*diff_img.height; i++)
	 {
      		lastDiffValue += (long)*diff_ptr;
	 }


//	if ( myParams->threshold > lastDiffValue )
//		return 0;

	return lastDiffValue;
 }

int vipMotionIlluminationInvariant::evalDifference(vipFrameRGB24& diff_img)
 {
	INFO("")

	vipFrameRGB24 tmp(diff_img.width, diff_img.height);

	// LP average 5x5
	vipDigitalFilter::doProcessing(diff_img, tmp, *myLowpass);

	lastDiffValue=0;
	for (unsigned int i=0; i< diff_img.width*diff_img.height; i++)
	 {
		lastDiffValue += (long)( (float)diff_img.data[i][0] * RED_COEF + (float)diff_img.data[i][0] * GREEN_COEF + (float)diff_img.data[i][0] * BLUE_COEF);
	 }

//	if ( myParams->threshold > lastDiffValue )
//		return 0;

	return lastDiffValue;
 }





VIPRESULT vipMotionIlluminationInvariant::getReflectance(vipFrameT<unsigned char> &refl_img, vipFrameRGB24& source_img)
 {
	unsigned char* refl_ptr = refl_img.data;
	unsigned int i=0;

	vipFrameT<float> buffer(source_img.width, source_img.height);
	vipFrameT<float> lowpass(source_img.width, source_img.height);

	float* buffer_ptr = buffer.data;
	float* lowpass_ptr = lowpass.data;

// refl_img <= log(source_img) = log(illumination) + log (reflectance)

	for (i=0; i< source_img.width*source_img.height; i++, buffer_ptr++)
	 {
		*buffer_ptr = (float)log( (float)source_img.data[i][0] * RED_COEF + (float)source_img.data[i][0] * GREEN_COEF + (float)source_img.data[i][0] * BLUE_COEF );
	 }


// l = LOWPASS(r) , illumination = exp( LOWPASS( log(source_img) ) )

	vipDigitalFilter::doProcessing(buffer, lowpass, *gaussian);


// refl_img = refl_img - l , reflectance = exp( log(source_img) - LOWPASS( log(source_img) )
	buffer_ptr = buffer.data;
	for (i=0; i< source_img.width*source_img.height; i++, lowpass_ptr++, buffer_ptr++)
	 {
		*buffer_ptr -= *lowpass_ptr;
//		*buffer_ptr = *lowpass_ptr - *buffer_ptr;
	 }


// refl_img <= exp(refl_img)

	buffer_ptr = buffer.data;
	for (i=0; i< source_img.width*source_img.height; i++, refl_ptr++, buffer_ptr++)
	 {
		*refl_ptr = (unsigned char) exp(*buffer_ptr);
	 }

	return VIPRET_OK;
 }


















VIPRESULT vipMotionIlluminationInvariant::getReflectance(vipFrameRGB24& source_img, vipFrameRGB24& refl_img)
 {

	unsigned char* refl_ptr = refl_img.data[0];

	vipFrameT<float> buffer(source_img.width, source_img.height);
	vipFrameT<float> lowpass(source_img.width, source_img.height);

	float* buffer_ptr = buffer.data;
	float* lowpass_ptr = lowpass.data;

	float tmp = 0;
	unsigned int i;

// refl_img <= log(source_img) = log(illumination) + log (reflectance)

	for (i=0; i< source_img.width*source_img.height; i++, buffer_ptr++)
	 {
//		*buffer_ptr = log( (float)*source_ptr );
		tmp = (float)( (float)source_img.data[i][0] * RED_COEF + (float)source_img.data[i][0] * GREEN_COEF + (float)source_img.data[i][0] * BLUE_COEF );
		if (tmp)
			*buffer_ptr = (float)log( tmp );

	 }


// l = LOWPASS(r) , illumination = exp( LOWPASS( log(source_img) ) )

	vipDigitalFilter::doProcessing(buffer, lowpass, *gaussian);


// refl_img = refl_img - l , reflectance = exp( log(source_img) - LOWPASS( log(source_img) )

	buffer_ptr = buffer.data;
	for (i=0; i< source_img.width*source_img.height; i++, lowpass_ptr++, buffer_ptr++)
	 {
//		*buffer_ptr -= *lowpass_ptr;
		*buffer_ptr = *lowpass_ptr - *buffer_ptr;

	 }


// refl_img <= exp(refl_img)
	buffer_ptr = buffer.data;
	for (i=0; i< source_img.width*source_img.height; i++)
	 {
		*refl_ptr = (unsigned char) exp(*buffer_ptr);
		*(refl_ptr+1) = (unsigned char) exp(*buffer_ptr);
		*(refl_ptr+2) = (unsigned char) exp(*buffer_ptr);
		refl_ptr += 3;
		buffer_ptr++;
	 }

	return VIPRET_OK;
 }


VIPRESULT vipMotionIlluminationInvariant::getIllumination(vipFrameRGB24& source_img, vipFrameRGB24& ill_img)
 {
	vipFrameT<float> buffer(source_img.width, source_img.height);
	vipFrameT<float> ill(source_img.width, source_img.height);

	float* buffer_ptr = buffer.data;
	float* ill_ptr = ill.data;
	unsigned char* ret_ptr = ill_img.data[0];

	float tmp;
	unsigned int i;

	for (i=0; i< source_img.width*source_img.height; i++, buffer_ptr++)
	 {
		tmp = (float)( (float)source_img.data[i][0] * RED_COEF + (float)source_img.data[i][0] * GREEN_COEF + (float)source_img.data[i][0] * BLUE_COEF);
		if (tmp)
			*buffer_ptr = (float)log( tmp );
	 }

	vipDigitalFilter::doProcessing(buffer, ill, *gaussian);

	for (i=0; i< source_img.width*source_img.height; i++)
	 {
		*ret_ptr = (unsigned char) exp(*ill_ptr);
		*(ret_ptr+1) = (unsigned char) exp(*ill_ptr);
		*(ret_ptr+2) = (unsigned char) exp(*ill_ptr);
		ret_ptr += 3;
		ill_ptr++;
	 }

	return VIPRET_OK;
 }

////////////////////////////////////////////////////////////////////////////////////////////////





vipMotionIlluminationInvariantParameters::vipMotionIlluminationInvariantParameters(unsigned int threshold, bool doAlert)
 {
	reset();

	setDoAlert(doAlert);
	setThresholdValue(threshold);
 }

void vipMotionIlluminationInvariantParameters::reset()
 {
	doAlert = false;
	threshold = 1;
 }


void vipMotionIlluminationInvariantParameters::setThresholdValue(unsigned int value)
 {
 	threshold = value;
 }



VIPRESULT vipMotionIlluminationInvariantParameters::saveToStreamXML(FILE *fp)
 {

	if ( fp == NULL )
		return VIPRET_PARAM_ERR;

	if( fprintf(fp, "<vipMotionIlluminationInvariantParameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <threshold=\"%u\" />\n", threshold) == EOF)
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <doEval=\"%u\" />\n", (int)doEval) == EOF)
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <doAlert=\"%u\" />\n", (int)doAlert) == EOF)
		return VIPRET_INTERNAL_ERR;

	if( fprintf(fp, "</vipMotionIlluminationInvariantParameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	return VIPRET_OK;
 }


VIPRESULT vipMotionIlluminationInvariantParameters::loadFromStreamXML(FILE *fp)
 {
	if ( fscanf(fp, "<vipMotionIlluminationInvariantParameters>\n") == EOF )
		throw "error in XML file, unable to import data.";

	if ( fscanf(fp, "  <threshold=\"%u\" />\n", &threshold) == EOF )
		throw "error in XML file, unable to import data.";

	int boolTmp = 0;
	if ( fscanf(fp, "  <doEval=\"%u\" />\n", &boolTmp) == EOF )
		throw "error in XML file, unable to import data.";

	if (boolTmp == 0)
		doEval = false;
	else
		doEval = true;

	boolTmp = 0;
	if ( fscanf(fp, "  <doAlert=\"%u\" />\n", &boolTmp) == EOF )
		throw "error in XML file, unable to import data.";

	if (boolTmp == 0)
		doAlert = false;
	else
		doAlert = true;

	return VIPRET_OK;
 }



