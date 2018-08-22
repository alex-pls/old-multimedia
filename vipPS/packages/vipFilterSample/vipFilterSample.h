/**
 *  @class   vipFilterSample
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
 *  @version 1.0
 *  @date    19/05/2006 7.33.36
 *  @author  Alessandro Polo
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



#ifndef __VIPLIB_VIPFILTERSAMPLE_H__
 #define __VIPLIB_VIPFILTERSAMPLE_H__

 #include "I:\Projects\Software\VIPLib\source\vipFilter.h"


class vipFilterSampleParameters : public vipFilterParameters
 {
	public:

		enum RUNMODE{ DO_NOTHING, ROTATE90, FLIP };



	protected:


		RUNMODE runMode;


		friend class vipFilterSample;

	public:

		vipFilterSampleParameters();
		~vipFilterSampleParameters() {};


		void reset();






		void setRunMode(RUNMODE mode) { runMode = mode; };

		RUNMODE getRunMode() { return runMode; };





		/**
		 * @brief  Serialize class to XML format.
		 *         Class' tag is <vipCoder_MOVParameters>
		 *
		 * @param[in] fp output stream's pointer
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
		 */
		VIPRESULT saveToStreamXML(FILE *fp);



		/**
		 * @brief  Deserialize class from XML format.
		 *         Class' tag must be <vipCoder_MOVParameters>
		 *
		 * @param[in] fp input stream's pointer
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
		 */
		VIPRESULT loadFromStreamXML(FILE *fp);


};



class vipFilterSample :	public vipFilter
 {

 protected:



		/**
		 * @brief  Current parameters.
		 */
		vipFilterSampleParameters* myParams;



 public:


		/**
		 * @brief  Default constructor, initialize parameters and superclasses.
		 * @param[in] initParams parameters for this module or NULL for defaults.
		 */
		vipFilterSample(vipFilterSampleParameters* initParams = NULL );



		/**
		 * @brief Default destructor, free buffer.
		 */
		~vipFilterSample();



		/**
		 * @brief  Set parameters for this filter.
		 *
		 * @param[in] initParams Instance of vipFilterSampleParameters or NULL,
		 *                       NULL argument make function to create a new
		 *                       instance with default parameters.
		 *
		 * @return VIPRET_OK
		 */
		VIPRESULT setParameters(vipFilterSampleParameters* initParams);



		/**
		 * @brief  Get parameters for this filter.
		 *
		 * @return pointer to vipFilterSampleParameters instance.
		 */
		vipFilterSampleParameters& getParameters() { return *myParams; };



		/**
		 * @brief  Set parameters for this filter.
		 *
		 * @param[in] initParams Instance of vipFilterSampleParameters or NULL,
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
				return setParameters(static_cast<vipFilterSampleParameters*>(initParams));
		 };



		/**
		 * @brief  Get parameters for this filter.
		 *
		 * @return pointer to vipFilterSampleParameters instance.
		 */
		vipFilterParameters* getFilterParameters ()
		 {
			if (myParams == NULL)
				return NULL;
			else
				return static_cast<vipFilterParameters*>(myParams);
		 };






		/**
		 * @brief  Reset buffers and parameters.
		 *
		 * @return VIPRET_OK
		 */
		VIPRESULT reset();





		/**
		 * @brief Rotate each frame 90 degrees (right).
		 *
		 * @param[out] dest destination frame.
		 * @param[in] source source frame.
		 *
		 * @return VIPRET_OK if success, VIPRET_ILLEGAL_USE if video is empty.
		 */
		static VIPRESULT rotate90(vipFrameYUV420& dest, vipFrameYUV420& source);



		/**
		 * @brief Rotate each frame 90 degrees (right).
		 *
		 * @param[out] dest destination frame.
		 * @param[in] source source frame.
		 *
		 * @return VIPRET_OK if success, VIPRET_ILLEGAL_USE if video is empty.
		 */
		static VIPRESULT rotate90(vipFrameRGB24& dest, vipFrameRGB24& source);



		/**
		 * @brief Rotate each frame 90 degrees (right).
		 *
		 * @param[out] dest destination frame.
		 * @param[in] source source frame.
		 *
		 * @return VIPRET_OK if success, VIPRET_ILLEGAL_USE if video is empty.
		 */
		static VIPRESULT rotate90(vipFrameT<unsigned char>& dest, vipFrameT<unsigned char>& source);







		/**
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



		/**
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



		/**
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



};





#endif //__VIPLIB_VIPFILTERSAMPLE_H__


