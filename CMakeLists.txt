cmake_minimum_required(VERSION 3.18)
project(picky
        DESCRIPTION "Provides facilities for reading and writing binary files and memory buffers."
        LANGUAGES CXX
)

# Make symbols hidden by default.
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
# Make inlined functions hidden by default.
set(CMAKE_CXX_VISIBILITY_INLINES_HIDDEN TRUE)

add_subdirectory(dependencies)

add_subdirectory(src)