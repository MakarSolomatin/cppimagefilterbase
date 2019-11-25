#include <vector>
#include <algorithm>
#include "image_data.h"
#include "filter.h"

void filter::base::operator()( image_data &imgData ) {

}

void filter::half_red::operator()( image_data &imgData ) {
    for (int y = imgData.h / 2; y < imgData.h; y++)
        for (int x = 0; x < imgData.w; x++) {
            imgData.pixels[(y * imgData.w + x) * imgData.compPerPixel] = 255;   //red
            imgData.pixels[(y * imgData.w + x) * imgData.compPerPixel + 1] = 0; //green
            imgData.pixels[(y * imgData.w + x) * imgData.compPerPixel + 2] = 0; //blue
        }
}

void filter::grayscale::operator()( image_data &imgData ) {
    for (int y = 0; y < imgData.h; y++)
        for (int x = 0; x < imgData.w; x++)
        {
            stbi_uc *rgb = imgData.pixels + (y * imgData.w + x) * imgData.compPerPixel;
            rgb[0] = rgb[1] = rgb[2] = (3 * rgb[0] + 6 * rgb[1] + rgb[2]) / 10;
        }
}

void filter::red::operator()( image_data &imgData ) {
    for (int y = 0; y < imgData.h; y++)
        for (int x = 0; x < imgData.w; x++)
        {
            imgData.pixels[(y * imgData.w + x) * imgData.compPerPixel] = 255;   //red
            imgData.pixels[(y * imgData.w + x) * imgData.compPerPixel + 1] = 0; //green
            imgData.pixels[(y * imgData.w + x) * imgData.compPerPixel + 2] = 0; //blue
        }
}

void filter::threshold::operator()( image_data &imgData ) {
    grayscale grayscale_filter;
    grayscale_filter(imgData);

    for (int y = 0; y < imgData.h; y++)
        for (int x = 0; x < imgData.w; x++)
        {
            std::vector<stbi_uc> kernel;
            stbi_uc *rgb = imgData.pixels + (y * imgData.w + x) * imgData.compPerPixel;
            
            for (int j = -2; j <= 2; j++)
                for (int i = -2; i <= 2; i++)
                {
                    int xn = x + i, yn = y + j;
                    if (xn >= 0 && xn < imgData.w && yn >= 0 && yn < imgData.h)
                        kernel.push_back(imgData.pixels[(yn * imgData.w + xn) * imgData.compPerPixel]);
                }
            std::sort(kernel.begin(), kernel.end());
            if (rgb[0] < kernel.at(kernel.size() / 2))
                rgb[0] = rgb[1] = rgb[2] = 0;
        }
}

void filter::edge::operator()( image_data &imgData ) {
    grayscale grayscale_filter;
    grayscale_filter(imgData);

    int kernel[3][3] = {{-1, -1, -1},
                        {-1, 9, -1},
                        {-1, -1, -1}};

    for (int y = 0; y < imgData.h; y++)
        for (int x = 0; x < imgData.w; x++)
        {
            stbi_uc *rgb = imgData.pixels + (y * imgData.w + x) * imgData.compPerPixel;
            
            int sum = 0;
            for (int j = -1; j <= 1; j++)
                for (int i = -1; i <= 1; i++)
                {
                    int xn = x + i, yn = y + j;
                    if (xn >= 0 && xn < imgData.w && yn >= 0 && yn < imgData.h)
                        sum += imgData.pixels[(yn * imgData.w + x) * imgData.compPerPixel] * kernel[j + 1][i + 1];
                }
            if (sum < 0)
                sum = 0;
            else if (sum > 255)
                sum = 255;

            rgb[0] = rgb[1] = rgb[2] = sum;
        }
}

void filter::blur::operator()( image_data &imgData ) {
    grayscale grayscale_filter;
    grayscale_filter(imgData);

    int kernel[3][3] = {{1, 1, 1},
                        {1, 1, 1},
                        {1, 1, 1}};

    for (int y = 0; y < imgData.h; y++)
        for (int x = 0; x < imgData.w; x++)
        {
            stbi_uc *rgb = imgData.pixels + (y * imgData.w + x) * imgData.compPerPixel;
            
            int sum = 0;
            for (int j = -1; j <= 1; j++)
                for (int i = -1; i <= 1; i++)
                {
                    int xn = x + i, yn = y + j;
                    if (xn >= 0 && xn < imgData.w && yn >= 0 && yn < imgData.h)
                        sum += imgData.pixels[(yn * imgData.w + x) * imgData.compPerPixel] * kernel[j + 1][i + 1];
                }
            sum /= 9;
            if (sum < 0)
                sum = 0;
            else if (sum > 255)
                sum = 255;

            rgb[0] = rgb[1] = rgb[2] = sum;
        }
}
