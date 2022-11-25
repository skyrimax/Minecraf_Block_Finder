add_executable(MinecraftBlockFinder MinecraftBlockFinder.cpp)
target_compile_features(MinecraftBlockFinder PRIVATE cxx_std_17)

target_link_libraries(MinecraftBlockFinder PRIVATE argparse finder_library)

add_custom_command(TARGET MinecraftBlockFinder POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "$<TARGET_FILE_DIR:finder_library>/NBTUtil.exe"
    $<TARGET_FILE_DIR:MinecraftBlockFinder>
)

add_executable(Test test.cpp)
target_compile_features(Test PRIVATE cxx_std_17)

target_link_libraries(Test PRIVATE argparse finder_library)

add_custom_command(TARGET Test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "$<TARGET_FILE_DIR:finder_library>/NBTUtil.exe"
    $<TARGET_FILE_DIR:Test>
)