/** @file    test_vipFilterGeometric.cpp
 *
 *  @brief   Testing code for class vipFilterGeometric.
 *
 *           Performs all available operations on a source image and
 *           save output to BMP file. Then tests settings serialization.
 *
 *
 *  @see     vipFilterGeometric
 *
 *  @version 1.0.2
 *  @date    02/09/2005 - 26/06/2008
 *  @author  Alessandro Polo, Nicola Conci
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

#include "../source/codecs/vipCodec_BMP.h"
#include "../source/filters/vipFilterGeometric.h"

#include <stdio.h>

#pragma argsused

int main(int argc, char* argv[])
 {
	printf("Testing vipFilterGeometric Development...\n");

	printf("\nCreating Instances...\n");
	vipFrameRGB24 img, img2;

	vipFilterGeometric geom;

	printf("Loading Frame...\n");
	vipCodec_BMP::load(img, "QVGA.bmp", vipCodec_BMP::FORMAT_BMP_24);
	geom.getParameters().forceOutputSize(true);

	printf("Start Processing...\n\n");

	printf(" ROTATING 90..\n");
	geom.getParameters().setRunMode(vipFilterGeometricParameters::ROTATE90);
	geom << img;
	geom >> img2;
	vipCodec_BMP::save(img2, "OUT_ROTATE90.bmp", vipCodec_BMP::FORMAT_BMP_24);

	printf(" ROTATING 180..\n");
	geom.getParameters().setRunMode(vipFilterGeometricParameters::ROTATE180);
	geom << img;
	geom >> img2;
	vipCodec_BMP::save(img2, "OUT_ROTATE180.bmp", vipCodec_BMP::FORMAT_BMP_24);

	printf(" ROTATING 270..\n");
	geom.getParameters().setRunMode(vipFilterGeometricParameters::ROTATE270);
	geom << img;
	geom >> img2;
	vipCodec_BMP::save(img2, "OUT_ROTATE270.bmp", vipCodec_BMP::FORMAT_BMP_24);

	

	printf(" FLIPPING VERTICAL..\n");
	geom.getParameters().setRunMode(vipFilterGeometricParameters::FLIP_VERTICAL);
	geom << img;
	geom >> img2;
	vipCodec_BMP::save(img2, "OUT_FLIP_VERTICAL.bmp", vipCodec_BMP::FORMAT_BMP_24);

	printf(" FLIPPING HORIZONTAL..\n");
	geom.getParameters().setRunMode(vipFilterGeometricParameters::FLIP_HORIZONTAL);
	geom << img;
	geom >> img2;
	vipCodec_BMP::save(img2, "OUT_FLIP_HORIZONTAL.bmp", vipCodec_BMP::FORMAT_BMP_24);

	printf(" RESIZING..\n");
	geom.getParameters().setRunMode(vipFilterGeometricParameters::RESIZE);
	geom.getParameters().setResizeDimension(200, 480);
	
	geom << img;
	geom >> img2;
	vipCodec_BMP::save(img2, "OUT_RESIZE.bmp", vipCodec_BMP::FORMAT_BMP_24);

	printf(" RESIZING CANVAS TO 300x300..\n");
	geom.getParameters().setRunMode(vipFilterGeometricParameters::RESIZECANVAS);
	geom.getParameters().setResizeDimension(300, 300);
	geom << img;
	geom >> img2;
	vipCodec_BMP::save(img2, "OUT_RESIZECANVAS.bmp", vipCodec_BMP::FORMAT_BMP_24);

//	printf("\nParameters Serialization (XML)...\n");
//	geom.getParameters().forceOutputSize(true);
//	geom.getParameters().setRunMode(vipFilterGeometricParameters::ROTATE);
//	geom.getParameters().setRotationDegree(45.3);
//	geom.getParameters().setResizeDimension(123, 456);
//	geom.getParameters().saveToXML("geom.XML");

	vipFilterGeometric geom2;
//	geom2.getParameters().loadFromXML("geom.XML");
//	geom2.getParameters().saveToXML("geom_COPY.XML");

	printf("Test Completed. Type something to continue...\n");
	getchar();

	return 0;
 }
//---------------------------------------------------------------------------
