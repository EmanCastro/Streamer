#include <pthread.h>
#include <InputHandler.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include <Thread.h>
#include <Pipeline.h>
#include <Logger.h>

static void* InputRunnable(void* args) {

    Streamer_t* streamer = (Streamer_t*) args; 

    char input;

    do {
        LOG("Input: ");
        scanf("%c", &input);

        switch (input) {
            case 'p':
                if (PauseResumeStream() != 0) {
                    LOG("Failed to Pause/Resume stream");
                }
            break;

            case 's':
                LOG("Switching input source..");
                if (streamer != NULL){
                    ChangeStreamPattern(streamer);
                }
                else {
                    LOG("Pipeline not yet initialized");
                }
            break;

            case 'v':
                int width=100, height=100;
                LOG("Request to switch viewport size. Insert new values");
                scanf("%d", &width);
                scanf("%d", &height);
                CropStream(streamer, width, height);
                printf("Changed viewport to %dx%d\n", width, height);
            
            default:
                LOG("Unrecognized input");
            break;
        }

    } while (input != 'q');
}

void StartInput(Thread* input_thread, Streamer_t* streamer) {
    InitThread(input_thread, InputRunnable, (void *) streamer);
}

void EndInput(Thread* input_thread) {
    DeInitThread(input_thread);
}
