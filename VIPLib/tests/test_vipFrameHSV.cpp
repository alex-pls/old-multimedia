/** @file    test_vipFrameHSV.cpp
 *
 *  @brief   Testing code for class vipFrameHSV.
 *
 *
 *
 *
 *
 *  @bug
 *  @warning
 *  @todo
 *
 *  @see     vipFrameHSV
 *
 *  @version 1.0
 *  @date    26/08/2005
 *  @author  Alessandro Polo
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

#include "../source/vipFrameRGB96.h"
#include "../source/vipFrameHSV.h"
#include "../source/vipFrameRGB24.h"
#include "../source/vipFrameGrey.h"
#include "../source/codecs/vipCodec_BMP.h"

#include <stdio.h>

#pragma argsused

int main(int argc, char* argv[])
 {
	printf("Testing vipFrameHSV development..\n");

	printf("\nCreating Instances...\n");
	vipFrameRGB96 img, img2;
	vipCodec_BMP::load(img, "frame1.bmp", vipCodec_BMP::FORMAT_BMP_24);

	vipFrameHSV myFrame;
	source >> img;

	myFrame << img;
	myFrame >> img2;

	vipCodec_BMP::save(img2, "OUT_frame1_COPY.bmp", vipCodec_BMP::FORMAT_BMP_24);

	for (unsigned int x=200; x < 400;x++)
		for (unsigned int y=200; y < 210;y++)
			myFrame.setHSV(x, y, 0, 0, 0);

	myFrame >> img;

	vipCodec_BMP::save(img, "OUT_frame2_LINE.bmp", vipCodec_BMP::FORMAT_BMP_24);

	vipFrameRGB myGFrame(img.width, img.height);

	myFrame >> myGFrame;
	myFrame << myGFrame;

	vipCodec_BMP::save(myGFrame, "OUT_frame1_RGB.bmp", vipCodec_BMP::FORMAT_BMP_24);

	printf("Test Completed. Type something to continue...\n");
	getchar();

	return 0;
 }
//---------------------------------------------------------------------------
