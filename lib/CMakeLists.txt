project(mutual CXX)

add_library(${PROJECT_NAME} STATIC)

if(NOT SERVER)
    set(JSONCPP_WITH_TESTS OFF CACHE BOOL "do not buid jsoncpp_tests" FORCE)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "do not buid jsoncpp_lib as shared" FORCE)
    set(BUILD_OBJECT_LIBS OFF CACHE BOOL "do not buid jsoncpp_lib as object" FORCE)
    # Not sure why it has to be included before and not here
    # include_directories("${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/jsoncpp/include")
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/jsoncpp")
endif()

target_sources(${PROJECT_NAME}
    PRIVATE
    include/base_data.hpp
    include/item_list.hpp
    src/Item/address_item.cpp
    src/Item/senior_citizen_item.cpp
    src/Item/user_item.cpp
    include/Item/infant_item.hpp
    src/Item/contact_item.cpp
    include/Item/person_item.hpp
    src/Item/owner_item.cpp
    src/Item/habitat_item.cpp
    src/Item/exterior_item.cpp
    src/Item/document_item.cpp
    src/Item/account_item.cpp
    src/Item/rent_item.cpp
    src/Item/company_item.cpp
    src/Item/team_item.cpp
)

add_library(mutual::mutual ALIAS ${PROJECT_NAME})

if(NOT SERVER)
    target_link_libraries(${PROJECT_NAME} PRIVATE jsoncpp_static)
endif()

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        $<BUILD_INTERFACE:${LIB_INCLUDES}>
)

