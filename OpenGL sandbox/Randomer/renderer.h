#pragma once

#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>

#include "util.h"
#include "shader_utils.h"
#include "camera_utils.h"
#include "randomer_light.h"
#include "randomer_cube.h"
#include "cglm/cglm.h"

typedef struct 
	{
	window_size32_t		window_size;
	GLFWwindow*			pWindow;
	unsigned int		uiVBO;
	unsigned int		uiEBO;
	unsigned int		uiVAO;
	unsigned int		shader_programs[ SHADER_PROGRAM_COUNT ];
	mat4				proj_mat;
	unsigned int		texture;
	Camera				camera;
	Light_Source		light_source;
	Cube_Type			cube;
	} Renderer;

/* 
Renderer initialization method
*/
void render_init
	(
	uint32_t,
	uint32_t
	);


/* 
Renderer add camera
*/
void render_attach_camera
	(
	Camera_Type,
	vec3,
	vec3,
	vec3
	);


/*
Compiles every shader program.
*/
void render_compile_all_shaders
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
Clears the screen to the selected
clear color
*/
void render_clear_screen
	(
	void
	);


/* ---- Triangle drawing ---- */
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


/* ---- Rectangle drawing ---- */
/*
Initialize the renderer for rendering
a set of rectangles.
*/
void render_rectangles_tex_init
	(
	float*,
	unsigned int*,
	unsigned int,
	char*
	);

/* 
Render the rectangles.
*/
void render_rectangles_tex_draw
	(
	void
	);


/* ---- Cube drawing ---- */
/*
Initialize the renderer for rendering
a set of cubes.
*/
void render_cubes_tex_init
	(
	float*,
	unsigned int,
	char*,
	vec3
	);

/* 
Render the rectangles.
*/
void render_cubes_tex_draw
	(
	void
	);


/* ---- Lighting ---- */
/*
Initialize the renderer light source
*/
void render_add_light_source
	(
	vec3,
	vec4,
	float
	);


/*
Renders a light source
*/
void render_draw_light
	(
	void
	);


/* ---- Window functions ---- */
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