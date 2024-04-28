#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "renderer.h"
#include "randomer_cube.h"
#include "camera_utils.h"
#include "data.h"


const unsigned int SCR_WIDTH = 750;
const unsigned int SCR_HEIGHT = 750;

vec3 camera_position  = { 0.5f, 0.5f,  2.1f };
vec3 camera_target    = { 0.0f, 0.0f, -1.0f };
vec3 camera_up        = { 0.0f, 1.0f,  0.0f };

vec3 light_pos        = { 3.0f, 3.0f, -3.0f };
vec4 light_color      = { 1.0f, 1.0f, 1.0f, 1.0f };
float light_ambient_strength = 0.1f;

vec3    cube_pos = { 0.0f, 0.0f, 0.0f };

int main( void )
{
 
render_init( SCR_WIDTH, SCR_HEIGHT );

render_attach_camera( CAMERA_TYPE_XYZ_KEYBOARD, camera_position, camera_target, camera_up );

render_cubes_tex_init
    (
    &cube_vertices_3p2t3n[ 0 ], 
    36, 
    "..\\..\\Assets\\Textures\\bricks.png",
    cube_pos
    );

render_add_light_source( light_pos, light_color, light_ambient_strength );

while( render_is_active() )
    {
    render_process_input();
    
    render_clear_screen();
    render_draw_light();

    render_cubes_tex_light_draw();

    render_draw_and_poll_events();
    }

render_defenestrate();
return 0;
}
