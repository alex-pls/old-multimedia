/** @file    test_vipVideo4Linux.cpp
 *
 *  @brief   Testing code for class vipVideo4Linux.
 *
 *           Connect to first capture device (/dev/video0), print
 *           size, colour depth and palette, capture a frame, print
 *           processing time (milliseconds) and store image to file.
 *
 *  @warning requires VIPLib with V4L support
 *           requires a valid capture device, Video4Linux library.
 *
 *  @see     vipVideo4Linux
 *  @see     test_vipVideo4LinuxPlayer.cpp
 *
 *  @version 1.0
 *  @date    5/08/2005
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

#include "../source/inputs/vipVideo4Linux.h"
#include "../source/outputs/vipDoctor.h"


#include <stdio.h>

#pragma argsused


int main(int argc, char* argv[])
 {
	printf("Testing vipVideo4Linux Development...\n");

	printf("\nCreating Instances and Connecting to /dev/video0...\n");
	vipFrameRGB96 img;
	vipFrameRGB24 img24;
	vipDoctor doc;

	vipVideo4Linux cap("/dev/video0");

	printf("Device INFO:\n");
	printf(" Device Width: %d\n", cap.getWidth() );
	printf(" Device Height: %d\n", cap.getHeight() );
	printf(" Device Color Depth: %d\n", cap.getColorDepth() );
	printf(" Device Palette: %d\n", cap.getPalette() );

	printf("\nStarting frame redirection loop...\n");
	int i = 0;
	long time = 0;
	doc.reset(true);
	while (i++ < 100)// 100 frames
	 {
		cap	>> img24;
	 }

	time = doc.getElapsedTime();
	float fps = (float)100000/(float)doc.getElapsedTime();

	printf("Elapsed milliseconds : %ld\n", time );
	printf("Average Frame Rate : %f fps\n", fps );

	printf("\nSaving last capture frame...\n");
	vipCodec_BMP::save(img24, "v4l_captured_frame", vipCodec_BMP::FORMAT_BMP_24);

	printf("Test Completed. Type something to continue...\n");
	getchar();

	return 0;
 }
//---------------------------------------------------------------------------
