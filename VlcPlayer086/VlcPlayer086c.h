/**
 * @class   wosh::devices::VlcPlayer086c
 * @brief   
 *
 * @note    
 *
 *
 * apt-get install libvlc0-dev
 *
 *
 ****************************************************************************
 * @version $Id: VlcPlayer086c.h 505 2009-09-13 23:51:17Z alex $
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

#ifndef __WOSH_DEVICES_VlcPlayer086c_H__
 #define __WOSH_DEVICES_VlcPlayer086c_H__

 #include <woshDefs.h>
 #include <core/Mutex.h>
 #include <core/ThreadWorker.h>

 #include "VlcPlayer.h"
 #include "IVlcPlayerListener.h"

 #include <map>
 #include <vlc/libvlc.h>

 #include <QtDebug>
 
using namespace std;
namespace wosh {
 namespace devices {

class VlcPlayer086c : public ThreadWorker, public VlcPlayer  {

	public:

		/**
		 * @brief   Default constructor. Init vars.
		 */
		VlcPlayer086c();

		/**
		 * @brief   Deconstructor. If thread is stll running, it will be stopped.
		 */
		virtual ~VlcPlayer086c();


/** @name Setters
 * @{
 ******************************************************************************/
	public:

		/**
		 * @brief   Set the IVlcPlayerListener interface for callbacks.
		 * @param listener [in] pointer to object which implements callback-functions
		 * @note    Call this method only once, after creation, it's not reetrant!
		 */
		void setPlayerListener( IVlcPlayerListener* listener );

//@}
/** @name Getters
 * @{
 ******************************************************************************/
	public:

		virtual int getVolume();
		virtual bool isPlaying();
		virtual bool isMuted();
		virtual int getPlaylistCount();


		virtual WRESULT getVLC_Info( std::map<std::string, std::string>& fields );


		virtual WRESULT setVlcArguments( const string& arguments_line );



		/**
		 * @brief   Get IVlcPlayerListener interface class for callbacks.
		 * @return  pointer to object which implements callback-functions
		 */
		IVlcPlayerListener* getPlayerListener();

//@}
/** @name Player Interface
 * @{
 ******************************************************************************/
	public:

		virtual WRESULT play( const std::string& file_url );
		virtual WRESULT enqueue( const std::string& file_url );

		virtual WRESULT pause();
		virtual WRESULT stop();

		virtual WRESULT next();
		virtual WRESULT prev();

		virtual WRESULT clear();

		virtual WRESULT setVolume( int newVolume );
		virtual WRESULT setVolumeOffset( int volume_span );
		virtual WRESULT setMute( bool on );
		
		virtual WRESULT setFullScreen( bool on );
		virtual WRESULT setVideoResize( int width, int height );

		virtual WRESULT getSnapshot( const string& output_file );
		
		virtual WRESULT setPosition( float position_rate );
		virtual WRESULT setPositionOffset( float position_rate_offset );


		virtual WRESULT updateInfo();

//@}
/** @name Internal methods
 * @{
 ******************************************************************************/
	protected:

		/**
		 * @brief   Perform periodic checkConnected() to update stats.
		 * @see     running
		 * @see     autoRefreshFrequency
		 */
		virtual void runThread();


		void raise(libvlc_exception_t * ex);

//@}

	protected:

		char** vlc_argv;
		int vlc_argc;

		IVlcPlayerListener* playerListener;	///< callbacks for stats (such as VlcPlayerBundle*)
		MutexRW configMux;					///< Mutex of configuration (previous vars)

		bool _isPlaying;

 
	private:

		libvlc_instance_t * _vlcinstance;
		libvlc_exception_t _vlcexcep;


}; // class def

 }; // namespace devices
}; // namespace wosh

#endif //__WOSH_DEVICES_VlcPlayer086c_H__
