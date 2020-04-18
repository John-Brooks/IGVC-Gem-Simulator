cmake_minimum_required (VERSION 3.10.2)
project( IGVCSimulator )

include(GNUInstallDirs)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
SET(CMAKE_CXX_FLAGS "-O0 ${CMAKE_CXX_FLAGS}")

if( WIN32 )
	#There doesn't seem to be a clean way to find SDL on Windows since you can extract the libraries anywhere
	set(SDL2_PATH "C:\\SDL2")
endif()

find_package(SDL2 REQUIRED)

include_directories( src include ${SDL2_INCLUDE_DIR} )

add_executable( IGVCSimulatorTest 
	src/main.cpp
	src/Vehicle.cpp
	src/Collision.cpp
	src/Graphics.cpp
	src/Environment.cpp
	src/Scenario.cpp
	src/tinyxml2.cpp
	src/EndZone.cpp
	src/DistanceSensor.cpp
)

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

add_library( IGVCSimulator SHARED
	src/main.cpp
	src/Vehicle.cpp
	src/Collision.cpp
	src/Graphics.cpp
	src/Environment.cpp
	src/Scenario.cpp
	src/tinyxml2.cpp
	src/EndZone.cpp
	src/DistanceSensor.cpp
    swig/IGVCSimulator_wrap.cxx
)

target_link_libraries( IGVCSimulatorTest ${SDL2_LIBRARY} )
target_link_libraries( IGVCSimulator ${SDL2_LIBRARY} ${PYTHON_LIBRARY})

install(TARGETS ${PROJECT_NAME} DESTINATION lib/${PROJECT_NAME})

file(GLOB HEADERS include/*.h)
install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})
