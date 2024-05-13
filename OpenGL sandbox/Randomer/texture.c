#include <stdio.h>
#include <string.h>
#include <glad/glad.h>

#include "mesh.h"
#include "texture.h"
#include "util.h"
#include "stb_image.h"

static Mesh_Texture_Type	loaded_textures[ 100 ];
static unsigned int			loaded_tex_cnt = 0;

void texture_load
	(
	unsigned int*	texture,
	char*			path
	)
{
unsigned int _id;
int _width, _height, _nr_channels;
unsigned char* _tex_data;
GLenum	_format;

/* Check if this texture was already loaded */
for( unsigned int i = 0; i < loaded_tex_cnt; i++ )
	{
	if( strcmp( path, loaded_textures[ i ].path ) == 0 )
		{
		*texture = loaded_textures[ i ].handle;
		return;
		}
	}

GL_CALL( glGenTextures( 1, &_id ) );

_tex_data = stbi_load( path, &_width, &_height, &_nr_channels, 0 );

if( !_tex_data )
	{
	printf( "Unable to read texture\n" );
	return;
	}

/* Choose the GL texture format based on the number of channels
extracted from the texture file */
switch( _nr_channels )
	{
	case 1:
		_format = GL_RED;
		break;
	case 3:
		_format = GL_RGB;
		break;
	case 4:
		_format = GL_RGBA;
		break;
	default:
		printf( "Invalid texture format\n" );
		stbi_image_free( _tex_data );
		return;
	}

/* Set up the GL texture */
GL_CALL( glBindTexture( GL_TEXTURE_2D, _id ) );
GL_CALL( glTexImage2D( GL_TEXTURE_2D, 0, _format, _width, _height, 0, _format, GL_UNSIGNED_BYTE, _tex_data ) );
GL_CALL( glGenerateMipmap( GL_TEXTURE_2D ) );

/* Set up the sampler */
GL_CALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT) );	
GL_CALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT) );
GL_CALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR) );
GL_CALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );

/* Set the texture handle after all operations were done */
*texture = _id;
loaded_textures[ loaded_tex_cnt ].handle = _id;
loaded_textures[ loaded_tex_cnt ].path = path;
loaded_tex_cnt++;

}