#include <iostream>
#include <memory>
#include <thread>

#include <Pipeline.hpp>
#include <gst/gst.h>

using namespace Streamer;

void Pipeline::InitPipeline(int& argc, char** argv) {

    gst_init(&argc, &argv);

    this->source = gst_element_factory_make("videotestsrc", "source");
    if (this->source == nullptr)
        GST_DEBUG("Failed to create source element.");

    this->crop = gst_element_factory_make("videocrop", "videocrop");
    g_object_set(this->crop, "left", 0, NULL);
    g_object_set(this->crop, "right", 0, NULL);
    g_object_set(this->crop, "bottom", 0, NULL);
    g_object_set(this->crop, "top", 0, NULL);

    this->sink = gst_element_factory_make("autovideosink", "sink");
    if (this->sink == nullptr)
        GST_DEBUG("Failed to create sink element");

    this->pipeline = gst_pipeline_new("test_pipeline");
    if (this->pipeline == nullptr)
        GST_DEBUG("Failed to create pipeline");

    gst_bin_add_many(GST_BIN(this->pipeline), this->source, this->crop, this->sink, NULL);
    gst_element_link_many(this->source, this->crop, this->sink, NULL);
}

void Pipeline::StartStopPipeline() {

    gst_element_set_state(this->pipeline, GST_STATE_PLAYING);
}

void Pipeline::SelectStreamPattern(char input) {

    gint new_pattern = (gint) input;

    if (new_pattern >= MAX_PATTERN_VALUE) {
        GST_DEBUG("Pattern value out of range, defaulting to 0");
        new_pattern = 0;
    }

    g_object_set(G_OBJECT(this->source), "pattern", new_pattern, NULL);
}


void Pipeline::CropStream(int width, int height) {

    gint g_width = static_cast<gint>(width);
    gint g_height = static_cast<gint>(height);

    g_object_set(this->crop, "left", g_width, NULL);
    g_object_set(this->crop, "right", g_height, NULL);
}

void Pipeline::DeInitPipeline() {

    gst_message_unref(this->message);
    gst_object_unref(this->bus);
    gst_element_set_state(this->pipeline, GST_STATE_NULL);
    gst_object_unref(this->pipeline);
}

//void Pipeline::SelectStreamPattern(){}
//void Pipeline::CropStream(){}

