/** @file    VlcPlayer086c.cpp
 *  @author  Alessandro Polo
 *  @version $Id: VlcPlayer086c.cpp 435 2009-08-21 02:15:11Z alex $
 *  @brief
 * File containing methods for the wosh::devices::VlcPlayer086c class.
 * The header for this class can be found in VlcPlayer086c.h, check that file
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

 #include "VlcPlayer086c.h"
 #include <core/Logger.h>


namespace wosh {
 namespace devices {

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////// CONSTRUCTORS

VlcPlayer086c::VlcPlayer086c() : ThreadWorker("wosh.Device.VlcPlayer086c.WorkerThread")
 {
	this->vlc_argv = NULL;
	this->vlc_argc = 0;

	this->playerListener = NULL;
 }

VlcPlayer086c::~VlcPlayer086c()
 {
	if ( log != NULL )
		log->log( Logger::VERBOSE, ":~VlcPlayer086c(): Destroying.." );

	if ( isThreadRunning() ) {
		quitThread();
	 }

 }

//////////////////////////////////////////////////////////////////////////////////////////////// CONSTRUCTORS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////// THREAD RUN

void VlcPlayer086c::runThread()
 {
	this->running = true;

	if ( log != NULL )
		log->log( Logger::VERBOSE, ":runThread() : Creating libVLC Instance.." );

	libvlc_exception_init(&_vlcexcep);
	_vlcinstance = libvlc_new(vlc_argc, vlc_argv, &_vlcexcep);
	raise(&_vlcexcep);

//	 media = libvlc_media_new(inst, filename, &excp);

	//qDebug()<<"Exception VLC init "<<libvlc_exception_get_message(&_vlcexcep);

/*
	if ( log != NULL )
		log->log( Logger::VERBOSE, ":runThread() : ADDING to playlist.." );

	int item = libvlc_playlist_add(_vlcinstance, "./sample.mp3", NULL, &_vlcexcep); 
	raise(&_vlcexcep);

	if ( log != NULL )
		log->log( Logger::VERBOSE, ":runThread() : PLAYING to playlist.." );

	libvlc_playlist_play(_vlcinstance, item, 0, NULL, &_vlcexcep); 
	raise(&_vlcexcep);

	if ( log != NULL )
		log->log( Logger::VERBOSE, ":runThread() : Entering Loop.." );
*/
	while(this->running) {
		Thread::sleepForSec(1);
	 }

	// Stop playing

	if ( log != NULL )
		log->log( Logger::VERBOSE, ":runThread() : Destroying libVLC instance.." );

	// Free the media_player
	if ( _vlcinstance != NULL ) {
		libvlc_destroy(_vlcinstance);
	 }

 }

////////////////////////////////////////////////////////////////////////////////////////////////// THREAD RUN
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

WRESULT VlcPlayer086c::play( const std::string& file_url )
 {
	if ( log != NULL )
		log->log( Logger::INFO, ":play() : Playing %s", file_url.c_str() );

	int item = libvlc_playlist_add(_vlcinstance, file_url.c_str(), NULL, &_vlcexcep); 
	raise(&_vlcexcep);

	libvlc_playlist_play(_vlcinstance, item, 0, NULL, &_vlcexcep); 
	raise(&_vlcexcep);


	_isPlaying=true;

	return WRET_OK;
 }

WRESULT VlcPlayer086c::enqueue( const std::string& file_url )
 {
	if ( log != NULL )
		log->log( Logger::INFO, ":enqueue() : Enqueueing %s", file_url.c_str() );

	int item = libvlc_playlist_add(_vlcinstance, file_url.c_str(), NULL, &_vlcexcep); 
	raise(&_vlcexcep);

	return WRET_OK;
 }

WRESULT VlcPlayer086c::pause()
 {
	if ( log != NULL )
		log->log( Logger::INFO, ":pause()" );

	libvlc_playlist_pause(_vlcinstance, &_vlcexcep); 
	raise(&_vlcexcep);

	return WRET_OK;
 }

WRESULT VlcPlayer086c::stop()
 {
	if ( log != NULL )
		log->log( Logger::INFO, ":stop()" );

	libvlc_playlist_stop(_vlcinstance, &_vlcexcep); 
	raise(&_vlcexcep);

	return WRET_OK;
 }

WRESULT VlcPlayer086c::next()
 {
	if ( log != NULL )
		log->log( Logger::INFO, ":next()" );

	libvlc_playlist_next(_vlcinstance, &_vlcexcep); 
	raise(&_vlcexcep);

	return WRET_OK;
 }

