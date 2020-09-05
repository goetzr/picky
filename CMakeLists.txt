cmake_minimum_required(VERSION 3.18)
project(picky
        DESCRIPTION "Provides facilities for reading and writing binary files and memory buffers."
        LANGUAGES CXX
)

add_subdirectory(dependencies)

add_subdirectory(src)