
 #include "vipTracker.h"

#include <codecs/vipCodec_RAW.h>

#include <outputs/vipDoctor.h>




#include "add2lib/vipLogic.h"
#include "add2lib/vipSampling.h"

#include <stdio.h>
#include <math.h>
#include <windows.h>




				// in util.cpp
int m_w_a = 150;//minimum workable area;150
int max_global_obj_nr = 25; //dimension of global_obj_array


int LowPassFilter(vipFrameYUV420& img);

int BoundBox(unsigned char* buffer,unsigned char* current_img, int width, int height, int i, FILE* fp);


int OpenClose(unsigned char* bufferIn,int width,int height);

int* Centro_id(unsigned char* img, int ldg, int width, int height);

int Contour_Extraction(vipFrameYUV420 img, unsigned char*out);

int Edge_Extraction(vipFrameYUV420 img, unsigned char*out, int T);





vipTracker::vipTracker()
{
	//for Bg color conversion
	background = NULL;
	BgRGB = NULL;
	BgHSV = NULL;

	//for frame diff
	previous_buff = NULL;

	//for blob_labelling
	max_lbl=85; //max available label for the operation
//max_lbl=200;

	i_l_v=255/max_lbl; //inter label value=distance in ldg between 2 consecutive label

	//for tracking
	previous_labelled = NULL;


	//for shadow&highlight remove
	range_S = 0;	  //saturation range in the current frame
	average_S = 0;  //average saturation value, threshold for shadow & highlight mask computation

/////////////////////////////////////////////


	bufferRGB = NULL;	//buffer in diff color space
	bufferHSV = NULL;

	V_temp = NULL;


	shadow = NULL;	//shadow mask
	highlight = NULL;	//highlight mask
	ghost = NULL;


	bufferBG = NULL;   //buffer for BgSubstraction
	bufferDIFF = NULL;    //buffer for frame differencing

	motion_px = 0;

	fIndex = 0;

	Global_Object_array = NULL;
}



vipTracker::~vipTracker()
{
	if ( previous_labelled != NULL )
		delete[] previous_labelled;
}






/**
* @brief  Make the lowpass filtering of current color plane
*
* @param[comp array]
* @return VIPRET_OK,....
*/
int LowPassFilter(float* data, int width, int height, int type)
	{
	if(type==5)//5x5
		for(int row = 0; row < height; row++)
			for(int col = 0; col < width; col++)
				{
				int cont=row*width+col;
				if(row<2 || row>=height-2 || col<2 || col>=width-2)
					data[cont]=0;
				else

					data[cont]=(data[cont-2*width-2]+data[cont-2*width-1]+data[cont-2*width]+data[cont-2*width+1]+data[cont-2*width+2]
				+data[cont-width-2]+data[cont-width-1]+data[cont-width]+data[cont-width+1]+data[cont-width+2]
			+data[cont-2]+data[cont-1]+data[cont]+data[cont+1]+data[cont+2]
		+data[cont+width-2]+data[cont+width-1]+data[cont+width]+data[cont+width+1]+data[cont+width+2]
	+data[cont-2*width-2]+data[cont-2*width-1]+data[cont-2*width]+data[cont-2*width+1]+data[cont-2*width+2])/25;

				}
	else
		if(type==3)//3x3
			for(int row = 0; row < height; row++)
				for(int col = 0; col < width; col++)
					{
					int cont=row*width+col;

					if(row<1 || row>=height-1 || col<1 || col>=width-1)
						data[cont]=0;
					else

						data[cont]=(data[cont-width-1]+data[cont-width]+data[cont-width+1]
					+data[cont-1]+data[cont]+data[cont+1]
				+data[cont+width-1]+data[cont+width]+data[cont+width+1])/9;
					}
				return VIPRET_OK;
	}



/**
* @brief  Make the background substraction for single frame
*
* @param[buffer] input structure in YUV420 color space
* @param[width, height] dimension of buffer structure
* @param[data] out structure from bgsubstraction passed thow a "soglia"(pixel value in 0-255)
* @
* @return VIPRET_OK,....
*/
int Y_BgSubstraction(vipFrameYUV420 buffer, unsigned char* bg, unsigned char* data,  int th)
	{

	static bool firstsubstraction = true;
	int width = buffer.width;
	int height = buffer.height;
	int motion_px = 0;

	int* diff = new int[width * height]; //difference vectors


	//calculating the image difference between the original frame and the bg (Y comp)

	for(int row = 0; row < height; row++)
		for(int col = 0; col < width; col++)
			{
			int cont = row*width + col;

			diff[cont] = abs((int) ((buffer.data[cont]) - (bg[cont])));

			if(diff[cont] < th)
				diff[cont] = 0;
			else
				diff[cont] = 255;//buffer.data[cont]+50;

			}
		//memcpy(data,diff,width*height);
		for(int row1 = 0;row1 < height; row1++)
			for(int col1 = 0;col1 < width; col1++)
				{
				int cont = row1*width + col1;

				//not consider the data on the 1 and last row & col
				if(row1==0 || row1==height-1 || col1==0 || col1==width-1)
					data[cont] = (unsigned char)0;
				else
					{
					//sort of filtering to reduce the noise
					//matching with 3x3 kernel
					if(diff[cont]!=0 && diff[cont-width]!=0 && diff[cont+width]!=0
						&& diff[cont-1]!=0 && diff[cont+1]!=0)
						{
						data[cont] = (unsigned char)diff[cont];//255
						motion_px+=1;
						}
					else
						data[cont] = (unsigned char)0;
					}
				}

			//freeing buffered resources..
			delete[] diff;

			return motion_px;
	}




/**
* @brief  Make the background substraction for single frame
*
* @param[buffer] input structure in HSV color space
* @param[width, height] dimension of buffer structure
* @param[data] out structure from bgsubstraction passed thow a "soglia"(pixel value in 0-255)
* @
* @return VIPRET_OK,....
*/
	int vipTracker::V_BgSubstraction(float* buffer, float* bg, unsigned char* data, int width, int height, double th)
	{


	int motion_px = 0;

	double* diff = new double[width * height]; //difference vectors
	double diffH = 0;
	double diffS = 0;
	double V_ratio = 0;
	double H_ratio = 0;
	double max_ratio = 0;




	//calculating the image difference between the original frame and the bg (V comp)

	for(int i = 0; i < 3 * width * height; i+=3)
		{
		//printf("\r%f",buffer[i+2] - bg[i+2]);

		diff[i/3] = buffer[i+2] - bg[i+2];
		diffH = buffer[i] - bg[i];
		diffS = buffer[i+1] - bg[i+1];
		if(bg[i+2]==0)
			V_ratio = 1;
		else
			V_ratio = buffer[i+2]/bg[i+2];



		if(diff[i/3] < 0) diff[i/3] = -diff[i/3];
		if(diffH < 0) diffH = -diffH;
		if(diffS < 0) diffS = -diffS;


		if( diff[i/3] > 0.02 || (diffS>(range_S*25/100)) || (diffH > 30) )
			diff[i/3] = 255;
		else
			diff[i/3] = 0;

		if( 0.65 <= V_ratio && V_ratio <=1.2)
			diff[i/3] = 0 ;




		}

	memset(data,0,3*width*height);//for the first and last row & col

	for(int row1 = 1; row1 < height-1; row1++)
		for(int col1 = 1; col1 < width-1; col1++)////////// to rechange!!!!!!!!!
			{
			int cont = row1*width + col1;

			//sort of filtering to reduce the noise
			//matching with 3x3 kernel
			if(diff[cont]==255)// && diff[cont-width+1]==255 && diff[cont-width-1]==255
				//&& diff[cont+width+1]==255 && diff[cont+width-1]==255)// && diff[cont-width-1]!=0.0
				//&& diff[cont-width+1]!=0.0 && diff[cont+width+1]!=0.0 && diff[cont+width-1]!=0.0)
				data[cont] = (unsigned char)255;
			else
				data[cont] = (unsigned char)0;

			}

		//freeing buffered resources..
		delete[] diff;

		return VIPRET_OK;
	}





