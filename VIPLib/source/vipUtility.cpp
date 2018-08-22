/** @file vipUtility.cpp
 *
 * File containing methods for the 'vipUtility' class.
 * The header for this class can be found in vipUtility.h, check that file
 * for class description.
 *
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




#include "vipUtility.h"

#include <stdio.h>
#include <cmath>
//#include "../include/ccvt/ccvt.h"



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#include <string.h>
char* vipUtility::getTypeNameFromClassTypeID(int classType_id)
 {
	char* ret = new char[32];

	switch( classType_id )
	 {
		case VIPCLASS_TYPE_FRAME	: strcpy(ret, "vipFrame");
		case VIPCLASS_TYPE_BUFFER	: strcpy(ret, "vipBuffer");
		case VIPCLASS_TYPE_INPUT	: strcpy(ret, "vipInput");
		case VIPCLASS_TYPE_OUTPUT	: strcpy(ret, "vipOutput");
		case VIPCLASS_TYPE_FILTER	: strcpy(ret, "vipFilter");
		case VIPCLASS_TYPE_CODEC	: strcpy(ret, "vipCodec");
		case VIPCLASS_TYPE_VISION	: strcpy(ret, "vipVision");
		default						: strcpy(ret, "UNKNOWN");
	 }
	return ret;
 }


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/**
* @brief  Make the color space conversion
*
* @param[YUV_Planar_ptr] in structure in YUV444 color space
* @param[RGB_Packed_Ptr] out structure in RGB24 color space
* @return VIPRET_OK,....
*/
VIPRESULT vipUtility::conv_PlanarYUV444toPixelRGB24(unsigned char* YUV_Planar_ptr, unsigned char* RGB_Packed_Ptr, unsigned int width, unsigned int height)
{
 // microsoft formula

 unsigned char* rgb = RGB_Packed_Ptr;
 unsigned char* y = YUV_Planar_ptr;
 unsigned char* u = YUV_Planar_ptr+width*height;
 unsigned char* v = YUV_Planar_ptr+width*height*2;
 double r,g,b;

 for (unsigned int i=0; i < width*height*3; i+=3, y++, u++, v++)
 {
  r = (double)( (298*(*y-16)                + 409*(*v-128) + 128) >> 8);
  g = (double)( (298*(*y-16) - 100*(*u-128) - 208*(*v-128) + 128) >> 8);
  b = (double)( (298*(*y-16) + 516*(*u-128)                + 128) >> 8);


  //clipping of the value in the range 0-255

  if(r<0)r=0;
  if(r>255)r=255;
  if(g<0)g=0;
  if(g>255)g=255;
  if(b<0) b=0;
  if(b>255) b=255;

  rgb[i] = (unsigned char)r;
  rgb[i+1] = (unsigned char)g;
  rgb[i+2] = (unsigned char)b;
 }


 return VIPRET_OK;

}


/**
* @brief  Make the color space conversion
*
* @param[RGB_Packed_Ptr] in structure in RGB24 color space
* @param[YUV_Planar_ptr] out structure in YUV444 color space
* @
* @return VIPRET_OK,....
*/
VIPRESULT vipUtility::conv_PixelRGB24toPlanarYUV444(unsigned char* RGB_Packet_ptr, unsigned char* YUV_Planar_ptr, unsigned int width, unsigned int height)
{
 // microsoft formula

 unsigned char* rgb = RGB_Packet_ptr;
 unsigned char* y = YUV_Planar_ptr;
 unsigned char* u = YUV_Planar_ptr+width*height;
 unsigned char* v = YUV_Planar_ptr+width*height*2;
 double Y,U,V;

 for (unsigned int i=0; i < width*height*3; i+=3, y++, u++, v++)
 {
  Y = (double)( ( ( 66*rgb[i] + 129*rgb[i+1] + 25*rgb[i+2] + 128 ) >> 8) + 16  );
  U = (double)( ( ( -38*rgb[i] - 74*rgb[i+1] + 112*rgb[i+2] + 128 ) >> 8) + 128 );
  V = (double)( ( ( 112*rgb[i] - 94*rgb[i+1] - 18*rgb[i+2] + 128 ) >> 8) + 128 );

  //printf("RGB %d %d %d",(int)rgb[i],(int)rgb[i+1],(int)rgb[i+2]);getchar();
  //clipping of the value in the range 0-255
  if(Y<0)	 Y=0;
  if(Y>255)Y=255;
  if(U<0)U=0;
  if(U>255)U=255;
  if(V<0)V=0;
  if(V>255)V=255;


  *y = (unsigned char)Y;
  *u = (unsigned char)U;
  *v = (unsigned char)V;
 }
 return VIPRET_OK;

}


/**
* @brief  Make the color space conversion
*
* @param[RGB_Packed_Ptr] in structure in RGB888 color space
* @param[HSV_Packet_ptr] out structure in HSVpacket color space
* @
* @return VIPRET_OK,....
*/
VIPRESULT vipUtility::conv_PixelRGB24toPixelHSV(unsigned char* RGB_Packet_ptr, PixelHSV* HSV_Packet_ptr, unsigned int width, unsigned int height, double* sat_range, double* sat_average)
{
 int* rgb=new int[3];
 int tmp;
 double temp=0;
 float S_min = 0;   //need to calculate the saturation range in the frame
 float S_max = 0;
 float H,S,V;

 double R,G,B;
 double min, max, delta;

 for(unsigned int i = 0; i < width * height * 3; i+=3)
 {


  rgb[0] = (int)RGB_Packet_ptr[i];     //red
  rgb[1] = (int)RGB_Packet_ptr[i+1];	 //green
  rgb[2] = (int)RGB_Packet_ptr[i+2];//blue

  R = rgb[0];
  G = rgb[1];
  B = rgb[2];

  //calculation of min & max in rgb
  for(int j = 0; j < 2; j++)

   if(rgb[j] >= rgb[j+1])
   {
	tmp = rgb[j];
	rgb[j] = rgb[j+1];
	rgb[j+1] = tmp;
   }

   max = (double)rgb[2];

   if(rgb[0] >= rgb[1])

	min = (double)rgb[1];

   else
	min = (double)rgb[0];

   V = max;
   delta = max - min;

   // Calculate saturation: saturation is 0 if r, g and b are all 0
   if (V == 0.0)

	S = 0.0;

   else
	S = delta / V;

   if (S==0.0)
	H = 0.0;    // should be Achromatic: When s = 0, h is undefined but..
   else       // Chromatic
	if (R == V)  // between yellow and magenta [degrees]

	 H=60.0*(G-B)/delta;

	else

	 if (G == V)  // between cyan and yellow

	  H = 120.0+60.0*(B-R)/delta;

	 else // between magenta and cyan

	  H = 240.0+60.0*(R-G)/delta;

	 //if ((int)H < 0) H = H+360.0;
	 if((int)H<0) H +=360.0;
	 if((int)H>=360) H-=360.0;

	 HSV_Packet_ptr[i/3].hue = H;
	 HSV_Packet_ptr[i/3].sat = S*255;
	 HSV_Packet_ptr[i/3].val = V /* /255 */;


	 if(S < S_min) S_min = S;
	 if(S > S_max) S_max = S;
	 temp+=S;  //to compute average S in the frame, used as threshold for shadow&highlight detection

 }
 	*sat_range = S_max - S_min;
 	*sat_average = temp/(width*height);



 return VIPRET_OK;
}


