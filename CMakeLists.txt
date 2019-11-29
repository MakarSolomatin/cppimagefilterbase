cmake_minimum_required(VERSION 2.8)

project(student_toolkit)
set(SOURCES "filter/filter.cpp"
            "png_toolkit/png_toolkit.cpp"
            "main.cpp"
            "filter/filter.h"
            "png_toolkit/image_data.h"
            "png_toolkit/png_toolkit.h"
            "stb_image/stb_image_write.h")
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC filter png_toolkit stb_image)