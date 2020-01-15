#ifndef PNG_TOOLKIT_H
#define PNG_TOOLKIT_H

#include <string>
#include <map>
//#include <memory>
#include "image_data.h"
#include "filter.h"

class png_toolkit
{
public:
    enum class Error {
        WrongSize,
        WrongFormat,
        Ok
    };

    png_toolkit();
    ~png_toolkit();
    bool load( std::string const &pictureName );
    void filter( filter::base &filter, int u = 0, int l = 0, int b = 1, int r = 1 );
    bool save( std::string const &pictureName );
    image_data getPixelData( void ) const;

private:
    image_data imgData;
};

#endif // PNG_TOOLKIT_H
