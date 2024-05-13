#pragma once

#include "texture.h"
#include "cglm/cglm.h"

typedef struct
	{
	unsigned int	VAO_handle;
	unsigned int	VBO_handle;
	Texture_Type	diffuse_tex;
	Texture_Type	specular_tex;
	int				vertex_count;
	mat4			model_mat;
	vec3			pos;
	char			attrib_bitmask;
	char*			tex_path;
	Material_Type	material;
	} Cube_Type;


static float material_ambient[ 3 ] = { 0.3f, 0.3f, 0.3f };
static float material_diffuse[ 3 ] = { 1.0f, 1.0f, 1.0f };
static float material_specular[ 3 ] = { 1.0f, 1.0f, 1.0f };


/* 
Sets up a cube based on the attributes provided
*/
void cube_init
	(
	Cube_Type*	cube,
	char		attrib_bitmask,
	vec3		pos,
	char*		diffuse_tex,
	char*		specular_tex,
	int			vertex_count,
	float*		data
	);


/*
Render a cube
*/
void cube_render
	(
	Cube_Type*	cube
	);