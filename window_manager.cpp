#include "window_manager.h"
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <string>

// Constructor to initialize the window with given dimensions
WindowManager::WindowManager(int width, int height)
    : width(width), height(height), window(nullptr), renderer(nullptr), texture(nullptr) {
    srand(static_cast<unsigned>(time(0)));
}

// Destructor to clean up resources
WindowManager::~WindowManager() {
    cleanup();
}

// Function to initialize the window
void WindowManager::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("SDL could not initialize! SDL_Error: " + std::string(SDL_GetError()));
    }

    window = SDL_CreateWindow("Bend Astroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        throw std::runtime_error("Window could not be created! SDL_Error: " + std::string(SDL_GetError()));
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == nullptr) {
        throw std::runtime_error("Renderer could not be created! SDL_Error: " + std::string(SDL_GetError()));
    }

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, width, height);
    if (texture == nullptr) {
        throw std::runtime_error("Texture could not be created! SDL_Error: " + std::string(SDL_GetError()));
    }
}

// Function to render a frame using the provided pixel array
void WindowManager::renderFrame(const std::vector<Pixel>& pixelArray) {
    void* pixels;
    int pitch;
    SDL_LockTexture(texture, nullptr, &pixels, &pitch);
    memcpy(pixels, pixelArray.data(), pixelArray.size() * sizeof(Pixel));
    SDL_UnlockTexture(texture);

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

// Function to create a randomized pixel array for testing
std::vector<Pixel> WindowManager::createRandomPixelArray() {
    std::vector<Pixel> pixels(width * height);
    for (auto& pixel : pixels) {
        pixel.r = rand() % 256;
        pixel.g = rand() % 256;
        pixel.b = rand() % 256;
    }
    return pixels;
}

// Function to run the main loop
void WindowManager::mainLoop() {
    bool quit = false;
    SDL_Event e;
    auto pixelArray = createRandomPixelArray();

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            processInput();
        }
        updateWindow(pixelArray);
    }
}

// Function to process input (placeholder for future expansion)
void WindowManager::processInput() {
    // Handle user input here if needed
}

// Function to update the window content
void WindowManager::updateWindow(const std::vector<Pixel>& pixelArray) {
    renderFrame(pixelArray);
}

// Function to clean up resources
void WindowManager::cleanup() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}