/**
* @brief  Make the frame differencing between 2 frame
*
* @param[img1] input structure in YUV420 color space
* @param[img2] input structure in YUV420 color space
* @param[data] out structure from bgsubstraction passed thow a threshold(pixel value in 0-255)
* @return VIPRET_OK,....
*/
int vipTracker::FrameDiff(float* img1, float* img2, unsigned char* data, int width, int height)
	{
	int motion = V_BgSubstraction(img1, img2, data, width, height, 0.08);//12

	return motion;
	}



/**
* @brief  Calculate the shadow mask for current frame
*
* @param[bufferHSV] input structure in HSV color space
* @param[width,height] input structure dimension
* @param[out] out structure containing tha shadow
* @return VIPRET_OK,....
*/
	int vipTracker::ShadowMask(unsigned char* orig_frame, float* bufferHSV, int width, int height, unsigned char* out)
	{

	double ThA = 0.65;				//from 0.4 to 0.9  ok con 055 09
	double ThB = 0.95;				//0.90 - 0.95
	double ThH = 60;				//H range in 0-360, each 60 change "color" (R G B C M Y)
	double ThS = range_S *15/100;	//average_S;			//S range in 0-1
	double V_ratio,H_diff,S_diff;


	memset(out,128,width*height*3);  //fill also UV comp..Y wil be rewrited soon..
	for(int i = 0; i < 3*width*height; i+=3)
		{

		H_diff = bufferHSV[i]-BgHSV[i];
		if(H_diff<0) H_diff= -H_diff;
		S_diff = bufferHSV[i+1]-BgHSV[i+1];
		if(S_diff<0) S_diff= -S_diff;
		V_ratio = bufferHSV[i+2]/BgHSV[i+2];

		if(  (H_diff < ThH) && (S_diff <= ThS)  && ((ThB >= V_ratio) && (V_ratio >= ThA)) )

			out[i/3] = (unsigned char)255 ;//orig_frame[i];

		else

			out[i/3] = (unsigned char)0 ;

		}

	return VIPRET_OK;
	}




/**
* @brief  Calculate the highlight mask for current frame
*
* @param[bufferHSV] input structure in HSV color space
* @param[width,height] input structure dimension
* @param[out] out structure containing tha shadow
* @return VIPRET_OK,....
*/
	int vipTracker::HighLightMask(unsigned char* orig_frame, float* bufferHSV, int width, int height, unsigned char* out)
	{

	double ThA = 0.65;		//from 0.65 to 0.80
	double ThB = 0.95;		//0.90 - 0.95
	double ThH = 60;		//H range in 0-360, each 60 change "color" (R G B C M Y)
	double ThS = range_S *15/100;//average_S ; //S range in 0-1
	double V_ratio,H_diff,S_diff;

	memset(out,128,width*height*3);  //fill also UV comp..Y wil be rewrited soon..
	for(int i = 0; i < 3*width*height; i+=3)
		{

		H_diff = bufferHSV[i]-BgHSV[i];
		if(H_diff<0) H_diff= -H_diff;
		S_diff = bufferHSV[i+1]-BgHSV[i+1];
		if(S_diff<0) S_diff= -S_diff;
		V_ratio = bufferHSV[i+2]/BgHSV[i+2];

		if(  (H_diff < ThH) && (S_diff <= ThS) && (((1/ThB) <= V_ratio) && (V_ratio <= (1/ThA))) )

			out[i/3] = (unsigned char)255 ;//orig_frame[i];

		else
			out[i/3] = (unsigned char)0 ;

		}

	return VIPRET_OK;
	}





/**
* @brief  Make edge extraction by sobel mask approach (heavy operations...)
*
* @param[img] input structure in YUV420 color space
* @param[out] out structure
* @return VIPRET_OK,....
*/
int Contour_Extraction(vipFrameYUV420 img, unsigned char*out)//through sobel mask
	{
	int width = img.width;
	int height = img.height;
	unsigned char* buffer= new unsigned char[width*height];
	unsigned char* buffer1 = new unsigned char[width*height];

	for(int row = 1; row < height-1; row++)//column sobel
		for(int col = 1; col < width-1; col++)
			{
			int cont=row*width+col;

			buffer[cont]=(-1*img.data[cont-width-1]-2*img.data[cont-width]-1*img.data[cont-width+1]
		+1*img.data[cont+width-1]+2*img.data[cont+width]+1*img.data[cont+width+1])/4;

			}

		for(int row1 = 1; row1 < height-1; row1++)//row sobel
			for(int col1 = 1; col1 < width-1; col1++)
				{
				int cont=row1*width+col1;

				buffer1[cont] =  (-1*img.data[cont-width-1]+ 1*img.data[cont-width+1]
			-2*img.data[cont-1]+2*img.data[cont+1]
		-1*img.data[cont+width-1]+1*img.data[cont+width+1])/4;

				}

			buffer[0]=buffer[height-1]=buffer1[0]=buffer1[height-1]=(unsigned char)0;

			for(int row2 = 0; row2 < height; row2++)
				for(int col2 = 0; col2 < width; col2++)
					{
					/* if((int)buffer[row2*width+col2] > 250)
					buffer[row2*width+col2]=(unsigned char)255;*/

					//  if((int)buffer[row2*width+col2] < 5)
					//	  buffer[row2*width+col2]=(unsigned char)255;
					//  buffer[row2*width+col2]=(unsigned char)255-buffer[row2*width+col2];

					//else
					//buffer[row2*width+col2]=0;

					/*if((int)buffer1[row2*width+col2]>250)
					buffer1[row2*width+col2]=(unsigned char)255;*/

					//  if((int)buffer1[row2*width+col2] < 5)
					//	  buffer1[row2*width+col2]=(unsigned char)255;
					//  buffer1[row2*width+col2]=(unsigned char)255-buffer1[row2*width+col2];
					//else
					//buffer1[row2*width+col2]=0;


					out[row2*width+col2] = buffer[row2*width+col2] + buffer1[row2*width+col2];

					if((int)out[row2*width+col2] <= 0 )
						out[row2*width+col2]=0;
					else
						//if((int)out[row2*width+col2] > 255)
						out[row2*width+col2]=(unsigned char)255;
					//if((int)out[row2*width+col2] > 10 && (int)out[row2*width+col2] < 245  )
					//	   out[row2*width+col2]=(unsigned char)0;
					}
				delete buffer;
				delete buffer1;
				return VIPRET_OK;
	}



/**
* @brief  Make edge extraction by faster algorithm
*
* @param[img] input structure in YUV420 color space
* @param[T] threshold
* @param[out] out structure
* @return VIPRET_OK,....
*/
int Edge_Extraction(unsigned char* img, unsigned char*out, int width, int height, double T)
	{
	unsigned char* bout = new unsigned char[width*height];

	for(int row = 1; row < height-1; row++)
		for(int col = 1; col < width-1; col++)
			{

			if(abs(img[row*width+col] - img[(row-1)*width+col-1])>(unsigned char)T ||
				abs(img[row*width+col] - img[(row-1)*width+col+1])>(unsigned char)T ||
				abs(img[row*width+col] - img[(row+1)*width+col-1])>(unsigned char)T ||
				abs(img[row*width+col] - img[(row+1)*width+col+1])>(unsigned char)T )
				bout[row*width+col] = (unsigned char) 255;
			else
				bout[row*width+col] = (unsigned char) 0;
			}


		memset(out,0,width*height);
		for(int row1 = 1; row1 < height-1; row1++)
			for(int col1 = 1; col1 < width-1; col1++)
				if(bout[row1*width+col1]==(unsigned char)255 &&
					//bout[row1*img.width+col1+1]==(unsigned char)255 &&
					bout[row1*width+col1+1]==(unsigned char)255)

					out[row1*width+col1] = bout[row1*width+col1];
				else
					out[row1*width+col1] = (unsigned char)0;

		delete[] bout;


		return VIPRET_OK;

	}

