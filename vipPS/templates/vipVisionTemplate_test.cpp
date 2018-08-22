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
 *  Source based on Package Studio template: vipVisionTemplate version 0.9.12
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
#include "%SOURCEDIR%outputs/vipDoctor.h"

#include "%CLASSNAME%.h"


//---------------------------------------------------------------------------
#include <stdio.h>


void* myAlertFunction(void* myArgumentStruct)
 {
	printf("\n -> Image has changed!\n");
	return NULL;
 }


int main(int argc, char* argv[])
 {
	printf("Testing %CLASSNAME% Development...\n");

	printf("\nCreating Instances...\n");
	vipDoctor doc;
	vipFrameRGB24 img, img2;
        int i = 0;
	long time = 0;
	float fps = 0 ;
	%CLASSNAME% myVisionClass;

	printf("Loading Frame...\n");
	vipCodec_BMP::load(img, "frame1.bmp", vipCodec_BMP::FORMAT_BMP_24);
	vipCodec_BMP::load(img2, "frame2.bmp", vipCodec_BMP::FORMAT_BMP_24);

	myVisionClass.setAlertCall(myAlertFunction);
	myVisionClass.getParameters().setDoAlert(true);

	myVisionClass << img;

	printf("Start Processing...\n\n");

	myVisionClass << img2;

	printf("Testing frame rate...\n\n");
	myVisionClass.getParameters().setDoAlert(false);

	doc.reset(true);
	while (i++ < 100)
	 {
		myVisionClass << img2;
	 }

	time = doc.getElapsedTime();
	fps = (float)100000/(float)doc.getElapsedTime();

	printf("Elapsed milliseconds : %ld\n", time );
	printf("Average Frame Rate : %f fps\n", fps );


	printf("\nParameters Serialization (XML)...\n");
	myVisionClass.getParameters().setDoAlert(true);
//	myVisionClass.getParameters().
	myVisionClass.getParameters().saveToXML("myVisionClass.XML");

	%CLASSNAME% myVisionClass2;
	myVisionClass2.getParameters().loadFromXML("myVisionClass.XML");
	myVisionClass2.getParameters().saveToXML("myVisionClass_COPY.XML");

	printf("Test Completed. Type something to continue...\n");
	getchar();




	return 0;
 }