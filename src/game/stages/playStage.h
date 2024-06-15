#pragma once
#include "framework/entities/entityUI.h"
#include "stage.h"
#include "framework/audio.h"


#include <array>

class EntityMissile;
class EntityHealth;
class EntityPower;
class EntityMesh;


class PlayStage : public Stage {
    eStages type = PLAY_STAGE;
public:
    PlayStage();

    std::vector<EntityMesh*> scene_roots;
    float forward_distance = 0.f;
    float last_forward_added = 80.f;
    static int amo;
    float recharge_timer = 0.f;
    float time_played = 0.f;
    static std::array<EntityMissile*, 10> missiles;
    static std::array<EntityHealth*, 5> health;
    static std::array<EntityPower*, 5> power;

    void render() override;
    void update(double deltaTime) override;
    void btnClick(int btn) override;
    static void addMissile(EntityMissile* new_missile);
    static void addHealth(EntityHealth* new_health);
    static void addPower(EntityPower* new_power);
    //~PlayStage();
    
    void onEnter();
    void onExit();
};

