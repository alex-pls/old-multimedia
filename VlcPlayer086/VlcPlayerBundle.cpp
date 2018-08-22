/** @file    VlcPlayerBundle.cpp
 *  @author  Alessandro Polo
 *  @version $Id: VlcPlayerBundle.cpp 734 2009-10-14 04:13:08Z alex $
 *  @brief
 * File containing methods for the wosh::devices::VlcPlayerBundle class.
 * The header for this class can be found in VlcPlayerBundle.h, check that file
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

 #include "VlcPlayerBundle.h"
 #include "VlcPlayer086c.h"
 //#include "VlcPlayer099.h"

 #include <core/MethodsDef.h>
 #include <core/Fact.h>
 #include <core/ThreadManager.h>
 #include <core/DeviceManager.h>


using namespace std;
namespace wosh {
 namespace devices {

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////// CONSTRUCTORS

VlcPlayerBundle::VlcPlayerBundle( const string& device_name ) : BundleGeneric()
 {
	if ( device_name.size() > 0 )	BundleGeneric::setName( device_name );
	else							BundleGeneric::setName( _VlcPlayer_NAME );
	BundleGeneric::setType( "wosh::devices::Player.Audio" );
	Properties.setProperty( _Bundle_KEY_Version, _VlcPlayer_VERSION );
	Interfaces.add( _Device_TYPE );
	Interfaces.add( _PlayerAudio_TYPE );

Log.setLevel( Logger::VERBOSE );

	Log.log( Logger::VERBOSE, " Configuring Player worker.." );
	this->playerWorker = new VlcPlayer086c();
	this->playerWorker->setLogger( &Log );
	this->playerWorker->setThreadListener(this);
	this->playerWorker->setPlayerListener(this);
	this->playerWorker->setOwnerObject(this);

	this->devState = wosh::interfaces::Device::UNKNOWN;

	Log.log( Logger::VERBOSE, " Setting default properties and permissions.." );
	Properties.setProperty( _Player_KEY_Volume,				0,	Permission( Permission::RW, Permission::RW, Permission::Read) );
	Properties.setProperty( _VlcPlayer_KEY_VlcArguments,	"",	Permission( Permission::RW, Permission::RW, Permission::Read) );
	Properties.setProperty( _Device_KEY_DeviceStatus,		wosh::interfaces::Device::getDeviceStateAsString(wosh::interfaces::Device::UNKNOWN), Permission( Permission::Read ) );

	std::map<std::string, std::string> fields;
	this->playerWorker->getVLC_Info( fields );
	std::map<std::string,std::string>::const_iterator it;
	for ( it=fields.begin(); it!=fields.end(); it++ ) {
		Properties.setProperty( it->first, it->second, Permission( Permission::Read ) );
	 }

	Log.log( Logger::VERBOSE, " Registering methods.." );

	MethodWRESULT* mmPause = new MethodWRESULT( _Player_METHOD_pause );
	mmPause->setMethod( this, (MethodWRESULTPtr)&VlcPlayerBundle::pause ); //direct method
	mmPause->getPermission().setMask( Permission::RX, Permission::RX, Permission::RX );
	Methods.registerMethod(mmPause);
	MethodWRESULT* mmStop = new MethodWRESULT( _Player_METHOD_stop );
	mmStop->setMethod( this, (MethodWRESULTPtr)&VlcPlayerBundle::stop ); //direct method
	mmStop->getPermission().setMask( Permission::RX, Permission::RX, Permission::RX );
	Methods.registerMethod(mmStop);
	MethodWRESULT* mmNext = new MethodWRESULT( _Player_METHOD_next );
	mmNext->setMethod( this, (MethodWRESULTPtr)&VlcPlayerBundle::next ); //direct method
	mmNext->getPermission().setMask( Permission::RX, Permission::RX, Permission::RX );
	Methods.registerMethod(mmNext);
	MethodWRESULT* mmPrev = new MethodWRESULT( _Player_METHOD_prev );
	mmPrev->setMethod( this, (MethodWRESULTPtr)&VlcPlayerBundle::prev ); //direct method
	mmPrev->getPermission().setMask( Permission::RX, Permission::RX, Permission::RX );
	Methods.registerMethod(mmPrev);
	MethodWRESULT* mmClear = new MethodWRESULT( _Player_METHOD_clear );
	mmClear->setMethod( this, (MethodWRESULTPtr)&VlcPlayerBundle::clear ); //direct method
	mmClear->getPermission().setMask( Permission::RX, Permission::RX, Permission::RX );
	Methods.registerMethod(mmClear);

	MethodRequest* mmPlay = new MethodRequest( _Player_METHOD_play );
	mmPlay->setMethod( this, (MethodRequestPtr)&VlcPlayerBundle::mmDoPlay );
	mmPlay->getPermission().setMask( Permission::RX, Permission::RX, Permission::RX );
	Methods.registerMethod(mmPlay);

	MethodRequest* mmEnqueue = new MethodRequest( _Player_METHOD_enqueue );
	mmEnqueue->setMethod( this, (MethodRequestPtr)&VlcPlayerBundle::mmDoEnqueue );
	mmEnqueue->getPermission().setMask( Permission::RX, Permission::RX, Permission::RX );
	Methods.registerMethod(mmEnqueue);

	MethodRequest* mmSetVolume = new MethodRequest( _Player_METHOD_set_volume );
	mmSetVolume->setMethod( this, (MethodRequestPtr)&VlcPlayerBundle::mmDoSetVolume );
	mmSetVolume->getPermission().setMask( Permission::RX, Permission::RX, Permission::RX );
	Methods.registerMethod(mmSetVolume);

	MethodRequest* mmSetMute = new MethodRequest( _Player_METHOD_set_mute );
	mmSetMute->setMethod( this, (MethodRequestPtr)&VlcPlayerBundle::mmDoSetMute );
	mmSetMute->getPermission().setMask( Permission::RX, Permission::RX, Permission::RX );
	Methods.registerMethod(mmSetMute);

	MethodRequest* mmSetPosition = new MethodRequest( _Player_METHOD_set_position );
	mmSetPosition->setMethod( this, (MethodRequestPtr)&VlcPlayerBundle::mmDoSetPosition );
	mmSetPosition->getPermission().setMask( Permission::RX, Permission::RX, Permission::RX );
	Methods.registerMethod(mmSetPosition);



	BusDevices.setMessageHandler(this);
	WRESULT bus_connected = BusDevices.connect( "wosh.Bus.Devices" );
	if ( WFAILED(bus_connected) )
		Log.log( Logger::CRITICAL, ":VlcPlayerBundle() : FAILED#%i Connecting Bus (wosh.Bus.Devices)..", bus_connected );

	setBundleState(Bundle::CREATED, false);
 }


VlcPlayerBundle::~VlcPlayerBundle()
 {
	Log.log( Logger::INFO, " Destroying.." );

	if ( isBundleRunning() ) {
		Log.log( Logger::WARNING, "~VlcPlayerBundle() : Destroying while Bundle is running! Trying to stop.." );
		bundleStop();
	 }

	if ( this->playerWorker->isThreadRunning() ) {
		Log.log( Logger::WARNING, "~VlcPlayerBundle() : Destroying while RUNNING! Trying to stop.." );
		this->playerWorker->quitThread();
		this->playerWorker->waitThread(30000);
	 }

	delete this->playerWorker; this->playerWorker = NULL;

	Log.log( Logger::VERBOSE, ":~VlcPlayerBundle() : Destroyed." );
 }

//////////////////////////////////////////////////////////////////////////////////////////////// CONSTRUCTORS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////// BUNDLE CONTROL

WRESULT VlcPlayerBundle::bundleStart()
 {
	if ( !BundleGeneric::bundleValidate_StartStop(Bundle::STARTING) )
		return WRET_ERR_WRONG_STATE;

	WRESULT ret = BundleGeneric::start_SynchThread( this->playerWorker );

	if ( WSUCCEEDED(ret) ) {
		Log.log( Logger::VERBOSE, ":bundleStart() : Registering as Device.." );
		wosh::Device* myself = new wosh::Device();
		myself->setName( this->getName() );
		myself->setBundleOwner( this->getName() );
		myself->getInterfaces().add( _PlayerAudio_TYPE );
		DeviceManager::registerDevice( myself );
	 }
	// BUNDLE-STATE (STARTED) will be updated async by WORKER, through call: IThreadListener::thread_event()
	return ret;
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

WRESULT VlcPlayerBundle::bundleStop()
 {
	if ( !BundleGeneric::bundleValidate_StartStop(Bundle::STOPPING) )
		return WRET_ERR_WRONG_STATE;

	WRESULT ret = BundleGeneric::stop_SynchThread( this->playerWorker );

	if ( WSUCCEEDED(ret) ) {
		Log.log( Logger::VERBOSE, ":bundleStart() : UnRegistering as Device.." );
		DeviceManager::unRegisterDevice( this->getName() );
	 }
	// BUNDLE-STATE (STOPPED) will be updated async by WORKER, through call: IThreadListener::thread_event()
	return ret;
 }

WRESULT VlcPlayerBundle::bundleDiagnostic()
 {
	Log.log( Logger::VERBOSE, ":bundleDiagnostic() : Starting VlcPlayerBundle-Diagnostic" );

	WRESULT ret = BundleGeneric::bundleDiagnostic();


	Log.log( Logger::INFO, ":bundleDiagnostic() : Finished VlcPlayerBundle-Diagnostic [%i]", ret );
	return ret;
 }

////////////////////////////////////////////////////////////////////////////////////////////// BUNDLE CONTROL
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VlcPlayerBundle::busMessage( const Message& message, Bus* source )
 {
	// avoid double-response, since there is route core<->devices,
	// if source bus is CORE and current is DEVICE, then it's a double message and we drop
	if ( message.getSourceBus() == BusCore.getBusName() && message.getCurrentBus() == BusDevices.getBusName() )
		return;

	BundleGeneric::busMessage( message, source );
 }


//////////////////////////////////////////////////////////////////////////////////////////// GENERATED EVENTS

void VlcPlayerBundle::raiseEvent( Fact* fact )
 {
	Message* msg_event = new Message();
	msg_event->setSource( this );
	msg_event->setContent( fact );
	msg_event->setDestinationBroadcast();
	BusDevices.postMessage(msg_event);
 }

//////////////////////////////////////////////////////////////////////////////////////////// GENERATED EVENTS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////// PROPERTY EVENT

WRESULT VlcPlayerBundle::applyingProperty( const string& key, const Data& value )
 {
	if ( key == _Player_KEY_Volume ) {
		string volumeStr = value.getData();
		Utilities::trimSpaces(volumeStr);
		if (volumeStr.size() == 0)
			return WRET_ERR_PARAM;

		WRESULT ret = WRET_ERR_INTERNAL;
		if (volumeStr.substr(0,1) == "+" || volumeStr.substr(0,1) == "-") {
			int sign = 1;
			if ( volumeStr.substr(0,1) == "-" )
				sign = -1;
		
			int vol_span = Utilities::convertString2Integer(volumeStr.substr(1));
			ret = setVolumeOffset( vol_span * sign );
		 }
		else {
			int volume = Utilities::convertString2Integer(volumeStr);
			ret = setVolume(volume);
		 }
	 }
	else if ( key == _VlcPlayer_KEY_VlcArguments ) {
		return setVlcArguments( value.getData() );
	 }
	else // maybe its a base-class Property (as name, debug-level, ..)
		return BundleGeneric::applyingProperty(key, value);

	return WRET_OK;
 }

////////////////////////////////////////////////////////////////////////////////////////////// PROPERTY EVENT
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////// THREAD EVENTS

void VlcPlayerBundle::thread_event( Thread* thread, Thread::THREAD_STATE event )
 {
	long id = 0;
	if ( thread != NULL )
		id = thread->getThreadID();

	Log.log( Logger::VERBOSE, ":thread_event(%i) : %s", id, Thread::getThreadStateAsString(event).c_str() );

	switch(event) {
		case Thread::RUNNING: {
				setBundleState( Bundle::STARTED );
				break;
			 }
		case Thread::STOPPED: {
				setBundleState( Bundle::STOPPED );
				break;
			 }
		default: break;
	 }
 }

/////////////////////////////////////////////////////////////////////////////////////////////// THREAD EVENTS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////// MODEM EVENTS

WRESULT VlcPlayerBundle::setVlcArguments( const std::string& arguments_line )
 {
	if ( isBundleRunning() ) {
		Log.log( Logger::CRITICAL, ":setVlcArguments(%s) Illegal while running!", arguments_line.c_str() );
		return WRET_ERR_ILLEGAL_USE;
	 }
	return this->playerWorker->setVlcArguments(arguments_line);
 }

WRESULT VlcPlayerBundle::updateInfo() {
	return this->playerWorker->updateInfo();
 }

WRESULT VlcPlayerBundle::play( const std::string& file_url ) {
	return this->playerWorker->play(file_url);
 }
WRESULT VlcPlayerBundle::enqueue( const std::string& file_url ) {
	return this->playerWorker->enqueue(file_url);
 }

WRESULT VlcPlayerBundle::pause() {
	return this->playerWorker->pause();
 }
WRESULT VlcPlayerBundle::stop() {
	return this->playerWorker->stop();
 }
WRESULT VlcPlayerBundle::next() {
	return this->playerWorker->next();
 }
WRESULT VlcPlayerBundle::prev() {
	return this->playerWorker->prev();
 }
WRESULT VlcPlayerBundle::clear() {
	return this->playerWorker->clear();
 }


WRESULT VlcPlayerBundle::setVolume( int newVolume ) {
	return this->playerWorker->setVolume(newVolume);
 }
WRESULT VlcPlayerBundle::setVolumeOffset( int volume_span ) {
	return this->playerWorker->setVolumeOffset(volume_span);
 }

WRESULT VlcPlayerBundle::setMute( bool on ) {
	return this->playerWorker->setMute(on);
 }
WRESULT VlcPlayerBundle::setPosition( float position_rate ) {
	return this->playerWorker->setPosition(position_rate);
 }
WRESULT VlcPlayerBundle::setPositionOffset( float position_rate_offset ) {
	return this->playerWorker->setPositionOffset(position_rate_offset);
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

WRESULT VlcPlayerBundle::synchWithPlayer( const string& device_player_name, int flags )
 {
(void)device_player_name;
(void)flags;

	return WRET_ERR_INTERNAL;
 }

//////////////////////////////////////////////////////////////////////////////////////////////// MODEM EVENTS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////// METHODS

Response* VlcPlayerBundle::mmDoEnqueue( const Request* request )
 {
	if ( request == NULL ) return NULL;
	// retrieve options
	string fileStr = request->getArgument().getData();
	Log.log( Logger::INFO, ":mmDoEnqueue(%s)", fileStr.c_str() );

	WRESULT ret = enqueue(fileStr);

	Response* response = new Response( request->getMethod(), ret );
	return response;
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

Response* VlcPlayerBundle::mmDoPlay( const Request* request )
 {
	if ( request == NULL ) return NULL;
	// retrieve options
	string fileStr = request->getArgument().getData();
	Log.log( Logger::INFO, ":mmDoPlay(%s)", fileStr.c_str() );

	WRESULT ret = play(fileStr);

	Response* response = new Response( request->getMethod(), ret );
	return response;
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

Response* VlcPlayerBundle::mmDoSetVolume( const Request* request )
 {
	if ( request == NULL ) return NULL;
	// retrieve options
	string volumeStr = request->getArgument().getData();
	Log.log( Logger::INFO, ":mmDoSetVolume(%s)", volumeStr.c_str() );

	WRESULT ret = applyingProperty(_Player_KEY_Volume, volumeStr);

	Response* response = new Response( request->getMethod(), ret );
	return response;
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

Response* VlcPlayerBundle::mmDoSetMute( const Request* request )
 {
	if ( request == NULL ) return NULL;
	// retrieve options
	string muteStr = request->getArgument().getData();
	Log.log( Logger::INFO, ":mmDoSetMute(%s)", muteStr.c_str() );

	bool mute = (bool)Utilities::convertString2Bool(muteStr, 0);
	WRESULT ret = setMute(mute);

	Response* response = new Response( request->getMethod(), ret );
	return response;
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

Response* VlcPlayerBundle::mmDoSetPosition( const Request* request )
 {
	if ( request == NULL ) return NULL;
	// retrieve options
	string posStr = request->getArgument().getData();
	Utilities::trimSpaces(posStr);
	Log.log( Logger::INFO, ":mmDoSetPosition(%s)", posStr.c_str() );

	WRESULT ret = WRET_OK;
	float pos = -1.0;
	if ( posStr == "+" )
		ret = setPositionOffset(0.1);
	else if ( posStr == "-" )
		ret = setPositionOffset(-0.1);
	else {
		Utilities::convert(posStr, pos);
		ret = setPosition(pos);
	 }

	Response* response = new Response( request->getMethod(), ret );
	return response;
 }

///////////////////////////////////////////////////////////////////////////////////////////////////// METHODS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

 }; // namespace devices
}; // namespace wosh
