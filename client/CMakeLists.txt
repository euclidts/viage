set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTORCC ON)

set(3RDPARTY_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty")
set(WRAPPER_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/Wrapper")
set(INTERFACE_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/Interface")
set(MODEL_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/Model")
set(CLIENT_DATA "${CMAKE_CURRENT_SOURCE_DIR}/Data")

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

    find_package(Qt6 REQUIRED COMPONENTS Svg)

    set(ALT_QRC "resources/empty.qrc")
else()
    set(ALT_QRC "resources/complete.qrc")
endif()

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Quick
    LinguistTools
    Multimedia)

set(TS_FILES resources/ts_files/viage_fr_FR.ts)

set(PROJECT_SOURCES
    main.cpp
    Interface/client.cpp
    Interface/bridge.cpp
    Interface/netManager.cpp
    Wrapper/base_wrapper.hpp
    Wrapper/wrapped_list.hpp
    Wrapper/wrapped_nested_item.hpp
    Wrapper/wrapped_nested_list.hpp
    Wrapper/life_expectency.cpp
    Wrapper/wrapped_calculator.cpp
    Model/list_model.hpp
    Model/base_filter_model.cpp
    Model/account_filter_model.cpp
    Model/document_filter_model.cpp
    Model/user_filter_model.cpp
    Data/c_base_data.cpp
    Data/c_list.hpp
    Data/Item/c_address.cpp
    Data/Item/c_person.cpp
    Data/Item/c_senior_citizen.cpp
    Data/Item/c_user.cpp
    Data/Item/c_infant.cpp
    Data/Item/c_contact.cpp
    Data/Item/c_person.cpp
    Data/Item/c_owner.cpp
    Data/Item/c_habitat.cpp
    Data/Item/c_exterior.cpp
    Data/Item/c_document.cpp
    Data/Item/c_account.cpp
    Data/Item/c_rent.cpp
    Data/Item/c_company.cpp
    Data/Item/c_team.cpp
    resources/viage.qrc
    ${ALT_QRC}
    ${TS_FILES}
    #${ITEM_SRC}
    # yet to be compiled seperaly as a library
    ../lib/Data/base_data.cpp
    ../lib/Data/item_list.hpp
    ../lib/Data/Item/address_item.cpp
    ../lib/Data/Item/person_item.cpp
    ../lib/Data/Item/senior_citizen_item.cpp
    ../lib/Data/Item/user_item.cpp
    ../lib/Data/Item/infant_item.cpp
    ../lib/Data/Item/contact_item.cpp
    ../lib/Data/Item/person_item.cpp
    ../lib/Data/Item/owner_item.cpp
    ../lib/Data/Item/habitat_item.cpp
    ../lib/Data/Item/exterior_item.cpp
    ../lib/Data/Item/document_item.cpp
    ../lib/Data/Item/account_item.cpp
    ../lib/Data/Item/rent_item.cpp
    ../lib/Data/Item/company_item.cpp
    ../lib/Data/Item/team_item.cpp)

include_directories(SYSTEM
    "${DATA_FOLDER}"
    "${CLIENT_DATA}"
    "${MODEL_FOLDER}"
    "${WRAPPER_FOLDER}"
    "${INTERFACE_FOLDER}"
    "${3RDPARTY_FOLDER}/verdigris/src"
    "${3RDPARTY_FOLDER}/DuckX/include"
    "${3RDPARTY_FOLDER}/DuckX/thirdparty/zip"
    "${3RDPARTY_FOLDER}/DuckX/thirdparty/pugixml")

add_subdirectory("${3RDPARTY_FOLDER}/DuckX")

set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/appicon.rc")

qt_add_executable(viage
    WIN32 ${app_icon_resource_windows}
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES})

if(ANDROID)
    # Define target properties for Android with Qt 6 as:
    set_property(TARGET viage APPEND PROPERTY
        QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    target_link_libraries(viage PRIVATE Qt6::Svg)
endif()

qt_add_translations(viage TS_FILES ${TS_FILES})

target_compile_definitions(viage
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(viage PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::Multimedia
    ${JSONCPP_LIBRARIES})

if(UNIX OR MINGW)
    target_link_libraries(viage PRIVATE ${CMAKE_BINARY_DIR}/client/3rdparty/DuckX/libduckx.a)
elseif()
    target_link_libraries(viage PRIVATE ${CMAKE_BINARY_DIR}/client/3rdparty/DuckX/libduckx.lib)
endif()

#set_target_properties(viage PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
#    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#    )

qt_import_qml_plugins(viage)

qt_finalize_executable(viage)

# Installer setup copyed from
# https://github.com/christopro/AwesomeWorld-Cmake/blob/main/AwesomeWorld/CMakeList.txt

if (NOT ANDROID AND NOT IOS AND CMAKE_BUILD_TYPE STREQUAL "Release")
    set(COMPONENT_NAME_MAIN "viage")
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
    set(CPACK_IFW_PACKAGE_NAME "viage")
    set(CPACK_IFW_PACKAGE_TITLE "viage")
    set(CPACK_IFW_PACKAGE_PUBLISHER "viage")
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

        set(CPACK_IFW_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/src/resources/icons/viageLogo.ico")
        set(CPACK_IFW_PACKAGE_LOGO "${CMAKE_CURRENT_SOURCE_DIR}/src/resources/icons/viageLogo.ico")
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
