/** @file vipPlainFrameGenerator.cpp
 *
 * File containing methods for the 'vipPlainFrameGenerator' class.
 * The header for this class can be found in vipPlainFrameGenerator.h,
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



#include "vipPlainFrameGenerator.h"

/**
 * @brief  Default constructor, frame rate
 *         is managed by vipInput class.
 *
 * @param[in] fps frame rate, default is 0: max possible
 */
vipPlainFrameGenerator::vipPlainFrameGenerator(float fps) : vipInput(fps)
 {
	INFO("vipPlainFrameGenerator::vipPlainFrameGenerator(float fps) : vipInput(fps) [CONTRUCTOR]")
	reset();
 }

/**
 * @brief  Default constructor initialize background, frame rate
 *         is managed by vipInput class.
 *
 * @param[in] background RGB pixel
 * @param[in] fps frame rate, default is 0: max possible
 */
vipPlainFrameGenerator::vipPlainFrameGenerator(PixelRGB96& background, float fps) : vipInput(fps)
 {
	DEBUGMSG("vipPlainFrameGenerator::vipPlainFrameGenerator(PixelRGB96& background, float fps) : vipInput(fps) [CONTRUCTOR]", background)
	reset();
//	bgRGB  = background;
 }

/**
 * @brief  Default constructor initialize background, frame rate
 *         is managed by vipInput class.
 *
 * @param[in] background RGB pixel
 * @param[in] fps frame rate, default is 0: max possible
 */
vipPlainFrameGenerator::vipPlainFrameGenerator(PixelGrey& background, float fps) : vipInput(fps)
 {
	DEBUGMSG("vipPlainFrameGenerator::vipPlainFrameGenerator(PixelGrey& background, float fps) : vipInput(fps) [CONTRUCTOR]", background)
	reset();
//	bgGrey   = background;
 }


vipPlainFrameGenerator::~vipPlainFrameGenerator()
 {
	releaseBuffers();
 }



VIPRESULT vipPlainFrameGenerator::reset()
 {
	releaseBuffers();

//	bgRGB[0] = VETPFG_DEF_COLOR_R;
//	bgRGB[1] = VETPFG_DEF_COLOR_G;
//	bgRGB[2] = VETPFG_DEF_COLOR_B;
//	bgGrey = VETPFG_DEF_COLOR_GREY;

	return VIPRET_OK;
 }



/**
 * @brief Close and free all buffers, then they are set to NULL.
 */
void vipPlainFrameGenerator::releaseBuffers()
 {
	if (bufferYUV != NULL)
		delete bufferYUV;

	if (bufferRGB != NULL)
		delete bufferRGB;

	if (bufferTuC != NULL)
		delete bufferTuC;

	bufferYUV = NULL;
	bufferRGB = NULL;
	bufferTuC = NULL;

 };


/**
 * @brief  Update and set current buffer (vipFrameYUV420) to new size.
 * @param[in] width new buffer's width.
 * @param[in] height new buffer's height.
 */
void vipPlainFrameGenerator::useBufferYUV(unsigned int width, unsigned int height)
 {
	if ( bufferYUV == NULL )
		bufferYUV = new vipFrameYUV420(width, height);
	else if ( bufferYUV->width != width || bufferYUV->height != height )
		bufferYUV->reAllocCanvas(width, height);

	if ( bufferRGB != NULL )
	 {
		delete bufferRGB;
		bufferRGB = NULL;
	 }
	if ( bufferTuC != NULL )
	 {
		delete bufferTuC;
		bufferTuC = NULL;
	 }
 };

/**
 * @brief  Update and set current buffer (vipFrameRGB24) to new size.
 * @param[in] width new buffer's width.
 * @param[in] height new buffer's height.
 */
void vipPlainFrameGenerator::useBufferRGB(unsigned int width, unsigned int height)
 {
	if ( bufferRGB == NULL )
		bufferRGB = new vipFrameRGB24(width, height);
	else if ( bufferRGB->width != width || bufferRGB->height != height )
		bufferRGB->reAllocCanvas(width, height);

	if ( bufferYUV != NULL )
	 {
		delete bufferYUV;
		bufferYUV = NULL;
	 }
	if ( bufferTuC != NULL )
	 {
		delete bufferTuC;
		bufferTuC = NULL;
	 }
 };

/**
 * @brief  Update and set current buffer (vipFrameT<uchar>) to new size.
 * @param[in] width new buffer's width.
 * @param[in] height new buffer's height.
 */
