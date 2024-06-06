#include <iostream>
#include <memory>
#include <thread>
#include <InputHandler.hpp>

using namespace Streamer;

    void InputHandler::InputRunnable() {

        char input;
        int pattern_value;
        std::cout << "InputHandler Running.." << std::endl;
        do {
            std::cout << "Input: ";

            std::cin >> input;
            switch (input) {

                case 'p':
                    this->_streamer->StartStopPipeline();
                    std::cout << "Failed to Pause/Resume stream\n" ;
                    break;

                case 's':
                    std::cout << "Select pattern value\n";
                    std::cin >> pattern_value;

                    if (this->_streamer) {
                        this->_streamer->SelectStreamPattern(pattern_value);
                    }
                    std::cout << "Switching input source..\n";
                    break;

                case 'v':
                    std::cout << "Request to switch viewport size. Insert new values\n";
                    break;

                case 'q':
                    std::cout << "Closing InputHandler..\n";
                    this->_streamer->DeInitPipeline();
                    this->isRunning.store(false);
                    break;

                default:
                    std::cout << "Unrecognized input\n";
                    break;

            }

        } while(isRunning.load());
        
        std::cout << "Closed InputHandler..\n";
    }
   
    void InputHandler::StartInput() {
        this->isRunning.store(true);
        this->input_thread = std::thread([this]{this->InputRunnable();});
    }

    void InputHandler::EndInput() {
        if (input_thread.joinable()) {
            input_thread.join();
        }
    }