/**
* @brief  Make the color space conversion
*
* @param[YUV_Planar_ptr] in structure in HSVpacket color space
* @param[RGB_Packed_Ptr] out structure in RGB888 color space
* @return VIPRET_OK,....
*/
VIPRESULT vipUtility::conv_PixelHSVtoPixelRGB24( PixelHSV* HSV_Pixel_ptr, unsigned char* RGB_Packet_ptr, unsigned int width, unsigned int height)
{

 unsigned char* rgb = RGB_Packet_ptr;
 int j;
 float f, p, q, t,R,G,B;
 float H,S,V;

 for(unsigned int i = 0; i < (width*height*3); i+=3)
 {
	 H = HSV_Pixel_ptr[i/3].hue;
	 S = (float)(HSV_Pixel_ptr[i/3].sat)/(float)(255);
	 V = HSV_Pixel_ptr[i/3].val;

  //printf("%d ",i);getchar();

  if( S == 0 ) {
   // achromatic (grey)
   R =  V;
   G =  V;
   B =  V;
   //printf("HSV %f %f %f, RGB %d %d %d",H,S,V,(int)RGB_Packed_ptr[i],(int)RGB_Packed_ptr[i+1],(int)RGB_Packed_ptr[i+2]);getchar();
   //printf("achromatic\n");

   goto label;
  }

  H /= 60;			// sector 0 to 5
  j = floor( H );
  f = H - j;			// factorial part of h
  p = V * ( 1 - S );
  q = V * ( 1 - S * f );
  t = V * ( 1 - S * ( 1 - f ) );

  switch( j ) {
  case 0:
   R = V;
   G = t;
   B = p;
   //printf("case1\n");
   break;

  case 1:
   R = q;
   G = V;
   B = p;
   //printf("case2\n");
   break;

  case 2:
   R = p;
   G = V;
   B = t;
   //printf("case3\n");
   break;

  case 3:
   R = p;
   G = q;
   B = V;
   //printf("case4\n");
   break;

  case 4:
   R = t;
   G = p;
   B = V;
   //printf("case5\n");
   break;

  default:		// case 5:
   R = V;
   G = p;
   B = q;
   //printf("case6\n");


  }
  //printf("%d %d",width, height);
  //printf("HSV %f %f %f ", H*60,S,V);
  //printf("RGB %f %f %f" , R*255, G*255, B*255);getchar();
label:
  rgb[i]= (unsigned char)(R);
  rgb[i+1]= (unsigned char)(G);
  rgb[i+2]= (unsigned char)(B);
  //printf("RGB %d %d %d" , (int)rgb[i], (int)rgb[i+1], (int)rgb[i+2]);getchar();


 }

 return VIPRET_OK;
}


/**
* @brief  Make the color space conversion
*
* @param[YUV_Planar_ptr] in structure in YUV444 color space
* @param[HSV_Packet_Ptr] out structure in HSV color space
* @return VIPRET_OK,....
*/
VIPRESULT vipUtility::conv_PlanarYUV444toPixelHSV(unsigned char* YUV_Planar_ptr, PixelHSV* HSV_Packet_ptr, unsigned int width, unsigned int height, double* sat_range, double* sat_average)
{
	//not fully tested..
 unsigned char* y = YUV_Planar_ptr;
 unsigned char* u = YUV_Planar_ptr+width*height;
 unsigned char* v = YUV_Planar_ptr+width*height*2;

 int* rgb = new int[3];
 float min, max, delta;
 double R,G,B;
 float H,S,V;

 int tmp;
 float temp=0;
 float S_min = 0;   //need to calculate the saturation range in the frame
 float S_max = 0;

 //calculation of RGB values from YUV
 for (unsigned int i=0; i < width*height*3; i+=3, y++, u++, v++)
 {
  R = (double)( (298*(*y-16)                + 409*(*v-128) + 128) >> 8);
  G = (double)( (298*(*y-16) - 100*(*u-128) - 208*(*v-128) + 128) >> 8);
  B = (double)( (298*(*y-16) + 516*(*u-128)                + 128) >> 8);


  //clipping of the value in the range 0-255

  if(R<0)R=0;
  if(R>255)R=255;
  if(G<0)G=0;
  if(G>255)G=255;
  if(B<0) B=0;
  if(B>255) B=255;

  rgb[0] = (int)R;
  rgb[1] = (int)G;
  rgb[2] = (int)B;


  //calculation from RGB to HSV

  //calculation of min & max in rgb
  for(int j = 0; j < 2; j++)

   if(rgb[j] >= rgb[j+1])
   {
	tmp = rgb[j];
	rgb[j] = rgb[j+1];
	rgb[j+1] = tmp;
   }

   max = (double)rgb[2];

   if(rgb[0] >= rgb[1])

	min = (double)rgb[1];

   else
	min = (double)rgb[0];

   V = max;
   delta = max - min;

   // Calculate saturation: saturation is 0 if r, g and b are all 0
   if (V == 0.0)

	S = 0.0;

   else
	S = delta / V;

   if (S==0.0)
	H = 0.0;    // should be Achromatic: When s = 0, h is undefined but..
   else       // Chromatic
	if (R == V)  // between yellow and magenta [degrees]

	 H=60.0*(G-B)/delta;

	else

	 if (G == V)  // between cyan and yellow

	  H = 120.0+60.0*(B-R)/delta;

	 else // between magenta and cyan

	  H = 240.0+60.0*(R-G)/delta;

   if((int)H<0) H +=360.0;
   if((int)H>=360) H-=360.0;

   //memorize value in out buffer..
   unsigned int pixindex = i/3;
   HSV_Packet_ptr[pixindex].hue = H;
   HSV_Packet_ptr[pixindex].sat = S*255;
   HSV_Packet_ptr[pixindex].val = V/*/255*/;

   //computing average value and variation range for the saturation..
   //used as threshold for shadow&highlight detection

   if(S < S_min) S_min = S;
   if(S > S_max) S_max = S;
   temp+=S;

 }

 *sat_range = S_max - S_min;
 *sat_average = temp / (width*height);

 delete[] rgb;

 return VIPRET_OK;
}

