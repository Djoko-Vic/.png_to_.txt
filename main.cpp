#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>
#include <string>

using namespace std;

// Function to map RGB values to the nearest console color index (0-15)
int rgb_to_console_color(unsigned char r, unsigned char g, unsigned char b) {
    // Predefined console colors (16 colors)
    const int colors[16][3] = {
        {0, 0, 0},       // 0: Black
        {0, 0, 255},     // 1: Blue
        {0, 255, 0},     // 2: Green
        {0, 255, 255},   // 3: Cyan
        {255, 0, 0},     // 4: Red
        {255, 0, 255},   // 5: Magenta
        {255, 255, 0},   // 6: Yellow
        {192, 192, 192}, // 7: Light Gray
        {128, 128, 128}, // 8: Dark Gray
        {192, 192, 255}, // 9: Light Blue
        {192, 255, 192}, // 10: Light Green
        {192, 255, 255}, // 11: Light Cyan
        {255, 192, 192}, // 12: Light Red
        {255, 192, 255}, // 13: Light Magenta
        {255, 255, 192}, // 14: Light Yellow
        {255, 255, 255}, // 15: white
    };

    // Initialize the nearest color
    int nearest_color = 0;
    double min_distance = std::numeric_limits<double>::max();

    // Calculate the distance to each console color and find the nearest
    for (int i = 0; i < 16; ++i) {
        double distance = sqrt(pow(r - colors[i][0], 2) +
            pow(g - colors[i][1], 2) +
            pow(b - colors[i][2], 2));
        if (distance < min_distance) {
            min_distance = distance;
            nearest_color = i;
        }
    }
    return nearest_color;
}

// Function to save pixel data to a .txt file
void save_pixel_data_to_txt(const vector<vector<int>>& pixel_data, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file for writing." << endl;
        return;
    }

    for (const auto& row : pixel_data) {
        for (size_t i = 0; i < row.size(); i++) {
            file << row[i];
            if (i != row.size() - 1)
                file << " ";
        }
        file << endl;
    }
    file.close();
}

// Main function to load PNG and convert it to a .txt file
void png_to_txt(const string& input_png, const string& output_txt) {
    int width, height, channels;
    unsigned char* img = stbi_load(input_png.c_str(), &width, &height, &channels, 0);

    if (!img) {
        cerr << "Error: Could not load image " << input_png << endl;
        return;
    }

    vector<vector<int>> pixel_data(height, vector<int>(width));

    // Iterate over each pixel
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int idx = (y * width + x) * channels;
            unsigned char r = img[idx];
            unsigned char g = img[idx + 1];
            unsigned char b = img[idx + 2];

            // Convert the RGB values to the nearest console color index
            pixel_data[y][x] = rgb_to_console_color(r, g, b);
        }
    }

    // Save the pixel data to a text file
    save_pixel_data_to_txt(pixel_data, output_txt);

    stbi_image_free(img);  // Free the image memory
}

int main() {
    string input_png = "S:/Uni/.vs/pngtotxt/pngtotxt/quaxly-887492.png";  // Path to your PNG file
    string output_txt = "S:/Uni/.vs/pngtotxt/pngtotxt/output.txt";     // Path to save the text file
    png_to_txt(input_png, output_txt);
    cout << "Image converted to text and saved to " << output_txt << endl;
    return 0;
}
