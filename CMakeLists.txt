cmake_minimum_required(VERSION 3.16)

project(DataStructure)
include_directories(${CMAKE_SOURCE_DIR}/include)

option(${PROJECT_NAME}_RBTREE "rbtree writen in C" ON)
option(${PROJECT_NAME}_SET "set written in C(based on rbtree)" ON)

set(DS_SRCS "")

if(${PROJECT_NAME}_SET)
    message("${PROJECT_NAME}_SET is ON")
    set(${PROJECT_NAME}_RBTREE ON)
    set(DS_SRCS ${DS_SRCS} "${CMAKE_SOURCE_DIR}/src/set.c")
    add_definitions(-DDS_SET)
else()
    message("${PROJECT_NAME}_SET is OFF")
endif()

if(${PROJECT_NAME}_RBTREE)
    message("${PROJECT_NAME}_RBTREE is ON")
    set(DS_SRCS ${DS_SRCS} "${CMAKE_SOURCE_DIR}/src/rbtree.c")
    add_definitions(-DDS_RBTREE)
else()
    message("${PROJECT_NAME}_RBTREE is OFF")
endif()

message("SRCS has ${DS_SRCS}")

add_library(DataStructure STATIC
        ${DS_SRCS}
    )