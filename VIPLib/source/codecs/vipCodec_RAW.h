/** @file    vipCodec_RAW.h
 *  @class   vipCodec_RAW
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
 *  @see     vipCodec
 *
 *  @version 0.1
 *  @date    10/11/2005
 *  @author  Nicola Piotto
 *
 *
 ****************************************************************************
 * VIPLibb Framework 1.02
 *  Copyright (C) Alessandro Polo 2005
 *  http://mmlab.disi.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DISI - University of Trento
 *
 ****************************************************************************/



#ifndef __VIPLIB_VIPCODER_RAW_H__
 #define __VIPLIB_VIPCODER_RAW_H__

//respect ./source/filters or ./packages/filters directory
 #include "../vipDefs.h"
 #include "../vipCodec.h"

 #include "../vipFrame.h"
 #include "../vipFrameRGB24.h"
 #include "../vipFrameYUV420.h"
 #include "../vipFrameYUV444.h"
 #include "../vipFrameGrey.h"

 #include "../vipFrameT.h"
 //#include <fstream.h>



 // include here needed headers
 // (but include all files you can in cpp instead)



class vipCodec_RAWParameters : public vipFilterParameters
{
	private:

		int Ywidth;   //dimension Y plane
		int Yheight;
		char Video_Format[15];  //yuv420,yuv444,..


	protected:


		char fileName[64];
		long frameIndex;
		int stream;
		int Fps;

		friend class vipCodec_RAW;


	public:

		/**
		 * @brief  Default constructor, call reset().
		 */
		vipCodec_RAWParameters();


		/**
		 * @brief Full constructor, call reset() and set parameters.
		 *
		 * @param[in] filename pointer to NULL terminated string [max 128].
		 * @param[in] stream movie's stream to load (default=0, first stream)
		 * @param[in] frameIndex stream position (default=0, first frame)
		 *
		 */
		vipCodec_RAWParameters(const char* filename, int stream = 0, long frameIndex = 0);


		/**
		 * @brief  Default destructor.
		 */
		~vipCodec_RAWParameters() { }



		/**
		 * @brief  Reset all parameters: filename, current stream, frame index.
		 */
		void reset();



		void setYwidth(int width);
		void setYheight(int height);
		void setVideoFormat(const char* format);
		void setFps(int fps);
		int getFps(){ return Fps; };



		/**
		 * @brief  set current stream (it's not applied really, but must call
		 *         load(stream) of vipCodec_MOV class).
		 *
		 * @param[in] stream movie's stream to load (default=0, first stream)
		 */
		void setStream(int stream = 0);



		/**
		 * @brief  set current stream (it's not applied really, but must call
		 *         load(filename, stream) of vipCodec_MOV class).
		 *
		 * @param[in] stream movie's filename to load (NULL Terminated string, max 128)
		 */
		void setFileName(const char *filename);


////////// to copy in parameter (char array)
		inline char* getFileName() { return fileName; };


		/**
		 * @brief  set current frame index (it's not applied really, but must call
		 *         setFrameIndex(index) of vipCodec_MOV class).
		 *
		 * @param[in] frameIndex stream position (default=0, first frame)
		 */
		void setFrameIndex(long index = 0);




		/**
		 * @brief  Serialize class to XML format.
		 *         Class' tag is <vipCodec_MOVParameters>
		 *
		 * @param[in] fp output stream's pointer
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
		 */
		int saveToStreamXML(FILE *fp);



		/**
		 * @brief  Deserialize class from XML format.
		 *         Class' tag must be <vipCodec_MOVParameters>
		 *
		 * @param[in] fp input stream's pointer
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
		 */
		int loadFromStreamXML(FILE *fp);



};


