cmake_minimum_required(VERSION 3.25)
project(mini_project)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)

add_executable(${PROJECT_NAME} src/main.c src/math/02_algebra/algebra.c)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} m)

enable_testing()
add_subdirectory(tests)