/**
* @brief  Make the downsampling of crominance component
*
* @param[in] in structure in YUV444 color space
* @param[out] out structure in YUV420 color space
*/
VIPRESULT vipUtility::conv_PlanarYUV444toPlanarYUV420(unsigned char* in, unsigned char* out, unsigned int width, unsigned int height) // was UV_downsampling() in VipSampling.cpp
{
	//memcpy( out, in, width*height*sizeof(unsigned char) );
//return; //????
	//memcpy(out,in,width*height);
	unsigned char* tmp = new unsigned char[width*height*3/2];

	// Fixed by Marco Verza, was:
	//memset(tmp,128,width*height*3/2);
	// changed to:
	memcpy(tmp, in, width*height);

	for(unsigned int row=0; row<height; row+=2)
	{
		for(unsigned int col=0; col<width; col+=2)
			{
			tmp[(width*height)+(row/2)*(width/2)+col/2] = in[(width*height)+row*width+col];
			tmp[(5*width*height/4)+(row/2)*(width/2)+col/2] = in[(2*width*height)+row*width+col];
			}
	}
	memcpy( out, tmp, width*height*3/2*sizeof(unsigned char) );

//	memset(out,1,width*height*3/2);

	delete[] tmp;

	return VIPRET_OK;
}


VIPRESULT vipUtility::conv_PlanarYUV420toPlanarYUV444(unsigned char *in, unsigned char *out, unsigned int width, unsigned int height, bool use_slow_interp )	// -> conv_PlanarYUV420toPlanarYUV444(), was formerly named UV_upsampling()
{
	if( !use_slow_interp )
	{
		// "fast" duplication... (added by Marco Verza). out buffer must be already correctly allocated!
		// check input
		if( in == NULL )
			throw("vipCodec_RAW::conv_PlanarYUV420toPlanarYUV444: input data pointer is null.");

		const unsigned int len = width * height;
		unsigned int j = 0;

		// prepare output
		if( out == NULL )
			throw("vipCodec_RAW::conv_PlanarYUV420toPlanarYUV444: output data pointer is null.");

		// copy Y component
		memcpy( out, in, sizeof(unsigned char)*len );

		int y;
		// upsample U component
		int xmax=width/2, ymax=height/2,inU=len, inV=len*1.25, i=0, in_curr=inU;
		for( y=0; y<ymax; y++)
		{
			for( int x=0; x<xmax; x++ )
			{
				in_curr++;// = inU+y*xmax+x;	//in_curr++ ?
				out[len+(((y<<1)  )*width)+(x<<1)  ] = in[in_curr];
				out[len+(((y<<1)  )*width)+(x<<1)+1] = in[in_curr];
				out[len+(((y<<1)+1)*width)+(x<<1)  ] = in[in_curr];
				out[len+(((y<<1)+1)*width)+(x<<1)+1] = in[in_curr];
				i++;
			}
		}
		// upsample V component
		in_curr = inV;
		for( y=0; y<ymax; y++)
		{
			for( int x=0; x<xmax; x++ )
			{
				in_curr++;// = inV+y*xmax+x;	//in_curr++ ?
				out[(len<<1)+(((y<<1)  )*width)+(x<<1)  ] = in[in_curr];
				out[(len<<1)+(((y<<1)  )*width)+(x<<1)+1] = in[in_curr];
				out[(len<<1)+(((y<<1)+1)*width)+(x<<1)  ] = in[in_curr];
				out[(len<<1)+(((y<<1)+1)*width)+(x<<1)+1] = in[in_curr];
			}
		}
		return VIPRET_OK;	// 
	}

 // else slow interpolation...:
 unsigned char* U = in+width*height;
 unsigned char* V = in+width*height*5/4;

 unsigned char* out_U = new unsigned char[width * height];
 unsigned char* out_V = new unsigned char[width * height];

 unsigned char** column_U = new unsigned char*[width];
 unsigned char** column_V = new unsigned char*[width];

 unsigned char* out_Us = new unsigned char[height * width/2];
 unsigned char* out_Vs = new unsigned char[height * width/2];

 unsigned char** column_Us = new unsigned char*[width/2];
 unsigned char** column_Vs = new unsigned char*[width/2];

 unsigned char* bufferY = new unsigned char[width*height];
 unsigned char* bufferU = new unsigned char[width*height];
 unsigned char* bufferV = new unsigned char[width*height];

 //unsigned char* out = new unsigned char[width * height * 3];



 //making upsampling by interpolation of row first and
 //in second time by interpolation of column
 //from 420-->"422" and from "422"-->444 accordin MSDN formula..

 //begin with 420-->422
 //NB::::the first 2 row and last 3 are handled later...

 for (int row = 2; row < height - 3; row++)//row index
  for(int col = 0; col < width/2; col++)
  {
   if((row % 2) == 0)//line even
   {
	out_Us[row * width/2 + col] = U[row/2 * width/2 +col];
	out_Vs[row * width/2 + col] = V[row/2 * width/2 +col];
   }
   else			//line odd
   {
	int sup = row/2; //integer part
	int sup1 = sup - 1;

	out_Us[row*width/2 + col] = (9*(U[sup*width/2+col]+U[(sup+1)*width/2+col])-
	 (U[sup1*width/2+col]+U[(sup+2)*width/2+col])+8)>>4;

	out_Vs[row*width/2 + col] = (9*(V[sup*width/2+col]+V[(sup+1)*width/2+col])-
	 (V[sup1*width/2+col]+V[(sup+2)*width/2+col])+8)>>4;
   }
  }



  //first 2 row + 3 last rows
  for(int col3 = 0; col3 < width/2; col3++)
  {
   //row 0
   out_Us[col3] = U[col3];
   out_Vs[col3] = V[col3];

   //row 1
   out_Us[width/2 + col3] = (9*(U[col3] + U[width/2 + col3])-
	(U[col3] + U[width + col3]) + 8)>>4;

   out_Vs[width/2 + col3] = (9*(V[col3] + V[width/2 + col3])-
	(V[col3] + V[width + col3]) + 8)>>4;

   //row height-3
   out_Us[(height-3)*(width/2) +col3] = (9*(U[(height/2 - 2)*(width/2) +col3] + U[(height/2 - 1)*(width/2) +col3])-
	(U[(height/2 - 3)*(width/2) +col3] + U[(height/2 - 1)*(width/2) +col3]) +8)>>4;

   out_Vs[(height-3)*(width/2) +col3] = (9*(V[(height/2 - 2)*(width/2) +col3] + V[(height/2 - 1)*(width/2) +col3])-
	(V[(height/2 - 3)*(width/2) +col3] + V[(height/2 - 1)*(width/2) +col3]) +8)>>4;

   //row height-2
   out_Us[(height-2)*(width/2) +col3] = U[(height/2 - 1)*(width/2) +col3];
   out_Vs[(height-2)*(width/2) +col3] = V[(height/2 - 1)*(width/2) +col3];

   //row height-1
   out_Us[(height-1)*(width/2) +col3] = (9*(U[(height/2 - 1)*(width/2) +col3] + U[(height/2 - 1)*(width/2) +col3])-
	(U[(height/2 - 2)*(width/2) +col3] + U[(height/2 - 1)*(width/2) +col3]) +8)>>4;

   out_Vs[(height-1)*(width/2) +col3] = (9*(V[(height/2 - 1)*(width/2) +col3] + V[(height/2 - 1)*(width/2) +col3])-
	(V[(height/2 - 2)*(width/2) +col3] + V[(height/2 - 1)*(width/2) +col3]) +8)>>4;
  }


  //now procede throw the convertion "422" --> 444

  //memory allocation for column array..
  for(int col1 = 0; col1 < width; col1++)
  {
   if(col1 < width/2)
   {
	column_U[col1] = new unsigned char[height];
	column_V[col1] = new unsigned char[height];

	column_Us[col1] = new unsigned char[height];
	column_Vs[col1] = new unsigned char[height];
   }
   else
   {
	column_U[col1] = new unsigned char[height];
	column_V[col1] = new unsigned char[height];
   }
  }


  //calculation of column array in out_Us,out_Vs..
  for(int col2 = 0; col2 < width/2; col2++)
  {
   for(int row1 = 0; row1 < height; row1++)
   {
	column_Us[col2][row1] = out_Us[col2 + row1*width/2];
	column_Vs[col2][row1] = out_Vs[col2 + row1*width/2];
   }
  }

  //now procede with the upper algorithm, modified to interpolate the columns..

  for(int col4 = 2; col4 < width - 3; col4++)//the last 3 column are handled later...
  {
   for(int row2 = 0; row2 < height; row2++)
   {
	if((col4 % 2) == 0)
	{
	 column_U[col4][row2] = column_Us[col4 /2][row2];
	 column_V[col4][row2] = column_Vs[col4 /2][row2];
	}
	else
	{
	 int sup2 = col4 / 2;   //integer part...
	 int sup3 = sup2 - 1;

	 column_U[col4][row2] = (9* (column_Us[sup2][row2] + column_Us[sup2+1][row2]) -
	  (column_Us[sup3][row2] + column_Us[sup2+2][row2]) +8)>>4;

	 column_V[col4][row2] = (9* (column_Vs[sup2][row2] + column_Vs[sup2+1][row2]) -
	  (column_Vs[sup3][row2] + column_Vs[sup2+2][row2]) +8)>>4;
	}
   }
  }

  //setting value for the first 2 and last 3 column..
  for(int row4 = 0; row4 < height; row4++)
  {
   //column 0
   column_U[0][row4] = column_Us[0][row4];
   column_V[0][row4] = column_Vs[0][row4];

   //column 1
   column_U[1][row4] = (9* (column_Us[0][row4] + column_Us[1][row4]) -
	(column_Us[0][row4] + column_Us[2][row4]) +8)>>4;

   column_V[1][row4] = (9* (column_Vs[0][row4] + column_Vs[1][row4]) -
	(column_Vs[0][row4] + column_Vs[2][row4]) +8)>>4;

   //column width-3
   column_U[width-3][row4] = (9*(column_Us[width/2 -2][row4] + column_Us[width/2 -1][row4])-
	(column_Us[width/2 -3][row4] + column_Us[width/2 -1][row4])+8)>>4;

   column_V[width-3][row4] = (9*(column_Vs[width/2 -2][row4] + column_Vs[width/2 -1][row4])-
	(column_Vs[width/2 -3][row4] + column_Vs[width/2 -1][row4])+8)>>4;

   //column width-2
   column_U[width-2][row4] = column_Us[width/2 -1][row4];
   column_V[width-2][row4] = column_Vs[width/2 -1][row4];

   //column width-1
   column_U[width-1][row4] = (9*(column_Us[width/2 -1][row4] + column_Us[width/2 -1][row4])-
	(column_Us[width/2 -2][row4] + column_Us[width/2 -1][row4])+8)>>4;
   column_V[width-1][row4] = (9*(column_Vs[width/2-2][row4] + column_Vs[width/2-1][row4])-
	(column_Vs[width/2 -2][row4] + column_Vs[width/2 -1][row4])+8)>>4;
  }


  //now we procede by copying the new interpolated data into the new structure...
  int cont2=0;
  int cont3=-1;

  for (int cont = 0;cont < width * height; cont++,cont2++)
  {
   if (cont%width == 0)
   {
	cont2=0;
	cont3++;
   }
   bufferY[cont] = in[cont];//pData
   bufferU[cont] = column_U[cont2][cont3];
   bufferV[cont] = column_V[cont2][cont3];
  }

  //copy all new data in new out structure..(YUV444)
  for(int cont1 = 0; cont1 < width * height; cont1++)
  {
   out[cont1] = bufferY[cont1];
   out[width*height+cont1] = bufferU[cont1];
   out[2*width*height+cont1] = bufferV[cont1];
  }

  //freeing the resources...


  for(int col5 = 0; col5 <width; col5++)
  {
   if(col5 < width/2)
   {
	delete[] column_U[col5];
	delete[] column_V[col5];
	delete[] column_Us[col5];
	delete[] column_Vs[col5];
   }
   else
   {
	delete[] column_U[col5];
	delete[] column_V[col5];
   }
  }

  delete[] out_U; delete[] out_V;
  delete[] out_Us; delete[] out_Vs;
  delete[] bufferY; delete[] bufferU; delete[] bufferV;
  delete[] column_U;
  delete[] column_V;
  delete[] column_Us;
  delete[] column_Vs;

  //return out;
  return VIPRET_OK;
}


