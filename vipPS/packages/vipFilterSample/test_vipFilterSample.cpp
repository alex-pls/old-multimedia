/** @file    test_vipFilterSample.cpp
 *
 *  @brief   Testing code for class vipFilterSample.
 *
 *
 *
 *
 *  @bug
 *
 *  @warning
 *  @note
 *
 *  @see     vipFilterSample
 *
 *  @version 1.0
 *  @date    19/05/2006 7.33.36
 *  @author  Alessandro Polo
 *
 *
 ****************************************************************************
 *  Source based on Package Studio template: vipFilterTemplate version 0.9.12
 ****************************************************************************
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.science.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DIT - University of Trento
 *
 ****************************************************************************/


//---------------------------------------------------------------------------

#include "I:\Projects\Software\VIPLib\source\vipFrameYUV420.h"
#include "I:\Projects\Software\VIPLib\source\vipFrameRGB24.h"
#include "I:\Projects\Software\VIPLib\source\codecs/vipCodec_BMP.h"
#include "I:\Projects\Software\VIPLib\source\outputs/vipDoctor.h"
#include "vipFilterSample.h"


//---------------------------------------------------------------------------
#include <stdio.h>


int main(int argc, char* argv[])
 {
	printf("Testing vipFilterSample Development...\n");

	int i = 0;
	const int iLoopCount = 100;
	long time = 0;
	float fps = 0 ;



	printf("\nCreating Instances...\n");

	vipDoctor doc;				// used as time counter (multiplatform)
	vipFrameRGB24 srcImage;		// source image (.. now empty)
	vipFrameRGB24 outImage;		// output image (.. now empty)
	vipFilterSample myFilterClass;	// subject component


	printf("Loading Frame...\n");
	vipCodec_BMP::load(srcImage, "frame1.bmp", vipCodec_BMP::FORMAT_BMP_24);
								// load an image from BMP 24bit (true color)


	printf("Configuring Filter settings...\n");

	myFilterClass.getParameters().setRunMode(vipFilterSampleParameters::ROTATE90);
								// run mode variable select default operation of the filter
								// parameters are editable/saved INTO vipFilterSampleParameters class


	printf("Start Processing...\n\n");

	myFilterClass << srcImage;	// LOAD IMAGE INTO COMPONENT (same as myFilterClass.importFrom(img); )
								// here is the processing: filter read data from source image, process it
								// writing into internal buffer.

	myFilterClass >> outImage;	// JUST COPY BUFFERED IMAGE (processed) TO OUTPUT
								// (same as myFilterClass.extractTo(img); )


	printf("Processing completed, saving output...\n\n");

	vipCodec_BMP::save(outImage, "vipFilterSample_PROCESSED.bmp", vipCodec_BMP::FORMAT_BMP_24);
								// save processed image as BMP 24bit (true color)


	printf("Testing average FPS (processing time)... [100 frames]\n\n");

	doc.reset(true);			// start counting
	while (i++ < 100)			// loop for getting a quick average fps (..or execution time)
	 {
		myFilterClass << srcImage;
								// here we are interested in processing time only,
								// don't care about copying result to another image/filter
								// so code 'myFilterClass >> outImage;' has been removed
	 }

	time = doc.getElapsedTime();
	fps = (float)iLoopCount*1000/(float)doc.getElapsedTime();
								// get elapsed time and fps (frame per second)

	printf("Processing Time : %f ms\n", (float)time/iLoopCount );
	printf("Average Frame Rate : %f fps\n", fps );








	printf("\nTesting Parameters Serialization (XML)...");
	printf("\n\tsaving current parameters to: vipFilterSample.XML");
	myFilterClass.getParameters().saveToXML("vipFilterSample.XML");

	printf("\n\tcreating an new instance and loading parameters..");
	vipFilterSample myFilterClass2;
	myFilterClass2.getParameters().loadFromXML("vipFilterSample.XML");

	printf("\n\tsaving applied parameters to: vipFilterSample_COPY.XML");
	myFilterClass2.getParameters().saveToXML("vipFilterSample_COPY.XML");

	printf("\nCheck if files are equal!");




	printf("\n\nTest Completed. Type a key to continue...\n");
	getchar();

	return 0;
 }
