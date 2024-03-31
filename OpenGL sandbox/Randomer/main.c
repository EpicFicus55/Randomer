#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "renderer.h"


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};

unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };


int main( void )
{
 
render_init();
render_rectangles_tex_init
    ( 
    &vertices[ 0 ], 
    &indices[ 0 ], 
    4, 
    "D:\\Stuff\\Randomer\\Assets\\Textures\\container.jpg" 
    );

while( render_is_active() )
    {
    render_process_input();
    
    render_rectangles_tex_draw();

    render_draw_and_poll_events();
    }

render_defenestrate();
return 0;
}
