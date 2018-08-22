/**
 *  @class   vipFrame
 *
 *  @brief   An abstract base class for all images in VIPLib.
 *
 *  @bug
 *  @warning
 *  @todo
 *
 *  @version 1.0.2
 *  @date    22/12/2005
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



#ifndef __VIPLIB_VIPFRAME_H__
 #define __VIPLIB_VIPFRAME_H__

 #include "vipDefs.h"

class vipFrame
 {
	public:

		/**
		 * @var Width of the image.
		 */
		unsigned int	 width;

		/**
		 * @var Height of the image.
		 */
		unsigned int	 height;

		/**
		 * @var Time signature of the creation, useful for real time task (Playout).
		 */
		long timeStamp;


		///< Copy Constructor
	//	vipFrame(vipFrame& img)  : width(img.width), height(img.height) { }

		/// Create an image with the given dimensions
	//	vipFrame(unsigned int w, unsigned int h)  : width(w), height(h) { }

		/// Create an image with 0x0 dimension
	//	vipFrame()  : width(0), height(0) { }


	/**
	 * Default constructor.
	 * protected as an instance of this class cannot be directly
	 * created. instead an instance of an inherited class should
	 * be used.
	 */
		vipFrame()  : width(0), height(0) { }


		/// Create an image with the given dimensions
		vipFrame(unsigned int w, unsigned int h)  : width(w), height(h) { }



		enum VIPFRAME_PROFILE	{
							VIPFRAME_NONE,		//empty
							VIPFRAME_MONO,		//grayscale

			// RGB formats
							VIPFRAME_RGB24,	//standard
							VIPFRAME_BGR24,	//also standard
							VIPFRAME_RGB32,	//
							VIPFRAME_BGR32,	//
							VIPFRAME_RGB96,	//
							VIPFRAME_BGR96,	//

							VIPFRAME_RGB565,	//pixel 16bit!
							VIPFRAME_BGR565,	//pixel 16bit!
							VIPFRAME_RGB555,	//pixel 16bit!
							VIPFRAME_BGR555,	//pixel 16bit!

							VIPFRAME_ARGB32,		//alpha + .
							VIPFRAME_ABGR32,		//alpha + .
							VIPFRAME_RGBA32,		//. + alpha
							VIPFRAME_BGRA32,		//. + alpha

			// YUV formats
							VIPFRAME_I420,		//4:2:0 planar (=IYUV)
							VIPFRAME_YV12,		//4:2:0 planar (common in MPEG software: NxM Y + N/2*M/2 V U )
							VIPFRAME_YUY2,		//4:2:2 packed (common in AVI and hardware devices)
							VIPFRAME_UYVY,		//4:2:2 packed (radius cinepack, 2nd choice of mpeg codecs)
							VIPFRAME_YVYU,		//4:2:2 packed
							VIPFRAME_I444,		//4:4:4 planar (added by Marco Verza for vipFrame444, not found on http://www.fourcc.org/yuv.php)

			//
							VIPFRAME_AYUV,			//alpha + 4:4:4 planar

							VIPFRAME_HSV,

							VIPFRAME_CUSTOM	//not listed here..
		};

		enum VIPFRAME_CHANNEL_TYPE	{
							VIPFRAME_CT_NONE,
							VIPFRAME_CT_PACKED,
							VIPFRAME_CT_PLANAR,
							VIPFRAME_CT_CUSTOM
		};


		/**
		 * @brief Default virtual destructor.
		 */
		virtual ~vipFrame() { }



		virtual VIPRESULT reAllocCanvas(unsigned int w, unsigned int h) = 0;


		virtual VIPRESULT extractBrightness(unsigned char* buffer, unsigned int* size = 0 ) = 0;


		/**
		 * @brief  Read current buffer address.
		 *
		 * @return pointer to current buffer.
		 */
		virtual void* dump_buffer() = 0;

		/**
		 * @brief  Read current buffer size (for example the real size of array).
		 *
		 * @return size in bytes of current buffer.
		 */
		virtual unsigned int getBufferSize() = 0;


		/**
		 * @brief  Initialize image (with current canvas) to black (min brightness).
		 */
		virtual VIPRESULT setBlack() = 0;
		/**
		 * @brief  Initialize image (with current canvas) to white (max brightness).
		 */
		virtual VIPRESULT setWhite() = 0;


		/**
		 * @brief  Read current image's width.
		 *
		 * @return Width in pixel.
		 */
		unsigned int getWidth() const { return width; };
		/**
		 * @brief  Read current image's width.
		 *
		 * @return Width in pixel.
		 */
		unsigned int getWidth() { return width; };


		/**
		 * @brief  Read current image's height.
		 *
		 * @return Height in pixel.
		 */
		unsigned int getHeight() const { return height; };
		/**
		 * @brief  Read current image's height.
		 *
		 * @return Height in pixel.
		 */
		unsigned int getHeight() { return height; };


		/**
		 * @brief  Get current format's BPP (Bits per Pixel).
		 *
		 * @return number of bits for a single pixel (or macropixel).
		 */
		virtual unsigned int getBpp() = 0;

		/**
		 * @brief
		 *
		 * @return .
		 */
		virtual VIPFRAME_PROFILE getProfile() = 0;

		/**
		 * @brief  .
		 *
		 * @return .
		 */
		virtual VIPFRAME_CHANNEL_TYPE getChannelType() = 0;

		/**
		 * @brief  Get FOURCC code of current data format, visit
		 *         http://www.fourcc.org for all codes.
		 *
		 * @return int value (usually defined as HEX 0x...).
		 */
		virtual int getFOURCC() = 0;



		/**
		 * @brief  Ignore this, it's a class-type definition, mostly used
		 *         by VIPLib WorkShop, sintax is a bit more complex than
		 *         usual because of a VC6 BUG, it's the same as:
		 *         const int vipClassType = VIPCLASS_TYPE_FRAME;
		 */
		enum{ vipClassType = VIPCLASS_TYPE_FRAME };

};


#endif //__VIPLIB_VIPFRAME_H__

