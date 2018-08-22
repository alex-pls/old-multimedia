/**
 *  @class   vipWindowQT
 *
 *  @brief   Class for displaying VIPLibb frames on a Linux Desktop Env.
 *           Require Trolltech QT library (included in most distribution)
 *           Inherit QWidget, so may be used in any QAplication without limitations.
 *           May be used to display video, sample applications played at 34 fps.
 *
 *  @bug     Currenlty does a single pixel routine.
 *  @warning Require a main QApplication.
 *  @todo
 *  @note    vipWindowQT must be initialized after QApplication.
 *
 *  @see     vipOutput
 *  @example ../../tests/test_vipWindowQT.cpp
 *  @example ../../tests/app_vipLinuxMOVPlayer.cpp
 *  @example ../../tests/app_vipLinuxMPEGPlayer.cpp
 *  @example ../../tests/app_vipVideo4LinuxPlayer.cpp
 *
 *  @version 1.0.2
 *  @date    15/09/2005
 *  @author  Alessandro Polo
 *
 *  @note    apt-get install libqt4-gui libqt4-dev
 *
 ****************************************************************************
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.disi.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DISI - University of Trento
 *
 ****************************************************************************/



#ifndef __VIPLIB_VIPWINDOWQT_H__
 #define __VIPLIB_VIPWINDOWQT_H__

 #include "../vipDefs.h"
 #include "../vipOutput.h"

 #include "../vipFrameYUV420.h"
 #include "../vipFrameRGB24.h"
 #include "../vipFrameT.h"


 //Trolltech QT headers
 #include <QtGui/qapplication.h>
 #include <QtGui/qpainter.h>
 #include <QtGui/qwidget.h>

/**
 * @brief  Deafult window's width.
 */
#define VIPWQT_DEF_WIDTH	320
/**
 * @brief  Deafult window's height.
 */
#define VIPWQT_DEF_HEIGHT	240


class vipWindowQT :		public vipOutput,
 						public QWidget
 {

	protected:


		vipFrameRGB24* imgCurr;

		/**
		 * @brief  QPainter instance, main drawing object.
		 */
		QPainter* dataCanvas;

		/**
		 * @brief  Paint Event callback functions for future extensions.
		 * @param[out] event Event raised.
		 */
		void vipWindowQT::paintEvent(QPaintEvent *);

	public:


		/**
		 * @brief  Default constructor initializes variables.
		 */
		vipWindowQT();

		/**
		 * @brief  Default constructor initializes variables.
		 *
		 * @param[in] width Window's width in pixels.
		 * @param[in] height Window's height in pixels.
		 */
		vipWindowQT(unsigned int width, unsigned int height);

		/**
		 * @brief  Set current canvas' height.
		 *
		 * @return height in pixel.
		 */
		VIPRESULT setHeight(unsigned int value);

		/**
		 * @brief  Set current canvas' width.
		 *
		 * @return width in pixel.
		 */
		VIPRESULT setWidth(unsigned int value);


		/**
		 * @brief  Currently not used.
		 * @return VIPRET_NOT_IMPLEMENTED
		 */
		VIPRESULT run() { return VIPRET_NOT_IMPLEMENTED; };


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
		VIPRESULT importFrom(vipFrameYUV420& img);

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
		VIPRESULT importFrom(vipFrameRGB24& img);

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
		VIPRESULT importFrom(vipFrameT<unsigned char>& img);


};

#endif //__VIPLIB_VIPWINDOWQT_H__
