#pragma once
#include "framework/entities/entityMesh.h"
#include "framework/entities/entityUI.h"

#include <map>
#include <array>

class EntityMissile;
class EntityHealth;
class EntityPower;

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
    bool isEnded;

    virtual void onEnter() {};
    virtual void onExit() {};
    virtual void btnClick(int btn) {};
};

class IntroStage: public Stage {
    eStages type = INTRO_STAGE;
public:
    void init();
    void render() override;
    void update(double deltaTime) override;
    void onEnter() {};
    void onExit() {};
};




class EndStage : public Stage {
    eStages type = END_STAGE;
public:
    void render() override;
    void update(double deltaTime) override;
    void onEnter() {};
    void onExit() {};
};