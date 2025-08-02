cmake_minimum_required(VERSION 3.16)

project(DataStructure)
include_directories(${CMAKE_SOURCE_DIR}/include)

option(${PROJECT_NAME}_RBTREE_C "rbtree writen in C" ON)

set(DS_SRCS "")

if(${PROJECT_NAME}_RBTREE_C)
    message("${PROJECT_NAME}_RBTREE_C is ON")
    set(DS_SRCS ${DS_SRCS} "${CMAKE_SOURCE_DIR}/src/rbtree.c")
    add_definitions(-DDS_RBTREE_C)
else()
    message("${PROJECT_NAME}_RBTREE_C is OFF")
endif()

message("SRCS has ${DS_SRCS}")

add_library(DataStructure STATIC
        ${DS_SRCS}
    )