/** @file %FILENAME%.cpp
 *
 * File containing methods for the '%CLASSNAME%' class.
 * The header for this class can be found in %FILENAME%.h, check that file
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



#include "%FILENAME%.h"

//include specific drivers header here

%VFI_START%
%DOCFUN%/**
 * @brief  Default constructor, frame rate
 *         is managed by vipInput class.
 *
 * @param[in] fps frame rate, default is 0: max possible
 */
%CLASSNAME%::%CLASSNAME%(float fps) : vipInput(fps)
 {
	INFO("%CLASSNAME%::%CLASSNAME%(float fps) : vipInput(fps) [CONTRUCTOR]")

%EFI_START%
	reset();
%EFI_END%
 }
%VFI_END%

%DOCFUN%/**
 * @brief  Default destructor, disconnect device and delete buffer.
 */
%CLASSNAME%::~%CLASSNAME%()
 {

 }


%VFI_START%
%DOCFUN%/**
 * @brief  Reset variables.
 *
 * @return VIPRET_OK
 */
VIPRESULT %CLASSNAME%::reset()
 {
%EFI_START%
	bgRGB[0] = VIPPFG_DEF_COLOR_R;
	bgRGB[1] = VIPPFG_DEF_COLOR_G;
	bgRGB[2] = VIPPFG_DEF_COLOR_B;
%EFI_END%

	return VIPRET_OK;
 }
%VFI_END%

%VFI_START%
/**
 * @brief  Get the state of current data source.
 *
 * @return true is there are no more frames to load, false else.
 */
bool %CLASSNAME%::EoF()
 {
	 return false;
 }

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
 * @see    operator >> (vipFrameYUV420&)
 */
VIPRESULT %CLASSNAME%::extractTo(vipFrameYUV420& img)
 {
	INFO("int %CLASSNAME%::extractTo(vipFrameYUV420& img) [pushing data]")

	if ( &img == NULL )
		return VIPRET_PARAM_ERR;

%EFI_START%
//TODO memcpy instead

	/*for (unsigned int i = 0; i < img.height * img.width; i++)
		img.data[i] = bgRGB;*/
%EFI_END%

	return VIPRET_NOT_IMPLEMENTED;
 }
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
VIPRESULT %CLASSNAME%::extractTo(vipFrameYUV444& img)
 {
	INFO("int vipInputIDWT::extractTo(vipFrameYUV444& img) [pushing data]")

	if ( &img == NULL )
		return VIPRET_PARAM_ERR;

%EFI_START%
//TODO memcpy instead

	/*for (unsigned int i = 0; i < img.height * img.width; i++)
		img.data[i] = bgRGB;*/

%EFI_END%
	return VIPRET_NOT_IMPLEMENTED;
 }
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
VIPRESULT %CLASSNAME%::extractTo(vipFrameRGB24& img)
 {
	INFO("int %CLASSNAME%::extractTo(vipFrameRGB24& img) [pushing data]")

	if ( &img == NULL )
		return VIPRET_PARAM_ERR;

%EFI_START%
//TODO memcpy instead

	PixelRGB24 bgRGB24((unsigned char)bgRGB[0], (unsigned char)bgRGB[1], (unsigned char)bgRGB[2] );

	for (unsigned int i = 0; i < img.height * img.width; i++)
		img.data[i] = bgRGB24;
%EFI_END%

	return VIPRET_OK;
 }
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
VIPRESULT %CLASSNAME%::extractTo(vipFrameT<unsigned char>& img)
 {
	INFO("int %CLASSNAME%::extractTo(vipFrameT<unsigned char>& img) [pushing data]")

	if ( &img == NULL )
		return VIPRET_PARAM_ERR;

	return VIPRET_NOT_IMPLEMENTED;
 }

%VFI_END%

