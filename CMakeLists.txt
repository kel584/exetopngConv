cmake_minimum_required(VERSION 3.28)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled main.cpp
        stb_image_write.h
        stb_image.h)

if (MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
    set(CMAKE_EXE_LINKER_FLAGS "-static")

    # Find the necessary libraries
    find_library(LIBGCC libgcc.a PATHS "C:/Program Files/JetBrains/CLion 2024.1.1/bin/mingw/lib/gcc/x86_64-w64-mingw32/13.1.0")
    find_library(LIBSTDCPP libstdc++.a PATHS "C:/Program Files/JetBrains/CLion 2024.1.1/bin/mingw/lib/gcc/x86_64-w64-mingw32/13.1.0")
    find_library(LIBWINPTHREAD libwinpthread.a PATHS "C:/Program Files/JetBrains/CLion 2024.1.1/bin/mingw/x86_64-w64-mingw32/lib")
else()
    target_link_libraries(ExeToPng -static-libgcc -static-libstdc++)
endif()