project(viage CXX)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
    PRIVATE
    src/base_data.cpp
    include/item_list.hpp
    src/Item/address_item.cpp
    src/Item/person_item.cpp
    src/Item/senior_citizen_item.cpp
    src/Item/user_item.cpp
    src/Item/infant_item.cpp
    src/Item/contact_item.cpp
    src/Item/person_item.cpp
    src/Item/owner_item.cpp
    src/Item/habitat_item.cpp
    src/Item/exterior_item.cpp
    src/Item/document_item.cpp
    src/Item/account_item.cpp
    src/Item/rent_item.cpp
    src/Item/company_item.cpp
    src/Item/team_item.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        $<BUILD_INTERFACE:${LIB_INCLUDES}>
)
