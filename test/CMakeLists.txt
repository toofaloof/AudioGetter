cmake_minimum_required(VERSION 3.22)

project(CursorAudioTest)

# Enable testing support
enable_testing()

# Create the test executable
set(SOURCE_FILES source/AudioProcessorTest.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Include directories for GoogleTest
target_include_directories(${PROJECT_NAME} PRIVATE ${GOOGLETEST_SOURCE_DIR}/googletest/include)

# Link against the AudioPlugin and gtest_main libraries
target_link_libraries(${PROJECT_NAME} PRIVATE AudioPlugin GTest::gtest_main)

# Enable strict C++ warnings and treat them as errors
set_source_files_properties(${SOURCE_FILES} PROPERTIES COMPILE_OPTIONS "${PROJECT_WARNINGS_CXX}")

# Include GoogleTest CMake utilities
include(GoogleTest)

# Register tests with CTest
if(CMAKE_GENERATOR STREQUAL Xcode)
    # Workaround for macOS arm64 test discovery with Xcode
    gtest_discover_tests(${PROJECT_NAME} DISCOVERY_MODE PRE_TEST)
else()
    gtest_discover_tests(${PROJECT_NAME})
endif()
