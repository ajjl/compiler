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
        errors.c
        errors.h
        lexical.c
        lexical.h
        lexsupport.c
        lexsupport.h
        sets.h
        stringpool.c
        stringpool.h
        symboltable.c
        symboltable.h
        testlex.c
        )

set_source_files_properties(${SOURCES} PROPERTIES LANGUAGE CXX)

add_executable(testlex ${SOURCES})
