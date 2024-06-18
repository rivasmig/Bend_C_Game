#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <vector>
#include <stdexcept>  // For std::runtime_error
#include <string>     // For std::string
#include <SDL2/SDL.h>

// Forward declarations for structures (if needed later)
struct Pixel;

// Structure to represent a pixel with RGB values
struct Pixel {
    unsigned char r, g, b;
};

// Class to manage the window and rendering
class WindowManager {
public:
    // Constructor to initialize the window with given dimensions
    WindowManager(int width, int height);

    // Destructor to clean up resources
    ~WindowManager();

    // Function to initialize the window
    void initialize();

    // Function to render a frame using the provided pixel array
    void renderFrame(const std::vector<Pixel>& pixelArray);

    // Function to create a randomized pixel array for testing
    std::vector<Pixel> createRandomPixelArray();

    // Function to run the main loop
    void mainLoop();

private:
    int width;  // Width of the window
    int height; // Height of the window

    SDL_Window* window;       // SDL window
    SDL_Renderer* renderer;   // SDL renderer
    SDL_Texture* texture;     // SDL texture

    // Function to process input (placeholder for future expansion)
    void processInput();

    // Function to update the window content
    void updateWindow(const std::vector<Pixel>& pixelArray);

    // Function to clean up resources
    void cleanup();
};

#endif // WINDOW_MANAGER_H
