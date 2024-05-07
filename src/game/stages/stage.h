#pragma once


enum eStages {
    UNDEFINED,
    INTRO_STAGE,
    PLAY_STAGE,
    END_STAGE,

};

class Stage {
    eStages type = UNDEFINED;

public:

    virtual void render(void) {};
    virtual void update(double deltaTime) {};

    virtual void onEnter() {};
    virtual void onExit() {};
};