#pragma once

#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>

#include "util.h"

typedef enum
	{
	TRIANGLES
	}render_type;

typedef struct 
	{
	window_size32_t		window_size;
	GLFWwindow*			pWindow;
	unsigned int		uiVBO;
	unsigned int		shader_program;
	unsigned int		uiVAO;
	} Renderer;

/* 
Renderer initialization method
*/
void render_init
	(
	void	
	);

/* 
Defenestrate render
*/
void render_defenestrate
	(
	void
	);

/*
Returns True if the renderer is active
*/
bool render_is_active
	(
	void
	);

/*
Sends the graphics command to the GPU
and waits for user input
*/
void render_draw_and_poll_events
	(
	void
	);

/*
Render a set of triangles
*/
void render_triangles_init
	(
	float*,
	unsigned int
	);

/*
Render a set of triangles
*/
void render_triangles_draw
	(
	void
	);

/*
Compiles a shader program based on the
render type
*/
void render_compile_shaders
	(
	render_type
	);

/*
Renderer size callback function
*/
void render_framebuffer_size_callback
	(
	GLFWwindow*, 
	int,
	int
	);

/*
Renderer process input function
*/
void render_process_input
	(
	void
	);