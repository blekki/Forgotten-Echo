#pragma once
#include "Newton.h"

extern NewtonWorld *world;

// save action type (rotate direction). Change when concrete key was pressed
enum action_t{
    ACTION_NOTHING = 0,

    ACTION_ROLL_CW = 1,
    ACTION_ROLL_CCW = 2,
    ACTION_YAW_CW = 4,
    ACTION_YAW_CCW = 8,
    ACTION_PITCH_UP = 16,
    ACTION_PITCH_DOWN = 32,

    ACTION_MOVE_FORWARD = 64,
    ACTION_MOVE_BACK = 128,
    ACTION_MOVE_LEFT = 256,
    ACTION_MOVE_RIGHT = 512,
    ACTION_MOVE_UP = 1024,
    ACTION_MOVE_DOWN = 2048,

    ACTION_HANDING = 4096,
};

constexpr float PI_DIV_180 = 3.1415f / 180.0f;

extern int actionStatus;