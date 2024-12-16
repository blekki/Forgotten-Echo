cmake_minimum_required(VERSION 3.14)

project(ForgottenEcho)

add_executable(${PROJECT_NAME} ForgottenEcho.cpp sphere.cpp planet.cpp model.cpp object.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw GL SOIL GLU)
# target_include_directories(${PROJECT_NAME} PUBLIC glad/glad)
# target_link_libraries(${PROJECT_NAME} PUBLIC glad)

SET(CMAKE_CXX_FLAGS "-O0 -g2")
SET(CMAKE_C_FLAGS "-O0 -g2")