cmake_minimum_required(VERSION 3.14)

project(viage VERSION 1.0.3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(DATA_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/src/Data")
set(CALCULATOR_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/src/Calculator")

#add_library(src)

add_subdirectory(client)
