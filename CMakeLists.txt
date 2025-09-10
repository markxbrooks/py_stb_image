cmake_minimum_required(VERSION 3.15)
project(stb_image_wrapper LANGUAGES CXX)

find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(stb_image_wrapper stb_image_wrapper/wrapper.cpp)

target_include_directories(stb_image_wrapper PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/extern)

# Enable C++17
target_compile_features(stb_image_wrapper PRIVATE cxx_std_17)

