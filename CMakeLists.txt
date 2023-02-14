cmake_minimum_required(VERSION 3.16)
project(Connect4_AI)

set(CMAKE_CXX_STANDARD 20)

# Specify the include directories
set(SFML_ROOT "C:/SFML")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system graphics window)
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Copy dlls to build
if (WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
    file(GLOB MINGW_DEP_DLLS "C:/mingw64/bin/*.dll")
    file(COPY ${MINGW_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif ()

# Sources
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.hpp src/*.hpp)

# Executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} include/player/Player.hpp include/game_logic/Coord.hpp src/game_logic/Coord.cpp src/player/Player.cpp include/player/PlayerColor.hpp include/player/HumanPlayer.hpp include/player/AIPlayer.hpp src/player/MinimaxAI.cpp include/player/MinimaxAI.hpp)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR} include)
    target_link_libraries(Connect4_AI ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
else ()
    message("SFML not found.")
endif ()