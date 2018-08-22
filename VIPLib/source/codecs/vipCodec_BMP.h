/**
 *  @class   vipCodec_BMP
 *
 *  @brief   A class for encoding (writing) and decoding (reading)
 *           Bitmap Format (BMP) images, implements vipFilter.
 *
 *            - load from BMP image data file to memory;
 *            - save from memory to BMP image;
 *
 *           It's Able also to output multiple images with filename
 *           (index) progression.
 *
 *  @bug
 *  @warning
 *  @todo
 *
 *  @see     vipCodec
 *  @see     vipFrameRGB96
 *
 *  @example test_vipCodec_BMP.cpp
 *  @example test_vipMultiplexer.cpp
 *
 *  @version 1.0
 *  @date    12/07/2005 - //2005
 *  @author  Alessandro Polo
 *
 *
 ****************************************************************************
 * VIPLib Framework 1.1
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.disi.unitn.it/projects/VIPLib/
 *
 ****************************************************************************/






#ifndef __VIPLIB_VETCODEC_BMP_H__
 #define __VIPLIB_VETCODEC_BMP_H__

 #include "../vipDefs.h"
 #include "../vipCodec.h"

 #include "../vipFrameYUV420.h"
 #include "../vipFrameRGB24.h"
 #include "../vipFrameT.h"
 #include "../vipFrameRGB96.h"
 #include "../vipFrameHSV.h"

#define VIPRET_CODER_FILEOUT_ER	1010     /*  */
#define VIPRET_CODER_SIZE_ER	1011     /*  */
#define VIPRET_CODER_WRITE_ER	1012     /*  */
#define VIPRET_CODER_PALETTE_ER	1013     /*  */



class vipCodec_BMPParameters;


