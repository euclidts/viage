cmake_minimum_required(VERSION 3.15)

project(viage VERSION 1.0.7 LANGUAGES CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

set(CLIENT ON CACHE BOOL "building client")
set(SERVER ON CACHE BOOL "building server")

if(SERVER)
    # Let Drogon do the heavy lifting for configuration
    find_package(Drogon CONFIG REQUIRED)
    include_directories(${JSONCPP_INCLUDE_DIRS})
    link_libraries(Jsoncpp_lib)
else()
    # Not sure why it has to be included here and not in lib
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/lib/3rdparty/jsoncpp/include")
endif()

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/lib/include")
add_subdirectory(lib)

if(CLIENT)
    add_subdirectory(client)
endif()

if(SERVER)
    add_subdirectory(server)
endif()
