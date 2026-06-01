cmake_minimum_required(VERSION 4.0.0)

project(cpp_image_dithering LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(stb_impl OBJECT
    src/stb_impl.cpp
)
target_include_directories(stb_impl PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
)

add_executable(cpp_image_dithering
    src/main.cpp
    src/bayer2x2.cpp
    src/bayer4x4.cpp
    src/bayer8x8.cpp
)

target_sources(cpp_image_dithering PRIVATE
    $<TARGET_OBJECTS:stb_impl>
)

target_include_directories(cpp_image_dithering PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/src"
)