class vipCodec_BMP :  protected vipFrameRGB96,
                      public vipCodec
 {

	public:

		enum FileFormat{ FORMAT_BMP_24,
						 FORMAT_BMP_RC,
						 FORMAT_BMP_MONO,
						 FORMAT_BMP_ANY    };

	protected:

		vipCodec_BMPParameters* myParams;

		char fileNameIndexBuffer[16];
		char fileNameBuffer[80];

		void doFileNameCurrent();

	public:


		/**
		 * @brief Default constructor, initializa parameters and superclasses.
		 */
		vipCodec_BMP(vipCodec_BMPParameters* initParams = NULL);

		/**
		 * @brief Copy constructor from vipFrameCache image, call superclass
		 *        vipFrameRGB copy constructor.
		 *
		 * @param[in] img source VIPLibb Cache Frame.
		 */
		vipCodec_BMP(vipFrameRGB96& img) : vipFrameRGB96(img), vipCodec() { reset(); }

		/**
		 * @brief Copy constructor from vipFrameRGB image, call superclass
		 *        vipFrameRGB copy constructor.
		 *
		 * @param[in] img source Color VIPLibb Frame.
		 */
		vipCodec_BMP(vipFrameRGB24& img) : vipFrameRGB96(img), vipCodec() { reset(); }

		/**
		 * @brief Creates a new frame from given dimensions, call superclass
		 *        vipFrameRGB constructor.
		 *
		 * @param[in] x width of the new frame.
		 * @param[in] y height of the new frame.
		 */
		vipCodec_BMP(unsigned int x, unsigned int y) : vipFrameRGB96(x, y), vipCodec() { reset(); }

		/**
		 * @brief Creates a new frame from given dimensions, call superclass
		 *        vipFrameRGB constructor.
		 *
		 * @param[in] filename Input BMP filename.
		 * @param[in] format BMP Encoding Format, default auto-selection.
		 */
		vipCodec_BMP(const char* filename, FileFormat format = vipCodec_BMP::FORMAT_BMP_ANY);



		/**
		 * @brief Save current buffered image to current filename, first
		 *        setup current filename and format then call this function.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 */
		VIPRESULT save();

		/**
		 * @brief Save current buffered image to given filename and format.
		 *
		 * @param[in] filename Output BMP filename.
		 * @param[in] format BMP Encoding Format.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 */
		VIPRESULT saveBMP(const char *filename, FileFormat format = vipCodec_BMP::FORMAT_BMP_24);

		/**
		 * @brief Load a BMP format image into current buffer (vipFrameRGB), first
		 *        setup current filename and format then call this function.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 */
		VIPRESULT load();

		/**
		 * @brief Load a BMP format image into current buffer (vipFrameRGB).
		 *
		 * @param[in] filename Input BMP filename.
		 * @param[in] format BMP Encoding Format.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 */
		VIPRESULT loadBMP(const char *filename, FileFormat format = vipCodec_BMP::FORMAT_BMP_24);



		VIPRESULT load(char *filename, int format = -1) { return loadBMP( filename, FORMAT_BMP_ANY); };
		VIPRESULT save(char *filename, int format = -1) { return saveBMP( filename, FORMAT_BMP_24); };

		/**
		 * @brief  Get the state of current data source.
		 *
		 * @return true is there are no more frames to load, false else.
		 */

		bool EoF();

		/**
		 * @return VIPRET_ILLEGAL_USE.
		 */
		VIPRESULT close() { return VIPRET_ILLEGAL_USE; };




		/**
		 * @brief  Set parameters for (de)coding.
		 *
		 * @param[in] initParams Instance of vipCodec_BMPParameters or NULL,
		 *                       NULL argument make function to create a new
		 *                       instance with default parameters.
		 *
		 * @return VIPRET_OK
		 */
		VIPRESULT setParameters(vipCodec_BMPParameters* initParams);

		/**
		 * @brief  Get parameters for (de)coding.
		 *
		 * @return pointer to vipCodec_MOVParameters class.
		 */
		vipCodec_BMPParameters& getParameters() { return *myParams; };

		/**
		 * @brief	Enable or disable filename progression, for example:
		 *          basefile name is "output", index is 13 so filename is output13.bmp,
		 *			if filename progression is enabled, when an operation is done
		 *          onto file, idex is incremented (output14.bmp).
		 *
		 * @param[in] value true to enable file name progression.
		 */
		void setFileNameProgression(bool value);

		/**
		 * @brief   Enable or disable auto input feature,
		 *
		 *
		 * @param[in]
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note
		 * @see
		 */
		void setAutoOutputEnabled(bool value = true);

		/**
		 * @brief
		 *
		 *
		 * @param[in]
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note
		 * @see
		 */
		void setAutoInputEnabled(bool value = true);

		/**
		 * @brief
		 *
		 *
		 * @param[in]
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note
		 * @see
		 */
		void setDoBuffering(bool value = true);

		/**
		 * @brief
		 *
		 *
		 * @param[in]
		 *
		 * @note
		 * @see
		 */
		void setFileName(const char *filename);

		/**
		 * @brief  Set current BMP format.
		 *
		 * @param[in] format BMP format enumaration.
		 *
		 * @see    FileFormat
		 */
		void setFileFormat(FileFormat format = vipCodec_BMP::FORMAT_BMP_24);

		/**
		 * @brief  Read current file name index, used in file name progression
		 *         routines.
		 *
		 * @return VIPRET_OK if everything is fine,
		 *		   VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note
		 * @see
		 */

		int getFileNameIndex();
		/**
		 * @brief
		 *
		 *
		 * @return true if filename progression is enabled.
		 *
		 * @see   fileNameProgression
		 */
		bool isFileNameProgressionEnabled();

		/**
		 * @brief
		 *

		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note
		 * @see
		 */
		bool isAutoInputEnabled();

		/**
		 * @brief
		 *
		 *
		 * @param[in]
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note
		 * @see
		 */
		bool isAutoOutputEnabled();

		/**
		 * @brief
		 *
		 *
		 * @param[in]
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note
		 * @see
		 */
		bool isBufferingEnabled();

		/**
		 * @brief Read base filename, if progression is enabled it's the base fixed
		 *        name.
		 *
		 * @param[in]
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note
		 * @see
		 */
		void getFileName(char *filename);

		/**
		 * @brief Read current filename, if progression is enabled it's the base fixed
		 *        name + current index + bmp extension.
		 *
		 * @param[out] Char Array to store current filename [Max size 64 chars]
		 *
		 * @see   fileNameBase
		 */
		void getFileNameCurrent(char *filename);

		/**
		 * @brief Read current bitmap encoding/decoding format.
		 *
		 * @return Current I/O BMP format.
		 *
		 * @see   FileFormat
		 * @see   fileFormat
		 */
		FileFormat getFileFormat(void);

		/**
		 * @brief Reset filename related setup.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR
		 *		   or VIPRET_ILLEGAL_USE else.
		 */
		VIPRESULT reset();


		/**
		 * @brief read current image's width.
		 *
		 * @return Width in pixel.
		 */
		unsigned int getWidth() const { return width; };

		/**
		 * @brief read current image's height.
		 *
		 * @return Height in pixel.
		 */
		unsigned int getHeight() const { return height; };

		/**
		 * @brief  Set current canvas' height.
		 *
		 * @return height in pixel.
		 */
		VIPRESULT setHeight(unsigned int value) { return VIPRET_NOT_IMPLEMENTED; };

		/**
		 * @brief  Set current canvas' width.
		 *
		 * @return width in pixel.
		 */
		VIPRESULT setWidth(unsigned int value) { return VIPRET_NOT_IMPLEMENTED; };

		int getAudioStreamCount() { return -1; };
		int getVideoStreamCount() { return -1; };

		bool hasAudio(int stream = -1) { return false; };
		bool hasVideo(int stream = -1) { return false; };

		long getVideoStreamLength(int stream = -1) { return -1; };

		long getAudioStreamLength(int stream = -1) { return -1; };


		/**
		 * @brief Load bmp data into image parameter, if AutoInput is enabled
		 *        try to load next filename, else just copy current data to img.
		 *
		 * @param[out] img VIPLibb Cache Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note  Ouput operator (>>) call directly this function.
		 * @see   operator >> (vipFrameYUV420&)
		 * @see   AutoInput
		 */
		VIPRESULT extractTo(vipFrameYUV420& img);
		
		/**
		 * @brief Load bmp data into image parameter, if AutoInput is enabled
		 *        try to load next filename, else just copy current data to img.
		 *
		 * @param[out] img VIPLibb Cache Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note  Ouput operator (>>) call directly this function.
		 * @see   operator >> (vipFrameYUV420&)
		 * @see   AutoInput
		 */
		VIPRESULT extractTo(vipFrameYUV444& img);

		/**
		 * @brief Load bmp data into image parameter, if AutoInput is enabled
		 *        try to load next filename, else just copy current data to img.
		 *
		 * @param[out] img VIPLibb Cache24 Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note  Ouput operator (>>) call directly this function.
		 * @see   operator >> (vipFrameRGB24&)
		 * @see   AutoInput
		 */
		VIPRESULT extractTo(vipFrameRGB24& img);


		/**
		 * @brief Load bmp data into image parameter, if AutoInput is enabled
		 *        try to load next filename, else just copy current data to img.
		 *
		 * @param[out] img Greyscale VIPLibb Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note  Ouput operator (>>) call directly this function.
		 * @see   operator >> (vipFrameT&)
		 * @see   AutoInput
		 */
		VIPRESULT extractTo(vipFrameT<unsigned char>& img);



		/**
		 * @brief Load given image into memory, if AutoOutput is enabled
		 *        image data will be saved as a BMP format file.
		 *
		 * @param[in] img VIPLibb Cache Frame to be processed (encoded for example)
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note  Input operator (<<) call directly this function.
		 * @see   operator << (vipFrameYUV420&)
		 */
		VIPRESULT importFrom(vipFrameYUV420& img );
		
		/**
		 * @brief Load given image into memory, if AutoOutput is enabled
		 *        image data will be saved as a BMP format file.
		 *
		 * @param[in] img VIPLibb Cache Frame to be processed (encoded for example)
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note  Input operator (<<) call directly this function.
		 * @see   operator << (vipFrameYUV420&)
		 */
		VIPRESULT importFrom(vipFrameYUV444& img );

		/**
		 * @brief Load given image into memory, if AutoOutput is enabled
		 *        image data will be saved as a BMP format file.
		 *
		 * @param[in] img VIPLibb Cache24 Frame to be processed (encoded for example)
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note  Input operator (<<) call directly this function.
		 * @see   operator << (vipFrameRGB24&)
		 */
		VIPRESULT importFrom(vipFrameRGB24& img);


		/**
		 * @brief Load given image into memory, if AutoOutput is enabled
		 *        image data will be saved as a BMP format file.
		 *
		 * @param[in] img Greyscale VIPLibb Frame to be processed (encoded for example)
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note  Input operator (<<) call directly this function.
		 * @see   operator << (vipFrameT&)
		 */
		VIPRESULT importFrom(vipFrameT<unsigned char>& img);






// call importFrom, so filename index is managed

		/**
		 * @brief Input operator, import standard VIPLibb frame formats,
		 *        current implementation calls directly importFrom() method.
		 *
		 * @param[in] img VIPLibb Cache Frame to be processed (encoded for example)
		 *
		 * @see   importFrom(vipFrameYUV420&)
		 */
		void operator << (vipFrameYUV420& img) { vipOutput::operator << (img); }
		void operator << (vipFrameRGB24& img) { vipOutput::operator << (img); }
		void operator << (vipFrameT<unsigned char>& img) { vipOutput::operator << (img); }

// call extractTo, so filename index and frame rate are managed

		/**
		 * @brief Ouput operator, export to standard VIPLibb frame formats,
		 *        current implementation calls directly extractTo() method
		 *        and if framerate isn't zero waits untill clock is syncronized,
		 *        if elaboration time is greater than sleeptime, no delay is applied.
		 *
		 * @param[out] img VIPLibb Cache Frame to store data.
		 *
		 * @return Address of current instance.
		 *
		 * @see   importFrom(vipFrameYUV420&)
		 * @see   vipsleep()
		 * @see   setElaborationStart()
		 * @see   getElaborationTime()
		 */
		vipInput& operator >> (vipFrameYUV420& img) { vipInput::operator >> (img); return *this; }
		vipInput& operator >> (vipFrameRGB24& img) { vipInput::operator >> (img); return *this; }
		vipInput& operator >> (vipFrameT<unsigned char>& img) { vipInput::operator >>( img); return *this; }






		/**
		 * @brief Save given image to a BMP file.
		 *
		 * @param[in] source VIPLibb Cache Frame to store data.
		 * @param[in] filename Output BMP filename.
		 * @param[in] format BMP Encoding Format.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 */
		static VIPRESULT save(vipFrameRGB24 &source, const char *filename,FileFormat format);

		/**
		 * @brief Save given image to a BMP file.
		 *
		 * @param[in] source VIPLibb Cache24 Frame to store data.
		 * @param[in] filename Output BMP filename.
		 * @param[in] format BMP Encoding Format.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 */
		static VIPRESULT save(vipFrameYUV420 &source, const char *filename,FileFormat format);

		/**
		 * @brief Save given image to a BMP file.
		 *
		 * @param[in] source Color VIPLibb Frame to store data.
		 * @param[in] filename Output BMP filename.
		 * @param[in] format BMP Encoding Format.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 */
		static VIPRESULT save(vipFrameT<unsigned char> &source, const char *filename, FileFormat format);

		/**
		 * @brief Save given image to a BMP file.
		 *
		 * @param[in] source VIPLibb Cache Frame to store data.
		 * @param[in] filename Output BMP filename.
		 * @param[in] format BMP Encoding Format.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 */
		static VIPRESULT save(vipFrameRGB96 &source, const char *filename,FileFormat format);

		/**
		 * @brief Load a BMP format image into given image.
		 *
		 * @param[out] source VIPLibb Cache Frame to store data.
		 * @param[in] filename Input BMP filename.
		 * @param[in] format BMP Encoding Format.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 */
		static VIPRESULT load(vipFrameRGB24 &source, const char *filename,FileFormat format);

		/**
		 * @brief Load a BMP format image into given image.
		 *
		 * @param[out] source VIPLibb Cache24 Frame to store data.
		 * @param[in] filename Input BMP filename.
		 * @param[in] format BMP Encoding Format.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 */
		static VIPRESULT load(vipFrameYUV420 &source, const char *filename,FileFormat format);

		/**
		 * @brief Load a BMP format image into given image.
		 *
		 * @param[out] source Color VIPLibb Frame to store data.
		 * @param[in] filename Input BMP filename.
		 * @param[in] format BMP Encoding Format.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 */
		static VIPRESULT load(vipFrameT<unsigned char> &source, const char *filename, FileFormat format);

		/**
		 * @brief Load a BMP format image into given image.
		 *
		 * @param[out] source GreyScale VIPLibb Frame to store data.
		 * @param[in] filename Input BMP filename.
		 * @param[in] format BMP Encoding Format.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 */
		static VIPRESULT load(vipFrameRGB96 &source, const char *filename, FileFormat format);


		bool isEncodingAvailable() { return true; };
		bool isDecodingAvailable() { return true; };

};


