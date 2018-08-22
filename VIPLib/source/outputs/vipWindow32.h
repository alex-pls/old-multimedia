/**
 *  @class   vipWindow32
 *
 *  @brief   This class create a Window able to import and display VIPLibb
 *           standard frames (vipFrameYUV420, vipFrameRGB24, vipFrameRGB)
 *           Class doesn't require any external library, uses Windows GDI.
 *
 *  @bug     It's too slow for displaying video
 *  @warning Require a Main Windows Application
 *  @todo
 *
 *  @see     vipOutput
 *  @example ../../tests/test_vipWindow32.cpp
 *  @example ../../tests/app_vipDirectXLamePlayer.cpp
 *
 *  @version 1.0.0
 *  @date    24/08/2005
 *  @author  Alessandro Polo
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



#ifndef __VIPLIB_VIPWINDOW32_H__
 #define __VIPLIB_VIPWINDOW32_H__

 #include "../vipDefs.h"
 #include "../vipOutput.h"

 #include "../vipFrameYUV420.h"
 #include "../vipFrameRGB24.h"
 #include "../vipFrameT.h"

 #include <windows.h>


/**
 * @brief  Deafult window's width.
 */
#define VIPW32_DEF_WIDTH	320
/**
 * @brief  Deafult window's height.
 */
#define VIPW32_DEF_HEIGHT	240


#define VIPW32_DEF_TITLE	TEXT("VIPLibb Preview Window32 0.56\0")
#define VIPW32_DEF_CLSNAME	TEXT("vipWindow32\0")




class vipWindow32 :  public vipOutput
 {

	protected:

		/**
		 * @brief  Parent Application's instance address.
		 */
		HINSTANCE parentHistance;

		/**
		 * @brief  Current window's handle.
		 */
		HWND myHandle;

		/**
		 * @brief  Canvas size and position.
		 */
		RECT myRect;

		/**
		 * @brief  Canvas.
		 */
		HDC hDisplay;


		unsigned int width;
		unsigned int height;

	public:


		/**
		 * @brief  Default constructor initializes variables; if present, set parent
		 *         instance and create window.
		 *
		 * @param[in] hInstance Main window (application) instance handle, required before
		 *                      calling createWindow()
		 */
		vipWindow32(HINSTANCE hInstance = 0);

		/**
		 * @brief  Default destructor, release canvas.
		 */
		~vipWindow32();

		/**
		 * @brief  Get application's handle.
		 *
		 * @return address of application instance.
		 */
		void setParentHistance(HINSTANCE appHinstance) { parentHistance = appHinstance; };

		/**
		 * @brief  Get application's handle.
		 *
		 * @return address of application instance.
		 */
		HINSTANCE getParentHistance() { return parentHistance; };

		/**
		 * @brief  Initialize canvas, parent instance must be valid.
		 *
		 * @param[in] width window's width in pixel
		 * @param[in] height window's height in pixel
		 *
		 * @return VIPRET_ILLEGAL_USE if app handle is not valid,
		 *         VIPRET_INTERNAL_ERR if window cannot be created,
		 *         VIPRET_OK else.
		 *
		 * @note   use setParentHistance() to update application's handle.
		 */
		VIPRESULT createWindow(unsigned int width, unsigned int height);

		/**
		 * @brief  Display some text.
		 *
		 * @return VIPRET_ILLEGAL_USE if app handle is not valid, VIPRET_OK else.
		 */
		VIPRESULT welcomeText();


		/**
		 * @brief  Set window's position (passed to SetWindowPos(..) )
		 *
		 * @param[in] X window's top-left x-axis position in screen.
		 * @param[in] Y window's top-left y-axis position in screen.
		 * @param[in] cx size
		 * @param[in] cy size
		 *
		 * @return false if update has falied, true else.
		 */
		BOOL setWindowPos(int X, int Y, int cx, int cy) { return SetWindowPos(myHandle, HWND_NOTOPMOST, X, Y, cx, cy, SWP_SHOWWINDOW ); };

		/**
		 * @brief  Set window's title. (passed to SetWindowText(..) )
		 *
		 * @param[in] lpString long pointer to null terminated string (window's title)
		 *
		 * @return false if update has falied, true else.
		 */
		BOOL setWindowText(LPCTSTR lpString) { return SetWindowText(myHandle, lpString); };

		/**
		 * @brief  Dump window's handle.
		 *
		 * @return address of window instance.
		 */
		HWND dump_handle() { return myHandle; };

		/**
		 * @brief  Dump canvas' RECT.
		 *
		 * @return Canvas' rectancle (position and dimension)
		 */
		LPRECT dump_WindowRect() { return &myRect; };

		/**
		 * @brief  Dump canvas' handle (DC).
		 *
		 * @return Canvas' handle (where data is displayed)
		 */
		HDC dump_DC() { return hDisplay; };


		/**
		 * @brief  Show the window, state is customizable
		 *
		 * @param[in] default is SW_SHOW, argument is passed to ShowWindow() API.
		 *
		 * @return VIPRET_ILLEGAL_USE if window handle is not valid, VIPRET_OK else.
		 */
		VIPRESULT show(int nCmdShow = SW_SHOW);

		/**
		 * @brief  Hide the window.
		 *
		 * @return VIPRET_ILLEGAL_USE if window handle is not valid, VIPRET_OK else.
		 */
		VIPRESULT hide();

		/**
		 * @brief  Currently not used.
		 * @return VIPRET_NOT_IMPLEMENTED
		 */
		VIPRESULT run() { return VIPRET_NOT_IMPLEMENTED; };

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


		unsigned int getWidth() const { return width; };
		unsigned int getHeight() const { return height; };

		/**
		 * @brief Display frame, single pixel routine.
		 *
		 * @param[in] img VIPLibb Cache Frame to be displayed.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
		 *
		 * @note  Input operator (<<) call directly this function.
		 * @see   operator << (vipFrameYUV420&)
		 */
		VIPRESULT importFrom(vipFrameYUV420& img);

		/**
		 * @brief Display frame, single pixel routine.
		 *
		 * @param[in] img VIPLibb Cache24 Frame to be displayed.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
		 *
		 * @note  Input operator (<<) call directly this function.
		 * @see   operator << (vipFrameRGB24&)
		 */
		VIPRESULT importFrom(vipFrameRGB24& img);

		/**
		 * @brief Display frame, conversion to vipFrameRGB24 and single pixel routine.
		 *
		 * @param[in] img VIPLibb Grey Frame to be displayed.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
		 *
		 * @note  Input operator (<<) call directly this function.
		 * @see   operator << (vipFrameT&)
		 */
		VIPRESULT importFrom(vipFrameT<unsigned char>& img);



};

#endif //__VIPLIB_VIPWINDOW32_H__
