/** @file    test_vipCodec_RAW.cpp
 *
 *  @brief   Testing code for class vipCoder_RAW.
 *
 *
 *
 *
 *  @bug
 *
 *  @warning
 *  @note
 *
 *  @see     vipCodec_RAW
 *
 *  @version 0.2
 *  @date    20/4/2006
 *  @author  Nicola Piotto
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

#include "../source/vipFrameRGB24.h"
#include "../source/vipFrameYUV420.h"
#include "../source/vipFrameYUV444.h"
#include "../source/outputs/vipDoctor.h"
#include "../source/codecs/vipCodec_BMP.h"
#include "../source/codecs/vipCodec_RAW.h"
#include "../source/filters/vipFilterGeometric.h"


#include <time.h>
#include <stdio.h>


/* Copy and Paste as param_test_ok.xml

<?xml version="1.0" ?>

<vipCodec_RAWParameters>
  <filename value=" test_small.yuv " />
  <stream value=" 0 " />
  <frameIndex value=" 0 " />
  <video format=" YUV_4:2:0 " />
  <width value=" 320 " />
  <height value=" 240 " />
  <frame rate value=" 30 " />
</vipCodec_RAWParameters>


*/
#pragma argsused


int main(int argc, char* argv[])
 {

	vipFilterGeometric myFilterClass;
	vipCodec_RAW myCoderClass;
	vipCodec_RAW myWriter;
	
	vipFrameYUV444 imgYUV;
	vipFrameYUV420 imgYUV2;
	vipFrameRGB24 imgRGB, imgRGBout;
	printf("Testing vipCodec_RAW Development...\n\n");


	printf("\n   Loading Basic Class Information from file (xml)...\n");
	myCoderClass.getParameters().loadFromXML("param_test_ok.xml");

	

	printf("\n   Loading and Processing Basic Class Information from Source file...\n");
	myCoderClass.load();

	
	
	vipCodec_BMP::load(imgRGB, "lena.bmp", vipCodec_BMP::FORMAT_BMP_24);

	myWriter.getParameters().setVideoFormat("YUV_4:2:0");
	myWriter.getParameters().setYwidth(640);
	myWriter.getParameters().setYheight(480);

	myWriter.newVideo("output.yuv");

	
	// RESIZE FILTER PARAMETERS
	
	myFilterClass.getParameters().setRunMode(vipFilterGeometricParameters::RESIZE);	
	myFilterClass.getParameters().setSamplingFactor(2);	
	
	
for (int k=0;k<10; k++){
	
	printf("%d\n", k);
	
	
	myCoderClass >> imgRGB;
	
	
	myFilterClass<<imgRGB;
	myFilterClass>>imgRGB;
	
	imgRGB>>imgYUV;
	//imgYUV>>imgRGB;
	
	//imgYUV>>imgYUV2;
	//vipCodec_BMP::save(imgRGB, "frameRGB.bmp", vipCodec_BMP::FORMAT_BMP_24);

	//myWriter << imgYUV2;
}

	printf("\n\n   Closing Basic Classes Structures...\n");
	myCoderClass.close();

	printf("\n   Saving Basic Class Information to file (xml)...\n");
	myCoderClass.getParameters().saveToXML("param_test_out.xml");

	printf("\n\n\nTest Completed. Type something to continue...\n");
	getchar();




	return 0;
 }

