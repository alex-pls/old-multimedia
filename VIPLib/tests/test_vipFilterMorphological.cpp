/** @file    test_vipFilterMorphological.cpp
 *
 *  @brief   Testing code for class vipFilterMorphological.
 *
 *
 *
 *
 *  @bug
 *
 *  @warning
 *  @note
 *
 *  @see     vipFilterMorphological
 *
 *  @version 1.0
 *  @date    26/05/2006 13.26.42
 *  @author  Stefano Asioli
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

#include "../source/vipFrameYUV420.h"
#include "../source/vipFrameRGB24.h"
#include "../source/codecs/vipCodec_BMP.h"
#include "../source/outputs/vipDoctor.h"
#include "../source/filters/vipFilterMorphological.h"


//---------------------------------------------------------------------------
#include <stdio.h>


int main(int argc, char* argv[])
 {
	//In this case parameters are set in the source code.  Uncomment/comment the
	//following lines to enable/disable this usage:
	 

	printf("Testing vipFilterMorphological Development...\n");

	printf("\nCreating Instances...\n");
	
	vipFrameRGB24 srcImage;		// source image (.. now empty)
	vipFrameRGB24 outImage;
	
	vipFilterMorphological myFilterClass;
	
	printf("Loading Frame...\n");
	
	vipCodec_BMP::load(srcImage, "lena.bmp", vipCodec_BMP::FORMAT_BMP_24);
	
	printf("Configuring Filter settings...\n\n");
	
	myFilterClass.getParameters().loadFromXML("vipFilterMorphological.XML");
	
	printf("Start Processing...\n\n");
	
	myFilterClass << srcImage;	// LOAD IMAGE INTO COMPONENT (same as myFilterClass.importFrom(img); )
								// here is the processing: filter read data from source image, process it
								// writing into internal buffer.

	myFilterClass >> outImage;	// JUST COPY BUFFERED IMAGE (processed) TO OUTPUT
								// (same as myFilterClass.extractTo(img); )


	printf("Processing completed, saving output...\n\n");

	vipCodec_BMP::save(outImage, "vipFilterMorphological_output.bmp", vipCodec_BMP::FORMAT_BMP_24);
								// save processed image as BMP 24bit (true color)

	printf("\nTesting Parameters Serialization (XML)...");
	printf("\n\tsaving current parameters to: vipFilterMorphological_output.XML");
	myFilterClass.getParameters().saveToXML("vipFilterMorphological_output.XML");

	/*printf("\n\tcreating an new instance and loading parameters..");
	vipFilterMorphological myFilterClass2;
	myFilterClass2.getParameters().loadFromXML("vipFilterMorphological.XML");

	printf("\n\tsaving applied parameters to: vipFilterMorphological_COPY.XML");
	myFilterClass2.getParameters().saveToXML("vipFilterMorphological_COPY.XML");
	
	printf("\nCheck if files are equal!");*/




	printf("\n\nTest Completed. Type a key to continue...\n");
	getchar();




	return 0;
 }
