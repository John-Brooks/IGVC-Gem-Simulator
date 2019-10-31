cmake_minimum_required (VERSION 3.10.2)
project( igvc-simulator )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_BUILD_TYPE Debug)

if( WIN32 )
	#There doesn't seem to be a clean way to find SDL on Windows since you can extract the libraries anywhere
	set(SDL2_PATH "C:\\SDL2")
endif()

find_package(SDL2 REQUIRED)

include_directories( src ${SDL2_INCLUDE_DIR} )

add_executable( igvc-simulator 
	src/main.cpp
	src/Vehicle.cpp
	src/Collision.cpp
	src/Graphics.cpp
	src/Environment.cpp
	src/Scenario.cpp
	src/tinyxml2.cpp
	src/EndZone.cpp
)

target_link_libraries( igvc-simulator ${SDL2_LIBRARY} )
