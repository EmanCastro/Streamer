#ifndef PIPELINE_H
#define PIPELINE_H

#include <gst/gst.h>

typedef struct {
        GstElement* pipeline;
        GstElement* source;
        GstElement* sink;
        GstElement* capsfilter;
        GstElement* crop;
        GstBus* bus;
        GstMessage* message;
} Streamer_t;

/**
 * @brief Create a Streamer object
 * 
 * @return Streamer_t* 
 */
Streamer_t* CreateStreamer();

/**
 * @brief Deinitializes the Gstreamer Pipeline
 * 
 * @param streamer 
 * @return int 
 */
int DeInitPipeline(Streamer_t* streamer);

/**
 * @brief Initializes the Gstreamer Pipeline
 * 
 * @param streamer 
 * @param argc 
 * @param argv 
 * @return Streamer_t* 
 */
Streamer_t* InitPipeline(Streamer_t* streamer, int* argc, char** argv);

/**
 * @brief Pause/Resume the Stream
 * 
 * @return int 
 */
int PauseResumeStream();

/**
 * @brief Change the stream pattern of the videotestsrc
 * 
 * @param streamer 
 */
void ChangeStreamPattern(Streamer_t* streamer);

/**
 * @brief Select the stream pattern of the videotestsrc accourding to the value of input
 * 
 * @param streamer 
 * @param input 
 */
void SelectStreamPattern(Streamer_t* streamer, char input);

/**
 * @brief Crop the Stream (current_width-width)x(current_width-height)
 * 
 * @param streamer 
 * @param width 
 * @param height 
 */
void CropStream(Streamer_t* streamer, int width, int height);

#endif