/**
* @brief  Convert YUV444 buffer to UYVY
*
* @param[in] in structure in YUV444 color space
* @param[out] out structure in UYVY color space
*
* @note	Only partially tested!
*
*/
VIPRESULT vipUtility::conv_PlanarYUV444toPackedUYVY( unsigned char *in, unsigned char *out, unsigned int width, unsigned int height )
{
	unsigned int framesize = width*height;
	unsigned int I=0,O=0;

	for( unsigned int i=0; i<framesize; i+=2 )
	{
		// set 2 pixels each cycle
		out[O  ] = (in[framesize+I]+in[framesize+I+1])/2;		// U_0
		out[O+1] = in[I+1];										// Y_0
		out[O+2] = (in[framesize*2+I]+in[framesize*2+I+1])/2;	// V_0
		out[O+3] = in[I+1];										// Y_1

		O += 4;
		I += 2;
	}

	return VIPRET_OK;
}



/**
* @brief  Rescale one component plane
*
* @param[in] in unsigned char buffer
* @param[out] out unsigned char buffer that MUST be handled outside this method
*
* @note	Only partially tested!s
*
*/
VIPRESULT vipUtility::rescale_plane( unsigned char *in, unsigned char *out, unsigned int inWidth, unsigned int inHeight, unsigned int outWidth, unsigned int outHeight )
{ // very simple linear implementation
	
	if( outWidth==inWidth && outHeight==inHeight )	// no rescale needed
	{
		memcpy( out, in, sizeof(unsigned char)*outWidth*outHeight );
		return VIPRET_OK;
	}

	double wRatio = double(inWidth) / double(outWidth);
	double hRatio = double(inHeight) / double(outHeight);

	if( wRatio != hRatio )
		return VIPRET_NOT_IMPLEMENTED;	// for now, not implemented


	if( outWidth>inWidth || outHeight>inHeight )	// larger out than in: interpolate
	{
		// Check ratio is a power of 2, else return not implemented
		bool isPow2 = false;
		double pow2 = 1;
		while( pow2 >= wRatio )
		{
			if( pow2 == wRatio )
			{
				isPow2 = true;
				break;
			}
			pow2 /= 2;
		}
		if( !isPow2 )
			return VIPRET_NOT_IMPLEMENTED;

		// Do the actual interpolation
		if( wRatio == 0.5 )
		{
			for( unsigned int h=0; h<inHeight; h++ )
			{
				unsigned int offset = h*inWidth; // just to avoid some multiplies
				for( unsigned int w=0; w<inWidth; w++ )
				{ // for every pixel of the INPUT plane, output 4 pixels:
					out[ (2*h)*(outWidth) + (2*w) ] = in[offset+w];
					out[ (2*h)*(outWidth) + (2*w) +1] = in[offset+w];
					out[ (2*h+1)*(outWidth) + (2*w) ] = in[offset+w];
					out[ (2*h+1)*(outWidth) + (2*w) +1] = in[offset+w];

				}
			}
		}
		else
		{
			// do recursive interpolation
			// todo
			return VIPRET_NOT_IMPLEMENTED;
		}
		

		return VIPRET_OK;
	}	// end of interpolate (larger out than in)


	// Check ratio is a power of 2, else return not implemented
	bool isPow2 = false;
	double pow2 = 2;
	while( pow2 <= wRatio )
	{
		if( pow2 == wRatio )
		{
			isPow2 = true;
			break;
		}
		pow2 *= 2;
	}
	if( !isPow2 )
		return VIPRET_NOT_IMPLEMENTED;


	unsigned int offset = 0;
	unsigned int srcW, srcH;

	//if( out != NULL )
	//	delete[] out;
	//out = new unsigned char[outWidth*outHeight];


	//// Actual rescale by factor of 2...
	if( wRatio==2 && hRatio==2 )
	{
		for( unsigned int h=0; h<outHeight; h++ )
		{
			offset = outWidth*h;	// just to avoid some of the multiplies in the cycle
			srcH = h<<1;
			for( unsigned int w=0; w<outWidth; w++ )
			{
				srcW = w<<1;
				out[offset+w] = ((double)in[(srcH  ) * inWidth + srcW  ]	/4 ) +
								((double)in[(srcH+1) * inWidth + srcW  ]	/4 ) +
								((double)in[(srcH  ) * inWidth + srcW+1]	/4 ) +
								((double)in[(srcH+1) * inWidth + srcW+1]	/4 ) ;

			} //w
		} //h
		return VIPRET_OK;
	}
	else if( wRatio<2 || hRatio<2 )
		return VIPRET_NOT_IMPLEMENTED;
	//// End of actual rescale by factor of 2


	//// Recursive rescale by factor of 2
	unsigned char *tmp_buff_in = new unsigned char[inWidth*inHeight];
	memcpy( tmp_buff_in, in, sizeof(unsigned char)*inWidth*inHeight );
	unsigned char *tmp_buff_out;
	while( wRatio >= 2 )
	{
		tmp_buff_out = new unsigned char[inWidth*inHeight/4];
		vipUtility::rescale_plane( tmp_buff_in, tmp_buff_out, inWidth, inHeight, inWidth/2, inHeight/2 );
		inWidth		= inWidth >> 1;	// update ratios and dimensions
		inHeight	= inHeight >> 1;
		wRatio		= wRatio / 2;
		hRatio		= hRatio / 2;

		if( wRatio > 1 )
		{
			memcpy( tmp_buff_in, tmp_buff_out, sizeof(unsigned char)*inWidth*inHeight );
			delete[] tmp_buff_out;
			tmp_buff_out = NULL;
		}
		if( wRatio == 1 )	// finished, give output
		{
			memcpy( out, tmp_buff_out, sizeof(unsigned char)*inWidth*inHeight );
			delete[] tmp_buff_out;
			tmp_buff_out = NULL;
			delete[] tmp_buff_in;
			return VIPRET_OK;
		}
	}
	//// End of recursive cycle

	// If everything's fine, following should not be called:

	if( tmp_buff_in != NULL )
		delete[] tmp_buff_in;
	if( tmp_buff_out != NULL )
		delete[] tmp_buff_out;
	return VIPRET_INTERNAL_ERR;

}



