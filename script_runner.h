#ifndef SCRIPT_RUNNER_H
#define SCRIPT_RUNNER_H

#include "window_manager.h"
#include <string>
#include <vector>

class ScriptRunner {
public:
    // Constructor to initialize with the path to the external script and other parameters
    ScriptRunner(const std::string& script_path, int window_width, int window_height, const std::string& gpu_type);

    // Method to run the external script and capture its output
    void run_script(const std::string& command);

    // Method to return the parsed pixel array
    const std::vector<Pixel>& get_pixel_array() const;

    // Method to get the current frame count
    int get_frame_count() const;

    // Method to reset the frame count
    void reset_frame_count();

private:
    std::string script_path;         // Path to the external script
    int window_width;                // Width of the window
    int window_height;               // Height of the window
    std::string gpu_type;            // Type of GPU
    std::vector<Pixel> pixel_array;  // Pixel array to store the output
    int frame_count;                 // Frame count to keep track of frames

    // Method to execute the command and capture its output
    std::string execute_command(const std::string& command);

    // Method to parse the output from the external script into pixel data
    void parse_output(const std::string& output);

    // Method to handle errors
    void handle_errors(const std::string& error);
};

#endif // SCRIPT_RUNNER_H
