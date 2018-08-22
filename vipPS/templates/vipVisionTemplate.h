/**
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
 *  @see     %SUPERCLASS%
 *
 *  @version %VERSION%
 *  @date    %TODAY%
 *  @author  %AUTHOR%
 *
 ****************************************************************************
 *  Class based on Package Studio template: vipVisionTemplate version 0.9.12
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


 #include "%SOURCEDIR%vipDefs.h"
 #include "%SOURCEDIR%vipVision.h"

 #include "%SOURCEDIR%vipFrameYUV420.h"
 #include "%SOURCEDIR%vipFrameRGB24.h"
 #include "%SOURCEDIR%vipFrameT.h"

 class %CLASSNAME%Parameters;


class %CLASSNAME%	:  public vipVision
 {
	protected:

		%CLASSNAME%Parameters* myParams;

%EFI_START%
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


		%CLASSNAME%(%CLASSNAME%Parameters* initParams = NULL );
		~%CLASSNAME%();

		int setParameters(%CLASSNAME%Parameters* initParams);
		%CLASSNAME%Parameters& getParameters() { return *myParams; };

		VIPRESULT reset();




%VFI_START%
		%DOCFUN%/**
		 * @brief  Set current canvas' height.
		 *
		 * @return height in pixel.
		 */
		int setHeight(unsigned int value)
		 {
			 return VIPRET_NOT_IMPLEMENTED;
		 };
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Set current canvas' width.
		 *
		 * @return width in pixel.
		 */
		int setWidth(unsigned int value)
		 {
			 return VIPRET_NOT_IMPLEMENTED;
		 };
%VFI_END%



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
		VIPRESULT importFrom(vipFrameYUV420& img);
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



 };



////////////////////////////////////////////////////////////////////////////////////////////////



class %CLASSNAME%Parameters : public vipVisionParameters
 {

	protected:




		friend class %CLASSNAME%;

	public:

		%CLASSNAME%Parameters();
		%CLASSNAME%Parameters(bool doAlert, bool doEval);
		~%CLASSNAME%Parameters() {};

		void reset();



		/**
		 * @brief  Serialize class to XML format.
		 *         Class' tag is <vipCoder_MOVParameters>
		 *
		 * @param[in] fp output stream's pointer
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
		 */
		int saveToStreamXML(FILE *fp);

		/**
		 * @brief  Deserialize class from XML format.
		 *         Class' tag must be <vipCoder_MOVParameters>
		 *
		 * @param[in] fp input stream's pointer
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
		 */
		int loadFromStreamXML(FILE *fp);

 };

#endif //__VIPLIB_%CLASSDEFINE%_H__

