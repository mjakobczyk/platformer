#sets up the minimum version of cmake
cmake_minimum_required(VERSION 3.12) # personally I'd set this version as low as required; you don't have to require the cutting edge version

#how the project will be called
project (platformer)

#set the C++ standard to be used
set (CMAKE_CXX_STANDARD 14)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set (SFML_ROOT "D:/SFML")

#set source files
set (SOURCE_FILES 
	src/main.cpp
)

#look for SFML and add it
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

#we add the executable of the program
add_executable (program ${SOURCE_FILES})
target_link_libraries(program ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})