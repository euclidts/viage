cmake_minimum_required(VERSION 3.5)

project(viage_3tier VERSION 1.0.3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CLIENT ON CACHE BOOL "building client")
set(SERVER ON CACHE BOOL "building server")

if(SERVER)
    # Let Drogon do the heavy lifting for configuration
    find_package(Drogon CONFIG REQUIRED)
    link_libraries(Jsoncpp_lib)
else()
    # Only link aqainst jsoncpp
    find_package(jsoncpp)
#    find_package(PkgConfig REQUIRED)
#    pkg_check_modules(JSONCPP jsoncpp)
    link_libraries(${JSONCPP_LIBRARIES})
endif()

include_directories(${JSONCPP_INCLUDE_DIRS}
                    "${CMAKE_CURRENT_SOURCE_DIR}/lib/include")
add_subdirectory(lib)

if(CLIENT)
    add_subdirectory(client)
endif()

if(SERVER)
    add_subdirectory(server)
endif()
