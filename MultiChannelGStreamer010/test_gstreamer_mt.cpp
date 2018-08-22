/**
 * @file    test_PlayerGStreamer.cpp
 * @brief   Test classes: wosh::devices::PlayerGStreamer
 *
 * apt-get install libgstreamer ..
 *
 *
 * @version $Id: test_gstreamer_mt.cpp 435 2009-08-21 02:15:11Z alex $
 * @author Alessandro Polo
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
 ******************************************************************************/


 #include <core/Logger.h>
 #include <core/Utilities.h>
 
 #include <unistd.h>
 #include <map>
 #include <iostream>
 
 #include "PlayerGStreamer010.h"
 #include <gst/gst.h>

 
 #define Q_OS_LINUX
 
using namespace std;
using namespace wosh;
using namespace wosh::devices;

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool exitRequest = false;
//////////////////////////////////////////////////////////////////
#ifdef Q_OS_LINUX
 #include <fcntl.h>
 #include <unistd.h>
 #include <signal.h>

void signal_handler(int sig) {
	switch(sig) {
		case SIGHUP:
		case SIGTERM:
		case SIGINT:
			exitRequest = true;
			break;
	}
 }
void registerSignals()  {
	signal (SIGINT, signal_handler);
	signal (SIGTERM, signal_handler);
	signal (SIGHUP, signal_handler);
 }
#endif
//////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

int main ( int argc, char *argv[] )
{
	/* make sure we have input */
	if (argc != 3) {
		g_print ("Usage: %s <alsa-device-1> <alsa-device-2>\n", argv[0]);
		return -1;
	}
	
#ifdef Q_OS_LINUX
	registerSignals();
#endif

	Logger log_1;
	log_1.setLevel( Logger::VERBOSE );
	log_1.setContext( "Player1Th" );
	log_1.setIndent( 1 );
	Logger log_2;
	log_2.setLevel( Logger::VERBOSE );
	log_2.setContext( "Player2Th" );
	log_2.setIndent( 1 );

	Logger log1;
	log1.setLevel( Logger::VERBOSE );
	log1.setContext( "Player1" );
	log1.setIndent( 2 );
	Logger log2;
	log2.setLevel( Logger::VERBOSE );
	log2.setContext( "Player2" );
	log2.setIndent( 2 );

	Log::log( "test_VlcPlayer() : Starting TEST" );

	PlayerGStreamer010* player1 = new PlayerGStreamer010();
	player1->setLogger( &log1 );
	player1->startThread();

	PlayerGStreamer010* player2 = new PlayerGStreamer010();
	player2->setLogger( &log2 );
	player2->startThread();

	sleep(2);
	player1->setDeviceOutput( string(argv[1]) );
	player2->setDeviceOutput( string(argv[2]) );

	int sel = 0;
	PlayerGStreamer010* selected = NULL;
	string message;
	printf( "Type 'QUIT' or CTRL-C to exit." );
	while( true ) {
		Thread::sleepForMSec(100);
		if ( exitRequest ) break;
		std::cout << endl << "CH" << sel << ": ";
		std::cin >> message;
		if ( message == "QUIT" ) break;
		else if ( message.find("SELECT") == 0 ) {
			cout << "Channel [1-2] : ";
			std::cin >> sel;
			if ( sel == 1 ) selected = player1;
			else if ( sel == 2 ) selected = player2;
		 }
		if ( selected == NULL ) {
			cout << "Please select a channel";
			continue;
		 }

		if ( message == "PAUSE" ) {
			selected->pause();
		 }
		else if ( message == "STOP" ) {
			selected->stop();
		 }
		else if ( message == "GVOL" ) {
			cout << "Volume [0:100] : " << selected->getVolume();
		 }
		else if ( message == "GPOS" ) {
			cout << "Position [0:100] : " << selected->getPosition();
		 }
		else if ( message.find("MUTE") == 0 ) {
			if ( message.find("ON") == string::npos )
				selected->setMute(true);
			else
				selected->setMute(false);
		 }
		else if ( message.find("SVOL") == 0 ) {
			cout << "Type Volume [0:100] : ";
			std::cin >> message;
			int vol = Utilities::convertString2Integer(message);
			cout << "Changing volume to " << vol;
			selected->setVolume(vol);
		 }
		else if ( message == "PL" ) {
			selected->play("/shared/DM2002.wav");
		 }
		else if ( message.find("PLAY") == 0 ) {
			cout << "Type Media URI : ";
			std::cin >> message;
			if ( message.size() > 3 )
				selected->play(message);
			else
				selected->play();
		 }

	 }

	delete player2;
	delete player1;



	Log::log( "test_VlcPlayer() : Finished TEST" );
	return 0;
}
