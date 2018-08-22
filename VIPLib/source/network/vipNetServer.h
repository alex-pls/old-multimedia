/** @file    vipNetServer.h
 *  @class   vipNetServer
 *
 *  @brief   This class may be very useful during filter's implementation
 *           and testing, frame rate statistics, base image analisis.
 *
 *
 *  @bug
 *  @warning
 *  @todo    image and frame statistics !
 *
 *  @see     vipOutput
 *  @example ../../tests/test_vipNetServer.cpp
 *
 *  @version 0.76
 *  @date    17/08/2005
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




/*

	LAN 100 Mbps	(12,5 Mb/s = 12800 Kb/s = 13107200 bytes/s)


	320*240 *3 *char	= 230400 bytes 		-> MAX 56.888 fps

	320*320 *3 *char	= 307200 bytes 		-> MAX 42.666 fps

	640*480 *3 *char	= 921600 bytes 		-> MAX 14.222 fps




*/



#ifndef __VIPLIB_VIPNETSERVER_H__
 #define __VIPLIB_VIPNETSERVER_H__

 #include "../vipDefs.h"
 #include "../vipOutput.h"

 #include "../vipFrameCache.h"
 #include "../vipFrameCache24.h"
 #include "../vipFrameRGB.h"
 #include "../vipFrameGrey.h"

 #include <time.h>	// clock()


class vipNetServer :  public vipOutput
 {

	protected:



	public:


		vipNetServer();

		vipNetServer(unsigned int port);


		int setPort(unsigned int port);


		/**
		 * @brief Analyze frame and store statistics, elaboration time is saved.
		 *
		 * @param[in] img VIPLibb Cache Frame to be processed (analyzed)
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note  Input operator (<<) call directly this function.
		 * @see   operator << (vipFrameCache&)
		 */
		int importFrom(vipFrameCache& img);

		/**
		 * @brief Analyze frame and store statistics, elaboration time is saved.
		 *
		 * @param[in] img VIPLibb Cache24 Frame to be processed (analyzed)
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note  Input operator (<<) call directly this function.
		 * @see   operator << (vipFrameCache24&)
		 */
		int importFrom(vipFrameCache24& img);

		/**
		 * @brief Analyze frame and store statistics, elaboration time is saved.
		 *
		 * @param[in] img Greyscale VIPLibb Frame to be processed (analyzed)
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note  Input operator (<<) call directly this function.
		 * @see   operator << (vipFrameGrey&)
		 */
		int importFrom(vipFrameGrey& img);




};

#endif //__VIPLIB_VIPNETSERVER_H__
