#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <glad/glad.h>

#include "util.h"
#include "shader_utils.h"


/*
Generates a shader program.
*/
void shdr_generate_program
	(
	unsigned int*	shdr_prog,
	char*			vert_shader_name,
	char*			frag_shader_name
	)
{
unsigned int	_vert_shdr = 0;
unsigned int	_frag_shdr = 0;
int				_success = 0;
char			_info_log[ 512 ];

/* Clear _info_log */
memset( &_info_log[ 0 ], 0, sizeof(_info_log) );

/* Compile the vertex shader */
shdr_compile_shader( &_vert_shdr, GL_VERTEX_SHADER, vert_shader_name );

/* Compile the fragment shader */
shdr_compile_shader( &_frag_shdr, GL_FRAGMENT_SHADER, frag_shader_name );

/* Create a new shader program */
GL_CALL( *shdr_prog = glCreateProgram() );

/* Attach the shaders and compile the program */
GL_CALL( glAttachShader( *shdr_prog, _vert_shdr ) );
GL_CALL( glAttachShader( *shdr_prog, _frag_shdr ) );
GL_CALL( glLinkProgram( *shdr_prog ) );

/* Validate the compilation */
GL_CALL( glGetProgramiv( *shdr_prog, GL_LINK_STATUS, &_success ) );
if ( !_success )
	{
	glGetShaderInfoLog( *shdr_prog, sizeof(_info_log), NULL, _info_log );
	printf( "Linking of the shader program failed: %s\n", _info_log );
	}

/* Delete the shader programs */
GL_CALL( glDeleteShader( _vert_shdr ) );
GL_CALL( glDeleteShader( _frag_shdr ) );

}


/*
Compiles a shader and updates 
the handle.
*/
void shdr_compile_shader
	(
	unsigned int*	shader,
	GLenum			shader_type,
	char*			input_file_name
	)
{
char*	_shader_source = NULL;
int		_success = 0;
char	_info_log[ 512 ];

/* Generate a shader */
GL_CALL( *shader = glCreateShader( shader_type ) );

/* Save the shader source in the local buffer */
shdr_read_file_into( input_file_name, &_shader_source );

/* Compile the shader */
GL_CALL( glShaderSource( *shader, 1, &_shader_source, NULL ) );
GL_CALL( glCompileShader( *shader ) );

/* Validate compilation */
GL_CALL( glGetShaderiv( *shader, GL_COMPILE_STATUS, &_success ) );
if ( !_success )
	{
	glGetShaderInfoLog( *shader, sizeof(_info_log), NULL, _info_log );
	printf( "Compilation of the vertex shader: %s\n", _info_log );
	}

/* Free the buffer */
free( _shader_source );

}


/*
Stores the contents of input_file_name
into the output_buffer and saves the
size of the file.

NOTE: the output buffer needs to be freed
after it is no longer needed.
*/
void shdr_read_file_into
	(
	char*	input_file_name,
	char**	output_buffer
	)
{
/* Local variables */
FILE*	_input_stream = NULL;
errno_t	_err = 0;
long	_file_size = 0;

/* Begin the file stream. Print a message if file doesn't exist */
_err = fopen_s( &_input_stream, input_file_name, "r" );
if( _err )
	{
	printf( "Error reading GLSL file: %s\n", input_file_name );
	return;
	}

/* Find out how long the file is */
fseek( _input_stream, 0, SEEK_END );
_file_size = ftell( _input_stream );

/* Reset the stream */
rewind( _input_stream );

/* Allocate enough memory to keep all the contents of the file */
*output_buffer = ( char* )calloc( _file_size, sizeof(char) );
fread_s( *output_buffer, _file_size, 1, _file_size, _input_stream );

/* Close the file stream */
fclose( _input_stream );

}