#ifndef PIPELINE_INTERFACE_HPP
#define PIPELINE_INTERFACE_HPP

#include <gst/gst.h>

namespace Streamer {
    class PipelineInterface {

    public:

        virtual void InitPipeline(int& argc, char** argv) = 0;
        virtual void DeInitPipeline() = 0;

    private:

    };
}

#endif