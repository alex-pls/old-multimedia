/** @file    test_vipDigitalFilter.cpp
 *
 *  @brief   Testing code for class vipDigitalFilter.cpp.
 *
 *           Applies noise on a frame, tests frame rate, use and external
 *           noise source (vipNoiseGenerator) and save outputs.
 *
 *
 *  @see     vipDigitalFilter.cpp
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

#include "../source/vipFrameT.h"
#include "../source/vipFrameRGB24.h"

#include "../source/codecs/vipCodec_BMP.h"
#include "../source/outputs/vipDoctor.h"

#include "../source/filters/vipDigitalFilter.h"


#include <stdio.h>

#pragma argsused



int main(int argc, char* argv[])
 {
	printf("Testing vipDigitalFilter.cpp development...\n");

	printf("\nCreating Instances...\n");
	vipDoctor doc;
	vipFrameRGB96 img;
	vipFrameRGB24 img24;
	int i = 0;
	long time = 0;
	float fps = 0 ;

	printf("\nasdasdhgnbnbn.\n");
	vipDFMatrix* gauss = vipDFMatrix::createKernel_3x3(VETDF_3x3_lowpass2);


	printf("\nLoading Images...\n");
	vipCodec_BMP::load(img, "frame1.bmp", vipCodec_BMP::FORMAT_BMP_24);
	vipCodec_BMP::load(img24, "frame1.bmp", vipCodec_BMP::FORMAT_BMP_24);

	printf("\nSetting Parameters...\n");

	printf("\nStarting frame processing... (with vipFrameRGB24)\n");

	vipFrameRGB96 img2(img.width, img.height);
	vipFrameRGB24 img242(img.width, img.height);

	vipDigitalFilter::doProcessing(img24, img242, *gauss);

	printf("\nSaving frame...\n");
	vipCodec_BMP::save(img242, "OUT_GAUSSIAN_3x3.bmp", vipCodec_BMP::FORMAT_BMP_24);



	vipFrameT<float> im(img.width, img.height);
	vipFrameT<float> im2(img.width, img.height);
	for (unsigned int i=0; i< img.width*img.height; i++)
		im.data[i] = (float)( (float)img24.data[i][0] * RED_COEF + (float)img24.data[i][0] * GREEN_COEF + (float)img24.data[i][0] * BLUE_COEF );

	printf("\nStarting frame processing... (with vipFrameT<float>)\n");
	vipDigitalFilter::doProcessing(im, im2, *gauss);

	for (unsigned int i=0; i< img.width*img.height; i++)
	 {
		img242.data[i][0] = (unsigned char) im2.data[i];
		img242.data[i][1] = (unsigned char) im2.data[i];
		img242.data[i][2] = (unsigned char) im2.data[i];
	 }

	printf("\nSaving frame...\n");
	vipCodec_BMP::save(img242, "OUT_GAUSSIAN_3x3_FLOAT.bmp", vipCodec_BMP::FORMAT_BMP_24);

	for (unsigned int i=0; i< img.width*img.height; i++)
	 {
		img242.data[i][0] = (unsigned char) (im.data[i] - im2.data[i]);
		img242.data[i][1] = (unsigned char) (im.data[i] - im2.data[i]);
		img242.data[i][2] = (unsigned char) (im.data[i] - im2.data[i]);
	 }

	vipCodec_BMP::save(img242, "OUT_GAUSSIAN_3x3_DIFFERENCE.bmp", vipCodec_BMP::FORMAT_BMP_24);

/////////////// USE AS A FILTER :

	printf("\nTesting run as a filter...\n");

	vipDigitalFilter myFilter;


	myFilter.setDefaultKernel(VETDF_3x3_edge_sd_hv);

	printf("\nStarting frame redirection... (with vipFrameRGB96)\n");
	doc.reset(true);
	myFilter << img;
	myFilter >> img2;

	time = doc.getElapsedTime();
	fps = (float)100000/(float)doc.getElapsedTime();
	printf("Elapsed milliseconds : %ld\n", time );
	printf("(Max possible) Average Frame Rate : %f fps\n", fps );

	printf("\nSaving frame...\n");
	vipCodec_BMP::save(img2, "OUT_edge_sd_hv_3x3.bmp", vipCodec_BMP::FORMAT_BMP_24);

	printf("\nStarting frame redirection... (with vipFrameRGB24)\n");
	doc.reset(true);
	myFilter << img24;
	myFilter >> img242;
	fps = (float)100000/(float)doc.getElapsedTime();
	printf("Elapsed milliseconds : %ld\n", time );
	printf("(Max possible) Average Frame Rate : %f fps\n", fps );

	printf("\nSaving frame...\n");
	vipCodec_BMP::save(img242, "OUT_edge_sd_hv_3x3_24b.bmp", vipCodec_BMP::FORMAT_BMP_24);


	printf("\nParameters Serialization (XML)...\n");
	myFilter.setDefaultKernel(VETDF_3x3_edge_sd_hv);
	myFilter.useBuffer24();
	myFilter.getParameters().setClampNegative(true);
	myFilter.getParameters().saveToXML("digital.XML");

//BUG
//	vipDigitalFilter myFilter2;
//	myFilter2.getParameters().loadFromXML("digital.XML");
//	myFilter2.getParameters().saveToXML("digital_COPY.XML");

	printf("Test Completed. Type something to continue...\n");
	getchar();

	return 0;
 }
//---------------------------------------------------------------------------









