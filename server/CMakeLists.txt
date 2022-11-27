project(viage_server CXX)

include(CheckIncludeFileCXX)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(nanodbc)

add_executable(${PROJECT_NAME}
    server.cpp
    main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    nanodbc
    Drogon::Drogon)

aux_source_directory(controllers CTL_SRC)
aux_source_directory(filters FILTER_SRC)
aux_source_directory(plugins PLUGIN_SRC)
aux_source_directory(models MODEL_SRC)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/models)

target_sources(${PROJECT_NAME} PRIVATE
    ${SRC_DIR}
    ${CTL_SRC}
    ${FILTER_SRC}
    ${PLUGIN_SRC}
    ${MODEL_SRC})

add_subdirectory(test)
