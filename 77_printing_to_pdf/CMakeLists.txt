cmake_minimum_required(VERSION 3.10)
project (printing_to_pdf)
add_executable(printing_to_pdf printing_to_pdf.cpp)
set_property(TARGET printing_to_pdf PROPERTY CXX_STANDARD 17)

add_custom_target(haru DEPENDS ${CMAKE_BINARY_DIR}/libharu/lib/libhpdf.so)
add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/libharu/lib/libhpdf.so
                   WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/external/libharu"
                   COMMAND bash buildconf.sh
                   COMMAND CC=${CMAKE_C_COMPILER} ./configure --prefix "${CMAKE_BINARY_DIR}/libharu"
                   COMMAND make clean
                   COMMAND make
                   COMMAND make install)

add_library(libharu SHARED IMPORTED)
add_dependencies(libharu haru)
set_property(TARGET libharu PROPERTY IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/libharu/lib/libhpdf.so)
set_property(TARGET libharu PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_BINARY_DIR}/libharu/include)


target_link_libraries(printing_to_pdf libharu)
target_include_directories(printing_to_pdf PUBLIC ${CMAKE_BINARY_DIR}/libharu/include)
