cmake_minimum_required(VERSION 3.14)

project(ForgottenEcho)
add_subdirectory(glfw/)

add_executable(${PROJECT_NAME} ForgottenEcho.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)