cmake_minimum_required(VERSION 2.8)

project(student_toolkit)
add_executable(${PROJECT_NAME} "main.cpp" "png_toolkit.cpp" "filter.cpp" "png_toolkit.h"
    "stb_image.h" "stb_image_write.h" "filter.h" "image_data.h")
