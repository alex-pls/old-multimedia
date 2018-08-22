/** @file vipInputSample.cpp
 *
 * File containing methods for the 'vipInputSample' class.
 * The header for this class can be found in vipInputSample.h, check that file
 * for class description.
 *
 *
 ****************************************************************************
 *  Class based on Package Studio template: vipInputTemplate version 0.9.12
 ****************************************************************************
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.science.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DIT - University of Trento
 *
 ****************************************************************************/



#include "vipInputSample.h"

//include specific drivers header here


/**
 * @brief  Default constructor, frame rate
 *         is managed by vipInput class.
 *
 * @param[in] fps frame rate, default is 0: max possible
 */
vipInputSample::vipInputSample(float fps) : vipInput(fps)
 {
	INFO("vipInputSample::vipInputSample(float fps) : vipInput(fps) [CONTRUCTOR]")


	reset();

 }


/**
 * @brief  Default destructor, disconnect device and delete buffer.
 */
vipInputSample::~vipInputSample()
 {

 }



/**
 * @brief  Reset variables.
 *
 * @return VIPRET_OK
 */
VIPRESULT vipInputSample::reset()
 {

	bgRGB[0] = VIPPFG_DEF_COLOR_R;
	bgRGB[1] = VIPPFG_DEF_COLOR_G;
	bgRGB[2] = VIPPFG_DEF_COLOR_B;


	return VIPRET_OK;
 }



/**
 * @brief  Get the state of current data source.
 *
 * @return true is there are no more frames to load, false else.
 */
bool EoF()
 {
	 return false;
 }




/**
 * @brief  Create/capture a new frame with current settings.
 *
 * @param[out] img VIPLib Cache Frame to store data.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid.
 *
 * @note   Ouput operator (>>) call directly this function.
 * @see    operator >> (vipFrameYUV420&)
 */
VIPRESULT vipInputSample::extractTo(vipFrameYUV420& img)
 {
	INFO("int vipInputSample::extractTo(vipFrameYUV420& img) [pushing data]")

	if ( &img == NULL )
		return VIPRET_PARAM_ERR;


//TODO memcpy instead

	for (unsigned int i = 0; i < img.height * img.width; i++)
		img.data[i] = bgRGB;


	return VIPRET_OK;
 }



/**
 * @brief  Create/capture a new frame with current settings.
 *
 * @param[out] img VIPLib Cache24 Frame to store data.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid.
 *
 * @note   Ouput operator (>>) call directly this function.
 * @see    operator >> (vipFrameRGB24&)
 */
VIPRESULT vipInputSample::extractTo(vipFrameRGB24& img)
 {
	INFO("int vipInputSample::extractTo(vipFrameRGB24& img) [pushing data]")

	if ( &img == NULL )
		return VIPRET_PARAM_ERR;


//TODO memcpy instead

	PixelRGB24 bgRGB24((unsigned char)bgRGB[0], (unsigned char)bgRGB[1], (unsigned char)bgRGB[2] );

	for (unsigned int i = 0; i < img.height * img.width; i++)
		img.data[i] = bgRGB24;


	return VIPRET_OK;
 }



/**
 * @brief  Create/capture a new frame with current settings.
 *
 * @param[out] img Greyscale VIPLib Frame to store data.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid.
 *
 * @note   Ouput operator (>>) call directly this function.
 * @see    operator >> (vipFrameT<unsigned char>&)
 */
VIPRESULT vipInputSample::extractTo(vipFrameT<unsigned char>& img)
 {
	INFO("int vipInputSample::extractTo(vipFrameT<unsigned char>& img) [pushing data]")

	if ( &img == NULL )
		return VIPRET_PARAM_ERR;

	return VIPRET_NOT_IMPLEMENTED;
 }



