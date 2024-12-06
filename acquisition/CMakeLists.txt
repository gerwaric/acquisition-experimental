
# This folder is structured differently from libacq and the external
# libraries because I could not find a way to use the canonical project
# structure with Qt QML without making confusing compromises.

qt_add_executable(acquisition WIN32 MACOSX_BUNDLE
    "src/acquisition.cpp"
    "src/acquisition.h"
    "src/float_filter.cpp"
    "src/float_filter.h"
    "src/main.cpp"
    "src/proxy_model.cpp"
    "src/proxy_model.h"
    "src/search.cpp"
    "src/search.h"
    "src/search_filters.cpp"
    "src/search_filters.h"
    "src/settings.cpp"
    "src/settings.h"
)

# The src directory needs to be on the path because c++
# classes declared with QML_ELEMENT need to be found
# directly on the include path, not in a subdirectory.
target_include_directories(acquisition PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
#    ${CMAKE_CURRENT_SOURCE_DIR}/qml
)

target_link_libraries(acquisition PRIVATE
    Qt6::Quick
    libacq
)

set_target_properties(acquisition PROPERTIES
    QT_QMLCACHEGEN_ARGUMENTS "--verbose"
)

qt_add_qml_module(acquisition URI MyAcquisition VERSION 1.0
    QML_FILES
    qml/Main.qml
    #
    qml/ActionListMenu.qml
    #acquisition/acquisition/qml/AutoComplete.qml
    #acquisition/acquisition/qml/IntField.qml
    qml/MainMenuBar.qml
    qml/SearchFilterGroup.qml
    #
    qml/SearchFilters/ArmourFilters.qml
    qml/SearchFilters/FilterSectionHeader.qml
    qml/SearchFilters/HeistFilters.qml
    qml/SearchFilters/MapFilters.qml
    qml/SearchFilters/MiscellaneousFilters.qml
    qml/SearchFilters/RequirementFilters.qml
    qml/SearchFilters/SanctumFilters.qml
    qml/SearchFilters/SocketFilters.qml
    qml/SearchFilters/TypeFilters.qml
    qml/SearchFilters/UltimatumFilters.qml
    qml/SearchFilters/WeaponFilters.qml
    #acquisition/acquisition/qml/MinField.qml
    #
    qml/SearchFilters/AttributeFilters.qml
    qml/SearchFilters/ResistanceFilters.qml
    #acquisition/acquisition/qml/MaxField.qml
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
