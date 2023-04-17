cmake_minimum_required(VERSION 3.15)

project(JuceProject VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(JUCE) # Path to the JUCE library

add_executable(JuceProject src/main.cpp)

target_include_directories(JuceProject PRIVATE
    ${JUCE_DIR}/modules
)

target_link_libraries(JuceProject PRIVATE
    juce::juce_analytics
    juce::juce_audio_basics
    juce::juce_audio_devices
    juce::juce_audio_formats
    juce::juce_audio_plugin_client
    juce::juce_audio_processors
    juce::juce_audio_utils
    juce::juce_box2d
    juce::juce_core
    juce::juce_cryptography
    juce::juce_data_structures
    juce::juce_dsp
    juce::juce_events
    juce::juce_graphics
    juce::juce_gui_basics
    juce::juce_gui_extra
    juce::juce_opengl
    juce::juce_osc
    juce::juce_product_unlocking
    juce::juce_video
)


# Enable JUCE's module header magic
target_compile_definitions(JuceProject PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_APP_VERSION_STRING="1.0.0"
    JUCE_APP_VERSION=0x10000
)
