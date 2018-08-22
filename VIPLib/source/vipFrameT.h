/**
 *  @class   vipFrameT
 *
 *  @brief
 *
 *
 *
 *
 *  @bug
 *  @warning
 *  @todo
 *
 *  @see
 *  @see     vipFrame
 *
 *  @version 0.6
 *  @date    12/07/2005 - //2005
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


//BUGssssssssssssssss
// SETPIXEL E GETPIXEL devono essere rifatte in base al pixelPacked e canali !!
// ecc (realloc)


#ifndef __VIPLIB_VIPFRAMETH__
 #define __VIPLIB_VIPFRAMETH__

 #define _VIPFRAMET_SLOWMODE

 #include "vipDefs.h"

 #include "vipFrame.h"


template<class T>
class vipFrameT : public virtual vipFrame
 {

	public:

		/**
		 * @var   Width of the image
		 */
		unsigned int width;

		/**
		 * @var   Height of the image
		 */
		unsigned int height;

		bool autoFreeData;

		VIPFRAME_PROFILE profile;

		VIPFRAME_CHANNEL_TYPE	dataType;

		/**
		 * @var   data array pointer. Size is unknown.
		 */
		T *data;


	public:

		/**
		 * @brief Default constructor, initialize height and width to 0.
		 */
		vipFrameT()
		 {
			height = 0;
			width = 0;
			data = NULL;
			autoFreeData = true;
			dataType = vipFrame::VIPFRAME_CT_NONE;
			profile = vipFrame::VIPFRAME_NONE;
		 }


		vipFrameT(unsigned int w, unsigned int h)
		 {
			data = NULL;
			autoFreeData = true;
			dataType = vipFrame::VIPFRAME_CT_PACKED;
			profile = vipFrame::VIPFRAME_MONO;

			reAllocCanvas(w, h);
		 }

		/**
		 * @brief Create an image with the given dimensions, allocates empty data.
		 * @param w Width of the image.
		 * @param h Height of the image.
		 */
		vipFrameT(unsigned int w, unsigned int h, vipFrame::VIPFRAME_PROFILE prof, vipFrame::VIPFRAME_CHANNEL_TYPE dataTy = vipFrame::VIPFRAME_CT_PLANAR)
		 {
			data = NULL;
			autoFreeData = true;
			dataType = dataTy;
			profile = prof;

			reAllocCanvas(w, h);
		 }

		/**
		 * @brief Copy Constructor, create an image from another image, copying memory.
		 * @param img source image.
		 */
		vipFrameT(vipFrameT& img)
		 {
			data = NULL;
			dataType = img.dataType;
			profile = img.profile;
			autoFreeData = img.autoFreeData;

			reAllocCanvas(img.width, img.height);
			memcpy(static_cast<char*>(data), static_cast<char*>(img.data), getBufferSize() );
		 }

		/**
		 * @brief Destructor currenly clear pixel data (array).
		 */
		~vipFrameT()
		 {
			if ( autoFreeData && data != NULL )
					delete [] data;
		 }


		bool isBuiltInSupportedProfile(VIPFRAME_PROFILE pr)
		 {
			switch( profile )
			 {
				case vipFrame::VIPFRAME_MONO:
				case vipFrame::VIPFRAME_RGB24:
				case vipFrame::VIPFRAME_BGR24:
				case vipFrame::VIPFRAME_RGB32:
				case vipFrame::VIPFRAME_BGR32:
					return true;

				case vipFrame::VIPFRAME_ARGB32:
				case vipFrame::VIPFRAME_ABGR32:
				case vipFrame::VIPFRAME_RGBA32:
				case vipFrame::VIPFRAME_BGRA32:
//BUG TODO
				default:
					return false;

			 }
		 }

		/**
		 * @brief read current image's width.
		 *
		 * @return Width in pixel.
		 */
		unsigned int getWidth() const { return width; };
		unsigned int getWidth() { return width; };

		/**
		 * @brief read current image's height.
		 *
		 * @return Height in pixel.
		 */
		unsigned int getHeight() const { return height; };
		unsigned int getHeight() { return height; };


		void* dump_buffer() { return static_cast<void*>(data); };

		VIPRESULT reAllocCanvas(unsigned int w, unsigned int h)
		 {
			width = w;
			height = h;

			if ( width == 0 || height == 0 )
				return VIPRET_PARAM_ERR;

			if ( data != NULL )
				delete [] data;
			data = NULL;

			int multiplier = 1;
			switch( profile )
			 {
				case vipFrame::VIPFRAME_MONO:
										multiplier = 1; break;

				case vipFrame::VIPFRAME_RGB24:
				case vipFrame::VIPFRAME_BGR24:
				case vipFrame::VIPFRAME_RGB96:
				case vipFrame::VIPFRAME_BGR32:
										multiplier = 3; break;

				case vipFrame::VIPFRAME_ARGB32:
				case vipFrame::VIPFRAME_ABGR32:
				case vipFrame::VIPFRAME_RGBA32:
				case vipFrame::VIPFRAME_BGRA32:
										multiplier = 4; break;
//BUG TODO
				default:
										break;
			 }

			data = new T[ (unsigned int)(width * height * multiplier) ];

			return VIPRET_OK;

		 }

		VIPRESULT extractBrightness(unsigned char* buffer, unsigned int* size = NULL )
		{
		return 666;
		}

		unsigned int getBpp()
		 {
			switch( profile )
			 {
				case vipFrame::VIPFRAME_RGB24:
				case vipFrame::VIPFRAME_BGR24:	return 24;
				case vipFrame::VIPFRAME_RGB96:
				case vipFrame::VIPFRAME_BGR96:	return 96;

				case vipFrame::VIPFRAME_ARGB32:
				case vipFrame::VIPFRAME_ABGR32:
				case vipFrame::VIPFRAME_RGBA32:
				case vipFrame::VIPFRAME_BGRA32: return 32;

//BUG TODO
				case vipFrame::VIPFRAME_MONO:	return sizeof(T) * 8;
				default:						return 0;

			 }
		 }

		unsigned int getBufferSize()
		 {
			switch( profile )
			 {
				case vipFrame::VIPFRAME_MONO:	return width * height * sizeof(T);
				case vipFrame::VIPFRAME_RGB24:
				case vipFrame::VIPFRAME_BGR24:	return width * height * 3 * sizeof(T);
				case vipFrame::VIPFRAME_RGB96:
				case vipFrame::VIPFRAME_BGR96:	return width * height * 3 * sizeof(T);

				case vipFrame::VIPFRAME_ARGB32:
				case vipFrame::VIPFRAME_ABGR32:
				case vipFrame::VIPFRAME_RGBA32:
				case vipFrame::VIPFRAME_BGRA32: return width * height * 4 * sizeof(T);

//BUG TODO
				default:						return 0;

			 }
		 }


		VIPRESULT setBlack()
		 {
			switch( profile )
			 {
				case vipFrame::VIPFRAME_MONO:
				case vipFrame::VIPFRAME_RGB24:
				case vipFrame::VIPFRAME_BGR24:
				case vipFrame::VIPFRAME_RGB96:
				case vipFrame::VIPFRAME_BGR96:
				case vipFrame::VIPFRAME_ARGB32:
				case vipFrame::VIPFRAME_ABGR32:
				case vipFrame::VIPFRAME_RGBA32:
				case vipFrame::VIPFRAME_BGRA32:
					{
					memset(data, '\0', getBufferSize() );
					return VIPRET_OK;
					}

				default:
					return VIPRET_NOT_IMPLEMENTED;

			 }
		 }

		VIPRESULT setWhite()
		 {
			switch( profile )
			 {
				case vipFrame::VIPFRAME_MONO:
				case vipFrame::VIPFRAME_RGB24:
				case vipFrame::VIPFRAME_BGR24:
				case vipFrame::VIPFRAME_RGB96:
				case vipFrame::VIPFRAME_BGR96:
					{
					memset(data, 255, getBufferSize() );
					return VIPRET_OK;
					}

				case vipFrame::VIPFRAME_ARGB32:
				case vipFrame::VIPFRAME_ABGR32:
					{
					memset(data, '\0', width*height );
					return VIPRET_OK;
					}

				case vipFrame::VIPFRAME_RGBA32:
				case vipFrame::VIPFRAME_BGRA32:
					{
					memset(data+width*height*3, '\0', width*height );
					return VIPRET_OK;
					}

				default:
					return VIPRET_NOT_IMPLEMENTED;

			 }
		 }


		/**
		 * @brief Set pixel (x, y) to the specified value.
		 *
		 * @param x x position of the pixel.
		 * @param y y position of the pixel.
		 * @param p new value for the selected coords.
		 *
		 * @note No check is made that x and y are in range.
		 */
		VIPRESULT setPixel(unsigned int x, unsigned int y, T p)
		 {
			#ifdef _VIPFRAMECACHE_SLOWMODE
				if ( x >= width || y >= height )
					return VIPRET_PARAM_ERR;
			//		throw "Invalid Coordinates in method vipFrameCache::setPixel(unsigned int x, unsigned int y, PixelRGB p)";
			#endif //_VIPFRAMECACHE_SLOWMODE

//			if ( channelType == VIPFRAMET_CT_PIXELPACKED)
//				data[y * width + x] = p;
//			else
				return VIPRET_NOT_IMPLEMENTED;

//BUG TODO

			return VIPRET_OK;
		 }


		/**
		 * @brief Get pixel (x, y) value and store it to p.
		 *
		 * @param x x position of the pixel.
		 * @param y y position of the pixel.
		 * @param p address to store selected pixel's value.
		 *
		 * @note No check is made that x and y are in range.
		 */
		VIPRESULT getPixel(unsigned int x, unsigned int y, T& p)
		 {
			#ifdef _VIPFRAMECACHE_SLOWMODE
				if ( x >= width || y >= height )
					return VIPRET_PARAM_ERR;
			//		throw "Invalid Coordinates in method vipFrameCache::getPixel(unsigned int x, unsigned int y, PixelRGB& p)";
			#endif //_VIPFRAMECACHE_SLOWMODE

//			if ( channelType == VIPFRAMET_CT_PIXELPACKED)
//				p = data[y * width + x];
//			else
				return VIPRET_NOT_IMPLEMENTED;
//BUG TODO

			return VIPRET_OK;
		 }


		/**
		 * @brief Copies all pixel data from img.
		 *        Throws an exception if images are of different size.
		 *
		 * @param img The image to copy the data from.
		 *
		 * @return current instance.
		 */
		vipFrameT&	operator = (vipFrameT& img)
		 {
			/* check we're not trying to copy ourself */
			if (this == &img)
				throw "Source and Destination are same Image";

			/* First check images are the same size and valid */
			if ( width != img.width || height != img.height || profile != img.profile )
			 {
				profile = img.profile;
				dataType = img.dataType;
				reAllocCanvas(img.width, img.height);
			 }

			if ( width == 0 || height == 0 )
				throw "Cannot do that with empty image (no size)";

			memcpy(static_cast<void*>(data), static_cast<void*>(img.data), getBufferSize() );

			return *this;
		 }

		/**
		 * @brief Overload equals-add (+=) operator for two images (pixel += loop)
		 *        Throws an exception if images are of different size.
		 *
		 * @param img The image to add to current data.
		 *
		 * @return current instance.
		 */
		vipFrameT& operator += (vipFrameT& img)
		{
			INFO("vipFrameCache& vipFrameCache::operator += (vipFrameCache& img)")

			if (width != img.width || height != img.height)
				throw "Difference in vipFrameCache Dimensions";
			if ( dataType != img.dataType || profile != img.profile )
				throw "Difference in vipFrameT data structure";

//			for(unsigned int i=0; i < width * height; i++)
//				data[i] += img.data[i];
//BUG TODO

			return *this;
		}




//		void operator << (const vipFrame& img);
//		void operator << (const vipFrame& img);
//		vipFrameT& operator >> (vipFrame& img);
//		vipFrameT& operator >> (vipFrame& img);


		VIPFRAME_PROFILE getProfile() { return profile; };

		VIPFRAME_CHANNEL_TYPE getChannelType() { return dataType; };


		int getFOURCC()
		 {
			switch( profile )
			 {
				case vipFrame::VIPFRAME_MONO:
				case vipFrame::VIPFRAME_RGB24:
				case vipFrame::VIPFRAME_BGR24:
				case vipFrame::VIPFRAME_RGB32:
				case vipFrame::VIPFRAME_BGR32:
					return 0x32424752;

				case vipFrame::VIPFRAME_ARGB32:
				case vipFrame::VIPFRAME_ABGR32:
					return 0x41424752;

				case vipFrame::VIPFRAME_RGBA32:
				case vipFrame::VIPFRAME_BGRA32:
//BUG TODO
				default:
					return 0;

			 }

		 };

 };



#endif //__VIPLIB_VIPFRAMETH__

