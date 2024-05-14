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
	unsigned int		shader_programs[ SHADER_PROGRAM_COUNT ];
	mat4				proj_mat;
	unsigned int		texture; /* Needs to be removed */
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
	char*,
	vec3
	);

/* 
Render the rectangles with lighting.
*/
void render_cubes_tex_light_draw
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



/* ---- Models ---- */
/*
 * Initialize the renderer models
 * This requires the following
 * - path to the model file
 * - name of the model file
 * - path to the diffuse maps directory
 * - path to the specular maps directory
 * 
 * The function will get the names of the maps
 * automatically.
 */
void render_add_model
	(
	char*	model_path,
	char*	diff_dir,	
	char*	spec_dir,	
	char*	model_name,	
	vec3	pos
	);

void render_draw_model
	(
	void
	);

void render_free_model
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
