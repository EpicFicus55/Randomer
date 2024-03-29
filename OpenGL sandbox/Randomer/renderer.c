#include <stdbool.h>

#include "renderer.h"

extern vert_frag_type vertex_fragment_shaders[];

static Renderer renderer;

void render_init
	(
	void
	)
{
/* Initialize the GLFW Window */
glfwInit();
glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
renderer.pWindow = glfwCreateWindow( 500, 500, "Randomer window", NULL, NULL );

glfwMakeContextCurrent( renderer.pWindow );
glfwSetFramebufferSizeCallback( renderer.pWindow, render_framebuffer_size_callback);

if ( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) )
	{
    printf( "Failed to initialize GLAD" );
    return;
	} 

/* Compile every shader program */
render_compile_all_shaders();

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

}
