cmake_minimum_required(VERSION 3.28)
project(HuskyHawksFirstGame LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(HelloWorld src/main.cpp)
target_compile_features(HelloWorld PRIVATE cxx_std_17)
target_link_libraries(HelloWorld PRIVATE SFML::Graphics)
#target_link_libraries(main
#    PRIVATE
#    sfml-graphics
#    sfml-window
#    sfml-system
#)

#
#cmake_minimum_required(VERSION 3.28)
#project(CMakeSFMLProject LANGUAGES CXX)

#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#{ changed code }
#

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT HelloWorld)