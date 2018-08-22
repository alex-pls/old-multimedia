/**
 *  @class   vipFilterMorphological
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
 *  @date    26/05/2006 13.26.42
 *  @author  Stefano Asioli
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



#ifndef __VIPLIB_VIPFILTERMORPHOLOGICAL_H__
 #define __VIPLIB_VIPFILTERMORPHOLOGICAL_H__

 #include "../../source/vipFilter.h"
#include <math.h>


class vipFilterMorphologicalParameters : public vipFilterParameters
 {
	public:

		enum RUNMODE{ DO_NOTHING, ERODE, DILATE, OPEN, CLOSE };



	protected:

	   /*
	    * @brief Run mode of the filter
		*/
		RUNMODE runMode;
	   /*
	    * @brief Radius of the structural element
		*/
		int StructElemRadius;
	   /*
	    * @brief Pointer to the matrix containing the structural element
		*/
		int ** StructElem;
		
		friend class vipFilterMorphological;

	public:
	   /**
		* @brief  Default constructor.
		*/
		vipFilterMorphologicalParameters();
	   
	   /**
		* @brief Default destructor, if necessary deletes the structural element.
		*/
		~vipFilterMorphologicalParameters();
		
	   /**
		* @brief Resets the object.
		*/
		void reset();

	   /**
		* @brief Gives the structural element radius.
		*
		* @return Structural element radius
		*/
		int getRadius();
		
	   /**
		* @brief Sets the structural element radius.
		*
		* @param[in] i Structural element row
		* @param[in] j Structural element column
		* @return Element in position (i,j)
		*/
		int getStructElem(int, int);

	   /**
		* @brief Sets the run mode of the filter.
		*/
		void setRunMode(RUNMODE mode) { runMode = mode; };
	   
	   /**
		* @brief Initializes the structural element.
		*/
		void setStructElem();
		
	   /**
		* @brief Sets the structural element radius.
		* 
		* @param[in] radius Structural element radius
		*/
		void setRadius(int);

	   /**
		* @brief Gives the run mode of the filter.
		*
		* @return Run mode.
		*/
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



class vipFilterMorphological :	public vipFilter
 {

 protected:

		/**
		 * @brief  Current parameters.
		 */
		vipFilterMorphologicalParameters* myParams;
		
		/**
		 * @brief  Pointer to a luminance matrix (actually, an image).
		 */
		float ** LuminanceMatrix;

 public:


		/**
		 * @brief  Default constructor, initialize parameters and superclasses.
		 * @param[in] initParams parameters for this module or NULL for defaults.
		 */
		vipFilterMorphological(vipFilterMorphologicalParameters* initParams = NULL );

		/**
		 * @brief Default destructor, free buffer.
		 */
		~vipFilterMorphological();
		
		/**
		 * @brief Creates a matrix containing the luminance of each pixel of the source image.
		 *
		 * @param[in] source VIPLib Frame RGB24 to be processed.
		 *
		 */
		 void setLuminanceMatrix(vipFrameRGB24);
		 
		/**
		 * @brief Deletes the matrix containing the luminance of each pixel of the source image.
		 *
		 * @param[in] height Numbers of lines in the matrix.
		 */
		 void deleteLuminanceMatrix(int);

		/**
		 * @brief  Set parameters for this filter.
		 *
		 * @param[in] initParams Instance of vipFilterMorphologicalParameters or NULL,
		 *                       NULL argument make function to create a new
		 *                       instance with default parameters.
		 *
		 * @return VIPRET_OK
		 */
		VIPRESULT setParameters(vipFilterMorphologicalParameters* initParams);

		/**
		 * @brief  Get parameters for this filter.
		 *
		 * @return pointer to vipFilterMorphologicalParameters instance.
		 */
		vipFilterMorphologicalParameters& getParameters() { return *myParams; };

		/**
		 * @brief  Set parameters for this filter.
		 *
		 * @param[in] initParams Instance of vipFilterMorphologicalParameters or NULL,
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
				return setParameters(static_cast<vipFilterMorphologicalParameters*>(initParams));
		 };

		/**
		 * @brief  Get parameters for this filter.
		 *
		 * @return pointer to vipFilterMorphologicalParameters instance.
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
		 * @brief Erodes source image and puts the result into dest.
		 *
		 * @param[out] dest VIPLib Frame RGB24 processed.
		 * @param[in]  source VIPLib Frame RGB24 to be processed.
		 *
		 * @return VIPRET_OK
		 *
		 * @note  This is not a static function.
		 */
		VIPRESULT erode(vipFrameRGB24& dest, vipFrameRGB24& source);
		VIPRESULT erode(vipFrameYUV420& dest, vipFrameYUV420& source);
		VIPRESULT erode(vipFrameYUV444& dest, vipFrameYUV444& source);
		VIPRESULT erode(vipFrameT<unsigned char>& dest, vipFrameT<unsigned char>& source);

		/**
		 * @brief Dilates source image and puts the result into dest.
		 *
		 * @param[out] dest VIPLib Frame RGB24 processed.
		 * @param[in]  source VIPLib Frame RGB24 to be processed.
		 *
		 * @return VIPRET_OK
		 *
		 * @note  This is not a static function.
		 */
		VIPRESULT dilate(vipFrameRGB24& dest, vipFrameRGB24& source);
		VIPRESULT dilate(vipFrameYUV420& dest, vipFrameYUV420& source);
		VIPRESULT dilate(vipFrameYUV444& dest, vipFrameYUV444& source);
		VIPRESULT dilate(vipFrameT<unsigned char>& dest, vipFrameT<unsigned char>& source);

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
		VIPRESULT importFrom(vipFrameYUV444& img);
		
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





#endif //__VIPLIB_VIPFILTERMORPHOLOGICAL_H__


