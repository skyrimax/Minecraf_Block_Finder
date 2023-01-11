# # Testing library
# FetchContent_Declare(
#   catch2
#   GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#   GIT_TAG v2.9.1)
# FetchContent_MakeAvailable(catch2)
# # Adds Catch2::Catch2

# Testing library
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
  coordinate_test
  Coordinate_test.cpp
)

target_link_libraries(
  coordinate_test
  coordinate_library
  GTest::gtest_main
)