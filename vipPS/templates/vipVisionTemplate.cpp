/** @file %FILENAME%.cpp
 *
 * File containing methods for the '%CLASSNAME%' class.
 * The header for this class can be found in %FILENAME%.h, check that file
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



#include "%FILENAME%.h"



%CLASSNAME%::%CLASSNAME%(%CLASSNAME%Parameters* initParams) : vipVision()
 {
	INFO("%CLASSNAME%::%CLASSNAME%(..* initParams) : vipMotion() [CONTRUCTOR]")

	setParameters(initParams);
	reset();
 }

%CLASSNAME%::~%CLASSNAME%()
 {
	INFO("%CLASSNAME%::~%CLASSNAME%() [DESTRUCTOR]")

	delete myParams;//BUG
 }

int %CLASSNAME%::reset()
 {
	INFO("int %CLASSNAME%::reset() [SET DEFAULT PARAMETERS]")

	alertCall = NULL;
	alertCallArgument = NULL;

	setName("");
	setDescription("");
	setVersion(0.0);

	return VIPRET_OK;
 }


int %CLASSNAME%::setParameters(%CLASSNAME%Parameters* initParams)
 {
	if ( initParams == NULL )
		myParams = new %CLASSNAME%Parameters();
	else
		myParams = initParams;

	return VIPRET_OK;
 }









VIPRESULT %CLASSNAME%::importFrom(vipFrameYUV420& img)
 {
	INFO("int %CLASSNAME%::importFrom(vipFrameYUV420& img) [reading data]")

	return VIPRET_NOT_IMPLEMENTED;
 }


VIPRESULT %CLASSNAME%::importFrom(vipFrameRGB24& img)
 {
	INFO("int %CLASSNAME%::importFrom(vipFrameRGB24& img) [reading data]")

	return VIPRET_NOT_IMPLEMENTED;
 }




VIPRESULT %CLASSNAME%::importFrom(vipFrameT<unsigned char>& img)
 {
	INFO("int %CLASSNAME%::importFrom(vipFrameT<unsigned char>& img) [reading data]")

	return VIPRET_NOT_IMPLEMENTED;
 }





////////////////////////////////////////////////////////////////////////////////////////////////



%CLASSNAME%Parameters::%CLASSNAME%Parameters()
 {
	reset();
 }

%CLASSNAME%Parameters::%CLASSNAME%Parameters(bool doAlert, bool doEval)
 {
	reset();

	setDoEval(doEval);
	setDoAlert(doAlert);
 }

void %CLASSNAME%Parameters::reset()
 {
	doAlert = false;
	doEval = true;
 }



int %CLASSNAME%Parameters::saveToStreamXML(FILE *fp)
 {

	if ( fp == NULL )
		return VIPRET_PARAM_ERR;

	if( fprintf(fp, "<%CLASSNAME%Parameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	// add your variables here

	if ( fprintf(fp, "  <doEval=\"%u\" />\n", (int)doEval) == EOF)
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <doAlert=\"%u\" />\n", (int)doAlert) == EOF)
		return VIPRET_INTERNAL_ERR;

	if( fprintf(fp, "</%CLASSNAME%Parameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	return VIPRET_OK;
 }


int %CLASSNAME%Parameters::loadFromStreamXML(FILE *fp)
 {
	if ( fscanf(fp, "<%CLASSNAME%Parameters>\n") == EOF )
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




