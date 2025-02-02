#pragma once

#include "zerostate.h"

class Shopstate: public Zerostate
{
    private:
        int shopTextureID;
        int status;
    
    public:
        virtual void pushActionStatus(int actionStatus) override {};
        virtual void render() override;
        virtual void prerender() override;
        Shopstate();
};