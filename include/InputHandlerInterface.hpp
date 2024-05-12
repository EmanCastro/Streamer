#ifndef INPUT_HANDLER_INTERFACE_HPP
#define INPUT_HANDLER_INTERFACE_HPP

#include <iostream>
#include <memory>
#include <thread>
#include <atomic>

namespace Streamer {
class InputHandlerInterface {
public:

    virtual void StartInput() = 0;
    virtual void EndInput() = 0;

protected:

    std::thread input_thread;
    std::atomic<bool> isRunning;
};
}

#endif