/**
 * @file    test_VlcPlayer.cpp
 * @brief   Test classes: wosh::devices::VlcPlayer
 *
 * @version $Id: test_VlcPlayer.cpp 435 2009-08-21 02:15:11Z alex $
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

 #include <woshDefs.h>
 #include <core/Logger.h>
 #include <core/Utilities.h>
 #include <iostream>
 
 #include "VlcPlayer086c.h"
 //#include "VlcPlayer099.h"

 #define Q_OS_LINUX
 
bool exitRequest = false;
//////////////////////////////////////////////////////////////////
#ifdef Q_OS_LINUX
 #include <fcntl.h>
 #include <unistd.h>
 #include <signal.h>

void test_VlcPlayer_signal_handler(int sig) {
	switch(sig) {
		case SIGHUP:
		case SIGTERM:
		case SIGINT:
			exitRequest = true;
			break;
	}
 }
void test_VlcPlayer_registerSignals()  {
	signal (SIGINT, test_VlcPlayer_signal_handler);
	signal (SIGTERM, test_VlcPlayer_signal_handler);
	signal (SIGHUP, test_VlcPlayer_signal_handler);
 }
#endif
//////////////////////////////////////////////////////////////////


using namespace std;
using namespace wosh;
using namespace wosh::devices;


void test_class_VlcPlayer();




int test_VlcPlayer()
 {
	Log::log( "test_VlcPlayer() : Starting TEST" );

	test_class_VlcPlayer();


	Log::log( "test_VlcPlayer() : Finished TEST" );
	return 0;
 }




void test_class_VlcPlayer()
 {
	Log::log( " test_class_VlcPlayer() : Starting TEST for class 'VlcPlayer'" );

#ifdef Q_OS_LINUX
	test_VlcPlayer_registerSignals();
#endif

	Logger log;
	log.setLevel( Logger::VERBOSE );

	VlcPlayer086c player;
	player.setLogger( &log );

	player.startThread();

//	player.play("sample.mp3");

	string message;
	log.log( "Type 'QUIT' or CTRL-C to exit." );
	while( true ) {
		Thread::sleepForMSec(100);
		if ( exitRequest ) break;
		std::cin >> message;
		if ( message == "QUIT" ) break;

		if ( message == "PAUSE" ) {
			player.pause();
		 }
		else if ( message == "STOP" ) {
			player.stop();
		 }
		else if ( message == "NEXT" ) {
			player.next();
		 }
		else if ( message == "PREV" ) {
			player.prev();
		 }
		else if ( message == "CLEAR" ) {
			player.clear();
		 }

		else if ( message.find("FULLSCREEN") == 0 ) {
			if ( message.find("ON") == 0 )
				player.setFullScreen(true);
			else
				player.setFullScreen(false);
		 }

		else if ( message.find("SNAPSHOT") == 0 ) {
			player.getSnapshot("snapshot");
		 }

		else if ( message.find("MUTE") == 0 ) {
			if ( message.find("ON") == 0 )
				player.setMute(true);
			else
				player.setMute(false);
		 }
		else if ( message.find("VOLUME") == 0 ) {
			cout << "Type Volume [0:100] : ";
			std::cin >> message;
			log.log( "Changing volume to " + message );
			int vol = Utilities::convertString2Integer(message);
			player.setVolume(vol);
		}
		else if ( message.find("PLAY") == 0 ) {
			cout << "Type Media URI : ";
			std::cin >> message;
			player.play(message);
		}
	 }

	// exit
	player.quitThread();

	log.log( " test_class_VlcPlayer() : Finished TEST for class 'VlcPlayer'" );
 }



int main()
 {
	return test_VlcPlayer();
 }
