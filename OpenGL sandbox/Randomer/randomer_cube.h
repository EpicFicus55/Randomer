#pragma once

#include "cglm/cglm.h"

typedef struct
	{
	unsigned int	VAO_handle;
	unsigned int	VBO_handle;
	unsigned int	tex_handle;
	int				vertex_count;
	mat4			model_mat;
	vec3			pos;
	char			attrib_bitmask;
	char*			tex_path;
	} Cube_Type;


/* 
Sets up a cube based on the attributes provided
*/
void cube_init
	(
	Cube_Type*	cube,
	char		attrib_bitmask,
	vec3		pos,
	char*		tex_path,
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