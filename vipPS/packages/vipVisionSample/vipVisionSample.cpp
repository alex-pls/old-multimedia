/** @file vipVisionSample.cpp
 *
 * File containing methods for the 'vipVisionSample' class.
 * The header for this class can be found in vipVisionSample.h, check that file
 * for class description.
 *
 *
 ****************************************************************************
 *  Class based on Package Studio template: vipVisionTemplate version 0.9.12
 ****************************************************************************
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.science.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DIT - University of Trento
 *
 ****************************************************************************/



#include "vipVisionSample.h"



vipVisionSample::vipVisionSample(vipVisionSampleParameters* initParams) : vipVision()
 {
	INFO("vipVisionSample::vipVisionSample(..* initParams) : vipMotion() [CONTRUCTOR]")

	setParameters(initParams);
	reset();
 }

vipVisionSample::~vipVisionSample()
 {
	INFO("vipVisionSample::~vipVisionSample() [DESTRUCTOR]")

	delete myParams;//BUG
 }

int vipVisionSample::reset()
 {
	INFO("int vipVisionSample::reset() [SET DEFAULT PARAMETERS]")

	alertCall = NULL;
	alertCallArgument = NULL;

	setName("");
	setDescription("");
	setVersion(0.0);

	return VIPRET_OK;
 }


int vipVisionSample::setParameters(vipVisionSampleParameters* initParams)
 {
	if ( initParams == NULL )
		myParams = new vipVisionSampleParameters();
	else
		myParams = initParams;

	return VIPRET_OK;
 }









VIPRESULT vipVisionSample::importFrom(vipFrameYUV420& img)
 {
	INFO("int vipVisionSample::importFrom(vipFrameYUV420& img) [reading data]")

	return VIPRET_NOT_IMPLEMENTED;
 }


VIPRESULT vipVisionSample::importFrom(vipFrameRGB24& img)
 {
	INFO("int vipVisionSample::importFrom(vipFrameRGB24& img) [reading data]")

	return VIPRET_NOT_IMPLEMENTED;
 }




VIPRESULT vipVisionSample::importFrom(vipFrameT<unsigned char>& img)
 {
	INFO("int vipVisionSample::importFrom(vipFrameT<unsigned char>& img) [reading data]")

	return VIPRET_NOT_IMPLEMENTED;
 }





////////////////////////////////////////////////////////////////////////////////////////////////



vipVisionSampleParameters::vipVisionSampleParameters()
 {
	reset();
 }

vipVisionSampleParameters::vipVisionSampleParameters(bool doAlert, bool doEval)
 {
	reset();

	setDoEval(doEval);
	setDoAlert(doAlert);
 }

void vipVisionSampleParameters::reset()
 {
	doAlert = false;
	doEval = true;
 }



int vipVisionSampleParameters::saveToStreamXML(FILE *fp)
 {

	if ( fp == NULL )
		return VIPRET_PARAM_ERR;

	if( fprintf(fp, "<vipVisionSampleParameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	// add your variables here

	if ( fprintf(fp, "  <doEval=\"%u\" />\n", (int)doEval) == EOF)
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <doAlert=\"%u\" />\n", (int)doAlert) == EOF)
		return VIPRET_INTERNAL_ERR;

	if( fprintf(fp, "</vipVisionSampleParameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	return VIPRET_OK;
 }


int vipVisionSampleParameters::loadFromStreamXML(FILE *fp)
 {
	if ( fscanf(fp, "<vipVisionSampleParameters>\n") == EOF )
		throw "error in XML file, unable to import data.";

	// add your variables here

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




