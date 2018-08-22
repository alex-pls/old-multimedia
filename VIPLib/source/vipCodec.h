/**
 *  @class   vipCodec
 *
 *  @brief   Abstract class for all VetLib de-coders, inherits (as vipFilter)
 *           vipInput, vipOutput and vipObject, some more virtual methods are
 *           imposed.
 *           Internal buffering implementation is left to inherited class.
 *
 *  @see     vipInput, vipOuput, vipObject
 *
 *  @version 1.0.2
 *  @date    23/12/2005
 *  @author  Alessandro Polo
 *
 *
 ****************************************************************************/
/**
 *  @class   vipCodecParameters
 *
 *  @brief   This object is designed to store main codec's variables and
 *           (de)serialize data (from) to XML,
 *
 *  @see     vipFilterParameters
 *
 *  @version 1.0.2
 *  @date    23/12/2005
 *  @author  Alessandro Polo
 *
 ****************************************************************************/
/**
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.disi.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DISI - University of Trento
 *
 ****************************************************************************/


#ifndef __VIPLIB_VIPCODEC_H__
 #define __VIPLIB_VIPCODEC_H__

 #include "vipDefs.h"
 #include "vipObject.h"
 #include "vipInput.h"
 #include "vipOutput.h"
 #include "vipFilter.h"

 #include "vipFrameYUV420.h"
 #include "vipFrameRGB24.h"
 #include "vipFrameT.h"


class vipCodecParameters;

