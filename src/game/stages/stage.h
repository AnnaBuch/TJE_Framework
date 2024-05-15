#pragma once
#include "framework/entities/entityMesh.h"

enum eStages {
    UNDEFINED,
    INTRO_STAGE,
    PLAY_STAGE,
    END_STAGE,

};

class Stage {
    eStages type = UNDEFINED;

public:

    virtual void render() {};
    virtual void update(double deltaTime) {};

    virtual void onEnter() {};
    virtual void onExit() {};
};

class IntroStage: public Stage {
    eStages type = INTRO_STAGE;


};

class PlayStage : public Stage {
    eStages type = PLAY_STAGE;
public:
    EntityMesh* scene_root = nullptr;

    void render() override;
    void update(double deltaTime) override;

    void onEnter() {};
    void onExit() {};

};

class EndStage : public Stage {
    eStages type = END_STAGE;

};