/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
//////// FUNZIONI DA VERIFICARE SINGOLARMENTE!!!!! //////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
///*
//void rgb555_rgb(void* src, void* dst, int width,int height)
// {
//
//	unsigned int* srcPtr = (unsigned int*)src;
//
//	for (unsigned int i = 0; i < width*height; i++)
//	 {
//		*(dst++) = bitcopy_n(srcPtr >> (10 - 3), 3);
//		*(dst++) = bitcopy_n(srcPtr >> (5 - 3), 3);
//		*(dst++) = bitcopy_n(srcPtr << 3, 3);
//	 }
//
//
// }
//
//
//void vipUtility::conv_420p_rgb96(int width,int height,void* src,void* dst)
//{
//	static unsigned int oldSize = 0;
//	static unsigned char* rgb;
////static ?
//
//	unsigned int size = width * height;
//
//	// reallocate memory if the sizes have changed
//	if (oldSize < size) {
//		delete [] rgb;
//		rgb = new  unsigned char [size * 4];
//	}
//
//	// set up all the pointers
//	unsigned char	*s = (unsigned char *)src;
//	int		*d = (int *)dst;
//
//	static unsigned int offset_U = size;
//	static unsigned int offset_V = size + size / 4;
//
//	unsigned char* 	Y = s;
//	unsigned char*	U = s + offset_U;
//	unsigned char*	V = s + offset_V;
//
//	// convert away
//	ccvt_420p_rgb32(width, height, Y, U, V, rgb);
//	conv_rgb32_rgb96(width, height, rgb, d);
//}
//*/
//
//
//void vipUtility::conv_420p_grey(int width,int height,void *src,void *dst)
//{
//	unsigned char	*s = (unsigned char *)src;
//	int		*d = (int *)dst;
//
//	unsigned int size = width * height;
//
//	for (unsigned int i = 0; i < size; i++)
//         *(d++) = *(s++);
//}
//
//
//void vipUtility::conv_bgr24_rgb96(void *src, unsigned char *dst, unsigned int width, unsigned int height)
//{
////BUG
//	unsigned char*  s = (unsigned char*)src ;
//	unsigned char* d = dst + 2 ;
//
//	for (unsigned int i = 0; i < width*height; i++, d+=5)
//	 {
//		*(d--) = *(s++);
//		*(d--) = *(s++);
//		*(d) = *(s++);
//	 }
//
//}
//
///*
//void conv_rgb24_rgb96(int width, int height, void *src, unsigned char *d)
//{
//	unsigned char**	rows = (unsigned char**) src;
//	unsigned char*	s;
//
//	for (int j = 0; j < height; j++) {
//		s = rows[j];
//
//		for (int i = 0; i < width; i++) {
//			*(d++) = *(s++);
//			*(d++) = *(s++);
//			*(d++) = *(s++);
//		}
//	}
//}
//
//	unsigned char* s = (unsigned char*)src;
//	unsigned char* d = dst;
//
//	for (unsigned int i = 0; i < width * height; i++) {
//		*(d++) = *(s++);
//		*(d++) = *(s++);
//		*(d++) = *(s++);
//	}
//*/
//void vipUtility::conv_rgb24_rgb96(void *src, unsigned char *dst, unsigned int width, unsigned int height)
//{
//	unsigned char**	rows = (unsigned char**) src;
//	unsigned char*	s;
//	unsigned char* d = dst;
//
//	for (unsigned int j = 0; j < height; j++) {
//		s = rows[j];
//
//		for (unsigned int i = 0; i < width; i++) {
//			*(d++) = *(s++);
//			*(d++) = *(s++);
//			*(d++) = *(s++);
//		}
//	}
//}
//
//void vipUtility::conv_rgb24_rgb96_(void *src, int *dst, unsigned int width, unsigned int height)
//{
//	unsigned char**	rows = (unsigned char**) src;
//	unsigned char*	s;
//	int* d = dst;
//
//	for (unsigned int j = 0; j < height; j++) {
//		s = rows[j];
//
//		for (unsigned int i = 0; i < width; i++) {
//			*(d++) = *(s++);
//			*(d++) = *(s++);
//			*(d++) = *(s++);
//		}
//	}
//}
//
//void vipUtility::conv_rgb32_rgb96(int width,int height,void *src,void *dst)
//{
//	unsigned char	*s = (unsigned char *)src;
//	int		*d = (int *)dst;
//
//	unsigned int size = width * height;
//
//	for (unsigned int i = 0; i < size; i++, s++) {
//		*(d++) = *(s++);
//		*(d++) = *(s++);
//		*(d++) = *(s++);
//	}
//}
//
//
//
//
//
//
//
///* Functions in ccvt_i386.S/ccvt_c.c */
///* 4:2:0 YUV interlaced to RGB 24bit */
///*
//VIPRESULT vipUtility::conv_420i_rgb24( void* dataIn, vipFrameRGB24& img)
// {
//	if ( &img == NULL || dataIn == NULL || img.width == 0 || img.height == 0 )
//		return VIPRET_PARAM_ERR;
//
//	ccvt_420i_rgb24(img.width, img.height, dataIn, (unsigned char*)img.data[0] );
//
//	return VIPRET_OK;
// }
//*/
///* Functions in ccvt_i386.S/ccvt_c.c */
///* RGB to 4:2:0 YUV planar     */
///*
//VIPRESULT vipUtility::conv_rgb24_420p(vipFrameRGB24& img, void *dsty, void *dstu, void *dstv)
// {
//	if ( &img == NULL || dsty == NULL || dstu == NULL ||  dstv == NULL || img.width == 0 || img.height == 0 )
//		return VIPRET_PARAM_ERR;
//
//	ccvt_rgb24_420p(img.width, img.height, (unsigned char*)img.data[0], dsty, dstu, dstv);
//
//	return VIPRET_OK;
// }
//*/
//
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
///*
//European TV (PAL and SECAM coded) uses Y'U'V' components. Y' is similar to
//perceived luminance, U' and V' carry the colour information and some
//luminance information and are bipolar (they go negative as well as positive).
//The symbols U and V here are not related to the U and V of CIE YUV (1960).
//
//This coding is also used in some 525 line systems with PAL subcarriers,
//particularly in parts of the Americas. The specification here is that of the
//European Broadcasting Union (EBU). Y' has a bandwidth of 5 MHz in Europe,
//5.5 MHz in UK. The U' and V' signals usually have up to 2.5 MHz bandwidth
//in a component studio system, but can be as little as 600 kHz or less in a
//VHS recorder. U' and V' always have the same bandwidth as each other. The
//CRT gamma law is assumed to be 2.8, but camera correction laws are the same
//as in all other systems (approximately 0.45). The system white point is D65,
//the chromaticity coordinates are:
//
//    R:      xr=0.64      yr=0.33
//    G:      xg=0.29      yg=0.60
//    B:      xb=0.15      yb=0.06
//    White:  xn=0.312713  yn=0.329016
//
//The conversion equations for linear signals are:-
//*/
//double cvm_rgb_yuv[] =	{
//							0.431, 0.342, 0.178,
//							0.222, 0.707, 0.071,
//							0.020, 0.130, 0.939
//						};
//double cvm_yuv_rgb[] =	{
//							 3.063, -1.393, -0.476,
//							-0.969,  1.876,  0.042,
//							 0.068, -0.229,  1.069
//						};
//
//
///*
//template<class T, class S>
//VIPRESULT vipUtility::conv_rgb_yuv(T* out, S* in, unsigned int width, unsigned int height)
// {
//	return conv_linear(out, in, cvm_yuv_rgb, width, height);
// }
//*/
//
//template<class T, class S>
//VIPRESULT vipUtility::conv_yuv_rgb(T* out, S* in, unsigned int width, unsigned int height)
// {
//	return conv_linear(out, in, cvm_rgb_yuv, width, height);
// }
//
//
//////////////////////////////////////////////////////////////////////////////////
///*
//The YIQ system is the color primary system adopted by National Television System Committee (NTSC) for color TV broadcasting. The YIQ color solid is made by a linear transformation of the RGB cube. Its purpose is to exploit certain characteristics of the human eye to maximize the utilization of a fixed bandwidth. The human visual system is more sensitive to changes in luminance than to changes in hue or saturation, and thus a wider bandwidth should be dedicated to luminance than to color information. Y is similar to perceived luminance, I and Q carry color information and some luminance information. The Y signal usually has 4.2 MHz bandwidth in a 525 line system. Originally, the I and Q had different bandwidths (1.5 and 0.6 MHz), but now they commonly have the same bandwidth of 1 MHz.
//
//*/
//double cvm_rgb_yiq[] =	{
//							0.299,  0.587,  0.114,
//							0.596, -0.275, -0.321,
//							0.212, -0.523,  0.311
//						};
//double cvm_yiq_rgb[] =	{
//							1,  0.956,  0.621,
//							1, -0.272, -0.647,
//							1, -1.105,  1.702
//    						};
//
//
//template<class T, class S>
//VIPRESULT vipUtility::conv_rgb_yiq(T* out, S* in, unsigned int width, unsigned int height)
// {
//	return conv_linear(out, in, cvm_rgb_yiq, width, height);
// }
//
//
//template<class T, class S>
//VIPRESULT vipUtility::conv_yiq_rgb(T* out, S* in, unsigned int width, unsigned int height)
// {
//	return conv_linear(out, in, cvm_yiq_rgb, width, height);
// }
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
///*
//SMPTE-C is the current colour standard for broadcasting in America, the old
//NTSC standard for primaries is no longer in wide use because the primaries
//of the system have gradually shifted towards those of the EBU
//(see section 6.2). In all other respects, SMPTE-C is the same as NTSC.
//The CRT gamma law is assumed to be 2.2. The white point is now D65, and
//the chromaticities are:
//
//    R:     xr=0.630     yr=0.340
//    G:     xg=0.310     yg=0.595
//    B:     xb=0.155     yb=0.070
//    White: xn=0.312713  yn=0.329016
//
//The conversion equations for linear signals are:
//*/
//double cvm_rgb_smpte_c[] =	{
//								0.3935, 0.3653, 0.1916,
//								0.2124, 0.7011, 0.0866,
//								0.0187, 0.1119, 0.9582
//						};
//double cvm_smpte_c_rgb[] =	{
//								 3.5058, -1.7397, -0.5440,
//								-1.0690,  1.9778,  0.0352,
//								 0.0563, -0.1970,  1.0501
//    						};
//
//
//template<class T, class S>
//VIPRESULT vipUtility::conv_rgb_smpte_c(T* out, S* in, unsigned int width, unsigned int height)
// {
//	return conv_linear(out, in, cvm_rgb_smpte_c, width, height);
// }
//
//
//template<class T, class S>
//VIPRESULT vipUtility::conv_smpte_c_rgb(T* out, S* in, unsigned int width, unsigned int height)
// {
//	return conv_linear(out, in, cvm_smpte_c_rgb, width, height);
// }
//
//
//////////////////////////////////////////////////////////////////////////////////
//
//
///*
//RGB values in a particular set of primaries can be transformed to and from CIE XYZ via a 3x3 matrix transform. These transforms involve tristimulus values, that is a set of three linear-light components that conform to the CIE color-matching functions. CIE XYZ is a special set of tristimulus values. In XYZ, any color is represented as a set of positive values.
//
//To transform from XYZ to RGB (with D65 white point), the matrix transform used is [3]:
//
//   [ R ]   [  3.240479 -1.537150 -0.498535 ]   [ X ]
//   [ G ] = [ -0.969256  1.875992  0.041556 ] * [ Y ]
//   [ B ]   [  0.055648 -0.204043  1.057311 ]   [ Z ].
//
//The range for valid R, G, B values is [0,1]. Note, this matrix has negative coefficients. Some XYZ color may be transformed to RGB values that are negative or greater than one. This means that not all visible colors can be produced using the RGB system.
//
//The inverse transformation matrix is as follows:
//
//   [ X ]   [  0.412453  0.357580  0.180423 ]   [ R ] **
//   [ Y ] = [  0.212671  0.715160  0.072169 ] * [ G ]
//   [ Z ]   [  0.019334  0.119193  0.950227 ]   [ B ].
//
//*/
//double cvm_rgb_xyz[] =	{
//							0.412453, 0.357580, 0.180423,
//							0.212671, 0.715160, 0.072169,
//							0.019334, 0.119193, 0.950227
//						};
//double cvm_xyz_rgb[] =	{
//							 3.240479, -1.537150, -0.498535,
//							-0.969256,  1.875992,  0.041556,
//							 0.055648, -0.204043,  1.057311
//    						};
//
////BUG
//template<class T, class S>
//VIPRESULT vipUtility::conv_rgb_xyz(T* out, S* in, unsigned int width, unsigned int height)
// {
//	return conv_linear(out, in, cvm_rgb_xyz, width, height);
// }
//
//
//template<class T, class S>
//VIPRESULT vipUtility::conv_xyz_rgb(T* out, S* in, unsigned int width, unsigned int height)
// {
//	return conv_linear(out, in, cvm_xyz_rgb, width, height);
// }
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////
///*
//[6.5] ITU.BT-709 HDTV studio production in Y'CbCr
//
//This is a recent standard, defined only as an interim standard for HDTV
//studio production. It was defined by the CCIR (now the ITU) in 1988, but is
//not yet recommended for use in broadcasting. The primaries are the R and B
//from the EBU, and a G which is midway between SMPTE-C and EBU. The CRT gamma
//law is assumed to be 2.2. White is D65. The chromaticities are:
//    R:      xr=0.64       yr=0.33
//    G:      xg=0.30       yg=0.60
//    B:      xb=0.15       yb=0.06
//    White:  xn=0.312713   yn=0.329016
//
//The conversion equations for linear signals are:
//*/
//double cvm_rgb_bt709[] =	{
//							0.412, 0.358, 0.180,
//							0.213, 0.715, 0.072,
//							0.019, 0.119, 0.950
//						};
//double cvm_bt709_rgb[] =	{
//							 3.241, -1.537, -0.499,
//							-0.969,  1.876,  0.042,
//							 0.056, -0.204,  1.057
//   						};
//
//
//template<class T, class S>
//VIPRESULT vipUtility::conv_rgb_bt709(T* out, S* in, unsigned int width, unsigned int height)
// {
//	return conv_linear(out, in, cvm_rgb_bt709, width, height);
// }
//
//
//template<class T, class S>
//VIPRESULT vipUtility::conv_bt709_rgb(T* out, S* in, unsigned int width, unsigned int height)
// {
//	return conv_linear(out, in, cvm_bt709_rgb, width, height);
// }
//
//
//////////////////////////////////////////////////////////////////////////////////
///*
//[6.6] SMPTE-240M Y'PbPr
//
//This one of the developments of NTSC component coding, in which the B primary
//and white point were changed. The CRT gamma law is assumed to be 2.2. The
//white point is D65, chromaticity coordinates are:
//    R:      xr=0.67     yr=0.33
//    G:      xg=0.21     yg=0.71
//    B:      xb=0.15     yb=0.06
//    White:  xn=0.312713 yn=0.329016
//
//The conversion equations for linear signals are:
//*/
//double cvm_rgb_smpte240m[] =	{
//							0.567, 0.190, 0.193,
//							0.279, 0.643, 0.077,
//							0.000, 0.073, 1.016
//						};
//double cvm_smpte240m_rgb[] =	{
//							 2.042, -0.565, -0.345,
//							-0.894,  1.815,  0.032,
//							 0.064, -0.129,  0.912
//						};
//
//
//template<class T, class S>
//VIPRESULT vipUtility::conv_rgb_smpte240m(T* out, S* in, unsigned int width, unsigned int height)
// {
//	return conv_linear(out, in, cvm_rgb_smpte240m, width, height);
// }
//
//
//template<class T, class S>
//VIPRESULT vipUtility::conv_smpte240m_rgb(T* out, S* in, unsigned int width, unsigned int height)
// {
//	return conv_linear(out, in, cvm_smpte240m_rgb, width, height);
// }
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//
//void yuv422to420p(unsigned char *map, unsigned char *cap_map, int width, int height)
//{
//	unsigned char *src, *dest, *src2, *dest2;
//	int i, j;
//
//	/* Create the Y plane */
//	src=cap_map;
//	dest=map;
//	for (i=width*height; i; i--) {
//		*dest++=*src;
//		src+=2;
//	}
//	/* Create U and V planes */
//	src=cap_map+1;
//	src2=cap_map+width*2+1;
//	dest=map+width*height;
//	dest2=dest+(width*height)/4;
//	for (i=height/2; i; i--) {
//		for (j=width/2; j; j--) {
//			*dest=((int)*src+(int)*src2)/2;
//			src+=2;
//			src2+=2;
//			dest++;
//			*dest2=((int)*src+(int)*src2)/2;
//			src+=2;
//			src2+=2;
//			dest2++;
//		}
//		src+=width*2;
//		src2+=width*2;
//	}
//}
//
//// this is bgr !
//void rgb24toyuv420p(unsigned char *map, unsigned char *cap_map, int width, int height)
//{
//	unsigned char *y, *u, *v;
//	unsigned char *r, *g, *b;
//	int i, loop;
//
//	b=cap_map;
//	g=b+1;
//	r=g+1;
//	y=map;
//	u=y+width*height;
//	v=u+(width*height)/4;
//	memset(u, 0, width*height/4);
//	memset(v, 0, width*height/4);
//
//	for(loop=0; loop<height; loop++) {
//		for(i=0; i<width; i+=2) {
//			*y++=(9796**r+19235**g+3736**b)>>15;
//			*u+=((-4784**r-9437**g+14221**b)>>17)+32;
//			*v+=((20218**r-16941**g-3277**b)>>17)+32;
//			r+=3;
//			g+=3;
//			b+=3;
//			*y++=(9796**r+19235**g+3736**b)>>15;
//			*u+=((-4784**r-9437**g+14221**b)>>17)+32;
//			*v+=((20218**r-16941**g-3277**b)>>17)+32;
//			r+=3;
//			g+=3;
//			b+=3;
//			u++;
//			v++;
//		}
//
//		if ((loop & 1) == 0)
//		{
//			u-=width/2;
//			v-=width/2;
//		}
//	}
//}
//

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////




