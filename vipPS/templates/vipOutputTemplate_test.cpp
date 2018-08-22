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
 *  Source based on Package Studio template: vipOutputTemplate version 0.9.12
 ****************************************************************************
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.science.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DIT - University of Trento
 *
 ****************************************************************************/


//---------------------------------------------------------------------------

#include "%SOURCEDIR%vipFrameYUV420.h"
#include "%SOURCEDIR%vipFrameRGB24.h"
#include "%SOURCEDIR%codecs/vipCodec_BMP.h"
#include "%SOURCEDIR%outputs/vipDoctor.h"

#include "%CLASSNAME%.h"


//---------------------------------------------------------------------------
#include <stdio.h>

int main(int argc, char* argv[])
 {
	printf("Testing %CLASSNAME% Development...\n");

	int i = 0;
	long time = 0;
	float fps = 0;



	printf("\nCreating Instances...\n");

	vipDoctor doc;				// used as time counter (multiplatform)
	vipFrameRGB24 img;			// source image (.. now empty)
	%CLASSNAME% myOutputClass;	// subject component

	printf("Loading Frame...\n");
	vipCodec_BMP::load(img, "frame1.bmp", vipCodec_BMP::FORMAT_BMP_24);
								// load an image from BMP 24bit (true color)




	printf("Start Processing...\n\n");

	doc.reset(true);			// start counting
	while (i++ < 100)			// loop for getting a quick average fps (..or execution time)
	 {
		myOutputClass << img;	// LOAD IMAGE INTO COMPONENT (same as myOutputClass.importFrom(img); )
	 }



	time = doc.getElapsedTime();
	fps = (float)i*1000/(float)doc.getElapsedTime();
								// get elapsed time and fps (frame per second)

	printf("Processing Time : %f ms\n", (float)time/i );
	printf("Average Frame Rate : %f fps\n", fps );










	printf("\n\nTest Completed. Type a key to continue...\n");
	getchar();


	return 0;
 }
