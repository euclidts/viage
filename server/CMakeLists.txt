project(viage_server CXX)

include(CheckIncludeFileCXX)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(nanodbc)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    nanodbc
    Drogon::Drogon)

include_directories(Data Data/Item)

set(TEMPLATE_SRC Data/s_list.hpp)

aux_source_directory(Data/Item ITEM_SRC)
aux_source_directory(controllers CTL_SRC)
aux_source_directory(filters FILTER_SRC)
aux_source_directory(plugins PLUGIN_SRC)
aux_source_directory(models MODEL_SRC)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/models)

target_sources(${PROJECT_NAME} PRIVATE
    server.cpp
    ${TEMPLATE_SRC}
    ${ITEM_SRC}
    ${SRC_DIR}
    ${CTL_SRC}
    ${FILTER_SRC}
    ${PLUGIN_SRC}
    ${MODEL_SRC})

add_subdirectory(test)

if(UNIX OR MINGW)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${CMAKE_BINARY_DIR}/client/3rdparty/DuckX/libduckx.a
        ${CMAKE_BINARY_DIR}/lib/libviage.a)
elseif()
    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${CMAKE_BINARY_DIR}/client/3rdparty/DuckX/libduckx.lib
        ${CMAKE_BINARY_DIR}/lib/libviage.lib)
endif()
