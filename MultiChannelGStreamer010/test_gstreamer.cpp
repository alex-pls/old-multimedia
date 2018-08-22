/**
 * @file    test_PlayerGStreamer.cpp
 * @brief   Test classes: wosh::devices::PlayerGStreamer
 *
 * apt-get install libgstreamer ..
 *
 *
 * @version $Id: test_gstreamer.cpp 435 2009-08-21 02:15:11Z alex $
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
#include <QtDebug>


int simple_init( int argc, char *argv[] )
 {
  const gchar *nano_str;
  guint major, minor, micro, nano;

  gst_init (&argc, &argv);

  gst_version (&major, &minor, &micro, &nano);

  if (nano == 1)
    nano_str = "(CVS)";
  else if (nano == 2)
    nano_str = "(Prerelease)";
  else
    nano_str = "";

  printf ("This program is linked against GStreamer %d.%d.%d %s\n",
          major, minor, micro, nano_str);

  return 0;
 }

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

int goption_init( int argc, char *argv[] )
 {
  gboolean silent = FALSE;
  gchar *savefile = NULL;
  GOptionContext *ctx;
  GError *err = NULL;
  GOptionEntry entries[] = {
    { "silent", 's', 0, G_OPTION_ARG_NONE, &silent,
      "do not output status information", NULL },
    { "output", 'o', 0, G_OPTION_ARG_STRING, &savefile,
      "save xml representation of pipeline to FILE and exit", "FILE" },
    { NULL }
  };

  /* we must initialise the threading system before using any
   * other GLib funtion, such as g_option_context_new() */
  if (!g_thread_supported ())
    g_thread_init (NULL);

  ctx = g_option_context_new ("- Your application");
  g_option_context_add_main_entries (ctx, entries, NULL);
  g_option_context_add_group (ctx, gst_init_get_option_group ());
  if (!g_option_context_parse (ctx, &argc, &argv, &err)) {
    g_print ("Failed to initialize: %s\n", err->message);
    g_error_free (err);
    return 1;
  }

  printf ("Run me with --help to see the Application options appended.\n");

  return 0;
 }

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

int element_test ( int argc, char *argv[] )
 {
  GstElement *element;

  /* init GStreamer */
  gst_init (&argc, &argv);

  /* create element */
  element = gst_element_factory_make ("fakesrc", "source");
  if (!element) {
    g_print ("Failed to create element of type 'fakesrc'\n");
    return -1;
  }

  /* get name */
  gchar *name;
  g_object_get (G_OBJECT (element), "name", &name, NULL);
  g_print ("The name of the element is '%s'.\n", name);
  g_free (name);

  gst_object_unref (GST_OBJECT (element));
  
  return 0;
 }

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
static gboolean
bus_call (GstBus     *bus,
          GstMessage *msg,
          gpointer    data)
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

int play_file ( int argc, char *argv[] )
 {
  /* make sure we have a URI */
  if (argc != 2) {
    g_print ("Usage: %s <URI>\n", argv[0]);
    return -1;
  }
  GMainLoop *loop;

  GstElement *pipeline, *music_player, *decoder, *resampler, *sink;
  GstBus *bus;

  /* Initialisation */
  gst_init (&argc, &argv);

  pipeline = gst_pipeline_new ("pipeline");
  loop = g_main_loop_new (NULL, FALSE);

   bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
  // gst_bus_add_watch (bus, my_bus_callback, loop);
   gst_bus_add_watch (bus, bus_call, loop);
   gst_object_unref (bus);
   
music_player = gst_element_factory_make( "playbin", "music-player" );
g_object_set (G_OBJECT (music_player), "volume", 0.9, NULL);
//g_object_set (G_OBJECT (music_player), "uri", "file:///shared/DM2002.wav", NULL);
g_object_set (G_OBJECT (music_player), "uri", "file:///shared/DM2002.mp3", NULL);

  sink = gst_element_factory_make ("alsasink", "sink");
  g_object_set (G_OBJECT (sink), "device", "play0", NULL);

  g_object_set (G_OBJECT (music_player), "audio-sink", sink, NULL);

  gst_bin_add (GST_BIN (pipeline), music_player);


  /* Set the pipeline to "playing" state*/
  g_print ("Now playing: %s\n", argv[1]);
  gst_element_set_state (pipeline, GST_STATE_PLAYING);


  /* Iterate */
  g_print ("Running...\n");
  g_main_loop_run (loop);


  /* Out of the main loop, clean up nicely */
  g_print ("Returned, stopping playback\n");
  gst_element_set_state (pipeline, GST_STATE_NULL);

  g_print ("Deleting pipeline\n");
  gst_object_unref (GST_OBJECT (pipeline));

  return 0;
 }

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
GstElement *audio;

