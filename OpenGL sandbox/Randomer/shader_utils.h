#pragma once

#include<stdbool.h>

#include "shader_source.h"
#include "cglm/cglm.h"

typedef struct
	{
	char* vert_shader;
	char* frag_shader;
	}vert_frag_type;

typedef enum
	{
	SHADER_PROGRAM_TRIANGLES,
	SHADER_PROGRAM_RECTANGLES,
	SHADER_PROGRAM_CUBES,
	SHADER_PROGRAM_CUBE_LIGHT,
	//SHADER_PROGRAM_PHONG,

	/* Must be last */
	SHADER_PROGRAM_COUNT
	} shader_program;


/*
Generates a shader program.
*/
void shdr_generate_program
	(
	unsigned int*	shdr_prog,
	char*			vert_shader_name,
	char*			frag_shader_name
	);


/*
Set a boolean uniform.
*/
void shdr_set_bool_uniform
	(
	unsigned int	shader,
	const char*		name,
	bool			value
	);


/*
Set a mat4 uniform.
*/
void shdr_set_mat4_uniform
	(
	unsigned int	shader,
	const char*		name,
	mat4			value
	);


/*
Set a vec4 uniform.
*/
void shdr_set_vec4_uniform
	(
	unsigned int	shader,
	const char*		name,
	vec4			value
	);

/*
Compiles a shader and updates 
the handle.
*/
static void shdr_compile_shader
	(
	unsigned int*	shader,
	GLenum			shader_type,
	char*			input_file_name
	);

/*
Stores the contents of input_file_name
into the output_buffer and saves the
size of the file.
*/
static void shdr_read_file_into
	(
	char*	input_file_name,
	char**	output_buffer
	);
