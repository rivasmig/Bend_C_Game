#include "script_runner.h"
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <cstdio>
#include <memory>
#include <iostream>
#include <array> // Include this header for std::array

// Constructor to initialize with the path to the external script and other parameters
ScriptRunner::ScriptRunner(const std::string& script_path, int window_width, int window_height, const std::string& gpu_type)
    : script_path(script_path), window_width(window_width), window_height(window_height), gpu_type(gpu_type), frame_count(0) {}

// Method to run the external script and capture its output
void ScriptRunner::run_script(const std::string& command) {
    std::string output = execute_command(command);
    parse_output(output);
    frame_count++;
}

// Method to execute the command and capture its output
std::string ScriptRunner::execute_command(const std::string& command) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

// Method to parse the output from the external script into pixel data
void ScriptRunner::parse_output(const std::string& output) {
    std::istringstream stream(output);
    std::string line;
    pixel_array.clear();
    while (std::getline(stream, line)) {
        int r, g, b;
        std::istringstream linestream(line);
        linestream >> r >> g >> b;
        pixel_array.push_back({static_cast<unsigned char>(r), static_cast<unsigned char>(g), static_cast<unsigned char>(b)});
    }
}

// Method to return the parsed pixel array
const std::vector<Pixel>& ScriptRunner::get_pixel_array() const {
    return pixel_array;
}

// Method to get the current frame count
int ScriptRunner::get_frame_count() const {
    return frame_count;
}

// Method to reset the frame count
void ScriptRunner::reset_frame_count() {
    frame_count = 0;
}

// Method to handle errors
void ScriptRunner::handle_errors(const std::string& error) {
    std::cerr << "An error occurred: " << error << std::endl;
    pixel_array.clear();
}
