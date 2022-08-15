cmake_minimum_required(VERSION 3.23)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/stm32-cmake/cmake/stm32_gcc.cmake)
set(STM32_CUBE_L4_PATH ${CMAKE_CURRENT_SOURCE_DIR}/STM32CubeL4)

project(stm32l4-app C CXX ASM)
# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

find_package(CMSIS COMPONENTS STM32L4 REQUIRED)
find_package(HAL COMPONENTS 
    RCC
    GPIO
    CORTEX
    FLASH
    PWR
    STM32L4 
    REQUIRED)

# External Libs
add_subdirectory(cppreg)

# Local
add_subdirectory(src)

SET(CMAKE_CXX_FLAGS  "-g3 -ggdb")

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
    gpio_lib
    cppreg
    HAL::STM32::L4::RCC
    HAL::STM32::L4::CORTEX
    HAL::STM32::L4::GPIO
    HAL::STM32::L4::PWR
    HAL::STM32::L4::PWREx
    HAL::STM32::L4::FLASH
    CMSIS::STM32::L476RG
    STM32::NoSys    
)

stm32_print_size_of_target(${PROJECT_NAME})
stm32_generate_binary_file(${PROJECT_NAME})
stm32_generate_hex_file(${PROJECT_NAME})