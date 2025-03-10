#ifndef PIPELINE_HPP
#define PIPELINE_HPP

#include <gst/gst.h>
#include <memory>
#include <PipelineInterface.hpp>

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
        GstBus* bus;
        GstMessage* message;

    private:
        static void OnPadAdded(GstElement *element, GstPad *pad, gpointer data) {
            GstPad *sinkpad;
            GstElement *decode = (GstElement *)data;

            sinkpad = gst_element_get_static_pad(decode, "sink");
            gst_pad_link(pad, sinkpad);
            gst_object_unref(sinkpad);
        }
    };
}

#endif