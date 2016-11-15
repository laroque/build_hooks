# GetVersion.cmake
# Author: N. Oblath
#
# Usage in top CMakeLists.txt: include GetVersion.cmake
#
# Expects the version to be in the file VERSION in the top source directory, 
# with the major version, minor version, and revision numbers as the only 
# contents of the file, separated by spaces.
#
# Sets the following variables:
#   PROJECT_VERSION_MAJOR
#   PROJECT_VERSION_MINOR
#   PROJECT_REVISION


# Make sure we have the VERSION file
find_file( VERSION_FILE VERSION ${CMAKE_CURRENT_SOURCE_DIR} NO_DEFAULT_PATH )
if( NOT EXISTS ${VERSION_FILE} )
    message( FATAL_ERROR "Did not find VERSION file" )
endif( NOT EXISTS ${VERSION_FILE} )

# Read the contents of VERSION
file( READ ${VERSION_FILE} VERSION_STRING )

# Parse the version string into a list
separate_arguments( VERSION_LIST UNIX_COMMAND ${VERSION_STRING} )

# Put the version numbers into separate variables
list( GET VERSION_LIST 0 PROJECT_VERSION_MAJOR )
list( GET VERSION_LIST 1 PROJECT_VERSION_MINOR )
list( GET VERSION_LIST 2 PROJECT_REVISION )

message( STATUS "Project version: ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_REVISION}")
