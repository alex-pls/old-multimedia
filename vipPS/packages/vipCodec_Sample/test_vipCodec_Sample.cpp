/** @file    test_vipCodec_Sample.cpp
 *
 *  @brief   Testing code for class vipCodec_Sample.
 *
 *
 *
 *
 *  @bug
 *
 *  @warning
 *  @note
 *
 *  @see     vipCodec_Sample
 *
 *  @version 1.0
 *  @date    19/05/2006 7.25.22
 *  @author  Alessandro Polo
 *
 ****************************************************************************
 *  Source based on Package Studio template: vipCodec_Template version 0.9.12
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
#include "vipCodec_Sample.h"


//---------------------------------------------------------------------------
#include <stdio.h>

int main(int argc, char* argv[])
 {

	printf("Testing vipCodec_Sample Development...\n");

	printf("\nCreating Instances...\n");
	vipCodec_Sample myCodecClass;
	vipDoctor doc;


	int ret = myCodecClass.load("source.extension");

	if ( ret == VIPRET_OK)
		printf("Stream loaded.\n");
	else
	 {
		printf("Stream HAS NOT BEEN loaded.\n");
		return 1;
	 }


	printf("\nStream INFO:\n");

	printf(" VIDEO STREAMS COUNT: %d\n", myCodecClass.getVideoStreamCount() );
//	printf(" VIDEO STREAM [0] FRAME RATE: %f\n", myCodecClass.getVideoFrameRate() );
//	printf(" VIDEO STREAM [0] FRAME COUNT: %ld\n", myCodecClass.getVideoStreamLenght() );
	printf(" VIDEO STREAM [0] WIDTH: %d\n", myCodecClass.getWidth() );
	printf(" VIDEO STREAM [0] HEIGHT: %d\n", myCodecClass.getHeight() );


	printf(" AUDIO STREAMS COUNT: %d\n", myCodecClass.getAudioStreamCount() );
//	printf(" AUDIO STREAM [0] CHANNELS: %d\n", myCodecClass.getAudioChannels() );
//	printf(" AUDIO STREAM [0] SAMPLE RATE: %f\n", myCodecClass.getAudioSampleRate() );
//	printf(" AUDIO STREAM [0] SAMPLE COUNT: %ld\n", myCodecClass.getAudioStreamLenght() );

	vipFrameRGB24 img24a(myCodecClass.getWidth(), myCodecClass.getHeight());
	vipFrameRGB24 img24b(myCodecClass.getWidth(), myCodecClass.getHeight());

	printf("\nExtracting frames..\n");

	myCodecClass >> img24a;
	myCodecClass >> img24b;

	vipCodec_BMP::save(img24a, "Extracted_Frame1.bmp", vipCodec_BMP::FORMAT_BMP_24);
	vipCodec_BMP::save(img24b, "Extracted_Frame2.bmp", vipCodec_BMP::FORMAT_BMP_24);


	printf("\nParameters Serialization (XML)...\n");


	myCodecClass.getParameters().setFileName("source.extension");
	myCodecClass.getParameters().setFrameIndex(1000);
	myCodecClass.getParameters().setStream(0);

	myCodecClass.getParameters().saveToXML("vipCodec_Sample_param.XML");


	vipCodec_Sample myCodecClass2;

	myCodecClass2.getParameters().loadFromXML("vipCodec_Sample_param.XML");
	myCodecClass2.getParameters().saveToXML("vipCodec_Sample_param_COPY.XML");


	printf("Test Completed. Type something to continue...\n");
	getchar();


	return 0;
 }

