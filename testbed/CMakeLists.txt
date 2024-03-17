file(GLOB_RECURSE TESTBED_SOURCES "src/*.cpp" "src/*.h")

add_executable(gpui-testbed ${TESTBED_SOURCES})

target_include_directories(gpui-testbed
                           PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../include")

target_link_libraries(gpui-testbed PUBLIC gpui)