class vipCodec_RAW :  public vipCodec
 {
	public:


	protected:

		vipCodec_RAWParameters* myParams;


		FILE * f;				//I/O operations

		unsigned int width;		// Ywidth
		unsigned int height;	// Yheight

		unsigned int UVwidth;   //UV plane dimension
		unsigned int UVheight;
		unsigned int NumberPixel;  //total number of pixel per frame (all YUV plane)
		unsigned int NumberFrame;  //total number of frames in sequence

		unsigned char*	pData;		//Pointer to the frame data



		 double range_S;
		 double average_S;


	public:


		/**
		 * @brief  Default constructor, initialize parameters and superclasses.
		 */
		vipCodec_RAW(vipCodec_RAWParameters* initParams = NULL);


		/**
		 * @brief  Initialize parameters and load image/video stream from file.
		 *         vipFrameRGB constructor.
		 *
		 * @param[in] filename Input BMP filename.
		 * @param[in] format BMP Encoding Format, default auto-selection.
		 */
		vipCodec_RAW(char* filename, int stream = 0);


		~vipCodec_RAW();



		/**
		 * @brief  Load an image/video into current buffer (vipFrameRGB).
		 *
		 * @param[in] filename Input BMP filename.
		 * @param[in] format BMP Encoding Format.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 */
		VIPRESULT load(char *filename, int stream = 0);
		VIPRESULT load();



		/**
		 * @brief  Load.
		 *
		 * @param[in] filename a valid MPEG1-2 movie filename
		 * @param[in] stream video stream to load (default is first: 0)
		 *
		 * @return VIPRET_ILLEGAL_USE if file is not correctly loaded, VIPRET_OK else.
		 */
		VIPRESULT save(char *filename, int stream = 0)
		{
			return VIPRET_NOT_IMPLEMENTED;
		};

		unsigned char ReadFrame(unsigned int Frame);
		int newVideo(const char *filename);
		//int sub_BackGround(unsigned char* in);
		//unsigned char* UV_upsampling(unsigned char* in);  //crominance upsampling..
		//int conv_PlanarYUVtoPixelRGB(unsigned char* YUV_Planar_ptr, unsigned char* RGB_Packed_Ptr, unsigned int width, unsigned int height);
		//int conv_PixelRGBtoPlanarYUV(unsigned char* RGB_Packed_Ptr, unsigned char* YUV_Planar_ptr, unsigned int width, unsigned int height);

		VIPRESULT close(void);

		/**
		 * @brief  Set parameters for (de)coding.
		 *
		 * @param[in] initParams Instance of vipCodec_RAWParameters or NULL,
		 *                       NULL argument make function to create a new
		 *                       instance with default parameters.
		 *
		 * @return VIPRET_OK
		 */
		VIPRESULT setParameters(vipCodec_RAWParameters* initParams);

		/**
		 * @brief  Get parameters for (de)coding.
		 *
		 * @return pointer to vipCodec_RAWParameters class.
		 */
		vipCodec_RAWParameters& getParameters() { return *myParams; };


		VIPRESULT setFilterParameters (vipFilterParameters* initParams) { return setParameters(static_cast<vipCodec_RAWParameters*>(initParams)); };
		vipFilterParameters* getFilterParameters () { return static_cast<vipFilterParameters*>(myParams); };

		/**
		 * @brief read current image's width.
		 *
		 * @return Width in pixel.
		 */
		unsigned int getWidth() const
		 {

			return width;

		 };





		/**
		 * @brief read current image's height.
		 *
		 * @return Height in pixel.
		 */
		unsigned int getHeight() const
		 {

			return height;

		 };



		/**
		 * @brief  Set current canvas' height.
		 *
		 * @return height in pixel.
		 */
		VIPRESULT setHeight(unsigned int value)
		 {
			if (f != NULL)
				return VIPRET_ILLEGAL_USE;

			height = value;

			return VIPRET_OK;
		 };



		/**
		 * @brief  Set current canvas' width.
		 *
		 * @return width in pixel.
		 */
		VIPRESULT setWidth(unsigned int value)
		 {
			if (f != NULL)
				return VIPRET_ILLEGAL_USE;

			width = value;

			return VIPRET_OK;
		 };



		/**
		 * @brief  Reset filename related setup.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR
		 *		   or VIPRET_ILLEGAL_USE else.
		 */
		VIPRESULT reset();



		/**
		 * @brief  return true when the end of file is reached
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR
		 *		   or VIPRET_ILLEGAL_USE else.
		 */
		bool EoF();


		/**
		 * @brief  return the total number of frame in the sequence
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR
		 *		   or VIPRET_ILLEGAL_USE else.
		 */
		unsigned int getNumberFrame() const
		{
			return NumberFrame;
		}


		/**
		 * @brief check if loaded movie has a video stream.
		 *
		 * @return true if there is at least one video stream, false else.
		 */
		bool hasVideo(int stream = -1) { return false; };



		/**
		 * @brief get movie's audio streams count.
		 *
		 * @return number of audio streams.
		 */
		bool hasAudio(int stream = -1) { return false; };


		long getAudioStreamLength(int stream = -1) { return -1; };



		/**
		 * @brief get movie's audio streams count.
		 *
		 * @return number of audio streams.
		 */
		int getAudioStreamCount()
		 {
			 return -1;
		 };



		/**
		 * @brief get movie's video streams count.
		 *
		 * @return number of video streams.
		 */
		int getVideoStreamCount()
		 {
			 return -1;
		 };




		long getVideoStreamLength(int stream = -1)
		{
			return 0;
		};


////////////////////////////////////////////////////////////////////////////////////////////
// Todo Comments

		inline double getFrameSaturationRange() { return range_S; };
		inline double getFrameSaturationAverage() { return average_S; };


// TEMP CONVERSIONS
//unsigned char* UV_upsampling(unsigned char* in, int width, int height); // commented by Marco Verza while cleaning up conversion routines
//to do down_sampling fro 420 to 444
// marcoverza_todo: clean up the following too?
VIPRESULT conv_PlanarYUVtoPixelRGB(unsigned char* YUV_Planar_ptr, unsigned char* RGB_Packed_Ptr, unsigned int width, unsigned int height);
VIPRESULT conv_PixelRGBtoPlanarYUV(unsigned char* RGB_Packed_Ptr, unsigned char* YUV_Planar_ptr, unsigned int width, unsigned int height);

VIPRESULT conv_PixelRGBtoPixelHSV(unsigned char* RGB_Packet_ptr, float* HSV_Packet_ptr, unsigned int width, unsigned int height);
VIPRESULT conv_PixelHSVtoPixelRGB(float* HSV_Pixel_ptr, unsigned char* RGB_Packed_ptr, unsigned int width, unsigned int height);

VIPRESULT conv_PlanarYUVtoPixelHSV(unsigned char* YUV_Planar_ptr, float* HSV_Packet_ptr, unsigned int width, unsigned int height);

////////////////////////////////////////////////////////////////////////////////////////////

		/**
		 * @brief  Load data into passed image, move current index to next frame.
		 *
		 * @param[out] img VIPLibb Cache Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note   Ouput operator (>>) call directly this function.
		 * @see    operator >> (vipFrameCache&)
		 * @see    AutoInput
		 */
		VIPRESULT extractTo(vipFrameYUV420& img);


		/**
		 * @brief  Load data into passed image, move current index to next frame.
		 *         Added by Marco Verza
		 *
		 * @param[out] img VIPLibb Cache Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note   Ouput operator (>>) call directly this function.
		 * @see    operator >> (vipFrameCache&)
		 * @see    AutoInput
		 */
		VIPRESULT extractTo(vipFrameYUV444& img);



		/**
		 * @brief  Load data into passed image, move current index to next frame.
		 *
		 * @param[out] img VIPLibb Cache24 Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note   Ouput operator (>>) call directly this function.
		 * @see    operator >> (vipFrameCache24&)
		 * @see    AutoInput
		 */
		VIPRESULT extractTo(vipFrameRGB24& img);



		/**
		 * @brief  Load data into passed image, move current index to next frame.
		 *
		 * @param[out] img Color VIPLibb Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note   Ouput operator (>>) call directly this function.
		 * @see    operator >> (vipFrameRGB&)
		 * @see    AutoInput
		 */
		VIPRESULT extractTo(vipFrameT<unsigned char>& img);





		/**
		 * @brief  Add given image to current stream.
		 *
		 * @param[in] img VIPLibb Cache Frame to be processed (encoded for example)
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note   Input operator (<<) call directly this function.
		 * @see    operator << (vipFrameCache&)
		 */
		VIPRESULT importFrom(vipFrameYUV420& img);



		/**
		 * @brief  Add given image to current stream.
		 *
		 * @param[in] img VIPLibb Cache24 Frame to be processed (encoded for example)
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note   Input operator (<<) call directly this function.
		 * @see    operator << (vipFrameCache24&)
		 */
		VIPRESULT importFrom(vipFrameRGB24& img);



		/**
		 * @brief  Add given image to current stream.
		 *
		 * @param[in] img Color VIPLibb Frame to be processed (encoded for example)
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note   Input operator (<<) call directly this function.
		 * @see    operator << (vipFrameRGB&)
		 */
		VIPRESULT importFrom(vipFrameT<unsigned char>& img);



		/**
		 * @brief  Add given image to current stream.
		 *
		 * @param[in] img Greyscale VIPLibb Frame to be processed (encoded for example)
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note   Input operator (<<) call directly this function.
		 * @see    operator << (vipFrameGrey&)
		 */
		//int importFrom(vipFrameGrey& img);




		/**
		 * @brief Input operator, import standard VIPLibb frame formats,
		 *        current implementation calls directly importFrom() method.
		 *
		 * @param[in] img VIPLibb Cache Frame to be processed (encoded for example)
		 *
		 * @see   importFrom(vipFrameCache&)
		 */
		void operator << (vipFrameYUV420& img) { vipOutput::operator << (img); }
		void operator << (vipFrameRGB24& img) { vipOutput::operator << (img); }
		void operator << (vipFrameT<unsigned char>& img) { vipOutput::operator << (img); }

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
		 * @see   importFrom(vipFrameCache&)
		 * @see   vipsleep()
		 * @see   setElaborationStart()
		 * @see   getElaborationTime()
		 */
		vipInput& operator >> (vipFrameYUV420& img) { vipInput::operator >> (img); return *this; }
		vipInput& operator >> (vipFrameYUV444& img) { vipInput::operator >> (img); return *this; }
		vipInput& operator >> (vipFrameRGB24& img) { vipInput::operator >> (img); return *this; }
		vipInput& operator >> (vipFrameT<unsigned char>& img) { vipInput::operator >>( img); return *this; }



		bool isEncodingAvailable() { return true; };
		bool isDecodingAvailable() { return true; };
};






#endif //__VIPLIB_VIPCODER_RAW_H__
