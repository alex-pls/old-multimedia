/** @file vipInput1394L.cpp
 *
 * File containing methods for the 'vipInput1394L' class.
 * The header for this class can be found in vipInput1394L.h,
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



#include "vipInput1394L.h"


vipInput1394L::vipInput1394L(float fps) : vipInput(fps)
 {
	INFO("vipInput1394L::vipInput1394L(float fps) : vipInput(fps) [CONTRUCTOR]")
 }

/*
vipInput1394L::vipInput1394L() : vipInput(fps)
 {
	DEBUGMSG("vipInput1394L::vipInput1394L(PixelRGB& background, float fps) : vipInput(fps) [CONTRUCTOR]", background)


 }

vipInput1394L::vipInput1394L() : vipInput(fps)
 {
	DEBUGMSG("vipInput1394L::vipInput1394L(PixelGrey& background, float fps) : vipInput(fps) [CONTRUCTOR]", background)


 }
*/


VIPRESULT vipInput1394L::extractTo(vipFrameYUV420& img)
 {
	INFO("int vipInput1394L::extractTo(vipFrameYUV420& img) [pushing data]")

	return VIPRET_NOT_IMPLEMENTED;

//	return VIPRET_OK;
 }


VIPRESULT vipInput1394L::extractTo(vipFrameRGB24& img)
 {
	INFO("int vipInput1394L::extractTo(vipFrameRGB24& img) [pushing data]")

	return VIPRET_NOT_IMPLEMENTED;

//	return VIPRET_OK;
 }

VIPRESULT vipInput1394L::extractTo(vipFrameT<unsigned char>& img)
 {
	INFO("int vipInput1394L::extractTo(vipFrameT& img) [pushing data]")

	return VIPRET_NOT_IMPLEMENTED;

//	return VIPRET_OK;
 }


