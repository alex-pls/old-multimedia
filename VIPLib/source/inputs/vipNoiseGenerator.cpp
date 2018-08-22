/** @file vipNoiseGenerator.cpp
 *
 * File containing methods for the 'vipNoiseGenerator' class.
 * The header for this class can be found in vipNoiseGenerator.h,
 * check that file for class description.
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


#include "vipNoiseGenerator.h"

#include <stdlib.h>	// rand()



#pragma warning(disable:4065) // warning C4065 @ line 84: switch statement contains 'default' but no 'case' labels


/**
 * @brief  Default constructor, frame rate
 *         is managed by vipInput class.
 *
 * @param[in] fps frame rate, default is 0: max possible
 */
vipNoiseGenerator::vipNoiseGenerator(float fps) : vipInput(fps)
 {
	INFO("vipNoiseGenerator::vipNoiseGenerator(float fps) : vipInput(fps) [CONTRUCTOR]")

	reset();
 }

/**
 * @brief  Default constructor initialize background, frame rate
 *         is managed by vipInput class.
 *
 * @param[in] runm current runmode.
 * @param[in] fps frame rate, default is 0: max possible
 */
vipNoiseGenerator::vipNoiseGenerator(RUNMODE runm, float fps) : vipInput(fps)
 {
	DEBUGMSG("vipNoiseGenerator::vipNoiseGenerator(RUNMODE runm, float fps) : vipInput(fps) [CONTRUCTOR]", runm)

	reset();

	v_runmode = runm;
 }

/**
 * @brief  Reset variables and noise source.
 *
 * @return VIPRET_OK
 */
VIPRESULT vipNoiseGenerator::reset()
 {
	v_runmode = 0;
	normalized = false;
	normalize_value = 255;
	spread = 1.;

	resetNoiseSource();

	return VIPRET_OK;
 }


/**
 * @brief  Reset current random generator source.
 */
void vipNoiseGenerator::resetNoiseSource()
 {
	DEBUGMSG("void vipNoiseGenerator::resetNoiseSource()", v_runmode)

	switch(v_runmode) {

		default:
				// initialise random sunber generator
				time_t t;
				srand((unsigned) time(&t));
				break;

	 }

 }

/**
 * @brief  Create a random RGB pixel
 *
 * @return VIPLibb RGB pixel [int rand, int rand, int rand].
 */
PixelRGB96 vipNoiseGenerator::getRandomPixelRGB96()
 {
        PixelRGB96 ret;
        ret[0] = rand();
        ret[1] = rand();
        ret[2] = rand();
        return ret;
 }


/**
 * @brief  Create a random RGB24 pixel
 *
 * @return VIPLibb RGB24 pixel [unsigned char rand,
 *         unsigned char rand, unsigned char rand].
 */
PixelRGB24 vipNoiseGenerator::getRandomPixelRGB24()
 {
        PixelRGB24 ret;
        ret[0] = (unsigned char)(rand()%255);
        ret[1] = (unsigned char)(rand()%255);
        ret[2] = (unsigned char)(rand()%255);
        return ret;
 }


/**
 * @brief  Create a random HSV pixel
 *
 * @return VIPLibb HSV pixel [int rand, int rand, int rand].
 */
PixelHSV vipNoiseGenerator::getRandomPixelHSV()
 {
        PixelHSV ret;
        ret.hue = rand();
        ret.val = rand()%255;
        ret.sat = rand()%255;
        return ret;
 }

/**
 * @brief  Create a random greyscale pixel
 *
 * @return VIPLibb greyscale pixel [int rand].
 */
PixelGrey vipNoiseGenerator::getRandomPixelGrey()
 {
        PixelGrey ret;
        ret = rand()%255;
        return ret;
 }



/**
 * @brief  Create a new noise frame with current settings.
 *
 * @param[out] img VIPLibb Cache Frame to store data.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid.
 *
 * @note   Ouput operator (>>) call directly this function.
 * @see    operator >> (vipFrameYUV420&)
 */
VIPRESULT vipNoiseGenerator::extractTo(vipFrameYUV420& img)
 {
	INFO("VIPRESULT vipNoiseGenerator::extractTo(vipFrameYUV420& img) [pushing data]")

	return VIPRET_NOT_IMPLEMENTED;
 }


/**
 * @brief  Create a new noise frame with current settings.
 *
 * @param[out] img VIPLibb Cache24 Frame to store data.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid.
 *
 * @note   Ouput operator (>>) call directly this function.
 * @see    operator >> (vipFrameRGB24&)
 */
VIPRESULT vipNoiseGenerator::extractTo(vipFrameRGB24& img)
 {
	INFO("VIPRESULT vipNoiseGenerator::extractTo(vipFrameRGB24& img) [pushing data]")

	unsigned int size = img.width * img.height;
	unsigned int perc = (unsigned int)( (float)(size) * spread);
	unsigned int noiseco;

	if ( normalized )
	 {
		for ( unsigned int i = 0; i < perc; i++ )
		 {
			noiseco = rand()*rand() % size;
			img.data[noiseco][0] = (unsigned char)( rand() % normalize_value);
			noiseco = rand()*rand() % size;
			img.data[noiseco][1] = (unsigned char)( rand() % normalize_value);
			noiseco = rand()*rand() % size;
			img.data[noiseco][2] = (unsigned char)( rand() % normalize_value);
		 }
	 }
	else
	 {
		for ( unsigned int i = 0; i < perc; i++ )
		 {
			noiseco = rand()*rand() % size;
			img.data[noiseco][0] = (unsigned char)(rand()%255);
			noiseco = rand()*rand() % size;
			img.data[noiseco][1] = (unsigned char)(rand()%255);
			noiseco = rand()*rand() % size;
			img.data[noiseco][2] = (unsigned char)(rand()%255);
		 }
	 }

	return VIPRET_OK;
 }


/**
 * @brief  Create a new noise frame with current settings.
 *
 * @param[out] img Greyscale VIPLibb Frame to store data.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid.
 *
 * @note   Ouput operator (>>) call directly this function.
 * @see    operator >> (vipFrameT&)
 */
VIPRESULT vipNoiseGenerator::extractTo(vipFrameT<unsigned char>& img)
 {
	INFO("VIPRESULT vipNoiseGenerator::extractTo(vipFrameT& img) [pushing data]")

	return VIPRET_NOT_IMPLEMENTED;
 }
