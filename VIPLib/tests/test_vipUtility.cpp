/** @file    test_vipUtility.cpp
 *
 *  @brief   Testing code for template class vipUtility.
 *
 *
 *
 *
 *
 *  @bug
 *  @warning
 *  @todo
 *
 *  @see     vipNoiseGenerator
 *  @see     vipFilterNoiseChannel
 *  @see     vipDoctor
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

//#pragma hdrstop

//---------------------------------------------------------------------------

#include "../source/vipFrameT.h"
#include "../source/vipFrameRGB96.h"
#include "../source/vipFrameRGB24.h"
#include "../source/vipFrameYUV444.h"
#include "../source/vipFrameYUV420.h"
#include "../source/codecs/vipCodec_BMP.h"

#include "../source/vipUtility.h"

#include <stdio.h>

//#pragma argsused


int main(int argc, char* argv[])
 {
	printf("Testing vipUtility Development...\n");

	printf("\nCreating Instances...\n");

	
	vipFrameRGB24 img, img2;
	vipFrameYUV444 frame444;
	vipFrameYUV420 frame420;

	vipCodec_BMP::load(img, "lena.bmp", vipCodec_BMP::FORMAT_BMP_24);



	printf("\nTesting Pixel-Packed <-> Channel-Packed functions...\n");

	//unsigned char* buffer_c = new unsigned char[img.width*img.height*3];
 
	img>>frame444;
	frame444>>frame420;
	frame420>>img2;
	
	

	vipCodec_BMP::save(img2, "frame1_COPY1_24b.bmp", vipCodec_BMP::FORMAT_BMP_24);


	printf("Test Completed. Type something to continue...\n");
	getchar();

	return 0;
 }
//---------------------------------------------------------------------------
