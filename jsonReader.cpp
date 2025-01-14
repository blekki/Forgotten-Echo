#include "fstream"

#include "jsonReader.h"
#include "json/single_include/nlohmann/json.hpp"

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

void JsonReader::readJsonSpaceship(Object *object, string path){
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
}