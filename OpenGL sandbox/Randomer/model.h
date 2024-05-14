#pragma once

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"

/* 
 * Definition for the limit of models that can be loaded 
 */
#define MAX_MODEL_COUNT	5


typedef struct
	{
	/* Active status */
	char			is_active;

	/* Model data */
	Mesh*			aMeshes;
	unsigned int	mesh_count;

	/* Position and model matrix */
	vec3			pos;
	mat4			model_mat;

	/* Directory */
	char*			name;
	char*			dir;
	char*			diff_dir;
	char*			spec_dir;
	} Model;


/*
 * Function for initializing the 
 * model matrix of a model.
 */
void model_init_position
	(
	Model*	model,
	vec3	pos
	);


/*
 * Function that loads a model based on the parameters
 * already set. 
 */
void model_load
	(
	Model*	model
	);


/*
 * Function that draws every mesh of a model.
 */
void model_draw
	(
	Model*			model,
	unsigned int	shader
	);


/* 
 * Function that frees the resources of a model.
 */
void model_free
	(
	Model*
	);