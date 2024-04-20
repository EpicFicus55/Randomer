#include "cglm/cglm.h"
#include "data.h"

typedef struct
	{
	vec3			position;
	vec4			color;
	mat4			model_matrix;
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

