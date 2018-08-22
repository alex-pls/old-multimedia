/** @file vipVideo4Linux.cpp
 *
 * File containing methods for the 'vipVideo4Linux' class.
 * The header for this class can be found in vipVideo4Linux.h,
 * check that file for class description.
 *
 *
 ****************************************************************************
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.disi.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DISI - University of Trento
 *
 ****************************************************************************/



#include "vipVideo4Linux.h"
#include "../vipUtility.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <linux/types.h>

/**
 * @brief  Default constructor initializes variables and connect.
 *         to device if asked.
 *
 * @param[in] device capture device's path (default: /dev/video0)
 */
vipVideo4Linux::vipVideo4Linux(char* device) : vipInput(0)
 {
	fd = -1;
	videoBuffer = NULL;
	reset();
	connect(device);
 }

/**
 * @brief  Default destructor, disconnect device and delete buffer.
 */
vipVideo4Linux::~vipVideo4Linux()
 {
	disconnect();
	delete [] videoBuffer;
 }

/**
 * @brief  Connect to device.
 *
 * @return VIPRET_PARAMS_ERR if inputfile is NULL, VIP_ILLEGAL_USE
 *         if a device is already connected, VIPRET_INTERNAL_ERR
 *         if any error occured, VIPRET_OK else.
 */
VIPRESULT vipVideo4Linux::connect(char* device)
 {
	if ( device == NULL )
		return VIPRET_PARAM_ERR;

	if ( fd != -1 )
		return VIPRET_ILLEGAL_USE;	//must disconnect first

	// Open the video4link device for reading.
	fd = open(device,O_RDONLY);

	if (fd < 0)
		return VIPRET_INTERNAL_ERR;	//throw "Cannot open device";

	//Make sure this is a video4linux device
	if (ioctl(fd,VIDIOCGCAP, &cap) < 0) {
		close(fd);
		return VIPRET_INTERNAL_ERR;	//throw "VIDEOGCAP, not a video4linux device";
	 }

	//Get the video overlay window
	if (ioctl(fd,VIDIOCGWIN, &win) < 0) {
		close(fd);
		return VIPRET_INTERNAL_ERR;	//throw "VIDIOCGWIN";
	 }

	//Get the picture properties
	if (ioctl (fd,VIDIOCGPICT, &vpic) < 0) {
		close(fd);
		return VIPRET_INTERNAL_ERR;	//throw "VIDIOCGPICT";
	 }

	//Now set the color resolution on the camera
	if (cap.type & VID_TYPE_MONOCHROME)
	 {
		vpic.depth=8;
		vpic.palette=VIDEO_PALETTE_GREY;
		if(ioctl(fd,VIDIOCSPICT,&vpic) < 0)
		 {
			vpic.depth=6;
			if(ioctl(fd,VIDIOCSPICT, &vpic) < 0)
			 {
				vpic.depth=4;
				if (ioctl(fd,VIDIOCSPICT, &vpic) <0) {
					close(fd);
					return VIPRET_INTERNAL_ERR;	//throw "Unable to find a supported Capture format";
				 }
			 }
		 }
	 }
	else
	 {
		vpic.depth = 24;
		vpic.palette = VIDEO_PALETTE_RGB24;

		if (ioctl(fd,VIDIOCSPICT,&vpic) <0)
		 {
			vpic.palette=VIDEO_PALETTE_RGB565;
			vpic.depth=16;

			if(ioctl(fd,VIDIOCSPICT,&vpic) == -1)
			 {
				vpic.palette = VIDEO_PALETTE_RGB555;
				vpic.depth=15;

				if(ioctl(fd, VIDIOCSPICT, &vpic) == -1) {
						close(fd);
						throw "Unable to find a supported Capture format";
				 }
			 }
		 }
	 }
	bpp = vpic.depth;

	if (win.width && win.height)
	 {
		if (videoBuffer != NULL)
			delete [] videoBuffer;

		videoBuffer = (unsigned char*) malloc(win.width * win.height * 3);

		if (videoBuffer == NULL)
			return VIPRET_INTERNAL_ERR;
	 }

	return VIPRET_OK;
 }

/**
 * @brief  Disconnect from current device.
 *
 * @return VIPRET_ILLEGAL_USE if no device is connected, VIPRET_OK else.
 */
VIPRESULT vipVideo4Linux::disconnect()
 {
	if ( fd==-1 )
		return VIPRET_ILLEGAL_USE;

	close(fd);
	fd=-1;
	win.height = 0;
	win.width = 0;
	win.height = 0;
	vpic.palette = 0;

	return VIPRET_OK;
 }

