#pragma once

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
Compiles a shader and updates 
the handle.
*/
void shdr_compile_shader
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
void shdr_read_file_into
	(
	char*	input_file_name,
	char**	output_buffer
	);
