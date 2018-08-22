/** @file    test_vipOutputDWT.cpp
 *
 *  @brief   Testing code for class vipOutputDWT.
 *
 *
 *
 *
 *  @bug
 *
 *  @warning
 *  @note
 *
 *  @see     vipOutputDWT
 *
 *  @version 1.0
 *  @date    28/09/2007 10.29.31
 *  @author  Valentina Pasqualino
 *
 ****************************************************************************
 *  Source based on Package Studio template: vipOutputTemplate version 0.9.12
 ****************************************************************************
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.science.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DIT - University of Trento
 *
 ****************************************************************************/


//---------------------------------------------------------------------------

#include "../../source/vipFrameYUV420.h"
#include "../../source/vipFrameRGB24.h"
#include "../../source/codecs/vipCodec_BMP.h"
#include "../../source/outputs/vipDoctor.h"

#include "vipOutputDWT.h"


//---------------------------------------------------------------------------
#include <stdio.h>

int main(int argc, char* argv[]){
	printf("Testing vipOutputDWT Development...\n");


	printf("\nCreating Instances...\n");
	
	vipFrameRGB24 img;			// source image (.. now empty)
	vipOutputDWT myOutputClass;	// subject component


	printf("Loading Frame...\n");
	vipCodec_BMP::load(img, "lena.bmp", vipCodec_BMP::FORMAT_BMP_24);
								// load an image from BMP 24bit (true color)

	printf("Start Processing...\n\n");


	myOutputClass.setIteration(1); // 0 = filter 5/3; 1 = filter 9/7
	myOutputClass.setFilter(1);
	myOutputClass << img;	

	//myOutputClass.imgOut.saveToFile("prova.txt");


	printf("\n\nTest Completed. Type a key to continue...\n");
	getchar();


	return 0;
 }
