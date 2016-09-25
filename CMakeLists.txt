CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

# prevent in-source builds
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")

    message(WARNING "SourceDir: ${CMAKE_SOURCE_DIR}")
    message(WARNING "BinDir: ${CMAKE_BINARY_DIR}")

    message(FATAL_ERROR "Dont do in source builds")
endif()

project(kestrel)

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
