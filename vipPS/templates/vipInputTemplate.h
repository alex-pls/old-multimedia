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
 *  @see     vipInput
 *
 *  @version %VERSION%
 *  @date    %TODAY%
 *  @author  %AUTHOR%
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



#ifndef __VIPLIB_%CLASSDEFINE%_H__
 #define __VIPLIB_%CLASSDEFINE%_H__

//respect ./source/inputs or ./packages/inputs directory
 #include "%SOURCEDIR%vipDefs.h"
 #include "%SOURCEDIR%vipInput.h"

 #include "%SOURCEDIR%vipFrameRGB24.h"
 #include "%SOURCEDIR%vipFrameYUV420.h"
 #include "%SOURCEDIR%vipFrameT.h"

%EFI_START%
 #define VIPPFG_DEF_COLOR_R		0 // |
 #define VIPPFG_DEF_COLOR_G		0 // |>black
 #define VIPPFG_DEF_COLOR_B		0 // |
%EFI_END%


class %CLASSNAME% : public vipInput
 {
	protected:

%EFI_START%
		%DOCVAR%/**
		 * @brief  Background RGB pixel color.
		 */
		PixelRGB24 bgRGB;

		%DOCVAR%/**
		 * @brief  Canvas' width.
		 */
		unsigned int width;
		%DOCVAR%/**
		 * @brief  Canvas' height.
		 */
		unsigned int height;

%EFI_END%


	public:

%VFI_START%
		%DOCFUN%/**
		 * @brief  Default constructor, frame rate
		 *         is managed by vipInput class.
		 *
		 * @param[in] fps frame rate, default is 0: max possible
		 */
		%CLASSNAME%(float fps = 0);
%VFI_END%


%EFI_START%
		%DOCFUN%/**
		 * @brief  Default constructor initialize background, frame rate
		 *         is managed by vipInput class.
		 *
		 * @param[in] background RGB pixel
		 * @param[in] fps frame rate, default is 0: max possible
		 */
		%CLASSNAME%::%CLASSNAME%(PixelRGB24& background, float fps) : vipInput(fps)
		 {
			DEBUGMSG("%CLASSNAME%::%CLASSNAME%(PixelRGB24& background, float fps) : vipInput(fps) [CONTRUCTOR]", background)
			reset();
			bgRGB  = background;
		 }
%EFI_END%


		%DOCFUN%/**
		 * @brief  Default destructor, disconnect device and delete buffer.
		 */
		~%CLASSNAME%();


%VFI_START%
		%DOCFUN%/**
		 * @brief  Reset current background pixels to defaults.
		 */
		VIPRESULT reset();
%VFI_END%


%VFI_START%
		/**
		 * @brief  Get the state of current data source.
		 *
		 * @return true is there are no more frames to load, false else.
		 */
		bool EoF();
%VFI_END%


%VFI_START%
		/**
		 * @brief  Read current image's width.
		 *
		 * @return Width in pixel.
		 */
		unsigned int getWidth() const
		 {
%EFI_START%
			return width;
%EFI_END%
		 };
%VFI_END%

%VFI_START%
		/**
		 * @brief  Read current image's height.
		 *
		 * @return Height in pixel.
		 */
		unsigned int getHeight() const
		 {
%EFI_START%
			return height;
%EFI_END%
		 };
%VFI_END%



%EFI_START%
		%DOCFUN%/**
		 * @brief  Set current RGB background.
		 *
		 * @param[in] background RGB pixel
		 */
		void setFrameColor(PixelRGB24& background) { bgRGB = background; };
%EFI_END%


%VFI_START%
		%DOCFUN%/**
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
		VIPRESULT extractTo(vipFrameYUV420& img);
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Create/capture a new frame with current settings.
		 *
		 * @param[out] img VIPLib Cache Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid.
		 *
		 * @note   Ouput operator (>>) call directly this function.
		 * @see    operator >> (vipFrameYUV444&)
		 */
		VIPRESULT extractTo(vipFrameYUV444& img);
%VFI_END%

%VFI_START%
		%DOCFUN%/**
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
		VIPRESULT extractTo(vipFrameRGB24& img);
%VFI_END%

%VFI_START%
		%DOCFUN%/**
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
		VIPRESULT extractTo(vipFrameT<unsigned char>& img);
%VFI_END%


 };



#endif	// __VIPLIB_%CLASSDEFINE%_H__
