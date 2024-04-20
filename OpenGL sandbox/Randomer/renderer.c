#include <stdbool.h>

#include "renderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "cglm/cglm.h"

extern vert_frag_type vertex_fragment_shaders[];

static Renderer renderer;

void render_init
	(
	uint32_t	width,
	uint32_t	height
	)
{
float _angle = 45.0f;

/* Initialize the GLFW Window */
glfwInit();
glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
renderer.pWindow = glfwCreateWindow( width, height, "Randomer window", NULL, NULL );
renderer.window_size.width = width;
renderer.window_size.height = height;

glfwMakeContextCurrent( renderer.pWindow );
glfwSetFramebufferSizeCallback( renderer.pWindow, render_framebuffer_size_callback);

if ( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) )
	{
    printf( "Failed to initialize GLAD" );
    return;
	} 

/* Compile every shader program */
render_compile_all_shaders();

/* It makes sense to initialize the projection matrix here, right? */
glm_mat4_identity( renderer.proj_mat );
glm_perspective
	( 
	_angle,	
	(float)( renderer.window_size.width / renderer.window_size.height ),
	0.1f,
	100.0f,
	renderer.proj_mat
	);

}


/* 
Renderer add camera
*/
void render_attach_camera
	(
	Camera_Type	camera_type,
	vec3		camera_position,
	vec3		camera_target,
	vec3		camera_up
	)
{
camera_init
	(
	&renderer.camera,
	camera_type,
	camera_position,
	camera_target,
	camera_up
	);
renderer.camera.camera_speed = 0.01f;

}


/*
Compiles every shader program.
*/
void render_compile_all_shaders
	(
	void
	)
{
for( int i = 0; i < SHADER_PROGRAM_COUNT; i++ )
	{
	shdr_generate_program
		(
		&renderer.shader_programs[ i ],
		vertex_fragment_shaders[ i ].vert_shader,
		vertex_fragment_shaders[ i ].frag_shader
		);
	}

}


/* 
Defenestrate render
*/
void render_defenestrate
	(
	void	
	)
{
glfwTerminate();

}


/*
Returns True if the renderer is active
*/
bool render_is_active
	(
	void
	)
{
return !glfwWindowShouldClose( renderer.pWindow );

}


/*
Render a set of triangles
*/
void render_triangles_init
	(
	float*			data,
	unsigned int	count
	)
{
GL_CALL( glGenVertexArrays( 1, &renderer.uiVAO ) );
GL_CALL( glGenBuffers( 1, &renderer.uiVBO ) );

GL_CALL( glBindVertexArray( renderer.uiVAO ) );

GL_CALL( glBindBuffer( GL_ARRAY_BUFFER, renderer.uiVBO ) );
GL_CALL( glBufferData( GL_ARRAY_BUFFER, sizeof( data[0] ) * count * 6, data, GL_STATIC_DRAW ) );

GL_CALL( glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0 ) );
GL_CALL( glEnableVertexAttribArray( 0 ) );

GL_CALL( glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(float) * 3) ) );
GL_CALL( glEnableVertexAttribArray( 1 ) );

GL_CALL( glBindBuffer( GL_ARRAY_BUFFER, 0 ) );
GL_CALL( glBindVertexArray( 0 ) );

/* Set the uniforms */
shdr_set_bool_uniform( renderer.shader_programs[ SHADER_PROGRAM_TRIANGLES ], "u_use_color", true );

}


/*
Render a set of triangles
*/
void render_triangles_draw
	(
	void
	)
{
GL_CALL( glClearColor( 0.2f, 0.3f, 0.3f, 1.0f ) );
GL_CALL( glClear( GL_COLOR_BUFFER_BIT ) );

GL_CALL( glUseProgram( renderer.shader_programs[ SHADER_PROGRAM_TRIANGLES ] ) );
GL_CALL( glBindVertexArray( renderer.uiVAO ) );

GL_CALL( glDrawArrays( GL_TRIANGLES, 0, 3 ) );

GL_CALL( glUseProgram( 0 ) );
GL_CALL( glBindVertexArray( 0 ) );

}


