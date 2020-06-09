cmake_minimum_required(VERSION 3.12)
project(HelloOpenGL)

set(CMAKE_CXX_STANDARD 20)

add_executable(HelloOpenGL WIN32 src/main.cpp)

target_include_directories(HelloOpenGL PRIVATE thirdparty/include)

TARGET_LINK_LIBRARIES(HelloOpenGL opengl32)

file(COPY data DESTINATION ${CMAKE_BINARY_DIR})