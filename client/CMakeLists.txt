project(viage CXX)

set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTORCC ON)

set(3RDPARTY_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty")
set(WRAPPER_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/Wrapper")
set(INTERFACE_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/Interface")
set(MODEL_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/Model")
set(DATA_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/Data")

if(ANDROID)
    file(COPY
        ${3RDPARTY_FOLDER}/android_openssl/latest/arm/libssl_1_1.so
        ${3RDPARTY_FOLDER}/android_openssl/latest/arm/libcrypto_1_1.so
        DESTINATION
        ${CMAKE_BINARY_DIR}/android-build/libs/armeabi-v7a
    )
    file(COPY
        ${3RDPARTY_FOLDER}/android_openssl/latest/arm64/libssl_1_1.so
        ${3RDPARTY_FOLDER}/android_openssl/latest/arm64/libcrypto_1_1.so
        DESTINATION
        ${CMAKE_BINARY_DIR}/android-build/libs/arm64-v8a
    )
    file(COPY
        ${3RDPARTY_FOLDER}/android_openssl/latest/x86/libssl_1_1.so
        ${3RDPARTY_FOLDER}/android_openssl/latest/x86/libcrypto_1_1.so
        DESTINATION
        ${CMAKE_BINARY_DIR}/android-build/libs/x86
    )
    file(COPY
        ${3RDPARTY_FOLDER}/android_openssl/latest/x86_64/libssl_1_1.so
        ${3RDPARTY_FOLDER}/android_openssl/latest/x86_64/libcrypto_1_1.so
        DESTINATION
        ${CMAKE_BINARY_DIR}/android-build/libs/x86_64
    )

    set(ALT_QRC "resources/empty.qrc")
else()
    set(ALT_QRC "resources/complete.qrc")
endif()

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Quick
    LinguistTools
    Multimedia
    Svg
)

qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR}
    resources/ts_files/viage_de.ts
)

set(PROJECT_SOURCES
    main.cpp
    client.cpp
    client_utils.cpp
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
    Data/c_base_data.hpp
    Data/c_list.hpp
    Data/Item/c_address.cpp
    Data/Item/c_person.hpp
    Data/Item/c_senior_citizen.cpp
    Data/Item/c_user.cpp
    Data/Item/c_infant.hpp
    Data/Item/c_contact.cpp
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
    ${QM_FILES}
)

include_directories(SYSTEM
    ${CMAKE_CURRENT_SOURCE_DIR}
    "${DATA_FOLDER}"
    "${MODEL_FOLDER}"
    "${WRAPPER_FOLDER}"
    "${INTERFACE_FOLDER}"
    "${3RDPARTY_FOLDER}/verdigris/src"
    "${3RDPARTY_FOLDER}/DuckX/include"
    "${3RDPARTY_FOLDER}/DuckX/thirdparty/zip"
    "${3RDPARTY_FOLDER}/DuckX/thirdparty/pugixml"
)

add_subdirectory("${3RDPARTY_FOLDER}/DuckX")

if(WIN32)
    set(RC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/appicon.rc")

    qt_add_executable(${PROJECT_NAME}
        WIN32 ${RC_PATH}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES})
elseif(APPLE)
    set(ICON_NAME "ViageLogo.icns")
    set(ICON_PATH "${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/${ICON_NAME}")
    set_source_files_properties(${ICON_PATH} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

    qt_add_executable(${PROJECT_NAME}
        MACOSX_BUNDLE ${ICON_PATH}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES})
else()
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES})
endif()


if(ANDROID)
    # Define target properties for Android with Qt 6 as:
    set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY
        QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
endif()

target_compile_definitions(${PROJECT_NAME}
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

#target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::Multimedia
    Qt6::Svg
    duckx
    mutual
)

qt_import_qml_plugins(${PROJECT_NAME})

qt_finalize_executable(${PROJECT_NAME})

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(WIN32)
    # Installer setup copyed from
    # https://github.com/christopro/AwesomeWorld-Cmake/blob/main/AwesomeWorld/CMakeList.txt
    set(COMPONENT_NAME_MAIN "${PROJECT_NAME}")
    set(COMPONENT_NAME_DEPENDENCIES "RuntimeLibs")

    include(GNUInstallDirs)
    install(TARGETS ${PROJECT_NAME}
        DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT ${COMPONENT_NAME_MAIN})

        if(MINGW)
            message(STATUS "Installing system-libraries: MinGW DLLs.")
            get_target_property(QMAKE_EXECUTABLE Qt::qmake IMPORTED_LOCATION)
            get_filename_component(QT_BINARY_DIR "${QMAKE_EXECUTABLE}" DIRECTORY)
            set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS
                # ${QT_BINARY_DIR}/libgcc_s_seh-1.dll
                ${QT_BINARY_DIR}/libstdc++-6.dll
                # ${QT_BINARY_DIR}/libwinpthread-1.dll
            )
        endif()

        set(CMAKE_INSTALL_SYSTEM_RUNTIME_COMPONENT ${COMPONENT_NAME_DEPENDENCIES})
        include(InstallRequiredSystemLibraries)

        set(CPACK_GENERATOR "IFW")
        set(CPACK_IFW_PACKAGE_NAME "${PROJECT_NAME}")
        set(CPACK_IFW_PACKAGE_TITLE "${PROJECT_NAME}")
        set(CPACK_IFW_PACKAGE_PUBLISHER "${PROJECT_NAME}")
        set(CPACK_IFW_PACKAGE_WIZARD_STYLE "Classic")
        set(CPACK_IFW_PACKAGE_WIZARD_SHOW_PAGE_LIST OFF)

        set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE)

        find_program(WINDEPLOYQT windeployqt HINTS "${_qt_bin_dir}")
        configure_file("${CMAKE_CURRENT_SOURCE_DIR}/ci/deploy-qt-windows.cmake.in"
            "${CMAKE_CURRENT_SOURCE_DIR}/ci/deploy-qt-windows.cmake"
            @ONLY)

        if(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS)
            install(PROGRAMS ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS}
                DESTINATION ${CMAKE_INSTALL_BINDIR}
                COMPONENT ${COMPONENT_NAME_MAIN})

            set(CPACK_IFW_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/viageLogo.ico")
            set(CPACK_IFW_PACKAGE_LOGO "${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/viageLogo.ico")
            set(CPACK_PRE_BUILD_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/ci/deploy-qt-windows.cmake)
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

    if(APPLE)
        set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE TRUE)
        set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_ICON_FILE ${ICON_NAME})

        find_program(MACDEPLOYQT macdeployqt HINTS "${_qt_bin_dir}")

        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${MACDEPLOYQT} ${CMAKE_BINARY_DIR}"/bin/${PROJECT_NAME}.app"
            -qmldir"=${CMAKE_CURRENT_SOURCE_DIR}"
            -dmg)
    endif()
endif()
