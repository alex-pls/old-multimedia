/** @file vipLogic
 *
 * File containing methods for the 'vipLogic' header.
 * The header for this class can be found in vipLogic.h, check
 * that file for class description.
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


#include "vipLogic.h"
#include <string.h>


/**
* @brief  make the logic and ("&") operation pixel x pixel of 2 input img
*
* @param[in1,in2] input structure in HSV color space
* @param[out] output structure
* @param[width,height] img dimension
* @return VIPRET_OK,....
*/
int Logic_AND(unsigned char* in1, unsigned char*in2, int width, int height, unsigned char* out)
	{
	unsigned char* buff = new unsigned char[width*height*3]; // temp buffer
	memset(buff,128,width*height*3);//care on UV comp

	for(int row = 0; row < height; row++)
		for(int col = 0; col < width; col++)
			{
			buff[row*width+col] = (unsigned char)(  (in1[row*width+col]/255)*
				(in2[row*width+col]/255)*255  );  // in 0 - 255
			}

		memcpy(out,buff,width*height*3);

		delete[] buff;
		return VIPRET_OK;
	}


/**
* @brief  make the substraction pixel x pixel of 3 input img
*
* @param[in1,in2,in3] input structure in HSV color space
* @param[out] output structure
* @param[width,height] img dimension
* @return VIPRET_OK,....
*/
int Logic_DIFF(unsigned char* in1, unsigned char* in2, unsigned char* in3, int width, int height, unsigned char* out)
	{
	unsigned char* buff = new unsigned char[width*height*3];
	memset(buff,128,width*height*3);

	for(int row = 0; row < height; row++)
		for(int col = 0; col < width; col++)
			{			// in 0 - 255
			buff[row*width+col] = (unsigned char)(in1[row*width+col]-in2[row*width+col]-in3[row*width+col]);
			if((int)buff[row*width+col]<=128) buff[row*width+col] = (unsigned char) 0;
			else buff[row*width+col] = (unsigned char) 255;
			}

		memcpy(out,buff,width*height*3);

		delete[] buff;
		return VIPRET_OK;
	}

/**
* @brief  make the substraction pixel x pixel of 2 input img
*
* @param[in1,in2] input structure in HSV color space
* @param[out] output structure
* @param[width,height] img dimension
* @return VIPRET_OK,....
*/
int Logic_DIFF(unsigned char* in1, unsigned char* in2,int width, int height, unsigned char* out)
	{
	unsigned char* buff = new unsigned char[width*height*3];
	memset(buff,128,width*height*3);

	for(int row = 0; row < height; row++)
		for(int col = 0; col < width; col++)
			{			// in 0 - 255
			buff[row*width+col] = (unsigned char)(in1[row*width+col]-in2[row*width+col]);
			if((int)buff[row*width+col]<0) buff[row*width+col] = -buff[row*width+col];//(unsigned char)0;
			}

		memcpy(out,buff,width*height*3);

		delete[] buff;
		return VIPRET_OK;
	}





/*function to verify the presence of value into in1[nrlabel] array
return 0 if the presence is not found else
return 1 */
int array_cmp(int* in1, int nrlabel, int value)
	{
	int tmp=0;

	if(nrlabel==0)
		return 0;
	else
		{
		for(int cont=0; cont<nrlabel;cont++)
			if(in1[cont] != value)
				tmp++;

		if(tmp==nrlabel)
			return 0; //ok, value not in the array
		else
			return 1;  //value already present in the array
		}

	}


int array_cmp(unsigned char* in1, int nrlabel, unsigned char value)
	{
	int tmp=0;

	if(nrlabel==0)
		return 0;
	else
		{
		for(int cont=0; cont<nrlabel;cont++)
			if(in1[cont] != value)
				tmp++;

		if(tmp==nrlabel)
			return 0; //ok, value not in the array
		else
			return 1;  //value already present in the array
		}

	}


