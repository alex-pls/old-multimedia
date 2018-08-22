/** @file    PlayerGStreamerBundle.cpp
 *  @author  Alessandro Polo
 *  @version $Id: PlayerGStreamerBundle.cpp 734 2009-10-14 04:13:08Z alex $
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

 #include "PlayerGStreamerBundle.h"
 #include "PlayerGStreamer010.h"

 #include <core/MethodsDef.h>
 #include <core/MessageProcessingCommon.h>
 #include <core/Fact.h>
 #include <core/Table.h>
 #include <core/ThreadManager.h>
 #include <core/DeviceManager.h>


using namespace std;
namespace wosh {
 namespace devices {

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////// CONSTRUCTORS

PlayerGStreamerBundle::PlayerGStreamerBundle( const string& name, const string& device_name ) : BundleGeneric()
 {
	if ( name.size() > 0 )	BundleGeneric::setName( name );
	else					BundleGeneric::setName( _PlayerGStreamer_NAME );

	BundleGeneric::setType( _PlayerAudio_TYPE );
	Properties.setProperty( _Bundle_KEY_Version, _PlayerGStreamer_VERSION );
	Interfaces.add( _Device_TYPE );
	Interfaces.add( _PlayerAudio_TYPE );

Log.setLevel( Logger::VERBOSE );

	Log.log( Logger::VERBOSE, " Configuring Player worker.." );
	this->playerWorker = new PlayerGStreamer010();
	this->playerWorker->setLogger( &Log );
	this->playerWorker->setThreadListener(this);
	this->playerWorker->setPlayerListener(this);
	this->playerWorker->setOwnerObject(this);

	this->devState = wosh::interfaces::Device::UNKNOWN;
	this->playerWorker->setDeviceOutput(device_name);

	Log.log( Logger::VERBOSE, " Setting default properties and permissions.." );
	Properties.setProperty( _Player_KEY_Volume,				10,	Permission( Permission::RW, Permission::RW, Permission::Read) );
	Properties.setProperty( _Player_KEY_DeviceOutput,		device_name,	Permission( Permission::RW, Permission::RW, Permission::Read) );
	Properties.setProperty( _Player_KEY_CurrentFile,		"",	Permission( Permission::Read ) );
	Properties.setProperty( _Player_KEY_Mute, 				0,	Permission( Permission::Read ) );
	Properties.setProperty( _Player_KEY_CurrentLength,		"",	Permission( Permission::Read ) );

	Properties.setProperty( _Device_KEY_DeviceStatus,		wosh::interfaces::Device::getDeviceStateAsString(wosh::interfaces::Device::UNKNOWN), Permission( Permission::Read ) );

	std::map<std::string, std::string> fields;
	this->playerWorker->getAPIInfo( fields );
	std::map<std::string,std::string>::const_iterator it;
	for ( it=fields.begin(); it!=fields.end(); it++ ) {
		Properties.setProperty( it->first, it->second, Permission( Permission::Read ) );
	 }

	Log.log( Logger::VERBOSE, " Registering methods.." );

	MethodWRESULT* mmPause = new MethodWRESULT( _Player_METHOD_pause );
	mmPause->setMethod( this, (MethodWRESULTPtr)&PlayerGStreamerBundle::pause ); //direct method
	mmPause->getPermission().setMask( Permission::RX, Permission::RX, Permission::RX );
	Methods.registerMethod(mmPause);
	MethodWRESULT* mmStop = new MethodWRESULT( _Player_METHOD_stop );
	mmStop->setMethod( this, (MethodWRESULTPtr)&PlayerGStreamerBundle::stop ); //direct method
	mmStop->getPermission().setMask( Permission::RX, Permission::RX, Permission::RX );
	Methods.registerMethod(mmStop);
	MethodWRESULT* mmNext = new MethodWRESULT( _Player_METHOD_next );
	mmNext->setMethod( this, (MethodWRESULTPtr)&PlayerGStreamerBundle::next ); //direct method
	mmNext->getPermission().setMask( Permission::RX, Permission::RX, Permission::RX );
	Methods.registerMethod(mmNext);
	MethodWRESULT* mmPrev = new MethodWRESULT( _Player_METHOD_prev );
	mmPrev->setMethod( this, (MethodWRESULTPtr)&PlayerGStreamerBundle::prev ); //direct method
	mmPrev->getPermission().setMask( Permission::RX, Permission::RX, Permission::RX );
	Methods.registerMethod(mmPrev);
	MethodWRESULT* mmClear = new MethodWRESULT( _Player_METHOD_clear );
	mmClear->setMethod( this, (MethodWRESULTPtr)&PlayerGStreamerBundle::clear ); //direct method
	mmClear->getPermission().setMask( Permission::RX, Permission::RX, Permission::RX );
	Methods.registerMethod(mmClear);
	MethodWRESULT* mmFirst = new MethodWRESULT( _Player_METHOD_first );
	mmFirst->setMethod( this, (MethodWRESULTPtr)&PlayerGStreamerBundle::first ); //direct method
	mmFirst->getPermission().setMask( Permission::RX, Permission::RX, Permission::RX );
	Methods.registerMethod(mmFirst);
	MethodWRESULT* mmLast = new MethodWRESULT( _Player_METHOD_last );
	mmLast->setMethod( this, (MethodWRESULTPtr)&PlayerGStreamerBundle::last ); //direct method
	mmLast->getPermission().setMask( Permission::RX, Permission::RX, Permission::RX );
	Methods.registerMethod(mmLast);

	MethodRequest* mmList = new MethodRequest( "list", "List engueued items" );
	mmList->setMethod( this, (MethodRequestPtr)&PlayerGStreamerBundle::mmDoList );
	mmList->getPermission().setMask( Permission::RX, Permission::RX, Permission::RX );
	Methods.registerMethod(mmList);

	MethodRequest* mmPlay = new MethodRequest( _Player_METHOD_play );
	mmPlay->setMethod( this, (MethodRequestPtr)&PlayerGStreamerBundle::mmDoPlay );
	mmPlay->getPermission().setMask( Permission::RX, Permission::RX, Permission::RX );
	Methods.registerMethod(mmPlay);

	MethodRequest* mmEnqueue = new MethodRequest( _Player_METHOD_enqueue );
	mmEnqueue->setMethod( this, (MethodRequestPtr)&PlayerGStreamerBundle::mmDoEnqueue );
	mmEnqueue->getPermission().setMask( Permission::RX, Permission::RX, Permission::RX );
	Methods.registerMethod(mmEnqueue);

	MethodRequest* mmSetVolume = new MethodRequest( _Player_METHOD_set_volume );
	mmSetVolume->setMethod( this, (MethodRequestPtr)&PlayerGStreamerBundle::mmDoSetVolume );
	mmSetVolume->getPermission().setMask( Permission::RX, Permission::RX, Permission::RX );
	Methods.registerMethod(mmSetVolume);

	MethodRequest* mmSetMute = new MethodRequest( _Player_METHOD_set_mute );
	mmSetMute->setMethod( this, (MethodRequestPtr)&PlayerGStreamerBundle::mmDoSetMute );
	mmSetMute->getPermission().setMask( Permission::RX, Permission::RX, Permission::RX );
	Methods.registerMethod(mmSetMute);

	MethodRequest* mmSetPosition = new MethodRequest( _Player_METHOD_set_position );
	mmSetPosition->setMethod( this, (MethodRequestPtr)&PlayerGStreamerBundle::mmDoSetPosition );
	mmSetPosition->getPermission().setMask( Permission::RX, Permission::RX, Permission::RX );
	Methods.registerMethod(mmSetPosition);

	MethodRequest* mmSynchWithPlayer = new MethodRequest( _Player_METHOD_synch );
	mmSynchWithPlayer->setMethod( this, (MethodRequestPtr)&PlayerGStreamerBundle::mmDoSynchWithPlayer );
	mmSynchWithPlayer->getPermission().setMask( Permission::RX, Permission::RX, Permission::RX );
	Methods.registerMethod(mmSynchWithPlayer);

	BusDevices.setMessageHandler(this);
	WRESULT bus_connected = BusDevices.connect( "wosh.Bus.Devices" );
	if ( WFAILED(bus_connected) )
		Log.log( Logger::CRITICAL, ":PlayerGStreamerBundle() : FAILED#%i Connecting Bus (wosh.Bus.Devices)..", bus_connected );

	setBundleState(Bundle::CREATED, false);
 }


PlayerGStreamerBundle::~PlayerGStreamerBundle()
 {
	Log.log( Logger::VERBOSE, " Destroying.." );

	if ( isBundleRunning() ) {
		Log.log( Logger::WARNING, "~PlayerGStreamerBundle() : Destroying while Bundle is running! Trying to stop.." );
		bundleStop();
	 }

	if ( this->playerWorker->isThreadRunning() ) {
		Log.log( Logger::WARNING, "~PlayerGStreamerBundle() : Destroying while RUNNING! Trying to stop.." );
		this->playerWorker->quitThread();
		this->playerWorker->waitThread(30000);
	 }

	delete this->playerWorker; this->playerWorker = NULL;

	Log.log( Logger::VERBOSE, ":~PlayerGStreamerBundle() : Destroyed." );
 }

//////////////////////////////////////////////////////////////////////////////////////////////// CONSTRUCTORS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////// BUNDLE CONTROL

WRESULT PlayerGStreamerBundle::bundleStart()
 {
	if ( !BundleGeneric::bundleValidate_StartStop(Bundle::STARTING) )
		return WRET_ERR_WRONG_STATE;

	WRESULT ret = BundleGeneric::start_SynchThread( this->playerWorker );

	if ( WSUCCEEDED(ret) ) {
		Properties.setProperty( _Player_KEY_Volume, this->playerWorker->getVolume() );

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

WRESULT PlayerGStreamerBundle::bundleStop()
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

WRESULT PlayerGStreamerBundle::bundleDiagnostic()
 {
	Log.log( Logger::VERBOSE, ":bundleDiagnostic() : Starting PlayerGStreamerBundle-Diagnostic" );

	WRESULT ret = BundleGeneric::bundleDiagnostic();

	Log.log( Logger::INFO, ":bundleDiagnostic() : Finished PlayerGStreamerBundle-Diagnostic [%i]", ret );
	return ret;
 }

////////////////////////////////////////////////////////////////////////////////////////////// BUNDLE CONTROL
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////// BUS MESSAGES

void PlayerGStreamerBundle::busMessage( const Message& message, Bus* source )
 {
	if ( message.isEmpty() ) return;
	if ( !message.getContent()->isRequest() )
		return;

	if ( message.getCurrentBus() == BusDevices.getBusName() ) {
		if ( message.getSourceBus() == BusCore.getBusName() )
			return; // no double messages
		if ( message.getDestination().getName() != this->getName() )
			return;

		Message* reply = MPC_busMessageRequest( message, Methods, Log );
		if ( reply == NULL )
			return;

		reply->setSource( this );
		BusDevices.postMessage(reply);
		return;
	 }
	else
		BundleGeneric::busMessage( message, source );
 }

//////////////////////////////////////////////////////////////////////////////////////////////// BUS MESSAGES
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////// GENERATED EVENTS

void PlayerGStreamerBundle::raiseEvent( Fact* fact )
 {
	Message* msg_event = new Message();
	msg_event->setSource( this );
	msg_event->setContent( fact );
	msg_event->setDestinationBroadcast();
	BusDevices.postMessage(msg_event);
 }

//////////////////////////////////////////////////////////////////////////////////////////// GENERATED EVENTS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////// PROPERTY EVENTS

bool PlayerGStreamerBundle::readingProperty( Property* property_curr, const PropertiesProvider* source )
 {
	(void)property_curr; (void)source;

	return true;
 }

bool PlayerGStreamerBundle::updatingProperty( Property* property_new, const Property* property_old, const PropertiesProvider* source )
 {
	(void)source; (void)property_old;
	if ( property_new == NULL ) // property was removed
		return true;

	if ( property_new->getKey() == _Player_KEY_Volume ) {
		string volumeStr = property_new->getValue().getData();

		if (volumeStr.size() == 0)
			return WRET_ERR_PARAM;

		int volume = Utilities::convertString2Integer(volumeStr);
		WRESULT ret = setVolume(volume);
		return WSUCCEEDED(ret);
	 }
	else if ( property_new->getKey() == _Player_KEY_DeviceOutput ) {
		WRESULT ret = setDeviceOutput(property_new->getValue().getData());
		return WSUCCEEDED(ret);
	 }

	return BundleGeneric::updatingProperty( property_new, property_old, source );
 }

///////////////////////////////////////////////////////////////////////////////////////////// PROPERTY EVENTS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////// THREAD EVENTS

void PlayerGStreamerBundle::thread_event( Thread* thread, Thread::THREAD_STATE event )
 {
	long id = 0;
	if ( thread != NULL ) id = thread->getThreadID();
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
/////////////////////////////////////////////////////////////////////////////////////////////// PLAYER EVENTS

void PlayerGStreamerBundle::update_play_state( PlayerGStreamer* source, int playing, int volume, bool muted )
 {
	(void)source;

	if ( playing == 0 )
		Properties.setProperty( _Player_KEY_State, "Idle" );
	else if ( playing == 1 )
		Properties.setProperty( _Player_KEY_State, "Playing" );
	else if ( playing == 2 )
		Properties.setProperty( _Player_KEY_State, "Paused" );
	else
		Properties.setProperty( _Player_KEY_State, "Unknown" );

// deadlock:
//	Properties.setProperty( _Player_KEY_Mute, muted );
//	Properties.setProperty( _Player_KEY_Volume, volume );

 }

void PlayerGStreamerBundle::update_play_file( PlayerGStreamer* source, const string& file_uri, const string& length )
 {
	(void)source;
	Properties.setProperty( _Player_KEY_CurrentFile, file_uri );
	Properties.setProperty( _Player_KEY_CurrentLength, length );

 }

/////////////////////////////////////////////////////////////////////////////////////////////// PLAYER EVENTS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////// PLAYER CONTROL

WRESULT PlayerGStreamerBundle::play() {		return this->playerWorker->play(); }
WRESULT PlayerGStreamerBundle::pause() {	return this->playerWorker->pause(); }
WRESULT PlayerGStreamerBundle::stop() {		return this->playerWorker->stop(); }
WRESULT PlayerGStreamerBundle::clear() {	return this->playerWorker->clear(); }
WRESULT PlayerGStreamerBundle::first() {	return this->playerWorker->first(); }
WRESULT PlayerGStreamerBundle::next() {		return this->playerWorker->next(); }
WRESULT PlayerGStreamerBundle::prev() {		return this->playerWorker->prev(); }
WRESULT PlayerGStreamerBundle::last() {		return this->playerWorker->last(); }

int PlayerGStreamerBundle::getVolume() {			return this->playerWorker->getVolume(); }
bool PlayerGStreamerBundle::isMuted() {				return this->playerWorker->isMuted(); }
bool PlayerGStreamerBundle::isPlaying() {			return this->playerWorker->isPlaying(); }
int PlayerGStreamerBundle::getPlaylistCount() {		return this->playerWorker->getPlayList().size(); }

WRESULT PlayerGStreamerBundle::play( const std::string& file_url ) {		return this->playerWorker->play(file_url); }
WRESULT PlayerGStreamerBundle::enqueue( const std::string& file_url ) {		return this->playerWorker->enqueue(file_url); }

WRESULT PlayerGStreamerBundle::setDeviceOutput( const string& dev_file ) {	return this->playerWorker->setDeviceOutput(dev_file); }
WRESULT PlayerGStreamerBundle::setVolume( int newVolume ) {					return this->playerWorker->setVolume(newVolume); }
WRESULT PlayerGStreamerBundle::setVolumeOffset( int volume_span ) {			return this->playerWorker->setVolumeOffset(volume_span); }

WRESULT PlayerGStreamerBundle::setMute( bool on ) {							return this->playerWorker->setMute(on); }
WRESULT PlayerGStreamerBundle::setPosition( float position_rate ) {			return this->playerWorker->setPosition(position_rate); }
WRESULT PlayerGStreamerBundle::setPositionOffset( float pos_off ) {			return this->playerWorker->setPositionOffset(pos_off); }

////////////////////////////////////////////////////////////////////////////////////////////// PLAYER CONTROL
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////// OTHER METHODS

WRESULT PlayerGStreamerBundle::synchWithPlayer( const string& device_player_name, int flags )
 {
	(void)flags;
	DataList* items = new DataList();
	this->playerWorker->getPlayList().mutex().lockForRead();

	items->add( new Data( this->playerWorker->getPlayListIndex()) );
	items->add( new Data( this->playerWorker->getPositionMs()) );
	items->add( new Data( Utilities::std_time()) );

	std::vector<PlayerItem*>::const_iterator it;
	std::vector<PlayerItem*>::const_iterator it_end = this->playerWorker->getPlayList().stdEnd();
	for ( it=this->playerWorker->getPlayList().stdBegin(); it!=it_end; it++ ) {
		if ( *it == NULL ) continue;
		items->add( new Data( (*it)->file_url ) );
	 }
	this->playerWorker->getPlayList().mutex().unLock();

	Message* message = new Message();
	Request* msg_req = new Request( _Player_METHOD_synch, items );
	message->setSource(this);
	message->setDestinationBroadcast(true);
	message->getDestination().setName(device_player_name);
	message->setContent( msg_req );

	BusDevices.postMessage( message );
	return WRET_OK;
 }

/////////////////////////////////////////////////////////////////////////////////////////////// OTHER METHODS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////// METHODS

Response* PlayerGStreamerBundle::mmDoList( const Request* request )
 {
	if ( request == NULL ) return NULL;
	string option = request->getArgument().getData();
	Log.log( Logger::VERBOSE, ":mmDoList(%s)", option.c_str() );

	if ( option == "s" || option == "short" ) {
		DataList* objs = new DataList();
		this->playerWorker->getPlayList().mutex().lockForRead();
		std::vector<PlayerItem*>::const_iterator it;
		std::vector<PlayerItem*>::const_iterator it_end = this->playerWorker->getPlayList().stdEnd();
		for ( it=this->playerWorker->getPlayList().stdBegin(); it!=it_end; it++ ) {
			if ( *it == NULL ) continue;
			objs->add( new Data((*it)->file_url) );
		}
		this->playerWorker->getPlayList().mutex().unLock();
		return new Response( request->getMethod(), objs );
	 }
	else {
		this->playerWorker->getPlayList().mutex().lockForRead();
		Table* tbl = new Table( this->playerWorker->getPlayList().size_() + 1, 2 );
		tbl->setTableName("PlayList");
		tbl->setHeader(true);
		tbl->set( new Data("Index"), 0, 0);
		tbl->set( new Data("URL"), 0, 1);
		unsigned int iRow = 1;
		std::vector<PlayerItem*>::const_iterator it;
		std::vector<PlayerItem*>::const_iterator it_end = this->playerWorker->getPlayList().stdEnd();
		for ( it=this->playerWorker->getPlayList().stdBegin(); it!=it_end; it++ ) {
			if ( *it == NULL ) continue;
			const PlayerItem* pItem = *it;

			tbl->set( new Data(iRow), iRow, 0);
			tbl->set( new Data(pItem->file_url), iRow, 1);

			++iRow;
		}
		this->playerWorker->getPlayList().mutex().unLock();
		return new Response( request->getMethod(), tbl );
	 }
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

Response* PlayerGStreamerBundle::mmDoEnqueue( const Request* request )
 {
	if ( request == NULL ) return NULL;

	string fileStr ="";
	if ( strcmp( request->getData()->getClassName(), "wosh::Data") == 0 )
		fileStr = request->getArgument().getData();
	else if ( strcmp( request->getData()->getClassName(), "wosh::DataList") == 0 ) {
		const DataList* file_splitted = dynamic_cast<const DataList*>(request->getData());
		file_splitted->join( fileStr, " " );
	 }
	Log.log( Logger::INFO, ":mmDoEnqueue(%s)", fileStr.c_str() );

	WRESULT ret = enqueue(fileStr);

	Response* response = new Response( request->getMethod(), ret );
	return response;
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

Response* PlayerGStreamerBundle::mmDoPlay( const Request* request )
 {
	if ( request == NULL ) return NULL;

	string fileStr ="";
	if ( request->hasData() ) {
		if ( strcmp( request->getData()->getClassName(), "wosh::Data") == 0 )
			fileStr = request->getArgument().getData();
		else if ( strcmp( request->getData()->getClassName(), "wosh::DataList") == 0 ) {
			const DataList* file_splitted = dynamic_cast<const DataList*>(request->getData());
			file_splitted->join( fileStr, " " );
		 }
	 }

	Log.log( Logger::INFO, ":mmDoPlay(%s)", fileStr.c_str() );

	WRESULT ret = play(fileStr);

	Response* response = new Response( request->getMethod(), ret );
	return response;
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

Response* PlayerGStreamerBundle::mmDoSynchWithPlayer( const Request* request )
 {
	if ( request == NULL ) return NULL;
	WRESULT ret = WRET_OK;

	// retrieve options
	if ( strcmp( request->getData()->getClassName(), "wosh::DataList") == 0 ) {
		const DataList* playlist_synch = dynamic_cast<const DataList*>(request->getData());
		if ( playlist_synch->size() < 3 )
			return new Response( request->getMethod(), WRET_ERR_PARAM );

		Log.log( Logger::INFO, ":mmDoSynchWithPlayer() %i items, play %i @ %s", playlist_synch->size(),
																				playlist_synch->get(0).getData().c_str(),
																				playlist_synch->get(1).getData().c_str()  );

		this->playerWorker->getPlayList().mutex().lockForWrite();
		this->playerWorker->getPlayList().free_();
		for ( int it=3; it<playlist_synch->size(); it++ ) {
			this->playerWorker->getPlayList().add_( new PlayerItem(playlist_synch->get(it).getData()) );
		 }
		this->playerWorker->getPlayList().mutex().unLock();

		this->playerWorker->setMute(true);
		this->playerWorker->play( playlist_synch->get(0).toInteger() );
		///@bug long offset = Utilities::std_time() - playlist_synch->get(2).toInteger();
		this->playerWorker->setPositionMs( (unsigned long)playlist_synch->get(1).toLong() );
		this->playerWorker->setMute(false);

	 }
	else if ( strcmp( request->getData()->getClassName(), "wosh::Data") == 0 ) {
		string device = request->getArgument().getData();
		Log.log( Logger::INFO, ":mmDoSynchWithPlayer(%s)", device.c_str() );

		if (device.size() == 0 )
			return new Response( request->getMethod(), WRET_ERR_PARAM );

		ret = synchWithPlayer(device);
	 }

	Response* response = new Response( request->getMethod(), ret );
	return response;
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

Response* PlayerGStreamerBundle::mmDoSetVolume( const Request* request )
 {
	if ( request == NULL ) return NULL;
	// retrieve options
	string volumeStr = request->getArgument().getData();
	Utilities::trimSpaces(volumeStr);
	Log.log( Logger::INFO, ":mmDoSetVolume(%s)", volumeStr.c_str() );
	if ( volumeStr.size() == 0 )
		return new Response( request->getMethod(), WRET_ERR_PARAM );
	WRESULT ret = WRET_OK;

	if (volumeStr.substr(0,1) == "+" || volumeStr.substr(0,1) == "-") {
		int sign = 1;
		if ( volumeStr.substr(0,1) == "-" )
			sign = -1;

		int vol_span = 2;
		if ( volumeStr.size() > 1 ) {
			vol_span = Utilities::convertString2Integer(volumeStr.substr(1));
		 }
		if ( vol_span <= 0 )
			vol_span = 2;
		ret = setVolumeOffset( vol_span * sign );
	 }
	else
		ret = setVolume( Utilities::convertString2Integer(volumeStr) );

	Response* response = new Response( request->getMethod(), ret );
	return response;
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

Response* PlayerGStreamerBundle::mmDoSetMute( const Request* request )
 {
	if ( request == NULL ) return NULL;
	// retrieve options
	string muteStr = request->getArgument().getData();
	Log.log( Logger::INFO, ":mmDoSetMute(%s)", muteStr.c_str() );

	short mute = Utilities::convertString2Bool(muteStr, 2);
	if ( mute != 0 || mute != 1 )
		return new Response( request->getMethod(), WRET_ERR_PARAM );

	WRESULT ret = setMute( (bool)mute );

	Response* response = new Response( request->getMethod(), ret );
	return response;
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

Response* PlayerGStreamerBundle::mmDoSetPosition( const Request* request )
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
