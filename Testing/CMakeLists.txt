# Run some tests with cmake
message("bin: ${CMAKE_BINARY_DIR}")#This is the top level build directory
message("src: ${CMAKE_SOURCE_DIR}")#This is the top level source directory
message("Current bin: ${CMAKE_CURRENT_BINARY_DIR}")# this is the current build directory
message("Current src: ${CMAKE_CURRENT_SOURCE_DIR}")# this is the current source directory

add_test(NAME testlex_parse_HelloWorld.kestrel COMMAND ${CMAKE_BINARY_DIR}/testlex ${CMAKE_CURRENT_SOURCE_DIR}/HelloWorld.kestrel )
