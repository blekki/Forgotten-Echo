cmake_minimum_required(VERSION 3.14)

project(ForgottenEcho)

add_executable(${PROJECT_NAME} ForgottenEcho.cpp glfw/include/GLFW)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw GL)
# target_include_directories(${PROJECT_NAME} PUBLIC glad/glad)
# target_link_libraries(${PROJECT_NAME} PUBLIC glad)

