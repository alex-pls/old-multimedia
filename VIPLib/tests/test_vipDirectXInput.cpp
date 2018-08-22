/** @file    test_vipDirectXInput.cpp
 *
 *  @brief   Testing code for class vipDirectXInput.
 *
 *           Enumerate available devices, print list with description,
 *           try to connect to first device and save 3 frames.
 *
 *
 *  @warning requires VIPLib with DirectX support
 *
 *  @todo    frame loop and fps estimation
 *
 *  @see     vipDirectXInput
 *
 *  @version 0.50
 *  @date    12/09/2005
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
#include "../source/codecs/vipCodec_BMP.h"

#include "../source/inputs/vipDirectXInput.h"
#include "../source/outputs/vipDoctor.h"


#include <stdio.h>
#include <windows.h>

#pragma argsused

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstP, LPSTR lpCmdLine, int nCmdShow)
{

//int main(int argc, char* argv[])
// {
	printf("Testing vipDirectXInput Development...\n");

	printf("\nCreating Instances...\n");
	vipFrameRGB96 img;
	vipDoctor doc;

	vipDirectXInput cap;

	printf("\nEnumerating Devices...\n");
	cap.enumerateDevices();

	printf("Devices Count: %d\n", cap.getDeviceCount() );

	for (int i=0; i<cap.getDeviceCount(); i++)
		printf(" Device #%d Description's: %s\n", i, cap.getDeviceDescription(i) );

	int myDev = 0;
	printf("\nConnecting to Device #%d...\n", myDev);
	int ret = cap.connectTo(myDev);
	if (ret)
	 {
		printf("CANNOT connect to device : %d [ret=%d]\n", myDev, ret);
		return 1;
	 }
	else
		printf("connected to device : %d\n", myDev);


	int f, w, h;
	char fdesc[255];

	cap.getImageSize(&w, &h);
	f = cap.getFormat();
	cap.getFormat(f, &w, &h, fdesc);

	printf("Device INFO:\n");
	printf(" Device Width: %d\n", w );
	printf(" Device Height: %d\n", h );
	printf(" Device Format: %d\n", f );
	printf(" Device Format Description: %s\n", fdesc );

	printf("\nCreating Frame Instances (and set background different to black)...\n");
	vipFrameRGB24 img24a(w, h);
	vipFrameRGB24 img24b(w, h);
	vipFrameRGB24 img24c(w, h);
	PixelRGB24 backR(255,0,0);
	PixelRGB24 backG(0, 255,0);
	PixelRGB24 backB(0,0, 255);
	img24a.clearWith(backR);
	img24b.clearWith(backG);
	img24c.clearWith(backB);


	printf("\nCapture data...\n");

//	cap.doStartLive();

//	if (cap.isLive())
//		printf("capturing data..\n");

	printf("\nExtracting frames...\n");
	cap >> img24a;
	cap >> img24b;
	cap >> img24c;

	printf("\nSaving frames...\n");
	vipCodec_BMP::save(img24a, "DX_CAPTURE1.bmp", vipCodec_BMP::FORMAT_BMP_24);
	vipCodec_BMP::save(img24b, "DX_CAPTURE2.bmp", vipCodec_BMP::FORMAT_BMP_24);
	vipCodec_BMP::save(img24c, "DX_CAPTURE3.bmp", vipCodec_BMP::FORMAT_BMP_24);
	cap >> img24a;
	cap >> img24b;
	cap >> img24c;

	printf("\nSaving frames...\n");
	vipCodec_BMP::save(img24a, "DX_CAPTURE11.bmp", vipCodec_BMP::FORMAT_BMP_24);
	vipCodec_BMP::save(img24b, "DX_CAPTURE12.bmp", vipCodec_BMP::FORMAT_BMP_24);
	vipCodec_BMP::save(img24c, "DX_CAPTURE13.bmp", vipCodec_BMP::FORMAT_BMP_24);
	cap >> img24a;
	cap >> img24b;
	cap >> img24c;

	printf("\nSaving frames...\n");
	vipCodec_BMP::save(img24a, "DX_CAPTURE21.bmp", vipCodec_BMP::FORMAT_BMP_24);
	vipCodec_BMP::save(img24b, "DX_CAPTURE22.bmp", vipCodec_BMP::FORMAT_BMP_24);
	vipCodec_BMP::save(img24c, "DX_CAPTURE23.bmp", vipCodec_BMP::FORMAT_BMP_24);
	cap >> img24a;
	cap >> img24b;
	cap >> img24c;

	printf("\nSaving frames...\n");
	vipCodec_BMP::save(img24a, "DX_CAPTURE31.bmp", vipCodec_BMP::FORMAT_BMP_24);
	vipCodec_BMP::save(img24b, "DX_CAPTURE32.bmp", vipCodec_BMP::FORMAT_BMP_24);
	vipCodec_BMP::save(img24c, "DX_CAPTURE33.bmp", vipCodec_BMP::FORMAT_BMP_24);


	printf("Test Completed. Type something to continue...\n");
	getchar();

	return 0;
 }
//---------------------------------------------------------------------------
