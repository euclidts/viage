cmake_minimum_required(VERSION 3.5)

project(viage_3tier VERSION 1.0.3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Let Drogon do the heavy lifting for configuration
find_package(Drogon CONFIG REQUIRED)

link_libraries(Jsoncpp_lib)
include_directories(${JSONCPP_INCLUDE_DIRS}
                    "${CMAKE_CURRENT_SOURCE_DIR}/lib/include")

add_subdirectory(lib)
add_subdirectory(client)
add_subdirectory(server)