WRESULT VlcPlayer086c::prev()
 {
	if ( log != NULL )
		log->log( Logger::INFO, ":prev()" );

	libvlc_playlist_prev(_vlcinstance, &_vlcexcep); 
	raise(&_vlcexcep);

	return WRET_OK;
 }

WRESULT VlcPlayer086c::clear()
 {
	if ( log != NULL )
		log->log( Logger::INFO, ":clear()" );

	libvlc_playlist_clear(_vlcinstance, &_vlcexcep); 
	raise(&_vlcexcep);

	return WRET_OK;
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

WRESULT VlcPlayer086c::setVolume(int newVolume)
{
	libvlc_exception_clear(&_vlcexcep);
	if (newVolume < 0)
		newVolume = 0;
//	else if (newVolume > 100)
//		newVolume = 1000;

	if ( log != NULL )
		log->log( Logger::INFO, ":changeVolume() : Setting Volume to %i..", newVolume );
	libvlc_audio_set_volume(_vlcinstance, newVolume, &_vlcexcep);
	raise(&_vlcexcep);
	return WRET_OK;
}

WRESULT VlcPlayer086c::setVolumeOffset( int volume_span )
 {
	int currentVolume = getVolume();
	currentVolume += volume_span;
	return setVolume(currentVolume);
 }

WRESULT VlcPlayer086c::setMute( bool on )
 {
	libvlc_exception_clear(&_vlcexcep);
	if ( log != NULL )
		log->log( Logger::INFO, ":setMute() : Setting Mute = %i..", (int)on );
	libvlc_audio_set_mute(_vlcinstance, on, &_vlcexcep);
	raise(&_vlcexcep);
	return WRET_OK;
 }


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

WRESULT VlcPlayer086c::setFullScreen( bool on )
 {
	libvlc_exception_clear(&_vlcexcep);
	if ( log != NULL )
		log->log( Logger::INFO, ":setFullScreen() : Setting FullScreen = %i..", (int)on );

	libvlc_input_t* cInput = libvlc_playlist_get_input(_vlcinstance, &_vlcexcep);
	raise(&_vlcexcep);
	libvlc_set_fullscreen(cInput, (int)on, &_vlcexcep);
	raise(&_vlcexcep);
	return WRET_OK;
 }

WRESULT VlcPlayer086c::setVideoResize( int width, int height )
 {
	libvlc_exception_clear(&_vlcexcep);
	if ( log != NULL )
		log->log( Logger::INFO, ":setFullScreen() : Setting Size %i x %i", width, height );
	libvlc_input_t* cInput = libvlc_playlist_get_input(_vlcinstance, &_vlcexcep);
	raise(&_vlcexcep);
	libvlc_video_resize(cInput, width, height, &_vlcexcep);
	raise(&_vlcexcep);
	return WRET_OK;
 }

WRESULT VlcPlayer086c::getSnapshot( const string& output_file )
 {
	char out_file[255];
	strcpy(out_file, output_file.c_str() );

	libvlc_exception_clear(&_vlcexcep);
	if ( log != NULL )
		log->log( Logger::INFO, ":getSnapshot() : Saving to '%s'..", output_file.c_str() );
	libvlc_input_t* cInput = libvlc_playlist_get_input(_vlcinstance, &_vlcexcep);
	raise(&_vlcexcep);
	libvlc_video_take_snapshot(cInput, out_file, &_vlcexcep);
	raise(&_vlcexcep);
	return WRET_OK;
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

WRESULT VlcPlayer086c::getVLC_Info( std::map<std::string, std::string>& fields )
 {
	fields["VLC_Version"] = string(VLC_Version());
//	fields["VLC_CompileTime"] = string(VLC_CompileTime());
	fields["VLC_CompileBy"] = string(VLC_CompileBy());
	fields["VLC_CompileHost"] = string(VLC_CompileHost());
	fields["VLC_CompileDomain"] = string(VLC_CompileDomain());
	fields["VLC_Compiler"] = string(VLC_Compiler());

	return WRET_OK;
 }


int VlcPlayer086c::getVolume()
 {
	int audio_vol = libvlc_audio_get_volume(_vlcinstance, &_vlcexcep);
	raise(&_vlcexcep);
	return audio_vol;
 }

bool VlcPlayer086c::isPlaying()
 {
	bool is_playing = libvlc_playlist_isplaying(_vlcinstance, &_vlcexcep);
	raise(&_vlcexcep);
	return is_playing;
 }

bool VlcPlayer086c::isMuted()
 {
	bool audio_mute = libvlc_audio_get_mute(_vlcinstance, &_vlcexcep);
	raise(&_vlcexcep);
	return audio_mute;
 }

int VlcPlayer086c::getPlaylistCount()
 {
	int playlist_count = libvlc_playlist_items_count(_vlcinstance, &_vlcexcep);
	raise(&_vlcexcep);
	return playlist_count;
 }


WRESULT VlcPlayer086c::updateInfo()
 {
	libvlc_exception_clear(&_vlcexcep);

	if ( log != NULL )
		log->log( Logger::VERBOSE, ":updateInfo() .." );

	libvlc_input_t* cInput = libvlc_playlist_get_input(_vlcinstance, &_vlcexcep);
	raise(&_vlcexcep);
	bool fullscreen = (bool)libvlc_get_fullscreen(cInput, &_vlcexcep);
	raise(&_vlcexcep);

	int curr_video_height = libvlc_video_get_height(cInput, &_vlcexcep);
	raise(&_vlcexcep);
	int curr_video_width = libvlc_video_get_width(cInput, &_vlcexcep);
	raise(&_vlcexcep);


	return WRET_OK;
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

WRESULT VlcPlayer086c::setPosition(float position_rate)
{
	libvlc_exception_clear(&_vlcexcep);

	libvlc_input_t* cInput = libvlc_playlist_get_input(_vlcinstance, &_vlcexcep);
	raise(&_vlcexcep);

	if (position_rate < 0.0) position_rate = 0.0;
	else if (position_rate > 1.0) position_rate = 1.0;

	libvlc_input_set_position(cInput, position_rate, &_vlcexcep);
	raise(&_vlcexcep);

	return WRET_OK;
}

WRESULT VlcPlayer086c::setPositionOffset(float position_rate_offset)
{
	libvlc_exception_clear(&_vlcexcep);

	libvlc_input_t* cInput = libvlc_playlist_get_input(_vlcinstance, &_vlcexcep);
	raise(&_vlcexcep);

	position_rate_offset += libvlc_input_get_position(cInput, &_vlcexcep);
	raise(&_vlcexcep);

	if (position_rate_offset < 0.0) position_rate_offset = 0.0;
	else if (position_rate_offset > 1.0) position_rate_offset = 1.0;

	libvlc_input_set_position(cInput, position_rate_offset, &_vlcexcep);
	raise(&_vlcexcep);

	return WRET_OK;
}

////////////////////////////////////////////////////////////////////////////////////////////////////// EVENTS

void VlcPlayer086c::raise(libvlc_exception_t * ex)
{
	if ( libvlc_exception_raised(ex) ) {
		char* message = libvlc_exception_get_message(ex);
		if ( message != NULL && log != NULL )
			log->log( Logger::VERBOSE, ":VLC_Exception : '%s'", message );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////// EVENTS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////

WRESULT VlcPlayer086c::setVlcArguments( const string& arguments_line )
 {
	if ( this->running ) {
		if ( log != NULL )
			log->log( Logger::WARNING, ":setVlcArguments() : Not allowed while running!" );
		return WRET_ERR_ILLEGAL_USE;
	 }
	if ( log != NULL )
		log->log( Logger::INFO, ":setVlcArguments(%s)", arguments_line.c_str() );

	std::vector<std::string> results;
	int count = Utilities::splitString(arguments_line, ' ', results, false);
	char** arguments_list = NULL;

	if ( count > 0 ) {
		arguments_list = new char*[count+1];
		int j = 1;
		std::vector<std::string>::iterator it;
		for ( it=results.begin(); it!=results.end(); it++, j++ ) {
			Utilities::trimSpaces(*it);
			arguments_list[j] = new char[(*it).size()];
			strcpy(arguments_list[j], (*it).c_str() );
qDebug() << j << " => " << arguments_list[j];
		 }
	 }
	else {
		arguments_list = new char*[1];
	 }
	++count;
	arguments_list[0] = new char[4];
	strcpy(arguments_list[0], "vlc" );

	///@bug memory dealloc
	if ( this->vlc_argv != NULL )
		delete [] this->vlc_argv;

	this->vlc_argv = arguments_list;
	this->vlc_argc = count;

	return WRET_OK;
 }

/////////////////////////////////////////////////////////////////////////////////////////////// MODEM METHODS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VlcPlayer086c::setPlayerListener( IVlcPlayerListener* Listener ) {
	MutexLockerWrite mL(&configMux);
	this->playerListener = Listener;
 }

//void VlcPlayer086c::setPppInterface( const std::string& value ) {
//	MutexLockerWrite mL(&configMux);
//	this->pppInterface = value;
// }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

//std::string VlcPlayer086c::getControlScript() const {
//	MutexLockerRead mL(&configMux);
//	return this->controlScript;
// }

IVlcPlayerListener* VlcPlayer086c::getPlayerListener() {
	MutexLockerRead mL(&configMux);
	return this->playerListener;
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////

 }; // namespace devices
}; // namespace wosh