/*
Initialize the renderer for rendering
a set of rectangles.
*/
void render_rectangles_tex_init
	(
	float*			vertex_data,
	unsigned int*	index_data,
	unsigned int	count,
	char*			tex_name
	)
{
int _width, _height, _nr_channels;
unsigned char* _tex_data = stbi_load( tex_name, &_width, &_height, &_nr_channels, 0 );

if( !_tex_data )
	{
	printf( "Invalid texture file: %s\n", tex_name );
	}

GL_CALL( glGenTextures( 1, &renderer.texture ) );
GL_CALL( glBindTexture( GL_TEXTURE_2D, renderer.texture ) );

GL_CALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT) );	
GL_CALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT) );
GL_CALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR) );
GL_CALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );

GL_CALL( glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, _tex_data ) );
GL_CALL( glGenerateMipmap( GL_TEXTURE_2D ) );

/* Load the vertex data */
GL_CALL( glGenVertexArrays( 1, &renderer.uiVAO ) );
GL_CALL( glGenBuffers( 1, &renderer.uiVBO ) );
GL_CALL( glGenBuffers( 1, &renderer.uiEBO ) );

GL_CALL( glBindVertexArray( renderer.uiVAO ) );

GL_CALL( glBindBuffer( GL_ARRAY_BUFFER, renderer.uiVBO ) );
GL_CALL( glBufferData( GL_ARRAY_BUFFER, sizeof( vertex_data[ 0 ] ) * count * 8, vertex_data, GL_STATIC_DRAW ) );

GL_CALL( glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, renderer.uiEBO ) );
GL_CALL( glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( index_data[ 0 ] ) * 6, index_data, GL_STATIC_DRAW ) );

GL_CALL( glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0 ) );
GL_CALL( glEnableVertexAttribArray( 0 ) );

GL_CALL( glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 3) ) );
GL_CALL( glEnableVertexAttribArray( 1 ) );

GL_CALL( glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 6) ) );
GL_CALL( glEnableVertexAttribArray( 2 ) );

GL_CALL( glBindBuffer( GL_ARRAY_BUFFER, 0 ) );
GL_CALL( glBindVertexArray( 0 ) );

stbi_image_free( _tex_data );

}


/* 
Render the rectangles.
*/
void render_rectangles_tex_draw
	(
	void
	)
{
GL_CALL( glClearColor( 0.2f, 0.3f, 0.3f, 1.0f ) );
GL_CALL( glClear( GL_COLOR_BUFFER_BIT ) );

GL_CALL( glUseProgram( renderer.shader_programs[ SHADER_PROGRAM_RECTANGLES ] ) );
GL_CALL( glBindVertexArray( renderer.uiVAO ) );
GL_CALL( glBindTexture( GL_TEXTURE_2D, renderer.texture ) );

GL_CALL( glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 ) );

GL_CALL( glUseProgram( 0 ) );
GL_CALL( glBindVertexArray( 0 ) );

}


/*
Initialize the renderer for rendering
a set of cubes.
*/
void render_cubes_tex_init
	(
	float*			vertex_data,
	unsigned int	count,
	char*			tex_name
	)
{
int				_width, _height, _nr_channels;
unsigned char*	_tex_data;
float			_angle = 45.0f;

GL_CALL( glGenVertexArrays( 1, &renderer.uiVAO ) );
GL_CALL( glGenBuffers( 1, &renderer.uiVBO ) );

/* Create the texture */
GL_CALL( glGenTextures( 1, &renderer.texture ) );
GL_CALL( glBindTexture( GL_TEXTURE_2D, renderer.texture ) );
GL_CALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT) );	
GL_CALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT) );
GL_CALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR) );
GL_CALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );

_tex_data = stbi_load( tex_name, &_width, &_height, &_nr_channels, 0 );
GL_CALL( glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, _tex_data ) );
GL_CALL( glBindTexture( GL_TEXTURE_2D, 0 ) );

/* Load the vertex data */
GL_CALL( glBindVertexArray( renderer.uiVAO ) );
GL_CALL( glBindBuffer( GL_ARRAY_BUFFER, renderer.uiVBO ) );

GL_CALL( glBufferData( GL_ARRAY_BUFFER, sizeof(vertex_data[0]) * count * 5, &vertex_data[ 0 ], GL_STATIC_DRAW ) );

GL_CALL( glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_data[0]) * 5, NULL ) );
GL_CALL( glEnableVertexAttribArray( 0 ) );

GL_CALL( glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_data[0]) * 5, (void*)(sizeof(float) * 3 ) ) );
GL_CALL( glEnableVertexAttribArray( 1 ) );

/* Initialize the matrix */
GL_CALL( glBindBuffer( GL_ARRAY_BUFFER, 0 ) );
GL_CALL( glBindVertexArray( 0 ) );

