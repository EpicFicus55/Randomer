#include <string.h>

#include "camera_utils.h"


static void camera_A_key_press_callback( Camera* );


/*
Initializes a camera based on user input
*/
void camera_init
	(
	Camera*			camera,
	Camera_Type		camera_type,
	vec3			camera_position,
	vec3			target_position
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
memcpy( &camera->camera_target[ 0 ], &target_position[ 0 ], sizeof(vec3) );

camera->camera_type = camera_type;

/* Compute the camera parameters */
glm_mat4_identity( camera->view );

glm_vec3_sub( camera->camera_pos, camera->camera_target, camera->camera_direction );
glm_normalize( camera->camera_direction );

glm_vec3_cross( camera->camera_direction, camera->system_y, camera->camera_right );
glm_normalize( camera->camera_right );

glm_vec3_cross( camera->camera_direction, camera->camera_right, camera->camera_up );
glm_normalize( camera->camera_up );

glm_lookat
	(
	camera->camera_pos,
	camera->camera_target,
	camera->camera_up,
	camera->camera_lookat
	);

/* The renderer will mostly use the view matrix to apply transformations */
memcpy( camera->view, camera->camera_lookat, sizeof(mat4) );

/* Set the camera up based on its type */
switch( camera_type )
	{
	case CAMERA_TYPE_STATIONARY_NONE:
		/* This is just a stationary view pointing to a target. */
		/* No callbacks necessary. */
		break;
	case CAMERA_TYPE_XZ_KEYBOARD:
		/* Can move along the X and Z directions using WASD. */
		camera->pfn_A_key_callback = &( camera_A_key_press_callback );
		break;
	case CAMERA_TYPE_XYZ_KEYBOARD_MOUSE:
		break;
	default:
		printf( "Invalid camera type\n" );
		break;
	};

}


static void camera_A_key_press_callback
	(
	Camera* camera
	)
{
camera->camera_pos;

}