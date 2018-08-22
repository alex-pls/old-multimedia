/** @file    test_vipFrameGrey.cpp
 *
 *  @brief   Testing code for class vipFrameGrey.
 *
 *
 *
 *
 *
 *  @bug
 *  @warning
 *  @todo
 *
 *  @see     vipFrameGrey
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
#include "../source/vipFrameRGB.h"
#include "../source/vipFrameGrey.h"
#include "../source/codecs/vipCodec_BMP.h"


#include <stdio.h>

#pragma argsused

int main(int argc, char* argv[])
 {
	printf("Testing vipFrameGrey development..\n");

	printf("\nCreating Instances...\n");
	vipCodec_BMP source("frame1.bmp", vipCodec_BMP::FORMAT_BMP_24);
	vipCodec_BMP saver;
	vipFrameRGB96 img, img2;
	vipFrameGrey myFrame;

	source >> img;

	myFrame << img;
	myFrame >> img2;

	saver.save(myFrame, "OUT_frame1_ToGrey.bmp", vipCodec_BMP::FORMAT_BMP_24);
	vipCodec_BMP::save(img2, "OUT_frame1_ToGrey_COPY.bmp", vipCodec_BMP::FORMAT_BMP_24);

	source.load(myFrame, "frame1Grey.bmp", vipCodec_BMP::FORMAT_BMP_24);
	saver.save(myFrame, "OUT_frame1Grey_COPY.bmp", vipCodec_BMP::FORMAT_BMP_24);


	printf("Test Completed. Type something to continue...\n");
	getchar();

	return 0;
 }
//---------------------------------------------------------------------------
