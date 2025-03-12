#include <iostream>
#include <memory>
#include <thread>

#include <Pipeline.hpp>
#include <qlogger.h>
#include <gst/gst.h>

using namespace Streamer;

void Pipeline::InitPipeline(int& argc, char** argv) {
    gst_init(&argc, &argv);
    main_loop = g_main_loop_new(NULL, FALSE);
    // TODO: fix this poor excuse of a pipeline switcher
    if (true) {
        GST_DEBUG("Init Video File Pipeline.");
        InitVideoFilePipeline();
    }
    else {
        GST_DEBUG("Init Test Source Pipeline.");
        InitTestSrcPipeline();
    }
}

void Pipeline::InitVideoFilePipeline() {
    source = gst_element_factory_make("filesrc", "source");
    if (!source)
        GST_ERROR("Failed to create source element.");
    g_object_set(source, "location", "/home/eman/Dev/Streamer2/bench_press.mkv", NULL);

    demux = gst_element_factory_make("matroskademux", "demux");
    if (!demux)
        GST_ERROR("Failed to create demux element.");

    decoder = gst_element_factory_make("decodebin", "decode");
    if (!decoder)
        GST_ERROR("Failed to create decode element.");

    videoscale = gst_element_factory_make("videoscale", "videoscale");
    if (!videoscale)
        GST_ERROR("Failed to create videoscale element.");

    capsfilter = gst_element_factory_make("capsfilter", "capsfilter");
    if (!capsfilter)
        GST_ERROR("Failed to create capsfilter element.");

    GstCaps *caps = gst_caps_new_simple("video/x-raw",
                                        "width", G_TYPE_INT, 500,
                                        "height", G_TYPE_INT, 500,
                                        NULL);
    g_object_set(capsfilter, "caps", caps, NULL);
    gst_caps_unref(caps);

    gst_bin_add_many(GST_BIN(pipeline), videoscale, capsfilter, NULL);
    gst_element_link_many(decoder, videoscale, capsfilter, sink, NULL);
    sink = gst_element_factory_make("autovideosink", "sink");
    if (!sink)
        GST_ERROR("Failed to create sink element");

    pipeline = gst_pipeline_new("videofile_pipeline");
    if (!pipeline)
        GST_ERROR("Failed to create pipeline");

    gst_bin_add_many(GST_BIN(pipeline), source, demux, decoder, videoscale, capsfilter, sink, NULL);

    // link beginning of pipeline
    gst_element_link(source, demux);
    // link end of pipeline
    gst_element_link_many(videoscale, capsfilter, sink, NULL);

    g_signal_connect(demux, "pad-added", G_CALLBACK(OnPadAdded), decoder);
    g_signal_connect(decoder, "pad-added", G_CALLBACK(OnPadAdded), videoscale);
}

void Pipeline::InitTestSrcPipeline() {
    source = gst_element_factory_make("videotestsrc", "source");
    if (source == nullptr)
        GST_ERROR("Failed to create source element.");

    crop = gst_element_factory_make("videocrop", "videocrop");
    g_object_set(crop, "left", 0, NULL);
    g_object_set(crop, "right", 0, NULL);
    g_object_set(crop, "bottom", 0, NULL);
    g_object_set(crop, "top", 0, NULL);

    sink = gst_element_factory_make("autovideosink", "sink");
    if (sink == nullptr)
        GST_ERROR("Failed to create sink element");

    pipeline = gst_pipeline_new("test_pipeline");
    if (pipeline == nullptr)
        GST_ERROR("Failed to create pipeline");

    gst_bin_add_many(GST_BIN(pipeline), source, crop, sink, NULL);
    gst_element_link_many(source, crop, sink, NULL);
}

void Pipeline::StartStopPipeline() {
    GstState state;
    GstStateChangeReturn ret;
    gst_element_get_state(pipeline, &state, NULL, GST_CLOCK_TIME_NONE);

    if (state == GST_STATE_PLAYING) {
        ret = gst_element_set_state(pipeline, GST_STATE_PAUSED);
    } else {
        ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
    }

    if (ret == GST_STATE_CHANGE_FAILURE) {
        GST_ERROR("Failed to set pipeline to PLAYING state.");
    }
}

void Pipeline::SelectStreamPattern(int &input) {
    if (input >= MAX_PATTERN_VALUE) {
        GST_DEBUG("Pattern value out of range, defaulting to 0");
        input = 0;
    }
    g_object_set(G_OBJECT(source), "pattern", static_cast<gint>(input), NULL);
}


void Pipeline::CropStream(int& width, int& height) {
    gint g_width = static_cast<gint>(width);
    gint g_height = static_cast<gint>(height);

    g_object_set(crop, "right", g_width, NULL);
    g_object_set(crop, "top", g_height, NULL);
}

void Pipeline::DeInitPipeline() {
    gst_message_unref(message);
    gst_object_unref(bus);
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);
}
