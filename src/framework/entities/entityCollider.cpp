#include "entityCollider.h"
#include "framework/camera.h"
#include "graphics/shader.h"
#include "graphics/mesh.h"
#include <algorithm>
#include "game/world.h"
#include "game/game.h"





void EntityCollider::render()
{
 
}



void EntityCollider::update(float deltaTime)
{
	
}
bool EntityCollider::checkPlayerCollisions(const Vector3& target_pos,
	std::vector<sCollisionData>& collisions) {
	Vector3 center = target_pos + Vector3(0.f, 1.25f, 0.f);
	float sphereRadius = 0.75f;
	Vector3 colPoint, colNormal;

	// For each collider entity “e” in root:
	/*std::vector<Entity*> asteroids = Game::instance->play_stage->scene_root->children;

	for (int i  = 0; i < asteroids.size(); ++i)
	{
		EntityMesh* e =  dynamic_cast<EntityMesh*>(asteroids[i]);
		Mesh* mesh = e->mesh;

		if (mesh->testSphereCollision(e->model, center,
			sphereRadius, colPoint, colNormal)) {
			collisions.push_back({ colPoint,
		colNormal.normalize() });
		}
	} 
	*/
	
	// End loop

	return !collisions.empty();
}




