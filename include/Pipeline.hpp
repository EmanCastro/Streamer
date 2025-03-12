#ifndef PIPELINE_HPP
#define PIPELINE_HPP

#include <gst/gst.h>
#include <memory>
#include <PipelineInterface.hpp>
#include <qlogger.h>

#define MAX_PATTERN_VALUE 25

namespace Streamer {
    class Pipeline: public PipelineInterface {

    public:

        void InitPipeline(int& argc, char** argv);
        void DeInitPipeline();

        void StartStopPipeline();
        void ChangeStreamPattern();
        void InitVideoFilePipeline();
        void InitTestSrcPipeline();
        void SelectStreamPattern(int& input);
        void CropStream(int& width, int& height);

        GstElement* pipeline;
        GstElement* source;
        GstElement* sink;
        GstElement* capsfilter;
        GstElement* crop;
        GstElement* demux;
        GstElement* decoder;
        GstElement* videoscale;
        GstBus* bus;
        GstMessage* message;
        GMainLoop *main_loop;

    private:
        /**
         * TODO: this function is no longer only for demuxer<-> decoder pad added
         * decoder <-> autovideosink is also using this callback so it should be
         * modified accordingly 
         */
        static void OnPadAdded(GstElement *element, GstPad *pad, gpointer data) {
            GstPad *sinkpad;
            GstElement *decoder = (GstElement *)data;
            QLOG("Pad called.");

            GstCaps *new_pad_caps = gst_pad_get_current_caps(pad);
            GstStructure *new_pad_struct = gst_caps_get_structure(new_pad_caps, 0);
            const gchar *new_pad_type = gst_structure_get_name(new_pad_struct);
            QLOG("New pad type: {}", new_pad_type);

            if (g_str_has_prefix(new_pad_type, "video/x-h264") || g_str_has_prefix(new_pad_type, "video/x-raw")) {
                sinkpad = gst_element_get_static_pad(decoder, "sink");
                if (gst_pad_link(pad, sinkpad) != GST_PAD_LINK_OK) {
                    QLOG("Failed to link demux pad to decoder sink pad.");
                }
                QLOG("Pad added.");
                gst_object_unref(sinkpad);
            }

            gst_caps_unref(new_pad_caps);
        }
    };
}

#endif