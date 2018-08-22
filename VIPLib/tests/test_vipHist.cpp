/** @file    test_vipHist.cpp
 *
 *  @brief   Testing code for class vipHist.
 *
 *           Populate Histogram with some data and save it to XML, then
 *           use some image as data source and save channels' data.
 *
 *
 *  @see     vipHist
 *
 *  @version 0.60
 *  @date    09/09/2005
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
#include "../source/codecs/vipCodec_BMP.h"

#include "../source/vipHist.h"


#include <stdio.h>

#pragma argsused

int main(int argc, char* argv[])
 {
	printf("Testing vipHist development..\n");

	printf("\nCreating Instances...\n");
	vipFrameRGB96 img;
	vipFrameRGB24 img2(320, 240), img3(320, 240);
	vipHist myHistogram;

	printf("\nPopulating Histogram...\n");
	myHistogram.reset(0,255);
	myHistogram.addValue(0);
	myHistogram.addValue(10);
	myHistogram.addValue(10);
	myHistogram.addValue(100);
	myHistogram.addValue(150);
	myHistogram.addValue(200);
	myHistogram.addValue(255);

	printf("\nSaving Histogram...\n");
	myHistogram.saveToXML("hist.xml");


	printf("\nLoading image...\n");
	vipCodec_BMP::load(img, "frame1.bmp", vipCodec_BMP::FORMAT_BMP_24);
	PixelRGB24 p(255,255,255);
	img3.clearWith(p);
	//img2 is black by default


	printf("\nUsing Histogram with images...saving R, G, B data\n");

	vipFrameRGB96 graph(500, 500);

	vipHist myHistR(img, vipFrameRGB96::RED);
	myHistR.saveToXML("hist_FRAME1_RED.xml");
	myHistR.drawGraph(graph);
	source.save(graph, "hist_FRAME_RED.bmp", vipCodec_BMP::FORMAT_BMP_24);

	vipHist myHistG(img, vipFrameRGB96::GREEN);
	myHistG.saveToXML("hist_FRAME1_GREEN.xml");
	myHistG.drawGraph(graph);
	source.save(graph, "hist_FRAME_GREEN.bmp", vipCodec_BMP::FORMAT_BMP_24);

	vipHist myHistB(img, vipFrameRGB96::BLUE);
	myHistB.saveToXML("hist_FRAME1_BLUE.xml");
	myHistB.drawGraph(graph);
	source.save(graph, "hist_FRAME_BLUE.bmp", vipCodec_BMP::FORMAT_BMP_24);




	vipHist myHistR(source, vipFrameRGB24::RED);
	vipHist myHistG(source, vipFrameRGB24::GREEN);
	vipHist myHistB(source, vipFrameRGB24::BLUE);

	float * probR = myHistR.dumpProbabilities();
	float * probG = myHistG.dumpProbabilities();
	float * probB = myHistB.dumpProbabilities();

	//myHistR.extractChist();
	float * ChistR = myHistR.dumpChist();
	//myHistG.extractChist();
	float * ChistG = myHistG.dumpChist();
	//myHistB.extractChist();
	float * ChistB = myHistB.dumpChist();

	for (int i=0; i<256; i++) {
		float R = ChistR[i];
		float G = ChistG[i];
		float B = ChistB[i];
		cout  << i << "   "<< R << "   " << G << "   "<< B << endl;
	}





	printf("Test Completed. Type something to continue...\n");
	getchar();

	return 0;
 }
//---------------------------------------------------------------------------