/**
* @brief  Make V plane extraction
*
* @param[img] input structure in HSV color space
* @param[out] output structure
* @param[width,height] img dimension
* @return VIPRET_OK,....
*/
int VComp_Extraction(float* img, float* out, int width, int height)
	{
	for(int i = 0; i < width*height*3; i+=3)
		out[i/3] = img[i+2];

	return VIPRET_OK;
	}

/**
* @brief  Make V plane insertion
*
* @param[img] input structure in HSV color space
* @param[out] output structure
* @param[width,height] img dimension
* @return VIPRET_OK,....
*/
int VComp_Substitution(float* img, float* H_temp, int width, int height)
	{
	for(int i = 0; i < width*height*3; i+=3)
		img[i+2] = H_temp[i/3];

	return VIPRET_OK;
	}



/**
* @brief  Draw the bounding box for each label in the frame (PROVVISORIO)
*
* @param[buffer] input labelled frame
* @param[current] input original frame (without any processing)
* @param[*nrlbl] input array with the number of label [0] and real number of used label[1]
* @param[*label] input array of used label value (ldg)
* @param[width,height] input frame dimension
* @param[i] input frame number
* @param[*fp] input file name to write the trajectory
* @return VIPRET_OK,....
*/
int BoundBox(unsigned char* buffer, unsigned char* current,int* nrlbl, int* label, int width, int height, int i, FILE* fp)
	{
	int s_top=0;
	int top=0;
	int bottom=height;
	int s_left=0;
	int left=0;
	int right=width;

	int t = 0;
	int b = 0;
	int l = 0;
	int r = 0;  //print variable

	int step=0;
	int* final_rect = NULL;
	//printf("nrlabel %d %d blob",nrlbl[0],nrlbl[1]);getchar();

	/*final_rect = new int[nrlbl[1]];
	if(nrlbl[1]!=0)
	{
	step = 255/nrlbl[1];
	//resetting of label of rect only for best viewing
	for(int cont=0;cont<nrlbl[1];cont++)
	final_rect[cont] = (int) (255-step*cont);
	}*/

	for(int counter=0;counter<(nrlbl[0]);counter++)
		if(label[counter]!=0)	 //if label=0 then blob is not considered..(already discarded)
			{
			s_top=0;
			top=0;
			bottom=height;
			for(int row2 = 0; row2 < height; row2++)
				for(int col2 = 0; col2 < width; col2++)
					{



					if(
						(int)buffer[row2*width + col2] == label[counter]//255
					//&& (int)buffer[row2*width + col2+2] == 255
					//	  && (int)buffer[row2*width + col2+1] == label[counter]//255
					//	  && (int)buffer[row2*width + col2-1] == label[counter]//255
					//&& (int)buffer[row2*width + col2-2] == 255

					//&&(int)buffer[(row2+2)*width + col2]==255
					//	  &&(int)buffer[(row2+1)*width + col2]==label[counter]//255
					//	  &&(int)buffer[(row2-1)*width + col2]==label[counter]//255
					//&&(int)buffer[(row2-2)*width + col2]==255


					)

						if(s_top==0)
							{
							top = row2;
							s_top = 1;
							}
						else  bottom = row2;
					}
				//	printf("top %d",label[counter]);getchar();

				s_left=0;
				left=0;
				right=width;
				for(int col4 = 0; col4 < width; col4++)
					for(int row4 = 0; row4 < height; row4++)
						{

						if(
							(int)buffer[row4*width + col4]==label[counter]//255
						//&&(int)buffer[(row4+2)*width + col4]==255
						//	   &&(int)buffer[(row4+1)*width + col4]==label[counter]//255
						//	   &&(int)buffer[(row4-1)*width + col4]==label[counter]//255
						//&&(int)buffer[(row4-2)*width + col4]==255

						//&& (int)buffer[row4*width + col4+2] == 255
						//	   && (int)buffer[row4*width + col4+1] == label[counter]//255
						//	   && (int)buffer[row4*width + col4-1] == label[counter]//255
						//&& (int)buffer[row4*width + col4-2] == 255


						)

							if(s_left==0)
								{
								left = col4;
								s_left = 1;
								}else  right =  col4;
						//printf("TESTOK %d\n",col2);

						}



					//printf(" left right top bottom %d %d %d %d",left,right,top,bottom);getchar();

					//writing bounding box on the original sequence..
					if(left!=0 || right!=width || top!=0 || bottom!=height)
						{

						//writing bounding box value to a file
						//ok prima  controllare CUEMOTIONTRACK
						//fprintf(fp,"%3d)    %5d%9d%7d%7d%11d%4d\n",i,top,bottom,left,right,top+(bottom-top)/2,left+(right-left)/2);

						//fprintf(fp,"%3d%3d%6d%4d%6d%4d%6d%4d\n",i-1,0,2*l,2*t,2*r,2*b,2*l+(r-l),2*t+(b-t));


						for(int col3 = left; col3 < right; col3++)
							{
							current[(top) * width + col3] = (unsigned char)255;//label[counter];
							current[(bottom) * width + col3] = (unsigned char)255;//label[counter];

							}

						for(int row3 = top; row3 < bottom; row3++)
							{
							current[row3 * width+left] = (unsigned char)255;//label[counter];
							current[row3 * width+right] = (unsigned char)255;//label[counter];
							}

						//40,139,158
						/*//writing baricentre of object in motion on the original sequence..

						current[(t+(b-t)/2+1)*width + l+(r-l)/2]=(unsigned char)255;

						current[(t+(b-t)/2-1)*width + l+(r-l)/2]=(unsigned char)255;

						current[(t+(b-t)/2)*width + l+(r-l)/2]=(unsigned char)255;

						current[(t+(b-t)/2)*width + l-1+(r-l)/2]=(unsigned char)255;

						current[(t+(b-t)/2)*width + l+1+(r-l)/2]=(unsigned char)255;*/

						}

			}

		delete[] final_rect;

		return VIPRET_OK;
	}