class vipCodec_BMPParameters : public vipCodecParameters
{
	protected:

		int fileNameIndex;
		char fileNameBase[128];
		bool fileNameProgression;
		bool autoOuput;
		bool autoInput;
		bool doBuffering;
		vipCodec_BMP::FileFormat fileFormat;


		friend class vipCodec_BMP;


	public:

		vipCodec_BMPParameters();
		vipCodec_BMPParameters(const char* filename, vipCodec_BMP::FileFormat format = vipCodec_BMP::FORMAT_BMP_ANY);
		~vipCodec_BMPParameters()  {  }

		void reset();


		/**
		 * @brief	Set current index for filename progression, for example:
		 *          basefile name is "output", index is 13 so filename is output13.bmp,
		 *			if filename progression is enabled, when an operation is done
		 *          onto file, idex is incremented.
		 *
		 * @param[in] base current filename index as integer value.
		 *
		 * @return VIPRET_OK if everything is fine,
		 *		   VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 * @see
		 */
		void setFileNameIndex(int base = -1) { fileNameIndex = base; };

		/**
		 * @brief	Enable or disable filename progression, for example:
		 *          basefile name is "output", index is 13 so filename is output13.bmp,
		 *			if filename progression is enabled, when an operation is done
		 *          onto file, idex is incremented (output14.bmp).
		 *
		 * @param[in] value true to enable file name progression.
		 */
		void setFileNameProgression(bool value = true) { fileNameProgression = value; };

