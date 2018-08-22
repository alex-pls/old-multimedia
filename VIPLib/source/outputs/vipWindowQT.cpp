/** @file vipWindowQT.cpp
 *
 * File containing methods for the 'vipWindowQT' class.
 * The header for this class can be found in vipWindowQT.h, check that file
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



#include "vipWindowQT.h"



/**
 * @brief  Default constructor initializes variables.
 */
vipWindowQT::vipWindowQT() : vipOutput()
 {
	INFO("vipWindowQT::vipWindowQT() : vipOutput() [CONTRUCTOR]")
	
	imgCurr = NULL;

	resize(VIPWQT_DEF_WIDTH,VIPWQT_DEF_HEIGHT);
 }


/**
 * @brief  Default constructor initializes variables.
 *
 * @param[in] width Window's width in pixels.
 * @param[in] height Window's height in pixels.
 */
vipWindowQT::vipWindowQT(unsigned int width, unsigned int height) : vipOutput()
 {
	INFO("vipWindowQT::vipWindowQT() : vipOutput() [CONTRUCTOR]")

	resize(width,height);
 }

/**
 * @brief  Set current canvas' height.
 *
 * @return height in pixel.
 */
VIPRESULT vipWindowQT::setHeight(unsigned int value)
 {
//	resize(width, value);

	return VIPRET_OK;
 }

/**
 * @brief  Set current canvas' width.
 *
 * @return width in pixel.
 */
VIPRESULT vipWindowQT::setWidth(unsigned int value)
 {
//	resize( value, height);

	return VIPRET_OK;
 }


/**
 * @brief  Display frame, single pixel routine.
 *
 * @param[in] img VIPLibb Cache Frame to be displayed.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 *
 * @note   Input operator (<<) call directly this function.
 * @see    operator << (vipFrameYUV420&)
 */
VIPRESULT vipWindowQT::importFrom(vipFrameYUV420& img)
 {
	INFO("int vipWindowQT::importFrom(vipFrameYUV420& img) [reading data]")

	return VIPRET_NOT_IMPLEMENTED;
 }

/**
 * @brief  Display frame, single pixel routine.
 *
 * @param[in] img VIPLibb Cache24 Frame to be displayed.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 *
 * @note   Input operator (<<) call directly this function.
 * @see    operator << (vipFrameRGB24&)
 */
VIPRESULT vipWindowQT::importFrom(vipFrameRGB24& img)
 {
	INFO("int vipWindowQT::importFrom(vipFrameRGB24& img) [reading data]")




	imgCurr = &img;

	repaint();

	return VIPRET_OK;
 }


/**
 * @brief  Display frame, single pixel routine.
 *
 * @param[in] img VIPLibb Grey Frame to be displayed.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 *
 * @note   Input operator (<<) call directly this function.
 * @see    operator << (vipFrameT&)
 */
VIPRESULT vipWindowQT::importFrom(vipFrameT<unsigned char>& img)
 {
	INFO("int vipWindowQT::importFrom(vipFrameT& img) [reading data]")

	return VIPRET_NOT_IMPLEMENTED;
 }


void vipWindowQT::paintEvent(QPaintEvent *)
 {
	INFO("VIPRESULT vipWindowQT::paintEvent(QPaintEvent *)")

	if ( imgCurr == NULL)
		return;

	dataCanvas = new QPainter;

	if (dataCanvas == NULL)
		return;

	dataCanvas->begin(this);

	int w = imgCurr->width;
	int h = imgCurr->height;

	for (int y=0; y < h; y++)//lame
		for (int x=0; x < w; x++)
		 {
			dataCanvas->setPen( QColor( (int)imgCurr->data[y*w+x][0], (int)imgCurr->data[y*w+x][1], (int)imgCurr->data[y*w+x][2] ));
			dataCanvas->drawPoint(x,y);
		 }
	dataCanvas->end();
	return;
 }



