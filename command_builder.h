#ifndef COMMAND_BUILDER_H
#define COMMAND_BUILDER_H

#include <string>

class CommandBuilder {
public:
    // Constructor
    CommandBuilder();

    // Setters for the command parameters
    void set_language(const std::string& language);
    void set_file(const std::string& file);
    void set_compile_needed(bool compile_needed);
    void set_window_size(int width, int height);
    void set_frame_count(int frame_count);
    void set_gpu_type(const std::string& gpu_type);

    // Method to build and get the command string
    std::string get_command() const;

private:
    std::string language;
    std::string file;
    bool compile_needed;
    int width;
    int height;
    int frame_count;
    std::string gpu_type;

    // Helper method to build the command based on the language
    std::string build_command() const;
};

#endif // COMMAND_BUILDER_H