/* Colour ConVerT: going from one colour space to another

   Format descriptions:
   420i = "4:2:0 interlaced"
           YYYY UU YYYY UU   even lines
           YYYY VV YYYY VV   odd lines
           U/V data is subsampled by 2 both in horizontal
           and vertical directions, and intermixed with the Y values.

   420p = "4:2:0 planar"
           YYYYYYYY      N lines
           UUUU          N/2 lines
           VVVV          N/2 lines
           U/V is again subsampled, but all the Ys, Us and Vs are placed
           together in separate buffers. The buffers may be placed in
           one piece of contiguous memory though, with Y buffer first,
           followed by U, followed by V.

   yuyv = "4:2:2 interlaced"
           YUYV YUYV YUYV ...   N lines
           The U/V data is subsampled by 2 in horizontal direction only.

   bgr24 = 3 bytes per pixel, in the order Blue Green Red (whoever came up
           with that idea...)
   rgb24 = 3 bytes per pixel, in the order Red Green Blue (which is sensible)
   rgb32 = 4 bytes per pixel, in the order Red Green Blue Alpha, with
           Alpha really being a filler byte (0)
   bgr32 = last but not least, 4 bytes per pixel, in the order Blue Green Red
           Alpha, Alpha again a filler byte (0)
 */

/* Functions in ccvt_i386.S/ccvt_c.c */

