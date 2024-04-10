#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "renderer.h"
#include "camera_utils.h"
#include "data.h"


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

vec3 camera_position  = { 0.0f, 0.0f, 3.0f };
vec3 camera_target    = { 0.0f, 0.0f, 0.0f };

int main( void )
{
 
render_init( 500, 500 );

render_attach_camera( CAMERA_TYPE_STATIONARY_NONE, camera_position, camera_target );

render_cubes_tex_init
    ( 
    &cube_vertices_3p2t[ 0 ], 
    36, 
    "D:\\Stuff\\Randomer\\Assets\\Textures\\container.jpg" 
    );

while( render_is_active() )
    {
    render_process_input();
    
    render_cubes_tex_draw();

    render_draw_and_poll_events();
    }

render_defenestrate();
return 0;
}
