#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <iostream>
#include <memory>
#include <thread>
#include <atomic>
#include <InputHandlerInterface.hpp>

namespace InputHandler {
    class InputHandler : protected InputHandlerInterface {
    public:

        void StartInput() override;
        void EndInput() override;

        InputHandler() {
            isRunning = false;
        };

    private:

        void InputRunnable();
    };
}

#endif