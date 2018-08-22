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

#include "%SOURCEDIR%vipFrameYUV420.h"
#include "%SOURCEDIR%vipFrameRGB24.h"
#include "%SOURCEDIR%outputs/vipDoctor.h"
#include "%SOURCEDIR%codecs/vipCodec_BMP.h"
#include "%CLASSNAME%.h"


//---------------------------------------------------------------------------
#include <stdio.h>

int main(int argc, char* argv[])
 {

	printf("Testing %CLASSNAME% Development...\n");

	printf("\nCreating Instances...\n");
	%CLASSNAME% myCodecClass;
	vipDoctor doc;

%EFI_START%
	int ret = myCodecClass.load("source.extension");

	if ( ret == VIPRET_OK)
		printf("Stream loaded.\n");
	else
	 {
		printf("Stream HAS NOT BEEN loaded.\n");
		return 1;
	 }
%EFI_END%

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

%EFI_START%
	myCodecClass.getParameters().setFileName("source.extension");
	myCodecClass.getParameters().setFrameIndex(1000);
	myCodecClass.getParameters().setStream(0);
%EFI_END%
	myCodecClass.getParameters().saveToXML("%CLASSNAME%_param.XML");


	%CLASSNAME% myCodecClass2;

	myCodecClass2.getParameters().loadFromXML("%CLASSNAME%_param.XML");
	myCodecClass2.getParameters().saveToXML("%CLASSNAME%_param_COPY.XML");


	printf("Test Completed. Type something to continue...\n");
	getchar();


	return 0;
 }

