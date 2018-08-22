/**
 *  @class   vipDigitalFilter
 *
 *  @brief
 *
 *
 *  @see     vipFilter
 *  @example ../../tests/test_vipDigitalFilter.cpp
 *
 *  @version 1.0.2
 *  @date    02/09/2005
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


#ifndef __VIPLIB_VIPDIGITALFILTER_H__
 #define __VIPLIB_VIPDIGITALFILTER_H__

 #include "../vipDefs.h"
 #include "../vipFilter.h"

 #include "../vipFrameT.h"
 #include "../vipFrameYUV420.h"
 #include "../vipFrameRGB24.h"

 #include "../math/vipMatrix.h"

 #include "../math/vipDFMatrix.h"



class vipDigitalFilterParameters : public vipFilterParameters
{
	public:

//		enum RUNMODE{ DO_NOTHING, SOLARIZE, POSTERIZE, CLAMP, INVERT, EXTRACTBITPLANE };

	protected:

		vipDFMatrix* currentKernel;
		bool clampNegative;


		friend class vipDigitalFilter;


	public:

		vipDigitalFilterParameters();
		~vipDigitalFilterParameters() {}

		void reset();

		void setCurrentKernel(vipDFMatrix* data);
		void setClampNegative(bool value = true);

		bool isClampNegativeEnabled() { return clampNegative; };
		vipDFMatrix* getCurrentKernel() { return currentKernel; };

		VIPRESULT saveToStreamXML(FILE *fp);
		VIPRESULT loadFromStreamXML(FILE *fp);

};




class vipDigitalFilter :	public vipFilter
 {

	protected:

		vipDigitalFilterParameters* myParams;

	public:


		/**
		 * @brief  Default constructor, initialize parameters and superclasses.
		 * @param[in] initParams parameters for this module or NULL for defaults.
		 */
		vipDigitalFilter(vipDigitalFilterParameters* initParams = NULL);

		/**
		 * @brief Default destructor, free buffer.
		 */
		~vipDigitalFilter();

		/**
		 * @brief  Set parameters for this filter.
		 *
		 * @param[in] initParams Instance of vipDigitalFilterParameters or NULL,
		 *                       NULL argument make function to create a new
		 *                       instance with default parameters.
		 *
		 * @return VIPRET_OK
		 */
		VIPRESULT setParameters(vipDigitalFilterParameters* initParams);

		/**
		 * @brief  Get parameters for this filter.
		 *
		 * @return pointer to vipDigitalFilterParameters instance.
		 */
		vipDigitalFilterParameters& getParameters() { return *myParams; };


		/**
		 * @brief  Set parameters for this filter.
		 *
		 * @param[in] initParams Instance of vipDigitalFilterParameters or NULL,
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
				return setParameters(static_cast<vipDigitalFilterParameters*>(initParams));
		 };



		/**
		 * @brief  Get parameters for this filter.
		 *
		 * @return pointer to vipDigitalFilterParameters instance.
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


		VIPRESULT setDefaultKernel(int index);


		// necessaria conversione di tipo per quelli definiti dall'utente !!

		template <class T, class S>
		static int doProcessing(vipFrameT<T> &source, vipFrameT<S> &dest, vipDFMatrix& kernel)
		 {
			if (&source == NULL || &dest == NULL || &kernel == NULL)
				return VIPRET_PARAM_ERR;

			signed long numb;
			unsigned int src_w = source.width;

			if (kernel.getDim() == 3)
			 {
				for(unsigned int x=0; x < src_w; x++)
				   for(unsigned int y=0; y < source.height; y++)
					{
						if ( x && y && (x != src_w-1) && (y != source.height-1)) //3x3 matrix!
						 {
						 numb = (long) (	source.data[(y-1) * src_w + (x-1)] * kernel[0] +
											source.data[(y-1) * src_w +  x   ] * kernel[1] +
											source.data[(y-1) * src_w + (x+1)] * kernel[2] +
											source.data[ y    * src_w + (x-1)] * kernel[3] +
											source.data[ y    * src_w +  x   ] * kernel[4] +
											source.data[ y    * src_w + (x+1)] * kernel[5] +
											source.data[(y+1) * src_w + (x-1)] * kernel[6] +
											source.data[(y+1) * src_w +  x   ] * kernel[7] +
											source.data[(y+1) * src_w + (x+1)] * kernel[8]	);

						 if ( numb )
							numb /= (long)kernel[9];//normalization

						dest.data[y * src_w + x] = (S)numb;

						 }
						else
							dest.data[y * src_w + x] = (S)source.data[y * src_w + x];
				   }
			 }
			else if (kernel.getDim() == 5)
			 {
				for(unsigned int x=0; x < src_w; x++)
				   for(unsigned int y=0; y < source.height; y++)
					{
						if ( (x-2) && (y-2) && (x != src_w-2) && (y != source.height-2)) //5x5 matrix!
						 {
						 numb = (long) (
											source.data[(y-2) * src_w + (x-2)] * kernel[0] +
											source.data[(y-2) * src_w + (x-1)] * kernel[1] +
											source.data[(y-2) * src_w +  x   ] * kernel[2] +
											source.data[(y-2) * src_w + (x+1)] * kernel[3] +
											source.data[(y-2) * src_w + (x+2)] * kernel[4] +
											source.data[(y-1) * src_w + (x-2)] * kernel[5] +
											source.data[(y-1) * src_w + (x-1)] * kernel[6] +
											source.data[(y-1) * src_w +  x   ] * kernel[7] +
											source.data[(y-1) * src_w + (x+1)] * kernel[8] +
											source.data[(y-1) * src_w + (x+2)] * kernel[9] +
											source.data[ y    * src_w + (x-2)] * kernel[10] +
											source.data[ y    * src_w + (x-1)] * kernel[11] +
											source.data[ y    * src_w +  x   ] * kernel[12] +
											source.data[ y    * src_w + (x+1)] * kernel[13] +
											source.data[ y    * src_w + (x+2)] * kernel[14] +
											source.data[(y+1) * src_w + (x-2)] * kernel[15] +
											source.data[(y+1) * src_w + (x-1)] * kernel[16] +
											source.data[(y+1) * src_w +  x   ] * kernel[17] +
											source.data[(y+1) * src_w + (x+1)] * kernel[18] +
											source.data[(y+1) * src_w + (x+2)] * kernel[19] +
											source.data[(y+2) * src_w + (x-2)] * kernel[20] +
											source.data[(y+2) * src_w + (x-1)] * kernel[21] +
											source.data[(y+2) * src_w +  x   ] * kernel[22] +
											source.data[(y+2) * src_w + (x+1)] * kernel[23] +
											source.data[(y+2) * src_w + (x+2)] * kernel[24]	);

						 if ( numb )
							numb /= (long)kernel[25];//normalization

						dest.data[y * src_w + x] = (S)numb;

						 }
						else
							dest.data[y * src_w + x] = (S)source.data[y * src_w + x];
				   }

			 }
			else if (kernel.getDim() == 7)
			 {
				for(unsigned int x=0; x < src_w; x++)
				   for(unsigned int y=0; y < source.height; y++)
					{
						if ( (x-3) && (y-3) && (x != src_w-3) && (y != source.height-3)) //7x7 matrix!
						 {
						 numb = (long) (
											source.data[(y-3) * src_w + (x-3)] * kernel[0] +
											source.data[(y-3) * src_w + (x-2)] * kernel[1] +
											source.data[(y-3) * src_w + (x-1)] * kernel[2] +
											source.data[(y-3) * src_w +  x   ] * kernel[3] +
											source.data[(y-3) * src_w + (x+1)] * kernel[4] +
											source.data[(y-3) * src_w + (x+2)] * kernel[5] +
											source.data[(y-3) * src_w + (x+3)] * kernel[6] +
											source.data[(y-2) * src_w + (x-3)] * kernel[7] +
											source.data[(y-2) * src_w + (x-2)] * kernel[8] +
											source.data[(y-2) * src_w + (x-1)] * kernel[9] +
											source.data[(y-2) * src_w +  x   ] * kernel[10] +
											source.data[(y-2) * src_w + (x+1)] * kernel[11] +
											source.data[(y-2) * src_w + (x+2)] * kernel[12] +
											source.data[(y-2) * src_w + (x+3)] * kernel[13] +
											source.data[(y-1) * src_w + (x-3)] * kernel[14] +
											source.data[(y-1) * src_w + (x-2)] * kernel[15] +
											source.data[(y-1) * src_w + (x-1)] * kernel[16] +
											source.data[(y-1) * src_w +  x   ] * kernel[17] +
											source.data[(y-1) * src_w + (x+1)] * kernel[18] +
											source.data[(y-1) * src_w + (x+2)] * kernel[19] +
											source.data[(y-1) * src_w + (x+3)] * kernel[20] +
											source.data[ y    * src_w + (x-3)] * kernel[21] +
											source.data[ y    * src_w + (x-2)] * kernel[22] +
											source.data[ y    * src_w + (x-1)] * kernel[23] +
											 source.data[ y    * src_w +  x   ] * kernel[24] +
											source.data[ y    * src_w + (x+1)] * kernel[25] +
											source.data[ y    * src_w + (x+2)] * kernel[26] +
											source.data[ y    * src_w + (x+3)] * kernel[27] +
											source.data[(y+1) * src_w + (x-3)] * kernel[28] +
											source.data[(y+1) * src_w + (x-2)] * kernel[29] +
											source.data[(y+1) * src_w + (x-1)] * kernel[30] +
											source.data[(y+1) * src_w +  x   ] * kernel[31] +
											source.data[(y+1) * src_w + (x+1)] * kernel[32] +
											source.data[(y+1) * src_w + (x+2)] * kernel[33] +
											source.data[(y+1) * src_w + (x+3)] * kernel[34] +
											source.data[(y+2) * src_w + (x-3)] * kernel[35] +
											source.data[(y+2) * src_w + (x-2)] * kernel[36] +
											source.data[(y+2) * src_w + (x-1)] * kernel[37] +
											source.data[(y+2) * src_w +  x   ] * kernel[38] +
											source.data[(y+2) * src_w + (x+1)] * kernel[39] +
											source.data[(y+2) * src_w + (x+2)] * kernel[40] +
											source.data[(y+2) * src_w + (x+3)] * kernel[41] +
											source.data[(y+3) * src_w + (x-3)] * kernel[42] +
											source.data[(y+3) * src_w + (x-2)] * kernel[43] +
											source.data[(y+3) * src_w + (x-1)] * kernel[44] +
											source.data[(y+3) * src_w +  x   ] * kernel[45] +
											source.data[(y+3) * src_w + (x+1)] * kernel[46] +
											source.data[(y+3) * src_w + (x+2)] * kernel[47] +
											source.data[(y+3) * src_w + (x+3)] * kernel[48]	);

						 if ( numb )
							numb /= (long)kernel[49];//normalization

						dest.data[y * src_w + x] = (S)numb;

						 }
						else
							dest.data[y * src_w + x] = (S)source.data[y * src_w + x];
				   }

			 }
			else
				return VIPRET_NOT_IMPLEMENTED;

		   return VIPRET_OK;
		 }


		static int doProcessing(vipFrameRGB24& source, vipFrameRGB24& dest, vipDFMatrix& kernel, bool clamp = true);
		static int doProcessing(vipFrameYUV420& source, vipFrameYUV420& dest, vipDFMatrix& kernel, bool clamp = true);
		static int doProcessing(vipFrameT<unsigned char>& source, vipFrameT<unsigned char>& dest, vipDFMatrix& kernel, bool clamp = true);


		static int doRotateKernel(vipDFMatrix& kernel);




		VIPRESULT importFrom(vipFrameYUV420& img);
		VIPRESULT importFrom(vipFrameRGB24& img);
		VIPRESULT importFrom(vipFrameT<unsigned char>& img);




};



#endif //__VIPLIB_VIPDIGITALFILTER_H__

