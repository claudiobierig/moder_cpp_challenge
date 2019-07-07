cmake_minimum_required(VERSION 3.10)

include(ExternalProject)
find_package(Git REQUIRED)

list(APPEND DATE_CMAKE_ARGS
    "-DCMAKE_INSTALL_PREFIX=${EXTERNAL_PATH}"
    "-DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}"
    "-DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}"
)

ExternalProject_Add(
    date
    GIT_REPOSITORY      https://github.com/HowardHinnant/date.git
    GIT_TAG             v2.4.1
    GIT_SHALLOW         1
    CMAKE_ARGS          ${DATE_CMAKE_ARGS}
    PREFIX              ${EXTERNAL_PATH}/date/prefix
    TMP_DIR             ${EXTERNAL_PATH}/date/tmp
    STAMP_DIR           ${EXTERNAL_PATH}/date/stamp
    DOWNLOAD_DIR        ${EXTERNAL_PATH}/date/download
    SOURCE_DIR          ${EXTERNAL_PATH}/date/src
    BINARY_DIR          ${EXTERNAL_PATH}/date/build
)

project (meeting_times)
add_executable(meeting_times meeting_times.cpp)
set_property(TARGET meeting_times PROPERTY CXX_STANDARD 17)
target_include_directories(meeting_times PUBLIC ${EXTERNAL_PATH}/include)
