cmake_minimum_required(VERSION 3.21)

project(acquisition
    VERSION 2.0
    DESCRIPTION "Stash and forum shop management for Path of Exile \\256"
    HOMEPAGE_URL "https://github.com/gerwaric/acquisition"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/EHsc)
    add_compile_options(/W4)
endif()

find_package(Qt6 REQUIRED COMPONENTS HttpServer Network NetworkAuth Quick Sql)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(acquisition WIN32 MACOSX_BUNDLE)

qt_add_qml_module(acquisition
    URI MyAcquisition
    VERSION 1.0
    QML_FILES
        acquisition/acquisition/qml/Main.qml
        #
        acquisition/acquisition/qml/ActionListMenu.qml
        #acquisition/acquisition/qml/AutoComplete.qml
        #acquisition/acquisition/qml/IntField.qml
        acquisition/acquisition/qml/MainMenuBar.qml
        acquisition/acquisition/qml/SearchFilterGroup.qml
        #
        acquisition/acquisition/qml/SearchFilters/ArmourFilters.qml
        acquisition/acquisition/qml/SearchFilters/FilterSectionHeader.qml
        acquisition/acquisition/qml/SearchFilters/HeistFilters.qml
        acquisition/acquisition/qml/SearchFilters/MapFilters.qml
        acquisition/acquisition/qml/SearchFilters/MiscellaneousFilters.qml
        acquisition/acquisition/qml/SearchFilters/RequirementFilters.qml
        acquisition/acquisition/qml/SearchFilters/SanctumFilters.qml
        acquisition/acquisition/qml/SearchFilters/SocketFilters.qml
        acquisition/acquisition/qml/SearchFilters/TypeFilters.qml
        acquisition/acquisition/qml/SearchFilters/UltimatumFilters.qml
        acquisition/acquisition/qml/SearchFilters/WeaponFilters.qml
        #acquisition/acquisition/qml/MinField.qml
        #
        acquisition/acquisition/qml/SearchFilters/AttributeFilters.qml
        acquisition/acquisition/qml/SearchFilters/ResistanceFilters.qml
        #acquisition/acquisition/qml/MaxField.qml
)

set_target_properties(acquisition PROPERTIES
    QT_QMLCACHEGEN_ARGUMENTS "--verbose"
)

add_subdirectory(acquisition)
add_subdirectory(libacq)
add_subdirectory(external/boost-headers-only)
add_subdirectory(external/json_struct)
add_subdirectory(external/QsLog)

target_link_libraries(acquisition PRIVATE
    Qt6::Quick
    QsLog
    libacq
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(acquisition PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER com.gerwaric.acquisition
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS acquisition
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
