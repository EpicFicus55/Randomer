#include <string.h>

#include "camera_utils.h"

static void camera_A_key_press_callback( Camera* );
static void camera_D_key_press_callback( Camera* );
static void camera_W_key_press_callback( Camera* );
static void camera_S_key_press_callback( Camera* );
static void camera_Space_key_press_callback( Camera* );
static void camera_Shift_key_press_callback( Camera* );


/*
Initializes a camera based on user input
*/
void camera_init
	(
	Camera*			camera,
	Camera_Type		camera_type,
	vec3			camera_position,
	vec3			camera_front,
	vec3			camera_up
	)
{
/* Clear the camera */
memset( camera, 0, sizeof( Camera ) );

/* Assume the initial system is the default */
camera->system_x[ 0 ] = 1.0f;
camera->system_y[ 1 ] = 1.0f;
camera->system_y[ 2 ] = 1.0f;

/* Set the camera position and target */
memcpy( &camera->camera_pos[ 0 ], &camera_position[ 0 ], sizeof(vec3) );
memcpy( &camera->camera_front[ 0 ], &camera_front[ 0 ], sizeof(vec3) );
memcpy( &camera->camera_up[ 0 ], &camera_up[ 0 ], sizeof(vec3) );

camera->camera_type = camera_type;

update_camera( camera );

/* Set the camera up based on its type */
switch( camera_type )
	{
	case CAMERA_TYPE_STATIONARY_NONE:
		/* This is just a stationary view pointing to a target. */
		/* No callbacks necessary. */
		break;
	case CAMERA_TYPE_XYZ_KEYBOARD:
		/* Can move along the X and Z directions using WASD. */
		camera->pfn_A_key_callback = &( camera_A_key_press_callback );
		camera->pfn_D_key_callback = &( camera_D_key_press_callback );
		camera->pfn_W_key_callback = &( camera_W_key_press_callback );
		camera->pfn_S_key_callback = &( camera_S_key_press_callback );
		camera->pfn_Space_key_callback = &( camera_Space_key_press_callback );
		camera->pfn_Shift_key_callback = &( camera_Shift_key_press_callback );
		break;
	case CAMERA_TYPE_XYZ_KEYBOARD_MOUSE:
		break;
	default:
		printf( "Invalid camera type\n" );
		break;
	};

}


/*
Updates a camera's matrices
*/
void update_camera
	(
	Camera*	camera
	)
{
vec3 _aux;

/* Compute the camera parameters */
glm_mat4_identity( camera->view );
glm_vec3_add( camera->camera_pos, camera->camera_front, _aux );

glm_lookat
	(
	camera->camera_pos,
	_aux,
	camera->camera_up,
	camera->camera_lookat
	);

/* The renderer will mostly use the view matrix to apply transformations */
memcpy( camera->view, camera->camera_lookat, sizeof(mat4) );

}


static void camera_A_key_press_callback
	(
	Camera* camera
	)
{
vec3 _aux;

memset( _aux, 0, sizeof(_aux) );

glm_vec3_cross( camera->camera_front, camera->camera_up, _aux );
glm_vec3_scale( _aux, camera->camera_speed, _aux );
//glm_normalize( _aux ); // is this needed ????
glm_vec3_sub( camera->camera_pos, _aux, camera->camera_pos );

}


static void camera_D_key_press_callback
	(
	Camera* camera
	)
{
vec3 _aux;

memset( _aux, 0, sizeof(_aux) );

glm_vec3_cross( camera->camera_front, camera->camera_up, _aux );
glm_vec3_scale( _aux, camera->camera_speed, _aux );
//glm_normalize( _aux ); // is this needed ????
glm_vec3_add( camera->camera_pos, _aux, camera->camera_pos );

}


static void camera_W_key_press_callback
	(
	Camera* camera
	)
{
vec3 _aux;

memset( _aux, 0, sizeof(_aux) );

glm_vec3_scale( camera->camera_front, camera->camera_speed, _aux );
//glm_normalize( _aux ); // is this needed ????
glm_vec3_add( camera->camera_pos, _aux, camera->camera_pos );

}


static void camera_S_key_press_callback
	(
	Camera* camera
	)
{
vec3 _aux;

memset( _aux, 0, sizeof(_aux) );

glm_vec3_scale( camera->camera_front, -camera->camera_speed, _aux );
//glm_normalize( _aux ); // is this needed ????
glm_vec3_add( camera->camera_pos, _aux, camera->camera_pos );

}


static void camera_Space_key_press_callback
	(
	Camera* camera
	)
{
vec3 _aux;

memset( _aux, 0, sizeof(_aux) );

//glm_normalize( _aux ); // is this needed ????
camera->camera_pos[ 1 ] += camera->camera_speed;
//glm_vec3_scale( camera->camera_pos, camera->camera_speed, camera->camera_pos );

}

static void camera_Shift_key_press_callback
	(
	Camera* camera
	)
{
vec3 _aux;

memset( _aux, 0, sizeof(_aux) );

//glm_normalize( _aux ); // is this needed ????
camera->camera_pos[ 1 ] -= camera->camera_speed;
//glm_vec3_scale( camera->camera_pos, camera->camera_speed, camera->camera_pos );

}