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
 *  @see     vipFilter
 *
 *  @version %VERSION%
 *  @date    %TODAY%
 *  @author  %AUTHOR%
 *
 *
 ****************************************************************************
 *  Class based on Package Studio template: vipFilterTemplate version 0.9.12
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

 #include "%SOURCEDIR%vipFilter.h"


class %CLASSNAME%Parameters : public vipFilterParameters
 {
	public:
%EFI_START%
		enum RUNMODE{ DO_NOTHING, ROTATE90, FLIP };
%EFI_END%


	protected:

%EFI_START%
		RUNMODE runMode;
%EFI_END%

		friend class %CLASSNAME%;

	public:

		%CLASSNAME%Parameters();
		~%CLASSNAME%Parameters() {};

%VFI_START%
		void reset();
%VFI_END%



%EFI_START%

		void setRunMode(RUNMODE mode) { runMode = mode; };

		RUNMODE getRunMode() { return runMode; };
%EFI_END%



%VFI_START%
		%DOCFUN%/**
		 * @brief  Serialize class to XML format.
		 *         Class' tag is <vipCoder_MOVParameters>
		 *
		 * @param[in] fp output stream's pointer
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
		 */
		VIPRESULT saveToStreamXML(FILE *fp);
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Deserialize class from XML format.
		 *         Class' tag must be <vipCoder_MOVParameters>
		 *
		 * @param[in] fp input stream's pointer
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
		 */
		VIPRESULT loadFromStreamXML(FILE *fp);
%VFI_END%

};



class %CLASSNAME% :	public vipFilter
 {

 protected:


%VFI_START%
		%DOCFUN%/**
		 * @brief  Current parameters.
		 */
		%CLASSNAME%Parameters* myParams;
%VFI_END%


 public:

%VFI_START%
		%DOCFUN%/**
		 * @brief  Default constructor, initialize parameters and superclasses.
		 * @param[in] initParams parameters for this module or NULL for defaults.
		 */
		%CLASSNAME%(%CLASSNAME%Parameters* initParams = NULL );
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief Default destructor, free buffer.
		 */
		~%CLASSNAME%();
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Set parameters for this filter.
		 *
		 * @param[in] initParams Instance of %CLASSNAME%Parameters or NULL,
		 *                       NULL argument make function to create a new
		 *                       instance with default parameters.
		 *
		 * @return VIPRET_OK
		 */
		VIPRESULT setParameters(%CLASSNAME%Parameters* initParams);
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Get parameters for this filter.
		 *
		 * @return pointer to %CLASSNAME%Parameters instance.
		 */
		%CLASSNAME%Parameters& getParameters() { return *myParams; };
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Set parameters for this filter.
		 *
		 * @param[in] initParams Instance of %CLASSNAME%Parameters or NULL,
		 *                       NULL argument make function to create a new
		 *                       instance with default parameters.
		 *
		 * @return VIPRET_OK
		 */
		VIPRESULT setFilterParameters (vipFilterParameters* initParams)
		 {
			if (initParams == NULL)
				return setParameters(NULL);
			else
				return setParameters(static_cast<%CLASSNAME%Parameters*>(initParams));
		 };
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Get parameters for this filter.
		 *
		 * @return pointer to %CLASSNAME%Parameters instance.
		 */
		vipFilterParameters* getFilterParameters ()
		 {
			if (myParams == NULL)
				return NULL;
			else
				return static_cast<vipFilterParameters*>(myParams);
		 };
%VFI_END%




%VFI_START%
		%DOCFUN%/**
		 * @brief  Reset buffers and parameters.
		 *
		 * @return VIPRET_OK
		 */
		VIPRESULT reset();
%VFI_END%



%EFI_START%
		%DOCFUN%/**
		 * @brief Rotate each frame 90 degrees (right).
		 *
		 * @param[out] dest destination frame.
		 * @param[in] source source frame.
		 *
		 * @return VIPRET_OK if success, VIPRET_ILLEGAL_USE if video is empty.
		 */
		static VIPRESULT rotate90(vipFrameYUV420& dest, vipFrameYUV420& source);
%EFI_END%

%EFI_START%
		%DOCFUN%/**
		 * @brief Rotate each frame 90 degrees (right).
		 *
		 * @param[out] dest destination frame.
		 * @param[in] source source frame.
		 *
		 * @return VIPRET_OK if success, VIPRET_ILLEGAL_USE if video is empty.
		 */
		static VIPRESULT rotate90(vipFrameRGB24& dest, vipFrameRGB24& source);
%EFI_END%

%EFI_START%
		%DOCFUN%/**
		 * @brief Rotate each frame 90 degrees (right).
		 *
		 * @param[out] dest destination frame.
		 * @param[in] source source frame.
		 *
		 * @return VIPRET_OK if success, VIPRET_ILLEGAL_USE if video is empty.
		 */
		static VIPRESULT rotate90(vipFrameT<unsigned char>& dest, vipFrameT<unsigned char>& source);
%EFI_END%





%VFI_START%
		%DOCFUN%/**
		 * @brief Process the frame with current settings and store in buffer.
		 *
		 * @param[in] img VIPLib Frame YUV420 to be processed.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if runmode is unknown,
		 *         VIPRET_NOT_IMPLEMENTED if this function is not enabled jet, VIPRET_INTERNAL_ERR else.
		 *
		 * @note  Input operator (<<) call directly this function.
		 * @see   operator << (vipFrameYUV420&)
		 */
		VIPRESULT importFrom(vipFrameYUV420& img);
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief Process the frame with current settings and store in buffer.
		 *
		 * @param[in] img VIPLib Frame RGB24 to be processed.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if runmode is unknown,
		 *         VIPRET_NOT_IMPLEMENTED if this function is not enabled jet, VIPRET_INTERNAL_ERR else.
		 *
		 * @note  Input operator (<<) call directly this function.
		 * @see   operator << (vipFrameRGB24&)
		 */
		VIPRESULT importFrom(vipFrameRGB24& img);
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief Process the frame with current settings and store in buffer.
		 *
		 * @param[in] img VIPLib Frame Template to be processed.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if runmode is unknown,
		 *         VIPRET_NOT_IMPLEMENTED if this function is not enabled jet, VIPRET_INTERNAL_ERR else.
		 *
		 * @note  Input operator (<<) call directly this function.
		 * @see   operator << (vipFrameT<unsigned char>&)
		 */
		VIPRESULT importFrom(vipFrameT<unsigned char>& img);

//avoid problems of abstract class creatin on <VIPInput>
		VIPRESULT extractTo(vipFrameYUV444& img){return VIPRET_NOT_IMPLEMENTED;};

%VFI_END%


};





#endif //__VIPLIB_%CLASSDEFINE%_H__


