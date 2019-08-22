cmake_minimum_required(VERSION 3.10)
project (printing_to_pdf)
add_executable(printing_to_pdf printing_to_pdf.cpp)
set_property(TARGET printing_to_pdf PROPERTY CXX_STANDARD 17)

add_custom_target(libharu DEPENDS "${CMAKE_BINARY_DIR}/libharu")
add_custom_command(OUTPUT "${CMAKE_BINARY_DIR}/libharu"
                   WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/external/libharu"
                   COMMAND bash buildconf.sh
                   COMMAND CC=${CMAKE_C_COMPILER} ./configure --prefix "${CMAKE_BINARY_DIR}/libharu"
                   COMMAND make clean
                   COMMAND make
                   COMMAND make install)

add_dependencies(printing_to_pdf libharu)
