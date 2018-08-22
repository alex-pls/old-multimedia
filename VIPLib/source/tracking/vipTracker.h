/**
 *  @class   vipTracker
 *
 *  @brief

 *  @bug
 *  @warning
 *  @todo
 *
 *  @see
 *
 *  @version 2.0.0
 *  @date    2007-10-08
 *  @author  Alessandro Polo (updated and converted into C++ Class)
 *           Nicola Piotto (written)
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

#ifndef __VIPLIB_VIPTRACKER_H__
 #define __VIPLIB_VIPTRACKER_H__


#include <vipDefs.h>

#include <vipFrameRGB24.h>
#include <vipFrameYUV420.h>

 #include <vipOutput.h>


 #include "vipMovingObject.h"


class vipTracker : public vipOutput
{
	protected:

		//for Bg color conversion
		unsigned char* background;
		unsigned char* BgRGB;
		float* BgHSV;

		unsigned int fIndex;

		//for frame diff
		float* previous_buff;

		//for blob_labelling
		int max_lbl; //max available label for the operation
		int i_l_v; //inter label value=distance in ldg between 2 consecutive label

		//for tracking
		unsigned char* previous_labelled;


		//for shadow&highlight remove
		double range_S;	  //saturation range in the current frame
		double average_S;  //average saturation value, threshold for shadow & highlight mask computation

		vipMovingObject* Global_Object_array;

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

	protected:

		// static like
		//support image strucure..
		vipFrameYUV420 sup_img;

		unsigned char* bufferRGB;	//buffer in diff color space
		float* bufferHSV;

		float* V_temp;

		unsigned char* shadow;	//shadow mask
		unsigned char* highlight;	//highlight mask
		unsigned char* ghost;


		unsigned char* bufferBG;   //buffer for BgSubstraction
		unsigned char* bufferDIFF;    //buffer for frame differencing

		int motion_px;

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

	protected:

		//int FrameDiff(vipFrameYUV420 img1, unsigned char* img2, unsigned char* data, int width, int height);
		int FrameDiff(float* img1, float* img2, unsigned char* data, int width, int height);

		int Y_BgSubstraction(vipFrameYUV420 buffer,  unsigned char* bg, unsigned char* data,int th);

		int V_BgSubstraction(float* buffer, float* bg, unsigned char* data, int width, int height, double th);
		//int V_BgSubstraction(double* buffer,  double* bg, unsigned char* data, int width, int height, double th);

		int ShadowMask(unsigned char* orig_frame, float* bufferHSV, int width, int height, unsigned char* out);

		int HighLightMask(unsigned char* orig_frame, float* bufferHSV, int width, int height, unsigned char* out);

		int Mode_previous(int id_row, int id_col, int width,int height);


		int Blob_Labeling(unsigned char* bufferIn,unsigned char* bufferOut,int width,int height);

		int Cue_Motion_Track(void);

		int Blob_Labeling(unsigned char* bufferIn,unsigned char* bufferOut,int width,int height,int *label);

		int Blob_tracking(unsigned char* Input,unsigned char* output,float* Original,int nr_lbl,int* label,int width, int height,int frame_nr);

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

	public:

		vipTracker();
		~vipTracker();


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

	vipMovingObject* getMovingObjectArray() { return Global_Object_array; };

	unsigned int getMovingObjectArraySize()
	{
		//int max_global_obj_nr = 25; //dimension of global_obj_array
		return 25;
	}

	int setHeight(unsigned int height);
	int setWidth(unsigned int width);


	vipFrameYUV420& vipTracker::getSupImg();


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

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
		VIPRESULT importFrom(vipFrameRGB24& img) { return VIPRET_NOT_IMPLEMENTED; };

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
		VIPRESULT importFrom(vipFrameT<unsigned char>& img) { return VIPRET_NOT_IMPLEMENTED; };


/* //WHAAT?
//for shadow&highlight remove
//				double range_S;	  //saturation range in the current frame
//				double average_S;  //average saturation value, threshold for shadow & highlight mask computation
int setSaturation(double range_S, double average_S);
*/

//int Motion_Track(vipCodec_RAW& video_in, vipCodec_RAW& video_out, vipCodec_RAW& videosmall);


};

#endif //__VIPLIB_VIPTRACKER_H__





