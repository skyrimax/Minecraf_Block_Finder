# Works with 3.14
cmake_minimum_required(VERSION 3.14)

# Project name and a few useful settings. Other commands can pick up the results
project(
    finder_lib
    VERSION 0.1
    DESCRIPTION "Library to extract the coordinates of all blocks of specified IDs in a Minecraft world"
    LANGUAGES CXX)

# Only do these if this is the main project, and not if it is included through
# add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # Let's ensure -std=c++xx instead of -std=g++xx
    set(CMAKE_CXX_EXTENSIONS OFF)

    # Let's nicely support folders in IDE's
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    # Testing only available if this is the main app. Note this needs to be done
    # in the main CMakeLists since it calls enable_testing, which must be in the
    # main CMakeLists.
    include(CTest)

    # Docs only available if this is the main app
    find_package(Doxygen)
    if(Doxygen_FOUND)
        add_subdirectory(docs)
    else()
        message(STATUS "Doxygen not found, not building docs")
    endif()
endif()

include(FetchContent)

# Fetch NBTExplorer release 2.8.0 to use NBTUtils, essential par of this library at the moment
FetchContent_Declare(
    NBTExplorer
    URL https://github.com/jaquadro/NBTExplorer/releases/download/v2.8.0-win/NBTExplorer-2.8.0.zip
    #DOWNLOAD_EXTRACT_TIMESTAMP True
)
FetchContent_MakeAvailable(NBTExplorer)
message("NBTExplorer folder id : ${nbtexplorer_SOURCE_DIR}")

# Fetch version 3.11.2 of nlohmann json
FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
    #DOWNLOAD_EXTRACT_TIMESTAMP True
)
FetchContent_MakeAvailable(json)

# fetch latest argparse
FetchContent_Declare(
    thread_pool
    GIT_REPOSITORY https://github.com/bshoshany/thread-pool
)
FetchContent_MakeAvailable(thread_pool)

# Load Utility library
add_subdirectory(Coordinate)

# Load external dependencies
add_subdirectory(extern)

# The compiled library code is here
add_subdirectory(src)

# The executable code is here
add_subdirectory(apps)

# Testing only available if this is the main app
if(BUILD_TESTING)
  add_subdirectory(tests)
endif()