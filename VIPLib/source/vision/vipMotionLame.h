/**
 *  @class   vipMotionLame
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



#ifndef __VIPLIB_VIPMOTIONLAME_H__
 #define __VIPLIB_VIPMOTIONLAME_H__

 #include "../vipDefs.h"
 #include "../vipVision.h"

 #include "../vipFilter.h" // vipFilterParameters !

 #include "../vipFrameYUV420.h"
 #include "../vipFrameRGB24.h"
 #include "../vipFrameT.h"


class vipMotionLameParameters;


/**
 * @brief Source class for storing video data
 *
 *
 *
 */
class vipMotionLame	:  public vipVision
 {
	protected:

		vipMotionLameParameters* myParams;

		vipFrameRGB24* buffer;

		vipFrameRGB24* diff;

// parametri x soglia

		long lastDiffValue;


//TODO..int alertCallArgumentScript;

		void initFrame(vipFrameRGB24& img);

		VIPRESULT evalDifference(vipFrameRGB24& diff_img);

	public:


		vipMotionLame(vipMotionLameParameters* initParams = NULL );
		~vipMotionLame();

		VIPRESULT setParameters(vipMotionLameParameters* initParams);
		vipMotionLameParameters& getParameters() { return *myParams; };

		VIPRESULT reset();

		unsigned int getLastDifferenceValue() { return lastDiffValue; };



		static long getDifferenceBrightnessValue(vipFrameRGB24& diff_img);





		// used into operator >>
		VIPRESULT importFrom(vipFrameYUV420& img);
		VIPRESULT importFrom(vipFrameRGB24& img);
		VIPRESULT importFrom(vipFrameT<unsigned char>& img);


 };



////////////////////////////////////////////////////////////////////////////////////////////////



class vipMotionLameParameters : public vipVisionParameters
 {

	protected:


		long threshold;

		friend class vipMotionLame;

	public:

		vipMotionLameParameters(long threshold = 1, bool doAlert = false, bool doEval = true);
//		~vipMotionLameParameters() {}

		void reset();

		void setThresholdValue(long value);
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

#endif //__VIPLIB_VIPMOTIONLAME_H__

