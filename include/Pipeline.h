#ifndef PIPELINE_H
#define PIPELINE_H

#include <gst/gst.h>

typedef struct {
        GstElement* pipeline;
        GstElement* source;
        GstElement* sink;
        GstElement* crop;
        GstBus* bus;
        GstMessage* message;
} Streamer_t;

Streamer_t* CreateStreamer();

int DeInitPipeline(Streamer_t* streamer);

Streamer_t* InitPipeline(Streamer_t* streamer, int* argc, char** argv);

int PauseResumeStream();

void ChangeStreamPattern(Streamer_t* streamer);

void CropStream(Streamer_t* streamer, int width, int height);

#endif