#pragma once

#include "cglm/cglm.h"

/*
 * Type used to determine what kind
 * of material map a texture represents.
 */
typedef enum
	{
	TEXTURE_DIFFUSE_MAP,
	TEXTURE_SPECULAR_MAP
	} Texture_Map_Type;

/*
 * Vertex types
 * - more will come
 */
typedef struct
	{
	vec3	position;
	vec3	normals;
	vec2	tex_coords;
	} Vertex_3p3n2t_Type;

typedef struct
	{
	unsigned int		handle;
	Texture_Map_Type	type;
	char*				path;
	} Mesh_Texture_Type;


typedef struct
	{
	Vertex_3p3n2t_Type*	aVertices;
	unsigned int*		aIndices;
	Mesh_Texture_Type*	aTextures;

	unsigned int	vertex_count;
	unsigned int	index_count;
	unsigned int	texture_count;
	
	unsigned int	VAO;
	unsigned int	EBO;
	unsigned int	VBO;
	} Mesh;


void mesh_init
	( 
	Mesh* mesh
	);

void mesh_draw
	(
	Mesh* mesh,
	unsigned int shader_program
	);
