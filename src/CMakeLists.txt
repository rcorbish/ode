
add_executable( ode main.cpp solution.cpp )

find_package(PythonLibs 3.6)

target_include_directories(ode PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(ode ${PYTHON_LIBRARIES})