		/**
		 * @brief   Enable or disable auto input feature,
		 *
		 *
		 * @param[in]
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note
		 * @see
		 */
		void setAutoOutputEnabled(bool value = true) { autoOuput = value; };

		/**
		 * @brief
		 *
		 *
		 * @param[in]
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note
		 * @see
		 */
		void setAutoInputEnabled(bool value = true) { autoInput = value; };

		/**
		 * @brief
		 *
		 *
		 * @param[in]
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note
		 * @see
		 */
		void setDoBuffering(bool value = true) { doBuffering = value; };

		/**
		 * @brief
		 *
		 *
		 * @param[in]
		 *
		 * @note
		 * @see
		 */
		void setFileName(const char *filename);

		/**
		 * @brief  Set current BMP format.
		 *
		 * @param[in] format BMP format enumaration.
		 *
		 * @see    FileFormat
		 */
		void setFileFormat(vipCodec_BMP::FileFormat format = vipCodec_BMP::FORMAT_BMP_24) { fileFormat = format; };

		/**
		 * @brief  Read current file name index, used in file name progression
		 *         routines.
		 *
		 * @return VIPRET_OK if everything is fine,
		 *		   VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note
		 * @see
		 */

		int getFileNameIndex() { return fileNameIndex;};
		/**
		 * @brief
		 *
		 *
		 * @return true if filename progression is enabled.
		 *
		 * @see   fileNameProgression
		 */
		bool isFileNameProgressionEnabled() { return fileNameProgression; };

