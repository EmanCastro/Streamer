#include <iostream>
#include <memory>
#include <thread>
#include <InputHandler.hpp>

using namespace Streamer;

    void InputHandler::InputRunnable() {

        char input;
        int pattern_value;
        int width;
        int height;
        std::cout << "InputHandler Running.." << std::endl;
        do {
            std::cout << "Input: ";

            std::cin >> input;
            switch (input) {

                case 'p':
                    streamer_->StartStopPipeline();
                    break;

                case 's':
                    std::cout << "Select pattern value\n";
                    std::cin >> pattern_value;

                    if (streamer_) {
                        streamer_->SelectStreamPattern(pattern_value);
                    }
                    std::cout << "Switching input source..\n";
                    break;

                case 'v':
                    std::cout << "Request to switch viewport size. Insert new values\n";
                    std::cin >> width;
                    std::cin >> height;
                    streamer_->CropStream(width, height);
                    break;

                case 'q':
                    std::cout << "Closing InputHandler..\n";
                    streamer_->DeInitPipeline();
                    isRunning.store(false);
                    break;

                default:
                    std::cout << "Unrecognized input\n";
                    break;

            }

        } while(isRunning.load());
        
        std::cout << "Closed InputHandler..\n";
    }
   
    void InputHandler::StartInput() {
        isRunning.store(true);
        input_thread = std::thread([this]{InputRunnable();});
    }

    void InputHandler::EndInput() {
        if (input_thread.joinable()) {
            input_thread.join();
        }
    }

