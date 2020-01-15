#include <iostream>
#include <fstream>
#include <vector>
#include "png_toolkit.h"
#include "filter.h"

using namespace std;

void apply_config( const string &file_name, png_toolkit &stud_tool ) {
    ifstream file(file_name);

    if (!file) {
        cout << "Config file not found";
        return;
    }

    while (!file.eof()) {
        string filter_name;
        int u, l, b, r;

        file >> filter_name;
        file >> u;
        file >> l;
        file >> b;
        file >> r;

        filter::base *filter = nullptr;
        if (filter_name == "Red")
            filter = new filter::red;
        else if (filter_name == "Threshold")
            filter = new filter::threshold;
        else if (filter_name == "Blur")
            filter = new filter::blur;
        else if (filter_name == "Edge")
            filter = new filter::edge;

        if (filter != nullptr)
            stud_tool.filter(*filter, u, l, b, r);

        delete filter;
    }

    file.close();
}

int main( int argc, char *argv[] )
{
    try
    {
        if (argc != 4)
            throw "Not enough arguments";

        png_toolkit stud_tool;
        stud_tool.load(argv[2]);
        apply_config(argv[1], stud_tool);
        stud_tool.save(argv[3]);
    }
    catch (const char *str)
    {
        cout << "Error: " << str << std::endl;
        return 1;
    }

    return 0;
}
