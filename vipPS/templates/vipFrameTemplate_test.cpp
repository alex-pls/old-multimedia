/** @file    test_%CLASSNAME%.cpp
 *
 *  @brief   Testing code for class %CLASSNAME%.
 *
 *
 *
 *
 *  @bug
 *
 *  @warning
 *  @note
 *
 *  @see     %CLASSNAME%
 *
 *  @version %VERSION%
 *  @date    %TODAY%
 *  @author  %AUTHOR%
 *
 ****************************************************************************
 *  Source based on Package Studio template: vipFrameTemplate version 0.9.12
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


#include "%SOURCEDIR%vipFrameYUV420.h"
#include "%SOURCEDIR%vipFrameRGB24.h"
#include "%SOURCEDIR%codecs/vipCodec_BMP.h"
#include "%CLASSNAME%.h"


#include <stdio.h>

#pragma argsused

int main(int argc, char* argv[])
 {
	printf("Testing %CLASSNAME% development..\n");

	printf("\nCreating Instances...\n");
	vipCodec_BMP source("frame1.bmp", vipCodec_BMP::FORMAT_BMP_24);
	vipCodec_BMP saver;
	vipFrameRGB24 img, img2;
	vipFrameYUV420 myFrame;

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
