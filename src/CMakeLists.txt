

add_executable( ode main.cpp solution.cpp )

target_include_directories(ode PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(ode ${PYTHON_LIBRARIES})
