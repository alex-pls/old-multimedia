/**
 *  @class   vipDirectXInput
 *
 *  @brief   This class is the bridge between VIPLibb and DirecX system,
 *           designed for capturing data from compatible devices, such as
 *           WebCams, TV Tuners and more..
 *
 *           DirectX 10 cuts the backward compatibility with older versions,
 *           this module has been developed and tested on DirectX 9.0.
 *           DX10 has not been released yet, probably you need to upgrade
 *           few lines (or nothing) to make this run on new platform, this
 *           because of we use only very standard objects and they might
 *           be compatible with older definitions.
 *
 *           DirectX 8.1 or later is compatible with IEEE1394 OHCI
 *           (Open Host Controller Interface) so you may acquire also
 *           from firewire devices.
 *
 *  @bug     each first frame after processing is blank, following ok.
 *
 *  @warning required DirecX library: amstrmid.lib
 *  @todo
 *
 *  @see     vipInput
 *  @example ../../tests/test_vipDirectXInput.cpp
 *  @example ../../tests/app_vipDirectXLamePlayer.cpp
 *
 *  @version 0.75
 *  @date    24/11/2005
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



#ifndef __VIPLIB_VIPDIRECTXINPUT_H__
 #define __VIPLIB_VIPDIRECTXINPUT_H__

 #include "../vipDefs.h"
 #include "../vipInput.h"

 #include "../vipFrameYUV420.h"
 #include "../vipFrameRGB24.h"
 #include "../vipFrameT.h"



 // just for HWND
// #include <windows.h>

 #define VETDX_MAXDEVICES	20

 struct vipDXCapture;	//defined in vipDirectXInput.cpp


class vipDirectXInput : public vipInput
 {

 protected:

		vipDXCapture* cCap;

		/**
		 * @brief  DirectX compatible device count.
		 */
		int deviceCount;
		/**
		 * @brief  DirectX compatible devices' description.
		 */
		char deviceDesc[VETDX_MAXDEVICES][160];

		int height;	// for control check only
		int width;	// for control check only


		int vipCheckVideoPort(vipDXCapture* vdx);

		int initCaptureGraphBuilder(vipDXCapture* vdx);

		int vipUpdateFormatList(vipDXCapture* vdx);

		/**
		 * @brief  Disconnect filter graph and free objects.
		 *
		 * @param[in] vdx vipDXCapture object to release.
		 */
		void doReleaseMixer(vipDXCapture* vdx);


 public:

		/** Creates a new imVideoCapture object. \n
		 * Returns NULL if there is no capture device available. \n
		 * In Windows returns NULL if DirectX version is older than 8.
		 *  */

		/**
		 * @brief  Default costructor, initialize variables and connect to
		 *         device if requested.
		 *
		 * @param  device device id:  [0, getDeviceCount()[
		 * @param  fps frame rate value (0 = max possible)
		 */

		vipDirectXInput(int device = -1);

		vipDirectXInput(int device, float fps);

		/**
		 * @brief  Default destructor, release objects and buffers
		 *         and destroy the imVideoCapture object.
		 */
		~vipDirectXInput();


		/**
		 * @brief  Read (update) windows' connected device list.
		 *
		 * @see    getDeviceCount(void);
		 * @see    getDeviceDescription(int device);
		 */
		void enumerateDevices(void);

		/**
		 * @brief  Return current device count, call enumerateDevices(void) first.
		 *
		 * @see    enumerateDevices(void);
		 */
		int getDeviceCount(void) { return deviceCount; };

		/**
		 * @brief  Returns the device description. Returns NULL in the last device.
		 *
		 * @see    enumerateDevices(void);
		 * @see    getDeviceCount(void);
		 */
		const char* getDeviceDescription(int device);

		/**
		 * @brief  Get current device id.
		 * @return current device id, if disconnected return -1
		 * @see    enumerateDevices(void);
		 * @see    getDeviceCount(void);
		 */
		int getCurrentDevice();

		/**
		 * @brief  Set current device
		 *
		 * @param[in] device device id:  [0, getDeviceCount()[
		 *
		 * @return VIPRET_ILLEGAL_USE if stream is playing, VIPRET_PARAM_ERR
		 *         if device id is not valid, VIPRET_OK else.
		 */
		VIPRESULT setDevice(int device);



	VIPRESULT openPropertyPage(void* HWND_Owner);


		/**
		 * @brief  Connect to device.
		 *
		 * @return VIPRET_PARAMS_ERR if device is not valid, VET_ILLEGAL_USE
		 *         if a device is already connected, VIPRET_INTERNAL_ERR
		 *         if any error occured, VIPRET_OK else.
		 */
		VIPRESULT connectTo(int device);

		/**
		 * @brief  Connect to current device.
		 *
		 * @return VET_ILLEGAL_USE if a device is already connected,
		 *         VIPRET_INTERNAL_ERR if any error occured, VIPRET_OK else.
		 *
		 * @see    setDevice(int device);
		 */
		VIPRESULT connect(void);

		/**
		 * @brief  Disconnect from current capture device.
		 *
		 * @return VIPRET_ILLEGAL_USE if no device is connected, VIPRET_OK else.
		 */
		VIPRESULT disconnect(void);


		/**
		 * @brief  Stop stream media control.
		 *
		 * @return VIPRET_ILLEGAL_USE if stream is already stopped, VIPRET_OK else.
		 */
		VIPRESULT doStopLive();

		/**
		 * @brief  Start stream media control.
		 *
		 * @return VIPRET_ILLEGAL_USE if stream is already playing,
		 *         VIPRET_INTERNAL_ERR if an error occured, VIPRET_OK else.
		 */
		VIPRESULT doStartLive();

		/**
		 * @brief  Return current media control state.
		 *
		 * @return true is stream is playing live.
		 */
		bool isLive();

		/**
		 * @brief  Get current canvas' width.
		 *
		 * @return width in pixel.
		 */
		unsigned int getWidth() const { return width; };

		/**
		 * @brief  Get current canvas' height.
		 *
		 * @return height in pixel.
		 */
		unsigned int getHeight() const { return height; };

		/**
		 * @brief  Set capture stream size.
		 *
		 * @return VIPRET_INTERNAL_ERR if any error occured, VIPRET_OK else.
		 */
		VIPRESULT setImageSize(int width, int height);

		/**
		 * @brief  Read current image size and store to passed arguments.
		 *
		 * @param[out] width image's width in pixel
		 * @param[out] height image's height in pixel
		 */
		void getImageSize(int *width, int *height);

		/**
		 * @brief  Read current format's id.
		 *
		 * @return format's id
		 */
		int getFormat();

		/**
		 * @brief  Set current format's id.
		 *
		 * @param[in] format format's id
		 *
		 * @return VIPRET_PARAM_ERR if format id is not valid,
		 *         VIPRET_INTERNAL_ERR if an error occured, VIPRET_OK else.
		 */
		VIPRESULT setFormat(int format);

		/**
		 * @brief  Read format's informations.
		 *
		 * @param[in] format's id
		 * @param[out] width selected format's width
		 * @param[out] height selected format's height
		 * @param[out] desc selected format's description
		 *
		 * @return VIPRET_PARAM_ERR if format id is not valid,
		 *         VIPRET_INTERNAL_ERR if an error occured, VIPRET_OK else.
		 */
		VIPRESULT getFormat(int format, int *width, int *height, char* desc);

		/**
		 * @brief  Read support format's count.
		 *
		 * @return valid format's count
		 */
		int getFormatCount();



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



#endif	//__VIPLIB_VIPDIRECTXINPUT_H__