/**
* @brief  make the open-close mophological operation on the input img
*
* @param[bufferIn] input structure in HSV color space
* @param[width,height] img dimension
* @return VIPRET_OK,....
*/
int OpenClose(unsigned char* bufferIn,int width,int height)
	{
	unsigned char* temp = new unsigned char[width*height];
	//memset(temp,0,width*height);
	for(int row=3;row<height-3;row++)
		for(int col=1;col<width-1;col++)
			{
			int cont = row*width+col;
			if(bufferIn[cont]==255 && bufferIn[cont-1]==255/* && bufferIn[cont+1]==255 &&
														   bufferIn[cont-2*width-1]==255 && bufferIn[cont-2*width+1]==255
														   && bufferIn[cont-width]==255 && bufferIn[cont+width]==255 &&
														   bufferIn[cont+2*width]==255 && bufferIn[cont-2*width]==255 */
														   )//&& bufferIn[cont-3*width]==255 && bufferIn[cont+3*width]==255)

														   temp[cont]=(unsigned char)255;
			else
				temp[cont]=0;



			}
		memset(bufferIn,0,width*height);
		for(int row1=0;row1<height-0;row1++)//5
			for(int col1=0;col1<width-0;col1++)//2
				{
				int cont1 = row1*width+col1;


				if(temp[cont1]==(unsigned char)255)
					{
					//pattern 3x3
					/*bufferIn[cont1-1]=255;bufferIn[cont1]=255;bufferIn[cont1+1]=255;
					bufferIn[cont1-width-1]=255;bufferIn[cont1-width]=255;bufferIn[cont1-width+1]=255;
					bufferIn[cont1+width-1]=255;bufferIn[cont1+width]=255;bufferIn[cont1+width+1]=255;
					*/
					/*//pattern 5X5 circular....
					bufferIn[cont1-2]=255;bufferIn[cont1-1]=255;bufferIn[cont1]=255;bufferIn[cont1+1]=255;bufferIn[cont1+2]=255;
					bufferIn[cont1-width-2]=255;bufferIn[cont1-width-1]=255;bufferIn[cont1-width]=255;bufferIn[cont1-width+1]=255;bufferIn[cont1-width+2]=255;
					bufferIn[cont1+width-2]=255;bufferIn[cont1+width-1]=255;bufferIn[cont1+width]=255;bufferIn[cont1+width+1]=255;bufferIn[cont1+width+2]=255;
					bufferIn[cont1-2*width-1]=255;bufferIn[cont1-2*width]=255;bufferIn[cont1-2*width+1]=255;
					bufferIn[cont1+2*width-1]=255;bufferIn[cont1+2*width]=255;bufferIn[cont1+2*width+1]=255;
					*/
					//pattern rett 3x7 (mod....)
					bufferIn[cont1-3*width]=255;bufferIn[cont1+3*width]=255;
					//bufferIn[cont1-3*width-1]=255;bufferIn[cont1-3*width]=255;bufferIn[cont1-3*width+1]=255;
					bufferIn[cont1-2*width-1]=255;bufferIn[cont1-2*width]=255;bufferIn[cont1-2*width+1]=255;
					bufferIn[cont1-width-1]=255;bufferIn[cont1-width]=255;bufferIn[cont1-width+1]=255;
					bufferIn[cont1-1]=255;bufferIn[cont1]=255;bufferIn[cont1+1]=255;
					bufferIn[cont1+width-1]=255;bufferIn[cont1+width]=255;bufferIn[cont1+width+1]=255;
					bufferIn[cont1+2*width-1]=255;bufferIn[cont1+2*width]=255;bufferIn[cont1+2*width+1]=255;
					bufferIn[cont1+3*width-1]=255;bufferIn[cont1+3*width]=255;bufferIn[cont1+3*width+1]=255;
					}
				}
			//needed by label alg..
			for(int row2=0;row2<height;row2++)//5
				for(int col2=0;col2<width;col2++)//2

					if(row2<5 || row2>=height-5 || col2<5 || col2>=width-5)
						bufferIn[row2*width+col2]=0;

			delete[] temp;
			return VIPRET_OK;
	}




/**
* @brief  calculate the centroid of the blob in the img
*
* @param[img] allready labelled unsigned char img buffer
* @param[ldg] level of gray of the blob to work with
* @param[col, row] output value for the position of centroid
* @param[width,height] img dimension
* @return out[], array of position for centroid col, row
*/


int* Centro_id(unsigned char* img, int ldg, int width, int height)
	{
	int sum_row = 0;
	int sum_col = 0;
	int area = 0;
	int* out = new int[3];//col-row for the centroid of current blob
	//printf("%d ",ldg);

	for(int row = 0; row < height; row++)
		for(int col = 0; col < width; col++)
			if ((int)img[row*width+col] == ldg)
				{
				sum_row+=row;
				sum_col+=col;
				area++;
				}

			//position of centroid
			out[0]=sum_col / area;
			out[1]=sum_row / area;
			out[2]=area;
			/*idcol = sum_col / area;
			idrow = sum_row / area;*/


			return out;
	}


/**
* @brief  Calculate the mode of the label in a 5x5 window in the previous_labelled img
*
*
* @param[id_row,id_col] input position of window's center
* @param[width] input dimension of previous_labelled img
* @return The label value more frequent in the window
*/
	int vipTracker::Mode_previous(int id_row, int id_col, int width,int height)
	{
	int* tmp_label = new int[21];	//array for the label in the window
	int* tmp_cont = new int[21];	//array for memorize the occurence of each label in tmp_label
	int counter = 0;	//counter of label's number

	int tmp_col = id_col;
	int tmp_row = 0;


	if(id_row>=5 && id_row<=height-5 && id_col>=5 && id_col<=width-5)
		for(int row=id_row-5; row<=id_row+5; row++)
			{
			tmp_row=row;

			if(row==id_row)
				for(int col=id_col-5;col<=id_col+5;col++)
					{
					tmp_col=col;
					if((int)previous_labelled[tmp_row*width+tmp_col]>0)
						{
						int lbl=(int)previous_labelled[tmp_row*width+tmp_col];
						for(int cont=0; cont<counter;cont++)
							if(tmp_label[cont]==lbl) tmp_cont[cont]+=1;
							else
								{
								tmp_label[counter]=lbl;
								tmp_cont[counter]+=1;
								counter++;
								}
							if(counter==0)
								{
								tmp_label[counter]=lbl;
								tmp_cont[counter]+=1;
								counter++;
								}
						}
					}
			}

		int max=0;
		int max_i=0;
		for(int i=0;i<counter;i++)
			if(tmp_cont[i]>max)
				{
				max=tmp_cont[i];
				max_i=i;
				}

			int final = tmp_label[max_i];

			delete[] tmp_label; delete[] tmp_cont;

			return final;
	}




