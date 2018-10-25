cmake_minimum_required (VERSION 3.4)
project (ode LANGUAGES CXX)

find_package(PythonLibs 3.6)

include_directories( inc )  

include(GNUInstallDirs)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}  )

add_compile_options( -std=c++14 )
add_compile_options( -g )
add_definitions( -DWITHOUT_NUMPY )

subdirs(src)
