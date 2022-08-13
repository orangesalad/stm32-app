cmake_minimum_required(VERSION 3.23)

SET(MODULE1_SOURCES
    module1.cpp   
)

add_library(module1 INTERFACE ${MODULE1_SOURCES})

target_include_directories(module1 INTERFACE include)