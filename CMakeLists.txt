cmake_minimum_required (VERSION 3.4)
project (ode LANGUAGES CXX)

find_package(PythonLibs 3.6)

include_directories( inc )  

include(GNUInstallDirs)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}  )

add_compile_options( -std=c++14 )
add_compile_options( -g )
add_definitions( -DWITHOUT_NUMPY )

if( NO_MATPLOT ) 
  add_definitions( -DNO_MATPLOT=1 )
endif( NO_MATPLOT ) 


subdirs(src)

# first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build documentation" ON)

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)


#OUTPUT_DIRECTORY       = @CMAKE_CURRENT_BINARY_DIR@/doc_doxygen/
#INPUT                  = @CMAKE_CURRENT_SOURCE_DIR@/../src/ @CMAKE_CURRENT_SOURCE_DIR@/../docs