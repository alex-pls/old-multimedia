/** @file    test_vipNoiseGenerator.cpp
 *
 *  @brief   Testing code for class vipNoiseGenerator.
 *
 *           Create a noise frame, tests max frame rate (memcpy),
 *           then set frame rate to 30 fps and test it.
 *
 *
 *  @see     vipNoiseGenerator
 *  @see     vipFilterNoiseChannel
 *  @see     vipDoctor
 *
 *  @version 1.0.2
 *  @date    22/08/2005
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
#include "../source/codecs/vipCodec_BMP.h"

#include "../source/inputs/vipNoiseGenerator.h"
#include "../source/outputs/vipDoctor.h"

#include "../source/filters/vipFilterNoiseChannel.h"


#include <stdio.h>

#pragma argsused


int main(int argc, char* argv[])
 {
	printf("Testing vipNoiseGenerator Development...\n");

	printf("\nCreating Instances...\n");
	vipFrameRGB96 img(320, 240);
	vipFrameRGB96 img24(320, 240);
	vipDoctor doc;
	long time = 0;
	int i = 0;
	float fps = 0;
	vipNoiseGenerator noise;

	printf("\nStarting frame loading loop... (with vipFrameRGB96)\n");
	doc.reset(true);
	while (i++ < 10)
	 {
		noise >> img;
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
		noise >> img24;
	 }

	time = doc.getElapsedTime();
	fps = (float)10000/(float)doc.getElapsedTime();

	printf("Elapsed milliseconds : %ld\n", time );
	printf("(Max possible) Average Frame Rate : %f fps\n", fps );

	noise.setFrameRate(30);

	printf("\nStarting frame loading loop...\n");
	i = 0;
	time = 0;
	fps = 0;
	doc.reset(true);
	while (i++ < 10)
	 {
		noise >> img;
	 }

	time = doc.getElapsedTime();
	fps = (float)10000/(float)doc.getElapsedTime();

	printf("Elapsed milliseconds : %ld\n", time );
	printf("Average Frame Rate : %f fps [should be around 30fps]\n", fps );


	printf("\nSaving frames...\n");

	vipCodec_BMP::save(img, "NoiseGenerator_OUT1.bmp", vipCodec_BMP::FORMAT_BMP_24);
	vipCodec_BMP::save(img24, "NoiseGenerator_OUT2_24b.bmp", vipCodec_BMP::FORMAT_BMP_24);


	printf("Test Completed. Type something to continue...\n");
	getchar();

	return 0;
 }
//---------------------------------------------------------------------------
