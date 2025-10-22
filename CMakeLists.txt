cmake_minimum_required(VERSION 3.25)
project(mini_project)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} src/math/02_algebra/algebra.c src/main.c)
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} m criterion)
