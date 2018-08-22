/**
 *  @class   %CLASSNAME%
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
 *  @version %VERSION%
 *  @date    %TODAY%
 *  @author  %AUTHOR%
 *
 ****************************************************************************
 *  Class based on Package Studio template: vipCodec_Template version 0.9.12
 ****************************************************************************
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.science.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DIT - University of Trento
 *
 ****************************************************************************/



#ifndef __VIPLIB_%CLASSDEFINE%_H__
 #define __VIPLIB_%CLASSDEFINE%_H__

 #include "%SOURCEDIR%vipCodec.h"

 // include here needed headers
 // (but include all files you can in cpp instead)





class %CLASSNAME%Parameters : public vipCodecParameters
{
	protected:


%EFI_START%
		char fileName[64];
		long frameIndex;
		int stream;
%EFI_END%

		friend class %CLASSNAME%;


	public:

		%DOCFUN%/**
		 * @brief  Default constructor, call reset().
		 */
		%CLASSNAME%Parameters();

%EFI_START%
		%DOCFUN%/**
		 * @brief Full constructor, call reset() and set parameters.
		 *
		 * @param[in] filename pointer to NULL terminated string [max 128].
		 * @param[in] stream movie's stream to load (default=0, first stream)
		 * @param[in] frameIndex stream position (default=0, first frame)
		 *
		 */
		%CLASSNAME%Parameters(const char* filename, int stream = 0, long frameIndex = 0);
%EFI_END%

		%DOCFUN%/**
		 * @brief  Default destructor.
		 */
		~%CLASSNAME%Parameters() { }


%VFI_START%
		%DOCFUN%/**
		 * @brief  Reset all parameters: filename, current stream, frame index.
		 */
		void reset();
%VFI_END%

%EFI_START%
		%DOCFUN%/**
		 * @brief  set current stream (it's not applied really, but must call
		 *         load(stream) of %CLASSNAME% class).
		 *
		 * @param[in] stream movie's stream to load (default=0, first stream)
		 */
		void setStream(int stream = 0);
%EFI_END%

%EFI_START%
		%DOCFUN%/**
		 * @brief  set current stream (it's not applied really, but must call
		 *         load(filename, stream) of %CLASSNAME% class).
		 *
		 * @param[in] stream movie's filename to load (NULL Terminated string, max 128)
		 */
		void setFileName(const char *filename);
%EFI_END%

%EFI_START%
		%DOCFUN%/**
		 * @brief  set current frame index (it's not applied really, but must call
		 *         setFrameIndex(index) of %CLASSNAME% class).
		 *
		 * @param[in] frameIndex stream position (default=0, first frame)
		 */
		void setFrameIndex(long index = 0);
%EFI_END%


%VFI_START%
		%DOCFUN%/**
		 * @brief  Serialize class to XML format.
		 *         Class' tag is <%CLASSNAME%Parameters>
		 *
		 * @param[in] fp output stream's pointer
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
		 */
		VIPRESULT saveToStreamXML(FILE *fp);
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Deserialize class from XML format.
		 *         Class' tag must be <%CLASSNAME%Parameters>
		 *
		 * @param[in] fp input stream's pointer
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
		 */
		VIPRESULT loadFromStreamXML(FILE *fp);
%VFI_END%


};





