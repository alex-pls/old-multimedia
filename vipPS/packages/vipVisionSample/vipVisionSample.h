/**
 *  @class   vipVisionSample
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
 *  @version 1.0
 *  @date    19/05/2006 7.26.23
 *  @author  Alessandro Polo
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



#ifndef __VIPLIB_VIPVISIONSAMPLE_H__
 #define __VIPLIB_VIPVISIONSAMPLE_H__


 #include "I:\Projects\Software\VIPLib\source\vipDefs.h"
 #include "I:\Projects\Software\VIPLib\source\vipVision.h"

 #include "I:\Projects\Software\VIPLib\source\vipFrameYUV420.h"
 #include "I:\Projects\Software\VIPLib\source\vipFrameRGB24.h"
 #include "I:\Projects\Software\VIPLib\source\vipFrameT.h"

 class vipVisionSampleParameters;


class vipVisionSample	:  public vipVision
 {
	protected:

		vipVisionSampleParameters* myParams;


		/**
		 * @brief  Canvas' width.
		 */
		unsigned int width;
		/**
		 * @brief  Canvas' height.
		 */
		unsigned int height;



	public:


		vipVisionSample(vipVisionSampleParameters* initParams = NULL );
		~vipVisionSample();

		int setParameters(vipVisionSampleParameters* initParams);
		vipVisionSampleParameters& getParameters() { return *myParams; };

		VIPRESULT reset();





		/**
		 * @brief  Set current canvas' height.
		 *
		 * @return height in pixel.
		 */
		int setHeight(unsigned int value)
		 {
			 return VIPRET_NOT_IMPLEMENTED;
		 };



		/**
		 * @brief  Set current canvas' width.
		 *
		 * @return width in pixel.
		 */
		int setWidth(unsigned int value)
		 {
			 return VIPRET_NOT_IMPLEMENTED;
		 };





		/**
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




		/**
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





		/**
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




 };



////////////////////////////////////////////////////////////////////////////////////////////////



class vipVisionSampleParameters : public vipVisionParameters
 {

	protected:




		friend class vipVisionSample;

	public:

		vipVisionSampleParameters();
		vipVisionSampleParameters(bool doAlert, bool doEval);
		~vipVisionSampleParameters() {};

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

#endif //__VIPLIB_VIPVISIONSAMPLE_H__

