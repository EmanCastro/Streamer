#include <iostream>
#include <gst/gst.h>
#include <memory>

#include <InputHandler.hpp>
#include <Pipeline.hpp>


int main(int argc, char** argv) {


    std::shared_ptr<Streamer::Pipeline> pipeline = std::make_shared<Streamer::Pipeline>();
    pipeline->InitPipeline(argc, argv);

    std::shared_ptr<Streamer::InputHandler> input_handler = std::make_shared<Streamer::InputHandler>(pipeline);
    input_handler->StartInput();
    
    input_handler->EndInput();
}