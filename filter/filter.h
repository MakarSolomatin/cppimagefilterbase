#ifndef _filter_h_
#define _filter_h_

#include "image_data.h"

namespace filter 
{
    class base 
    {
    public:
        virtual void operator()( image_data &imgData, int u = 0, int b = 1, int l = 0, int r = 1 );
    protected:
        image_rect determine_rect( image_data &imgData, int u, int b, int l, int r );
    };

    class half_red : public base
    {
    public:
        void operator()( image_data &imgData, int u = 0, int b = 1, int l = 0, int r = 1 ) override;
    };

    class grayscale : public base
    {
    public:
        void operator()( image_data &imgData, int u = 0, int b = 1, int l = 0, int r = 1 ) override;
    };

    class red : public base
    {
    public:
        void operator()( image_data &imgData, int u = 0, int b = 1, int l = 0, int r = 1 ) override;
    };

    class threshold : public base
    {
    public:
        void operator()( image_data &imgData, int u = 0, int b = 1, int l = 0, int r = 1 ) override;
    };
    
    class edge : public base
    {
    public:
        void operator()( image_data &imgData, int u = 0, int b = 1, int l = 0, int r = 1 ) override;
    };

    class blur : public base
    {
    public:
        void operator()( image_data &imgData, int u = 0, int b = 1, int l = 0, int r = 1 ) override;
    };

}
#endif /*_filter_h_*/
