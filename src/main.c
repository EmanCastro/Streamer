#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <gst/gst.h>
#include <stdlib.h>

#include <Logger.h>
#include <Pipeline.h>
#include <InputHandler.h>
#include <Thread.h>


int main(int argc, char** argv) {

    char* param = NULL;
    if (argc > 1) {
        param = argv[1];
    }    

    if (param != NULL) {
        LOG(param);
    }

    Thread* input_thread = malloc(sizeof(Thread));
    Streamer_t* streamer = CreateStreamer();
    
    StartInput(input_thread, streamer);
    InitPipeline(streamer, &argc, argv);

    EndInput(input_thread);
    DeInitPipeline(streamer);
}