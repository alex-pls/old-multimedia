/** @file    test_vipMotionLame.cpp
 *
 *  @brief   Testing code for class vipMotionLame.
 *
 *
 *
 *  @see     vipMotionLame
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

#include "../source/outputs/vipDoctor.h"
#include "../source/codecs/vipCodec_BMP.h"
#include "../source/vision/vipMotionLame.h"

#include <stdio.h>

#pragma argsused

void* myAlertFunction(void* myArgumentStruct)
 {
	printf("\n -> Image has changed!\n");
	return NULL;
 }


int main(int argc, char* argv[])
 {
	printf("Testing vipMotionLame Development...\n");

	printf("\nCreating Instances...\n");
	vipDoctor doc;
	vipFrameRGB24 img, img2;
        int i = 0;
	long time = 0;
	float fps = 0 ;
	vipMotionLame mdec;

	printf("Loading Frame...\n");
	vipCodec_BMP::load(img, "frame1.bmp", vipCodec_BMP::FORMAT_BMP_24);
	vipCodec_BMP::load(img2, "frame2.bmp", vipCodec_BMP::FORMAT_BMP_24);

	mdec.setAlertCall(myAlertFunction);
	mdec.getParameters().setDoAlert(true);

	mdec << img;

	printf("Start Processing...\n\n");

	mdec << img2;


	printf("Testing frame rate...\n\n");
	mdec.getParameters().setDoAlert(false);

	doc.reset(true);
	while (i++ < 100)
	 {
		mdec << img2;
	 }

	time = doc.getElapsedTime();
	fps = (float)100000/(float)doc.getElapsedTime();

	printf("Elapsed milliseconds : %ld\n", time );
	printf("Average Frame Rate : %f fps\n", fps );


//	vipCodec_BMP::save(img2, "OUT_RESIZECANVAS.bmp", vipCodec_BMP::FORMAT_BMP_24);

	printf("\nParameters Serialization (XML)...\n");
	mdec.getParameters().setDoAlert(true);
//	mdec.getParameters().
//	geom.getParameters().
	mdec.getParameters().saveToXML("mdec.XML");

	vipMotionLame mdec2;
	mdec2.getParameters().loadFromXML("mdec.XML");
	mdec2.getParameters().saveToXML("mdec_COPY.XML");

	printf("Test Completed. Type something to continue...\n");
	getchar();

	return 0;
 }
//---------------------------------------------------------------------------
