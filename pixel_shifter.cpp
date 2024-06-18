#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <string>
#include <sstream>
#include <stdexcept>

// Structure to represent a pixel with RGB values
struct Pixel {
    int r, g, b;
};

// Generate a random noise array with shades of blue
std::vector<Pixel> generate_blue_noise(int width, int height) {
    std::vector<Pixel> pixels(width * height);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100, 255); // Shades of blue

    for (auto& pixel : pixels) {
        pixel = {0, 0, dis(gen)};
    }
    return pixels;
}

// Shift pixels to the right, wrapping around
std::vector<Pixel> shift_pixels(const std::vector<Pixel>& pixels) {
    if (pixels.empty()) {
        return pixels;
    }
    std::vector<Pixel> shifted_pixels = pixels;
    Pixel last_pixel = shifted_pixels.back();
    for (int i = shifted_pixels.size() - 1; i > 0; --i) {
        shifted_pixels[i] = shifted_pixels[i - 1];
    }
    shifted_pixels[0] = last_pixel;
    return shifted_pixels;
}

// Main function
int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: pixel_shifter <width> <height> <frame_count> <gpu_type>" << std::endl;
        return 1;
    }

    int width = std::stoi(argv[1]);
    int height = std::stoi(argv[2]);
    int frame_count = std::stoi(argv[3]);
    std::string gpu_type = argv[4];

    std::vector<Pixel> pixels;
    if (frame_count == 0) {
        pixels = generate_blue_noise(width, height);
    } else {
        std::ifstream infile("pixels.json");
        if (!infile) {
            std::cerr << "Error reading pixels.json" << std::endl;
            return 1;
        }
        std::string line;
        while (std::getline(infile, line)) {
            std::istringstream iss(line);
            Pixel pixel;
            if (!(iss >> pixel.r >> pixel.g >> pixel.b)) {
                std::cerr << "Error parsing pixel data" << std::endl;
                return 1;
            }
            pixels.push_back(pixel);
        }
        infile.close();
        pixels = shift_pixels(pixels);
    }

    // Save the current pixel state for the next frame
    std::ofstream outfile("pixels.json");
    if (!outfile) {
        std::cerr << "Error writing to pixels.json" << std::endl;
        return 1;
    }
    for (const auto& pixel : pixels) {
        outfile << pixel.r << " " << pixel.g << " " << pixel.b << std::endl;
    }
    outfile.close();

    // Output the pixel array
    for (const auto& pixel : pixels) {
        std::cout << pixel.r << " " << pixel.g << " " << pixel.b << std::endl;
    }

    return 0;
}
