cmake_minimum_required(VERSION 3.22)

# Version is needed by JUCE.
project(CursorAudio VERSION 0.1.0)

# A subfolder in include/ helps avoid name clashes later on.
set(INCLUDE_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/include/CursorAudio"
)

# Adds a JUCE plugin target (like Projucer does).
juce_add_plugin(
    ${PROJECT_NAME}
    COMPANY_NAME              "toofaloof"
    IS_SYNTH                  FALSE
    NEEDS_MIDI_INPUT          FALSE
    NEEDS_MIDI_OUTPUT         FALSE
    PLUGIN_MANUFACTURER_CODE  Toof
    PLUGIN_CODE               Aiii
    FORMATS                   Standalone VST3
    PRODUCT_NAME              "CursorAudio"
    MODULES
        juce_audio_processors
        juce_audio_basics
        juce_audio_formats
        juce_core
        juce_gui_basics
)


juce_generate_juce_header(${PROJECT_NAME})

# Source files
set(SOURCE_FILES
    source/PluginEditor.cpp
    source/PluginProcessor.cpp
)

# Header files (for IDE file‐tree grouping)
set(HEADER_FILES
    ${INCLUDE_DIR}/PluginEditor.h
    ${INCLUDE_DIR}/PluginProcessor.h
)

target_sources(
    ${PROJECT_NAME}
    PRIVATE
        ${SOURCE_FILES}
        ${HEADER_FILES}
)

# Include directories
target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link JUCE modules
# If you add more JUCE modules (e.g. DSP), list them here.
target_link_libraries_system(
    ${PROJECT_NAME}
    PUBLIC
        juce::juce_audio_utils
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

# Recommended JUCE defines
target_compile_definitions(
    ${PROJECT_NAME}
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)

# Enable strict C++ warnings (treat warnings as errors)
set_source_files_properties(
    ${SOURCE_FILES}
    PROPERTIES
        COMPILE_OPTIONS "${PROJECT_WARNINGS_CXX}"
)

# Nice grouping of files in Visual Studio “Filters”
source_group(
    TREE ${CMAKE_CURRENT_SOURCE_DIR}/..
)
