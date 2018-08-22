/** @file    test_%CLASSNAME%.cpp
 *
 *  @brief   Testing code for class %CLASSNAME%.
 *
 *
 *
 *
 *  @bug
 *
 *  @warning
 *  @note
 *
 *  @see     %CLASSNAME%
 *
 *  @version %VERSION%
 *  @date    %TODAY%
 *  @author  %AUTHOR%
 *
 ****************************************************************************
 *  Source based on Package Studio template: vipBufferTemplate version 0.9.12
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

#include "%SOURCEDIR%vipFrameYUV420.h"
#include "%CLASSNAME%.h"


//---------------------------------------------------------------------------
#include <stdio.h>




class vipFrameYUV420Test : public vipFrameYUV420 {
	public:
		int imageid;
 		vipFrameYUV420Test(unsigned int width, unsigned int height) : vipFrameYUV420(width, height) {}
		~vipFrameYUV420Test() {}
 };



int main(int argc, char* argv[])
 {

	printf("Testing %CLASSNAME% Development...\n");

	printf("\nCreating Instances...\n");
	%CLASSNAME%<vipFrameYUV420Test> myBuffer;


	// new empty frames
	const int testcount = 20;
	long i;

	vipFrameYUV420Test** newFrames = new vipFrameYUV420Test*[testcount];

	for (int il = 0; il < testcount; il++) {
			newFrames[il] = new vipFrameYUV420Test(320, 240);
			newFrames[il]->imageid = 100 + il;
	 }




// ADDING, REMOVING, INSERTING, UPDATING FRAMES VIPVIDEO IMPLEMENTATION TEST
	printf("\nADDING, REMOVING, INSERTING FRAMES VIPVIDEO IMPLEMENTATION TEST\n\n");

	// add frames sequentially
	for (i = 0; i < testcount; i++) {
			myBuffer.addFrame(newFrames[i]);
	 }

	printf("Frames Count: %d\n", myBuffer.getFramesCount());
	for (i = 0; i < myBuffer.getFramesCount(); i++)
		printf("Frame #: %d : %d\n", i,  myBuffer.getFrame(i)->imageid);

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


// FRAMES BROWSING VIPVIDEO IMPLEMENTATION TEST
	printf("\n\nFRAMES BROWSING VIPVIDEO IMPLEMENTATION TEST\n\n");

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


	printf("delete frames..\n");
	myBuffer.deleteFrames();

	printf("Test Completed. Type something to continue...\n");
	getchar();


	return 0;
 }




