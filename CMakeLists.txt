CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

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

# set compiler flags
set(CFLAGS "${CFLAGS} -g -Wall -Wextra -Wparentheses -Wshadow -Wdouble-promotion -Winline")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CFLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CFLAGS}")

# make and build the google-test framework
include(${CMAKE_SOURCE_DIR}/CMake/External_GTest.cmake)

set( SOURCES
        config.h
        errors.cpp
        errors.h
        lexical.cpp
        lexical.h
        lexsupport.cpp
        lexsupport.h
        sets.h
        stringpool.cpp
        stringpool.h
        symboltable.cpp
        symboltable.h
        testlex.cpp
        )

add_executable(testlex ${SOURCES})

# the Testing directory
add_subdirectory(Testing)
