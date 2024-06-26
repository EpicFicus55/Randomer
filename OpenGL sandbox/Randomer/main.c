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

vec3 light_pos        = { 3.0f, 3.0f, 3.0f };
vec4 light_color      = { 1.0f, 1.0f, 1.0f, 1.0f };
float light_ambient_strength = 0.3f;

vec3    cube_pos = { 0.0f, 0.0f, 0.0f };
vec3    backpack_pos = { 0.0f, 0.0f, 0.0f };

int main( void )
{
/* Model handle */
unsigned int _model_backpack;

render_init( SCR_WIDTH, SCR_HEIGHT );
render_attach_camera( CAMERA_TYPE_XYZ_KEYBOARD, camera_position, camera_target, camera_up );

_model_backpack = render_add_model
    ( 
    "..\\..\\Assets\\Models\\backpack", /* path to the model file */
    "..\\..\\Assets\\Models\\backpack", /* path to the diffuse maps */
    "..\\..\\Assets\\Models\\backpack", /* path to the specular maps */
    "backpack.obj",                     /* model name               */
    backpack_pos 
    );


render_add_light_source( light_pos, light_color, light_ambient_strength );

while( render_is_active() )
    {
    render_process_input();
    
    render_clear_screen();
    render_draw_light();

    render_draw_model( _model_backpack );

    render_draw_and_poll_events();
    }

render_defenestrate();
return 0;
}
