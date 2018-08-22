/** @file    VlcPlayer099.cpp
 *  @author  Alessandro Polo
 *  @version $Id: VlcPlayer099.cpp 435 2009-08-21 02:15:11Z alex $
 *  @brief
 * File containing methods for the wosh::devices::VlcPlayer099 class.
 * The header for this class can be found in VlcPlayer099.h, check that file
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

 #include "VlcPlayer099.h"
 #include <core/Logger.h>


namespace wosh {
 namespace devices {

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////// CONSTRUCTORS

VlcPlayer099::VlcPlayer099() : ThreadWorker("wosh.Device.VlcPlayer099.WorkerThread")
 {

	
	this->playerListener = NULL;
 }

VlcPlayer099::~VlcPlayer099()
 {
	if ( log != NULL )
		log->log( Logger::VERBOSE, ":~VlcPlayer099(): Destroying.." );

	if ( isThreadRunning() ) {
		quitThread();
	 }

 }

//////////////////////////////////////////////////////////////////////////////////////////////// CONSTRUCTORS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////// THREAD RUN

void VlcPlayer099::runThread()
 {
	this->running = true;

	//Initialize an instance of vlc
    //a structure for the exception is neede for this initalization
	libvlc_exception_init(&_vlcexcep);

	//create a new libvlc instance
    _vlcinstance=libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args,&_vlcexcep);  //tricky calculation of the char space used
    raise (&_vlcexcep);

	// Create a media player playing environement 
    _mp = libvlc_media_player_new (_vlcinstance, &_vlcexcep);
    raise (&_vlcexcep);


	if ( log != NULL )
		log->log( Logger::VERBOSE, ":runThread() : Entering Loop.." );

	while(this->running)
	 {
		Thread::sleepForSec(1);
	 }

    // Stop playing
    libvlc_media_player_stop (_mp, &_vlcexcep);

    // Free the media_player
    libvlc_media_player_release (_mp);

    libvlc_release (_vlcinstance);
    raise (&_vlcexcep);
 }

////////////////////////////////////////////////////////////////////////////////////////////////// THREAD RUN
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

WRESULT VlcPlayer099::play( const std::string& file_url )
 {
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

	/* Create a new LibVLC media descriptor */
	_m = libvlc_media_new (_vlcinstance, file.toAscii(), &_vlcexcep);
	raise(&_vlcexcep);

	libvlc_media_player_set_media (_mp, _m, &_vlcexcep);
	raise(&_vlcexcep);

	// Please note
	// passing the widget to the lib shows vlc at which position it should show up
	// vlc automatically resizes the video to the ´given size of the widget
	// and it even resizes it, if the size changes at the playing
/*
	// Get our media instance to use our window
#if defined(Q_OS_WIN)
	libvlc_media_player_set_drawable(_mp, reinterpret_cast<unsigned int>(_videoWidget->winId()), &_vlcexcep );
	//libvlc_media_player_set_hwnd(_mp, _videoWidget->winId(), &_vlcexcep ); // for vlc 1.0
#elif defined(Q_OS_MAC)
	libvlc_media_player_set_drawable(_mp, _videoWidget->winId(), &_vlcexcep );
	//libvlc_media_player_set_agl (_mp, _videoWidget->winId(), &_vlcexcep); // for vlc 1.0
#else //Linux
	libvlc_media_player_set_drawable(_mp, _videoWidget->winId(), &_vlcexcep );
	//libvlc_media_player_set_xwindow(_mp, _videoWidget->winId(), &_vlcexcep ); // for vlc 1.0
#endif
	raise(&_vlcexcep);
*/

	// Play
	libvlc_media_player_play (_mp, &_vlcexcep );
	raise(&_vlcexcep);

	_isPlaying=true;

	return WRET_OK;
 }

WRESULT VlcPlayer099::changeVolume(int newVolume)
{
	libvlc_exception_clear(&_vlcexcep);
	libvlc_audio_set_volume (_vlcinstance,newVolume , &_vlcexcep);
	raise(&_vlcexcep);

	return WRET_OK;
}

WRESULT VlcPlayer099::changePosition(int newPosition)
{
	libvlc_exception_clear(&_vlcexcep);
	// It's possible that the vlc doesn't play anything so check before

	libvlc_media_t *curMedia = libvlc_media_player_get_media (_mp, &_vlcexcep);
	libvlc_exception_clear(&_vlcexcep);
	if (curMedia == NULL)
		return WRET_ERR_INTERNAL;

	float pos=(newPosition)/POSITION_RESOLUTION;
	libvlc_media_player_set_position (_mp, pos, &_vlcexcep);
	raise(&_vlcexcep);

	return WRET_OK;
}


////////////////////////////////////////////////////////////////////////////////////////////////////// EVENTS

void VlcPlayer099::raise(libvlc_exception_t * ex)
{
	if ( libvlc_exception_raised(ex) ) {
		if ( log != NULL )
			log->log( Logger::VERBOSE, ":runThread() : Entering Loop.." );

		exit (-1);
	}
}


/*
void VlcPlayer099::raiseEvent( PlayerInterface::CONNECTION_STATE state )
 {
	this->configMux.lockForRead();
	IVlcPlayerListener* handler = this->playerListener;
	this->configMux.unLock();

	if ( handler != NULL )
		handler->player_ConnectionState( this, state );
 }
*/
////////////////////////////////////////////////////////////////////////////////////////////////////// EVENTS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////

WRESULT VlcPlayer099::setVlcArguments( const string& arguments_line )
 {
	return WRET_OK;

 }

/////////////////////////////////////////////////////////////////////////////////////////////// MODEM METHODS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VlcPlayer099::setPlayerListener( IVlcPlayerListener* Listener ) {
	MutexLockerWrite mL(&configMux);
	this->playerListener = Listener;
 }

//void VlcPlayer099::setPppInterface( const std::string& value ) {
//	MutexLockerWrite mL(&configMux);
//	this->pppInterface = value;
// }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

//std::string VlcPlayer099::getControlScript() const {
//	MutexLockerRead mL(&configMux);
//	return this->controlScript;
// }

IVlcPlayerListener* VlcPlayer099::getPlayerListener() {
	MutexLockerRead mL(&configMux);
	return this->playerListener;
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////

 }; // namespace devices
}; // namespace wosh
