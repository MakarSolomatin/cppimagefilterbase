#include <iostream>
#include <fstream>
#include <vector>
#include "png_toolkit.h"
#include "filter.h"

using namespace std;

void apply_config( const string &file_name ) {
    ifstream file(file_name);

    if (!file)
    {
        cout << "Config file not found";
        return;
    }

    while (!file.eof())
    {
        string filter_name;
        int u, l, b, r;

        file >> filter_name;
        file >> u;
        file >> l;
        file >> b;
        file >> r;

    }

    file.close();
}

int main( int argc, char *argv[] )
{
    // toolkit filter_name base_pic_name sudent_tool student_pic_name limitPix limitMSE
    // toolkit near test images!
    try
    {
        if (argc != 3)
            throw "Not enough arguments";

        png_toolkit studTool;
        studTool.load(argv[1]);

        filter::blur my_filter;
        studTool.filter(my_filter);

        studTool.save(argv[2]);
    }
    catch (const char *str)
    {
        cout << "Error: " << str << std::endl;
        return 1;
    }

    return 0;
}
