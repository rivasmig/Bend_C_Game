#include "window_manager.h"
#include "script_runner.h"
#include "command_builder.h"
#include <iostream>
#include <chrono>
#include <thread>

const bool DEV_OUTPUT = true; // Set to false to disable FPS-related console outputs

int main(int argc, char* argv[]) {
    const int windowWidth = 800;
    const int windowHeight = 600;
    const std::string gpuType = "NVIDIA"; // Example GPU type
    const int maxFPS = 60; // Define maximum FPS
    const std::chrono::milliseconds frameDuration(1000 / maxFPS); // Duration of each frame in milliseconds

    try {
        WindowManager windowManager(windowWidth, windowHeight);
        windowManager.initialize();

        ScriptRunner scriptRunner("", windowWidth, windowHeight, gpuType);

        CommandBuilder commandBuilder;
        commandBuilder.set_language("C++");
        commandBuilder.set_file("pixel_shifter");
        commandBuilder.set_compile_needed(true);
        commandBuilder.set_window_size(windowWidth, windowHeight);
        commandBuilder.set_gpu_type(gpuType);

        // Variables for FPS calculation
        int frameCount = 0;
        auto startTime = std::chrono::high_resolution_clock::now();
        const int fpsInterval = 1000; // Output FPS every 1000 ms

        // Main loop to display the pixels from the script
        bool quit = false;
        SDL_Event e;
        while (!quit) {
            auto frameStart = std::chrono::high_resolution_clock::now(); // Start time of the frame

            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
            }

            commandBuilder.set_frame_count(scriptRunner.get_frame_count());
            std::string command = commandBuilder.get_command();

            // Run the script
            auto scriptStart = std::chrono::high_resolution_clock::now();
            scriptRunner.run_script(command);
            auto scriptEnd = std::chrono::high_resolution_clock::now();
            auto scriptDuration = std::chrono::duration_cast<std::chrono::milliseconds>(scriptEnd - scriptStart);

            if (DEV_OUTPUT) {
                std::cout << "Script execution time: " << scriptDuration.count() << " ms" << std::endl;
            }

            const std::vector<Pixel>& pixels = scriptRunner.get_pixel_array();
            windowManager.renderFrame(pixels);

            auto frameEnd = std::chrono::high_resolution_clock::now(); // End time of the frame
            auto frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart);

            // Calculate the true FPS and output it at regular intervals
            frameCount++;
            auto currentTime = std::chrono::high_resolution_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
            if (elapsedTime >= fpsInterval) {
                double fps = frameCount / (elapsedTime / 1000.0);
                if (DEV_OUTPUT) {
                    std::cout << "FPS: " << fps << std::endl;
                }
                frameCount = 0;
                startTime = currentTime;
            }

            if (frameDuration > frameTime) {
                std::this_thread::sleep_for(frameDuration - frameTime); // Sleep for the remaining time to control FPS
            }
        }
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