class %CLASSNAME% :  public vipCodec
 {
	public:


	protected:

		%CLASSNAME%Parameters* myParams;

%EFI_START%

		unsigned char**	buff;		///< Buffer for decoded data

		char *Y ;            ///< Buffer for decoded YUV Y data
		char *U ;            ///< Buffer for decoded YUV U data
		char *V ;            ///< Buffer for decoded YUV V data

		unsigned int width;		///< width
		unsigned int height;		///< height
%EFI_END%

	public:


		%DOCFUN%/**
		 * @brief  Default constructor, initialize parameters and superclasses.
		 */
		%CLASSNAME%(%CLASSNAME%Parameters* initParams = NULL);

%EFI_START%
		%DOCFUN%/**
		 * @brief  Initialize parameters and load image/video stream from file.
		 *         vipFrameRGB constructor.
		 *
		 * @param[in] filename Input BMP filename.
		 * @param[in] format BMP Encoding Format, default auto-selection.
		 */
		%CLASSNAME%(char* filename, int stream = 0);
%EFI_END%

		~%CLASSNAME%();



		%DOCFUN%/**
		 * @brief  Set parameters for (de)coding.
		 *
		 * @param[in] initParams Instance of %CLASSNAME%Parameters or NULL,
		 *                       NULL argument make function to create a new
		 *                       instance with default parameters.
		 *
		 * @return VIPRET_OK
		 */
		int setParameters(%CLASSNAME%Parameters* initParams);

		%DOCFUN%/**
		 * @brief  Get parameters for (de)coding.
		 *
		 * @return pointer to %CLASSNAME%Parameters class.
		 */
		%CLASSNAME%Parameters& getParameters() { return *myParams; };


%VFI_START%
		%DOCFUN%/**
		 * @brief  Load an image/video into current buffer (vipFrameRGB).
		 *
		 * @param[in] filename Input BMP filename.
		 * @param[in] format BMP Encoding Format.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 */
		VIPRESULT load(char *filename, int stream = 0);
%VFI_END%



%VFI_START%
		%DOCFUN%/**
		 * @brief  Save current movie to file.
		 *
		 * @param[in] filenameoutput movie filename
		 * @param[in] stream video stream to load (default is first: 0)
		 *
		 * @return VIPRET_ILLEGAL_USE if file is not correctly loaded, VIPRET_OK else.
		 */
		VIPRESULT save(char *filename, int stream = -1);
%VFI_END%


%VFI_START%
		%DOCFUN%/**
		 * @brief  Close current movie (close file access).
		 *
		 * @return VIPRET_ILLEGAL_USE if movie was not loaded, VIPRET_OK else.
		 */
		VIPRESULT close();
%VFI_END%



%VFI_START%
		%DOCFUN%/**
		 * @brief  Check ability to encode data.
		 *
		 * @return true is class is able to encode video data, flase else.
		 */
		bool isEncodingAvailable()
		 {
%EFI_START%
			return false;
%EFI_END%
		 };
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Check ability to decode data.
		 *
		 * @return true is class is able to decode video data, flase else.
		 */
		bool isDecodingAvailable()
		 {
%EFI_START%
			return false;
%EFI_END%
		 };
%VFI_END%



%VFI_START%
		%DOCFUN%/**
		 * @brief  Get the state of current data source.
		 *
		 * @return true is there are no more frames to load, false else.
		 */
		bool EoF()
		 {
%EFI_START%
			return false;
%EFI_END%
		 };
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief read current image's width.
		 *
		 * @return Width in pixel.
		 */
		unsigned int getWidth() const
		 {
%EFI_START%
			return width;
%EFI_END%
		 };
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief read current image's height.
		 *
		 * @return Height in pixel.
		 */
		unsigned int getHeight() const
		 {
%EFI_START%
			return height;
%EFI_END%
		 };
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Set current canvas' height.
		 *
		 * @return height in pixel.
		 */
		VIPRESULT setHeight(unsigned int value)
		 {
%EFI_START%
			 height = value;
%EFI_END%
			 return VIPRET_NOT_IMPLEMENTED;
		 };
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Set current canvas' width.
		 *
		 * @return width in pixel.
		 */
		VIPRESULT setWidth(unsigned int value)
		 {
%EFI_START%
			 width = value;
%EFI_END%
			 return VIPRET_NOT_IMPLEMENTED;
		 };
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Reset filename related setup.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR
		 *		   or VIPRET_ILLEGAL_USE else.
		 */
		VIPRESULT reset();
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Check if loaded movie has a video stream.
		 *
		 * @param[in] stream select stream, default is current stream.
		 *
		 * @return true if there is at least one video stream, false else.
		 */
		bool hasVideo(int stream = -1)
		 {
%EFI_START%
			return false;
%EFI_END%
		 };
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Check if loaded movie has an audio stream.
		 *
		 * @param[in] stream select stream, default is current stream.
		 *
		 * @return true if there is at least one video stream, false else.
		 */
		bool hasAudio(int stream = -1)
		 {
%EFI_START%
			return false;
%EFI_END%
		 };
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief get movie's audio streams count.
		 *
		 * @return number of audio streams.
		 */
		int getAudioStreamCount();
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief get movie's video streams count.
		 *
		 * @return number of video streams.
		 */
		int getVideoStreamCount();
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief get movie's video frame rate.
		 *
		 * @param[in] stream select stream index.
		 *                   default is -1: current active stream.
		 *
		 * @return number of frame per second.
		 */
		float getVideoFrameRate(int stream = -1);
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Get movie's video stream frame count.
		 *
		 * @param[in] stream select stream, default is current stream.
		 *
		 * @return number of frames in selected video stream.
		 */
		long getVideoStreamLength(int stream = -1);
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Get movie's audio stream sample count.
		 *
		 * @param[in] stream select stream, default is current stream.
		 *
		 * @return number of samples in selected audio stream.
		 */
		long getAudioStreamLength(int stream = -1);
%VFI_END%






%VFI_START%
		%DOCFUN%/**
		 * @brief  Load data into passed image, move current index to next frame.
		 *
		 * @param[out] img VIPLib Cache Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note   Ouput operator (>>) call directly this function.
		 * @see    operator >> (vipFrameYUV420&)
		 * @see    AutoInput
		 */
		VIPRESULT extractTo(vipFrameYUV420& img);
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Load data into passed image, move current index to next frame.
		 *
		 * @param[out] img VIPLib Cache Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note   Ouput operator (>>) call directly this function.
		 * @see    operator >> (vipFrameYUV444&)
		 * @see    AutoInput
		 */
		VIPRESULT extractTo(vipFrameYUV444& img);
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Load data into passed image, move current index to next frame.
		 *
		 * @param[out] img VIPLib Cache24 Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note   Ouput operator (>>) call directly this function.
		 * @see    operator >> (vipFrameRGB24&)
		 * @see    AutoInput
		 */
		VIPRESULT extractTo(vipFrameRGB24& img);
%VFI_END%


%VFI_START%
		%DOCFUN%/**
		 * @brief  Load data into passed image, move current index to next frame.
		 *
		 * @param[out] img Greyscale VIPLib Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note   Ouput operator (>>) call directly this function.
		 * @see    operator >> (vipFrameT<unsigned char>&)
		 * @see    AutoInput
		 */
		VIPRESULT extractTo(vipFrameT<unsigned char>& img);
%VFI_END%



%VFI_START%
		%DOCFUN%/**
		 * @brief  Add given image to current stream.
		 *
		 * @param[in] img VIPLib Cache Frame to be processed (encoded for example)
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note   Input operator (<<) call directly this function.
		 * @see    operator << (vipFrameYUV420&)
		 */
		VIPRESULT importFrom(vipFrameYUV420& img);
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Add given image to current stream.
		 *
		 * @param[in] img VIPLib Cache24 Frame to be processed (encoded for example)
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note   Input operator (<<) call directly this function.
		 * @see    operator << (vipFrameRGB24&)
		 */
		VIPRESULT importFrom(vipFrameRGB24& img);
%VFI_END%


%VFI_START%
		%DOCFUN%/**
		 * @brief  Add given image to current stream.
		 *
		 * @param[in] img Greyscale VIPLib Frame to be processed (encoded for example)
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note   Input operator (<<) call directly this function.
		 * @see    operator << (vipFrameT<unsigned char>&)
		 */
		VIPRESULT importFrom(vipFrameT<unsigned char>& img);
%VFI_END%



};




#endif //__VIPLIB_%CLASSDEFINE%_H__
