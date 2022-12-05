cmake_minimum_required(VERSION 3.16)
project (gpio_lib)

SET(GPIO_SOURCES
    gpio.cpp
)

add_library(gpio_lib INTERFACE)

target_sources(gpio_lib INTERFACE ${GPIO_SOURCES})
target_include_directories(gpio_lib INTERFACE include)
