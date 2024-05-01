#include <iostream>
#include <gst/gst.h>
#include <memory>

#include <InputHandler.hpp>


int main(int argc, char** argv) {

    std::shared_ptr<InputHandler::InputHandler> input_handler = std::make_shared<InputHandler::InputHandler>();

    input_handler->StartInput();

    input_handler->EndInput();

}