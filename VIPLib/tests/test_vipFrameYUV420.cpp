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

#include <stdio.h>

#pragma argsused

int main(int argc, char* argv[])
 {
	printf("Testing vipFrameHSV development..\n");

	printf("\nCreating Instances...\n");
	vipFrameRGB24 img, img2;
	vipCodec_BMP::load(img, "test.bmp", vipCodec_BMP::FORMAT_BMP_24);

	vipFrameYUV420 myFrame;
	
	//img2 << img;
	

	vipCodec_BMP::save(img2, "OUT_frame1_COPY.bmp", vipCodec_BMP::FORMAT_BMP_24);

	for (unsigned int x=0; x < 352;x++)
		for (unsigned int y=0; y < 288;y++)
			//myFrame.setPixel(x, y, 0, 0, 0);
			myFrame.setBlack();

	myFrame >> img;

	vipCodec_YUV::save(img, "OUT_frame2_LINE.bmp", vipCodec_BMP::FORMAT_BMP_24);

	printf("Test Completed. Type something to continue...\n");
	getchar();

	return 0;
 }
//---------------------------------------------------------------------------
