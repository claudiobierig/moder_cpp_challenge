cmake_minimum_required(VERSION 3.10)
project (modern_cpp_challenge)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

add_subdirectory(13_computing_pi)
add_subdirectory(19_adding_to_a_container)
add_subdirectory(20_contains_any_all_none)
add_subdirectory(22_literals_temperature_scales)
add_subdirectory(37_finding_files)
add_subdirectory(43_meeting_time_multiple_timezones)
add_subdirectory(61_parallel_transform)
add_subdirectory(75_data_to_json)
add_subdirectory(77_printing_to_pdf)