/* 4:2:0 YUV planar to RGB/BGR     */
//void ccvt_420p_rgb32(int width, int height, void *srcy, void *srcu, void *srcv, void *dst);
//void ccvt_420p_bgr32(int width, int height, void *srcy, void *srcu, void *srcv, void *dst);

/* RGB/BGR to 4:2:0 YUV interlaced */

/* RGB/BGR to 4:2:0 YUV planar     */
//void ccvt_rgb24_420p(int width, int height, void *src, void *dsty, void *dstu, void *dstv);
//void ccvt_bgr24_420p(int width, int height, void *src, void *dsty, void *dstu, void *dstv);

/* Go from 420i to other yuv formats */
//void ccvt_420i_420p(int width, int height, void *src, void *dsty, void *dstu, void *dstv);
//void ccvt_420i_yuyv(int width, int height, void *src, void *dst);



//void ccvt_420i_bgr24(int width, int height, void *src, void *dst);
//void ccvt_420i_bgr32(int width, int height, void *src, void *dst);























// SLEEPING ROUTINES, OS DEPENDENT


#if defined(sun)        || defined(__sun)       || defined(linux)       || defined(__linux)    \
 || defined(__CYGWIN__) || defined(__FreeBSD__) || defined(__OPENBSD__) || defined(__MACOSX__) \
 || defined(__APPLE__)  || defined(sgi)         || defined(__sgi)
