#include "command_builder.h"

// Constructor
CommandBuilder::CommandBuilder()
    : compile_needed(false), width(0), height(0), frame_count(0) {}

// Setters for the command parameters
void CommandBuilder::set_language(const std::string& lang) {
    language = lang;
}

void CommandBuilder::set_file(const std::string& f) {
    file = f;
}

void CommandBuilder::set_compile_needed(bool compile) {
    compile_needed = compile;
}

void CommandBuilder::set_window_size(int w, int h) {
    width = w;
    height = h;
}

void CommandBuilder::set_frame_count(int count) {
    frame_count = count;
}

void CommandBuilder::set_gpu_type(const std::string& gpu) {
    gpu_type = gpu;
}

// Method to build and get the command string
std::string CommandBuilder::get_command() const {
    return build_command();
}

// Helper method to build the command based on the language
std::string CommandBuilder::build_command() const {
    std::string command;
    if (language == "PYTHON") {
        command = "python " + file + ".py " + std::to_string(width) + " " +
                  std::to_string(height) + " " + std::to_string(frame_count) + " " + gpu_type;
    } else if (language == "C++") {
        if (compile_needed) {
            command = "g++ -o " + file + " " + file + ".cpp && ";
        }
        command += "./" + file + " " + std::to_string(width) + " " +
                   std::to_string(height) + " " + std::to_string(frame_count) + " " + gpu_type;
    }
    // Additional languages can be added here
    return command;
}
