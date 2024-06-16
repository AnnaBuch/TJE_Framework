#pragma once

#include "framework/entities/entityMesh.h"
class Mesh;

enum eButtonId{
	Undefined,
	PlayButton,
	EndButton,
	PlayAgainButton,
	MenuButton,
	HelpButton,
};

class EntityUI : public EntityMesh {
public:
	EntityUI(Vector2 size, const Material& material);
	EntityUI(Vector2 position, Vector2 size, const Material& material, eButtonId buttonId = Undefined );
	~EntityUI() {};

	Vector2 position;
	Vector2 size;

	bool visible = true; 

	Camera* camera2d;

	Mesh* quad;

	eButtonId buttonId;
	Material material;

	void render(Camera* camera2d);
	void update(float seconds_elapsed);

};