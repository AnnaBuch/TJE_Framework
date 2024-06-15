#pragma once
#include "framework/entities/entityMesh.h"
#include "framework/entities/entityUI.h"
#include "framework/audio.h"


#include <map>
#include <array>

class EntityMissile;
class EntityHealth;
class EntityPower;

enum eStages {
    UNDEFINED,
    INTRO_STAGE,
    PLAY_STAGE,
    VICTORY_STAGE,
    LOSING_STAGE

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
    HCHANNEL theme;

};

class IntroStage: public Stage {
    eStages type = INTRO_STAGE;
public:
    IntroStage();
    void render() override;
    void update(double deltaTime) override;
    void onEnter();
    void onExit();
    bool menuInitialized = false;
    EntityUI* background = nullptr;
    EntityUI* play_button = nullptr;
    EntityUI* exit_button = nullptr;
    Camera* camera2d = nullptr;
};




class VictoryStage : public Stage {
    eStages type = VICTORY_STAGE;
public:
    VictoryStage();
    void render() override;
    void update(double deltaTime) override;
    void onEnter();
    void onExit();
};

class LosingStage : public Stage {
    eStages type = LOSING_STAGE;
public:
    LosingStage();
    void render() override;
    void update(double deltaTime) override;
    void onEnter();
    void onExit();

};