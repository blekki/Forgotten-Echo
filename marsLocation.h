#pragma once
#include "gamestate3d.h"

#include "primal.h"
#include "planet.h"
#include "sun.h"
#include "particlebox.h"
#include "spaceship.h"

class MarsLocation : public Gamestate3d
{
    private:
        int personView;

        Primal primal;
        Planet mars;
        Planet moon;
        Planet mercury;
        Sun sun;

        Spaceship spaceship;
        Spaceship mothership;
        Spaceship testObj;

        ParticleBox particle;

    public:
        void pushPersonView(int viewType);
        virtual void pushActionStatus(int actionStatus) override;


        void renderObjects();
        virtual void prerender() override;
        virtual void render() override;

        MarsLocation();
};