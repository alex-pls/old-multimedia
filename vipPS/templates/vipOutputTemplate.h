/** @file    %FILENAME%.h
 *  @class   %CLASSNAME%
 *
 *  @brief
 *
 *
 *
 *
 *  @bug
 *  @warning
 *  @todo
 *
 *  @see     vipOutput
 *
 *  @version %VERSION%
 *  @date    %TODAY%
 *  @author  %AUTHOR%
 *
 ****************************************************************************
 *  Class based on Package Studio template: vipOutputTemplate version 0.9.12
 ****************************************************************************
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.science.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DIT - University of Trento
 *
 ****************************************************************************/



#ifndef __VIPLIB_%CLASSDEFINE%_H__
 #define __VIPLIB_%CLASSDEFINE%_H__


//respect ./source/motion or ./packages/filters directory
 #include "%SOURCEDIR%vipDefs.h"
 #include "%SOURCEDIR%vipOutput.h"
 #include "%SOURCEDIR%vipFrameYUV420.h"
 #include "%SOURCEDIR%vipFrameRGB24.h"
 #include "%SOURCEDIR%vipFrameT.h"
%EFI_START%
 #include "%SOURCEDIR%vipFrameRGB96.h"
%EFI_END%

%EFI_START%
 %DOCVAR%/**
  * @brief  Deafult window's width.
  */
 #define %CLASSDEFINE%_DEF_WIDTH	320
 %DOCVAR%/**
  * @brief  Deafult window's height.
  */
 #define %CLASSDEFINE%_DEF_HEIGHT	240
%EFI_END%


