cmake_minimum_required(VERSION 3.10)

project (meeting_times)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=deprecated-declarations")

add_executable(meeting_times
    meeting_times.cpp
    ../external/date/src/tz.cpp
)

set_property(TARGET meeting_times PROPERTY CXX_STANDARD 17)
target_include_directories(meeting_times PUBLIC ../external/date/include)
target_link_libraries(meeting_times curl)
