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

add_subdirectory(acquisition)
add_subdirectory(external/boost-headers-only)
add_subdirectory(external/json_struct)
add_subdirectory(external/QsLog)

target_link_libraries(acquisition PRIVATE
    Qt6::HttpServer
    Qt6::Network
    Qt6::NetworkAuth
    Qt6::Quick
    Qt6::Sql
    boost-headers-only
    json_struct
    QsLog
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
