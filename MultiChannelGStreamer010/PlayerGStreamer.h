/**
 * @class   PlayerGStreamer
 * @brief   Interface for PlayerGStreamer implementations.
 *
 * @see     IPlayerGStreamerListener
 ****************************************************************************
 * @version $Id: PlayerGStreamer.h 581 2009-09-28 10:58:28Z alex $
 * @author  Alessandro Polo
 * @date    Released on 2009-09-28
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

#ifndef __WOSH_DEVICES_PlayerGStreamer_H__
 #define __WOSH_DEVICES_PlayerGStreamer_H__

 #include <woshDefs.h>
 #include <core/List.h>
 #include <core/ThreadWorker.h>

 
using namespace std;
using namespace wosh;


class PlayerItem {
	public:

		PlayerItem( const std::string& url = "" ) {
			this->file_url = url;
			this->duration = 0.0;
		 }

		virtual ~PlayerItem() { }

	public:
		string file_url;
		float duration;

};

class IPlayerGStreamerListener;

class PlayerGStreamer : public ThreadWorker  {

	public:

		virtual WRESULT play() = 0;
		virtual WRESULT play( unsigned int index ) = 0;
		virtual WRESULT play( const std::string& file_url ) = 0;
		virtual WRESULT stop() = 0;

		virtual WRESULT enqueue( const std::string& file_url ) = 0;

		virtual WRESULT pause() = 0;

		virtual WRESULT first() = 0;
		virtual WRESULT next() = 0;
		virtual WRESULT prev() = 0;
		virtual WRESULT last() = 0;



		virtual WRESULT clear() = 0;

		virtual List<PlayerItem*>& getPlayList() = 0;

		virtual int getPlayListIndex() const = 0;


		virtual WRESULT setVolumeOffset( int volume_span ) = 0;
		virtual WRESULT setVolume( int newVolume ) = 0;
		virtual WRESULT setMute( bool on ) = 0;

		virtual WRESULT setPosition( float position_rate ) = 0;
		virtual WRESULT setPositionOffset( float position_rate_offset ) = 0;

		virtual WRESULT setPositionMs( unsigned long position_rate ) = 0;

		virtual float getPosition() = 0;
		virtual unsigned long getPositionMs() = 0;

		virtual WRESULT setDeviceOutput( const string& dev_file ) = 0;

		virtual int getVolume() = 0;
		virtual bool isPlaying() = 0;
		virtual bool isMuted() = 0;


		virtual WRESULT getAPIInfo( std::map<std::string, std::string>& fields ) = 0;

	public:

		PlayerGStreamer() : ThreadWorker("wosh.Device.PlayerGStreamer.worker#") {
			this->playerListener = NULL;
		 }

		PlayerGStreamer( const string& name ) : ThreadWorker(name) {
			this->playerListener = NULL;
		 }

		virtual ~PlayerGStreamer() { }

		virtual void setPlayerListener( IPlayerGStreamerListener* Listener ) {
			this->playerListener = Listener;
		 }

	protected:

		IPlayerGStreamerListener* playerListener;

}; // class def


#endif //__WOSH_DEVICES_PlayerGStreamer_H__
