/**
 *  @class   vipFilterEdge
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
 *  @version 0.1
 *  @date    23/05/2006 15:04:41
 *  @author  Nicola Conci
 *
 *
 ****************************************************************************
 *  Class based on Package Studio template: vipFilterTemplate version 0.9.12
 ****************************************************************************
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.disi.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DISI - University of Trento
 *
 ****************************************************************************/



#ifndef __VIPLIB_VIPFILTEREDGE_H__
 #define __VIPLIB_VIPFILTEREDGE_H__

 #include "../../source/vipFilter.h"


#define VIPFILTERSOBEL_DEFAULT_THRESHOLD 100;
#define VIPFILTERCANNY_DEFAULT_THRESHOLD_HI 120;
#define VIPFILTERCANNY_DEFAULT_THRESHOLD_LO 40;


class vipFilterEdgeParameters : public vipFilterParameters
 {
	public:

		enum RUNMODE{ DO_NOTHING, DO_SOBEL, DO_CANNY };



	protected:


		RUNMODE runMode;
		int threshold_sobel;
		int threshold_canny_hi;
		int threshold_canny_lo;



		friend class vipFilterEdge;

	public:

		vipFilterEdgeParameters();
		~vipFilterEdgeParameters() {};


		void reset();


		void setRunMode(RUNMODE mode) { runMode = mode; };

		RUNMODE getRunMode() { return runMode; };




		void setThresholdSobel(int value) { threshold_sobel = value; };
		int getThresholdSobel() { return threshold_sobel; };

		void setThresholdCannyHi(int value) { threshold_canny_hi = value; };
		int getThresholdCannyHi() { return threshold_canny_hi; };

		void setThresholdCannyLo(int value) { threshold_canny_lo = value; };
		int getThresholdCannyLo() { return threshold_canny_lo; };





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



class vipFilterEdge :	public vipFilter
 {

 protected:



		/**
		 * @brief  Current parameters.
		 */
		vipFilterEdgeParameters* myParams;



 public:


		/**
		 * @brief  Default constructor, initialize parameters and superclasses.
		 * @param[in] initParams parameters for this module or NULL for defaults.
		 */
		vipFilterEdge(vipFilterEdgeParameters* initParams = NULL );



		/**
		 * @brief Default destructor, free buffer.
		 */
		~vipFilterEdge();



		/**
		 * @brief  Set parameters for this filter.
		 *
		 * @param[in] initParams Instance of vipFilterEdgeParameters or NULL,
		 *                       NULL argument make function to create a new
		 *                       instance with default parameters.
		 *
		 * @return VIPRET_OK
		 */
		VIPRESULT setParameters(vipFilterEdgeParameters* initParams);



		/**
		 * @brief  Get parameters for this filter.
		 *
		 * @return pointer to vipFilterEdgeParameters instance.
		 */
		vipFilterEdgeParameters& getParameters() { return *myParams; };



		/**
		 * @brief  Set parameters for this filter.
		 *
		 * @param[in] initParams Instance of vipFilterEdgeParameters or NULL,
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
				return setParameters(static_cast<vipFilterEdgeParameters*>(initParams));
		 };



		/**
		 * @brief  Get parameters for this filter.
		 *
		 * @return pointer to vipFilterEdgeParameters instance.
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
		 * @brief Apply Sobel Filter.
		 *
		 * @param[out] dest destination frame.
		 * @param[in] source source frame.
		 *
		 * @return VIPRET_OK if success, VIPRET_ILLEGAL_USE if video is empty.
		 */
		static VIPRESULT applySobel(vipFrameYUV420& dest, vipFrameYUV420& source, int threshold);



		/**
		 * @brief Apply Sobel Filter.
		 *
		 * @param[out] dest destination frame.
		 * @param[in] source source frame.
		 *
		 * @return VIPRET_OK if success, VIPRET_ILLEGAL_USE if video is empty.
		 */
		static VIPRESULT applySobel(vipFrameRGB24& dest, vipFrameRGB24& source, int threshold);



		/**
		 * @brief Apply Sobel Filter.
		 *
		 * @param[out] dest destination frame.
		 * @param[in] source source frame.
		 *
		 * @return VIPRET_OK if success, VIPRET_ILLEGAL_USE if video is empty.
		 */
		static VIPRESULT applySobel(vipFrameT<unsigned char>& dest, vipFrameT<unsigned char>& source, int threshold);







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
		 * @param[in] img VIPLib Frame YUV444 to be processed.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if runmode is unknown,
		 *         VIPRET_NOT_IMPLEMENTED if this function is not enabled jet, VIPRET_INTERNAL_ERR else.
		 *
		 * @note  Input operator (<<) call directly this function.
		 * @see   operator << (vipFrameYUV444&)
		 */
		VIPRESULT importFrom(vipFrameYUV444 &img);
		




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


		// added by marco verza to remove abstraction from vipInput
		VIPRESULT vipFilterEdge::extractTo(vipFrameYUV444 &frame444)
		{return VIPRET_NOT_IMPLEMENTED;};



		/**
		 * @brief Apply Canny Edge detection Filter.
		 *
		 * @param[in] source VIPLib Frame Template to be processed.
		 * @param[out]  dest VIPLib Frame Template result of the filtering.
		 *
		 * @return VIPRET_OK if success, VIPRET_ILLEGAL_USE if video is empty.
		 * @note	Not fully tested.
		 */
		static VIPRESULT applyCanny(vipFrameT<unsigned char>& dest, vipFrameT<unsigned char>& source, int up_threshold = 120, int low_threshold = 40);
		
};


#endif //__VIPLIB_VIPFILTEREDGE_H__


