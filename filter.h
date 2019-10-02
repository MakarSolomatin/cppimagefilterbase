#ifndef _filter_h_
#define _filter_h_

struct image_data;
namespace filter 
{
  class base 
  {
  public:
    virtual image_data apply( image_data &imgData );
 };
  class fill_red : public base
  {
  public:
    virtual image_data apply( image_data &imgData ) override;
  };
}
#endif /*_filter_h_*/
