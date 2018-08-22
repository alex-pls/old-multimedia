/**
 *  @class   vipMotionIlluminationInvariant
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
 *  @see     vipVision
 *
 *  @version 0.8
 *  @date    12/07/2005 - //2005
 *  @author  Alessandro Polo
 *
 *
 ****************************************************************************
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.disi.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DISI - University of Trento
 *
 ****************************************************************************/



#ifndef __VIPLIB_VIPMOTIONILLUMINATIONINVARIANT_H__
 #define __VIPLIB_VIPMOTIONILLUMINATIONINVARIANT_H__

 #include "../vipDefs.h"
 #include "../vipVision.h"

 #include "../vipFrameT.h"
 #include "../vipFrameYUV420.h"
 #include "../vipFrameRGB24.h"


class vipMotionIlluminationInvariantParameters;


/**
 * @brief Source class for storing video data
 *
 *
 *
 */
class vipMotionIlluminationInvariant	:  public vipVision
 {
	protected:

		vipMotionIlluminationInvariantParameters* myParams;

		vipFrameT<unsigned char> *reflectance;
		vipFrameT<unsigned char> *buffer;

		vipFrameT<unsigned char> *diff;

		float* reflectanceCurrent;
		float* reflectanceBuffer;



// parametri x soglia

		long lastDiffValue;


//TODO..int alertCallArgumentScript;

		void initFrame(vipFrameRGB24& img);

		int evalDifference(vipFrameRGB24& diff_img);
		int evalDifference(vipFrameT<unsigned char>& diff_img);

	public:


		vipMotionIlluminationInvariant(vipMotionIlluminationInvariantParameters* initParams = NULL );
		~vipMotionIlluminationInvariant();

		VIPRESULT setParameters(vipMotionIlluminationInvariantParameters* initParams);
		vipMotionIlluminationInvariantParameters& getParameters() { return *myParams; };

		VIPRESULT reset();



		static int getIllumination(vipFrameRGB24& source_img, vipFrameRGB24& ill_img);

		static int getReflectance(vipFrameT<unsigned char> &refl_img, vipFrameRGB24& source_img);

		static int getReflectance(vipFrameRGB24& refl_img, vipFrameRGB24& source_img);





		// used into operator >>
		VIPRESULT importFrom(vipFrameYUV420& img);
		VIPRESULT importFrom(vipFrameRGB24& img);
		VIPRESULT importFrom(vipFrameT<unsigned char>& img);


 };



////////////////////////////////////////////////////////////////////////////////////////////////



class vipMotionIlluminationInvariantParameters : public vipVisionParameters
 {

	protected:

		unsigned int threshold;

		friend class vipMotionIlluminationInvariant;

	public:

		vipMotionIlluminationInvariantParameters(unsigned int threshold = 1, bool doAlert = false);
		~vipMotionIlluminationInvariantParameters() {}

		void reset();

		void setThresholdValue(unsigned int value);
		long getThresholdValue() { return threshold; };


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

#endif //__VIPLIB_VIPMOTIONILLUMINATIONINVARIANT_H__

