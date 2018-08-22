/**
 *  @class   vipUtility
 *
 *  @brief   This class implements static methods used by many VIPLib modules as:
 *
 *            - PixelPacked <-> ChannelPacked conversion
 *            - ColorSpace conversions
 *            - sleep function (multi-platform)
 *
 *           Syntax: vipUtility::methodName(arg);
 *
 *
 *  @bug
 *  @warning
 *  @todo
 *
 *  @see
 *
 *  @example ../tests/test_vipUtility.cpp
 *
 *  @version 1.0.0
 *  @date    17/09/2005
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



/* conversion routines
void conv_420p_rgb96 (int width, int height, void *src, void *dst);
void conv_420p_grey  (int width, int height, void *src, void *dst);
void conv_rgb24_rgb96(int width, int height, void *src, void *dst);
void conv_rgb24_grey(int width, int height, void *src, void *dst);
void conv_rgb32_rgb96(int width, int height, void *src, void *dst);
void conv_rgb32_grey (int width, int height, void *src, void *dst);

void conv_bgr24_rgb96(int width, int height, void *src, void *dst);


*/

// sleeping


#ifndef __VIPLIB_VIPUTILITY_H__
 #define __VIPLIB_VIPUTILITY_H__

 #include "vipDefs.h"
 #include "vipFrameT.h"
 #include "vipFrameYUV420.h"
 #include "vipFrameRGB24.h"


