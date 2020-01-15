#include <vector>
#include <algorithm>
#include <cmath>
#include "image_data.h"
#include "filter.h"

void filter::base::operator()( image_data &imgData, int u, int l, int b, int r ) {
}


image_rect filter::base::determine_rect( image_data &imgData, int u, int l, int b, int r )
{
    int x1, x2, y1, y2;

    if (l == 0)
        x1 = 0;
    else
        x1 = imgData.w / l;

    if (u == 0)
        y1 = 0;
    else
        y1 = imgData.h / u;

    if (r == 0)
        x2 = 0;
    else
        x2 = imgData.w / r;

    if (b == 0)
        y2 = 0;
    else
        y2 = imgData.h / b;
    return image_rect(x1, y1, abs(x2 - x1), abs(y2 - y1));
}

void filter::half_red::operator()( image_data &imgData, int u, int l, int b, int r ) {
    image_rect imgRect = determine_rect(imgData, u, l, b, r);
    for (int y = imgRect.y + imgRect.h / 2; y < imgRect.y + imgRect.h; y++)
        for (int x = imgRect.x; x < imgRect.x + imgRect.w; x++) {
            imgData.pixels[(y * imgData.w + x) * imgData.compPerPixel] = 255;   //red
            imgData.pixels[(y * imgData.w + x) * imgData.compPerPixel + 1] = 0; //green
            imgData.pixels[(y * imgData.w + x) * imgData.compPerPixel + 2] = 0; //blue
        }
}

void filter::grayscale::operator()( image_data &imgData, int u, int l, int b, int r ) {
    image_rect imgRect = determine_rect(imgData, u, l, b, r);
    for (int y = imgRect.y; y < imgRect.y + imgRect.h; y++)
        for (int x = imgRect.x; x < imgRect.x + imgRect.w; x++) {
            stbi_uc *rgb = imgData.pixels + (y * imgData.w + x) * imgData.compPerPixel;
            rgb[0] = rgb[1] = rgb[2] = (3 * rgb[0] + 6 * rgb[1] + rgb[2]) / 10;
        }
}

void filter::red::operator()( image_data &imgData, int u, int l, int b, int r ) {
    image_rect imgRect = determine_rect(imgData, u, l, b, r);
    for (int y = imgRect.y; y < imgRect.y + imgRect.h; y++)
        for (int x = imgRect.x; x < imgRect.x + imgRect.w; x++) {
            imgData.pixels[(y * imgData.w + x) * imgData.compPerPixel] = 255;   //red
            imgData.pixels[(y * imgData.w + x) * imgData.compPerPixel + 1] = 0; //green
            imgData.pixels[(y * imgData.w + x) * imgData.compPerPixel + 2] = 0; //blue
        }
}

void filter::threshold::operator()( image_data &imgData, int u, int l, int b, int r ) {
    image_rect imgRect = determine_rect(imgData, u, l, b, r);

    grayscale grayscale_filter;
    grayscale_filter(imgData, u, b, l, r);

    for (int y = imgRect.y; y < imgRect.y + imgRect.h; y++)
        for (int x = imgRect.x; x < imgRect.x + imgRect.w; x++) {
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

void filter::edge::operator()( image_data &imgData, int u, int l, int b, int r ) {
    image_rect imgRect = determine_rect(imgData, u, l, b, r);

    grayscale grayscale_filter;
    grayscale_filter(imgData, u, b, l, r);

    int kernel[3][3] = {{-1, -1, -1},
                        {-1, 9, -1},
                        {-1, -1, -1}};

    for (int y = imgRect.y; y < imgRect.y + imgRect.h; y++)
        for (int x = imgRect.x; x < imgRect.x + imgRect.w; x++) {
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

void filter::blur::operator()( image_data &imgData, int u, int l, int b, int r ) {
    image_rect imgRect = determine_rect(imgData, u, l, b, r);

    int kernel[3][3] = {{1, 1, 1},
                        {1, 1, 1},
                        {1, 1, 1}};

    for (int y = imgRect.y; y < imgRect.y + imgRect.h; y++)
        for (int x = imgRect.x; x < imgRect.x + imgRect.w; x++) {
            stbi_uc *rgb = imgData.pixels + (y * imgData.w + x) * imgData.compPerPixel;
            
            int sum[3] = {0, 0, 0};
            for (int j = -1; j <= 1; j++)
                for (int i = -1; i <= 1; i++)
                    for (int k = 0; k < 3; k++)
                    {
                        int xn = x + i, yn = y + j;
                        if (xn >= 0 && xn < imgData.w && yn >= 0 && yn < imgData.h)
                            sum[k] += imgData.pixels[(yn * imgData.w + x) * imgData.compPerPixel + k] * kernel[j + 1][i + 1];
                    }
            for (int k = 0; k < 3; k++) {
                sum[k] /= 9;
                if (sum[k] < 0)
                    sum[k] = 0;
                else if (sum[k] > 255)
                    sum[k] = 255;
                rgb[k] = sum[k];
            }
        }
}
