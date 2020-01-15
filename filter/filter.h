#ifndef _filter_h_
#define _filter_h_

#include "image_data.h"

namespace filter 
{
    class base 
    {
    public:
        virtual void operator()( image_data &imgData, int u, int l, int b, int r );
    protected:
        image_rect determine_rect( image_data &imgData, int u, int l, int b, int r );
    };

    class half_red : public base
    {
    public:
        void operator()( image_data &imgData, int u, int l, int b, int r ) override;
    };

    class grayscale : public base
    {
    public:
        void operator()( image_data &imgData, int u, int l, int b, int r ) override;
    };

    class red : public base
    {
    public:
        void operator()( image_data &imgData, int u, int l, int b, int r ) override;
    };

    class threshold : public base
    {
    public:
        void operator()( image_data &imgData, int u, int l, int b, int r ) override;
    };
    
    class edge : public base
    {
    public:
        void operator()( image_data &imgData, int u, int l, int b, int r ) override;
    };

    class blur : public base
    {
    public:
        void operator()( image_data &imgData, int u, int l, int b, int r ) override;
    };

}
#endif /*_filter_h_*/
