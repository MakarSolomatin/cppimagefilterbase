#include "image_data.h"
#include "filter.h"

void filter::base::apply( image_data &imgData ) {

}

void filter::half_red::apply( image_data &imgData ) {
  for (int y = imgData.h / 2; y < imgData.h; y++)
      for (int x = 0; x < imgData.w; x++) {
          imgData.pixels[(y * imgData.w + x) * imgData.compPerPixel] = 255;   //red
          imgData.pixels[(y * imgData.w + x) * imgData.compPerPixel + 1] = 0; //green
          imgData.pixels[(y * imgData.w + x) * imgData.compPerPixel + 2] = 0; //blue
      }
}
