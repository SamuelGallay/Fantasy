cmake_minimum_required(VERSION 3.1)

set (CMAKE_CXX_STANDARD 11)

project(Fantasy)

if(MSVC)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(SFML_STATIC_LIBRARIES TRUE)
endif(MSVC)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

include_directories(headers/)

set(
	SOURCES
	sources/main.cpp
	sources/Application.cpp
	sources/Player.cpp
	sources/Level.cpp
	sources/TileMap.cpp
)

add_executable(Fantasy ${SOURCES})
target_link_libraries(Pong sfml-graphics sfml-audio)

# Install executable
install(TARGETS Fantasy
		RUNTIME DESTINATION .)

# Install game data
install(DIRECTORY media
		DESTINATION .)
