#include <iostream>
#include <vector>
#include <string>

#include "stb/stb_image.h"
#include "stb/stb_image_write.h"

int bayer2x2(const std::string& input_path)
{
    int width    {};
    int height   {};
    int channels {};
    const int bayer[2][2] {
        {0, 2},
        {3, 1}
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
            int bx           {x % 2};
            int by           {y % 2};
            int index        {(y * width + x) * channels};
            float bayer_cell {static_cast<float>(bayer[by][bx])};
            float threshold  {((bayer_cell + 0.5f) / 4.0f) * 255.0f};
            
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

    stbi_write_png("1.png", width, height, channels, image, width * channels);
    stbi_image_free(image);

    return 0;
}