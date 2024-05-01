#ifndef PIPELINE_INTERFACE_HPP
#define PIPELINE_INTERFACE_HPP

#include <gst/gst.h>

namespace Pipeline {
    class PipelineInterface {

    public:

        virtual void InitPipeline() = 0;
        virtual void DeInitPipeline() = 0;

    private:

    };
}

#endif