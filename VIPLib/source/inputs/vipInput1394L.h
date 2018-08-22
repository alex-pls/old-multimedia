/**
 *  @class   vipInput1394L
 *
 *  @brief
 *
 *
 *  @bug
 *  @warning
 *  @todo
 *
 *  @see     vipInput
 *
 *  @version 0.01
 *  @date    21/09/2005
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


/*******************************************************

libraw1394
libdc1394

http://www.vision.ie.niigata-u.ac.jp/~tamaki/LTI-Lib



*******************************************************/

#ifndef __VIPLIB_VIPINPUT1394L_H__
 #define __VIPLIB_VIPINPUT1394L_H__

 #include "../vipDefs.h"
 #include "../vipInput.h"


 #include "../vipFrameYUV420.h"
 #include "../vipFrameRGB24.h"
 #include "../vipFrameT.h"


class vipInput1394L : public vipInput // virtual ?
 {

 protected:


 public:

		vipInput1394L(float fps = 0);
//		vipInput1394L();
//		vipInput1394L();



		/**
		 * @brief  Pixel are generated directly into output image!
		 * @return 0
		 */
		unsigned int getWidth() const { return 0; };

		/**
		 * @brief  Pixel are generated directly into output image!
		 * @return 0
		 */
		unsigned int getHeight() const { return 0; };



		VIPRESULT extractTo(vipFrameYUV420& img);
		VIPRESULT extractTo(vipFrameRGB24& img);
		VIPRESULT extractTo(vipFrameT<unsigned char>& img);


};


#endif	//__VIPLIB_VIPINPUT1394L_H__
