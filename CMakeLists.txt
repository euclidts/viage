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
    # Only link aqainst jsoncpp
    set(JSONCPP_WITH_TESTS OFF CACHE BOOL "do not buid jsoncpp_tests" FORCE)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/jsoncpp")
    get_target_property(JSON_INC_PATH jsoncpp_lib INTERFACE_INCLUDE_DIRECTORIES)
    include_directories(${JSON_INC_PATH})
    link_libraries(jsoncpp_lib)
endif()

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/lib/include")
add_subdirectory(lib)

if(CLIENT)
    add_subdirectory(client)
endif()

if(SERVER)
    add_subdirectory(server)
endif()
