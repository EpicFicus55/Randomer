#pragma once
#include "cglm/cglm.h"

typedef enum
	{
	CAMERA_TYPE_STATIONARY_NONE,
	CAMERA_TYPE_XZ_KEYBOARD,
	CAMERA_TYPE_XYZ_KEYBOARD_MOUSE,

	/* Must be last */
	CAMERA_TYPE_COUNT
	} Camera_Type;

typedef void ( *Camera_Key_Callback )( void* );

typedef struct  
		{
		/* Camera type */
		Camera_Type camera_type;

		/* Main system axes */
		vec3 system_x;
		vec3 system_y;
		vec3 system_z;

		/* Camera specific axes */
		vec3 camera_pos;
		vec3 camera_front;
		vec3 camera_direction;
		vec3 camera_right;
		vec3 camera_up;

		/* Camera matrices */
		mat4 camera_lookat;
		mat4 view;

		/* Camera parameters */
		float camera_speed;

		/* Callbacks */
		Camera_Key_Callback pfn_A_key_callback;
		Camera_Key_Callback pfn_D_key_callback;
		Camera_Key_Callback pfn_W_key_callback;
		Camera_Key_Callback pfn_S_key_callback;

		} Camera;

/*
Initializes a camera based on user input
*/
void camera_init
	(
	Camera*,
	Camera_Type,
	vec3,
	vec3,
	vec3
	);

/*
Updates a camera's matrices
*/
void update_camera
	(
	Camera*
	);
