/**
 * @class   wosh::devices::VlcPlayer
 * @brief   Interface for VlcPlayer callbacks (events).
 *
 * @see     wosh::devices::VlcPlayer
 ****************************************************************************
 * @version $Id: VlcPlayer.h 435 2009-08-21 02:15:11Z alex $
 * @author Alessandro Polo
 * @date   Released on 2009-06-04
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

#ifndef __WOSH_DEVICES_VlcPlayer_H__
 #define __WOSH_DEVICES_VlcPlayer_H__

 #include <woshDefs.h>

using namespace std;
namespace wosh {
 namespace devices {


class VlcPlayer  {
	public:

		//the file has to be in one of the following formats /perhaps a little bit outdated)
		/*
		[file://]filename              Plain media file
		http://ip:port/file            HTTP URL
		ftp://ip:port/file             FTP URL
		mms://ip:port/file             MMS URL
		screen://                      Screen capture
		[dvd://][device][@raw_device]  DVD device
		[vcd://][device]               VCD device
		[cdda://][device]              Audio CD device
		udp:[[<source address>]@[<bind address>][:<bind port>]]
		*/
		virtual WRESULT play( const std::string& file_url ) = 0;
		virtual WRESULT enqueue( const std::string& file_url ) = 0;

		virtual WRESULT pause() = 0;
		virtual WRESULT stop() = 0;

		virtual WRESULT next() = 0;
		virtual WRESULT prev() = 0;

		virtual WRESULT clear() = 0;

		
		virtual WRESULT setFullScreen( bool on ) = 0;
		virtual WRESULT setVideoResize( int width, int height ) = 0;

		virtual WRESULT getSnapshot( const string& output_file ) = 0;

		virtual WRESULT setVolumeOffset( int volume_span ) = 0;
		virtual WRESULT setVolume( int newVolume ) = 0;
		virtual WRESULT setMute( bool on ) = 0;

		virtual WRESULT setPosition( float position_rate ) = 0;
		virtual WRESULT setPositionOffset( float position_rate_offset ) = 0;



		virtual int getVolume() = 0;
		virtual bool isPlaying() = 0;
		virtual bool isMuted() = 0;
		virtual int getPlaylistCount() = 0;


		virtual WRESULT updateInfo() = 0;
		virtual WRESULT getVLC_Info( std::map<std::string, std::string>& fields ) = 0;
		

		virtual WRESULT setVlcArguments( const string& arguments_line ) = 0;

	public:
		virtual ~VlcPlayer() { }

}; // class def

 }; // namespace services
}; // namespace wosh

#endif //__WOSH_DEVICES_VlcPlayer_H__