		/**
		 * @brief
		 *

		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note
		 * @see
		 */
		bool isAutoInputEnabled() { return autoInput;};

		/**
		 * @brief
		 *
		 *
		 * @param[in]
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note
		 * @see
		 */
		bool isAutoOutputEnabled() { return autoOuput;};

		/**
		 * @brief
		 *
		 *
		 * @param[in]
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note
		 * @see
		 */
		bool isBufferingEnabled() { return doBuffering;};

		/**
		 * @brief Read base filename, if progression is enabled it's the base fixed
		 *        name.
		 *
		 * @param[in]
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note
		 * @see
		 */
		void getFileName(char *filename);

		/**
		 * @brief Read current filename, if progression is enabled it's the base fixed
		 *        name + current index + bmp extension.
		 *
		 * @param[out] Char Array to store current filename [Max size 64 chars]
		 *
		 * @see   fileNameBase
		 */
		void getFileNameCurrent(char *filename);

		/**
		 * @brief Read current bitmap encoding/decoding format.
		 *
		 * @return Current I/O BMP format.
		 *
		 * @see   FileFormat
		 * @see   fileFormat
		 */
		vipCodec_BMP::FileFormat getFileFormat() { return fileFormat; };


		int saveToStreamXML(FILE *fp);
		int loadFromStreamXML(FILE *fp);

};






#endif //__VIPLIB_VETCODER_BMP_H__
