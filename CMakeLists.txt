cmake_minimum_required(VERSION 3.12)

project (platformer)

set (CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# set (SFML_ROOT "D:/SFML")
# set (SFML_ROOT "/Users/Majki/Local/SFML")

set (SOURCE_FILES 
	src/main.cpp
	src/animation.cpp
	src/button.cpp
	src/character.cpp
	src/constants.cpp
	src/enemy.cpp
	src/engine.cpp
	src/entity.cpp
	src/game.cpp
	src/game-over.cpp
	src/hero.cpp
	src/interface.cpp
	src/level.cpp
	src/menu.cpp
	src/moveable.cpp
	src/other.cpp
	src/resources.cpp
	src/spell.cpp
	src/stable.cpp
	src/tile.cpp
)

set (HEADER_FILES
	include/animation.h
	include/button.h
	include/basic.h
	include/character.h
	include/constants.h
	include/enemy.h
	include/engine.h
	include/entity.h
	include/game.h
	include/game-over.h
	include/hero.h
	include/interface.h
	include/level.h
	include/menu.h
	include/moveable.h
	include/resources.h
	include/spell.h
	include/stable.h
	include/tile.h
	include/wektor.h
)

# Look for SFML and add it
set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package (SFML COMPONENTS system window graphics network audio)

if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
else()
	message(${SFML_INCLUDE_DIR})
	set(SFML_ROOT "" CACHE PATH "SFML top-level directory")
	message("\n-> SFML directory not found. Set SFML_ROOT to SFML's top-level path (containing \"include\" and \"lib\" directories).")
	message("-> Make sure the SFML libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
endif()

# Add executable to the program
add_executable (program ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(program ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})