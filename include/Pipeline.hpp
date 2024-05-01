#ifndef PIPELINE_HPP
#define PIPELINE_HPP

#include <gst/gst.h>
#include <PipelineInterface.hpp>

namespace Pipeline {
    class Pipeline: public PipelineInterface {

    public:

        void InitPipeline();
        void DeInitPipeline();

        void PauseResumeStream();
        void ChangeStreamPattern();
        void SelectStreamPattern();
        void CropStream();

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