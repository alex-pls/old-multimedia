/** @file    test_vipFilterColor.cpp
 *
 *  @brief   Testing code for class vipFilterColor.
 *
 *
 *
 *
 *  @bug
 *
 *  @warning
 *  @note
 *
 *  @see     vipFilterColor
 *
 *  @version 1.2
 *  @date    06/07/2006 21.27.48
 *  @author  Fabrizio Baffetti, Diego Bosetti, Nicola Conci
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

#include "../source/codecs/vipCodec_BMP.h"
#include "../source/outputs/vipDoctor.h"
#include "../source/filters/vipFilterColor.h"


//---------------------------------------------------------------------------
#include <stdio.h>


int main(int argc, char* argv[])
 {
	printf("Testing vipFilterColor Development...\n");

	printf("\nCreating Instances...\n");
	vipFrameRGB24 img;		// source image (.. now empty)
	vipFrameRGB24 img2;		// output image (.. now empty)
	vipFilterColor colorf;

	printf("Loading Frame...\n");
	vipCodec_BMP::load(img, "QVGA.bmp", vipCodec_BMP::FORMAT_BMP_24); //loading source image

	printf("Start Processing...\n\n");

	printf(" ..\n");

	colorf.getParameters().setRunMode(vipFilterColorParameters::CLIPPING);
	colorf.getParameters().setLowerThreshold(127);		//select upper threshold
	colorf.getParameters().setUpperThreshold(127);		//select upper threshold
	colorf << img;
	colorf >> img2;
	vipCodec_BMP::save(img2, "OUT_CLIPPING.bmp", vipCodec_BMP::FORMAT_BMP_24);

	printf("Start Processing...\n\n");
	printf(" ..\n");

	colorf.getParameters().setRunMode(vipFilterColorParameters::EQUALIZER);
	colorf << img;
	colorf >> img2;
    vipCodec_BMP::save(img2, "OUT_EQUALIZER.bmp", vipCodec_BMP::FORMAT_BMP_24);

	vipFrameRGB24 graph(500, 500);

	vipHist myHistR(img, vipFrameRGB24::RED);
	vipHist myHistG(img, vipFrameRGB24::GREEN);
	vipHist myHistB(img, vipFrameRGB24::BLUE);
	
	myHistR.drawGraph(graph);										
	vipCodec_BMP::save(graph, "GRAPH_RED1.bmp", vipCodec_BMP::FORMAT_BMP_24);
	myHistG.drawGraph(graph);
	vipCodec_BMP::save(graph, "GRAPH_GREEN1.bmp", vipCodec_BMP::FORMAT_BMP_24);
	myHistB.drawGraph(graph);
	vipCodec_BMP::save(graph, "GRAPH_BLUE1.bmp", vipCodec_BMP::FORMAT_BMP_24);

	vipHist myHistR2(img2, vipFrameRGB24::RED);
	vipHist myHistG2(img2, vipFrameRGB24::GREEN);
	vipHist myHistB2(img2, vipFrameRGB24::BLUE);
	
	myHistR2.drawGraph(graph);
	vipCodec_BMP::save(graph, "GRAPH_RED2.bmp", vipCodec_BMP::FORMAT_BMP_24);
	myHistG2.drawGraph(graph);
	vipCodec_BMP::save(graph, "GRAPH_GREEN2.bmp", vipCodec_BMP::FORMAT_BMP_24);
	myHistB2.drawGraph(graph);
	vipCodec_BMP::save(graph, "GRAPH_BLUE2.bmp", vipCodec_BMP::FORMAT_BMP_24);
	
	colorf.getParameters().setRunMode(vipFilterColorParameters::SEPIA);
	colorf << img;
	colorf >> img2;
	vipCodec_BMP::save(img2, "OUT_SEPIA.bmp", vipCodec_BMP::FORMAT_BMP_24);
	
	
	/*printf(" ..\n");
	colorf.getParameters().setRunMode(vipFilterColorParameters::CLAMP);
	colorf.getParameters().setWorkingBpp(24);
	colorf << img;
	colorf >> img2;
	vipCodec_BMP::save(img2, "OUT_CLAMP24.bmp", vipCodec_BMP::FORMAT_BMP_24);

	printf(" ..\n");
	colorf.getParameters().setRunMode(vipFilterColorParameters::CLAMP);
	colorf.getParameters().setWorkingBpp(16);
	colorf << img;
	colorf >> img2;
	vipCodec_BMP::save(img2, "OUT_CLAMP16.bmp", vipCodec_BMP::FORMAT_BMP_24);

	printf(" ..\n");
	colorf.getParameters().setRunMode(vipFilterColorParameters::INVERT);
	colorf << img;
	colorf >> img2;
	vipCodec_BMP::save(img2, "OUT_INVERT.bmp", vipCodec_BMP::FORMAT_BMP_24);

	printf(" ..\n");
	colorf.getParameters().setRunMode(vipFilterColorParameters::EXTRACTBITPLANE);
	colorf << img;
	colorf >> img2;
	vipCodec_BMP::save(img2, "OUT_EXTRACTBITPLANE1.bmp", vipCodec_BMP::FORMAT_BMP_24);

	printf(" ..\n");
	colorf.getParameters().setRunMode(vipFilterColorParameters::EXTRACTBITPLANE);
	colorf.getParameters().setBitPlaneBits(4);
	colorf << img;
	colorf >> img2;
	vipCodec_BMP::save(img2, "OUT_EXTRACTBITPLANE4.bmp", vipCodec_BMP::FORMAT_BMP_24);

	printf("\nParameters Serialization (XML)...\n");
	colorf.getParameters().setRunMode(vipFilterColorParameters::CLAMP);
	colorf.getParameters().setWorkingBpp(16);
	colorf.getParameters().setBitPlaneBits(4);
	colorf.getParameters().saveToXML("color.XML");

	vipFilterColor colorf2;
	colorf2.getParameters().loadFromXML("color.XML");
	colorf2.getParameters().saveToXML("color_COPY.XML");*/

	printf("Test Completed. Type something to continue...\n");
	getchar();

	return 0;
 }
//---------------------------------------------------------------------------
