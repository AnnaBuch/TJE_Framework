#pragma once

#include "entity.h"
#include "graphics/material.h"

class Mesh;

//level of detail meshses
struct sMeshLOD {
	Mesh* mesh;
	float distance;

};


class EntityMesh : public Entity
{
public:
	EntityMesh() {};
	EntityMesh(Mesh* mesh, const Material& material, const std::string& name = "");
	//~EntityMesh();

	// Attributes of the derived class  
	Mesh* mesh = nullptr;

	Material material;

	//Instancing
	bool isInstanced = false;
	std::vector<Matrix44> models; //vector of all the model matrxs that are actually the same object: aka meshes repetides en posicions diferents 

	std::vector<sMeshLOD> mesh_lods;

	// Methods overwritten from base class
	void render();
	void update(float elapsed_time);

	void addInstance(Matrix44 model);
	void addLOD(sMeshLOD mesh_lod);

};
