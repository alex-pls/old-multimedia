/** @file    PlayerGStreamerBundle.cpp
 *  @author  Alessandro Polo
 *  @version $Id: PlayerGStreamer010.cpp 734 2009-10-14 04:13:08Z alex $
 *  @brief
 * File containing methods for the wosh::devices::PlayerGStreamerBundle class.
 * The header for this class can be found in PlayerGStreamerBundle.h, check that file
 * for class description.
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
 
#include "PlayerGStreamer010.h"
#include "IPlayerGStreamerListener.h"

#include <core/FileSystem.h>

#include <fstream> // m3u parsing
#include <iostream> // m3u parsing
#include <algorithm> // folder parsing (sorting)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
gboolean bus_call (GstBus *bus, GstMessage *msg, gpointer data)
{
	GMainLoop *gst_loop = (GMainLoop *) data;
	(void)gst_loop; (void)bus;
	if ( msg == NULL ) return TRUE;
	
	MutexLockerRead mL(&PlayerGStreamer010::instancesMux);
	PlayerGStreamer010* instance = NULL;
	if ( PlayerGStreamer010::instances.find(gst_loop) != PlayerGStreamer010::instances.end() )
		instance = PlayerGStreamer010::instances[gst_loop];
	if ( instance == NULL ) {
		return TRUE;
	 }

	switch (GST_MESSAGE_TYPE (msg)) {

		case GST_MESSAGE_EOS: {
			instance->item_EndOfStream();
			break;
			}
		case GST_MESSAGE_BUFFERING: {
			gint percent = 0;
			gst_message_parse_buffering(msg, &percent);
			instance->item_Buffering( percent );
			break;
			}
		case GST_MESSAGE_STATE_CHANGED: {
			GstState oldState;
			GstState newState;
			GstState pending;
			gst_message_parse_state_changed(msg, &oldState, &newState, &pending);
			instance->gst_StateChanged( newState, oldState );
			break;
			}
		case GST_MESSAGE_TAG: {
			GstTagList *taglist;
			gst_message_parse_tag(msg, &taglist);

			std::map<string, string> fields;
			char* data = NULL;
			if (gst_tag_list_get_string(taglist, GST_TAG_TITLE, &data) && data)
				fields[GST_TAG_TITLE] = string(data);
			data = NULL;
			if (gst_tag_list_get_string(taglist, GST_TAG_ARTIST, &data) && data)
				fields[GST_TAG_ARTIST] = string(data);
			data = NULL;
			if (gst_tag_list_get_string(taglist, GST_TAG_ALBUM, &data) && data)
				fields[GST_TAG_ALBUM] = string(data);
			data = NULL;
		//	if (gst_tag_list_get_string(taglist, GST_TAG_GENRE, &data) && data)
		//		fields[GST_TAG_GENRE] = string(data);
		//	data = NULL;
		//	if (gst_tag_list_get_string(taglist, GST_TAG_BITRATE, &data) && data)
		//		fields[GST_TAG_BITRATE] = string(data);

			gst_tag_list_free(taglist);
			instance->item_InfoTag(fields);
			break;
			}
		case GST_MESSAGE_WARNING: {
			gchar  *debug;
			GError *error;
			gst_message_parse_warning(msg, &error, &debug);
			g_free (debug);
			instance->gst_Warning( error->message );
			g_error_free (error);
			break;
			}
		case GST_MESSAGE_ERROR: {
			gchar  *debug;
			GError *error;
			gst_message_parse_error(msg, &error, &debug);
			g_free (debug);
			instance->gst_Error( error->message );
			g_error_free (error);
			break;
			}
		default:
			break;
	 }

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
map<GMainLoop*, PlayerGStreamer010*> PlayerGStreamer010::instances;
MutexRW PlayerGStreamer010::instancesMux;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////// CONSTRUCTORS

PlayerGStreamer010::PlayerGStreamer010() : PlayerGStreamer("wosh.Device.PlayerGS.WorkerThread")
 {
	this->gst_pipeline = NULL;

	this->gst_sink_audio = NULL;
	this->gst_bin_play = NULL;

	this->gst_state = GST_STATE_NULL;

	this->playListIndex = 0;
	this->device_output = "";

	this->currentRepeat = 0;
	this->playListRepeat = 0;

	this->volume_muted = 0;

	// init only once, there may be more Players on same host
	PlayerGStreamer010::instancesMux.lockForRead();
	if ( PlayerGStreamer010::instances.size() == 0 )
		gst_init(NULL, NULL);
	PlayerGStreamer010::instancesMux.unLock();

	// register the player and its gst loop (for the callbacks)
	PlayerGStreamer010::instancesMux.lockForWrite();
	this->gst_loop = g_main_loop_new(NULL, false);
	PlayerGStreamer010::instances[this->gst_loop] = this;
	PlayerGStreamer010::instancesMux.unLock();
 }

PlayerGStreamer010::~PlayerGStreamer010()
 {
	if ( log != NULL )
		log->log( Logger::VERBOSE, ":~PlayerGStreamer010(): Destroying.." );

	this->playList.free();

	PlayerGStreamer010::instancesMux.lockForWrite();
	PlayerGStreamer010::instances[this->gst_loop] = NULL;

	map<GMainLoop*, PlayerGStreamer010*>::iterator it;
	it = PlayerGStreamer010::instances.find(this->gst_loop);
	if ( it != PlayerGStreamer010::instances.end() ) {
		PlayerGStreamer010::instances.erase (it);
	 }

	// de-init GST only when this istance is the last active
	if ( PlayerGStreamer010::instances.size() == 0 ) {
		if ( log != NULL )
			log->log( Logger::INFO, ":~PlayerGStreamer010(): De-Initializing GST.." );
		gst_deinit();
	 }
	PlayerGStreamer010::instancesMux.unLock();
 }

//////////////////////////////////////////////////////////////////////////////////////////////// CONSTRUCTORS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////// THREAD RUN

void PlayerGStreamer010::initializingThread()
 {
	if ( log != NULL )
		log->log( Logger::VERBOSE, ":runThread(): STARTING" );

	this->gst_pipeline = gst_pipeline_new("gst_pipeline");

	GstBus * bus = gst_pipeline_get_bus (GST_PIPELINE (this->gst_pipeline));
	gst_bus_add_watch (bus, bus_call, this->gst_loop);
	gst_object_unref (bus);

	this->gst_bin_play = gst_element_factory_make( "playbin", "music-player" );
	//g_object_set (G_OBJECT (this->gst_bin_play), "volume", 0.9, NULL);
	//g_object_set (G_OBJECT (this->gst_bin_play), "uri", this->file.c_str(), NULL);

	this->gst_sink_audio = gst_element_factory_make("alsasink", "sink-audio");
	if ( this->device_output != "" )
		g_object_set(G_OBJECT (this->gst_sink_audio), "device", this->device_output.c_str(), NULL);

	g_object_set(G_OBJECT (this->gst_bin_play), "audio-sink", gst_sink_audio, NULL);

	//sink_video = gst_element_factory_make ("fakesink", "sink-fake");
	//g_object_set (G_OBJECT (this->gst_bin_play), "video-sink", sink_video, NULL);

	gst_bin_add(GST_BIN (this->gst_pipeline), this->gst_bin_play);
 }


void PlayerGStreamer010::runThread()
 {
	if ( log != NULL )
		log->log( Logger::VERBOSE, ":runThread(): RUNNING" );

	if ( this->playerListener != NULL )
		this->playerListener->update_play_state( this, 0, 1, false );

	g_main_loop_run(this->gst_loop);
 }

void PlayerGStreamer010::exitingThread()
 {
	if ( log != NULL )
		log->log( Logger::VERBOSE, ":runThread(): EXITING" );

	gst_element_set_state (this->gst_pipeline, GST_STATE_NULL);
//	gst_object_unref (GST_OBJECT (this->gst_sink_audio));
//	gst_object_unref (GST_OBJECT (this->gst_bin_play));
	gst_object_unref (GST_OBJECT (this->gst_pipeline));

	this->gst_sink_audio = NULL;
	this->gst_bin_play = NULL;
	this->gst_pipeline = NULL;
 }

void PlayerGStreamer010::quitThread()
 {
	if ( log != NULL )
		log->log( Logger::VERBOSE, ":quitThread()" );

	if ( isPlaying() )
		stop();

	// exit the GST loop (GLib)
	g_main_quit(this->gst_loop);

	Thread::quitThread();
 }

////////////////////////////////////////////////////////////////////////////////////////////////// THREAD RUN
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////// GSTREAMER EVENTS

void PlayerGStreamer010::gst_StateChanged( GstState new_state, GstState old_state )
 {
	(void)old_state;
	// let's not flood the log, write only once
	if ( log != NULL && new_state != this->gst_state )
		log->log( Logger::INFO, ":gst_StateChanged() : %s => %s", PlayerGStreamer010::getGstState2String(this->gst_state).c_str(),
																		PlayerGStreamer010::getGstState2String(new_state).c_str() );

	this->gst_state = new_state;
 }

void PlayerGStreamer010::item_InfoTag( const std::map<string, string> &fields )
 {
	if ( log == NULL )
		return;

	std::map<std::string,std::string>::const_iterator it;
	for ( it=fields.begin(); it!=fields.end(); it++ ) {
		log->log( Logger::INFO, ":item_InfoTag() : '%s' = '%s'", it->first.c_str(), it->second.c_str() );
	 }
 }

void PlayerGStreamer010::item_Buffering( int percent )
 {
	if ( log != NULL )
		log->log( Logger::INFO, ":item_Buffering() : Buffering %i percent done..", percent );
 }

void PlayerGStreamer010::item_EndOfStream()
 {
	if ( this->currentRepeat ) {
		if ( log != NULL )
			log->log( Logger::INFO, ":item_EndOfStream() Repeating.." );
		MutexLockerWrite mL(&this->playList.mutex());
		if ( this->playListIndex == -1 || this->playList.size_() == 0 )
			play_( this->playList.size_() );
		return;
	 }

	MutexLockerWrite mL(&this->playList.mutex());
	if ( this->playListIndex == -1 || this->playList.size_() == 0 ) {
		if ( log != NULL )
			log->log( Logger::INFO, ":item_EndOfStream()" );
		return;
	 }
	else if ( this->playListIndex == (int)this->playList.size_() -1 ) {
		if ( log != NULL )
			log->log( Logger::INFO, ":item_EndOfStream() : End of Playlist" );
		if ( this->playListRepeat == 0 )
			return;
		play_(0);
		return;
	 }
	if ( log != NULL )
		log->log( Logger::INFO, ":item_EndOfStream(%i) Playing next Item [of %i]", this->playListIndex, this->playList.size_() );

	play_( this->playListIndex + 1 );
	return;
 }

void PlayerGStreamer010::gst_Warning( const char* message )
 {
	if ( log == NULL ) return;
	if ( message != NULL )
		log->log( Logger::WARNING, ":gst_Warning() : %s", message );
	else
		log->log( Logger::WARNING, ":gst_Warning() : NULL" );
 }

void PlayerGStreamer010::gst_Error( const char* message )
 {
	if ( log != NULL ) {
		if ( message != NULL )
			log->log( Logger::CRITICAL, ":gst_Error() : %s", message );
		else
			log->log( Logger::CRITICAL, ":gst_Error() : NULL" );
	 }
	this->quitThread();
 }

//////////////////////////////////////////////////////////////////////////////////////////// GSTREAMER EVENTS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////// INTERNAL ENQUEUE/PLAY

int PlayerGStreamer010::enqueue_( const std::string& file_url )
 {
	// fix the url
	// parse it {may be invalid, folder, .m3u playlist}
	// enqueque item(s)
	// return playindex of first item or (-)ERROR#

	if ( file_url.size() < 3 ) {
		if ( log != NULL )
			log->log( Logger::CRITICAL, ":enqueue_(%s) : INVALID File!", file_url.c_str() );
		return -1;
	 }

	if ( log != NULL )
		log->log( Logger::VERBOSE, ":enqueue_(%s) : Parsing..", file_url.c_str() );

	string url = file_url;
	size_t psf = url.find( "://" ); //protocol separator (file://path/to/resource; dvd://1)
	if ( psf == string::npos )
		url = "file://" + url;

	int element_index = 0;
	if ( this->playList.size_() > 0 )
		element_index = this->playList.size_() - 1;

	if ( url.find("file://") == 0 && FileSystem::isFolder(url.substr(7)) ) {
		// inline creation of playlist, not recursive
		vector<string> files;
		FileSystem::fixPath(url);

		WRESULT ret = FileSystem::getFilesOf(url.substr(7), files, false );
		if ( WFAILED(ret) || files.size() == 0 ) {
			if ( log != NULL )
				log->log( Logger::CRITICAL, ":enqueue_(%s): INVALID Folder [%i files]", url.c_str(), files.size() );
			return -2;
		 }
		if ( log != NULL )
			log->log( Logger::VERBOSE, ":enqueue_(%s): Analysing %i elements from folder", url.c_str(), files.size() );

		std::sort( files.begin(), files.end() );
		//Utilities::sortVector(files);

		std::vector<string>::const_iterator it;
		for ( it=files.begin(); it!=files.end(); it++ ) {
			enqueue_( FileSystem::combinePaths(url.substr(7), *it) ); // recusive
		 }

		return element_index;
	 }
	else if ( url.find("file://") == 0 && FileSystem::isFile(url.substr(7)) && FileSystem::getExtensionOf(url) == "m3u" ) {

		ifstream infile;
		infile.open( url.substr(7).c_str(), ifstream::in );

		if ( !infile.is_open() ) {
			if ( log != NULL )
				log->log( Logger::CRITICAL, ":enqueue_(%s) : Invalid filename (can't open)", url.substr(7).c_str() );
			return WRET_ERR_PARAM;
		 }

		if ( log != NULL )
			log->log( Logger::VERBOSE, ":enqueue_(%s): Loading Playlist..", url.c_str() );
 
		string base_dir;
		FileSystem::getFolderOf( url, base_dir );
		string buffer;
		size_t cPos;
		long found = 0;

		while ( infile.good() ) {
			if ( infile.eof() ) break;
			getline( infile, buffer);
			cPos = buffer.find("#");
			if ( cPos != string::npos )
				continue;
			if ( buffer.size() < 3 )
				continue;

			buffer.erase(buffer.size()-1); // remove endline
			enqueue_( FileSystem::combinePaths( base_dir, buffer ) );
			++found;
		 }

		if ( log != NULL )
			log->log( Logger::INFO, ":enqueue_(%s) : Loaded %i files", url.c_str(), found );

		infile.close();

		return element_index;
	 }
	else { // normal file/url
		PlayerItem* item = new PlayerItem(file_url);

		size_t psf = item->file_url.find( "://" ); //protocol separator (file://path/to/resource; dvd://1)
		if ( psf == string::npos )
			item->file_url = "file://" + item->file_url;

		this->playList.add_(item);

		if ( log != NULL )
			log->log( Logger::INFO, ":enqueue_(%s) : Enqueued #%i", url.c_str(), this->playList.size_()-1 );

		return this->playList.size_()-1;
	 }

	return -10;
 }

WRESULT PlayerGStreamer010::play_( unsigned int index )
 {
	if ( this->playList.size_() == 0 ) return WRET_ERR_ILLEGAL_USE;
	if ( index >= this->playList.size_() ) return WRET_ERR_PARAM;

	this->playListIndex = index;
	PlayerItem* item = this->playList.item_(this->playListIndex);
	if ( item == NULL ) {
		return WRET_ERR_INTERNAL;
	 }
	return play_( item->file_url );
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

WRESULT PlayerGStreamer010::play_( const std::string& file_url )
 {
	if ( this->gst_bin_play == NULL ) {
		if ( log != NULL )
			log->log( Logger::CRITICAL, ":play_(): NULL gst_bin_play" );
		return WRET_ERR_ILLEGAL_USE;
	 }
	if ( this->gst_pipeline == NULL ) {
		if ( log != NULL )
			log->log( Logger::CRITICAL, ":play_(): NULL gst_pipeline" );
		return WRET_ERR_ILLEGAL_USE;
	 }

	if ( isPlaying() ) {
		stop();
	//	gst_element_seek(	this->gst_pipeline, 1.0, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH,
	//						GST_SEEK_TYPE_SET, 0,
	//						GST_SEEK_TYPE_NONE, GST_CLOCK_TIME_NONE);
	 }

	if ( file_url.empty() ) {

		gst_element_set_state(this->gst_pipeline, GST_STATE_PLAYING );

		if ( this->playerListener != NULL )
			this->playerListener->update_play_state( this, 1, getVolume(), isMuted() );

		return WRET_OK;
		//return WRET_ERR_PARAM;
	 }

	g_object_set (G_OBJECT (this->gst_bin_play), "uri", file_url.c_str(), NULL);

	if ( log != NULL )
		log->log( Logger::INFO, ":play_(%s): Playing..", file_url.c_str() );

	if ( this->playerListener != NULL ) {
		gint64 len = 1;
		GstFormat fmt = GST_FORMAT_TIME;
		if ( gst_element_query_duration( this->gst_pipeline, &fmt, &len) ) {
			char duration[256];
			memset(duration, 0, 256);
			sprintf(duration, "%" GST_TIME_FORMAT, GST_TIME_ARGS (len));
			this->playerListener->update_play_file( this, file_url, string(duration) );
		 }
		else
			this->playerListener->update_play_file( this, file_url, "" );
	 }

	gst_element_set_state(this->gst_pipeline, GST_STATE_PLAYING );

	if ( this->playerListener != NULL )
		this->playerListener->update_play_state( this, 1, getVolume(), isMuted() );

	return WRET_OK;

 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

WRESULT PlayerGStreamer010::play( const std::string& file_url )
 {
	MutexLockerWrite mL(&this->playList.mutex());
	int index = enqueue_(file_url);
	if ( index < 0 ) {
		if ( log != NULL )
			log->log( Logger::CRITICAL, ":play(%s): Invalid Item", file_url.c_str() );
		return WRET_ERR_PARAM;
	 }
	return play_(index);
 }

/////////////////////////////////////////////////////////////////////////////////////// INTERNAL ENQUEUE/PLAY
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////// PLAYER METHODS

WRESULT PlayerGStreamer010::enqueue( const std::string& file_url )
 {
	MutexLockerWrite mL(&this->playList.mutex());
	int index = enqueue_(file_url);
	if ( index < 0 )
		return WRET_ERR_INTERNAL;
	return WRET_OK;
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

WRESULT PlayerGStreamer010::clear()
 {
	MutexLockerWrite mL(&this->playList.mutex());

	if ( isPlaying() ) {
		if ( log != NULL )
			log->log( Logger::VERBOSE, ":clear() Stopped." );
		stop();
	 }

	this->playListIndex = -1;
	this->playList.free_();

	if ( log != NULL )
		log->log( Logger::INFO, ":clear() Playlist cleaned." );

	return WRET_OK;
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

WRESULT PlayerGStreamer010::first() {
	MutexLockerWrite mL(&this->playList.mutex());
	return play_( 0 );
 }

WRESULT PlayerGStreamer010::last() {
	MutexLockerWrite mL(&this->playList.mutex());
	return play_( this->playList.size_() - 1 );
 }

WRESULT PlayerGStreamer010::prev() {
	MutexLockerWrite mL(&this->playList.mutex());
	if ( this->playListIndex < 1 )
		return WRET_ERR_ILLEGAL_USE;
	return play_( this->playListIndex - 1 );
 }

WRESULT PlayerGStreamer010::next() {
	MutexLockerWrite mL(&this->playList.mutex());
	return play_( this->playListIndex + 1 );
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

WRESULT PlayerGStreamer010::play( unsigned int index )
 {
	MutexLockerWrite mL(&this->playList.mutex());
	return play_( index );
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

WRESULT PlayerGStreamer010::pause()
 {
	if ( this->gst_pipeline == NULL ) {
		if ( log != NULL )
			log->log( Logger::CRITICAL, ":pause(): NULL gst_pipeline" );
		return WRET_ERR_ILLEGAL_USE;
	 }
	if ( !isPlaying() ) {
		if ( log != NULL )
			log->log( Logger::CRITICAL, ":pause(): NOT playing" );
		return WRET_ERR_ILLEGAL_USE;
	 }

	if ( log != NULL )
		log->log( Logger::VERBOSE, ":pause(): setting PAUSED state.." );

	gst_element_set_state(this->gst_pipeline, GST_STATE_PAUSED );

	if ( this->playerListener != NULL )
		this->playerListener->update_play_state( this, 2, getVolume(), isMuted() );

	return WRET_OK;
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

WRESULT PlayerGStreamer010::stop()
 {
	if ( this->gst_pipeline == NULL ) {
		if ( log != NULL )
			log->log( Logger::CRITICAL, ":stop(): NULL gst_pipeline" );
		return WRET_ERR_ILLEGAL_USE;
	 }

	if ( isPlaying() ) {
		if ( log != NULL )
			log->log( Logger::INFO, ":stop(): setting PAUSED state.." );
		gst_element_set_state(this->gst_pipeline, GST_STATE_PAUSED );
	 }
	else if ( log != NULL )
		log->log( Logger::WARNING, ":stop(): NOT playing" );

	gst_element_set_state(this->gst_pipeline, GST_STATE_NULL );

	if ( this->playerListener != NULL )
		this->playerListener->update_play_state( this, 0, getVolume(), isMuted() );

	return WRET_OK;
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool PlayerGStreamer010::isPlaying()
 {
	GstState state;
	GstStateChangeReturn ret = gst_element_get_state(this->gst_pipeline, &state, NULL, GST_CLOCK_TIME_NONE);
	if ( ret == GST_STATE_CHANGE_FAILURE )
		return false;
	return (state == GST_STATE_PLAYING);
 }

////////////////////////////////////////////////////////////////////////////////////////////// PLAYER METHODS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////// VOLUME CONTROL

WRESULT PlayerGStreamer010::setVolume( int newVolume )
 {
	if ( this->gst_bin_play == NULL ) {
		if ( log != NULL )
			log->log( Logger::CRITICAL, ":setVolume(): NULL gst_bin_play" );
		return WRET_ERR_ILLEGAL_USE;
	 }

	if ( log != NULL )
		log->log( Logger::VERBOSE, ":setVolume(): %i (/100)", newVolume );

	gdouble vol = newVolume / 10.0;
	g_object_set (G_OBJECT (this->gst_bin_play), "volume", vol, NULL);

//Properties deadlock	if ( this->playerListener != NULL )
//		this->playerListener->update_play_state( this, isPlaying(), getVolume(), isMuted() );

	return WRET_OK;
 }

WRESULT PlayerGStreamer010::setVolumeOffset( int volume_span )
 {
	if ( this->gst_bin_play == NULL ) {
		if ( log != NULL )
			log->log( Logger::CRITICAL, ":setVolumeOffset(): NULL gst_bin_play" );
		return WRET_ERR_ILLEGAL_USE;
	 }

	if ( log != NULL )
		log->log( Logger::VERBOSE, ":setVolumeOffset(): %i (/100)", volume_span );

	gdouble vol = -1;
	g_object_get (G_OBJECT (this->gst_bin_play), "volume", &vol, NULL);
	if ( vol == -1 ) {
		return WRET_ERR_INTERNAL;
	 }

	vol += volume_span / 10.0;
	if ( vol < 0 )			vol = 0;
	else if ( vol > 10.0 )	vol = 10.0;

	g_object_set (G_OBJECT (this->gst_bin_play), "volume", vol, NULL);

//Properties deadlock	if ( this->playerListener != NULL )
//		this->playerListener->update_play_state( this, isPlaying(), getVolume(), isMuted() );

	return WRET_OK;
 }

WRESULT PlayerGStreamer010::setMute( bool on )
 {
	if ( this->gst_bin_play == NULL ) {
		if ( log != NULL )
			log->log( Logger::CRITICAL, ":setMute(): NULL gst_bin_play" );
		return WRET_ERR_ILLEGAL_USE;
	 }

	if ( log != NULL )
		log->log( Logger::VERBOSE, ":setMute(): %i", (int)on );

	if ( on ) {
		this->volume_muted = getVolume();
		gdouble vol = 0.0;
		g_object_set (G_OBJECT (this->gst_bin_play), "volume", vol, NULL);
	 }
	else {
		WRESULT ret = setVolume(this->volume_muted);
		this->volume_muted = 0;
		return ret;
	 }

	return WRET_OK;
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int PlayerGStreamer010::getVolume()
 {
	if ( this->gst_bin_play == NULL ) {
		if ( log != NULL )
			log->log( Logger::CRITICAL, ":getVolume(): NULL gst_bin_play" );
		return -1;
	 }

	gdouble vol = -1;
	g_object_get (G_OBJECT (this->gst_bin_play), "volume", &vol, NULL);
	if ( vol != -1 )
		return (int)(vol * 10.0);
	return -1;
 }

bool PlayerGStreamer010::isMuted()
 {
	return (this->volume_muted != 0);
 }

////////////////////////////////////////////////////////////////////////////////////////////// VOLUME CONTROL
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////// POSITION CONTROL

WRESULT PlayerGStreamer010::setPosition( float position_rate )
 {
	if ( this->gst_pipeline == NULL ) {
		if ( log != NULL )
			log->log( Logger::CRITICAL, ":setPosition(): NULL gst_pipeline" );
		return -1;
	 }
	gint64 len = 1;
	gint64 time_nanoseconds = 1000;
	GstFormat fmt = GST_FORMAT_TIME;
	if ( !gst_element_query_duration( this->gst_pipeline, &fmt, &len) ) {
		if ( log != NULL )
			log->log( Logger::CRITICAL, ":setPosition(%f): FAILED Seeking", position_rate );
		return WRET_ERR_ILLEGAL_USE;
	 }
	time_nanoseconds = position_rate * len;
	if ( !gst_element_seek(	this->gst_pipeline, 1.0, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH,
							GST_SEEK_TYPE_SET, time_nanoseconds,
							GST_SEEK_TYPE_NONE, GST_CLOCK_TIME_NONE) ) {
		if ( log != NULL )
			log->log( Logger::VERBOSE, ":setPosition(%f): FAILED Seeking", position_rate );
		return WRET_ERR_ILLEGAL_USE;
	 }
	if ( log != NULL )
		log->log( Logger::INFO, ":setPosition(%f): Seek %i ms", position_rate, time_nanoseconds );

	return WRET_OK;
 }

WRESULT PlayerGStreamer010::setPositionOffset( float position_rate_offset )
 {
	if ( this->gst_pipeline == NULL ) {
		if ( log != NULL )
			log->log( Logger::CRITICAL, ":setPositionOffset(): NULL gst_pipeline" );
		return -1;
	 }
	gint64 pos = 0;
	gint64 len = 1;
	gint64 time_nanoseconds = 1000;
	GstFormat fmt = GST_FORMAT_TIME;
	if ( !gst_element_query_duration( this->gst_pipeline, &fmt, &len ) ) {
		if ( log != NULL )
			log->log( Logger::CRITICAL, ":setPositionOffset(%f): FAILED Seeking", position_rate_offset );
		return WRET_ERR_ILLEGAL_USE;
	 }
	if ( !gst_element_query_position( this->gst_pipeline, &fmt, &pos ) ) {
		if ( log != NULL )
			log->log( Logger::CRITICAL, ":setPositionOffset(%f): FAILED Seeking", position_rate_offset );
		return WRET_ERR_ILLEGAL_USE;
	 }

	time_nanoseconds = pos + position_rate_offset * len;
	if ( !gst_element_seek(	this->gst_pipeline, 1.0, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH,
							GST_SEEK_TYPE_SET, time_nanoseconds,
							GST_SEEK_TYPE_NONE, GST_CLOCK_TIME_NONE ) ) {
		if ( log != NULL )
			log->log( Logger::CRITICAL, ":setPositionOffset(%f): FAILED Seeking", position_rate_offset );
		return WRET_ERR_ILLEGAL_USE;
	 }
	if ( log != NULL )
		log->log( Logger::INFO, ":setPositionOffset(%f): Seek %i ms", position_rate_offset, time_nanoseconds );

	return WRET_OK;
 }

WRESULT PlayerGStreamer010::setPositionMs( unsigned long position_ms )
 {
	if ( this->gst_pipeline == NULL ) {
		if ( log != NULL )
			log->log( Logger::CRITICAL, ":setPositionMs(): NULL gst_pipeline" );
		return -1;
	 }
	gint64 time_nanoseconds = position_ms * GST_MSECOND;
	if ( !gst_element_seek_simple( this->gst_pipeline, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH, time_nanoseconds) ) {
		if ( log != NULL )
			log->log( Logger::VERBOSE, ":setPositionMs(%i): FAILED Seeking", position_ms );
		return WRET_ERR_INTERNAL;
	 }
	if ( log != NULL )
		log->log( Logger::INFO, ":setPositionMs(): Seek %i ms", position_ms );

	return WRET_OK;
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

float PlayerGStreamer010::getPosition()
 {
	if ( this->gst_pipeline == NULL ) {
		if ( log != NULL )
			log->log( Logger::CRITICAL, ":getPosition(): NULL gst_pipeline" );
		return -1;
	 }
	gint64 pos = 0;
	gint64 len = 1;
	float pos_rel = 0.0;

	GstFormat fmt = GST_FORMAT_TIME;
	if ( gst_element_query_position( this->gst_pipeline, &fmt, &pos)
			&& gst_element_query_duration( this->gst_pipeline, &fmt, &len) ) {
		//g_print ("Time: %" GST_TIME_FORMAT " / %" GST_TIME_FORMAT "\r",
		//GST_TIME_ARGS (pos), GST_TIME_ARGS (len));
		pos_rel = pos / (float)len;
		return pos_rel;
	 }
	return -2;
 }

unsigned long PlayerGStreamer010::getPositionMs()
 {
	if ( this->gst_pipeline == NULL ) {
		if ( log != NULL )
			log->log( Logger::CRITICAL, ":getPositionMs(): NULL gst_pipeline" );
		return 0;
	 }

	gint64 pos = 0;
	GstFormat fmt = GST_FORMAT_TIME;
	if ( gst_element_query_position( this->gst_pipeline, &fmt, &pos) ) {
		return (unsigned long)(pos/GST_MSECOND);
	 }
	return 0;
 }

//////////////////////////////////////////////////////////////////////////////////////////// POSITION CONTROL
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

WRESULT PlayerGStreamer010::setDeviceOutput( const string& dev_file )
 {
	this->device_output = dev_file;

	if ( !this->running ) {
		if ( log != NULL )
			log->log( Logger::INFO, ":setDeviceOutput(%s) [really applied when started]", this->device_output.c_str() );
		return WRET_OK;
	 }

	if ( this->gst_sink_audio == NULL ) {
		if ( log != NULL )
			log->log( Logger::WARNING, ":setDeviceOutput(%s): NULL gst_sink_audio [but Player running!?]", this->device_output.c_str() );
		return WRET_ERR_INTERNAL;
	 }

	if ( isPlaying() ) {
		if ( log != NULL )
			log->log( Logger::WARNING, ":setDeviceOutput(%s) : Set while playing.. Stopping..", this->device_output.c_str() );
		WRESULT ret = stop();
		if ( WFAILED(ret) ) {
			if ( log != NULL )
				log->log( Logger::CRITICAL, ":setDeviceOutput(%s) : ERROR#%i while stopping playback!", this->device_output.c_str(), ret );
			return WRET_ERR_ILLEGAL_USE;
		 }
	 }
	else if ( log != NULL )
		log->log( Logger::INFO, ":setDeviceOutput(%s) : Set while running.. trying to apply", this->device_output.c_str() );

	g_object_set(G_OBJECT (this->gst_sink_audio), "device", this->device_output.c_str(), NULL);

	return WRET_OK;
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

WRESULT PlayerGStreamer010::getAPIInfo( std::map<std::string, std::string>& fields )
 {
	guint major, minor, micro, nano;
	gst_version (&major, &minor, &micro, &nano);

	fields["GS_Version"] = Utilities::convertInteger2String(major) + "." + Utilities::convertInteger2String(minor) + "." + Utilities::convertInteger2String(micro);

	if (nano == 1)
		fields["GS_Built"] = "(CVS)";
	else if (nano == 2)
		fields["GS_Built"] = "(Prerelease)";
	else
		fields["GS_Built"] = "[unknown]";

	return WRET_OK;
 }

////////////////////////////////////////////////////////////////////////////////////////////// PLAYER METHODS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////// STATIC METHODS

string PlayerGStreamer010::getGstState2String( GstState state )
 {
	switch(state) {
		case GST_STATE_VOID_PENDING:	return "PENDING";
		case GST_STATE_NULL:			return "NULL";
		case GST_STATE_READY:			return "READY";
		case GST_STATE_PAUSED:			return "PAUSED";
		case GST_STATE_PLAYING:			return "PLAYING";
		default:						return "UNKNOWN";
	 }
 }

////////////////////////////////////////////////////////////////////////////////////////////// STATIC METHODS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