void vipPlainFrameGenerator::useBufferTuC(unsigned int width, unsigned int height, vipFrame::VIPFRAME_PROFILE profile)
 {
	if ( bufferTuC == NULL )
		bufferTuC = new vipFrameT<unsigned char>(width, height, profile);
	else if ( bufferTuC->width != width || bufferTuC->height != height )
		bufferTuC->reAllocCanvas(width, height);

	if ( bufferYUV != NULL )
	 {
		delete bufferYUV;
		bufferYUV = NULL;
	 }
	if ( bufferRGB != NULL )
	 {
		delete bufferRGB;
		bufferRGB = NULL;
	 }
 };


/**
 * @brief  Set current canvas' height.
 *
 * @return height in pixel.
 */
VIPRESULT vipPlainFrameGenerator::setHeight(unsigned int value)
 {
	if (bufferYUV != NULL)
	 {
		bufferYUV->reAllocCanvas(bufferYUV->width, value);
		return VIPRET_OK;
	 }
	else if (bufferRGB != NULL)
	 {
		bufferRGB->reAllocCanvas(bufferRGB->width, value);
		return VIPRET_OK;
	 }
	else if (bufferTuC != NULL)
	 {
		bufferTuC->reAllocCanvas(bufferTuC->width, value);
		return VIPRET_OK;
	 }

	return VIPRET_NOT_IMPLEMENTED;
 };

/**
 * @brief  Set current canvas' width.
 *
 * @return width in pixel.
 */
VIPRESULT vipPlainFrameGenerator::setWidth(unsigned int value)
 {
	if (bufferYUV != NULL)
	 {
		bufferYUV->reAllocCanvas(value, bufferYUV->height);
		return VIPRET_OK;
	 }
	else if (bufferRGB != NULL)
	 {
		bufferRGB->reAllocCanvas(value, bufferRGB->height);
		return VIPRET_OK;
	 }
	else if (bufferTuC != NULL)
	 {
		bufferTuC->reAllocCanvas(value, bufferTuC->height);
		return VIPRET_OK;
	 }

	return VIPRET_NOT_IMPLEMENTED;
 };

/**
 * @brief  Read current canvas's width.
 *
 * @return Width in pixel.
 */
unsigned int vipPlainFrameGenerator::getWidth() const
 {
	if (bufferYUV != NULL)
		return bufferYUV->width;

	else if (bufferRGB != NULL)
		return bufferRGB->width;

	else if (bufferTuC != NULL)
		return bufferTuC->width;

	return 0;
 };

/**
 * @brief  Read current canvas's height.
 *
 * @return Height in pixel.
 */
unsigned int vipPlainFrameGenerator::getHeight() const
 {
	if (bufferYUV != NULL)
		return bufferYUV->height;

	else if (bufferRGB != NULL)
		return bufferRGB->height;

	else if (bufferTuC != NULL)
		return bufferTuC->height;

	return 0;
 };






/**
 * @brief  Clear the frame with background pixel.
 *
 * @param[out] img VIPLibb Cache Frame to store data.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid.
 *
 * @note   Ouput operator (>>) call directly this function.
 * @see    operator >> (vipFrameYUV420&)
 */
VIPRESULT vipPlainFrameGenerator::extractTo(vipFrameYUV420& img)
 {
	INFO("VIPRESULT vipPlainFrameGenerator::extractTo(vipFrameYUV420& img) [pushing data]")

	if ( !isBufferYUV() )
		return VIPRET_ILLEGAL_USE;

	img = *bufferYUV;

	return VIPRET_OK;
 };


/**
 * @brief  Clear the frame with background pixel.
 *
 * @param[out] img VIPLibb Cache24 Frame to store data.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid.
 *
 * @note   Ouput operator (>>) call directly this function.
 * @see    operator >> (vipFrameRGB24&)
 */
VIPRESULT vipPlainFrameGenerator::extractTo(vipFrameRGB24& img)
 {
	INFO("VIPRESULT vipPlainFrameGenerator::extractTo(vipFrameRGB24& img) [pushing data]")

	if ( !isBufferRGB() )
		return VIPRET_ILLEGAL_USE;

	img = *bufferRGB;

	return VIPRET_OK;
 };


/**
 * @brief  Clear the frame with background pixel.
 *
 * @param[out] img Greyscale VIPLibb Frame to store data.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid.
 *
 * @note   Ouput operator (>>) call directly this function.
 * @see    operator >> (vipFrameT&)
 */
VIPRESULT vipPlainFrameGenerator::extractTo(vipFrameT<unsigned char>& img)
 {
	INFO("VIPRESULT vipPlainFrameGenerator::extractTo(vipFrameT<unsigned char>& img) [pushing data]")

	if ( !isBufferTuC() )
		return VIPRET_ILLEGAL_USE;

	img = *bufferTuC;

	return VIPRET_OK;
 };



