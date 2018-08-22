/**
 *  @class   vipFilterGeometric
 *
 *  @brief
 *
 *
 *  @bug
 *  @warning
 *  @todo
 *
 *  @see     vipFilter
 *  @example ../../tests/test_vipFilterGeometric.cpp
 *
 *  @version 0.75
 *  @date    12/07/2005 - 02/07/2008
 *  @author  Alessandro Polo - Nicola Conci
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




#ifndef __VIPLIB_VIPFILTERGEOMETRIC_H__
 #define __VIPLIB_VIPFILTERGEOMETRIC_H__

 #include "../vipDefs.h"
 #include "../vipFilter.h"
 #include "../vipFrameYUV420.h"
 #include "../vipFrameYUV444.h"
 #include "../vipFrameRGB24.h"
 #include "../vipFrameT.h"



class vipFilterGeometricParameters : public vipFilterParameters
{
	public:

		enum RUNMODE{ DO_NOTHING, ROTATE90, ROTATE180, ROTATE270, ROTATE, FLIP_VERTICAL, FLIP_HORIZONTAL, RESIZE, RESIZECANVAS };

	protected:

		RUNMODE runMode;

		float par_Rotation;
		unsigned int par_ResizeWidth;
		unsigned int par_ResizeHeight;
		bool par_forzeSize;
		

		friend class vipFilterGeometric;

	public:

		vipFilterGeometricParameters(RUNMODE mode = vipFilterGeometricParameters::DO_NOTHING);
		~vipFilterGeometricParameters() {}

		void reset();

		void setRunMode(RUNMODE mode) { runMode = mode; };
		RUNMODE getRunMode() { return runMode; };

		void setRotationDegree(float degree) { par_Rotation = degree; };
		void setResizeDimension(unsigned int width, unsigned int height) { par_ResizeWidth = width; par_ResizeHeight = height; };
		
		float getRotationDegree() { return par_Rotation; };
		unsigned int getResizeDimensionWidth() { return par_ResizeWidth; };
		unsigned int getResizeDimensionHeight() { return par_ResizeHeight; };

		void forceOutputSize(bool value = true) { par_forzeSize = value; };
		bool isForceOutputSizeEnabled() { return par_forzeSize; };


		VIPRESULT saveToStreamXML(FILE *fp);
		VIPRESULT loadFromStreamXML(FILE *fp);

};



class vipFilterGeometric :	public vipFilter
 {

 protected:

		/**
		 * @brief  Current parameters.
		 */
		vipFilterGeometricParameters* myParams;



 public:

		/**
		 * @brief  Default constructor, initialize parameters and superclasses.
		 * @param[in] initParams parameters for this module or NULL for defaults.
		 */
		vipFilterGeometric(vipFilterGeometricParameters* initParams = NULL );

		/**
		 * @brief Default destructor, free buffer.
		 */
		~vipFilterGeometric();

		float getFrameRate()  const { return 0; };
	//	virtual int setFrameRate(float );



		/**
		 * @brief  Set parameters for this filter.
		 *
		 * @param[in] initParams Instance of vipFilterGeometricParameters or NULL,
		 *                       NULL argument make function to create a new
		 *                       instance with default parameters.
		 *
		 * @return VIPRET_OK
		 */
		VIPRESULT setParameters(vipFilterGeometricParameters* initParams);

		/**
		 * @brief  Get parameters for this filter.
		 *
		 * @return pointer to vipFilterGeometricParameters instance.
		 */
		vipFilterGeometricParameters& getParameters() { return *myParams; };



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
				return setParameters(static_cast<vipFilterGeometricParameters*>(initParams));
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
		 * @brief Resize each frame to new dimension
		 *
		 * @param newdimX New video width.
		 * @param newdimY New video height.
		 * @param N Optional parameter in case a resize ratio is desired (N>1 -> upsample, N<1 -> downsample
		 * @return VIPRET_OK if success, VIPRET_ILLEGAL_USE if video is empty,
		 *			VIPRET_PARAM_ERR if parameters are out of range ]0, INT[,
		 *			VIPRET_INTERNAL_ERR else.
		 * @todo implement bilinear interpolation. the available one is simple pixel replication
		 */
		VIPRESULT resize(vipFrameYUV420& img, unsigned int dimX , unsigned int dimY);
		VIPRESULT resize(vipFrameYUV444& img, unsigned int dimX , unsigned int dimY);
		VIPRESULT resize(vipFrameRGB24& img, unsigned int dimX , unsigned int dimY);
		VIPRESULT resize(vipFrameT<unsigned char>& img, unsigned int dimX , unsigned int dimY);


		/**
		 * @brief Resize frames' canvas to new dimension, if smaller video will be cropped,
		 *			if greater new pixels will be in VIPDEF_PIXEL_COLOR.
		 *
		 * @param newdimX New canvas width.
		 * @param newdimY New canvas height.
		 *
		 * @return VIPRET_OK if success, VIPRET_ILLEGAL_USE if video is empty,
		 *			VIPRET_PARAM_ERR if parameters are out of range ]0, INT[,
		 *			VIPRET_INTERNAL_ERR else.
		 */
		VIPRESULT resizeCanvas(vipFrameYUV420& img, unsigned int newdimX, unsigned int newdimY);
		VIPRESULT resizeCanvas(vipFrameYUV444& img, unsigned int newdimX, unsigned int newdimY);
		VIPRESULT resizeCanvas(vipFrameRGB24& img, unsigned int newdimX, unsigned int newdimY);
		VIPRESULT resizeCanvas(vipFrameT<unsigned char>& img, unsigned int newdimX, unsigned int newdimY);

		/**
		 * @brief Resize frames' canvas to new dimension, if smaller video will be cropped,
		 *			if greater new pixels will be in VIPDEF_PIXEL_COLOR.
		 *
		 * @param newdimX New canvas width.
		 * @param newdimY New canvas height.
		 * @param defaultColor Color for new pixels (if canvas is greater than original).
		 *
		 * @return VIPRET_OK if success, VIPRET_ILLEGAL_USE if video is empty,
		 *			VIPRET_PARAM_ERR if parameters are out of range ]0, INT[,
		 *			VIPRET_INTERNAL_ERR else.
		 */
		VIPRESULT resizeCanvas(vipFrameYUV420& img, unsigned int newdimX , unsigned int newdimY, unsigned char& valY, unsigned char& valU, unsigned char& valV);
		VIPRESULT resizeCanvas(vipFrameYUV444& img, unsigned int newdimX , unsigned int newdimY, unsigned char& valY, unsigned char& valU, unsigned char& valV);
		VIPRESULT resizeCanvas(vipFrameRGB24& img, unsigned int newdimX , unsigned int newdimY, PixelRGB24 defaultColor);
		VIPRESULT resizeCanvas(vipFrameT<unsigned char>& img, unsigned int newdimX , unsigned int newdimY, unsigned char& val1, unsigned char& val2, unsigned char& val3);


		/**
		 * @brief Rotate each frame 90 degrees (right). [MultiThread]
		 *
		 * @return VIPRET_OK if success, VIPRET_ILLEGAL_USE if video is empty.
		 */
		VIPRESULT rotate90(vipFrameYUV420& img);
		VIPRESULT rotate90(vipFrameYUV444& img);
		VIPRESULT rotate90(vipFrameRGB24& img);
		VIPRESULT rotate90(vipFrameT<unsigned char>& img);


		/**
		 * @brief Rotate each frame 180 degrees (right). [MultiThread]
		 *
		 * @return VIPRET_OK if success, VIPRET_ILLEGAL_USE if video is empty.
		 */
		VIPRESULT rotate180(vipFrameYUV420& img);
		VIPRESULT rotate180(vipFrameYUV444& img);
		VIPRESULT rotate180(vipFrameRGB24& img);
		VIPRESULT rotate180(vipFrameT<unsigned char>& img);


		/**
		 * @brief Rotate each frame 270 degrees (right). [MultiThread]
		 *
		 * @return VIPRET_OK if success, VIPRET_ILLEGAL_USE if video is empty.
		 */
		VIPRESULT rotate270(vipFrameYUV420& img);
		VIPRESULT rotate270(vipFrameYUV444& img);
		VIPRESULT rotate270(vipFrameRGB24& img);
		VIPRESULT rotate270(vipFrameT<unsigned char>& img);


		/**
		 * @brief Rotate each frame on the right. [MultiThread]
		 *
		 * @param alpha degrees on the right
		 *
		 * @return VIPRET_OK if success, VIPRET_ILLEGAL_USE if video is empty.
		 */
		VIPRESULT rotate(vipFrameYUV420& img, float alpha);
		VIPRESULT rotate(vipFrameYUV444& img, float alpha);
		VIPRESULT rotate(vipFrameRGB24& img, float alpha);
		VIPRESULT rotate(vipFrameT<unsigned char>& img, float alpha);


		/**
		 * @brief Flip Horizontal each frame. [MultiThread]
		 *
		 * @return VIPRET_OK if success, VIPRET_ILLEGAL_USE if video is empty.
		 */
		VIPRESULT flipHorizontal(vipFrameYUV420& img);
		VIPRESULT flipHorizontal(vipFrameYUV444& img);
		VIPRESULT flipHorizontal(vipFrameRGB24& img);
		VIPRESULT flipHorizontal(vipFrameT<unsigned char>& img);


		/**
		 * @brief Flip Vertical each frame. [MultiThread]
		 *
		 * @return VIPRET_OK if success, VIPRET_ILLEGAL_USE if video is empty.
		 */
		VIPRESULT flipVertical(vipFrameYUV420& img);
		VIPRESULT flipVertical(vipFrameYUV444& img);
		VIPRESULT flipVertical(vipFrameRGB24& img);
		VIPRESULT flipVertical(vipFrameT<unsigned char>& img);



		/**
		 * @brief Process the frame with current settings and store in buffer.
		 *
		 * @param[in] img VIPLib Cache Frame to be processed.
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
		 * @param[in] img VIPLib Cache Frame to be processed.
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
		 * @param[in] img VIPLib Cache24 Frame to be processed.
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





























/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

		template <class T>
		static VIPRESULT rotate90(vipFrameT<T> *src, vipFrameT<T> *dst, bool clockDir)
		{
	
			return VIPRET_NOT_IMPLEMENTED;
		}


		template <class T>
		static VIPRESULT rotate180(vipFrameT<T> *src, vipFrameT<T> *dst)
		{
			for (unsigned int i=0; i < src.width*src.height; i++)      // reverse array
				dst.data[i] = src.data[src.width*src.height-1-i];

			return VIPRET_OK;

		/*  int xd,yd,x,y;

		  yd = dst.height - 1;

		  for(y = 0 ; y < src.height ; y++)
		  {
			xd = dst.width - 1;

			for(x = 0 ; x < src.width ; x++)
			{
			  dst.data[yd * dst.width + xd] = src.data[y * src.width + x];
			  xd--;
			}

			yd--;
		  }
		*/
		}

		template <class T>
		static VIPRESULT mirror(vipFrameT<T> *src, vipFrameT<T> *dst)
		{
			unsigned int width = src.width;

			for ( unsigned int y=0; y < src.height; y++ ) // single pixel copy routine
			 for ( unsigned int x=0; x < src.width; x++ )
				dst->data[x+y*width] = src.data[y*width + (width-1)-x];

			return VIPRET_OK;
		/*  int xd,x,y;
		  (void)dst.height;

		  for(y = 0 ; y < src.height ; y++)
		  {
			xd = dst.width - 1;

			for(x = 0 ; x < src.width ; x++)
			{
			  dst.data[y * dst.width + xd] = src.data[y * src.width + x];
			  xd--;
			}
		  }
		*/
		}

		template <class T>
		static VIPRESULT flip(vipFrameT<T> *src, vipFrameT<T> *dst)
		{
			int yd,y;

			yd = dst.height - 1;

			for(y = 0 ; y < src.height ; y++)
			 {
				memcpy(dst.data+yd*dst.width,src.data+y*src.width,src.width * sizeof(T));
				yd--;
			 }
			return VIPRET_OK;
		}

/////////////////////////////////////////////////////////////////////////////////////




};


#endif //__VIPLIB_VIPFILTERGEOMETRIC_H__

