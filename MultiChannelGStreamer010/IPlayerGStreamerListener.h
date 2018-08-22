/**
 * @class   wosh::devices::IPlayerGStreamerListener
 * @brief   Interface for PlayerGStreamer callbacks (events).
 *
 * @see     PlayerGStreamer
 ****************************************************************************
 * @version $Id: IPlayerGStreamerListener.h 581 2009-09-28 10:58:28Z alex $
 * @author  Alessandro Polo
 * @date    Released on 2009-09-28
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

#ifndef __WOSH_DEVICES_IPlayerGStreamerListener_H__
 #define __WOSH_DEVICES_IPlayerGStreamerListener_H__

 #include <string>

using namespace std;

class PlayerGStreamer;

class IPlayerGStreamerListener  {

	public:

		/**
		 * @brief   Raised when play-state changes.
		 * @param source [in] the source (instance) of the event
		 * @param playing [in] playing status
		 * @param volume [in] volume in range [0:100]
		 * @param muted [in] muted flag
		 */
		virtual void update_play_state( PlayerGStreamer* source, int playing, int volume, bool muted ) = 0;

		/**
		 * @brief   Raised when current playing file changes.
		 * @param source [in] the source (instance) of the event
		 * @param playing [in] playing status
		 * @param volume [in] volume in range [0:100]
		 * @param muted [in] muted flag
		 */
		virtual void update_play_file( PlayerGStreamer* source, const string& file_uri, const string& length ) = 0;


	public:
		virtual ~IPlayerGStreamerListener() { }

}; // class def


#endif //__WOSH_DEVICES_IPlayerGStreamerListener_H__
