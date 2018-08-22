/** @file    test_vipInputSample.cpp
 *
 *  @brief   Testing code for class vipInputSample.
 *
 *
 *
 *
 *  @bug
 *
 *  @warning
 *  @note
 *
 *  @see     vipInputSample
 *
 *  @version 1.0
 *  @date    19/05/2006 7.25.41
 *  @author  Alessandro Polo
 *
 ****************************************************************************
 *  Source based on Package Studio template: vipInputTemplate version 0.9.12
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

#include "I:\Projects\Software\VIPLib\source\vipFrameYUV420.h"
#include "I:\Projects\Software\VIPLib\source\vipFrameRGB24.h"
#include "I:\Projects\Software\VIPLib\source\outputs/vipDoctor.h"
#include "I:\Projects\Software\VIPLib\source\codecs/vipCodec_BMP.h"
#include "vipInputSample.h"


//---------------------------------------------------------------------------
#include <stdio.h>

int main(int argc, char* argv[])
 {

	printf("Testing vipInputSample Development...\n");

	printf("\nCreating Instances...\n");
	vipFrameYUV420 img(320, 240);
	vipFrameYUV420 img24(320, 240);
	vipDoctor doc;
	long time = 0;
	int i = 0;
	float fps = 0;
	vipInputSample myInputClass;

	printf("\nStarting frame loading loop... (with vipFrameYUV420)\n");
	doc.reset(true);
	while (i++ < 10)
	 {
		myInputClass >> img;
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
		myInputClass >> img24;
	 }

	time = doc.getElapsedTime();
	fps = (float)10000/(float)doc.getElapsedTime();

	printf("Elapsed milliseconds : %ld\n", time );
	printf("(Max possible) Average Frame Rate : %f fps\n", fps );

	myInputClass.setFrameRate(30);

	printf("\nStarting frame loading loop...\n");
	i = 0;
	time = 0;
	fps = 0;
	doc.reset(true);
	while (i++ < 10)
	 {
		myInputClass >> img;
	 }

	time = doc.getElapsedTime();
	fps = (float)10000/(float)doc.getElapsedTime();

	printf("Elapsed milliseconds : %ld\n", time );
	printf("Average Frame Rate : %f fps [should be around 30fps]\n", fps );


	printf("\nSaving frames...\n");

	vipCoder_BMP::save(img, "vipInputSample_OUT1.bmp", vipCoder_BMP::FORMAT_BMP_24);
	vipCoder_BMP::save(img24, "vipInputSample_OUT2_24b.bmp", vipCoder_BMP::FORMAT_BMP_24);


	printf("Test Completed. Type something to continue...\n");
	getchar();



	return 0;
 }



