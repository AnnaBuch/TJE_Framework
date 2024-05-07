#pragma once

#include "entityMesh.h"

struct sCollisionData {
	Vector3 colPoint;
	Vector3 colNormal;
};

enum {
	NONE = 0,
	FLOOR = 1 << 0,
	WALL = 1 << 1,
	PLAYER = 1 << 2,
	ENEMY = 1 << 3,
	// Both WALL and FLOOR are considered SCENARIO
	// using OR operator
	SCENARIO = WALL | FLOOR,
	ALL = 0xFF
};

class EntityCollider : public EntityMesh
{
public:
	void render();
	void update(float elapsed_time);

	int layer = NONE;



};
