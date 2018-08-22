/** @file    test_vipFilterNoiseChannel.cpp
 *
 *  @brief   Testing code for class vipFilterNoiseChannel.
 *
 *           Applies noise on a frame, tests frame rate, use and external
 *           noise source (vipNoiseGenerator) and save outputs.
 *
 *
 *  @see     vipFilterNoiseChannel
 *  @see     vipDoctor
 *  @see     vipNoiseGenerator
 *
 *  @version 1.0.2
 *  @date    30/08/2005
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

#include "../source/codecs/vipCodec_BMP.h"
#include "../source/vipFrameRGB96.h"

#include "../source/inputs/vipNoiseGenerator.h"
#include "../source/outputs/vipDoctor.h"

#include "../source/filters/vipFilterNoiseChannel.h"


#include <stdio.h>

#pragma argsused


int main(int argc, char* argv[])
 {
	printf("Testing vipFilterNoiseChannel development...\n");

	printf("\nCreating Instances...\n");
	vipDoctor doc;
	vipFrameRGB96 img, img2;
	vipFrameRGB24 img24, img242;
	int i = 0;
	long time = 0;
	float fps = 0 ;
	vipFilterNoiseChannel myChannel;

	printf("\nLoading Images...\n");
	vipCodec_BMP::load(img, "frame1.bmp", vipCodec_BMP::FORMAT_BMP_24);
	vipCodec_BMP::load(img24, "frame1.bmp", vipCodec_BMP::FORMAT_BMP_24);

	printf("\nSetting Parameters...\n");
	myChannel.getParameters().setNormalisedNoise(true);
	myChannel.getParameters().setNormalisedNoiseValue(100);
	myChannel.getParameters().setSpread(10);

	printf("\nStarting frame redirection loop... (with vipFrameRGB96)\n");
	doc.reset(true);
	while (i++ < 100)
	 {
		myChannel << img;
		myChannel >> img2;
	 }

	time = doc.getElapsedTime();
	fps = (float)100000/(float)doc.getElapsedTime();

	printf("Elapsed milliseconds : %ld\n", time );
	printf("(Max possible) Average Frame Rate : %f fps\n", fps );

	printf("\nSaving frame...\n");
	vipCodec_BMP::save(img2, "OUT_NOISE1.bmp", vipCodec_BMP::FORMAT_BMP_24);

	printf("\nStarting frame redirection loop... (with vipFrameRGB24)\n");
	i = 0;
	time = 0;
	fps = 0;
	doc.reset(true);
	while (i++ < 100)
	 {
		myChannel << img24;
		myChannel >> img242;
	 }

	time = doc.getElapsedTime();
	fps = (float)100000/(float)doc.getElapsedTime();

	printf("Elapsed milliseconds : %ld\n", time );
	printf("(Max possible) Average Frame Rate : %f fps\n", fps );

	printf("\nSaving frame...\n");
	vipCodec_BMP::save(img242, "OUT_NOISE1_24b.bmp", vipCodec_BMP::FORMAT_BMP_24);


	printf("\nUsing External Noise source...\n");
	vipNoiseGenerator noiseg;
	myChannel.setNoiseSource(noiseg);

//	myChannel.setNoiseSourceFactor(0.1);
	myChannel.setFrameRate(40);

	printf("\nStarting frame redirection loop... (with vipFrameRGB24)\n");
	i = 0;
	time = 0;
	fps = 0;
	doc.reset(true);
	while (i++ < 100)
	 {
		myChannel << img24;
		myChannel >> img242;
	 }

	time = doc.getElapsedTime();
	fps = (float)100000/(float)doc.getElapsedTime();

	printf("Elapsed milliseconds : %ld\n", time );
	printf("Average Frame Rate : %f fps (should be around 40)\n", fps );

	printf("\nSaving frame...\n");
	vipCodec_BMP::save(img242, "OUT_NOISE_EXTSOURCE.bmp", vipCodec_BMP::FORMAT_BMP_24);


	printf("\nParameters Serialization (XML)...\n");
	myChannel.getParameters().setNormalisedNoise(true);
	myChannel.getParameters().setNormalisedNoiseValue(100);
	myChannel.getParameters().setSpread(5.5255);
	myChannel.getParameters().saveToXML("noisech.XML");

	vipFilterNoiseChannel myChannel2;
	myChannel2.getParameters().loadFromXML("noisech.XML");
	myChannel2.getParameters().saveToXML("noisech_COPY.XML");


	printf("Test Completed. Type something to continue...\n");
	getchar();

	return 0;
 }
//---------------------------------------------------------------------------

