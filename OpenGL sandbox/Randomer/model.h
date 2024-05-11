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
	vec3			pos;
	mat4			model_mat;

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

void model_free
	(
	Model*
	);