#include "cglm/cglm.h"

typedef struct
	{
	vec3			position;
	vec4			color;
	unsigned int	VAO_handle;
	unsigned int	VBO_handle;
	} Light_Source;

/*
Initialize a light source
*/
void render_init_light
	(
	Light_Source*	source,
	vec3			position,
	vec4			color
	);
