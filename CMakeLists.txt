cmake_minimum_required(VERSION 3.26)
project(HuskyHawksFirstGame LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Download and build SFML 3.0.2
include(FetchContent)
FetchContent_Declare(
  SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 3.0.2
  GIT_SHALLOW TRUE
)

# This downloads AND builds SFML
FetchContent_MakeAvailable(SFML)

# SFML targets are now available directly (no find_package needed)
# They are named: sfml-graphics, sfml-window, sfml-system

add_executable(main
  src/main.cpp
  src/GameManager.cpp
  src/InputManager.cpp
  src/MainManager.cpp
  src/Pad.cpp
  src/TitleScreen.cpp
)
target_compile_features(main PRIVATE cxx_std_17)

# Link to the SFML targets built by FetchContent
target_link_libraries(main PRIVATE 
    sfml-graphics
    sfml-window
    sfml-system
)

# Include directories should be automatically added
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)
