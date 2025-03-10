#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <iostream>
#include <memory>
#include <thread>
#include <atomic>
#include <InputHandlerInterface.hpp>
#include <Pipeline.hpp>

namespace Streamer {

    class InputHandler : protected InputHandlerInterface {
    public:

        void StartInput() override;
        void EndInput() override;

        InputHandler() {
            isRunning = false;
        };
        InputHandler(std::shared_ptr<Pipeline> streamer) : streamer_(streamer) {
            isRunning = false;
        }

    private:
        std::shared_ptr<Pipeline> streamer_;
        void InputRunnable();
    };
}

#endif