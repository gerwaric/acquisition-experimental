 target_include_directories(acquisition PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# The next line is a compromise that violates the
# rest of this project's organization because c++
# objects declared QML_ELEMENT need to be found
# directly on the include path, no in a subdirectory.
target_include_directories(acquisition PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/acquisition
)

target_sources(acquisition PRIVATE
    "acquisition/acquisition.cpp"
    "acquisition/acquisition.h"
    "acquisition/float_filter.cpp"
    "acquisition/float_filter.h"
    "acquisition/main.cpp"
    "acquisition/proxy_model.cpp"
    "acquisition/proxy_model.h"
    "acquisition/search.cpp"
    "acquisition/search.h"
    "acquisition/search_filters.cpp"
    "acquisition/search_filters.h"
    "acquisition/settings.cpp"
    "acquisition/settings.h"
)

add_subdirectory("acquisition/search_filters")
