/** @file    test_vipFilterSplitMerge.cpp
 *
 *  @brief   Testing code for class vipFilterSplitMerge.
 *
 *
 *
 *
 *  @bug
 *
 *  @warning
 *  @note
 *
 *  @see     vipFilterSplitMerge
 *
 *  @version 0.1
 *  @date    29/09/2006 12.42.06
 *  @author  Marco Verza - Manuel Di Toma
 *
 *
 ****************************************************************************
 *  Source based on Package Studio template: vipFilterTemplate version 0.9.12
 ****************************************************************************
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.disi.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DISI - University of Trento
 *
 ****************************************************************************/


//---------------------------------------------------------------------------

#include "../../source/vipFrameYUV420.h"
#include "../../source/vipFrameYUV444.h"
#include "../../source/vipFrameRGB24.h"
#include "../../source/vipUtility.h"
#include "../../source/codecs/vipCodec_BMP.h"
#include "../../source/outputs/vipDoctor.h"
#include "vipFilterSplitMerge.h"


//---------------------------------------------------------------------------
#include <stdio.h>


int main(int argc, char* argv[])
 {
	printf("Testing vipFilterSplitMerge Development...\n");


	printf("\nCreating Instances...\n");

	vipDoctor doc;				// used as time counter (multiplatform)
	vipFrameRGB24 srcImage;		// source image (.. now empty)
	vipFrameRGB24 outImage;		// output image (.. now empty)
	vipFilterSplitMerge myFilterClass;	// subject component


	printf("Loading Frame...\n");
	vipCodec_BMP::load(srcImage, "1-house-in.bmp", vipCodec_BMP::FORMAT_BMP_24);
								// load an image from BMP 24bit (true color)


	printf("Configuring Filter settings...\n");

	myFilterClass.getParameters().setRunMode(vipFilterSplitMergeParameters::SPLITMERGE);
								// run mode variable select default operation of the filter
								// parameters are editable/saved INTO vipFilterSplitMergeParameters class

	// SETUP FILTER PARAMETERS
	myFilterClass.getParameters().setRunMode( vipFilterSplitMergeParameters::SPLITMERGE );
	myFilterClass.getParameters().SetVarianceThreshold( 0.01 ); // ~0.005
	myFilterClass.getParameters().SetMinFrameSize(4);


	printf("Start Processing...\n\n");

	myFilterClass << srcImage;	// LOAD IMAGE INTO COMPONENT (same as myFilterClass.importFrom(img); )
								// here is the processing: filter read data from source image, process it
								// writing into internal buffer.

	myFilterClass >> outImage;	// JUST COPY BUFFERED IMAGE (processed) TO OUTPUT
								// (same as myFilterClass.extractTo(img); )


	printf("First test processing completed, saving output...\n\n");


	vipCodec_BMP::save(outImage, "vipFilterSplitMerge_PROCESSED.bmp", vipCodec_BMP::FORMAT_BMP_24);
								// save processed image as BMP 24bit (true color)


/***printf("Testing average FPS (processing time)... [100 frames]\n\n");
	int i = 0;
	const int iLoopCount = 100;
	long time = 0;
	float fps = 0 ;
	doc.reset(true);			// start counting
	while (i++ < iLoopCount)	// loop for getting a quick average fps (..or execution time)
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
***/

/***
	printf("\nTesting Parameters Serialization (XML)...");
	printf("\n\tsaving current parameters to: vipFilterSplitMerge.XML");
	myFilterClass.getParameters().saveToXML("vipFilterSplitMerge.XML");

	printf("\n\tcreating an new instance and loading parameters..");
	vipFilterSplitMerge myFilterClass2;
	myFilterClass2.getParameters().loadFromXML("vipFilterSplitMerge.XML");

	printf("\n\tsaving applied parameters to: vipFilterSplitMerge_COPY.XML");
	myFilterClass2.getParameters().saveToXML("vipFilterSplitMerge_COPY.XML");

	printf("\nCheck if files are equal!");
***/

	printf("\nProcessing 1-house-in.bmp (1 of 4)\n");

	vipCodec_BMP::load(srcImage, "1-house-in.bmp", vipCodec_BMP::FORMAT_BMP_24);
	myFilterClass.getParameters().SetVarianceThreshold( 0.005 ); // ~0.005
	myFilterClass.getParameters().SetMinFrameSize(1);
	myFilterClass << srcImage;	// LOAD IMAGE INTO COMPONENT (same as myFilterClass.importFrom(img); )
	myFilterClass >> outImage;	// JUST COPY BUFFERED IMAGE (processed) TO OUTPUT
	vipCodec_BMP::save(outImage, "1-house-out-0.005-size1.bmp", vipCodec_BMP::FORMAT_BMP_24);

	printf("\nProcessing 2-beans-in.bmp (2 of 4)\n");

	vipCodec_BMP::load(srcImage, "2-beans-in.bmp", vipCodec_BMP::FORMAT_BMP_24);
	myFilterClass.getParameters().SetVarianceThreshold( 0.005 ); // ~0.005
	myFilterClass.getParameters().SetMinFrameSize(1);
	myFilterClass << srcImage;	// LOAD IMAGE INTO COMPONENT (same as myFilterClass.importFrom(img); )
	myFilterClass >> outImage;	// JUST COPY BUFFERED IMAGE (processed) TO OUTPUT
	vipCodec_BMP::save(outImage, "2-beans-out-0.005-size1.bmp", vipCodec_BMP::FORMAT_BMP_24);

	printf("\nProcessing 3-lena-in.bmp (3 of 4)\n");

	vipCodec_BMP::load(srcImage, "3-lena-in.bmp", vipCodec_BMP::FORMAT_BMP_24);
	myFilterClass.getParameters().SetVarianceThreshold( 0.005 ); // ~0.005
	myFilterClass.getParameters().SetMinFrameSize(1);
	myFilterClass << srcImage;	// LOAD IMAGE INTO COMPONENT (same as myFilterClass.importFrom(img); )
	myFilterClass >> outImage;	// JUST COPY BUFFERED IMAGE (processed) TO OUTPUT
	vipCodec_BMP::save(outImage, "3-lena-out-0.005-size1.bmp", vipCodec_BMP::FORMAT_BMP_24);

	printf("\nProcessing 4-peppers-in.bmp (4 of 4):\n");

	printf("\t- Variance Threshold = 0.005 ; Min. Framesize = 1;\n");
	vipCodec_BMP::load(srcImage, "4-peppers-in.bmp", vipCodec_BMP::FORMAT_BMP_24);
	myFilterClass.getParameters().SetVarianceThreshold( 0.005 ); // ~0.005
	myFilterClass.getParameters().SetMinFrameSize(1);
	myFilterClass << srcImage;	// LOAD IMAGE INTO COMPONENT (same as myFilterClass.importFrom(img); )
	myFilterClass >> outImage;	// JUST COPY BUFFERED IMAGE (processed) TO OUTPUT
	vipCodec_BMP::save(outImage, "4-peppers-out-0.005-size1.bmp", vipCodec_BMP::FORMAT_BMP_24);


	printf("\t- Variance Threshold = 0.010 ; Min. Framesize = 1;\n");
	vipCodec_BMP::load(srcImage, "4-peppers-in.bmp", vipCodec_BMP::FORMAT_BMP_24);
	myFilterClass.getParameters().SetVarianceThreshold( 0.010 ); // ~0.005
	myFilterClass.getParameters().SetMinFrameSize(1);
	myFilterClass << srcImage;	// LOAD IMAGE INTO COMPONENT (same as myFilterClass.importFrom(img); )
	myFilterClass >> outImage;	// JUST COPY BUFFERED IMAGE (processed) TO OUTPUT
	vipCodec_BMP::save(outImage, "4-peppers-out-0.010-size1.bmp", vipCodec_BMP::FORMAT_BMP_24);

	printf("\t- Variance Threshold = 0.020 ; Min. Framesize = 1;\n");
	vipCodec_BMP::load(srcImage, "4-peppers-in.bmp", vipCodec_BMP::FORMAT_BMP_24);
	myFilterClass.getParameters().SetVarianceThreshold( 0.020 ); // ~0.005
	myFilterClass.getParameters().SetMinFrameSize(1);
	myFilterClass << srcImage;	// LOAD IMAGE INTO COMPONENT (same as myFilterClass.importFrom(img); )
	myFilterClass >> outImage;	// JUST COPY BUFFERED IMAGE (processed) TO OUTPUT
	vipCodec_BMP::save(outImage, "4-peppers-out-0.020-size1.bmp", vipCodec_BMP::FORMAT_BMP_24);


	printf("\t- Variance Threshold = 0.050 ; Min. Framesize = 1;\n");
	vipCodec_BMP::load(srcImage, "4-peppers-in.bmp", vipCodec_BMP::FORMAT_BMP_24);
	myFilterClass.getParameters().SetVarianceThreshold( 0.050 ); // ~0.005
	myFilterClass.getParameters().SetMinFrameSize(1);
	myFilterClass << srcImage;	// LOAD IMAGE INTO COMPONENT (same as myFilterClass.importFrom(img); )
	myFilterClass >> outImage;	// JUST COPY BUFFERED IMAGE (processed) TO OUTPUT
	vipCodec_BMP::save(outImage, "4-peppers-out-0.050-size1.bmp", vipCodec_BMP::FORMAT_BMP_24);

	printf("\t- Variance Threshold = 0.100 ; Min. Framesize = 1;\n");
	vipCodec_BMP::load(srcImage, "4-peppers-in.bmp", vipCodec_BMP::FORMAT_BMP_24);
	myFilterClass.getParameters().SetVarianceThreshold( 0.100 ); // ~0.005
	myFilterClass.getParameters().SetMinFrameSize(1);
	myFilterClass << srcImage;	// LOAD IMAGE INTO COMPONENT (same as myFilterClass.importFrom(img); )
	myFilterClass >> outImage;	// JUST COPY BUFFERED IMAGE (processed) TO OUTPUT
	vipCodec_BMP::save(outImage, "4-peppers-out-0.100-size1.bmp", vipCodec_BMP::FORMAT_BMP_24);



	printf("\t- Variance Threshold = 0.010 ; Min. Framesize = 16;\n");
	vipCodec_BMP::load(srcImage, "4-peppers-in.bmp", vipCodec_BMP::FORMAT_BMP_24);
	myFilterClass.getParameters().SetVarianceThreshold( 0.010 ); // ~0.005
	myFilterClass.getParameters().SetMinFrameSize(16);
	myFilterClass << srcImage;	// LOAD IMAGE INTO COMPONENT (same as myFilterClass.importFrom(img); )
	myFilterClass >> outImage;	// JUST COPY BUFFERED IMAGE (processed) TO OUTPUT
	vipCodec_BMP::save(outImage, "4-peppers-out-0.010-size16.bmp", vipCodec_BMP::FORMAT_BMP_24);

	printf("\t- Variance Threshold = 0.010 ; Min. Framesize = 64;\n");
	vipCodec_BMP::load(srcImage, "4-peppers-in.bmp", vipCodec_BMP::FORMAT_BMP_24);
	myFilterClass.getParameters().SetVarianceThreshold( 0.010 ); // ~0.005
	myFilterClass.getParameters().SetMinFrameSize(64);
	myFilterClass << srcImage;	// LOAD IMAGE INTO COMPONENT (same as myFilterClass.importFrom(img); )
	myFilterClass >> outImage;	// JUST COPY BUFFERED IMAGE (processed) TO OUTPUT
	vipCodec_BMP::save(outImage, "4-peppers-out-0.010-size64.bmp", vipCodec_BMP::FORMAT_BMP_24);

	printf("\t- Variance Threshold = 0.001 ; Min. Framesize = 16;\n");
	vipCodec_BMP::load(srcImage, "4-peppers-in.bmp", vipCodec_BMP::FORMAT_BMP_24);
	myFilterClass.getParameters().SetVarianceThreshold( 0.001 ); // ~0.005
	myFilterClass.getParameters().SetMinFrameSize(16);
	myFilterClass << srcImage;	// LOAD IMAGE INTO COMPONENT (same as myFilterClass.importFrom(img); )
	myFilterClass >> outImage;	// JUST COPY BUFFERED IMAGE (processed) TO OUTPUT
	vipCodec_BMP::save(outImage, "4-peppers-out-0.001-size16.bmp", vipCodec_BMP::FORMAT_BMP_24);


	printf("\t- Variance Threshold = 0.001 ; Min. Framesize = 64;\n");
	vipCodec_BMP::load(srcImage, "4-peppers-in.bmp", vipCodec_BMP::FORMAT_BMP_24);
	myFilterClass.getParameters().SetVarianceThreshold( 0.001 ); // ~0.005
	myFilterClass.getParameters().SetMinFrameSize(64);
	myFilterClass << srcImage;	// LOAD IMAGE INTO COMPONENT (same as myFilterClass.importFrom(img); )
	myFilterClass >> outImage;	// JUST COPY BUFFERED IMAGE (processed) TO OUTPUT
	vipCodec_BMP::save(outImage, "4-peppers-out-0.001-size64.bmp", vipCodec_BMP::FORMAT_BMP_24);

	printf("\n\nProcessing complete! Hit any key to quit...");
	getchar();
	return 0;
 }
