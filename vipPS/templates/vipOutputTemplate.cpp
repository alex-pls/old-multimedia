/** @file %FILENAME%.cpp
 *
 * File containing methods for the '%CLASSNAME%' class.
 * The header for this class can be found in %FILENAME%.h, check that file
 * for class description.
 *
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



#include "%FILENAME%.h"

%EFI_START%
#include "%SOURCEDIR%vipUtility.h"
%EFI_END%


%DOCFUN%/**
 * @brief  Default constructor initializes variables and canvas.
 *
 * @param[in]  mainWindow Main window's handle, if not NULL, it will be created.
 */
%CLASSNAME%::%CLASSNAME%() : vipOutput()
 {
	INFO("%CLASSNAME%::%CLASSNAME%() : vipOutput() [CONTRUCTOR]")

%EFI_START%
	height = %CLASSDEFINE%_DEF_HEIGHT;
	width = %CLASSDEFINE%_DEF_WIDTH;
	v_sleeptime = 0;

	init();
%EFI_END%

 }

%EFI_START%
%DOCFUN%/**
 * @brief  Default constructor initializes variables.
 *
 * @param width Canvas' width.
 * @param height Canvas' height.
 *
 * @param[in]  mainWindow Main window's handle, if not NULL, it will be created.
 */
%CLASSNAME%::%CLASSNAME%(unsigned int w, unsigned int h) : vipOutput()
 {
	INFO("%CLASSNAME%::%CLASSNAME%() : vipOutput() [CONTRUCTOR]")


	height = h;
	width = w;
	v_sleeptime = 0;

	init();
 }
%EFI_END%

%DOCFUN%/**
 * @brief  Default destructor, wait for pending events and flush.
 */
%CLASSNAME%::~%CLASSNAME%()
 {

 }

%EFI_START%
%DOCFUN%/**
 * @brief  Initialize canvas, create window if necessary.
 * @return VIPRET_OK
 */
VIPRESULT %CLASSNAME%::init()
 {
	return VIPRET_NOT_IMPLEMENTED;
 }
%EFI_END%

%VFI_START%
%DOCFUN%/**
 * @brief  Set display frame rate (elaboration time is not subtracted).
 *
 * @param[in] frames per second (default is 0, no sleep)
 *
 * @return VIPRET_PARAM_ERR if fps is lower than 0, VIPRET_OK else.
 */
VIPRESULT %CLASSNAME%::setFrameRate(float fps)
 {
	if (fps < 0.)
		return VIPRET_PARAM_ERR;

	if ( fps == 0 )
		v_sleeptime = 0;
	else
		v_sleeptime = (long)( (float)1000 / fps ); // milliseconds

	return VIPRET_OK;
 }
%VFI_END%

%EFI_START%
%DOCFUN%/**
 * @brief  Show canvas and if selected also main window.
 *
 * @return VIPRET_OK
 */
VIPRESULT %CLASSNAME%::show()
 {
	return VIPRET_NOT_IMPLEMENTED;
 }
%EFI_END%

%EFI_START%
%DOCFUN%/**
 * @brief  Hide canvas and if selected also main window.
 *
 * @return VIPRET_OK
 */
VIPRESULT %CLASSNAME%::hide()
 {
	return VIPRET_NOT_IMPLEMENTED;
 }
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
VIPRESULT %CLASSNAME%::importFrom(vipFrameYUV420& img)
 {
	INFO("int %CLASSNAME%::importFrom(vipFrameYUV420& img) [reading data]")

// image displaying routine
%EFI_START%
	//	if ( v_sleeptime && v_sleeptime > (long)getElaborationTime())
	//		vipUtility::vipSleep( v_sleeptime - (long)getElaborationTime() );
	vipUtility::vipSleep( v_sleeptime );    // milliseconds
%EFI_END%

	return VIPRET_NOT_IMPLEMENTED;
 }
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
VIPRESULT %CLASSNAME%::importFrom(vipFrameRGB24& img)
 {
	INFO("int %CLASSNAME%::importFrom(vipFrameRGB24& img) [reading data]")

// image displaying routine
%EFI_START%

	//	if ( v_sleeptime && v_sleeptime > (long)getElaborationTime())
	//		vipUtility::vipSleep( v_sleeptime - (long)getElaborationTime() );
	vipUtility::vipSleep( v_sleeptime );    // milliseconds
%EFI_END%

	return VIPRET_NOT_IMPLEMENTED;
 }
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
VIPRESULT %CLASSNAME%::importFrom(vipFrameRGB96& img)
 {
	INFO("int %CLASSNAME%::importFrom(vipFrameRGB96& img) [reading data]")

// image displaying routine
	//	if ( v_sleeptime && v_sleeptime > (long)getElaborationTime())
	//		vipUtility::vipSleep( v_sleeptime - (long)getElaborationTime() );
	vipUtility::vipSleep( v_sleeptime );    // milliseconds

	return VIPRET_NOT_IMPLEMENTED;
 }
%EFI_END%


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
VIPRESULT %CLASSNAME%::importFrom(vipFrameT<unsigned char>& img)
 {
	INFO("int %CLASSNAME%::importFrom(vipFrameT<unsigned char>& img) [reading data]")

// image displaying routine
%EFI_START%

	//	if ( v_sleeptime && v_sleeptime > (long)getElaborationTime())
	//		vipUtility::vipSleep( v_sleeptime - (long)getElaborationTime() );
	vipUtility::vipSleep( v_sleeptime );    // milliseconds
%EFI_END%

	return VIPRET_NOT_IMPLEMENTED;
 }
%VFI_END%





