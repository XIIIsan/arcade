cmake_minimum_required(VERSION 3.9)
project(cpp_arcade)

set(CMAKE_CXX_STANDARD 11)
set(APP_INCLUDE ./include)

include_directories(${APP_INCLUDE})

add_library(lib_arcade_pacman.so SHARED
        games/pacman/PacmanGame.cpp games/pacman/PacmanGame.hpp
        games/pacman/entryPoint.cpp games/solarfox/Player.cpp
        games/solarfox/Player.hpp games/pacman/Enemy.cpp
        games/pacman/Enemy.hpp games/pacman/ACharacter.cpp games/pacman/ACharacter.hpp)

add_library(lib_arcade_solarfox.so SHARED
        games/solarfox/entryPoint.cpp games/solarfox/SolarFoxGame.cpp games/solarfox/SolarFoxGame.hpp games/solarfox/Beam.cpp games/solarfox/Beam.hpp games/solarfox/Enemy.cpp games/solarfox/Enemy.hpp)

add_library(lib_arcade_sdl2.so SHARED
        lib/sdl2/SDL2GraphicLib.cpp lib/sdl2/SDL2GraphicLib.hpp
        lib/sdl2/entryPoint.cpp)

add_library(lib_arcade_ncurse.so SHARED
        lib/ncurse/NCursesGraphicLib.cpp lib/ncurse/NCursesGraphicLib.hpp
        lib/ncurse/entryPoint.cpp)

add_library(lib_arcade_sfml.so SHARED
        lib/sfml/SFMLGraphicLib.cpp lib/sfml/SFMLGraphicLib.hpp
        lib/sfml/entryPoint.cpp)

add_executable(cpp_arcade
        src/main.cpp
        include/Core/LibsHandler.hpp
        include/Core/DLLoader.hpp
        src/FileManager.cpp include/Core/FileManager.hpp
        src/Core.cpp include/Core/Core.hpp
        utils/Color.cpp
        utils/PixelBox.cpp
        utils/TextBox.cpp src/Menu.cpp include/Core/Menu.hpp include/Core/Keys.hpp)

target_link_libraries(cpp_arcade dl)