/**
* @brief  Make the labelling of the blob in the img
*
* (see the paper from IEEE "A simple and efficient connected components labeling algorithm")
*  Luigi di Stefano - Andrea Bulgarelli
*
* @param[bufferIn] input structure(binary)
* @param[bufferOut] output structure
* @param[width,height] img dimension
* @return Array with The total number of label used,the real label used....
*/
int vipTracker::Blob_Labeling(unsigned char* bufferIn,unsigned char* bufferOut,int width,int height,int *label)
	{
	int nrlbl = 0; //number label utilized in the work

	//moved to variable.h
	//int max_lbl = 85;//max available label for the operation
	//int i_l_v = 255/max_lbl; //inter label value==distance in ldg between 2 consecutive label


	//NB: changing the lenght of C[] array (=the nr of possible label available)
	//means change the inter-label value (i_l_v).Given that we have to pay attention
	//in the Blob_tracking(..) method when assigning the output label value to each region(..)

	int lx;
	int* C = new int[max_lbl];  //label array...


	for(int ck = 0; ck < max_lbl; ck++)//initialize label array....
		C[ck]=255-i_l_v*ck;


	memset(bufferOut,0,width*height);	//init buffer output

	//first round...
	for(int row=1;row<height-1;row++)
		for(int col=1;col<width-1;col++)
			{
			int cont = row*width+col;

			if(bufferIn[cont]==255)  //if is Foreground
				{
				int pc = (int)bufferIn[cont-1];
				int pr = (int)bufferIn[cont-width];
				if(pc == 0 && pr == 0)
					{
					nrlbl++;	//set new label value
					lx = nrlbl;
					}
				else if((C[pc] != C[pr]) && (pc != 0) && (pr != 0)) //found equivalence between pc - pr
					{
					//merge of corrispondent class
					for(int k=0; k<max_lbl; k++)
						if(C[k]==C[pc]) C[k]=C[pr];

					lx=pc;
					}
				else if(pc != 0) lx = pc;
				else if(pr != 0) lx = pr;

				bufferIn[cont] = (unsigned char)lx;

				}
			else
				bufferIn[cont] = (unsigned char)0;


			}



		int temp = 0;		//memorize actual label (level of gray)..
		//label = new int[50];	//array really used label(allmost equal to nr of label)
		int used_label = 0;		//number of really used label, array index
		int r_nrlbl = 0;  //really used label

		//second scan, assign final label &
		//memorize the really used label in the frame

		for(int row1=0; row1<height; row1++)
			for(int col1=0; col1<width; col1++)

				if( (int)bufferIn[row1*width+col1] != 0 )
					{
					int sup = (int)bufferIn[row1*width+col1];  //support variable
					bufferOut[row1*width+col1] = (unsigned char)C[sup];

					//control if the label is already in the label array...
					if(array_cmp(label,used_label,C[sup])==0)
						{
						label[used_label] = C[sup];		//memorize only the used label..
						used_label++;r_nrlbl++;
						}
					}


				//now we are interested in finding the centroid for every blob in the frame

				//we now the level of gray of every label in the frame (the int array label[])

				/*	int* cid_position = new int[2*used_label];//row column for each centroid

				for(int cont1 = 0; cont1 < used_label; cont1++)
				{
				int* cid_pos_tmp = Centro_id(bufferOut,label[cont1], width, height);
				cid_position[2*cont1] = cid_pos_tmp[0];		//centroid column
				cid_position[2*cont1+1] = cid_pos_tmp[1];	//centroid row
				blob_area[cont1] = cid_pos_tmp[2];

				delete[] cid_pos_tmp;
				}

				//merge of blobs, assign final label grouping the blobs
				int* support_pL = new int[used_label];
				int* support_bI = new int[used_label];
				int counter = 0;   //blobs counter
				*/
				/*************************************************************************************/

				/*	for(int cont2=0;cont2<2*used_label;cont2+=2)
				{
				int col=cid_position[cont2];//centroid position
				int row=cid_position[cont2+1];

				//memorize the actual blob's centroid label and the label of the
				//pixel at the same position of the actual blob centroid in the prev frame(window mode)
				int bI = (int)bufferOut[row*width+col];
				int pL = Mode_previous(row,col,width,height);

				support_pL[cont2/2] = pL;
				support_bI[cont2/2] = label[cont2/2] ;// ;bI
				counter++;

				for(int cont3=0;cont3<counter;cont3++)

				//decide that if the blob is small enought than it is possible
				//part of a bigger object else it is a separate object

				//depends on the size of the people moving in the sequence
				if(blob_area[cont3]<50)  //50 per test5
				if(support_pL[cont3]==bI && pL!=0)

				for(int cont4=0;cont4<50;cont4++)
				if(C[cont4]==support_bI[cont3])
				{
				C[cont4]=label[cont2/2];//support_bI[cont3];

				}

				}*/
				/***********************************************************************************/

				//re-calculation of used label
				/*	memset(label,0,50);
				used_label = 0;r_nrlbl = 0;

				for(int row2=0; row2<height; row2++)
				for(int col2=0; col2<width; col2++)


				if( (int)bufferIn[row2*width+col2] != 0 )
				{
				int sup1 = (int)bufferIn[row2*width+col2];  //support variable
				bufferOut[row2*width+col2] = (unsigned char)( C[sup1] ) ;

				if(array_cmp(label,used_label,C[sup1])==0)
				{
				label[used_label] = C[sup1];		//memorize only the used label..

				//printf("label_value%dfine",label[used_label]);getchar();
				used_label++;r_nrlbl++;
				}
				}

				//printf("used_label%dfine",used_label);//getchar();


				//re-calculation of fused-blob's centroid
				for(cont1 = 0; cont1 < used_label; cont1++)
				{
				int* cid_pos_tmp = Centro_id(bufferOut,label[cont1], width, height);
				cid_position[2*cont1] = cid_pos_tmp[0];		//centroid column
				cid_position[2*cont1+1] = cid_pos_tmp[1];	//centroid row
				blob_area[cont1]=cid_pos_tmp[2];

				delete[] cid_pos_tmp;

				}*/



				//memcpy(previous_labelled,bufferOut,sizeof(unsigned char)*width*height);

				/*  definitively removed......

				//draw the blobs centroids
				for(int cont4=0;cont4<2*used_label;cont4+=2)
				{
				int row = cid_position[cont4+1];
				int col = cid_position[cont4];
				if(row!=0 && col!=0)
				bufferOut[row*width+col] = (unsigned char)(255-bufferOut[row*width+col]);
				}*/





				/*delete[] cid_position; delete[] support_pL; delete[] support_bI;*/
				delete[] C;

				return used_label;  //nr of labelled region
	}



int vipTracker::Cue_Motion_Track(void)//not essential....
	{
	FILE* file;
	file = fopen("motion_file.txt","wt");
	/*	fprintf(file,"\n*****************************************************\n");
	fprintf(file,"\nFrame       Top    Bottom   Left  Right    CentroId\n");
	fprintf(file,"\n*****************************************************\n\n\n");*/
	fclose(file);

	return VIPRET_OK;
	}


