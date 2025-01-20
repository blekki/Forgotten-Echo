#include "fstream"

#include <nlohmann/json.hpp>
#include "jsonReader.h"

#include "spaceship.h"

void JsonReader::readJsonPlanet(Planet *planet, string path){
    using json = nlohmann::json;
    ifstream file(path);
    json data = json::parse(file);

    float x = {data["position"][0]["x"]};
    float y = {data["position"][0]["y"]};
    float z = {data["position"][0]["z"]};
    float scale = {data["scale"]};
    float rotateSpeed = {data["rotateSpeed"]};
    string texture = {data["texture"]};

    planet->setPosition(x, y, z);
    planet->setScale(scale);
    planet->setRotateSpeed(rotateSpeed);
    planet->setTexture(texture.c_str());

    file.close();
}

void JsonReader::readJsonSun(Sun *sun, string path){
    using json = nlohmann::json;
    ifstream file(path);
    json data = json::parse(file);

    float x = {data["position"][0]["x"]};
    float y = {data["position"][0]["y"]};
    float z = {data["position"][0]["z"]};
    float scale = {data["scale"]};

    sun->setPosition(x, y, z);
    sun->setScale(scale);

    file.close();
}

void applyCallback(const NewtonBody* const body, dFloat timestep, int threadIndex){
    void *userData = NewtonBodyGetUserData(body);
    Spaceship *spaceship = (Spaceship *) userData;
    spaceship->ApplyForceAndTorque();
}

void JsonReader::readJsonSpaceship(Spaceship *spaceship, string path){
    using json = nlohmann::json;
    ifstream file(path);
    json data = json::parse(file);

    // basic properties (position and scale)
    float x = {data["position"][0]["x"]};
    float y = {data["position"][0]["y"]};
    float z = {data["position"][0]["z"]};
    float scale = {data["scale"]};
    spaceship->setPosition(x, y, z);
    spaceship->setScale(scale);

    // read rotation position
    float rotX = {data["rotation-vec"][0]["x-axis"]};
    float rotY = {data["rotation-vec"][0]["y-axis"]};
    float rotZ = {data["rotation-vec"][0]["z-axis"]};
    spaceship->setRotatationPosition(rotX, rotY, rotZ);

    // speed-up
    float forwardSpeedUp = {data["speed-up"][0]["forward"]};
    float rightSpeedUp = {data["speed-up"][0]["right"]};
    float upSpeedUp = {data["speed-up"][0]["up"]};
    spaceship->setSpeedUp(forwardSpeedUp, rightSpeedUp, upSpeedUp);

    // rotation speed-up
    float rollSpeedUp = {data["rotation-speed-up"][0]["roll"]};
    float yawSpeedUp = {data["rotation-speed-up"][0]["yaw"]};
    float pitchSpeedUp = {data["rotation-speed-up"][0]["pitch"]};
    spaceship->setRotationSpeedUp(rollSpeedUp, yawSpeedUp, pitchSpeedUp);

    // read model place and name
    string folder = {data["path"]};
    string obj = {data["model.obj"]};
    string mtl = {data["model.mtl"]};
    spaceship->newPath(folder);
    spaceship->newModel(folder + obj);
    spaceship->newMaterials(folder + mtl);

    file.close();

    // todo: get a real model size
    NewtonCollision *collision = NewtonCreateBox(world, 0.1, 0.1, 0.1, 0, NULL); // <-- need update
    Matrix4 worldMatrix;
    worldMatrix = spaceship->getRotation();
    worldMatrix.ptr()[12] = spaceship->getX();
    worldMatrix.ptr()[13] = spaceship->getY();
    worldMatrix.ptr()[14] = spaceship->getZ();
    NewtonBody *body = NewtonCreateDynamicBody(world, collision, worldMatrix.ptr());
    float weight = 1;
    NewtonBodySetMassProperties(body, weight, collision);
    NewtonBodySetForceAndTorqueCallback(body, applyCallback);

    // set a few world properties
    NewtonBodySetLinearDamping(body, 0.9f);
    float vec[3] {0.9, 0.9, 0.9};
    NewtonBodySetAngularDamping(body, vec);

    // connect collition to the object
    NewtonDestroyCollision(collision);
    spaceship->setNewtonBody(body);
}