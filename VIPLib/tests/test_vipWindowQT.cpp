/** @file    test_vipWindowQT.cpp
 *
 *  @brief   Testing code for class vipWindowQT.
 *
 *           Load two frames using vipFrameRGB96 and vipFrameRGB24 both,
 *           show QWindow sliding some times between the two frames.
 *           Frame rate should be the higher possible, after 100 frames,
 *           loop will exit printing average fps.
 *           During tests average fps was around 20.
 *
 *  @warning need VIPLib with GUI support (make gui)
 *           Need Linux OS, QT Library and a desktop environment (KDE, GNOME)
 *
 *  @see     vipWindowQT
 *  @see     vipCodec_BMP
 *  @see     test_Video4LinuxPlayer.cpp
 *  @see     test_LinuxMPEGPlayer.cpp
 *  @see     test_LinuxMOVPlayer.cpp
 *
 *  @version 1.0.2
 *  @date    08/09/2005
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

#include "../source/outputs/vipWindowQT.h"
#include "../source/outputs/vipDoctor.h"
#include "../source/vipUtility.h"


#include <stdio.h>

#pragma argsused


int main(int argc, char* argv[])
 {
	printf("Testing vipWindowQT Development...\n");

	printf("\nCreating Instances...\n");
	vipFrameRGB24 imgRGB24_A, imgRGB24_B;
	vipDoctor doc;

	printf("\nLoading Frames...\n");
	vipCodec_BMP::load(imgRGB24_A, "frame1.bmp", vipCodec_BMP::FORMAT_BMP_24);
	vipCodec_BMP::load(imgRGB24_B, "frame2.bmp", vipCodec_BMP::FORMAT_BMP_24);

	printf("\nCreating QApplication...\n");
	QApplication app(argc, argv);

	printf("\nCreating QWindow...\n");

	vipWindowQT myWin( imgRGB24_A.getWidth(), imgRGB24_A.getHeight() );

	printf("\nShowing vipWindowQT...\n");
	myWin.show();
//	app.setMainWidget(&myWin);

	printf("\nStarting frame redirection loop...\n");
	int i = 0;
	long time = 0;
	long sleeptime = 20;

	long offset = 0;
	doc.reset(true);
	while (i++ < 5)// 10 frames
	 {
		myWin << imgRGB24_A;
		myWin << imgRGB24_B;
	 }

	time = doc.getElapsedTime();

	float fps = (float)10000/(float)doc.getElapsedTime();

	printf("Elapsed milliseconds : %ld\n", time );
	printf("Average Frame Rate : %f fps\n", fps );

	app.exec();

	printf("Test Completed. Type something to continue...\n");
	getchar();

	return 0;
 }
//---------------------------------------------------------------------------