// Unix (Linux,Solaris,BSD,Irix,...)

	#include <unistd.h>
	#include <time.h>


	// got problems using usleep(millisec), and this is great :P
	void vipUtility::vipSleep(long millisec)
	 {
		if (millisec == 0)
			return;

		double offset = clock() * 1000000 / CLOCKS_PER_SEC;

		while (offset + millisec*1000  >= clock() * 1000000 / CLOCKS_PER_SEC) ;
	 }


	/* returns time in micro-s*/
	double vipUtility::getTime_usec()
	 {
		clock_t clk;
		clk = clock();
		return clk * 1000000 / CLOCKS_PER_SEC;
	 }

#elif defined(_WIN32) || defined(__WIN32__)
// Windows

	#include <windows.h>
	#include <time.h>	/* for gettimeofday */

	void vipUtility::vipSleep(long millisec)
	 {
		Sleep(millisec);
	 }


	/* returns time in micro-s*/

//BUG
	double vipUtility::getTime_usec()
	 {
//		struct timeval  tv;
//		gettimeofday(&tv, 0);
		return -1;
	 }
/*
#else
// Unknown configuration : compile with minimal dependencies.


	void vipUtility::vipSleep(long millisec)
	 {
		;
	 }


//BUG
	double vipUtility::getTime_usec()
	 {
//		struct timeval  tv;
//		gettimeofday(&tv, 0);
		return -1;
	 }
*/
#endif




