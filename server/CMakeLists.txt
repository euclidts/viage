project(viage_server CXX)

include(CheckIncludeFileCXX)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(nanodbc)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    nanodbc
    Drogon::Drogon
    duckx
    viage
)

include_directories(Data Data/Item)

set(TEMPLATE_SRC
#    Data/s_base_data.hpp
    Data/s_list.hpp
    Data/Item/s_person.hpp
    Data/Item/s_infant.hpp
    controllers/list_ctl.hpp
    controllers/nested_item_ctl.hpp
    controllers/nested_list_ctl.hpp
)

set(SRC
    server.cpp
    server_utils.cpp
    Data/Item/s_account.cpp
    Data/Item/s_address.cpp
    Data/Item/s_company.cpp
    Data/Item/s_team.cpp
    Data/Item/s_user.cpp
    Data/Item/s_contact.cpp
    Data/Item/s_owner.cpp
)

aux_source_directory(controllers CTL_SRC)
aux_source_directory(filters FILTER_SRC)
aux_source_directory(plugins PLUGIN_SRC)
aux_source_directory(models MODEL_SRC)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/models)

target_sources(${PROJECT_NAME} PRIVATE
    ${SRC}
    ${TEMPLATE_SRC}
    ${SRC_DIR}
    ${CTL_SRC}
    ${FILTER_SRC}
    ${PLUGIN_SRC}
    ${MODEL_SRC})

#add_subdirectory(test)
