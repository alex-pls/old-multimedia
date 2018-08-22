/** @file    test_vipMultiplexer.cpp
 *
 *  @brief   Testing code for class vipMultiplexer.
 *
 *           This example links two vipCodecs_BMP, loading frames from
 *           bmp format files and storing them in the same format.
 *
 *  @warning need 4 input frames (frame1.bmp, frame2.bmp, ..)
 *
 *  @see     vipMultiplexer
 *  @see     vipCodec_BMP
 *
 *  @version 1.0.2
 *  @date    25/08/2005
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

#include "../source/vipFrameRGB24.h"
#include "../source/outputs/vipDoctor.h"

#include "../source/codecs/vipCodec_BMP.h"
#include "../source/filters/vipFilterGeometric.h"

#include "../source/filters/vipMultiplexer.h"


#include <stdio.h>

#pragma argsused


int main(int argc, char* argv[])
 {
	printf("Testing vipMultiplexer Development...\n");

	printf("\nCreating Instances...\n");
	vipDoctor doc;
	vipCodec_BMP source;
	vipCodec_BMP dest;

	vipMultiplexer multi, multi2;

	printf("\nSetting BMP data source...\n");
	source.setDoBuffering(false);
	source.setAutoInputEnabled(true);
	source.setFileNameProgression(true);
	source.setFileFormat(vipCodec_BMP::FORMAT_BMP_24);
	source.setFileName("frame");
	source.getParameters().setFileNameIndex(1);

	printf("Setting BMP data output...\n");
	dest.setDoBuffering(false);
	dest.setAutoOutputEnabled(true);
	dest.setFileNameProgression(true);
	dest.setFileFormat(vipCodec_BMP::FORMAT_BMP_24);
	dest.setFileName("output");
	dest.getParameters().setFileNameIndex(1);

	printf("\nSetting Multiplexer connections...\n");
	multi.addInput(&source);
	multi.setCurrentInput(0);
	multi.addOutput(&dest);
	multi.setCurrentOutput(0);

	printf("\nLaunching redirection loop...\n");
	doc.reset(true);
	multi.run(4);
	printf("Elapsed milliseconds : %ld", doc.getElapsedTime() );


	printf("\nTesting with a geometric filter...\n");
	vipFilterGeometric geom;
	geom.getParameters().setRunMode(vipFilterGeometricParameters::ROTATE180);

	printf("\nSetting Multiplexer connections...\n");
	multi.addInput(&source);
	multi.setCurrentInput(0);
	multi.addOutput(&geom);
	multi.setCurrentOutput(0);

	multi2.addInput(&geom);
	multi2.setCurrentInput(0);
	multi2.addOutput(&dest);
	multi2.setCurrentOutput(0);

	source.getParameters().setFileNameIndex(1);
	dest.getParameters().setFileNameIndex(1);

	printf("\nLaunching redirection loop...\n");
	doc.reset(true);
	multi.run(4);
	printf("Elapsed milliseconds : %ld", doc.getElapsedTime() );


	printf("Test Completed. Type something to continue...\n");
	getchar();

	return 0;
 }
//---------------------------------------------------------------------------
