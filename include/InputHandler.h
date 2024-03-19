#include <Thread.h>
#include <Pipeline.h>

/**
 * @brief Wrapper function for starting the custom thread from the input handler 
 * 
 * @param input_thread 
 * @param streamer 
 */
void StartInput(Thread* input_thread, Streamer_t* streamer);

/**
 * @brief Wrapper function for terminating the custom thread from the input handler
 * 
 * @param input_thread 
 */
void EndInput(Thread* input_thread);