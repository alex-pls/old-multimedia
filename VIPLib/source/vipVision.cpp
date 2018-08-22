/** @file vipVision.cpp
 *
 * File containing methods for the 'vipVision' class.
 * The header for this class can be found in vipVision.h, check that file
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



#include "vipVision.h"


/**
 * @brief Default constructor call vipInput constructor which setup frame rate,
 *        initialize description arrays and set default name (should be updated).
 *
 * @param fps Frame per second value, default is 0, the max input+processing rate.
 */
vipVision::vipVision()
 {
	alertCall = NULL;
	alertCallArgument = NULL;

	setName("Abstract Motion Detector");
	setDescription("Abstract Class");
	setVersion(0.0);
 }


/**
 * @brief Destructor currenly clear only filters description strings.
 */
vipVision::~vipVision()
 {


 }


void vipVision::doAlert()
 {
  if (alertCall != NULL)
   alertCall(alertCallArgument);

 }


int vipVision::getDifference(vipFrameYUV420& diff_img, vipFrameYUV420& source_img, vipFrameYUV420& second_img)
 {
	INFO("")

	unsigned char* diff_ptr = diff_img.data;
	unsigned char* source_ptr = source_img.data;
	unsigned char* second_ptr = second_img.data;

	for (unsigned int i=0; i<source_img.height*source_img.width*3; i++, diff_ptr++, source_ptr++, second_ptr++)
	 {
                *diff_ptr = *source_ptr - *second_ptr;
	 }

	return VIPRET_OK;
 }

int vipVision::getDifference(vipFrameRGB24& diff_img, vipFrameRGB24& source_img, vipFrameRGB24& second_img)
 {
	INFO("")

	unsigned char* diff_ptr = diff_img.data[0];
	unsigned char* source_ptr = source_img.data[0];
	unsigned char* second_ptr = second_img.data[0];

	for (unsigned int i=0; i<source_img.height*source_img.width*3; i++, diff_ptr++, source_ptr++, second_ptr++)
	 {
                *diff_ptr = *source_ptr - *second_ptr;
	 }

	return VIPRET_OK;
 }


template<class T, class S, class J>
static int getDifference(vipFrameT<T>& diff_img, vipFrameT<S>& source_img, vipFrameT<J>& second_img)
 {
	INFO("")

	T* diff_ptr = diff_img.data[0];
	S* source_ptr = source_img.data[0];
	J* second_ptr = second_img.data[0];

	for (unsigned int i=0; i<source_img.height*source_img.width*source_img.channelCount; i++, diff_ptr++, source_ptr++, second_ptr++)
	 {
                *diff_ptr = (J)( *source_ptr - *second_ptr );
	 }

	return VIPRET_OK;
 };


int vipVision::getDifference(vipFrameT<unsigned char>& diff_img, vipFrameT<unsigned char>& source_img, vipFrameT<unsigned char>& second_img)
 {
	INFO("")

	unsigned char* diff_ptr = diff_img.data;
	unsigned char* source_ptr = source_img.data;
	unsigned char* second_ptr = second_img.data;

	for (unsigned int i=0; i<source_img.height*source_img.width; i++, diff_ptr++, source_ptr++, second_ptr++)
	 {
                *diff_ptr = *source_ptr - *second_ptr;
	 }

	return VIPRET_OK;
 }

int vipVision::getDifference(vipFrameT<int>& diff_img, vipFrameT<int>& source_img, vipFrameT<int>& second_img)
 {
	INFO("")

	int* diff_ptr = diff_img.data;
	int* source_ptr = source_img.data;
	int* second_ptr = second_img.data;

	for (unsigned int i=0; i<source_img.height*source_img.width; i++, diff_ptr++, source_ptr++, second_ptr++)
	 {
                *diff_ptr = *source_ptr - *second_ptr;
	 }

	return VIPRET_OK;
 }

int vipVision::getDifference(vipFrameT<float>& diff_img, vipFrameT<float>& source_img, vipFrameT<float>& second_img)
 {
	INFO("")

	float* diff_ptr = diff_img.data;
	float* source_ptr = source_img.data;
	float* second_ptr = second_img.data;

	for (unsigned int i=0; i<source_img.height*source_img.width; i++, diff_ptr++, source_ptr++, second_ptr++)
	 {
                *diff_ptr = *source_ptr - *second_ptr;
	 }

	return VIPRET_OK;
 }




void vipVisionParameters::setDoEval(bool value)
 {
 	doEval = value;
 }

void vipVisionParameters::setDoAlert(bool value)
 {
 	doAlert = value;
 }


int vipVisionParameters::saveToXML(const char* filename)
 {
	FILE *fp;
	int ret = VIPRET_OK;

	if ( (fp = fopen(filename, "w")) == NULL )
		return VIPRET_PARAM_ERR;

	if( fprintf(fp, "<?xml version=\"1.0\" ?>\n\n") == EOF )
	 {
		fclose(fp);
		return VIPRET_INTERNAL_ERR;
	 }

	ret = saveToStreamXML(fp);

	fclose(fp);

	return ret;

 }


int vipVisionParameters::loadFromXML(const char* filename)
 {
    FILE *fp;
	int ret = VIPRET_OK;

    if ( (fp=fopen(filename,"r")) == NULL )
    	return VIPRET_PARAM_ERR;

    float xmlversion = 0;

    fscanf(fp, "<?xml version=\"%f\" ?>\n\n", &xmlversion);

    if (xmlversion == 0)
    	throw "Incompatible XML file format";

	ret = loadFromStreamXML(fp);

	// closing tags reading is omitted

    fclose(fp);

    return ret;
 }


