/** @file    app_vipVideo4LinuxPlayer.cpp
 *
 *  @brief   Testing code for class vipVideo4Linux and vipWindowQT.
 *
 *           Load video stream from first device (/dev/video0) and
 *           show preview in a window with the same size, stream
 *           is passed through vipFrameRGB24 objects.
 *           Frame rate should be the higher possible, after 100 frames,
 *           loop will exit printing average fps; this number depends
 *           on source rate and window's redrawing both (sum).
 *           Then last captured frame is saved.
 *
 *           Tested on a Linux 2.4.29 kernel with an USB Logitech Express
 *           Webcam, frame rate is around 15 fps, that is hardware limit.
 *           In example test_LinuxMPEGPlayer was 34 fps (decoding+displaying).
 *
 *  @warning requires VIPLib with V4L support and GUI support
 *           requires a valid capture device, Video4Linux library, QT library.
 *
 *  @see     vipVideo4Linux
 *  @see     vipWindowQT
 *  @see     vipDoctor
 *  @see     app_LinuxMPEGPlayer.cpp
 *  @see     app_LinuxMOVPlayer.cpp
 *
 *  @version 1.0.2
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

#include "../source/vipFrameRGB24.h"

#include "../source/inputs/vipVideo4Linux.h"
#include "../source/outputs/vipWindowGTK.h"
#include "../source/outputs/vipDoctor.h"

#include "../source/codecs/vipCodec_BMP.h"

#include <stdio.h>

#pragma argsused


int main(int argc, char* argv[])
 {
	printf("Testing vipVideo4Linux and vipWindowQT Development...\n");


	printf("\nCreating Instances and Connecting to /dev/video0...\n");
	vipVideo4Linux cap("/dev/video0");
	vipDoctor doc;
	float fps;
	int i;
	long time;

	printf("\nDevice Stream INFO:\n");
	printf(" Device Stream Width: %d\n", cap.getWidth() );
	printf(" Device Stream Height: %d\n", cap.getHeight() );
	printf(" Device Stream Color Depth: %d\n", cap.getColorDepth() );
	printf(" Device Stream Palette: %d\n", cap.getPalette() );

	vipFrameRGB24 imgRGB24 ( cap.getWidth(), cap.getHeight() );

//	cap.setBrightness(0);
//	cap.setContrast(0);
//	cap.setHue(0);

	printf("\nCreating Application...\n");
	vipWindowGTK myWin(cap.getWidth(), cap.getHeight());
	myWin.show();

	printf("\nStarting frame redirection loop... (with vipFrameRGB24)\n");
	i = 0;
	time = 0;
	doc.reset(true);
	while (i++ < 100)
	 {
		cap >> imgRGB24;
		myWin << imgRGB24;
	 }

	time = doc.getElapsedTime();
	fps = (float)100000/(float)doc.getElapsedTime();

	printf("Elapsed milliseconds : %ld\n", time );
	printf("Average Frame Rate : %f fps\n", fps );

	printf("\nSaving last capture frame...\n");
	vipCodec_BMP::save(imgRGB24, "v4l_captured_last.bmp", vipCodec_BMP::FORMAT_BMP_24);


	printf("Test Completed. Type something to continue...\n");
	getchar();

	return 0;
 }
//---------------------------------------------------------------------------
