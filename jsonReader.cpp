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

void JsonReader::readJsonSpaceship(Object *spaceship, string path){
    using json = nlohmann::json;
    ifstream file(path);
    json data = json::parse(file);

    float x = {data["position"][0]["x"]};
    float y = {data["position"][0]["y"]};
    float z = {data["position"][0]["z"]};
    spaceship->setPosition(x, y, z);

    float scale = {data["scale"]};
    spaceship->setScale(scale);

    string obj = {data["model.obj"]};
    spaceship->newModel(obj);
    string mtl = {data["model.mtl"]};
    spaceship->newMaterials(mtl);

    file.close();
}