#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <Pipeline.h>
#include <gst/gst.h>

#include <Logger.h>

#define MAX_PATTERN_VALUE 25

Streamer_t* CreateStreamer() {

    GstElement *pipeline, *source, *sink, *crop;
    GstBus *bus;
    GstMessage *msg;

    Streamer_t* streamer = malloc(sizeof(Streamer_t));
    streamer->pipeline = pipeline;
    streamer->source = source;
    streamer->sink = sink;
    streamer->crop = crop;
    streamer->bus = bus;
    streamer->message = msg;

    return streamer;
}

static int BuildPipeline(Streamer_t* streamer) {

    gst_bin_add_many (GST_BIN (streamer->pipeline), streamer->source, streamer->crop, streamer->sink, NULL);
    return 0;
}

static int LinkPipeline(Streamer_t* streamer) {

    if (gst_element_link_many (streamer->source, streamer->crop, streamer->sink, NULL) != TRUE) {
        gst_object_unref(streamer->pipeline);
        return -1;
    }
    return 0;
}

static int create_caps_probe(Streamer_t* streamer) {

    GstPad* srcpad = gst_element_get_static_pad(streamer->source, "src");
    if (!srcpad) {
        g_printerr("Failed to get source pad\n");
        return -1;
    }
}

static void init_videocrop_element(GstElement** videocrop) {

    *videocrop = gst_element_factory_make("videocrop", "videocrop");
    g_object_set (*videocrop, "left", 0, NULL);
    g_object_set (*videocrop, "right", 0, NULL);
    g_object_set (*videocrop, "bottom", 0, NULL);
    g_object_set (*videocrop, "top", 0, NULL);
}

Streamer_t* InitPipeline(Streamer_t* streamer, int* argc, char** argv) {

    gst_init(argc, &argv);

    streamer->source = gst_element_factory_make("videotestsrc", "source");
    if (streamer->source == NULL) {
        LOG_DEBUG("Failed to create source element.");
        return NULL;
    }
    g_object_set(streamer->source, "pattern", 0, NULL);

    init_videocrop_element(&streamer->crop);
    if (streamer->crop == NULL) {
        LOG_DEBUG("Failed to create crop element.");
        return NULL;
    }

    streamer->sink = gst_element_factory_make("autovideosink", "sink");
    if (streamer->sink == NULL) {
        LOG_DEBUG("Failed to create sink element.");
        return NULL;
    }
    
    streamer->pipeline = gst_pipeline_new("test_pipeline");
    if (streamer->pipeline == NULL) {
        LOG_DEBUG("Failed to create pipeline element.");
        return NULL;
    }

    if (!streamer->pipeline || !streamer->source || !streamer->sink || !streamer->crop) {
        g_printerr("Not all elements could be created.\n");
        return NULL;
    }

    if (BuildPipeline(streamer) != 0) {
        LOG_DEBUG("Failed to build pipeline");
        return NULL;
    }

    if (LinkPipeline(streamer) != 0) {
        LOG_DEBUG("Failed to link pipeline");
        return NULL;
    }

    gst_element_set_state(streamer->pipeline, GST_STATE_PLAYING);

    streamer->bus = gst_element_get_bus(streamer->pipeline);
    streamer->message = gst_bus_timed_pop_filtered(streamer->bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

    if (GST_MESSAGE_TYPE (streamer->message) == GST_MESSAGE_ERROR) {
        g_error("An error occured\n");
    }

    return streamer;
}

int PauseResumeStream() {
    LOG("resumed/paused stream");
    return 0;
}

void SelectStreamPattern(Streamer_t* streamer, char input) {
    
    gint new_pattern = (gint) input;
    g_object_get(G_OBJECT(streamer->source), "pattern", &new_pattern, NULL);
    
    if (new_pattern >= MAX_PATTERN_VALUE) {
        LOG("Value above permited, defaulting to 0");
        new_pattern = 0;
    }
    else {
        g_object_set(G_OBJECT(streamer->source), "pattern", new_pattern, NULL);
    }
}

void ChangeStreamPattern(Streamer_t* streamer) {
    
    gint current_pattern = 0;
    g_object_get(G_OBJECT(streamer->source), "pattern", &current_pattern, NULL);
    
    if (current_pattern >= MAX_PATTERN_VALUE) {
        current_pattern = 0;
    }
    else {
        current_pattern++;
    }
    g_object_set(G_OBJECT(streamer->source), "pattern", current_pattern, NULL);
}

void CropStream(Streamer_t* streamer, int width, int height) {

    gint g_width = (gint) width;
    gint g_height = (gint) height;

    g_object_set(streamer->crop, "left", g_width, NULL);
    g_object_set(streamer->crop, "bottom", g_height, NULL);
}

int DeInitPipeline(Streamer_t* streamer) {

    gst_message_unref(streamer->message);
    gst_object_unref(streamer->bus);
    gst_element_set_state(streamer->pipeline, GST_STATE_NULL);
    gst_object_unref(streamer->pipeline);

    free(streamer);

    return 0;
}