#include <iostream>
#include <vector>
#include <string>

#include "stb/stb_image.h"
#include "stb/stb_image_write.h"

int bayer8x8(const std::string& input_path)
{
    int width    {};
    int height   {};
    int channels {};
    const int bayer[8][8] {
    { 0, 32,  8, 40,  2, 34, 10, 42},
    {48, 16, 56, 24, 50, 18, 58, 26},
    {12, 44,  4, 36, 14, 46,  6, 38},
    {60, 28, 52, 20, 62, 30, 54, 22},
    { 3, 35, 11, 43,  1, 33,  9, 41},
    {51, 19, 59, 27, 49, 17, 57, 25},
    {15, 47,  7, 39, 13, 45,  5, 37},
    {63, 31, 55, 23, 61, 29, 53, 21}
};

    unsigned char* image = stbi_load(input_path.c_str(), &width, &height, &channels, 0);

    if (image == NULL)
    {
        std::cerr << "Was not able to open the .jpg file!\n";
        return 1;
    }

    int total_pixels {width * height * channels};
    std::vector<float> buffer(total_pixels);

    for (int i = 0; i < total_pixels; ++i)
        buffer[i] = static_cast<float>(image[i]);

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            float intensity  {};
            int bx           {x % 8};
            int by           {y % 8};
            int index        {(y * width + x) * channels};
            float bayer_cell {static_cast<float>(bayer[by][bx])};
            float threshold  {((bayer_cell + 0.5f) / 64.0f) * 255.0f};
            
            if (channels >= 3)
            {
                float r          {buffer[index + 0]};
                float g          {buffer[index + 1]};
                float b          {buffer[index + 2]};

                intensity = 0.299f * r + 0.587f * g + 0.114f * b;
            }
            else if (channels == 1)
            {
                intensity = buffer[index];
            }
            else if (channels == 2)
            {
                intensity = buffer[index];
            }

            unsigned char out {static_cast<unsigned char>((intensity >= threshold) ? 255 : 0)};

            if (channels >= 3)
            {
                image[index + 0] = out;
                image[index + 1] = out;
                image[index + 2] = out;
            }
            else if (channels == 1)
            {
                image[index] = out;
            }
            else if (channels == 2)
            {
                image[index + 0] = out;
            }
        }
    }

    stbi_write_png("3.png", width, height, channels, image, 100);
    stbi_image_free(image);

    return 0;
}