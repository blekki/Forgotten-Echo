#pragma once

#include "zerostate.h"

class Shopstate: public Zerostate
{
    private:
        int shopTextureID;
        int status;
    
    public:
        void render();
        void prerender(){
            return;
        }
        Shopstate();
};