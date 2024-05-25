#include "world.h"
#include "framework/includes.h"
#include "framework/camera.h"
#include "framework/entities/entityMesh.h"
#include "framework/entities/entityPlayer.h"

#include "graphics/mesh.h"
#include "graphics/shader.h"
#include "graphics/texture.h"
#include "game/game.h"
#include <fstream> 


World::World() 
{
	Camera* camera = Camera::current;
	//camera = new Camera();
	// Create our camera
	//this->root = root;


	Material landscape_cubemap;
	landscape_cubemap.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/cubemap.fs");
	landscape_cubemap.diffuse = new Texture();
	//TODO: buscar pngs 
	landscape_cubemap.diffuse->loadCubemap("landscape", {
	"data/px.png",
	"data/nx.png",
	"data/ny.png",
	"data/py.png",
	"data/pz.png",
	"data/nz.png"
		});

	skybox = new EntityMesh(Mesh::Get("data/meshes/cubemap.ASE"), landscape_cubemap, "");
	player = new EntityPlayer();

	camera->setPerspective(70.f, Game::instance->window_width / (float)Game::instance->window_height, 0.1f, 1000.f); //set the projection, we want to be perspective
	//camera->lookAt(Vector3(0.f, 10.f, 10.f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f)); //position the camera and point to 0,0,0

	//camera->rotate(180.f, camera->up);
	/*landscape_cubemap.diffuse->loadCubemap("landscape", {
		"data/textures/skybox/right.png",
		"data/textures/skybox/left.png",
		"data/textures/skybox/bottom.png",
		"data/textures/skybox/top.png",
		"data/textures/skybox/front.png",
		"data/textures/skybox/back.png"
		});*/


}/*
void World::render() {


}

void World::update(double deltaTime) {

}*/

bool World::parseScene(const char* filename, EntityMesh* root, float translation)
{
	
	std::cout << " + Scene loading: " << filename << "..." << std::endl;

	meshes_to_load.clear();

	std::ifstream file(filename);

	if (!file.good()) {
		std::cerr << "Scene [ERROR]" << " File not found!" << std::endl;
		return false;
	}

	std::string scene_info, mesh_name, model_data;
	file >> scene_info; file >> scene_info;
	int mesh_count = 0;

	// Read file line by line and store mesh path and model info in separated variables
	while (file >> mesh_name >> model_data)
	{
		if (mesh_name[0] == '#')
			continue;

		// Get all 16 matrix floats
		std::vector<std::string> tokens = tokenize(model_data, ",");

		// Fill matrix converting chars to floats
		Matrix44 model;
		for (int t = 0; t < tokens.size(); ++t) {
			model.m[t] = (float)atof(tokens[t].c_str());
		}

		// Add model to mesh list (might be instanced!)
		sRenderData& render_data = meshes_to_load[mesh_name];
		//model.translate(0.f, 0.f, translation);
		render_data.models.push_back(model);
		mesh_count++;
	}

	// Iterate through meshes loaded and create corresponding entities
	for (auto data : meshes_to_load) {

		mesh_name = "data/" + data.first;
		sRenderData& render_data = data.second;

		// No transforms, nothing to do here
		if (render_data.models.empty())
			continue;


		Material mat = render_data.material;


		EntityMesh* new_entity = nullptr;

		size_t tag = data.first.find("@asteroid");

		Mesh* mesh = Mesh::Get(mesh_name.c_str());
		
		new_entity = new EntityMesh(mesh, mat);
		
		//generate a random number between 0 and 1
		
		new_entity->name = data.first;

		// Create instanced entity
		if (render_data.models.size() > 1) {
			new_entity->isInstanced = true;

			//iterate over render models and add them to the entity if the random value is greater than 0.5
			for (int i = 0; i < render_data.models.size(); i++) {
				//if the random number is greater than 0.5, add the model
				float rand_value = random();
				if (rand_value > 0.3) {
					new_entity->addInstance(render_data.models[i]);
				}
				else {
					continue;
				}
			}
		}

		else {
			new_entity->model = render_data.models[0];
		}

		new_entity->isAsteroid = true;
		// Add entity to scene root
		root->addChild(new_entity);
	}

	std::cout << "Scene [OK]" << " Meshes added: " << mesh_count << std::endl;
	return true;
}

/*
sCollisionData World::rayCast() {
	sCollisionData data;

	for (auto e : root.children)
	{
		EntityCollider* ec = dynamic_cast<EntityCollider*> (e);
		if (ec == nullptr || !(ec->getLayer())) {
			continue;
		}
		Vector3 col_point;
		Vector3 col_normal;

		if (!ec->mesh->testRayCollision(ec->model, origin, direction, col_point, col_normal, max_ray_dist)) {
			continue;
		}

		data.collided = true;

		// There was a collision! Update if nearest. Float new distance (col peint erigin).length();

		float new_distance = (col_point - origin).length();
		if (new distance data distance) {
			data.col_point = col_point; 
			data.col_normal  = col_normal;
			data.distance = new_distance;
			data.colliderec = ec;
		}
	}
	
	return data;
}
*/
