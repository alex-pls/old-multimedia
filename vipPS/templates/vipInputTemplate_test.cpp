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
	vipFrameYUV420 img(320, 240);
	vipFrameYUV420 img24(320, 240);
	vipDoctor doc;
	long time = 0;
	int i = 0;
	float fps = 0;
	%CLASSNAME% myInputClass;

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

	vipCodec_BMP::save(img, "%CLASSNAME%_OUT1.bmp", vipCodec_BMP::FORMAT_BMP_24);
	vipCodec_BMP::save(img24, "%CLASSNAME%_OUT2_24b.bmp", vipCodec_BMP::FORMAT_BMP_24);


	printf("Test Completed. Type something to continue...\n");
	getchar();



	return 0;
 }