/**
* @brief  Make the tracking of the moving object in the sequence
*
* @param[Input] input labelled img (with blob_labelling(...))
* @param[Original] input original img (HSV format )
* @param[nr_lbl] input array for nr of label in the img
* @param[label] input array of used label
* @param[width.height] input img dimension
* @return Array with The total number of label used,the real label used....
*/

	int vipTracker::Blob_tracking(unsigned char* Input,unsigned char* output,float* Original,int nr_lbl,int* label,int width, int height,int frame_nr)
	{

	//static array of object found globally in the sequence
	//initialized once in the entire processing, first motion frame

	//store the previous final labelled frame
	static unsigned char* previous_final_labelled;

	//store the list of used label in the previous final labelled frame...
	static unsigned char* final_label;
	static int nr_final_label;

	//store the temporary label used..
	unsigned char* temp_label = NULL;

	vipMovingObject* Local_Object_array = NULL;


	if(nr_lbl>0) //if there are moving objects..
		{
		if( nr_lbl > max_global_obj_nr )
			printf("\n\n\nERROR:::::TOO MUCH MOVING OBJECT IN THE SCENE::::::::\n\n\n");

		temp_label = new unsigned char[nr_lbl];

		//allocating memory for found moving objects
		Local_Object_array = new vipMovingObject[nr_lbl];

		//printf("movobj=%d",nr_lbl);getchar();

		if(previous_final_labelled == NULL) //first frame with moving object..
			{
			//unique array memory allocation..(static structure)

			//memory allocation for global_object array (15 object stored)
			Global_Object_array = new vipMovingObject[max_global_obj_nr];

			//set the ID for the global objects
			for(int i=0;i<max_global_obj_nr;i++)
				Global_Object_array[i].Set_Id(i);

			previous_final_labelled = new unsigned char[width*height];

			for(int cont=0;cont<nr_lbl;cont++)
				{
				//setting up initial attributes for each moving object detected..
				Local_Object_array[cont].Set_input_label((unsigned char)label[cont]);
				Local_Object_array[cont].Set_Id(cont);

				//setup of region Area and allocation of region pixel indexes array
				Local_Object_array[cont].Set_PixelMap(Input,width,height);


				//calculation of region statistic..(see .cpp file)
				//USE THE ARRAY PIXEL_MAP TO PROCESS THE FRAME!!!!!!!!!!!!!!!!!!!!!!!!
				Local_Object_array[cont].Get_Statistic(Original);

				//this is the first frame with moving object..
				//assign to each object the final label = input label-3
				Local_Object_array[cont].Set_output_label((unsigned char)(label[cont]-(i_l_v-1)));
				//ATTENTION:::::in the setoutputlabel "2" must be inferior to i_l_v (inter_label_value)
				//given in the blob_labelling method..

				//repaint the region with the final label computed (if big enought)
				Local_Object_array[cont].Re_paint_Color(Input,width,height);


				//store the label value associated with the region
				temp_label[cont] = Local_Object_array[cont].Get_Output_label();
				Local_Object_array[cont].Presence(true);
				Local_Object_array[cont].Set_last_frame_seen(frame_nr+1);
				Local_Object_array[cont].copy_to(Global_Object_array,max_global_obj_nr,true,frame_nr);

				}//end for(int cont=0;cont<nr_lbl;cont++)
			}//end if(previous_final_labelled..)

		else if(previous_final_labelled)  //not first frame, acting temporal analisys...
			{
			//here the previous_final_labelled array is already allocated and its content
			//is used to temporal analisys..

			for(int cont=0;cont<nr_lbl;cont++)
				{
				//setting up main attributes for each object
				Local_Object_array[cont].Set_input_label((unsigned char)label[cont]);
				Local_Object_array[cont].Set_Id(cont);

				//setup of region area and allocation of region pixel indexes array
				Local_Object_array[cont].Set_PixelMap(Input,width,height);

				//calculation of region statistic..(see .cpp file)
				//USE THE ARRAY PIXEL_MAP TO PROCESS THE FRAME!!!!!!!!!!!!!!!!!!!!!!!!
				Local_Object_array[cont].Get_Statistic(Original);


				//now we look for drag the label assigned to each region in the previous frame
				//if it's so, we procede dragging the label to the region in actual frame
				//else we assign to the actual region a new final label...

				//in dragging operation may happens that a whole region (usually small..) falls
				//into another object (the previous labelling fase is not error-free): in this case
				//we need to update the Pixel_Map of the object...

				//check of calculated final label (must be unique in the frame!!!)

				if(Local_Object_array[cont].drag_label(Input,previous_final_labelled) == 0 )
					{
					//printf("Correctly label Dragged...\n");
					//output label correctly calculated..
					Local_Object_array[cont].Re_paint_Color(Input,width,height);
					temp_label[cont] = Local_Object_array[cont].Get_Output_label();
					}
				else
					{
					//printf("Label dragged re-evaluation...\n");
					//need to re-evaluate the final label for the region..

					//set temporary out lbl
					Local_Object_array[cont].Set_output_label(Local_Object_array[cont].Get_input_label()-(i_l_v-1));
					//ATTENTION:::::in the setoutputlabel "2" must be less than i_l_v (inter_label_value)
					//given in the blob_labelling method..

					unsigned char value = Local_Object_array[cont].Get_Output_label();

					//check if it's already present in the frame (previous final labelled)
					int check = array_cmp(final_label,nr_final_label,value);
					if(check==1)// check failure..
						while(check==1)
							{
							//going to change the fin_lbl value until check is passed successfully
							Local_Object_array[cont].Set_output_label(Local_Object_array[cont].Get_Output_label()-i_l_v);
							//ATTENTION:::::in the setoutputlabel "3" must be equal to i_l_v (inter_label_value)
							//given in the blob_labelling method..
							value = Local_Object_array[cont].Get_Output_label();
							check = array_cmp(final_label,nr_final_label,value);
							}

						Local_Object_array[cont].Re_paint_Color(Input,width,height);
						temp_label[cont] = Local_Object_array[cont].Get_Output_label();
					}//end if(found a dragged label.)else



				Local_Object_array[cont].Presence(true);
				Local_Object_array[cont].Set_last_frame_seen(frame_nr+1);
				Local_Object_array[cont].copy_to(Global_Object_array,max_global_obj_nr,false,frame_nr);

				} //end for(int cont=0;cont<nr_lbl;cont++)



			}//end else if (previous_final_labelled)else..


		//check if there are multiple object with the same final_label(in the local array..)
		unsigned char* loc_array = new unsigned char[nr_lbl];
		bool Do_Discriminate = false;  //tic for function activation
		unsigned char lf;
		int nr_occlusion=0;//nr of occlusion to handle
		unsigned char* occlusion_label = new unsigned char[3];//label duplicated array

		for(int e=0; e<nr_lbl; e++)
			if(Local_Object_array[e].Get_area()>m_w_a)//do not consider too small region
				{
				lf = Local_Object_array[e].Get_Output_label();

				if(array_cmp(loc_array,nr_lbl,lf)==1)
					{
					/*printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\n");
					printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\n");
					printf("\t\t\tWARNING::::::label %d duplication\t\t\t\n",lf);
					printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\n");*/

					//given the duplication we procede looking for the Global_Object
					//corrispondent to that label. In this (Special) Object is contained all of the information
					//relative the fused object label from which it's possible retrieve the
					//global_object ID of fused object: given that( the ID of Global Object fused)
					//we procede comparing the hist of the object to distinguish after an occlusion..

					Do_Discriminate=true;//tic for discrimination function activation
					//lw=lf;
					occlusion_label[nr_occlusion] = lf;
					nr_occlusion++;

					}
				else
					//store the label for future comparison..
					loc_array[e]=lf;
				}

			if(Do_Discriminate==true)
				for(int o=0;o<nr_occlusion;o++)
				//activate and calling of discrimination function

				Discriminate(Local_Object_array,Global_Object_array,occlusion_label[o],nr_lbl);

			for(int cont=0;cont<nr_lbl;cont++)
				{
				//black repaint of too small object..
				if(Local_Object_array[cont].Get_area()<m_w_a)
					{
					Local_Object_array[cont].Set_output_label(0);
					Local_Object_array[cont].Re_paint_Color(Input,width,height);
					}
				else
					{
					//object to visualize...
					//mainly for centro_id and traject drawing..
					int tmp=Local_Object_array[cont].Get_Corrispondent();
					Global_Object_array[tmp].Set_Active(true);

					//..and color repaint for the others..
					Local_Object_array[cont].Re_paint_Color(Input,width,height);

					}
				}



			//memcpy(output,Input,width*height*3);

			//remove blinking object..buffering..(review)
			//here set the th in nr of frame..(too rare object are refused..)
			Buffer_Presence(output,width,height,Global_Object_array,max_global_obj_nr,frame_nr);


			delete[] final_label;
			delete[] occlusion_label;
			final_label = new unsigned char[nr_lbl];

			//copy the final labelled frame to static structure..
			memcpy(previous_final_labelled,Input,sizeof(unsigned char)*width*height);

			//copy the used final label to static array..
			memcpy(final_label,temp_label,sizeof(unsigned char)*nr_lbl);

			nr_final_label = nr_lbl;

			//freeing unused resources...
			delete[] temp_label;
			delete[] loc_array;
			delete[] Local_Object_array;

		}//endif (nr_lbl>0)




	return 0;
	}


vipFrameYUV420& vipTracker::getSupImg()
{
	return sup_img;
}


	int vipTracker::setHeight(unsigned int height)
	{
			//we will work with quarter dimension support image
			sup_img.height = height/2;
			return 0;
	}

	int vipTracker::setWidth(unsigned int width)
	{
			//we will work with quarter dimension support image
			sup_img.width = width/2;
			return 0;
	}