class %CLASSNAME% :  public vipOutput
 {

	protected:

%EFI_START%
		%DOCVAR%/**
		 * @brief  Canvas' width.
		 */
		unsigned int width;
		%DOCVAR%/**
		 * @brief  Canvas' height.
		 */
		unsigned int height;

		%DOCVAR%/**
		 * @brief  Milliseconds to wait after frame (re)drawing.
		 */
		long v_sleeptime;

		%DOCVAR%/**
		 * @brief  Initialize canvas.
		 * @return VIPRET_OK
		 */
		VIPRESULT init();
%EFI_END%


	public:

%VFI_START%
		%DOCFUN%/**
		 * @brief  Default constructor initializes variables and canvas.
		 *
		 */
		%CLASSNAME%();
%VFI_END%

%EFI_START%
		%DOCFUN%/**
		 * @brief  Default constructor initializes variables.
		 *
		 * @param[in] width Canvas' width.
		 * @param[in] height Canvas' height.
		 *
		 */
		%CLASSNAME%(unsigned int width, unsigned int height);
%EFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Default destructor, wait for pending events and flush.
		 */
		~%CLASSNAME%();
%VFI_END%


%EFI_START%
		%DOCFUN%/**
		 * @brief  Show canvas.
		 *
		 * @return VIPRET_OK
		 */
		VIPRESULT show();
%EFI_END%

%EFI_START%
		%DOCFUN%/**
		 * @brief  Hide canvas.
		 *
		 * @return VIPRET_OK
		 */
		VIPRESULT hide();
%EFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Set display frame rate (elaboration time is not subtracted).
		 *
		 * @param[in] frames per second (default is 0, no sleep)
		 *
		 * @return VIPRET_PARAM_ERR if fps is lower than 0, VIPRET_OK else.
		 */
		int setFrameRate(float fps = 0);
%VFI_END%


%VFI_START%
		%DOCFUN%/**
		 * @brief  Set current canvas' height.
		 *
		 * @return height in pixel.
		 */
		VIPRESULT setHeight(unsigned int value)
		 {
%EFI_START%
			height = value;
%EFI_END%
			return VIPRET_NOT_IMPLEMENTED;
		 };
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Set current canvas' width.
		 *
		 * @return width in pixel.
		 */
		VIPRESULT setWidth(unsigned int value)
		 {
%EFI_START%
			width = value;
%EFI_END%
			 return VIPRET_NOT_IMPLEMENTED;
		 };
%VFI_END%


%EFI_START%
		%DOCFUN%/**
		 * @brief  Get current canvas' width.
		 *
		 * @return width in pixel.
		 */
		unsigned int getWidth() const { return width; };
%EFI_END%

%EFI_START%
		%DOCFUN%/**
		 * @brief  Get current canvas' height.
		 *
		 * @return height in pixel.
		 */
		unsigned int getHeight() const { return height; };
%EFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Display frame, conversion to vipFrameRGB24 and data-copy routine.
		 *
		 * @param[in] img VIPLib Cache Frame to be displayed.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
		 *
		 * @note   Input operator (<<) call directly this function.
		 * @see    operator << (vipFrameYUV420&)
		 */
		int importFrom(vipFrameYUV420& img);
%VFI_END%


%VFI_START%
		%DOCFUN%/**
		 * @brief  Display frame, data-copy routine. (optimized)
		 *
		 * @param[in] img VIPLib Cache24 Frame to be displayed.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
		 *
		 * @note   Input operator (<<) call directly this function.
		 * @see    operator << (vipFrameRGB24&)
		 */
		VIPRESULT importFrom(vipFrameRGB24& img);
%VFI_END%


%EFI_START%
		%DOCFUN%/**
		 * @brief  Display frame, conversion to vipFrameRGB24
		 *         and single channel data-copy routine.
		 *
		 * @param[in] img VIPLib RGB Frame to be displayed.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
		 *
		 * @note   Input operator (<<) call directly this function.
		 * @see    operator << (vipFrameRGB96&)
		 */
		VIPRESULT importFrom(vipFrameRGB96& img);
%EFI_END%


%VFI_START%
		%DOCFUN%/**
		 * @brief  Display frame, conversion to vipFrameRGB24
		 *         and single channel data-copy routine.
		 *
		 * @param[in] img VIPLib Grey Frame to be displayed.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
		 *
		 * @note   Input operator (<<) call directly this function.
		 * @see    operator << (vipFrameT<unsigned char>&)
		 */
		VIPRESULT importFrom(vipFrameT<unsigned char>& img);
%VFI_END%


%EFI_START%
		%DOCFUN%/**
		 * @brief  Input operator, import standard VIPLib frame formats,
		 *         current implementation calls directly importFrom() method.
		 *
		 * @param[in] img VIPLib Cache Frame to be displayed.
		 *
		 * @note   Overloaded because we add vipFrameRGB support and all
		 *         operators need to (re)defined.
		 * @see    importFrom(vipFrameYUV420&)
		 */
		void operator << (vipFrameYUV420& img) { importFrom(img); };

		%DOCFUN%/**
		 * @brief  Input operator, import standard VIPLib frame formats,
		 *         current implementation calls directly importFrom() method.
		 *
		 * @param[in] img VIPLib Cache24 Frame to be displayed.
		 *
		 * @note   Overloaded because we add vipFrameRGB support and all
		 *         operators need to (re)defined.
		 * @see    importFrom(vipFrameRGB24&)
		 */
		void operator << (vipFrameRGB24& img) { importFrom(img); };

		%DOCFUN%/**
		 * @brief  Input operator, import standard VIPLib frame formats,
		 *         current implementation calls directly importFrom() method.
		 *
		 * @param[in] img VIPLib RGB Frame to be displayed.
		 *
		 * @note   Overloaded because we add vipFrameRGB96 support and all
		 *         operators need to (re)defined.
		 * @see    importFrom(vipFrameRGB96&)
		 */
		void operator << (vipFrameRGB96& img) { importFrom(img); };

		%DOCFUN%/**
		 * @brief  Input operator, import standard VIPLib frame formats,
		 *         current implementation calls directly importFrom() method.
		 *
		 * @param[in] img VIPLib Grey Frame to be displayed.
		 *
		 * @note   Overloaded because we add vipFrameRGB support and all
		 *         operators need to (re)defined.
		 * @see    importFrom(vipFrameT<unsigned char>&)
		 */
		void operator << (vipFrameT<unsigned char>& img) { importFrom(img); };
%EFI_END%

};

#endif //__VIPLIB_%CLASSDEFINE%_H__
