/**
 *  @class   vipStatistics
 *
 *  @brief   This class implements static methods used by many VIPLibb modules as:
 *
 *            - PixelPacked <-> ChannelPacked conversion
 *            - ColorSpace conversions
 *            - sleep function (multi-platform)
 *
 *           Syntax: vipStatistics::methodName(arg);
 *
 *
 *  @bug
 *  @warning
 *  @todo
 *
 *  @see
 *
 *  @example ../tests/test_vipStatistics.cpp
 *
 *  @version 1.0.0
 *  @date    17/09/2005
 *  @author  Alessandro Polo
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



/* conversion routines
void conv_420p_rgb96 (int width, int height, void *src, void *dst);
void conv_420p_grey  (int width, int height, void *src, void *dst);
void conv_rgb24_rgb96(int width, int height, void *src, void *dst);
void conv_rgb24_grey(int width, int height, void *src, void *dst);
void conv_rgb32_rgb96(int width, int height, void *src, void *dst);
void conv_rgb32_grey (int width, int height, void *src, void *dst);

void conv_bgr24_rgb96(int width, int height, void *src, void *dst);


*/

// sleeping


#ifndef __VIPLIB_VIPSTATISTICS_H__
 #define __VIPLIB_VIPSTATISTICS_H__

 #include "../vipDefs.h"


class vipStatistics
 {
	protected:

		//static members only
		vipStatistics() {}

	public:

		virtual ~vipStatistics() {}



//		float getSNR();


 };


#endif //__VIPLIB_VIPSTATISTICS_H__

