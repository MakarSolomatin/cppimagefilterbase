#ifndef _filter_h_
#define _filter_h_

#include "image_data.h"

namespace filter 
{
    class base 
    {
    public:
        virtual void operator()( image_data &imgData );
    };

    class half_red : public base
    {
    public:
        void operator()( image_data &imgData ) override;
    };

    class grayscale : public base
    {
    public:
        void operator()( image_data &imgData ) override;
    };

    class red : public base
    {
    public:
        void operator()( image_data &imgData ) override;
    };

    class threshold : public base
    {
    public:
        void operator()( image_data &imgData ) override;
    };
    
    class edge : public base
    {
    public:
        void operator()( image_data &imgData ) override;
    };

    class blur : public base
    {
    public:
        void operator()( image_data &imgData ) override;
    };

}
#endif /*_filter_h_*/
