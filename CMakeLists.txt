cmake_minimum_required(VERSION 3.22)

project(CursorAudioPlugin)

set(CMAKE_CXX_STANDARD 20)

set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)

include(cmake/cpm.cmake)

# This commands downloads AND configures JUCE. It sets up some variables, like JUCE_SOURCE_DIR.

cpmaddpackage(
  NAME
  JUCE
  GIT_TAG 8.0.6
  VERSION 8.0.6
  GITHUB_REPOSITORY
  juce-framework/JUCE
  SOURCE_DIR
  ${LIB_DIR}/juce
)




# Add compiler warning utilities
include(cmake/CompilerWarnings.cmake)
include(cmake/Util.cmake)


# Adds all the targets configured in the "plugin" folder.
add_subdirectory(plugin)
