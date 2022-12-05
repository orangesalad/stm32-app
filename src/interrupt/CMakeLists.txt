cmake_minimum_required(VERSION 3.16)
project (nvic_lib)

SET(GPIO_SOURCES
    interrupt.cpp
)

add_library(nvic_lib INTERFACE)

target_sources(nvic_lib INTERFACE ${NVIC_SOURCES})
target_include_directories(nvic_lib INTERFACE include)
