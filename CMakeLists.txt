cmake_minimum_required(VERSION 3.0)
project(luchok)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FOLDER source)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
find_package(SDL2 REQUIRED)
find_package(Lua 5.4 REQUIRED)

file(GLOB_RECURSE FILES CONFIGURE_DEPENDS ${SOURCE_FOLDER}/*.h ${SOURCE_FOLDER}/*.hpp ${SOURCE_FOLDER}/*.c 
${SOURCE_FOLDER}/*.cpp ${SOURCE_FOLDER}/*.cxx)

include_directories(${SDL2_INCLUDE_DIRS} ${LUA_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${FILES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${LUA_LIBRARIES})