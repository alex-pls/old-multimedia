/**
 *  @class   vipFilterNoiseChannel
 *
 *  @brief
 *
 *
 *  @bug     bad noise, very slowwwww
 *  @warning
 *  @todo
 *
 *  @see     vipFilter
 *  @example ../../tests/test_vipFilterNoiseChannel.cpp
 *
 *  @version 0.4
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




#ifndef __VIPLIB_VIPFILTERNOISECHANNEL_H__
 #define __VIPLIB_VIPFILTERNOISECHANNEL_H__

 #include "../vipDefs.h"
 #include "../vipFilter.h"

 #include "../vipFrameYUV420.h"
 #include "../vipFrameRGB24.h"
 #include "../vipFrameT.h"



class vipFilterNoiseChannelParameters : public vipFilterParameters
{
	public:

		enum NOISEOPER{ ADDITIVE, MULTIPLICATIVE };

	protected:

		NOISEOPER operation;
		bool normalized;
		float spread;
		int normalize_value;

		friend class vipFilterNoiseChannel;


	public:

		vipFilterNoiseChannelParameters(NOISEOPER mode = vipFilterNoiseChannelParameters::ADDITIVE);
		~vipFilterNoiseChannelParameters() {}

		void reset();

		void setOperation(NOISEOPER mode) { operation = mode; };
		NOISEOPER getOperation() { return operation; };

		void setNormalisedNoise(bool value = true) { normalized = value; };
		bool isNormalisedNoise() { return normalized; };

		void setNormalisedNoiseValue(int value) { normalize_value = value; };
		int getNormalisedNoiseValue() { return normalize_value; };

		void setSpread(float value) { spread = value; };
		float isSpread() { return spread; };


		VIPRESULT saveToStreamXML(FILE *fp);
		VIPRESULT loadFromStreamXML(FILE *fp);


};

class vipFilterNoiseChannel :	public vipFilter
 {

 protected:

		/**
		 * @brief  Current parameters.
		 */
		vipFilterNoiseChannelParameters* myParams;

		vipInput* externalSource;

		PixelRGB24 zeroRGB;
		PixelRGB24 oneRGB;

		unsigned char zeroChar;
		unsigned char oneChar;

		void generateNoise(vipFrameYUV420& img, unsigned char zero);
		void generateNoise(vipFrameRGB24& img, PixelRGB24 zero);
		void generateNoise(vipFrameT<unsigned char>& img, unsigned char zero);

 public:


		/**
		 * @brief  Default constructor, initialize parameters and superclasses.
		 * @param[in] initParams parameters for this module or NULL for defaults.
		 */
		vipFilterNoiseChannel(vipFilterNoiseChannelParameters* initParams = NULL);

		/**
		 * @brief Default destructor, free buffer.
		 */
		~vipFilterNoiseChannel();

		/**
		 * @brief  Set parameters for this filter.
		 *
		 * @param[in] initParams Instance of vipFilterNoiseChannelParameters or NULL,
		 *                       NULL argument make function to create a new
		 *                       instance with default parameters.
		 *
		 * @return VIPRET_OK
		 */
		VIPRESULT setParameters(vipFilterNoiseChannelParameters* initParams);

		/**
		 * @brief  Get parameters for this filter.
		 *
		 * @return pointer to vipFilterNoiseChannelParameters instance.
		 */
		vipFilterNoiseChannelParameters& getParameters() { return *myParams; };

		/**
		 * @brief  Set parameters for this filter.
		 *
		 * @param[in] initParams Instance of vipFilterNoiseChannelParameters or NULL,
		 *                       NULL argument make function to create a new
		 *                       instance with default parameters.
		 *
		 * @return VIPRET_OK
		 */
		VIPRESULT setFilterParameters (vipFilterNoiseChannelParameters* initParams)
		 {
			if (initParams == NULL)
				return setParameters(NULL);
			else
				return setParameters(static_cast<vipFilterNoiseChannelParameters*>(initParams));
		 };



		/**
		 * @brief  Get parameters for this filter.
		 *
		 * @return pointer to vipFilterNoiseChannelParameters instance.
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


		// take care of frame rate and neutral pixel (0 for add, 1 for mult)
		VIPRESULT setNoiseSource(vipInput& frameSource);

		//internal
		void resetNoiseSource();



		VIPRESULT AddNoise(vipFrameYUV420& img);
		VIPRESULT AddNoise(vipFrameRGB24& img);
		VIPRESULT AddNoise(vipFrameT<unsigned char>& img);

		VIPRESULT MultiplyNoise(vipFrameYUV420& img);
		VIPRESULT MultiplyNoise(vipFrameRGB24& img);
		VIPRESULT MultiplyNoise(vipFrameT<unsigned char>& img);




		/**
		 * @brief Process the frame with current settings and store in buffer.
		 *
		 * @param[in] img VIPLibb Cache Frame to be processed.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
		 *
		 * @note  Input operator (<<) call directly this function.
		 * @see   operator << (vipFrameYUV420&)
		 */
		VIPRESULT importFrom(vipFrameYUV420& img);

		/**
		 * @brief Process the frame with current settings and store in buffer.
		 *
		 * @param[in] img VIPLibb Cache24 Frame to be processed.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
		 *
		 * @note  Input operator (<<) call directly this function.
		 * @see   operator << (vipFrameRGB24&)
		 */
		VIPRESULT importFrom(vipFrameRGB24& img);

		/**
		 * @brief Process the frame with current settings and store in buffer.
		 *
		 * @param[in] img VIPLibb Grayscale Frame to be processed.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
		 *
		 * @note  Input operator (<<) call directly this function.
		 * @see   operator << (vipFrameT&)
		 */
		VIPRESULT importFrom(vipFrameT<unsigned char>& img);



};



#endif //__VIPLIB_VIPFILTERNOISECHANNEL_H__

/*
//TODO
	S/N // -> calcolo potenze!

*/
