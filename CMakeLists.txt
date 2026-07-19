cmake_minimum_required(VERSION 3.21)
project(martebursdag LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SFML COMPONENTS System Window Graphics Audio CONFIG REQUIRED)

add_executable(martebursdag
    src/main.cpp
    src/pokemon/Pokemon.cpp
    src/pokemon/Pokemon_loader.cpp
    src/pokemon/Stats.cpp
    src/move/Move.cpp
    src/move/Move_loader.cpp
    src/move/Move_display.cpp
    src/move/Protect.cpp
    src/typechart/TypeChart.cpp
    src/battle/DamageCalc.cpp
    src/battle/StatusDamage.cpp
    src/battle/Simulator.cpp
)

target_include_directories(martebursdag PRIVATE include)

target_link_libraries(martebursdag PRIVATE
    SFML::System
    SFML::Window
    SFML::Graphics
    SFML::Audio
)
