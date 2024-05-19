cmake_minimum_required(VERSION 3.22)
project(coop C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_BUILD_TYPE Debug)

set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/coop")

message(STATUS "Printing all included files.")
file(GLOB_RECURSE SOURCE_FILES "${SOURCE_DIR}/*.c")
string(REGEX MATCHALL "[^,]+" MY_LIST "${SOURCE_FILES}")
foreach (element IN LISTS MY_LIST)
    message(STATUS "\t${element}")
endforeach ()
file(GLOB_RECURSE HEADER_FILES "${SOURCE_DIR}/*.h")
string(REGEX MATCHALL "[^;]+" MY_LIST "${HEADER_FILES}")
foreach (element IN LISTS MY_LIST)
    message(STATUS "\t${element}")
endforeach ()

add_executable(coop main.c entry_point.h entry_point.c ${SOURCE_FILES} ${HEADER_FILES}
        coop/builtins.h)
