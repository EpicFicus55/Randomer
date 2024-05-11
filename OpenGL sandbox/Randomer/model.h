#pragma once

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"

typedef struct
	{
	/* Model data */
	Mesh*			aMeshes;
	unsigned int	mesh_count;

	/* Position and model matrix */
	mat4			model_mat;
	vec3			pos;

	/* Directory */
	char*			dir;
	} Model;


/*
 This calculates the model matrix
*/
void model_init_position
	(
	Model*	model,
	vec3	pos
	);

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


void model_process_mesh
	(
	Mesh*					randomer_mesh,
	struct aiMesh*			assimp_mesh,
	const struct aiScene*	scene
	);
