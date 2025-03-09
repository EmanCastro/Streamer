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
        void SelectStreamPattern(int& input);
        void CropStream(int& width, int& height);

        GstElement* pipeline;
        GstElement* source;
        GstElement* sink;
        GstElement* capsfilter;
        GstElement* crop;
        GstBus* bus;
        GstMessage* message;

    private:

    };
}

#endif