#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "renderer.h"


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float vertices[] = {
    // positions         // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
};    


int main( void )
{
 
render_init();
render_triangles_init( &vertices[ 0 ], 3 );

while( render_is_active() )
    {
    render_process_input();
    
    render_triangles_draw();

    render_draw_and_poll_events();
    }

render_defenestrate();
return 0;
}
