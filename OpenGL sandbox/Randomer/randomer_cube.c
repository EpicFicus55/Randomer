#include <string.h>

#include "util.h"
#include "randomer_cube.h"
#include "texture.h"
#include "stb_image.h"

void cube_init
	(
	Cube_Type*	cube,
	char		attrib_bitmask,
	vec3		pos,
	char*		diffuse_tex,
	char*		specular_tex,
	int			vertex_count,
	float*		data
	)
{
int				_stride = 0;
int				_color_offset = 0;
int				_tex_offset = 0;
int				_normal_vec_offset = 0;

/* Verify the validity of the vertex attributes */
if( attrib_bitmask == 0 )
	{
	printf( "Bad cube data!\n" );
	return;
	}

/* Initialize the position and the model matrix*/
memcpy( cube->pos, pos, sizeof(cube->pos) );

glm_mat4_identity( cube->model_mat );
glm_translate( cube->model_mat, cube->pos );
glm_rotate_y( cube->model_mat, 0.5f, cube->model_mat );

/* Set the material lighting parameters */
memcpy( cube->material.ambient, material_ambient, sizeof(vec3) );
memcpy( cube->material.diffuse, material_diffuse, sizeof(vec3) );
memcpy( cube->material.specular, material_specular, sizeof(vec3) );
cube->material.shininess = 0.4f;

cube->vertex_count = vertex_count;

/* Create the VAO and VBO for the cube */
GL_CALL( glGenVertexArrays( 1, &cube->VAO_handle ) );
GL_CALL( glGenBuffers( 1, &cube->VBO_handle ) );

/* I'm going to make some assumptions 
	- 3 floats for the vertex positions
	- 4 floats for the color
	- 2 floats for the tex coordinates 
	- 3 floats for the normal vectors */
if( attrib_bitmask & VERTEX_POSITION_BIT )
	{
	_stride += 3;
	_color_offset += 3;
	_tex_offset += 3;
	_normal_vec_offset += 3;
	}
if( attrib_bitmask & COLOR_BIT )
	{
	_stride += 4;
	_tex_offset += 4;
	_normal_vec_offset += 4;
	}
if( attrib_bitmask & TEXTURE_COORDS_BIT )
	{
	/* Create the texture, if necessary */
	GL_CALL( glActiveTexture( GL_TEXTURE0 ) );
	texture_load( &cube->diffuse_tex.handle, diffuse_tex );

	GL_CALL( glActiveTexture( GL_TEXTURE1 ) );
	texture_load( &cube->specular_tex.handle, specular_tex );

	_stride += 2;
	_normal_vec_offset += 2;
	}

if( attrib_bitmask & NORMAL_VEC_BIT )
	{
	_stride += 3;
	}

GL_CALL( glBindVertexArray( cube->VAO_handle ) );
GL_CALL( glBindBuffer( GL_ARRAY_BUFFER, cube->VBO_handle ) );

GL_CALL( glBufferData( GL_ARRAY_BUFFER, sizeof( data[0] ) * vertex_count * _stride, &data[ 0 ], GL_STATIC_DRAW ) );

if( attrib_bitmask & VERTEX_POSITION_BIT )
	{
	/* The cube vertices have a position (duh) */
	GL_CALL( glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof(data[0]) * _stride, NULL ) );
	GL_CALL( glEnableVertexAttribArray( 0 ) );
	}

if( attrib_bitmask & COLOR_BIT )
	{
	GL_CALL( glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, sizeof( data[0] ) * _stride, (void*)(sizeof(float) * _color_offset) ) );
	GL_CALL( glEnableVertexAttribArray( 1 ) );
	}

if( attrib_bitmask & TEXTURE_COORDS_BIT )
	{
	GL_CALL( glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, sizeof( data[0] ) * _stride, (void*)(sizeof(float) * _tex_offset) ) );
	GL_CALL( glEnableVertexAttribArray( 2 ) );
	}

if( attrib_bitmask & NORMAL_VEC_BIT )
	{
	GL_CALL( glVertexAttribPointer( 3, 3, GL_FLOAT, GL_FALSE, sizeof( data[0] ) * _stride, (void*)(sizeof(float) * _normal_vec_offset) ) );
	GL_CALL( glEnableVertexAttribArray( 3 ) );
	}

/* Final cleanup */
GL_CALL( glBindBuffer( GL_ARRAY_BUFFER, 0 ) );
GL_CALL( glBindTexture( GL_TEXTURE_2D, 0 ) );
GL_CALL( glBindVertexArray( 0 ) );

}


void cube_render
	(
	Cube_Type*	cube
	)
{
GL_CALL( glBindVertexArray( cube->VAO_handle ) );
GL_CALL( glActiveTexture( GL_TEXTURE0 ) );
GL_CALL( glBindTexture( GL_TEXTURE_2D, cube->diffuse_tex.handle ) );

GL_CALL( glActiveTexture( GL_TEXTURE1 ) );
GL_CALL( glBindTexture( GL_TEXTURE_2D, cube->specular_tex.handle) );

GL_CALL( glEnable( GL_DEPTH_TEST ) );
GL_CALL( glDrawArrays( GL_TRIANGLES, 0, cube->vertex_count ) );
GL_CALL( glDisable( GL_DEPTH_TEST ) );

GL_CALL( glBindTexture( GL_TEXTURE_2D, 0) );
GL_CALL( glBindVertexArray( 0 ) );
}