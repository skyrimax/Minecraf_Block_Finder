# Note that headers are optional, and do not affect add_library, but they will
# not show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later: file(GLOB HEADER_LIST
# CONFIGURE_DEPENDS "${minecraft_block_finder_SOURCE_DIR}/include/modern/*.hpp")
set(HEADER_LIST
    "${finder_lib_SOURCE_DIR}/include/Finder/BlockFinder.hpp"
    "${finder_lib_SOURCE_DIR}/include/Finder/DataExtractor.hpp")

set(EXTERNAL_HEADER_LIST
    "${thread_pool_SOURCE_DIR}/BS_thread_pool.hpp")

# Make an automatic library - will be static or dynamic based on user setting
add_library(finder_library
            BlockFinder.cpp
            DataExtractor.cpp
            ${HEADER_LIST}
            ${EXTERNAL_HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(finder_library PUBLIC
                            ../include/Finder
                            ${thread_pool_SOURCE_DIR})

target_link_libraries(finder_library PUBLIC
                        nlohmann_json::nlohmann_json
                        utility_library)

# All users of this library will need at least C++17
target_compile_features(finder_library PUBLIC cxx_std_17)

add_custom_command(TARGET finder_library POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${nbtexplorer_SOURCE_DIR}/NBTUtil.exe"
    ${RUNTIME_OUTPUT_DIRECTORY}
)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})