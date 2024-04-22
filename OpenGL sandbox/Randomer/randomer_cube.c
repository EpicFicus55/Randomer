#include <string.h>

#include "util.h"
#include "randomer_cube.h"
#include "stb_image.h"

void cube_init
	(
	Cube_Type*	cube,
	char		attrib_bitmask,
	vec3		pos,
	char*		tex_path,
	int			vertex_count,
	float*		data
	)
{
int				_stride = 0;
int				_color_offset = 0;
int				_tex_offset = 0;
int				_tex_width = 0;
int				_tex_height = 0;
int				_tex_nr_channels = 0;
unsigned char*	_tex_data;

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

cube->vertex_count = vertex_count;

/* Create the VAO and VBO for the cube */
GL_CALL( glGenVertexArrays( 1, &cube->VAO_handle ) );
GL_CALL( glGenBuffers( 1, &cube->VBO_handle ) );

/* I'm going to make some assumptions 
	- 3 floats for the vertex positions
	- 4 floats for the color
	- 2 floats for the tex coordinates */
if( attrib_bitmask & VERTEX_POSITION_BIT )
	{
	_stride += 3;
	_color_offset += 3;
	_tex_offset += 3;
	}
if( attrib_bitmask & COLOR_BIT )
	{
	_stride += 4;
	_tex_offset += 4;
	}
if( attrib_bitmask & TEXTURE_COORDS_BIT )
	{
	/* Create the texture, if necessary */
	GL_CALL( glGenTextures( 1, &cube->tex_handle) );
	GL_CALL( glBindTexture( GL_TEXTURE_2D, cube->tex_handle ) );
	GL_CALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT) );	
	GL_CALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT) );
	GL_CALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR) );
	GL_CALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );

	_tex_data = stbi_load( tex_path, &_tex_width, &_tex_height, &_tex_nr_channels, 0 );
	GL_CALL( glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, _tex_width, _tex_height, 0, GL_RGB, GL_UNSIGNED_BYTE, _tex_data ) );
	GL_CALL( glBindTexture( GL_TEXTURE_2D, 0 ) );
	
	stbi_image_free( _tex_data );

	_stride += 2;
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
GL_CALL( glBindTexture( GL_TEXTURE_2D, cube->tex_handle ) );

GL_CALL( glEnable( GL_DEPTH_TEST ) );
GL_CALL( glDrawArrays( GL_TRIANGLES, 0, cube->vertex_count ) );
GL_CALL( glDisable( GL_DEPTH_TEST ) );

GL_CALL( glBindTexture( GL_TEXTURE_2D, 0) );
GL_CALL( glBindVertexArray( 0 ) );
}