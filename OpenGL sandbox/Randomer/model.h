#pragma once

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"

typedef struct
	{
	Mesh*			aMeshes;
	unsigned int	mesh_count;
	char*			dir;
	} Model;


void model_load
	(
	Model*	model,
	char*	path
	);


void model_draw
	(
	Model*			model,
	unsigned int	shader
	);


void model_node_process
	(
	Model*					model,
	struct aiNode*			node,
	const struct aiScene*	scene
	);


Mesh model_process_mesh
	(
	struct aiMesh*			mesh,
	const struct aiScene*	scene
	);
