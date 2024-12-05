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

add_subdirectory("acquisition")
add_subdirectory("acquisition/api_types")
add_subdirectory("acquisition/data_model")
add_subdirectory("acquisition/data_stores")
add_subdirectory("acquisition/oauth")
#add_subdirectory("acquisition/qml") # This currently lives in the top-level CMakeLists.txt
add_subdirectory("acquisition/rate_limit")
add_subdirectory("acquisition/search_filters")
add_subdirectory("acquisition/utils")
