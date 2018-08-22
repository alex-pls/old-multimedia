/**
 *  @class   vipOutput
 *
 *  @brief   Abstract class for all data outputs, implementations should
 *           encode VIPLib data stream to a device (visualization or storage
 *           for example), inherited classes must implement data encoding
 *           throw importFrom() methods, base input operators (<<) make a
 *           direct call to these functions, inherited classes may obviously
 *           override current operators behaviour.
 *
 *  @version 1.0.2
 *  @date    24/12/2005
 *  @author  Alessandro Polo
 *
 ****************************************************************************
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.disi.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DISI - University of Trento
 *
 ****************************************************************************/



#ifndef __VIPLIB_VIPOUTPUT_H__
 #define __VIPLIB_VIPOUTPUT_H__


 #include "vipDefs.h"
 #include "vipFrameYUV420.h"
 #include "vipFrameRGB24.h"
 #include "vipFrameT.h"


class vipOutput
 {

	public:

		/**
		 * @brief Default constructor is protected because this is an
		 *        abstract class and instance cannot be created directly.
		 */
		vipOutput() { }


		virtual ~vipOutput() { }


		/**
		 * @brief  Set current canvas' height.
		 *
		 * @return height in pixel.
		 */
		virtual VIPRESULT setHeight(unsigned int value) = 0;

		/**
		 * @brief  Set current canvas' width.
		 *
		 * @return width in pixel.
		 */
		virtual VIPRESULT setWidth(unsigned int value) = 0;


		/**
		 * @brief Inherited class must implement this function,
		 *        processing frames to specific output (device or stream)
		 *
		 * @param[in] img VIPLib Cache Frame to be processed (encoded for example)
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note  Input operator (<<) call directly this function.
		 * @see   operator << (vipFrameYUV420&)
		 */
		virtual VIPRESULT importFrom(vipFrameYUV420& img) = 0;

		/**
		 * @brief Inherited class must implement this function,
		 *        processing frames to specific output (device or stream)
		 *
		 * @param[in] img VIPLib Cache24 Frame to be processed (encoded for example)
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note  Input operator (<<) call directly this function.
		 * @see   operator << (vipFrameRGB24&)
		 */
		virtual VIPRESULT importFrom(vipFrameRGB24& img) = 0;
		
		

		/**
		 * @brief Inherited class must implement this function,
		 *        processing frames to specific output (device or stream)
		 *
		 * @param[in] img Greyscale VIPLib Frame to be processed (encoded for example)
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note  Input operator (<<) call directly this function.
		 * @see   operator << (vipFrameT&)
		 */
		virtual VIPRESULT importFrom(vipFrameT<unsigned char>& img) = 0;



		/**
		 * @brief Input operator, import standard VIPLib frame formats,
		 *        current implementation calls directly importFrom() method.
		 *
		 * @param[in] img VIPLib Cache Frame to be processed (encoded for example)
		 *
		 * @see   importFrom(vipFrameYUV420&)
		 */
		void operator << (vipFrameYUV420& img) { importFrom(img); };


		/**
		 * @brief Input operator, import standard VIPLib frame formats,
		 *        current implementation calls directly importFrom() method.
		 *
		 * @param[in] img VIPLib Cache24 Frame to be processed (encoded for example)
		 *
		 * @see   importFrom(vipFrameRGB24&)
		 */
		void operator << (vipFrameRGB24& img) { importFrom(img); };
		
		

		/**
		 * @brief Input operator, import standard VIPLib frame formats,
		 *        current implementation calls directly importFrom() method.
		 *
		 * @param[in] img Greyscale VIPLib Frame to be processed (encoded for example)
		 *
		 * @see   importFrom(vipFrameT&)
		 */
		void operator << (vipFrameT<unsigned char>& img) { importFrom(img); };


		/**
		 * @brief  Ignore this, it's a class-type definition, mostly used
		 *         by VIPLib WorkShop, sintax is a bit more complex than
		 *         usual because of a VC6 BUG, it's the same as:
		 *         const int vipClassType = VIPCLASS_TYPE_OUTPUT;
		 */
		enum{ vipClassType = VIPCLASS_TYPE_OUTPUT };

};




#endif //__VIPLIB_VIPOUTPUT_H__

