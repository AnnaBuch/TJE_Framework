#pragma once
#include "framework/entities/entityMesh.h"
#include <map>

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

    virtual void onEnter() {};
    virtual void onExit() {};
    virtual void btnClick(int btn) {};
};

class IntroStage: public Stage {
    eStages type = INTRO_STAGE;
public:
    void render() override;
    void update(double deltaTime) override;
    void onEnter() {};
    void onExit() {};
};

class PlayStage : public Stage {
    eStages type = PLAY_STAGE;
public:
    std::vector<EntityMesh*> scene_roots;
    float forward_distance = 0.f;
    float last_forward_added = 80.f;
    int amo = 10;
    float recharge_timer = 0.f;
    std::vector<EntityMissile*> missiles;
    std::vector<EntityHealth*> health;
    std::vector<EntityPower*> power;
    //std::map<EntityMissile*, EntityMesh*> missiles;

    void render() override;
    void update(double deltaTime) override;
    void btnClick(int btn) override;
    //EntityMissile* shoot();
    
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