/**
* @brief  Disconnect and reset the module.
*
* @return VIPRET_INTERNAL_ERR if any error occur, VIPRET_OK else.
*/
VIPRESULT vipVideo4Linux::reset()
 {
	disconnect();

	if (videoBuffer != NULL)
		delete [] videoBuffer;

	videoBuffer = NULL;
	fd = -1;
	win.height = 0;
	win.width = 0;
	win.height = 0;
	vpic.palette = 0;

	return VIPRET_OK;
 }


/**
* @brief  Get the state of current data source.
*
* @return true is there are no more frames to load, false else.
*/
bool vipVideo4Linux::EoF()
 {
	if ( fd == -1 )	// not connected
		return true;

	return false;
 }


/**
 * @brief  Grab a frame and copy to VIPLibb standard format.
 *
 * @param[out] img VIPLibb Cache Frame to store data.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR if any
 *		   device reading error occurs, VIPRET_NOT_IMPLEMENTED if color
 *         format is not support.
 *
 * @note   Ouput operator (>>) call directly this function.
 * @see    operator >> (vipFrameYUV420&)
 */
VIPRESULT vipVideo4Linux::extractTo(vipFrameYUV420& img)
 {
	if ( fd == -1 )
		return VIPRET_ILLEGAL_USE;

	if (img.width != win.width || img.height != win.height)
	 {
		 img.reAllocCanvas(win.width, win.height);
	 }

	if ( vpic.palette == VIDEO_PALETTE_RGB24 )
	 {
		return VIPRET_NOT_IMPLEMENTED;
	 }
	else if ( vpic.palette == VIDEO_PALETTE_RGB565 )
	 {
		return VIPRET_NOT_IMPLEMENTED;
	 }
	else if ( vpic.palette == VIDEO_PALETTE_RGB555 )
	 {
		return VIPRET_NOT_IMPLEMENTED;
	 }

	return VIPRET_OK;
 }

/**
 * @brief  Grab a frame and copy to VIPLibb standard format.
 *
 * @param[out] img VIPLibb Cache24 Frame to store data.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR if any
 *		   device reading error occurs, VIPRET_NOT_IMPLEMENTED if color
 *         format is not support.
 *
 * @note   Ouput operator (>>) call directly this function.
 * @see    operator >> (vipFrameRGB24&)
 */
VIPRESULT vipVideo4Linux::extractTo(vipFrameRGB24& img)
 {
	if ( fd == -1 )
		return VIPRET_ILLEGAL_USE;

	if (img.width != win.width || img.height != win.height)
	 {
		 img.reAllocCanvas(win.width, win.height);
	 }

	if ( vpic.palette == VIDEO_PALETTE_RGB24 )
	 {
		if (videoBuffer == NULL)
			return VIPRET_INTERNAL_ERR;

		read(fd,videoBuffer, win.width * win.height * 3 * sizeof(unsigned char) ); //BGR
		vipUtility::conv_bgr_rgb((unsigned char*)img.data[0], videoBuffer, win.width, win.height);
	 }
	else if ( vpic.palette == VIDEO_PALETTE_RGB565 )
	 {
		return VIPRET_NOT_IMPLEMENTED;
	 }
	else if ( vpic.palette == VIDEO_PALETTE_RGB555 )
	 {
		return VIPRET_NOT_IMPLEMENTED;
	 }

	return VIPRET_OK;
 }

/**
 * @brief  Grab a frame and copy to VIPLibb standard format.
 *
 * @param[out] img Greyscale VIPLibb Frame to store data.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR if any
 *		   device reading error occurs, VIPRET_NOT_IMPLEMENTED if color
 *         format is not support.
 *
 * @note   Ouput operator (>>) call directly this function.
 * @see    operator >> (vipFrameT&)
 */
VIPRESULT vipVideo4Linux::extractTo(vipFrameT<unsigned char>& img)
 {
	if ( fd == -1 )
		return VIPRET_ILLEGAL_USE;

	if (win.width != img.width || win.height != img.height)
		img.reAllocCanvas(win.width, win.height);

	if ( vpic.palette == VIDEO_PALETTE_RGB24  && img.profile == vipFrame::VIPFRAME_BGR24 )
	 {
		read(fd, img.data, win.width * win.height * 3 * sizeof(unsigned char) );//BGR
		return VIPRET_OK;
	 }
	if ( vpic.palette == VIDEO_PALETTE_RGB24  && img.profile == vipFrame::VIPFRAME_RGB24 )
	 {
		if (videoBuffer == NULL)
			return VIPRET_INTERNAL_ERR;

		read(fd,videoBuffer, win.width * win.height * 3 * sizeof(unsigned char) ); //BGR
		vipUtility::conv_bgr_rgb(img.data, videoBuffer, win.width, win.height);

	 }

	return VIPRET_NOT_IMPLEMENTED;
 }


