cmake_minimum_required(VERSION 3.14)

project(viage VERSION 0.1.5 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(DATA_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/src/Data")
set(WRAPPER_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/src/Wrapper")
set(INTERFACE_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/src/Interface")
set(CALCULATOR_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/src/Calculator")
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

    set(ALT_QRC "src/resources/empty.qrc")
else()
    set(ALT_QRC "src/resources/complete.qrc")
endif()

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Quick
    LinguistTools
    Multimedia
    Svg)

set(TS_FILES src/resources/ts_files/viage_fr_FR.ts)

set(PROJECT_SOURCES
    src/main.cpp
    src/Interface/bridge.hpp
    src/Interface/bridge.cpp
    src/Interface/netManager.cpp
    src/Interface/netManager.hpp
    src/Data/base_data.hpp
    src/Data/base_data.cpp
    src/Wrapper/base_wrapper.hpp
    src/Wrapper/wrapped_list.hpp
    src/Wrapper/wrapped_nested_item.hpp
    src/Wrapper/wrapped_nested_list.hpp
    src/Data/Items/base_item.hpp
    src/Data/Items/base_item.cpp
    src/Data/Items/address_item.hpp
    src/Data/Items/address_item.cpp
    src/Data/Items/person_item.hpp
    src/Data/Items/person_item.cpp
    src/Data/Items/senior_citizen_item.hpp
    src/Data/Items/senior_citizen_item.cpp
    src/Data/Items/user_item.hpp
    src/Data/Items/user_item.cpp
    src/Data/Items/infant_item.hpp
    src/Data/Items/infant_item.cpp
    src/Data/Items/contact_item.hpp
    src/Data/Items/contact_item.cpp
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
    src/Data/Items/rent_item.hpp
    src/Data/Items/rent_item.cpp
    src/Data/Items/company_item.hpp
    src/Data/Items/company_item.cpp
    src/Data/Items/team_item.hpp
    src/Data/Items/team_item.cpp
    src/Data/Lists/base_list.hpp
    src/Data/Lists/simple_item_list.hpp
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
    src/Calculator/life_expectency.hpp
    src/Calculator/life_expectency.cpp
    src/Calculator/wrapped_calculator.hpp
    src/Calculator/wrapped_calculator.cpp
    src/resources/viage.qrc
    ${ALT_QRC}
    ${TS_FILES})

include_directories(SYSTEM
    "${DATA_FOLDER}"
    "${WRAPPER_FOLDER}"
    "${INTERFACE_FOLDER}"
    "${CALCULATOR_FOLDER}"
    "${3RDPARTY_FOLDER}/verdigris/src")

set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/src/resources/icons/appicon.rc")

qt_add_executable(viage
    WIN32 ${app_icon_resource_windows}
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES})

if(ANDROID)
    # Define target properties for Android with Qt 6 as:
    set_property(TARGET viage APPEND PROPERTY
        QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

endif()

qt_add_translations(viage TS_FILES ${TS_FILES})

target_compile_definitions(viage
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(viage PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::Svg
    Qt6::Multimedia)

#set_target_properties(viage PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
#    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#    )

qt_import_qml_plugins(viage)

qt_finalize_executable(viage)

# Installer setup copyed from
# https://github.com/christopro/AwesomeWorld-Cmake/blob/main/AwesomeWorld/CMakeLists.txt

if (NOT ANDROID AND NOT IOS)
    set(COMPONENT_NAME_MAIN "Viage")
    set(COMPONENT_NAME_DEPENDENCIES "RuntimeLibs")

    include(GNUInstallDirs)
    install(TARGETS viage DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT ${COMPONENT_NAME_MAIN})

    if(MINGW)
        message(STATUS "Installing system-libraries: MinGW DLLs.")
        get_target_property(QMAKE_EXECUTABLE Qt::qmake IMPORTED_LOCATION)
        get_filename_component(QT_BINARY_DIR "${QMAKE_EXECUTABLE}" DIRECTORY)
        set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS
            ${QT_BINARY_DIR}/libgcc_s_seh-1.dll
            ${QT_BINARY_DIR}/libstdc++-6.dll
            ${QT_BINARY_DIR}/libwinpthread-1.dll)
    endif()

    set(CMAKE_INSTALL_SYSTEM_RUNTIME_COMPONENT ${COMPONENT_NAME_DEPENDENCIES})
    include(InstallRequiredSystemLibraries)

    set(CPACK_GENERATOR "IFW")
    set(CPACK_IFW_PACKAGE_NAME "Viage")
    set(CPACK_IFW_PACKAGE_TITLE "Viage")
    set(CPACK_IFW_PACKAGE_PUBLISHER "Viage")
    set(CPACK_IFW_PACKAGE_WIZARD_STYLE "Classic")
    set(CPACK_IFW_PACKAGE_WIZARD_SHOW_PAGE_LIST OFF)

    set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)

    if (WIN32)
        find_program(WINDEPLOYQT windeployqt HINTS "${_qt_bin_dir}")
        configure_file("${CMAKE_CURRENT_SOURCE_DIR}/ci/deploy-qt-windows.cmake.in"
            "${CMAKE_CURRENT_SOURCE_DIR}/deploy-qt-windows.cmake" @ONLY)

        if(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS)
            install(PROGRAMS ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS}
                DESTINATION ${CMAKE_INSTALL_BINDIR}
                COMPONENT ${COMPONENT_NAME_MAIN})
        endif()

        set(CPACK_IFW_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/src/resources/icons/ViageLogo.ico")
        set(CPACK_IFW_PACKAGE_LOGO "${CMAKE_CURRENT_SOURCE_DIR}/src/resources/icons/ViageLogo.ico")
        set(CPACK_PRE_BUILD_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/deploy-qt-windows.cmake)
    endif()

    include(CPack)
    include(CPackIFW)

    CPACK_ADD_COMPONENT(${COMPONENT_NAME_MAIN})

    cpack_ifw_configure_component(${COMPONENT_NAME_DEPENDENCIES} VIRTUAL FORCED_INSTALLATION)
    cpack_ifw_configure_component(${COMPONENT_NAME_MAIN} ESSENTIAL FORCED_INSTALLATION)
    cpack_ifw_configure_component(${COMPONENT_NAME_MAIN} LICENSES
        "LGPL License" ${CPACK_RESOURCE_FILE_LICENSE})
    cpack_ifw_configure_component(${COMPONENT_NAME_MAIN} SCRIPT
        ${CMAKE_CURRENT_SOURCE_DIR}/ci/installScript.qs)
endif()
