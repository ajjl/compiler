# By Alexander Leinoff
# This cmake file was inspired by
# Superbuild structure of BRAINSTools
# http://github.com/BRAINSia/BRAINSTools.git

# Enable ExternalProject CMake module
include(ExternalProject)

# git protocol
if(NOT DEFINED git_protocol)
	set(git_protocol "git")
endif()

# Set google-test variables
set(proj gtest)
set(${proj}_REPOSITORY ${git_protocol}://github.com/google/googletest.git)
set(${proj}_GIT_TAG 43c0ae3375361107286d92e71dc043ae522e7ee4) # This is the last build that passed on github

# Download and install GoogleTest
ExternalProject_Add(
	${proj}
	GIT_REPOSITORY ${${proj}_REPOSITORY}
	GIT_TAG ${${proj}_GIT_TAG}
	SOURCE_DIR ${proj}
	BINARY_DIR ${proj}-build
	
	CMAKE_CACHE_ARGS
	  -DBUILD_GTEST:BOOL=ON

	# Disable install step
	INSTALL_COMMAND ""
)

set(GTEST_ROOT ${CMAKE_BINARY_DIR}/${proj}-build/googlemock/gtest)
set(GTEST_INCLUDE_DIR ${CMAKE_BINARY_DIR}/${proj}/googletest/include)
message("GRoot: ${GTEST_ROOT}")