class vipCodec :	public vipInput,
					public vipOutput,
					public vipObject
 {

	protected:




	public:

		/**
		 * @brief Default constructor is protected because this is an
		 *        abstract class and instance cannot be created directly.
		 *
		 * @param fps Frame per second value, default is 0, the max input+processing rate.
		 */
		vipCodec(float fps = 0) : vipObject() { v_sleeptime = 0; }


		/**
		 * @brief Destructor currenly clear only filters description strings.
		 */
		virtual ~vipCodec() {}


		/**
		 * @brief Inherited class must implement this function,
		 *        should reset all filters' parameters, something like
		 *        constructor initialization.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 */
		virtual VIPRESULT reset() = 0;

		/**
		 * @brief  Get movie's audio streams count.
		 *
		 * @return number of audio streams.
		 */
		virtual int getAudioStreamCount() = 0;

		/**
		 * @brief  Get movie's video streams count.
		 *
		 * @return number of video streams.
		 */
		virtual int getVideoStreamCount() = 0;


		/**
		 * @brief  Get the state of current data source.
		 *
		 * @return true is there are no more frames to load, false else.
		 */
		virtual bool EoF() = 0;

		/**
		 * @brief  Check ability to encode data.
		 *
		 * @return true is class is able to encode video data, flase else.
		 */
		virtual bool isEncodingAvailable() = 0;

		/**
		 * @brief  Check ability to decode data.
		 *
		 * @return true is class is able to decode video data, flase else.
		 */
		virtual bool isDecodingAvailable() = 0;



		/**
		 * @brief  Get movie's video stream frame count.
		 *
		 * @param[in] stream select stream, default is current stream.
		 *
		 * @return number of frames in selected video stream.
		 */
		virtual long getVideoStreamLength(int stream = -1) = 0;

		/**
		 * @brief  Get movie's video stream sample count.
		 *
		 * @param[in] stream select stream, default is current stream.
		 *
		 * @return number of samples in selected video stream.
		 */
		virtual long getAudioStreamLength(int stream = -1) = 0;



		/**
		 * @brief  Check if loaded movie has an audio stream.
		 *
		 * @param[in] stream select stream, default is current stream.
		 *
		 * @return true if there is at least one video stream, false else.
		 */
		virtual bool hasAudio(int stream = -1) = 0;

		/**
		 * @brief  Check if loaded movie has a video stream.
		 *
		 * @param[in] stream select stream, default is current stream.
		 *
		 * @return true if there is at least one video stream, false else.
		 */
		virtual bool hasVideo(int stream = -1) = 0;



		/**
		 * @brief  Close current movie (close file access).
		 *
		 * @return VIPRET_ILLEGAL_USE if movie was not loaded, VIPRET_OK else.
		 */
		virtual VIPRESULT close() = 0;




		/**
		 * @brief  Load a movie from a file.
		 *
		 * @param[in] filename input movie filename
		 * @param[in] stream video stream to load (default is first: 0)
		 *
		 * @return VIPRET_ILLEGAL_USE if file is not correctly loaded, VIPRET_OK else.
		 */
		virtual VIPRESULT load(char *filename, int stream = -1) = 0;

		/**
		 * @brief  Save current movie to file.
		 *
		 * @param[in] filenameoutput movie filename
		 * @param[in] stream video stream to load (default is first: 0)
		 *
		 * @return VIPRET_ILLEGAL_USE if file is not correctly loaded, VIPRET_OK else.
		 */
		virtual VIPRESULT save(char *filename, int stream = -1) = 0;




		/**
		 * @brief Inherited class must implement this function, processing
		 *        hardware/format specific stream to standard VIPLib frame formats.
		 *
		 * @param[out] img VIPLib Cache Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note   Ouput operator (>>) call directly this function.
		 * @see    operator >> (vipFrameYUV420&)
		 */
		virtual VIPRESULT extractTo(vipFrameYUV420& img) = 0;

		/**
		 * @brief Inherited class must implement this function, processing
		 *        hardware/format specific stream to standard VIPLib frame formats.
		 *
		 * @param[out] img VIPLib Cache24 Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note   Ouput operator (>>) call directly this function.
		 * @see    operator >> (vipFrameRGB24&)
		 */
		virtual VIPRESULT extractTo(vipFrameRGB24& img) = 0;

		/**
		 * @brief Inherited class must implement this function, processing
		 *        hardware/format specific stream to standard VIPLib frame formats.
		 *
		 * @param[out] img Greyscale VIPLib Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note   Ouput operator (>>) call directly this function.
		 * @see    operator >> (vipFrameT&)
		 */
		virtual VIPRESULT extractTo(vipFrameT<unsigned char>& img) = 0;



		/**
		 * @brief Inherited class must implement this function,
		 *        processing frames to specific output (device or stream)
		 *
		 * @param[in] img VIPLib Cache Frame to be processed (encoded for example)
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note   Input operator (<<) call directly this function.
		 * @see    operator << (vipFrameYUV420&)
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
		 * @note   Input operator (<<) call directly this function.
		 * @see    operator << (vipFrameRGB24&)
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
		 * @note   Input operator (<<) call directly this function.
		 * @see    operator << (vipFrameT&)
		 */
		virtual VIPRESULT importFrom(vipFrameT<unsigned char>& img) = 0;



		/**
		 * @brief  Ignore this, it's a class-type definition, mostly used
		 *         by VIPLib WorkShop, sintax is a bit more complex than
		 *         usual because of a VC6 BUG, it's the same as:
		 *         const int vipClassType = VIPCLASS_TYPE_CODER;
		 */
		enum{ vipClassType = VIPCLASS_TYPE_CODEC };
};



////////////////////////////////////////////////////////////////////////////////////////////////

 #include <stdio.h>
 #include <fstream>


class vipCodecParameters : public vipFilterParameters
 {

	protected:

		char fileName[128];

		long frameIndex;

		int stream;

	public:

		/**
		 * @brief  Default constructor, protected but inherited classes may
		 *         overload to public.
		 */
		vipCodecParameters() { fileName[0] = '\0'; frameIndex = 0, stream = 0; };


		/**
		 * @brief  Default destructor.
		 */
		virtual ~vipCodecParameters() {}


		void reset() {};

		/**
		 * @brief  Serialize class to XML format.
		 *         Class' tag is <vipCodec_MOVParameters>
		 *
		 * @param[in] fp output stream's pointer
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
		 */
		virtual VIPRESULT saveToStreamXML(FILE *fp) = 0;

		/**
		 * @brief  Deserialize class from XML format.
		 *         Class' tag must be <vipCodec_MOVParameters>
		 *
		 * @param[in] fp input stream's pointer
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
		 */
		virtual VIPRESULT loadFromStreamXML(FILE *fp) = 0;

 };


#endif //__VIPLIB_VIPCODEC_H__

