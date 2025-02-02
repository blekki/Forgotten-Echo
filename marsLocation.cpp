#include "jsonReader.h"

#include "primal.h"
#include "planet.h"
#include "sun.h"
#include "particlebox.h"
#include "spaceship.h"

#include "marsLocation.h"

void MarsLocation::prerender(){
    sun.pushWindowSize(windowLink);
    sun.prerender(sunShader);
}

void MarsLocation::pushPersonView(int viewType){
    this->personView = viewType;
}

void MarsLocation::pushActionStatus(int actionStatus){
    this->spaceship.newActionStatus(actionStatus);
}

void MarsLocation::renderObjects(){
    Vec3 whereIam {spaceship.getX(), spaceship.getY(), spaceship.getZ()};
    Vec3 forward = multiplyMatrixVec(spaceship.makeModelMatrix(), Vec3 {0, 0, -1});
    Vec3 to = whereIam + forward;
    Vec3 preUp = multiplyMatrixVec(spaceship.makeModelMatrix(), Vec3 {0, 1, 0});
    if (personView == 1) {
        glLoadIdentity();
        gluLookAt(whereIam.x, whereIam.y, whereIam.z,
                    to.x, to.y, to.z,
                    preUp.x, preUp.y, preUp.z);
    }
    else {
        glLoadIdentity();
        gluLookAt(50, 0, 0,
                    spaceship.getX(), spaceship.getY(), spaceship.getZ(),
                    0, 1, 0);
    }

    glUseProgram(brightnessShader.getShaderID());
    brightnessShader.setSun(sun.getXYZ());
    mothership.draw(brightnessShader);
    testObj.draw(brightnessShader);

    // spaceship.newActionStatus(actionStatus);
    cursor.pushWindowSize(windowLink);
    if (!personView) {
        spaceship.draw(brightnessShader);
    }
    else {
        spaceship.mouseRotation(cursor.getTransformX(), cursor.getTransformY());
    }

    glUseProgram(planetShader.getShaderID());
    planetShader.setSun(sun.getXYZ());
    mars.draw(planetShader, spaceship.getXYZ());
    moon.draw(planetShader, spaceship.getXYZ());
    mercury.draw(planetShader, spaceship.getXYZ());
    glUseProgram(0);

    sun.draw(spaceship.getXYZ());
        
    // replace particalBox around your spaceship
    particle.newBoxPosition(spaceship.getX(), spaceship.getY(), spaceship.getZ());
    particle.draw();

    // draw axis
    primal.drawFollowCoord(spaceship.makeModelMatrix());
    primal.drawCoord();

    // draw cursor
    cursor.draw();
}

void MarsLocation::render(){
    prepareMatrix();
    pushPersonView(personView);
    renderObjects();
}

MarsLocation::MarsLocation(){
    personView = 0;

    
    JsonReader jsonReader;
    // planets creating
    jsonReader.readJsonPlanet(&mars, "characters/planets/mars.json");
    jsonReader.readJsonPlanet(&moon, "characters/planets/moon.json");
    jsonReader.readJsonPlanet(&mercury, "characters/planets/mercury.json");
    jsonReader.readJsonSun(&sun, "characters/planets/sun.json");

    jsonReader.readJsonSpaceship(&spaceship, "characters/objects/myship.json");
    spaceship.setControlStatus(true);
    spaceship.pushWindowSize(&screen_width, &screen_height);
    jsonReader.readJsonSpaceship(&mothership, "characters/objects/mothership.json");
    mothership.newActionStatus(ACTION_ROLL_CW);
    jsonReader.readJsonSpaceship(&testObj, "characters/objects/test.json");

    particle.newGenerate();
}