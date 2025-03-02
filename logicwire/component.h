#pragma once

#include "logicwire.h"

class Component: public LogicWire
{
    private:
        string name;
        uint width;
        uint height;
        uint consuming;

    public:
        void setName(string name);
        void setSize(uint width, uint height);
        void setConsuming(uint comsuming);
};