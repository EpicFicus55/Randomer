#include <glad/glad.h>
#include <stdlib.h>
#include <string.h>

#include "randomer_light.h"
#include "util.h"
#include "shader_utils.h"

/*
Initialize a light source
*/
void render_init_light
	(
	Light_Source*	source,
	vec3			position,
	vec4			color
	)
{
/* Initialize the position and the model matrix*/
memcpy( source->position, position, sizeof(source->position) );

glm_mat4_identity( source->model_matrix );
//glm_translate( source->model_matrix, source->position );
glm_translate_x( source->model_matrix, 0.5f );

/* Initialize the color */
memcpy( source->color, color, sizeof(source->color) );

/* Initialize a VAO and the vertex attributes */
GL_CALL( glGenVertexArrays( 1, &source->VAO_handle ) );
GL_CALL( glGenBuffers( 1, &source->VBO_handle ) );

GL_CALL( glBindVertexArray( source->VAO_handle ) );
GL_CALL( glBindBuffer( GL_ARRAY_BUFFER, source->VBO_handle ) );
GL_CALL( glBufferData( GL_ARRAY_BUFFER, sizeof(cube_vertices_3p2t), cube_vertices_3p2t, GL_STATIC_DRAW ) );

GL_CALL( glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), NULL ) );
GL_CALL( glEnableVertexAttribArray( 0 ) );

GL_CALL( glBindBuffer( GL_ARRAY_BUFFER, 0 ) );
GL_CALL( glBindVertexArray( 0 ) );

}
