#pragma once

#include "cglm/cglm.h"

typedef enum
	{
	TEXTURE_DIFFUSE_MAP,
	TEXTURE_SPECULAR_MAP
	} Texture_Type;

typedef struct
	{
	vec3	position;
	vec3	normals;
	vec2	tex_coords;
	} Vertex_3p3n2t;

typedef struct
	{
	unsigned int	handle;
	Texture_Type	type;
	} Texture;


typedef struct
	{
	Vertex_3p3n2t*	aVertices;
	unsigned int*	aIndices;
	Texture*		aTextures;

	unsigned int	vertex_count;
	unsigned int	index_count;
	unsigned int	texture_count;
	
	unsigned int	VAO;
	unsigned int	EBO;
	unsigned int	VBO;
	} Mesh;


void mesh_init
	( 
	Mesh* mesh, 
	Vertex_3p3n2t* vertices,	unsigned int vertex_count,
	unsigned int* indices,		unsigned int index_count,
	Texture* textures,			unsigned int texture_count
	);

void mesh_draw
	(
	Mesh* mesh,
	unsigned int shader_program
	);
