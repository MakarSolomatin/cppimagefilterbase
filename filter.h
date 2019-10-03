#ifndef _filter_h_
#define _filter_h_

#include "image_data.h"

namespace filter 
{
  class base 
  {
  public:
    virtual void apply( image_data &imgData );
 };
  class half_red : public base
  {
  public:
    void apply( image_data &imgData ) override;
  };
}
#endif /*_filter_h_*/
