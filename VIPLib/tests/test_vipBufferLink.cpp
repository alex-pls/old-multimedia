/** @file    test_vipBufferLink.cpp
 *
 *  @brief   Testing code for template class vipBufferLink.
 *
 *
 *
 *
 *
 *  @bug
 *  @warning
 *  @todo
 *
 *  @see     vipNoiseGenerator
 *  @see     vipFilterNoiseChannel
 *  @see     vipDoctor
 *
 *  @version 1.0
 *  @date    26/08/2005
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
#include "../source/buffers/vipBufferLink.h"

#include <stdio.h>

#pragma argsused



class vipFrameRGB24Test : public vipFrameRGB24 {
	public:
		int imageid;
 		vipFrameRGB24Test(unsigned int width, unsigned int height) : vipFrameRGB24(width, height) {}
		~vipFrameRGB24Test() {}
 };





int main(int argc, char* argv[])
 {
	printf("Testing vipBufferLink Development...\n");

	printf("\nCreating Instances...\n");
	vipBufferLink<vipFrameRGB24Test> myBuffer;


	// new empty frames
	const int testcount = 20;
	long i;

	vipFrameRGB24Test** newFrames = new vipFrameRGB24Test*[testcount];

	for (int il = 0; il < testcount; il++) {
			newFrames[il] = new vipFrameRGB24Test(320, 240);
			newFrames[il]->imageid = 100 + il;
	 }




// ADDING, REMOVING, INSERTING, UPDATING FRAMES VETVIDEO IMPLEMENTATION TEST
	printf("\nADDING, REMOVING, INSERTING FRAMES VETVIDEO IMPLEMENTATION TEST\n\n");

	// add frames sequentially
	for (i = 0; i < testcount; i++) {
			myBuffer.addFrame(newFrames[i]);
	 }

	printf("Frames Count: %d\n", myBuffer.getFramesCount());
	for (i = 0; i < myBuffer.getFramesCount(); i++)
		printf("Frame #: %d : %d [%p]\n", i,  myBuffer.getFrame(i)->imageid, myBuffer.getFrame(i));

	// remove a frame (not first or last)
	printf("removing frame 110\n");
	myBuffer.removeFrame(newFrames[10]);

	printf("Frames Count: %d\n", myBuffer.getFramesCount());
	for (i = 0; i < myBuffer.getFramesCount(); i++)
		printf("Frame #: %d : %d\n", i,  myBuffer.getFrame(i)->imageid);

	// remove first frame
	printf("removing FIRST frame [#100]\n");
	myBuffer.removeFrame(newFrames[0]);

	printf("Frames Count: %d\n", myBuffer.getFramesCount());
	for (i = 0; i < myBuffer.getFramesCount(); i++)
		printf("Frame #: %d : %d\n", i,  myBuffer.getFrame(i)->imageid);

	// remove last frame
	printf("removing LAST frame [# %d ]\n", (100 + testcount));
	myBuffer.removeFrame(newFrames[testcount-1]);

	printf("Frames Count: %d\n", myBuffer.getFramesCount());
	for (i = 0; i < myBuffer.getFramesCount(); i++)
		printf("Frame #: %d : %d\n", i,  myBuffer.getFrame(i)->imageid);

	// insert FIRST FRAME
	printf("inserting FIRST frame [#100]\n");
	myBuffer.insertFrame(0, newFrames[0]);

	printf("Frames Count: %d\n", myBuffer.getFramesCount());
	for (i = 0; i < myBuffer.getFramesCount(); i++)
		printf("Frame #: %d : %d\n", i,  myBuffer.getFrame(i)->imageid);

	// insert LAST FRAME
	printf("inserting LAST frame [# %d ] in position %d", (100 + testcount-1), myBuffer.getFramesCount());
	myBuffer.insertFrame(myBuffer.getFramesCount()-1, newFrames[testcount-1]);

	printf("Frames Count: %d\n", myBuffer.getFramesCount());
	for (i = 0; i < myBuffer.getFramesCount(); i++)
		printf("Frame #: %d : %d\n", i,  myBuffer.getFrame(i)->imageid);

	// insert a frame (not first or last)
	printf("inserting frame 110 in position 10\n");
	myBuffer.insertFrame(10, newFrames[10]);

	printf("Frames Count: %d\n", myBuffer.getFramesCount());
	for (i = 0; i < myBuffer.getFramesCount(); i++)
		printf("Frame #: %d : %d\n", i,  myBuffer.getFrame(i)->imageid);


// FRAMES BROWSING VETVIDEO IMPLEMENTATION TEST
	printf("\n\nFRAMES BROWSING VETVIDEO IMPLEMENTATION TEST\n\n");

	// browse frames with frame index pointer (lower to higher)
	printf("browse frames with frame index pointer (lower to higher)\n");
	myBuffer.goToFirstFrame();

	for (i = 0; i < myBuffer.getFramesCount(); i++) {
			printf("Frame #: %d : %d\n", i,  myBuffer.getCurrentFrame()->imageid);
			myBuffer.goToNextFrame();
	 }

	// browse frames with frame index pointer (higher to lower)
	printf("browse frames with frame index pointer (higher to lower)\n");
	myBuffer.goToLastFrame();

	for (i = myBuffer.getFramesCount()-1; i >= 0; i--) {
			printf("Frame #: %d : %d\n", i,  myBuffer.getCurrentFrame()->imageid);
			myBuffer.goToPreviousFrame();
	 }

	// browse frames with frame index
	printf("browse frames with frame index\n");

	for (i = 0; i < myBuffer.getFramesCount(); i++) {
			myBuffer.goToFrame(i);
			printf("Frame #: %d : %d\n", i,  myBuffer.getCurrentFrame()->imageid);
	 }

	printf("deleting frames..\n");
        myBuffer.deleteFrames();

	printf("Test Completed. Type something to continue...\n");
	getchar();

	return 0;
 }
//---------------------------------------------------------------------------