VIPRESULT vipTracker::importFrom(vipFrameYUV420& current_img)
{
			//downsampling of orig frame(current_imgYUV420,sup_imgYUV444,downsample only Y)
			sup_img.data = Down_Sample(current_img);


			//allocation temp buffer for color space conversion
			bufferHSV = new float[3*sup_img.width*sup_img.height];
			V_temp = new float[sup_img.width*sup_img.height];

			//allocation buffer for shadow&highlight
			shadow = new unsigned char[3*sup_img.width*sup_img.height];//yuv444
			highlight = new unsigned char[3*sup_img.width*sup_img.height];//yuv444

			//allocation memory for BgSubstraction (binary img)
			bufferBG = new unsigned char[3*sup_img.width*sup_img.height];
			bufferDIFF = new unsigned char[3*sup_img.width*sup_img.height];


			if( fIndex == 0 )
				{
				//the first frame is the Bg..
				//allocation memory for color space conversion
				BgHSV = new float[3*sup_img.width * sup_img.height];
				previous_buff = new float[3*sup_img.width*sup_img.height];//indeed I need only V comp

				previous_labelled = new unsigned char[sup_img.width*sup_img.height];

				background = new unsigned char[sup_img.width*sup_img.height*3];

				//copy Bg data into global variable
				memcpy(background, sup_img.data, sup_img.width*sup_img.height*3);

				//conversion in HSV and memorization into global variable
				//video_in.
					conv_PlanarYUVtoPixelHSV(background,BgHSV,sup_img.width,sup_img.height, &range_S, &average_S);

				//lowing pass of V plane(too noisy to work with it..)
				VComp_Extraction(BgHSV,V_temp,sup_img.width,sup_img.height);
				LowPassFilter(V_temp,sup_img.width,sup_img.height,3);
				VComp_Substitution(BgHSV,V_temp,sup_img.width,sup_img.height);


				memcpy(previous_buff, BgHSV, sizeof(double)*sup_img.width*sup_img.height);

				}
			else if( fIndex > 0 )//case of ordinary frame, not Bg..
					{

					//video_in. ,  variable needed for calculation of shadow & highlight mask..
					conv_PlanarYUVtoPixelHSV(sup_img.data,bufferHSV,sup_img.width,sup_img.height, &range_S, &average_S);

					//lowing pass of V plane(too noisy to work with it..)
					VComp_Extraction(bufferHSV,V_temp,sup_img.width,sup_img.height);
					LowPassFilter(V_temp,sup_img.width,sup_img.height,3);
					VComp_Substitution(bufferHSV,V_temp,sup_img.width,sup_img.height);


					//consider Value bg-substraction(....)
					motion_px = V_BgSubstraction(bufferHSV, BgHSV, bufferBG, sup_img.width, sup_img.height, 0.08);


					memset(shadow,128,sup_img.width*sup_img.height*3);//mainly for set UV comp
					memset(highlight,128,sup_img.width*sup_img.height*3);

					ShadowMask(sup_img.data,bufferHSV,sup_img.width,sup_img.height,shadow);//yuv444
					HighLightMask(sup_img.data,bufferHSV,sup_img.width,sup_img.height,highlight);//yuv444

					//substraction of shadow mask from bufferBG,
					//to obtain tha real motion objects
					Logic_DIFF(bufferBG, shadow, highlight, sup_img.width, sup_img.height, bufferBG);

					//Edge_Extraction(bufferBG,sup_img.data,sup_img.width,sup_img.height,5);


					if( fIndex % 1000 == 0)		//refresh rate for BG frame..
						{
						motion_px = FrameDiff(bufferHSV,previous_buff,bufferDIFF, sup_img.width, sup_img.height);
						//Logic_DIFF(bufferDIFF, shadow, highlight, sup_img.width, sup_img.height, bufferDIFF);
						Logic_DIFF(bufferBG, bufferDIFF,  sup_img.width,sup_img.height,bufferDIFF);
						//memcpy(sup_img.data,bufferDIFF, sup_img.width*sup_img.height*3);

						//Edge_Extraction(bufferDIFF,sup_img.data,sup_img.width,sup_img.height,5);

						for(unsigned int t = 0; t < sup_img.width*sup_img.height*3; t+=3)
							if((int)bufferDIFF[t] == 255)
								{
								double a=0;
								double b=1;//a*background[t]+b*
								background[t] = (unsigned char)(a*background[t]+b*sup_img.data[t]);
								background[t+1] = (unsigned char)(a*background[t+1]+b*sup_img.data[t+1]);
								background[t+2] = (unsigned char)(a*background[t+2]+b*sup_img.data[t+2]);
								}
							//memcpy(sup_img.data,background, sup_img.width*sup_img.height*3);
							//video_in.
								conv_PlanarYUVtoPixelHSV(background,BgHSV,sup_img.width,sup_img.height, &range_S, &average_S);

//OK							range_S = video_in.getFrameSaturationRange();  //saturation range in the current frame
//OK							average_S = video_in.getFrameSaturationAverage();  //average saturation value, threshold for shadow & highlight mask computation


							VComp_Extraction(BgHSV,V_temp,sup_img.width,sup_img.height);
							LowPassFilter(V_temp,sup_img.width,sup_img.height,3);
							VComp_Substitution(BgHSV,V_temp,sup_img.width,sup_img.height);

							//memorize previous_frame
							memcpy(previous_buff,bufferHSV, sizeof(float)*sup_img.width*sup_img.height*3);
						}


					//free resources..
					delete[] shadow;
					delete[] highlight;
					//delete[] bufferHSV;//copy of actual frame in HSV
					delete[] bufferDIFF;
					delete[] V_temp;


					}


				OpenClose(bufferBG, sup_img.width, sup_img.height);

				int* label = new int[max_lbl];//array of fused label value
				//int* area_blob = new int[50];//area of area of each region labelled..

				//support array
				unsigned char* temporal = new unsigned char[3*sup_img.width * sup_img.height];
				memset(temporal,128,3*sup_img.width*sup_img.height);


				//in position 0 of nrlabel we have number of label
				//in position 1 of nrlabel we have number of really usefull label
				int nrlabel = Blob_Labeling(bufferBG, temporal, sup_img.width, sup_img.height,label);

			//memcpy(sup_img.data,temporal,3*sup_img.width*sup_img.height);

				//printf("nr_label=%d!!!\n",nrlabel);getchar();

				Blob_tracking(temporal,sup_img.data,bufferHSV,nrlabel,label,sup_img.width,sup_img.height,fIndex);

				delete[] bufferBG;
				delete[] temporal;
				delete[] label;
				//delete[] area_blob;//
				delete[] bufferHSV;

				//reconvert to YUV420
				//UV_downsampling(sup_img.data, sup_img.data, sup_img.width, sup_img.height);


//				videosmall.getParameters().setVideoFormat("YUV_4:4:4");
				//videosmall.getParameters().setVideoFormat("YUV_4:2:0");
//				videosmall << sup_img;


fIndex++;


	return VIPRET_OK;
	}






