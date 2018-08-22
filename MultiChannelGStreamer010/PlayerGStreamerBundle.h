/**
 * @class   wosh::devices::PlayerGStreamerBundle
 * @brief   
 *
 *
 *
 *
 * @ingroup Devices
 * @see     wosh::devices::PlayerGStreamer
 ****************************************************************************
 * @version $Id: PlayerGStreamerBundle.h 728 2009-10-13 23:39:59Z alex $
 * @author  Alessandro Polo
 * @date    Released on 2009-06-04
 ****************************************************************************/
/* Copyright (c) 2007-2009, WOSH - Wide Open Smart Home 
 * by Alessandro Polo - OpenSmartHome.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the OpenSmartHome.com WOSH nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY Alessandro Polo ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Alessandro Polo BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ****************************************************************************/

#ifndef __WOSH_Bundles_Devices_PlayerGStreamer_H__
 #define __WOSH_Bundles_Devices_PlayerGStreamer_H__

 #include <core/BundleGeneric.h>
 #include <core/ThreadWorker.h>

 #include <interfaces/Device.h>
 #include <interfaces/devices/PlayerAudio.h>

 #include "IPlayerGStreamerListener.h"


using namespace std;
namespace wosh {
 namespace devices {

 #define _PlayerGStreamer_NAME			"PlayerGStreamer"
 #define _PlayerGStreamer_VERSION		"0.10.19"


class PlayerGStreamerBundle :	public BundleGeneric,
								public virtual wosh::interfaces::Device,
								public virtual wosh::interfaces::devices::PlayerAudio,
								public virtual IThreadListener,
								public IPlayerGStreamerListener  {

	public:

		/**
		 * @brief   Empty constructor, init bundle and vars, Properties and Methods. May Assign device name
		 */
		PlayerGStreamerBundle( const string& name = "", const string& device_name = "default" );

		/**
		 * @brief   Empty destructor, may (synch) stop bundle and internal threads when still running
		 */
		virtual ~PlayerGStreamerBundle();


/** @name Bundle Interface
 * @{
 ******************************************************************************/
	public:

		/**
		 * @brief   Start the internal thread (used for refreshing stats). Also register bundle as Device
		 * @see    BundleGeneric::bundleStart()
		 */
		virtual WRESULT bundleStart();

		/**
		 * @brief   Stop the internal thread (used for refreshing stats). Also unregister bundle as Device
		 * @see    BundleGeneric::bundleStop()
		 */
		virtual WRESULT bundleStop();

		virtual WRESULT bundleDiagnostic();

		virtual void busMessage( const Message& message, Bus* source );

//@}
/** @name Device Interface
 * @{
 ******************************************************************************/
	public:

		virtual bool isDeviceLinked() const					{ return (this->devState == wosh::interfaces::Device::LINKED); }
		virtual bool isDeviceUnLinked() const				{ return (this->devState == wosh::interfaces::Device::UNLINKED); }
		virtual bool isDeviceBroken() const					{ return (this->devState == wosh::interfaces::Device::BROKEN); }

		virtual wosh::interfaces::Device::DEVICE_STATE getDeviceState() const
															{ return this->devState; }

//@}
/** @name PlayerAudio Interface - Playback
 * @{
 ******************************************************************************/
	public:

		virtual WRESULT play( const std::string& file_url );

		virtual WRESULT play();

		virtual WRESULT pause();

		virtual WRESULT stop();

		virtual WRESULT first();

		virtual WRESULT next();

		virtual WRESULT prev();

		virtual WRESULT last();

//@}
/** @name PlayerAudio Interface - PlayList
 * @{
 ******************************************************************************/
	public:

		virtual WRESULT enqueue( const std::string& file_url );

		virtual WRESULT clear();

//@}
/** @name PlayerAudio Interface - Setters
 * @{
 ******************************************************************************/
	public:

		virtual WRESULT setVolume(int newVolume);

		virtual WRESULT setVolumeOffset( int volume_span );
		virtual WRESULT setMute( bool on );

		virtual WRESULT setPosition( float position_rate );
		virtual WRESULT setPositionOffset( float position_rate_offset );

//@}
/** @name PlayerAudio Interface - Getters
 * @{
 ******************************************************************************/
	public:

		virtual int getVolume();
		virtual bool isMuted();

		virtual bool isPlaying();

		virtual int getPlaylistCount();

//@}

		virtual WRESULT setDeviceOutput( const string& dev_file );

		virtual WRESULT synchWithPlayer( const string& device_player_name, int flags = 0 );// = PlayerGStreamer_SYNCH_NO_FLAGS );


/** @name Getters
 * @{
 ******************************************************************************/
	public:

		/**
		 * @brief   Get POSIX interface associated with connection
		 * @return  interface name (example: ppp0)
		 */


//@}
/** @name Player Events
 * @{
 ******************************************************************************/
 	public:

		virtual void update_play_state( PlayerGStreamer* source, int playing, int volume, bool muted );
		virtual void update_play_file( PlayerGStreamer* source, const string& file_uri, const string& length );

//@}
/** @name PropertiesProviderListener interface
 * @{
 ******************************************************************************/
 	public:
		virtual bool readingProperty( Property* property_curr, const PropertiesProvider* source );
		virtual bool updatingProperty( Property* property_new, const Property* property_old, const PropertiesProvider* source );

//@}
/** @name Thread Events
 * @{
 ******************************************************************************/
 	public:
		virtual void thread_event( Thread* player, Thread::THREAD_STATE event );

//@}
/** @name Internal methods
 * @{
 ******************************************************************************/
	protected:

		Response* mmDoList( const Request* request );

		Response* mmDoEnqueue( const Request* request );
		Response* mmDoPlay( const Request* request );

		Response* mmDoSynchWithPlayer( const Request* request );

		
		Response* mmDoSetVolume( const Request* request );
		Response* mmDoSetMute( const Request* request );

		Response* mmDoSetPosition( const Request* request );


	//	virtual WRESULT updateInfo();

		/**
		 * @brief   Raise a standard Device event (fact): Create Message and inject in BusDevices (wosh.Bus.Devices)
		 * @param fact [in] the fact (instance) to include in (event) Message, instance will be deleted by Bus
		 */
		void raiseEvent( Fact* fact );


//@}

	protected:

		BusConnector BusDevices;							///< register myself & work as Device too

		PlayerGStreamer* playerWorker;						///< real implementation

		wosh::interfaces::Device::DEVICE_STATE devState;	///< current state of device


}; // class def

 }; // namespace devices
}; // namespace wosh

#endif //__WOSH_Bundles_Devices_PlayerGStreamer_H__