stbi_image_free( _tex_data );

/* Set the uniforms */
glm_mat4_identity( renderer.model_mat );
glm_make_rad( &_angle );

_angle = -55.0f;
glm_make_rad( &_angle );
glm_rotate_x(renderer.model_mat, _angle, renderer.model_mat);

}


/* 
Render the rectangles.
*/
void render_cubes_tex_draw
	(
	void
	)
{

GL_CALL( glClearColor( 0.2f, 0.3f, 0.3f, 1.0f ) );
GL_CALL( glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ) );

shdr_set_mat4_uniform( renderer.shader_programs[ SHADER_PROGRAM_CUBES ], "uProjMat", renderer.proj_mat );
shdr_set_mat4_uniform( renderer.shader_programs[ SHADER_PROGRAM_CUBES ], "uViewMat", renderer.camera.view );
shdr_set_mat4_uniform( renderer.shader_programs[ SHADER_PROGRAM_CUBES ], "uModelMat", renderer.model_mat );

GL_CALL( glBindVertexArray( renderer.uiVAO ) );
GL_CALL( glBindTexture( GL_TEXTURE_2D, renderer.texture ) );
GL_CALL( glUseProgram( renderer.shader_programs[ SHADER_PROGRAM_CUBES ] ) );

GL_CALL( glEnable( GL_DEPTH_TEST ) );

GL_CALL( glDrawArrays( GL_TRIANGLES, 0, 36 ) );

GL_CALL( glDisable( GL_DEPTH_TEST ) );

GL_CALL( glUseProgram( 0 ) );
GL_CALL( glBindVertexArray( 0 ) );

}


/*
Sends the graphics command to the GPU
and waits for user input
*/
void render_draw_and_poll_events
	(
	void
	)
{
glfwSwapBuffers( renderer.pWindow );
glfwPollEvents();

}


/* ---- Lighting ---- */
/*
Initialize the renderer light source
*/
void render_add_light_source
	(
	vec3	position,
	vec4	color
	)
{
render_init_light( &renderer.light_source, position, color );

}


/*
Renders a light source
*/
void render_draw_light
	(
	void
	)
{
GL_CALL( glClearColor( 0.2f, 0.3f, 0.3f, 1.0f ) );
GL_CALL( glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ) );

GL_CALL( glBindVertexArray( renderer.light_source.VAO_handle ) );

GL_CALL( glUseProgram( renderer.shader_programs[ SHADER_PROGRAM_CUBE_LIGHT ] ) );
shdr_set_mat4_uniform( renderer.shader_programs[ SHADER_PROGRAM_CUBE_LIGHT ], "uProjMat", renderer.proj_mat );
shdr_set_mat4_uniform( renderer.shader_programs[ SHADER_PROGRAM_CUBE_LIGHT ], "uViewMat", renderer.camera.view );
shdr_set_mat4_uniform( renderer.shader_programs[ SHADER_PROGRAM_CUBE_LIGHT ], "uModelMat", renderer.light_source.model_matrix );

GL_CALL( glEnable( GL_DEPTH_TEST ) );

GL_CALL( glDrawArrays( GL_TRIANGLES, 0, 36 ) );

GL_CALL( glDisable( GL_DEPTH_TEST ) );

GL_CALL( glUseProgram( 0 ) );
GL_CALL( glBindVertexArray( 0 ) );

}


/*
Renderer size callback method
*/
void render_framebuffer_size_callback
	(
	GLFWwindow* pWindow, 
	int width,
	int height
	)
{
/* Update the viewport */
glViewport( 0, 0, width, height );
renderer.window_size.width = width;
renderer.window_size.height = height;

}


/*
Renderer process input function
*/
void render_process_input
	(
	void
	)
{
if( glfwGetKey( renderer.pWindow, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
	{
	glfwSetWindowShouldClose( renderer.pWindow, 1 );
	}
if( glfwGetKey( renderer.pWindow, GLFW_KEY_A ) == GLFW_PRESS )
	{
	if( renderer.camera.pfn_A_key_callback )
		{
		renderer.camera.pfn_A_key_callback( &renderer.camera );
		}
	}
if( glfwGetKey( renderer.pWindow, GLFW_KEY_D ) == GLFW_PRESS )
	{
	if( renderer.camera.pfn_D_key_callback )
		{
		renderer.camera.pfn_D_key_callback( &renderer.camera );
		}
	}

update_camera( &renderer.camera );

}
