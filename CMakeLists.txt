cmake_minimum_required(VERSION 3.15)
project(KellySimulator VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable aggressive warnings to enforce clean production standards
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -O3)
endif()

include_directories(include)

add_executable(kelly_sim src/main.cpp src/kelly_sim.cpp)
