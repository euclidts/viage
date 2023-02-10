project(mutual CXX)

add_library(${PROJECT_NAME} STATIC)

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

add_library(mutual::mutual ALIAS mutual)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        $<BUILD_INTERFACE:${LIB_INCLUDES}>
)
