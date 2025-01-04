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
    planet->setPosition(x, y, z);

    float scale = {data["scale"]};
    planet->setScale(scale);

    float rotateSpeed = {data["rotateSpeed"]};
    planet->setRotateSpeed(rotateSpeed);

    string texture = {data["texture"]};
    planet->setTexture(texture.c_str());

    file.close();
}

void JsonReader::readJsonSpaceship(Object *object, string path){
    using json = nlohmann::json;
    ifstream file(path);
    json data = json::parse(file);

    float x = {data["position"][0]["x"]};
    float y = {data["position"][0]["y"]};
    float z = {data["position"][0]["z"]};
    object->setPosition(x, y, z);

    float scale = {data["scale"]};
    object->setScale(scale);

    string folder = {data["path"]};
    object->newPath(folder);

    string obj = {data["model.obj"]};
    object->newModel(folder + obj);
    string mtl = {data["model.mtl"]};
    object->newMaterials(folder + mtl);

    file.close();
}