/** @file vipMotionLame.cpp
 *
 * File containing methods for the 'vipMotionLame' class.
 * The header for this class can be found in vipMotionLame.h, check that file
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



#include "vipMotionLame.h"

 #define RED_COEF .2989961801
 #define GREEN_COEF .5869947588
 #define BLUE_COEF .1139912943


#include "../filters/vipDigitalFilter.h" // lowpass and average
//#include "../filters/vipDigitalFilters.def" // lowpass and average
vipDFMatrix* lowpass = vipDFMatrix::createKernel_3x3(VETDF_3x3_gaussian);


vipMotionLame::vipMotionLame(vipMotionLameParameters* initParams) : vipVision()
 {
	INFO("vipMotionLame::vipMotionLame(..* initParams) : vipMotion() [CONTRUCTOR]")

	buffer = NULL;
	diff = NULL;

	setParameters(initParams);
	reset();
 }

vipMotionLame::~vipMotionLame()
 {
	INFO("vipMotionLame::~vipMotionLame() [DESTRUCTOR]")

	if (buffer != NULL)
		delete buffer;

	if (diff != NULL)
		delete diff;


	delete myParams;//BUG

 }

VIPRESULT vipMotionLame::reset()
 {
	INFO("int vipMotionLame::reset() [SET DEFAULT PARAMETERS]")

	if (buffer != NULL)
		delete buffer;
	buffer = NULL;

	if (diff != NULL)
		delete diff;
	diff = NULL;

	alertCall = NULL;
	alertCallArgument = NULL;

	lastDiffValue = 0;

	setName("Lame Motion Detection");
	setDescription("detect difference between 2 frames.");
	setVersion(1.0);

	return VIPRET_OK;
 }


VIPRESULT vipMotionLame::setParameters(vipMotionLameParameters* initParams)
 {
	if ( initParams == NULL )
		myParams = new vipMotionLameParameters();
	else
		myParams = initParams;

	return VIPRET_OK;
 }




void vipMotionLame::initFrame(vipFrameRGB24& img)
 {
	if (buffer != NULL)
		delete buffer;

	buffer = new vipFrameRGB24(img);

	if (diff != NULL)
		delete diff;

	diff = new vipFrameRGB24(img.width, img.height);
	// memory is already 00000 from PixelRGB24

	lastDiffValue = 0;
 }






VIPRESULT vipMotionLame::importFrom(vipFrameRGB24& img)
 {
	INFO("int vipMotionLame::importFrom(vipFrameRGB24& img) [reading data]")

	if (buffer == NULL)
	 {
		initFrame(img);
		return VIPRET_OK;
	 }

	getDifference(*diff, *buffer, img);

	if ( myParams->doEval && evalDifference(*diff) && myParams->doAlert )
		doAlert();

	*buffer = img;

	return VIPRET_OK;
 }




VIPRESULT vipMotionLame::importFrom(vipFrameYUV420& img)
 {
	INFO("int vipMotionLame::importFrom(vipFrameYUV420& img) [reading data]")

	return VIPRET_NOT_IMPLEMENTED;

 }




VIPRESULT vipMotionLame::importFrom(vipFrameT<unsigned char>& img)
 {
	INFO("int vipMotionLame::importFrom(vipFrameT<unsigned char>& img) [reading data]")

	return VIPRET_NOT_IMPLEMENTED;
 }


int vipMotionLame::evalDifference(vipFrameRGB24& diff_img)
 {
	INFO("")

	vipDigitalFilter::doProcessing(diff_img, *buffer, *lowpass);

	lastDiffValue = getDifferenceBrightnessValue(*buffer);

	if ( myParams->threshold > lastDiffValue )
		return 0;

	return lastDiffValue;
 }



long vipMotionLame::getDifferenceBrightnessValue(vipFrameRGB24& diff_img)
 {
	INFO("")

	long result = 0;

	for (unsigned int i=0; i<diff_img.height*diff_img.width; i++)
	 {
	 	result += (long)(diff_img.data[i][0] * RED_COEF + diff_img.data[i][0] * GREEN_COEF + diff_img.data[i][0] * BLUE_COEF);
	 }

	return result;
 }




////////////////////////////////////////////////////////////////////////////////////////////////




vipMotionLameParameters::vipMotionLameParameters(long threshold, bool doAlert, bool doEval)
 {
	reset();

	setDoEval(doEval);
	setDoAlert(doAlert);
	setThresholdValue(threshold);
 }

void vipMotionLameParameters::reset()
 {
	doAlert = false;
	doEval = true;
	threshold = 1;
 }


void vipMotionLameParameters::setThresholdValue(long value)
 {
 	threshold = value;
 }



VIPRESULT vipMotionLameParameters::saveToStreamXML(FILE *fp)
 {

	if ( fp == NULL )
		return VIPRET_PARAM_ERR;

	if( fprintf(fp, "<vipMotionLameParameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <threshold=\"%ld\" />\n", threshold) == EOF)
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <doEval=\"%u\" />\n", (int)doEval) == EOF)
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <doAlert=\"%u\" />\n", (int)doAlert) == EOF)
		return VIPRET_INTERNAL_ERR;

	if( fprintf(fp, "</vipMotionLameParameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	return VIPRET_OK;
 }


VIPRESULT vipMotionLameParameters::loadFromStreamXML(FILE *fp)
 {
	if ( fscanf(fp, "<vipMotionLameParameters>\n") == EOF )
		throw "error in XML file, unable to import data.";

	if ( fscanf(fp, "  <threshold=\"%ld\" />\n", &threshold) == EOF )
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




