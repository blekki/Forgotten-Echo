cmake_minimum_required(VERSION 3.14)

project(ForgottenEcho)

# include_directories(BEFORE PUBLIC ./lightning)
# include_directories(BEFORE PUBLIC ./shader)
add_executable(${PROJECT_NAME} ForgottenEcho.cpp primal.cpp sphere.cpp planet.cpp object.cpp entity.cpp model.cpp qued.cpp matrices.cpp particlebox.cpp jsonReader.cpp 
                               zerostate.cpp gamestate3d.cpp marsLocation.cpp shopstate.cpp
                               sun.cpp spaceship.cpp
                               cursor.cpp
                               soundtrack.cpp
                               shader/shader.cpp shader/brightness.cpp shader/planetShader.cpp shader/sunShader.cpp
                               logicwire/logicwire.cpp logicwire/board.cpp logicwire/input.cpp logicwire/gate.cpp logicwire/output.cpp logicwire/component.cpp logicwire/pin.cpp logicwire/circuit.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw GL SOIL GLU GLEW newton-dynamics openal opus opusfile png)
# target_include_directories(${PROJECT_NAME} PUBLIC glad/glad)
# target_link_libraries(${PROJECT_NAME} PUBLIC glad)

SET(CMAKE_CXX_FLAGS "-O0 -g2")
SET(CMAKE_C_FLAGS "-O0 -g2")