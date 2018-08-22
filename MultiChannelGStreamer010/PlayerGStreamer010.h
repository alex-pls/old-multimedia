/**
 * @class   PlayerGStreamer010
 * @brief   
 *
 *
 *
 *
 * @see     PlayerGStreamer
 * @ingroup Devices
 ****************************************************************************
 * @version $Id: PlayerGStreamer010.h 694 2009-10-08 14:26:06Z alex $
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

#ifndef __WOSH_DEVICES_PlayerGStreamer010_H__
 #define __WOSH_DEVICES_PlayerGStreamer010_H__

 #include <woshDefs.h>
 #include <map>

 #include "PlayerGStreamer.h"
 #include <gst/gst.h>


using namespace std;
using namespace wosh;


class PlayerGStreamer010 : public PlayerGStreamer  {

	public:

		/**
		 * @brief   Default constructor. Init vars and GLib main gst_loop, associating
		 *          it to current instance (this).
		 * @see     PlayerGStreamer010::instances
		 */
		PlayerGStreamer010();

		/**
		 * @brief   Deconstructor. If playing or idle (thread is stll running), it will be stopped.
		 */
		virtual ~PlayerGStreamer010();


	public:

		virtual WRESULT play( unsigned int index );

		virtual WRESULT play()				{ return play(""); }


		/**
		 * @brief   Play a resource
		 * @param stream_uri [in] the URI of the resource to be played. Multiple protocols are supported:
		 *                         - filesystem [file:///path/to/somefile.avi] (default: '/path/to/somefile.avi' will work too) 
		 *                           Also folders are supported, but it will clear the playlist and enqueue files, not recursive.
		 *                         - Network stream, HTTP [http://www.alessandropolo.name/music/sounday/Longe-at-the-Counter.mp3]
		 *                         - Compact Disc Digital Audio [cdda://4]
		 *                         - DVD [dvd://1]
		 */
		virtual WRESULT play( const std::string& stream_uri );

		virtual WRESULT enqueue( const std::string& stream_uri );

		virtual WRESULT pause();
		virtual WRESULT stop();

		virtual WRESULT first();
		virtual WRESULT next();
		virtual WRESULT prev();
		virtual WRESULT last();

		virtual WRESULT clear();

		virtual WRESULT setVolume( int newVolume );
		virtual WRESULT setVolumeOffset( int volume_span );

		virtual WRESULT setMute( bool on );


		WRESULT setDeviceOutput( const string& dev_file );

		virtual WRESULT setPosition( float position_rate );
		virtual WRESULT setPositionOffset( float position_rate_offset );

		virtual WRESULT setPositionMs( unsigned long position_rate );

		virtual float getPosition();
		virtual unsigned long getPositionMs();

		virtual int getVolume();
		virtual bool isMuted();

		virtual bool isPlaying();


		virtual int getPlayListIndex() const		{ return this->playListIndex; }

		virtual WRESULT getAPIInfo( std::map<std::string, std::string>& fields );

		virtual List<PlayerItem*>& getPlayList()	{ return this->playList; }


	protected:

		WRESULT play_( const std::string& file_url );
		WRESULT play_( unsigned int index );
		WRESULT enqueue_( const std::string& file_url );

		WRESULT enqueueFromPlayList_( const std::string& m3u_url );

		virtual void item_Buffering( int percent );
		virtual void item_EndOfStream();
		virtual void item_InfoTag( const std::map<string, string> &fields );

		virtual void gst_StateChanged( GstState new_state, GstState old_state );

		virtual void gst_Error( const char* message );
		virtual void gst_Warning( const char* message );


		virtual void initializingThread();
		virtual void runThread();
		virtual void exitingThread();

		// overload
		virtual void quitThread();

		static string getGstState2String( GstState state );


	private:

		GMainLoop *gst_loop;			///< GLib loop pointer
		GstElement *gst_pipeline;		///< GStreamer pipeline pointer

		GstElement *gst_sink_audio;		///< pointer to the GStreamer Audio Sink
		GstElement *gst_bin_play;		///< pointer to the GStreamer BIN play

		GstState gst_state;				///< (last) gstreamer pipeline state 

		string device_output;			///< ALSA device name (default; ..)

		List<PlayerItem*> playList;		///< elements of the playlist
		int playListIndex;				///< current (playing item) index of the playlist

		short currentRepeat;			///< flag: repeat current item forever
		short playListRepeat;			///< flag: repeat whole playlist forever

		int volume_muted;				///< cache of last volume while muted, 0 when not muted

		static map<GMainLoop*, PlayerGStreamer010*> instances;	///< global collection of instances
		static MutexRW instancesMux;							///< mutex of global instances-collection

		friend gboolean bus_call (GstBus *bus, GstMessage *msg, gpointer data);

}; // class def


#endif //__WOSH_DEVICES_PlayerGStreamer010_H__
