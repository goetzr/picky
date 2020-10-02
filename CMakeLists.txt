cmake_minimum_required(VERSION 3.16)

# Determine if picky is built as a subproject (using add_subdirectory)
# or if it is the master project.
set(MASTER_PROJECT FALSE)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(MASTER_PROJECT TRUE)
endif()

# Set the default CMAKE_BUILD_TYPE to Release.
# This should be done before the project command since the latter can set
# CMAKE_BUILD_TYPE itself (it does so for nmake).
if (MASTER_PROJECT AND NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING
		"Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel."
	)
endif()

project(picky
        DESCRIPTION "Provides facilities for reading and writing binary files and memory buffers."
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD					17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS				NO)

# TODO: Set enable warnings
# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

option(PICKY_TEST "Generate the test target." ${MASTER_PROJECT})

# Make symbols hidden by default.
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
# Make inlined functions hidden by default.
set(CMAKE_CXX_VISIBILITY_INLINES_HIDDEN TRUE)

add_subdirectory(dependencies)

add_subdirectory(src)

if (${PICKY_TEST})
	enable_testing()
	add_subdirectory(test)
endif()