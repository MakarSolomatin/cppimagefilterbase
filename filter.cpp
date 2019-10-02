#include "filter.h"

image_data filter::base::image_data apply( image_data &imgData )
{
  return imgData;
}

image_data filter::fill_red::image_data apply( image_data &imgData )
{
  return imgData;
}
