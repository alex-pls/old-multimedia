/** @file    test_vipPlainFrameGenerator.cpp
 *
 *  @brief   Testing code for class vipPlainFrameGenerator.
 *
 *           Create a monocrome frame, tests max frame rate (memcpy),
 *           then set frame rate to 20 fps and test it.
 *
 *  @see     vipPlainFrameGenerator
 *  @see     vipDoctor
 *
 *  @version 1.0.2
 *  @date    06/08/2005
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

#include "../source/PixelRGB.h"
#include "../source/vipFrameRGB96.h"
#include "../source/vipFrameRGB24.h"
#include "../source/codecs/vipCodec_BMP.h"
#include "../source/outputs/vipDoctor.h"

#include "../source/inputs/vipPlainFrameGenerator.h"


#include <stdio.h>

#pragma argsused


int main(int argc, char* argv[])
 {
	printf("Testing vipPlainFrameGenerator Development...\n");

	printf("\nCreating Instances...\n");
	vipDoctor doc;
	vipFrameRGB96 img(640, 480);
	vipFrameRGB96 img24(640, 480);
	long time = 0;
	int i = 0;
	float fps = 0;
	vipPlainFrameGenerator plaing;

	PixelRGB background(130,80,50);
	plaing.setFrameColor(background);

	printf("\nStarting frame loading loop... (with vipFrameRGB96)\n");
	doc.reset(true);
	while (i++ < 10)
	 {
		plaing >> img;
	 }

	time = doc.getElapsedTime();
	fps = (float)10000/(float)doc.getElapsedTime();

	printf("Elapsed milliseconds : %ld\n", time );
	printf("(Max possible) Average Frame Rate : %f fps\n", fps );


	printf("\nStarting frame loading loop... (with vipFrameRGB24)\n");
	i = 0;
	time = 0;
	fps = 0;
	doc.reset(true);
	while (i++ < 10)
	 {
		plaing >> img24;
	 }

	time = doc.getElapsedTime();
	fps = (float)10000/(float)doc.getElapsedTime();

	printf("Elapsed milliseconds : %ld\n", time );
	printf("(Max possible) Average Frame Rate : %f fps\n", fps );


	plaing.setFrameRate(25);

	printf("\nStarting frame loading loop...\n");
	i = 0;
	time = 0;
	fps = 0;
	doc.reset(true);
	while (i++ < 10)
	 {
		plaing >> img;
	 }

	time = doc.getElapsedTime();
	fps = (float)10000/(float)doc.getElapsedTime();

	printf("Elapsed milliseconds : %ld\n", time );
	printf("Average Frame Rate : %f fps [should be around 25fps]\n", fps );


	printf("\nSaving frames...\n");

	vipCodec_BMP::save(img, "PlainFrame_R130G80B50.bmp", vipCodec_BMP::FORMAT_BMP_24);


	printf("Test Completed. Type something to continue...\n");
	getchar();

	return 0;
 }
//---------------------------------------------------------------------------