static void
cb_newpad (GstElement *decodebin,
	   GstPad     *pad,
	   gboolean    last,
	   gpointer    data)
{
  GstCaps *caps;
  GstStructure *str;
  GstPad *audiopad;

  // only link once
  audiopad = gst_element_get_pad (audio, "sink");
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


int play_file2 ( int argc, char *argv[] )
 {
  /* make sure we have input */
  if (argc != 3) {
    g_print ("Usage: %s <filename> <alsa-device>\n", argv[0]);
    return -1;
  }

  GstElement *pipeline;

  GMainLoop *loop;
  GstElement *src, *dec, *conv, *sink;
  GstPad *audiopad;
  GstBus *bus;

  /* init GStreamer */
  gst_init (&argc, &argv);
  loop = g_main_loop_new (NULL, FALSE);

  /* setup */
  pipeline = gst_pipeline_new ("pipeline");

   bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
  // gst_bus_add_watch (bus, my_bus_callback, loop);
   gst_bus_add_watch (bus, bus_call, loop);
   gst_object_unref (bus);

  src = gst_element_factory_make ("filesrc", "source");
  g_object_set (G_OBJECT (src), "location", argv[1], NULL);
  dec = gst_element_factory_make ("decodebin", "decoder");
  g_signal_connect (dec, "new-decoded-pad", G_CALLBACK (cb_newpad), NULL);
  gst_bin_add_many (GST_BIN (pipeline), src, dec, NULL);
  gst_element_link (src, dec);

  /* create audio output */
  audio = gst_bin_new ("audiobin");
  conv = gst_element_factory_make ("audioresample", "ares");
  audiopad = gst_element_get_pad (conv, "sink");
  sink = gst_element_factory_make ("alsasink", "sink");
  g_object_set (G_OBJECT (sink), "device", argv[2], NULL);

  gst_bin_add_many (GST_BIN (audio), conv, sink, NULL);
  gst_element_link (conv, sink);
  gst_element_add_pad (audio, gst_ghost_pad_new ("sink", audiopad));
  gst_object_unref (audiopad);
  gst_bin_add (GST_BIN (pipeline), audio);

  /* run */
  gst_element_set_state (pipeline, GST_STATE_PLAYING);

  g_main_loop_run (loop);

  /* cleanup */
  gst_element_set_state (pipeline, GST_STATE_NULL);
  gst_object_unref (GST_OBJECT (pipeline));

  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////




GstElement *audio2;
GstElement *audio2b;

static void
cb_newpad2 (GstElement *decodebin,
	   GstPad     *pad,
	   gboolean    last,
	   gpointer    data)
{
  GstCaps *caps;
  GstStructure *str;
  GstPad *audiopad;

  // only link once
  if ( audio2b != NULL ) {
  qDebug() << "cb_newpad2:: using audio2b";
	audiopad = gst_element_get_pad (audio2b, "sink");
  }
  else {
	qDebug() << "cb_newpad2:: using audio2";
	audiopad = gst_element_get_pad (audio2, "sink");
  }

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

int pipe_play ( GstElement *pipeline, GstElement** audio, char * file, char * device )
 {
  GstElement *src, *dec, *conv, *sink;
  GstPad *audiopad;

  src = gst_element_factory_make ("filesrc", "source");
  g_object_set (G_OBJECT (src), "location", file, NULL);
  dec = gst_element_factory_make ("decodebin", "decoder");
  g_signal_connect (dec, "new-decoded-pad", G_CALLBACK (cb_newpad2), NULL);
  gst_bin_add_many (GST_BIN (pipeline), src, dec, NULL);
  gst_element_link (src, dec);

  /* create audio output */
  *audio = gst_bin_new ("audiobin");
  conv = gst_element_factory_make ("audioresample", "ares");
  audiopad = gst_element_get_pad (conv, "sink");
  sink = gst_element_factory_make ("alsasink", "sink");
  g_object_set (G_OBJECT (sink), "device", device, NULL);

  gst_bin_add_many (GST_BIN (*audio), conv, sink, NULL);
  gst_element_link (conv, sink);
  gst_element_add_pad (*audio, gst_ghost_pad_new ("sink", audiopad));
  gst_object_unref (audiopad);
  gst_bin_add (GST_BIN (pipeline), *audio);
  
  return 0;
 }

///////////////////////////////////////////////////////////////////////////////////////////////////

int play_files ( int argc, char *argv[] )
 {
  /* make sure we have input */
  if (argc != 5) {
    g_print ("Usage: %s <filename> <alsa-device> <filename> <alsa-device>\n", argv[0]);
    return -1;
  }

  GstElement *pipeline, *pipeline2;
  GMainLoop *loop;
  GstBus *bus, *bus2;

audio2 = NULL;
audio2b = NULL;

  /* init GStreamer */
  gst_init (NULL, NULL);
  loop = g_main_loop_new (NULL, FALSE);

  /* setup */
  pipeline = gst_pipeline_new ("pipeline");
  pipeline2 = gst_pipeline_new ("pipeline2");

   bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
  // gst_bus_add_watch (bus, my_bus_callback, loop);
   gst_bus_add_watch (bus, bus_call, loop);
   gst_object_unref (bus);

   bus2 = gst_pipeline_get_bus (GST_PIPELINE (pipeline2));
  // gst_bus_add_watch (bus, my_bus_callback, loop);
   gst_bus_add_watch (bus2, bus_call, loop);
   gst_object_unref (bus2);

	pipe_play ( pipeline, &audio2, argv[1], argv[2] );
	sleep(1);

	qDebug() << "here0";
	pipe_play ( pipeline2, &audio2b, argv[3], argv[4] );
	qDebug() << "here1";

  qDebug() << "Setting PLAY to playlist 1";
  gst_element_set_state (pipeline, GST_STATE_PLAYING);
  qDebug() << "Setting PLAY to playlist 2";
  gst_element_set_state (pipeline2, GST_STATE_PLAYING);

  qDebug() << "Entering Loop..";
  g_main_loop_run (loop);
  qDebug() << "Exit Loop.";

  /* cleanup */
  gst_element_set_state (pipeline, GST_STATE_NULL);
  gst_object_unref (GST_OBJECT (pipeline));

  gst_element_set_state (pipeline2, GST_STATE_NULL);
  gst_object_unref (GST_OBJECT (pipeline2));
  
  return 0;
 }

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

int main ( int argc, char *argv[] )
 {
//	simple_init(argc, argv);

// not working?	goption_init(argc, argv);
// ok	element_test(argc, argv);

// not working play_file(argc, argv);
	play_file(argc, argv);

//  play_files(argc, argv);
 }


