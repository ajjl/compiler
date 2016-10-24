CMAKE_MINIMUM_REQUIRED(VERSION 2.7)

# prevent in-source builds
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")

    message(WARNING "SourceDir: ${CMAKE_SOURCE_DIR}")
    message(WARNING "BinDir: ${CMAKE_BINARY_DIR}")

    message(FATAL_ERROR "Dont do in source builds")
endif()

# the main project
project(kestrel)

# include ctest stuff
include(CTest)
enable_testing()

# set compiler flags
set(CFLAGS "${CFLAGS} -g -Wall -Wextra -Wparentheses -Wshadow -Wdouble-promotion -Winline")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CFLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CFLAGS}")

# make and build the google-test framework
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
#include(${CMAKE_SOURCE_DIR}/CMake/External_GTest.cmake)

if(1)
    message(WARNING "SOURCES: ${SOURCES}")

    file(GLOB SOURCES
            *.cpp
            *.h
            )
    list(REMOVE_ITEM SOURCES "${CMAKE_SOURCE_DIR}/testlex.cpp" )
    list(REMOVE_ITEM SOURCES "${CMAKE_SOURCE_DIR}/main.cpp" )

    message(WARNING "SOURCES: ${SOURCES}")
endif()
#add_executable(testlex ${SOURCES} testlex.cpp)
add_library(LEXlib ${SOURCES})
add_executable(kestrel main.cpp main.h)
target_link_libraries(kestrel LEXlib)
add_executable(testlex testlex.cpp)
target_link_libraries(testlex LEXlib)

# the Testing directory
add_subdirectory(Testing)
