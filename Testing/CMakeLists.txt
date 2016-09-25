# Run some tests with cmake
message("###$ GTEST_ROOT: ${GTEST_ROOT}")
message("bin: ${CMAKE_BINARY_DIR}")#This is the top level build directory
message("src: ${CMAKE_SOURCE_DIR}")#This is the top level source directory
message("Current bin: ${CMAKE_CURRENT_BINARY_DIR}")# this is the current build directory
message("Current src: ${CMAKE_CURRENT_SOURCE_DIR}")# this is the current source directory

add_test(NAME testlex_parse_HelloWorld.kestrel COMMAND ${CMAKE_BINARY_DIR}/testlex ${CMAKE_CURRENT_SOURCE_DIR}/HelloWorld.kestrel )

# try the google test

find_package(GTEST REQUIRED)
message(WARNING "GTEST_FOUND: ${GTEST_FOUND}")
message(WARNING "GTEST_INCLUDE_DIRS: ${GTEST_INCLUDE_DIRS}")
message(WARNING "GTEST_BOTH_LIBRARIES: ${GTEST_BOTH_LIBRARIES}")
message(WARNING "GTEST_LIBRARIES: ${GTEST_LIBRARIES}")
message(WARNING "GTEST_MAIN_LIBRARIES: ${GTEST_MAIN_LIBRARIES}")
message(WARNING "GTEST_ROOT: ${GTEST_ROOT}")



include_directories(${GTEST_INCLUDE_DIRS})

# I think only one google test can have main?? not sure
add_executable(firstGTest FirstGoogleTest.cpp)
target_link_libraries(firstGTest ${GTEST_LIBRARIES} ${GTEST_BOTH_LIBRARIES})

# Error tests
add_executable(errorTest ErrorTester.cpp ${CMAKE_SOURCE_DIR}/errors.h ${CMAKE_SOURCE_DIR}/errors.cpp)
target_link_libraries(errorTest ${GTEST_LIBRARIES})

# add each google test as a ctest
#GTEST_ADD_TESTS(firstGTest ARGN FirstGoogleTest.cpp)
GTEST_ADD_TESTS(errorTest ARGN ErrorTester.cpp)
