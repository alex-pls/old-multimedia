/**
 * @file    test_PlayerGStreamer.cpp
 * @brief   Test classes: wosh::devices::PlayerGStreamer
 *
 * apt-get install libgstreamer ..
 *
 *
 * @version $Id: test_gstreamer.multitrack-play.cpp 435 2009-08-21 02:15:11Z alex $
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

#include <gst/gst.h>
#include <unistd.h>
#include <map>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
std::map<GstElement*, GstElement*> decodeBinMap; // decodeBin => audio

static gboolean bus_call (GstBus *bus, GstMessage *msg, gpointer data)
{
  GMainLoop *loop = (GMainLoop *) data;

  switch (GST_MESSAGE_TYPE (msg)) {

    case GST_MESSAGE_EOS:
      g_print ("End of stream\n");
      g_main_loop_quit (loop);
      break;

    case GST_MESSAGE_ERROR: {
      gchar  *debug;
      GError *error;

      gst_message_parse_error (msg, &error, &debug);
      g_free (debug);

      g_printerr ("Error: %s\n", error->message);
      g_error_free (error);

      g_main_loop_quit (loop);
      break;
    }
    default:
      break;
  }

  return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////


static void cb_newpad2 (GstElement *decodebin, GstPad *pad, gboolean last, gpointer data)
{
  GstCaps *caps;
  GstStructure *str;
  GstPad *audiopad;

audiopad = gst_element_get_pad (decodeBinMap[decodebin], "sink");

  if (GST_PAD_IS_LINKED (audiopad)) {
    g_object_unref (audiopad);
    return;
  }

  // check media type 
  caps = gst_pad_get_caps (pad);
  str = gst_caps_get_structure (caps, 0);
  if (!g_strrstr (gst_structure_get_name (str), "audio")) {
    gst_caps_unref (caps);
    gst_object_unref (audiopad);
    return;
  }
  gst_caps_unref (caps);

  /* link'n'play */
  gst_pad_link (pad, audiopad);
}

class ChannelPlayer
 {
 
	public:

		GstElement *pipeline;

		char* file;
		char* device;


		ChannelPlayer()
		 {
			this->pipeline = NULL;
			this->file = NULL;
			this->device = NULL;
		 }
 
		virtual ~ChannelPlayer()
		 {
			if ( this->pipeline == NULL )
				return;

			gst_element_set_state (this->pipeline, GST_STATE_NULL);
			gst_object_unref (GST_OBJECT (this->pipeline));

		 }


		void create_pipeline( GMainLoop *loop )
		 {
			this->pipeline = gst_pipeline_new ("pipeline");

			GstBus * bus = gst_pipeline_get_bus (GST_PIPELINE (this->pipeline));
			gst_bus_add_watch (bus, bus_call, loop);
			gst_object_unref (bus);
		 }

		void create_elements()
		 {
			if ( this->pipeline == NULL )
				return;

			GstElement *src, *dec, *conv, *sink;
			GstElement * audio = NULL;
			GstPad *audiopad;

			src = gst_element_factory_make ("filesrc", "source");
			g_object_set (G_OBJECT (src), "location", file, NULL);
			dec = gst_element_factory_make ("decodebin", "decoder");
			g_signal_connect (dec, "new-decoded-pad", G_CALLBACK (cb_newpad2), NULL);
			gst_bin_add_many (GST_BIN (this->pipeline), src, dec, NULL);
			gst_element_link (src, dec);

			audio = gst_bin_new ("audiobin");
			conv = gst_element_factory_make ("audioresample", "ares");
			audiopad = gst_element_get_pad (conv, "sink");
			sink = gst_element_factory_make ("alsasink", "sink");
			g_object_set (G_OBJECT (sink), "device", device, NULL);

			decodeBinMap[dec] = audio;

			gst_bin_add_many (GST_BIN (audio), conv, sink, NULL);
			gst_element_link (conv, sink);
			gst_element_add_pad (audio, gst_ghost_pad_new ("sink", audiopad));
			gst_object_unref (audiopad);
			gst_bin_add (GST_BIN (this->pipeline), audio);
		 }






		void play()
		 {
			if ( this->pipeline == NULL )
				return;
			gst_element_set_state (this->pipeline, GST_STATE_PLAYING);
		 }




 };

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////



int main ( int argc, char *argv[] )
{
	/* make sure we have input */
	if (argc != 5) {
		g_print ("Usage: %s <filename> <alsa-device> <filename> <alsa-device>\n", argv[0]);
		return -1;
	}

	GMainLoop *loop;

	/* init GStreamer */
	gst_init (NULL, NULL);
	loop = g_main_loop_new (NULL, FALSE);

	ChannelPlayer player1;
	player1.file = argv[1];
	player1.device = argv[2];
	player1.create_pipeline(loop);
	player1.create_elements();

	ChannelPlayer player2;
	player2.file = argv[3];
	player2.device = argv[4];
	player2.create_pipeline(loop);
	player2.create_elements();

	player1.play();
	player2.play();

	g_main_loop_run (loop);

	return 0;
}
