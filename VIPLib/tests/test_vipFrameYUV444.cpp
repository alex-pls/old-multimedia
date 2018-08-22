/** @file    test_vipFrameYUV420.cpp
 *
 *  @brief   Testing code for class vipFrameYUV420.
 *
 *
 *
 *
 *
 *  @bug
 *  @warning
 *  @todo
 *
 *  @see     vipFrameYUV420
 *
 *  @version 1.0
 *  @date    25/10/2006
 *  @author  Nicola Conci
 *
 *
 ****************************************************************************
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.science.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DIT - University of Trento
 *
 ****************************************************************************/


//---------------------------------------------------------------------------

#pragma hdrstop

//---------------------------------------------------------------------------

#include "../source/vipFrameRGB24.h"
#include "../source/vipFrameYUV420.h"
#include "../source/codecs/vipCodec_BMP.h"
#include "../source/vipUtility.h"

#include <stdio.h>

#pragma argsused

int main(int argc, char* argv[])
 {
	printf("Testing vipFrameYUV444 development..\n");

	printf("\nCreating Instances...\n");
	vipFrameRGB24 img, img2;
	vipCodec_BMP::load(img, "test.bmp", vipCodec_BMP::FORMAT_BMP_24);

	unsigned char* data= new unsigned char[img.width*img.height*3];
	

	//img2 << img;
	vipUtility::conv_PixelRGB24toPlanarYUV444(img.data[0], data, img.width, img.height);

	// make it blank to check it is real
	//for (int i =0; i<img.width*img.height/2; i++)
	//	data[i] = '/0';


	vipUtility::conv_PlanarYUV444toPixelRGB24(data, img.data[0], img.width, img.height);


	vipCodec_BMP::save(img, "OUT_frame1_COPY.bmp", vipCodec_BMP::FORMAT_BMP_24);

	
	printf("Test Completed. Type something to continue...\n");
	getchar();

	return 0;
 }
//---------------------------------------------------------------------------
