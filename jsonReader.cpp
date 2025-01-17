#include "fstream"

#include "ForgottenEcho.h"
#include "jsonReader.h"
#include "json/single_include/nlohmann/json.hpp"

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

void JsonReader::readJsonSpaceship(Spaceship *object, string path){
    using json = nlohmann::json;
    ifstream file(path);
    json data = json::parse(file);

    float x = {data["position"][0]["x"]};
    float y = {data["position"][0]["y"]};
    float z = {data["position"][0]["z"]};
    float scale = {data["scale"]};

    float rotX = {data["rotation_vec"][0]["x_axis"]};
    float rotY = {data["rotation_vec"][0]["y_axis"]};
    float rotZ = {data["rotation_vec"][0]["z_axis"]};
    object->setRotatationPosition(rotX, rotY, rotZ);

    string folder = {data["path"]};
    string obj = {data["model.obj"]};
    string mtl = {data["model.mtl"]};

    object->setPosition(x, y, z);
    object->setScale(scale);
    object->newPath(folder);
    object->newModel(folder + obj);
    object->newMaterials(folder + mtl);

    file.close();

    // todo: get real model size
    NewtonCollision *collision = NewtonCreateBox(world, 0.1, 0.1, 0.1, 0, NULL);
    Matrix4 worldMatrix;
    worldMatrix = object->getRotation();
    worldMatrix.ptr()[12] = object->getX();
    worldMatrix.ptr()[13] = object->getY();
    worldMatrix.ptr()[14] = object->getZ();
    NewtonBody *body = NewtonCreateDynamicBody(world, collision, worldMatrix.ptr());
    float weight = 1;
    NewtonBodySetMassProperties(body, weight, collision);
    NewtonBodySetForceAndTorqueCallback(body, applyCallback);

    NewtonDestroyCollision(collision);
    object->setNewtonBody(body);
}