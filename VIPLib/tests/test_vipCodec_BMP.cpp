/** @file    test_vipCodec_BMP.cpp
 *
 *  @brief   Testing code for class vipCodec_BMP.
 *
 *           Some tests on BMP file format, read/write speed and redirection.
 *
 *
 *  @see     vipCodec_BMP
 *  @see     vipMultiplexer
 *  @see     vipDoctor
 *
 *  @version 1.0.2
 *  @date    26/07/2005
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

#include "../source/vipFrameRGB96.h"
#include "../source/vipFrameRGB24.h"
#include "../source/vipFrameGrey.h"

#include "../source/codecs/vipCodec_BMP.h"
#include "../source/filters/vipMultiplexer.h"
#include "../source/outputs/vipDoctor.h"


#include <stdio.h>

#pragma argsused


int main(int argc, char* argv[])
 {
	printf("Testing vipCodec_BMP development...\n");

	printf("\nCreating Instances...\n");
	vipDoctor doc;
	vipCodec_BMP source;
	vipCodec_BMP dest;
	vipCodec_BMP saver;
	vipFrameRGB96 img, img2;

	source.load("frame1.bmp", (int)vipCodec_BMP::FORMAT_BMP_24);

	source >> img;
 	saver << img;

	saver.save("frame1_COPY.bmp", (int)vipCodec_BMP::FORMAT_BMP_24);
	vipCodec_BMP::save(img, "frame1_COPY2.bmp", vipCodec_BMP::FORMAT_BMP_24);
	saver.save(source, "frame1_COPY4.bmp", vipCodec_BMP::FORMAT_BMP_24);

	vipCodec_BMP::load(img2, "frame1.bmp", vipCodec_BMP::FORMAT_BMP_24);
	vipCodec_BMP::save(img2, "frame1_COPY3.bmp", vipCodec_BMP::FORMAT_BMP_24);

	vipFrameRGB24 img3;
	source >> img;
	img3 << img;
	img3 >> img;
	vipCodec_BMP::save(img, "frame1_COPY4_24BIT.bmp", vipCodec_BMP::FORMAT_BMP_24);

	source.setDoBuffering(false);
	source.setAutoInputEnabled(true);
	source.setFileNameProgression(true);
	source.setFileFormat(vipCodec_BMP::FORMAT_BMP_24);
	source.setFileName("frame");
	source.getParameters().setFileNameIndex(1);

	dest.setDoBuffering(false);
	dest.setAutoOutputEnabled(true);
	dest.setFileNameProgression(true);
	dest.setFileFormat(vipCodec_BMP::FORMAT_BMP_24);
	dest.setFileName("frames_COPY");
	dest.getParameters().setFileNameIndex(1);

	vipMultiplexer multi;
	multi.addInput(&source);
	multi.setCurrentInput(0);
	multi.addOutput(&dest);
	multi.setCurrentOutput(0);

	doc.reset(true);
	multi.run(2);
	printf("Elapsed milliseconds : %ld", (long)doc.getElapsedTime() );


	printf("\nParameters Serialization (XML)...\n");

	source.setFileName("frames_COPY");
	source.getParameters().setFileNameIndex(1);
	source.setFileFormat(vipCodec_BMP::FORMAT_BMP_24);
	source.setAutoOutputEnabled(true);
	source.setAutoInputEnabled(false);
	source.setFileNameProgression(true);
	source.getParameters().saveToXML("BMP_param.XML");

	dest.getParameters().loadFromXML("BMP_param.XML");
	dest.getParameters().saveToXML("BMP_param_COPY.XML");


	printf("Test Completed. Type something to continue...\n");
	getchar();

	return 0;
 }
//---------------------------------------------------------------------------
