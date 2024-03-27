#include "renderer.h"
#include "shader_source.h"
#include "shader_utils.h"

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
render_compile_shaders( TRIANGLES );

GL_CALL( glGenVertexArrays( 1, &renderer.uiVAO ) );
GL_CALL( glGenBuffers( 1, &renderer.uiVBO ) );

GL_CALL( glBindVertexArray( renderer.uiVAO ) );

GL_CALL( glBindBuffer( GL_ARRAY_BUFFER, renderer.uiVBO ) );
GL_CALL( glBufferData( GL_ARRAY_BUFFER, sizeof( data[0] ) * count * 3 , data, GL_STATIC_DRAW ) );

GL_CALL( glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 ) );
GL_CALL( glEnableVertexAttribArray( 0 ) );

GL_CALL( glBindBuffer( GL_ARRAY_BUFFER, 0 ) );
GL_CALL( glBindVertexArray( 0 ) );

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

GL_CALL( glUseProgram( renderer.shader_program ) );
GL_CALL( glBindVertexArray( renderer.uiVAO ) );
GL_CALL( glDrawArrays( GL_TRIANGLES, 0, 3 ) );

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
Compiles a shader program based on the
render type
*/
void render_compile_shaders
	(
	render_type draw_type
	)
{
	   
switch( draw_type )
	{
	case TRIANGLES:
		shdr_generate_program
			( 
			&renderer.shader_program, 
			TRIANGLE_VERTEX_SHADER_FILE, 
			TRIANGLE_FRAGMENT_SHADER_FILE 
			);
		break;
	default:
		printf( "Unsupported render type!\n" );
		break;
	}

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