/** @file    test_vipMotionIlluminationInvariant.cpp
 *
 *  @brief   Testing code for class vipMotionIlluminationInvariant.
 *
 *           Performs all available operations on a source image and
 *           save output to BMP file. Then tests settings serialization.
 *
 *
 *  @see     vipMotionIlluminationInvariant
 *
 *  @version 1.0.2
 *  @date    02/09/2005
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

#include "../source/codecs/vipCodec_BMP.h"
#include "../source/vision/vipMotionIlluminationInvariant.h"

#include <stdio.h>

#pragma argsused

int main(int argc, char* argv[])
 {
	printf("Testing vipMotionIlluminationInvariant Development...\n");

	printf("\nCreating Instances...\n");
	vipFrameRGB24 img;
	vipMotionIlluminationInvariant mot;

	printf("Loading Frame...\n");
	vipCodec_BMP::load(img, "MOV_Extracted_Frame1.bmp", vipCodec_BMP::FORMAT_BMP_24);

	vipFrameRGB24 img2(img.width, img.height);
	vipFrameRGB24 img3(img.width, img.height);
	vipFrameRGB24 img4(img.width, img.height);

	printf("Start Processing...\n\n");

	mot.getReflectance(img, img2);
	mot.getIllumination(img, img4);

	vipCodec_BMP::save(img2, "Reflectance_1.bmp", vipCodec_BMP::FORMAT_BMP_24);
	vipCodec_BMP::save(img4, "Illumination_1.bmp", vipCodec_BMP::FORMAT_BMP_24);

	vipCodec_BMP::load(img, "MOV_Extracted_Frame3.bmp", vipCodec_BMP::FORMAT_BMP_24);

 	mot.getReflectance(img, img3);
	mot.getIllumination(img, img4);

	vipCodec_BMP::save(img3, "Reflectance_2.bmp", vipCodec_BMP::FORMAT_BMP_24);
	vipCodec_BMP::save(img4, "Illumination_2.bmp", vipCodec_BMP::FORMAT_BMP_24);

	mot.getDifference(img, img3, img2);

	vipCodec_BMP::save(img, "DIFFERENCE.bmp", vipCodec_BMP::FORMAT_BMP_24);


/*
	printf("\nParameters Serialization (XML)...\n");
	geom.getParameters().forceOutputSize(true);
	geom.getParameters().setRunMode(vipFilterGeometricParameters::ROTATE);
	geom.getParameters().setRotationDegree(45.3);
	geom.getParameters().setResizeDimension(123, 456);
	geom.getParameters().saveToXML("geom.XML");

	vipFilterGeometric geom2;
	geom2.getParameters().loadFromXML("geom.XML");
	geom2.getParameters().saveToXML("geom_COPY.XML");
*/
	printf("Test Completed. Type something to continue...\n");
	getchar();

	return 0;
 }
//---------------------------------------------------------------------------