/*

int vipTracker::Motion_Track(vipCodec_RAW& video_in, vipCodec_RAW& video_out, vipCodec_RAW& videosmall)
	{

	int width = video_in.getWidth();
	int height = video_in.getHeight();

	int motion_px = 0;


	//file to memorize the motion object trajectory
	//FILE* fp;
	//fp=fopen("motion_file.txt","at");

	//image structure for current frame process
	vipFrameYUV420 current_img;

	//support image strucure..
	vipFrameYUV420 sup_img;

	//statistic support
	vipDoctor doctor;

	unsigned char* bufferRGB = NULL;	//buffer in diff color space
	float* bufferHSV = NULL;

	float* V_temp = NULL;


	unsigned char* shadow = NULL;	//shadow mask
	unsigned char* highlight = NULL;	//highlight mask
	unsigned char* ghost = NULL;


	unsigned char* bufferBG = NULL;   //buffer for BgSubstraction
	unsigned char* bufferDIFF = NULL;    //buffer for frame differencing


	//setting video out parameters..
	video_out.getParameters().setVideoFormat("YUV_4:2:0");	 //influence the import << operator
	video_out.getParameters().setYwidth(current_img.width);
	video_out.getParameters().setYheight(current_img.height);

	videosmall.getParameters().setVideoFormat("YUV_4:4:4");  //influence the import << operator
	videosmall.getParameters().setYwidth(current_img.width/2);
	videosmall.getParameters().setYheight(current_img.height/2);


	//reset counter & statistics..
	doctor.reset(true);

	//graphic console handling..
	HANDLE hOut;
	DWORD Written;
	COORD Position;
	COORD BarPosition;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	char* clr = "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\n";



	for(unsigned int i = 0; i < video_in.getNumberFrame(); i++)
		{

		video_in >> current_img;

		int nf_ratio = 100*(i+1) / video_in.getNumberFrame();

		Position.X = 2;
		Position.Y = 19;
		SetConsoleCursorPosition(hOut,Position);

		printf("   Processing frame : %d of %d total frames   ( %d%s , ", i+1, video_in.getNumberFrame(),nf_ratio,"%");

		////////////////////////////////////////////////
		////////////////////////////////////////////////
		//move the console cursor to print eventual debug msg..
		Position.X = 2;
		Position.Y = 24;
		SetConsoleCursorPosition(hOut,Position);
		printf("INFO & DEBUG MESSAGE\n\n");
		////////////////////////////////////////////////
		////////////////////////////////////////////////

		if(i>=0) //i>0..(....not usefull to remove)
			{
			//we will work with quarter dimension support image
			sup_img.height = current_img.height/2;
			sup_img.width = current_img.width/2;

			//downsampling of orig frame(current_imgYUV420,sup_imgYUV444,downsample only Y)
			sup_img.data = Down_Sample(current_img);


			//allocation temp buffer for color space conversion
			bufferHSV = new float[3*sup_img.width*sup_img.height];
			V_temp = new float[sup_img.width*sup_img.height];

			//allocation buffer for shadow&highlight
			shadow = new unsigned char[3*sup_img.width*sup_img.height];//yuv444
			highlight = new unsigned char[3*sup_img.width*sup_img.height];//yuv444

			//allocation memory for BgSubstraction (binary img)
			bufferBG = new unsigned char[3*sup_img.width*sup_img.height];
			bufferDIFF = new unsigned char[3*sup_img.width*sup_img.height];


			if(i==0)
				{
				//the first frame is the Bg..
				//allocation memory for color space conversion
				BgHSV = new float[3*sup_img.width * sup_img.height];
				previous_buff = new float[3*sup_img.width*sup_img.height];//indeed I need only V comp

				previous_labelled = new unsigned char[sup_img.width*sup_img.height];

				background = new unsigned char[sup_img.width*sup_img.height*3];

				//copy Bg data into global variable
				memcpy(background, sup_img.data, sup_img.width*sup_img.height*3);

				//conversion in HSV and memorization into global variable
				video_in.conv_PlanarYUVtoPixelHSV(background,BgHSV,sup_img.width,sup_img.height);

				range_S = video_in.getFrameSaturationRange();  //saturation range in the current frame
				average_S = video_in.getFrameSaturationAverage();  //average saturation value, threshold for shadow & highlight mask computation


				//lowing pass of V plane(too noisy to work with it..)
				VComp_Extraction(BgHSV,V_temp,sup_img.width,sup_img.height);
				LowPassFilter(V_temp,sup_img.width,sup_img.height,3);
				VComp_Substitution(BgHSV,V_temp,sup_img.width,sup_img.height);


				memcpy(previous_buff, BgHSV, sizeof(double)*sup_img.width*sup_img.height);

				}
			else


				if(i>0)//case of ordinary frame, not Bg..
					{

					video_in.conv_PlanarYUVtoPixelHSV(sup_img.data,bufferHSV,sup_img.width,sup_img.height);

					//variable needed for calculation of shadow & highlight mask..
					range_S = video_in.getFrameSaturationRange();  //saturation range in the current frame
					average_S = video_in.getFrameSaturationAverage();  //average saturation value, threshold for shadow & highlight mask computation


					//lowing pass of V plane(too noisy to work with it..)
					VComp_Extraction(bufferHSV,V_temp,sup_img.width,sup_img.height);
					LowPassFilter(V_temp,sup_img.width,sup_img.height,3);
					VComp_Substitution(bufferHSV,V_temp,sup_img.width,sup_img.height);


					//consider Value bg-substraction(....)
					motion_px = V_BgSubstraction(bufferHSV, BgHSV, bufferBG, sup_img.width, sup_img.height, 0.08);


					memset(shadow,128,sup_img.width*sup_img.height*3);//mainly for set UV comp
					memset(highlight,128,sup_img.width*sup_img.height*3);

					ShadowMask(sup_img.data,bufferHSV,sup_img.width,sup_img.height,shadow);//yuv444
					HighLightMask(sup_img.data,bufferHSV,sup_img.width,sup_img.height,highlight);//yuv444

					//substraction of shadow mask from bufferBG,
					//to obtain tha real motion objects
					Logic_DIFF(bufferBG, shadow, highlight, sup_img.width, sup_img.height, bufferBG);

					//Edge_Extraction(bufferBG,sup_img.data,sup_img.width,sup_img.height,5);


					if(i%1000==0)		//refresh rate for BG frame..
						{
						motion_px = FrameDiff(bufferHSV,previous_buff,bufferDIFF, sup_img.width, sup_img.height);
						//Logic_DIFF(bufferDIFF, shadow, highlight, sup_img.width, sup_img.height, bufferDIFF);
						Logic_DIFF(bufferBG, bufferDIFF,  sup_img.width,sup_img.height,bufferDIFF);
						//memcpy(sup_img.data,bufferDIFF, sup_img.width*sup_img.height*3);

						//Edge_Extraction(bufferDIFF,sup_img.data,sup_img.width,sup_img.height,5);

						for(unsigned int t = 0; t < sup_img.width*sup_img.height*3; t+=3)
							if((int)bufferDIFF[t] == 255)
								{
								double a=0;
								double b=1;//a*background[t]+b*
								background[t] = (unsigned char)(a*background[t]+b*sup_img.data[t]);
								background[t+1] = (unsigned char)(a*background[t+1]+b*sup_img.data[t+1]);
								background[t+2] = (unsigned char)(a*background[t+2]+b*sup_img.data[t+2]);
								}
							//memcpy(sup_img.data,background, sup_img.width*sup_img.height*3);
							video_in.conv_PlanarYUVtoPixelHSV(background,BgHSV,sup_img.width,sup_img.height);

							range_S = video_in.getFrameSaturationRange();  //saturation range in the current frame
							average_S = video_in.getFrameSaturationAverage();  //average saturation value, threshold for shadow & highlight mask computation


							VComp_Extraction(BgHSV,V_temp,sup_img.width,sup_img.height);
							LowPassFilter(V_temp,sup_img.width,sup_img.height,3);
							VComp_Substitution(BgHSV,V_temp,sup_img.width,sup_img.height);

							//memorize previous_frame
							memcpy(previous_buff,bufferHSV, sizeof(float)*sup_img.width*sup_img.height*3);
						}


					//free resources..
					delete[] shadow;
					delete[] highlight;
					//delete[] bufferHSV;//copy of actual frame in HSV
					delete[] bufferDIFF;
					delete[] V_temp;


					}


				OpenClose(bufferBG, sup_img.width, sup_img.height);

				int* label = new int[max_lbl];//array of fused label value
				//int* area_blob = new int[50];//area of area of each region labelled..

				//support array
				unsigned char* temporal = new unsigned char[3*sup_img.width * sup_img.height];
				memset(temporal,128,3*sup_img.width*sup_img.height);


				//in position 0 of nrlabel we have number of label
				//in position 1 of nrlabel we have number of really usefull label
				int nrlabel = Blob_Labeling(bufferBG, temporal, sup_img.width, sup_img.height,label);

			//memcpy(sup_img.data,temporal,3*sup_img.width*sup_img.height);

				//printf("nr_label=%d!!!\n",nrlabel);getchar();

				Blob_tracking(temporal,sup_img.data,bufferHSV,nrlabel,label,sup_img.width,sup_img.height,i);

				delete[] bufferBG; delete[]temporal;delete[] label;
				//delete[] area_blob;//
				delete[] bufferHSV;

				//reconvert to YUV420
				//UV_downsampling(sup_img.data, sup_img.data, sup_img.width, sup_img.height);


				videosmall.getParameters().setVideoFormat("YUV_4:4:4");
				//videosmall.getParameters().setVideoFormat("YUV_4:2:0");
				videosmall << sup_img;



				//free resources
				if(i != video_in.getNumberFrame()-1)
					{
					delete[] sup_img.data;

					}

			}//end if(i>=0) (to remove..)


		else

			video_out << current_img;


		long time = doctor.getElapsedTime()/1000; //in seconds

		if(time != 0 )
			{
			Position.X = 58;
			Position.Y = 19;
			SetConsoleCursorPosition(hOut,Position);
			printf(" %ld fps ) \n", i/time);
			}

		//progress bar
		int cur = 60*i/video_in.getNumberFrame();


		if(cur%2==0 || cur==59)
			{
			BarPosition.X = 6;
			BarPosition.Y = 21;
			FillConsoleOutputCharacter(hOut,'*',cur,BarPosition,&Written);
			}


		if(cur%2 !=0 || cur==59)
			{
			BarPosition.X = 6;
			BarPosition.Y = 22;
			FillConsoleOutputCharacter(hOut,'*',cur,BarPosition,&Written);
			}

		printf("\n\n\n");

		}// for video_in.getnumberframe..



		Position.X = 2;
		Position.Y = 26;
		SetConsoleCursorPosition(hOut,Position);
		for(int c=0;c<20;c++)
			printf("%s",clr);
		//FillConsoleOutputCharacter(hOut,clr,20,Position,&Written);

		Position.X = 2;
		Position.Y = 26;
		SetConsoleCursorPosition(hOut,Position);
	//closing file structure..

//	fclose(fp);motion file.txt

	delete[] previous_labelled;
	return VIPRET_OK;
	}

*/