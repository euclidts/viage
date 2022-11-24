cmake_minimum_required(VERSION 3.14)

project(viage VERSION 1.0.3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})
include_directories(${JSON_INC_PATH})

#set(DATA_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/lib/Data")
add_subdirectory(lib)
#aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/lib/Data/Item" ITEM_CRS)
#add_library(VIAGE_LIB lib/Data/Item/adress_item.cpp)

add_subdirectory(client)
