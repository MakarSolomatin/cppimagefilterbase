#ifndef _image_data_h
#define _image_data_h

#include "stb_image.h"

struct image_data
{
    stbi_uc *pixels;
    int w, h;
    int compPerPixel;
};

#endif /*_image_data_h*/
