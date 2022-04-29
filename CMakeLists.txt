cmake_minimum_required(VERSION 3.14)

if(MSVC)
    set(CMAKE_C_COMPILER_FORCED TRUE)
    set(CMAKE_CXX_COMPILER_FORCED TRUE)
endif()

project(viage VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(DATA_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/src/Data")
set(INTERFACE_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/src/Interface")
set(SERVICE_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/src/Service")
set(3RDPARTY_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty")

if(ANDROID)
    file(COPY
        ${3RDPARTY_FOLDER}/android_openssl/latest/arm/libssl_1_1.so
        ${3RDPARTY_FOLDER}/android_openssl/latest/arm/libcrypto_1_1.so
        DESTINATION
        ${CMAKE_BINARY_DIR}/android-build/libs/armeabi-v7a)
    file(COPY
        ${3RDPARTY_FOLDER}/android_openssl/latest/arm64/libssl_1_1.so
        ${3RDPARTY_FOLDER}/android_openssl/latest/arm64/libcrypto_1_1.so
        DESTINATION
        ${CMAKE_BINARY_DIR}/android-build/libs/arm64-v8a)
    file(COPY
        ${3RDPARTY_FOLDER}/android_openssl/latest/x86/libssl_1_1.so
        ${3RDPARTY_FOLDER}/android_openssl/latest/x86/libcrypto_1_1.so
        DESTINATION
        ${CMAKE_BINARY_DIR}/android-build/libs/x86)
    file(COPY
        ${3RDPARTY_FOLDER}/android_openssl/latest/x86_64/libssl_1_1.so
        ${3RDPARTY_FOLDER}/android_openssl/latest/x86_64/libcrypto_1_1.so
        DESTINATION
        ${CMAKE_BINARY_DIR}/android-build/libs/x86_64)
endif()

find_package(QT NAMES Qt6 COMPONENTS
    Core
    Quick
    LinguistTools
    Multimedia
    Svg
    REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS
    Core
    Quick
    LinguistTools
    Multimedia
    Svg
    REQUIRED)

set(TS_FILES src/resources/ts_files/viage_fr_FR.ts)

set(PROJECT_SOURCES
    src/main.cpp
    src/Interface/bridge.hpp
    src/Interface/bridge.cpp
    src/Service/access.cpp
    src/Service/access.hpp
    src/Service/smtp.cpp
    src/Service/smtp.hpp
    src/Data/base_data.hpp
    src/Data/base_data.cpp
    src/Data/Wrapper/wrapped_list.hpp
    src/Data/Wrapper/wrapped_nested_item.hpp
    src/Data/Wrapper/wrapped_nested_list.hpp
    src/Data/Items/base_item.hpp
    src/Data/Items/base_item.cpp
    src/Data/Items/address_item.hpp
    src/Data/Items/address_item.cpp
    src/Data/Items/person_item.hpp
    src/Data/Items/person_item.cpp
    src/Data/Items/user_item.hpp
    src/Data/Items/user_item.cpp
    src/Data/Items/infant_item.hpp
    src/Data/Items/infant_item.cpp
    src/Data/Items/person_item.cpp
    src/Data/Items/owner_item.hpp
    src/Data/Items/owner_item.cpp
    src/Data/Items/habitat_item.hpp
    src/Data/Items/habitat_item.cpp
    src/Data/Items/exterior_item.hpp
    src/Data/Items/exterior_item.cpp
    src/Data/Items/document_item.hpp
    src/Data/Items/document_item.cpp
    src/Data/Items/account_item.hpp
    src/Data/Items/account_item.cpp
    src/Data/Lists/base_list.hpp
    src/Data/Lists/item_list.hpp
    src/Data/Models/base_model.hpp
    src/Data/Models/list_model.hpp
    src/Data/Models/base_filter_model.hpp
    src/Data/Models/base_filter_model.cpp
    src/Data/Models/account_filter_model.hpp
    src/Data/Models/account_filter_model.cpp
    src/Data/Models/document_filter_model.hpp
    src/Data/Models/document_filter_model.cpp
    src/Data/Models/user_filter_model.hpp
    src/Data/Models/user_filter_model.cpp
    src/resources/viage.qrc
    ${TS_FILES})

include_directories(SYSTEM
    "${DATA_FOLDER}"
    "${INTERFACE_FOLDER}"
    "${SERVICE_FOLDER}"
    "${3RDPARTY_FOLDER}/verdigris/src")

set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/src/resources/appicon.rc")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(viage
        WIN32 ${app_icon_resource_windows}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES})

    if(ANDROID)
        # Define target properties for Android with Qt 6 as:
        set_property(TARGET viage APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
            ${CMAKE_CURRENT_SOURCE_DIR}/android)
        # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
    endif()

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_compile_definitions(viage
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(viage PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Svg
    Qt${QT_VERSION_MAJOR}::Multimedia)

if(MSVC)
    target_compile_options(viage PRIVATE /Zc:__cplusplus)
endif()

#set_target_properties(viage PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
#    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#    )

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(viage)
    qt_finalize_executable(viage)
endif()

# Installer setup copyed from https://github.com/christopro/AwesomeWorld-Cmake/blob/main/AwesomeWorld/CMakeLists.txt

if (NOT ANDROID AND NOT IOS)
    set(COMPONENT_NAME_MAIN "Viage")
    set(COMPONENT_NAME_DEPENDENCIES "RuntimeLibs")

    install(TARGETS viage DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT ${COMPONENT_NAME_MAIN})

    include(InstallRequiredSystemLibraries)
    set(CPACK_GENERATOR "IFW")
    set(CPACK_PACKAGE_VERSION_MAJOR "1")
    set(CPACK_PACKAGE_VERSION_MINOR "0")

    set(CPACK_IFW_PACKAGE_NAME "Viage")
    set(CPACK_IFW_PACKAGE_TITLE "Viage")
    set(CPACK_IFW_PACKAGE_PUBLISHER "Viage")
    set(CPACK_IFW_PACKAGE_WIZARD_STYLE "Classic")
    set(CPACK_IFW_PACKAGE_WIZARD_SHOW_PAGE_LIST OFF)

    set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)

    if (WIN32)
        find_program(WINDEPLOYQT windeployqt HINTS "${_qt_bin_dir}")
        configure_file("${CMAKE_CURRENT_SOURCE_DIR}/ci/deploy-qt-windows.cmake.in" "${CMAKE_CURRENT_SOURCE_DIR}/deploy-qt-windows.cmake" @ONLY)

        set(CPACK_IFW_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/src/resources/ViageLogo.ico")
        set(CPACK_IFW_PACKAGE_LOGO "${CMAKE_CURRENT_SOURCE_DIR}/src/resources/ViageLogo.ico")
        set(CPACK_PRE_BUILD_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/deploy-qt-windows.cmake)
    endif()

    include(CPack)
    include(CPackIFW)

    CPACK_ADD_COMPONENT(${COMPONENT_NAME_MAIN})

    cpack_ifw_configure_component(${COMPONENT_NAME_MAIN} ESSENTIAL FORCED_INSTALLATION)
    cpack_ifw_configure_component(${COMPONENT_NAME_MAIN} LICENSES "LGPL License" ${CPACK_RESOURCE_FILE_LICENSE})
    cpack_ifw_configure_component(${COMPONENT_NAME_MAIN} SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/ci/installScript.qs)
endif()
