/**
 *  @class   vipVideo4Linux
 *
 *  @brief   VIPLibb interface with Video4Linux library, captures from
 *           compatible devices, such as webcams, tv tuners and more.
 *
 *  @bug     only RGB device are currently supported (most of)
 *  @warning
 *  @todo    muti-threading, vipVideo4Linux2 (v4l2)
 *
 *  @see     vipInput
 *  @example ../../tests/test_vipVideo4Linux.cpp
 *  @example ../../tests/app_vipVideo4LinuxPlayer.cpp
 *
 *  @version 0.6.8
 *  @date    14/08/2005
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



#ifndef __VIPLIB_VIPVIDEO4LINUX_H__
 #define __VIPLIB_VIPVIDEO4LINUX_H__

 #include "../vipDefs.h"
 #include "../vipInput.h"

 #include "../vipFrameYUV420.h"
 #include "../vipFrameRGB24.h"
 #include "../vipFrameT.h"


// move this to source file!
 #include <linux/videodev.h>


class vipVideo4Linux : public vipInput
 {
	protected:

		/**
		 * @brief single frame BGR buffer (24bpp)
		 */
		unsigned char* videoBuffer;

		/**
		 * @brief Bits per pixel value
		 */
		int bpp;

		/**
		 * @brief device state (disconnected = -1)
		 */
		int fd;

		/**
		 * @brief video depth
		 */
		unsigned int src_depth;

		/**
		 * @brief  Capture stream informations
		 */
		struct video_capability cap;

		/**
		 * @brief  Frame informations (width, height, ..)
		 */
		struct video_window	win;

		/**
		 * @brief  Capture settings (contrast, brightness, ..)
		 */
		struct video_picture vpic;


	public:

		/**
		 * @brief  Default constructor initializes variables and connect.
		 *         to device if asked.
		 *
		 * @param[in] device capture device's path (default: /dev/video0)
		 */
		vipVideo4Linux(char* inputFile = "/dev/video0");

		/**
		 * @brief  Default destructor, disconnect device and delete buffer.
		 */
		~vipVideo4Linux();


		/**
		 * @brief  Connect to device.
		 *
		 * @return VIPRET_PARAMS_ERR if inputfile is NULL, VIP_ILLEGAL_USE
		 *         if a device is already connected, VIPRET_INTERNAL_ERR
		 *         if any error occured, VIPRET_OK else.
		 */
		VIPRESULT connect(char* inputFile = "/dev/video0");

		/**
		 * @brief  Disconnect from current device.
		 *
		 * @return VIPRET_ILLEGAL_USE if no device is connected, VIPRET_OK else.
		 */
		VIPRESULT disconnect();


		/**
		 * @brief  Get the state of current data source.
		 *
		 * @return true is there are no more frames to load, false else.
		 */
		bool EoF();


		/**
		 * @brief  Disconnect and reset the module.
		 *
		 * @return VIPRET_INTERNAL_ERR if any error occur, VIPRET_OK else.
		 */
		VIPRESULT reset();

		/**
		 * @brief  Read color depth for selected stream.
		 *
		 * @return Color Depth.
		 */
		int getColorDepth() { return bpp; };

		/**
		 * @brief  Read pixel count.
		 *
		 * @return Width * Height.
		 */
		int getSize() { return win.width * win.height; };

		/**
		 * @brief  Read current image's width.
		 *
		 * @return Width in pixel.
		 */
		unsigned int getWidth() const { return (unsigned int)win.width; };
		/**
		 * @brief  Read current image's height.
		 *
		 * @return Height in pixel.
		 */
		unsigned int getHeight() const { return (unsigned int)win.height; };

		/**
		 * @brief  Read color palette for current stream.
		 *
		 * @return Color Palette.
		 */
		int getPalette() { return vpic.palette; };

		/**
		 * @brief  Get movie's video streams count.
		 *
		 * @return number of video streams.
		 */
		int getVideoChannelCount() { return cap.channels; };

		/**
		 * @brief  Get movie's audio streams count.
		 *
		 * @return number of audio streams.
		 */
		int getAudioChannelCount() { return cap.audios; };

		/**
		 * @brief  Get current video brightness
		 *
		 * @return brightness value ]MIN_INT, MAX_INT[
		 */
		int getBrightness() { return vpic.brightness; };

		/**
		 * @brief  Set current video brightness
		 *
		 * @param[in] value brightness value ]MIN_INT, MAX_INT[
		 */
		void setBrightness(int value) { vpic.brightness = value; };

		/**
		 * @brief  Get current video contrast
		 *
		 * @return contrast value ]MIN_INT, MAX_INT[
		 */
		int getContrast() { return vpic.contrast; };

		/**
		 * @brief  Set current video contrast
		 *
		 * @param[in] value contrast value ]MIN_INT, MAX_INT[
		 */
		void setContrast(int value) { vpic.contrast = value; };

		/**
		 * @brief  Get current video hue
		 *
		 * @return hue value ]MIN_INT, MAX_INT[
		 */
		int getHue() { return vpic.hue; };

		/**
		 * @brief  Set current video hue
		 *
		 * @param[in] value hue value ]MIN_INT, MAX_INT[
		 */
		void setHue(int value) { vpic.hue = value; };

		/**
		 * @brief  Get current video color
		 *
		 * @return color value ]MIN_INT, MAX_INT[
		 */
		int getColour() { return vpic.colour; };

		/**
		 * @brief  Set current video colour
		 *
		 * @param[in] value colour value ]MIN_INT, MAX_INT[
		 */
		void setColour(int value) { vpic.colour = value; };

		/**
		 * @brief  Get current video whiteness
		 *
		 * @return whiteness value ]MIN_INT, MAX_INT[
		 */
		int getWhiteness() { return vpic.whiteness; };

		/**
		 * @brief  Set current video whiteness
		 *
		 * @param[in] value whiteness value ]MIN_INT, MAX_INT[
		 */
		void setWhiteness(int value) { vpic.whiteness = value; };


		/**
		 * @deprecated
		 *
		 * @brief  Get video buffer address, deprecated.
		 *
		 * @return pointer to buffer (unsigned char * 3 channels, BGR)
		 */
		unsigned char* dump_buffer() { return videoBuffer; };


		/**
		 * @brief  Grab a frame and copy to VIPLibb standard format.
		 *
		 * @param[out] img VIPLibb Cache Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR if any
		 *		   device reading error occurs, VIPRET_NOT_IMPLEMENTED if color
		 *         format is not support.
		 *
		 * @note   Ouput operator (>>) call directly this function.
		 * @see    operator >> (vipFrameYUV420&)
		 */
		VIPRESULT extractTo(vipFrameYUV420& img);

		/**
		 * @brief  Grab a frame and copy to VIPLibb standard format.
		 *
		 * @param[out] img VIPLibb Cache24 Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR if any
		 *		   device reading error occurs, VIPRET_NOT_IMPLEMENTED if color
		 *         format is not support.
		 *
		 * @note   Ouput operator (>>) call directly this function.
		 * @see    operator >> (vipFrameRGB24&)
		 */
		VIPRESULT extractTo(vipFrameRGB24& img);

		/**
		 * @brief  Grab a frame and copy to VIPLibb standard format.
		 *
		 * @param[out] img Greyscale VIPLibb Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR if any
		 *		   device reading error occurs, VIPRET_NOT_IMPLEMENTED if color
		 *         format is not support.
		 *
		 * @note   Ouput operator (>>) call directly this function.
		 * @see    operator >> (vipFrameT&)
		 */
		VIPRESULT extractTo(vipFrameT<unsigned char>& img);

 };



#endif	// __VIPLIB_VIPVIDEO4LINUX_H__