class vipUtility
 {
	protected:

		//static members only
		vipUtility() {}

	public:

		virtual ~vipUtility() {}


		static double getTime_usec();
		static void vipSleep(long millisec);


		static char* getTypeNameFromClassTypeID(int classType_id);

		static VIPRESULT conv_PixelRGB24toPlanarYUV444(unsigned char* RGB_Packet_ptr, unsigned char* YUV_Planar_ptr, unsigned int width, unsigned int height);
		static VIPRESULT conv_PlanarYUV444toPixelRGB24(unsigned char* YUV_Planar_ptr, unsigned char* RGB_Packed_Ptr, unsigned int width, unsigned int height);
		static VIPRESULT conv_PixelRGB24toPixelHSV(unsigned char* RGB_Packet_ptr, PixelHSV* HSV_Packet_ptr, unsigned int width, unsigned int height, double* sat_range, double* sat_average);
		static VIPRESULT conv_PixelHSVtoPixelRGB24(PixelHSV* HSV_Pixel_ptr, unsigned char* RGB_Packet_ptr, unsigned int width, unsigned int height);
		static VIPRESULT conv_PlanarYUV444toPixelHSV(unsigned char* YUV_Planar_ptr, PixelHSV* HSV_Packet_ptr, unsigned int width, unsigned int height, double* sat_range, double* sat_average);
		static VIPRESULT conv_PlanarYUV444toPlanarYUV420(unsigned char* in, unsigned char* out, unsigned int width, unsigned int height); // was UV_downsampling() in VipSampling.cpp
		static VIPRESULT conv_PlanarYUV420toPlanarYUV444(unsigned char* in, unsigned char* out, unsigned int width, unsigned int height, bool use_slow_interp = true);	// -> conv_PlanarYUV420toPlanarYUV444(), was UV_upsampling()

		// MarcoVerza added:
		static VIPRESULT conv_PlanarYUV444toPackedUYVY( unsigned char *in, unsigned char *out, unsigned int width, unsigned int height );
		static VIPRESULT rescale_plane( unsigned char *in, unsigned char *out, unsigned int inWidth, unsigned int inHeight, unsigned int outWidth, unsigned int outHeight );


///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
////// FUNZIONI DA VERIFICARE SINGOLARMENTE!!!!! //////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
//			template<class T, class S>
//		static VIPRESULT conv_PixelPackedToChannelPacked(T* out, S* in, unsigned int width, unsigned int height, unsigned int channels = 3)
//		 {
//			if ( out == NULL || in == NULL || width == 0 || height == 0)
//				return VIPRET_PARAM_ERR;
//
//			T* outPtr;
//			S* inPtr;
//			unsigned int i;
//
//			for (unsigned int ch=0; ch < channels; ch++)
//			 {
//				inPtr = in + ch;
//				outPtr = out + width*height*ch;
//
//				for (i=0; i< width*height; i++)
//				 {
//					*outPtr = (T)*inPtr;
//					outPtr++;
//					inPtr+= 3;
//				 }
//			 }
//
//			return VIPRET_OK;
//		 };
//
//
//
//			template<class T, class S>
//		static VIPRESULT conv_ChannelPackedToPixelPacked(T* out, S* in, unsigned int width, unsigned int height, unsigned int channels)
//		 {
//			if ( out == NULL || in == NULL || width == 0 || height == 0)
//				return VIPRET_PARAM_ERR;
//
//			T* outPtr;
//			S* inPtr;
//			unsigned int i;
//
//			for (unsigned int ch=0; ch < channels; ch++)
//			 {
//				inPtr = in + width*height*ch;
//				outPtr = out + ch;
//
//				for (i=0; i< width*height; i++)
//				 {
//					*outPtr = (T)*inPtr;
//					inPtr++;
//					outPtr+= 3;
//				 }
//			 }
//
//			return VIPRET_OK;
//		 };
//
//
//			template<class RGB, class YUV>
//		static VIPRESULT conv_PixelRGBtoPlanarYUV(RGB* RGB_Packed_Ptr, YUV* YUV_Planar_ptr, unsigned int width, unsigned int height, unsigned int formula = 0)
//		 {
//			switch ( formula )
//			 {
//				case 0:		// microsoft formula
//				 	{
//						RGB* rgb = RGB_Packed_Ptr;
//						YUV* y = YUV_Planar_ptr;
//						YUV* u = YUV_Planar_ptr + width*height;
//						YUV* v = YUV_Planar_ptr + width*height*2;
//
//						cout<< "F0_" << endl;
//
//						for (int i=0; i<width*height*3; i++, y++, u++, v++)
//						 {
//							 *y = (YUV)( (( rgb[i] *  66 + rgb[i+1] * 129 + rgb[i+2] *  25 + 128 ) >> 8) + 16  );
//							 *u = (YUV)( (( rgb[i] * -38 + rgb[i+1] *  74 + rgb[i+2] * 112 + 128 ) >> 8) + 128 );
//							 *v = (YUV)( (( rgb[i] * 112 + rgb[i+1] *  94 + rgb[i+2] *  18 + 128 ) >> 8) + 128 );
//							 rgb = rgb+3;
//						 }
//
//					}
//					break;
//
//				case 1:		// www.fourcc.org
//				 	{
//						RGB* rgb = RGB_Packed_Ptr;
//						YUV* y = YUV_Planar_ptr;
//						YUV* u = YUV_Planar_ptr + width*height;
//						YUV* v = YUV_Planar_ptr + width*height*2;
//
//						cout<< "F1_" << endl;
//
//						for (int i=0; i<width*height*3; i++, y++, u++, v++)
//						 {
//							 *y = (YUV)( 0.257 * rgb[i] + 0.504 * rgb[i+1] + 0.098 * rgb[i+2] + 16 );
//							 *u = (YUV)( 0.439 * rgb[i] - 0.368 * rgb[i+1] + 0.071 * rgb[i+2] + 128 );
//							 *v = (YUV)(-0.148 * rgb[i] - 0.291 * rgb[i+1] + 0.439 * rgb[i+2] + 128 );
//							 rgb = rgb+3;
//						 }
//
//					}
//					break;
//
//				case 2:		//
//				 	{
//						RGB* rgb = RGB_Packed_Ptr;
//						YUV* y = YUV_Planar_ptr;
//						YUV* u = YUV_Planar_ptr + width*height;
//						YUV* v = YUV_Planar_ptr + width*height*2;
//
//cout<< "F2_" << endl;
//
//						for (int i=0; i<width*height*3; i++, y++, u++, v++)
//						 {
//cout<< "F2_1" << endl;
//							 *y = (YUV)( rgb[i] * .299 + rgb[i+1] * .587 + rgb[i+2] * .114 );
//cout<< "F2_2" << endl;
//							 *u = (YUV)( rgb[i] *-.169 + rgb[i+1] *-.332 + rgb[i+2] * .500 + 128. );
//cout<< "F2_3" << endl;
//							 *v = (YUV)( rgb[i] * .500 + rgb[i+1] * .419 + rgb[i+2] *-.0813 + 128. );
//cout<< "F2_4" << endl;
//							 rgb = rgb+3;
//cout<< "F2_5" << endl;
//						 }
//
//					}
//					break;
//
//				default:
//					return VIPRET_PARAM_ERR;
//			 }
//
//			return VIPRET_OK;
//		 };
//
//
//			template<class RGB, class YUV>
//		static VIPRESULT conv_PlanarYUVtoPixelRGB(YUV* YUV_Planar_ptr, RGB* RGB_Packed_Ptr, unsigned int width, unsigned int height, unsigned int formula = 0)
//		 {
//			switch ( formula )
//			 {
//				case 0:		// microsoft formula
//				 	{
//						RGB* rgb = RGB_Packed_Ptr;
//						YUV* y = YUV_Planar_ptr;
//						YUV* u = YUV_Planar_ptr + width*height;
//						YUV* v = YUV_Planar_ptr + width*height*2;
//
//						for (unsigned int i=0; i<width*height*3; i++, y++, u++, v++)
//						 {
//							 rgb[i]   = (RGB)( (298* (*y-16)                 + 409* (*v-128) + 128) >> 8);
//							 rgb[i+1] = (RGB)( (298* (*y-16) - 100* (*u-128) - 208* (*v-128) + 128) >> 8);
//							 rgb[i+2] = (RGB)( (298* (*y-16) + 516* (*u-128)                 + 128) >> 8 );
//							 rgb = rgb+3;
//						 }
//
//					}
//					break;
//
//				case 1:	// www.fourcc.org
//				 	{
//						RGB* rgb = RGB_Packed_Ptr;
//						YUV* y = YUV_Planar_ptr;
//						YUV* u = YUV_Planar_ptr + width*height;
//						YUV* v = YUV_Planar_ptr + width*height*2;
//
//						for (unsigned int i=0; i<width*height*3; i++, y++, u++, v++)
//						 {
////							 rgb[i]   = (RGB)(  );
////BUG 							 rgb[i+1] = (RGB)(  );
////							 rgb[i+2] = (RGB)(  );
//							 rgb = rgb+3;
//						 }
//
//					}
//					break;
//
//				case 2:
//				 	{
//						RGB* rgb = RGB_Packed_Ptr;
//						YUV* y = YUV_Planar_ptr;
//						YUV* u = YUV_Planar_ptr + width*height;
//						YUV* v = YUV_Planar_ptr + width*height*2;
//
//						for (unsigned int i=0; i<width*height*3; i++, y++, u++, v++)
//						 {
//							 rgb[i]   = (RGB)( *y + (*v - 128) * 1.4075 );
//							 rgb[i+1] = (RGB)( *y - (*u - 128) * 0.3455 + (*v - 128) * 0.7196 );
//							 rgb[i+2] = (RGB)( *y + (*u - 128) * 1.7790 );
//							 rgb = rgb+3;
//						 }
//
//					}
//					break;
//
//				default:
//					return VIPRET_PARAM_ERR;
//			 }
//
//			return VIPRET_OK;
//		 };
//
//
//
//
//			template<class T, class S>
//		static VIPRESULT conv_bgr_rgb(T* out, S* in, unsigned int width, unsigned int height)
//		 {
//			if ( out == NULL || in == NULL || width == 0 || height == 0)
//				return VIPRET_PARAM_ERR;
//
//			T* outPtr = out + 2;
//			S* inPtr = in;
//
//			for (unsigned int i=0; i< width*height; i++)
//			 {
//				*(outPtr--) = *(inPtr++);
//				*(outPtr--) = *(inPtr++);
//				*(outPtr) = *(inPtr++);
//				outPtr += 5;
//			 }
//
//			return VIPRET_OK;
//		 };
//
//
//
//			template<class T, class S>
//		static VIPRESULT conv_linear(T* out, S* in, double* matrix, unsigned int width, unsigned int height)
//		 {
//			if ( out == NULL || in == NULL || width == 0 || height == 0)
//				return VIPRET_PARAM_ERR;
//
//			T* outPtr = out;
//			S* inPtr = in;
//
//			for (unsigned int i=0; i < width*height; i++)
//			 {
//				*(outPtr++) = *inPtr * matrix[0] + *(inPtr+1) * matrix[1] + *(inPtr+2) * matrix[2];
//				*(outPtr++) = *inPtr * matrix[3] - *(inPtr+1) * matrix[4] - *(inPtr+2) * matrix[5];
//				*(outPtr++) = *inPtr * matrix[6] - *(inPtr+1) * matrix[7] + *(inPtr+2) * matrix[8];
//				inPtr += 3;
//			 }
//
//			return VIPRET_OK;
//		 };
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
//
//
////TEST e finire anche con altri, tra l'altro hanno errori...........
//
//
///////////////////////////////////////////////////////////////
//			template<class T, class S>
//		static VIPRESULT conv_rgb_yuv(T* out, S* in, unsigned int width, unsigned int height);
//			template<class T, class S>
//		static VIPRESULT conv_yuv_rgb(T* out, S* in, unsigned int width, unsigned int height);
//
///////////////////////////////////////////////////////////////
//			template<class T, class S>
//		static VIPRESULT conv_rgb_yiq(T* out, S* in, unsigned int width, unsigned int height);
//			template<class T, class S>
//		static VIPRESULT conv_yiq_rgb(T* out, S* in, unsigned int width, unsigned int height);
//
///////////////////////////////////////////////////////////////
//			template<class T, class S>
//		static VIPRESULT conv_rgb_xyz(T* out, S* in, unsigned int width, unsigned int height);
//			template<class T, class S>
//		static VIPRESULT conv_xyz_rgb(T* out, S* in, unsigned int width, unsigned int height);
//
///////////////////////////////////////////////////////////////
//			template<class T, class S>
//		static VIPRESULT conv_rgb_smpte_c(T* out, S* in, unsigned int width, unsigned int height);
//			template<class T, class S>
//		static VIPRESULT conv_smpte_c_rgb(T* out, S* in, unsigned int width, unsigned int height);
//
///////////////////////////////////////////////////////////////
//			template<class T, class S>
//		static VIPRESULT conv_rgb_bt709(T* out, S* in, unsigned int width, unsigned int height);
//			template<class T, class S>
//		static VIPRESULT conv_bt709_rgb(T* out, S* in, unsigned int width, unsigned int height);
//
///////////////////////////////////////////////////////////////
//			template<class T, class S>
//		static VIPRESULT conv_rgb_smpte240m(T* out, S* in, unsigned int width, unsigned int height);
//			template<class T, class S>
//		static VIPRESULT conv_smpte240m_rgb(T* out, S* in, unsigned int width, unsigned int height);
//
///////////////////////////////////////////////////////////////
//
//
//
//		static VIPRESULT conv_rgb24_420p(vipFrameRGB24& img, void* dataOut);
////		static VIPRESULT conv_rgb24_420p(vipFrameRGB24& img, void *dsty, void *dstu, void *dstv);
//
////		static void conv_420p_rgb96(int width, int height, void* src, void* dst);
//		static void conv_420p_grey(int width, int height, void *src, void *dst);
//
////		static VIPRESULT conv_420i_rgb24(void* dataIn, vipFrameRGB24& img);
//
//
//		static void conv_rgb24_rgb96(void *src, unsigned char *dst, unsigned int width, unsigned int height);
//		static void conv_bgr24_rgb96(void *src, unsigned char *dst, unsigned int width, unsigned int height);
//
//		static void conv_rgb24_rgb96_(void *src, int *dst, unsigned int width, unsigned int height);
//
//
//		static void conv_rgb32_rgb96(int width, int height, void *src, void *dst);



 };


#endif //__VIPLIB_VIPUTILITY_H__

