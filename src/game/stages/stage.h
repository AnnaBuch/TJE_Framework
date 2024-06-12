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
    MENU,
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
    std::array<EntityMissile*, 10> missiles;
    std::vector<EntityHealth*> health;
    std::vector<EntityPower*> power;
    //std::map<EntityMissile*, EntityMesh*> missiles;

    void render() override;
    void update(double deltaTime) override;
    void btnClick(int btn) override;
    void addMissile(EntityMissile* new_missile);
    PlayStage();
    //EntityMissile* shoot();
    
    void onEnter() {};
    void onExit() {};
};

class Menu : public Stage {

    eStages type = MENU;
public:
    Menu() {};

    Texture* fondo;
    int world_width;
    int world_height;

    Camera* camera2d;

    Entity* background;
    Entity* play_button;
    Entity* exit_button;


    void init();
    void restart();
    void render();
    void update(float seconds_elapsed);
    void onButtonPressed(eButtonId buttonid) {};
};


class EndStage : public Stage {
    eStages type = END_STAGE;
public:
    void render() override;
    void update(double deltaTime) override;
    void onEnter() {};
    void onExit() {};
};