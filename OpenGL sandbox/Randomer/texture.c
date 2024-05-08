#include <stdio.h>
#include <glad/glad.h>

#include "texture.h"
#include "util.h"
#include "stb_image.h"

void texture_load
	(
	Texture*	texture,
	char*		path
	)
{
unsigned int _id;
int _width, _height, _nr_channels;
unsigned char* _tex_data;
GLenum	_format;

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
GL_CALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR) );
GL_CALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );

/* Set the texture handle after all operations were done */
texture->handle = _id;

}