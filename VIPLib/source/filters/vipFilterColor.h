/**
 *  @class   vipFilterColor
 *
 *  @brief   this class performs clipping and equalization operations on a source image
 *
 *
 *
 *
 *  @bug
 *  @warning
 *  @todo
 *
 *  @see     vipFilter, vipHist
 *
 *  @version 1.1
 *  @date    06/07/2006 21.27.48
 *  @author  Fabrizio Baffetti, Diego Bosetti
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



#ifndef __VIPLIB_VIPFILTERCOLOR_H__
 #define __VIPLIB_VIPFILTERCOLOR_H__

 #include "../../source/vipDefs.h"
 #include "../../source/vipFilter.h"
 #include "../../source/vipHist.h"

 #include "../../source/vipFrameYUV420.h"
 #include "../../source/vipFrameYUV444.h"
 #include "../../source/vipFrameRGB24.h"
 #include "../../source/vipFrameT.h"


class vipFilterColorParameters : public vipFilterParameters
{
	public:

		enum RUNMODE{ DO_NOTHING, CLIPPING, EQUALIZER, CLAMP, INVERT, EXTRACTBITPLANE, SEPIA };

	protected:

		RUNMODE runMode;

		unsigned int currBpp;
		unsigned int currBits;
		unsigned int lowerThreshold;
		unsigned int upperThreshold;

		friend class vipFilterColor;


	public:

		vipFilterColorParameters(RUNMODE mode = vipFilterColorParameters::DO_NOTHING);
		~vipFilterColorParameters() {}

		void reset();

		void setRunMode(RUNMODE mode) { runMode = mode; };
		RUNMODE getRunMode() { return runMode; };

		void setWorkingBpp(unsigned int value) { currBpp = value; };
		unsigned int getWorkingBpp() { return currBpp; };

		void setBitPlaneBits(unsigned int value) { currBits = value; };
		unsigned int getBitPlaneBits() { return currBits; };

		void setLowerThreshold(unsigned int value) { lowerThreshold = value; };
		unsigned int getLowerThreshold() { return lowerThreshold; };

		void setUpperThreshold(unsigned int value) { upperThreshold = value; };
		unsigned int getUpperThreshold() { return upperThreshold; };


		VIPRESULT saveToStreamXML(FILE *fp);
		VIPRESULT loadFromStreamXML(FILE *fp);

};


class vipFilterColor :	public vipFilter
 {

 protected:

		/**
		 * @brief  Current parameters.
		 */
		vipFilterColorParameters* myParams;

 public:


		/**
		 * @brief  Default constructor, initialize parameters and superclasses.
		 * @param[in] initParams parameters for this module or NULL for defaults.
		 */
		vipFilterColor( vipFilterColorParameters* initParams = NULL );

		/**
		 * @brief Default destructor, free buffer.
		 */
		~vipFilterColor();


		float getFrameRate()  const { return 0; };

		/**
		 * @brief  Set parameters for this filter.
		 *
		 * @param[in] initParams Instance of vipFilterColorParameters or NULL,
		 *                       NULL argument make function to create a new
		 *                       instance with default parameters.
		 *
		 * @return VIPRET_OK
		 */
		VIPRESULT setParameters(vipFilterColorParameters* initParams);

		/**
		 * @brief  Get parameters for this filter.
		 *
		 * @return pointer to vipFilterColorParameters instance.
		 */
		vipFilterColorParameters& getParameters() { return *myParams; };


		/**
		 * @brief  Set parameters for this filter.
		 *
		 * @param[in] initParams Instance of vipFilterColorParameters or NULL,
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
				return setParameters(static_cast<vipFilterColorParameters*>(initParams));
		 };



		/**
		 * @brief  Get parameters for this filter.
		 *
		 * @return pointer to vipFilterColorParameters instance.
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



		VIPRESULT clamp(vipFrameRGB24& img, unsigned int bpp);
		VIPRESULT clamp(vipFrameYUV420& img, unsigned int bpp);//=sizeof(int)*3
		VIPRESULT clamp(vipFrameYUV444& img, unsigned int bpp);//=sizeof(int)*3
		VIPRESULT clamp(vipFrameT<unsigned char>& img, unsigned int bpp);

		VIPRESULT invert(vipFrameRGB24& img, unsigned int bpp);//=sizeof(int)*3
		VIPRESULT invert(vipFrameYUV420& img, unsigned int bpp);//=sizeof(int)*3
		VIPRESULT invert(vipFrameYUV444& img, unsigned int bpp);//=sizeof(int)*3
		VIPRESULT invert(vipFrameT<unsigned char>& img, unsigned int bpp);//=sizeof(int)*3

		VIPRESULT extractBitPlane(vipFrameRGB24& img, unsigned int bits = 1);
		
		VIPRESULT extractBitPlane(vipFrameYUV420& img, unsigned int bits = 1);
		VIPRESULT extractBitPlane(vipFrameYUV444& img, unsigned int bits = 1);
		VIPRESULT extractBitPlane(vipFrameT<unsigned char>& img, unsigned int bits = 1);
		

		/**
		* @brief applies clipping process on the frame in income.
		*
		* @param[in] img VIPLib FrameRGB24 to be processed, lower threshold and upper threshold.
		* @param[out] dest destination FrameRGB24.
		*
		* @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if runmode is unknown,
		*         VIPRET_NOT_IMPLEMENTED if this function is not enabled jet.
		*
		*/
		VIPRESULT clipping(vipFrameRGB24& img, vipFrameRGB24& dest, unsigned int inf, unsigned int sup);
		
		VIPRESULT clipping(vipFrameYUV420& img, vipFrameYUV420& dest, unsigned int inf,unsigned int sup);
		VIPRESULT clipping(vipFrameYUV444& img, vipFrameYUV444& dest, unsigned int inf,unsigned int sup);
		VIPRESULT clipping(vipFrameT<unsigned char>& img, vipFrameT<unsigned char>& dest, unsigned int inf,unsigned int sup);

		
		
		/**
		* @brief applies equalization process on the frame in income.
		*
		* @param[in] img VIPLib FrameRGB24 to be processed.
		* @param[out] dest destination FrameRGB24.
		*
		* @return VIPRET_OK if everything is fine, VIPRET_NOT_IMPLEMENTED if this function is not enabled jet.
		*
		*/
		VIPRESULT equalizer(vipFrameRGB24& source,vipFrameRGB24& dest);
		
		VIPRESULT equalizer(vipFrameYUV420& source, vipFrameYUV420& dest);
		VIPRESULT equalizer(vipFrameYUV444& source, vipFrameYUV444& dest);
		VIPRESULT equalizer(vipFrameT<unsigned char>& source, vipFrameT<unsigned char>& dest);

		
		
		/**
		* @brief applies sepia filter on the frame in income.
		*
		* @param[in] img VIPLib FrameRGB24 to be processed.
		* @param[out] dest destination FrameRGB24.
		*
		* @return VIPRET_OK if everything is fine, VIPRET_NOT_IMPLEMENTED if this function is not enabled jet.
		*
		*/
		VIPRESULT sepia(vipFrameRGB24& source,vipFrameRGB24& dest);
		VIPRESULT sepia(vipFrameYUV420& source, vipFrameYUV420& dest);
		VIPRESULT sepia(vipFrameYUV444& source, vipFrameYUV444& dest);
		VIPRESULT sepia(vipFrameT<unsigned char>& source, vipFrameT<unsigned char>& dest);


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
		 * @param[in] img VIPLibb Cache Frame to be processed.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
		 *
		 * @note  Input operator (<<) call directly this function.
		 * @see   operator << (vipFrameYUV444&)
		 */
		VIPRESULT importFrom(vipFrameYUV444& img);
		
		
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



#endif //__VIPLIB_VIPFILTERCOLOR_H__


