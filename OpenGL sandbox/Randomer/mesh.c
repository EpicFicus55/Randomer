#include <glad/glad.h>
#include <string.h>

#include "mesh.h"
#include "util.h"
#include "shader_utils.h"

void mesh_init
	( 
	Mesh* mesh, 
	Vertex_3p3n2t* vertices,	unsigned int vertex_count,
	unsigned int* indices,		unsigned int index_count,
	Texture* textures,			unsigned int texture_count
	)
{
mesh->aVertices = vertices;
mesh->aIndices  = indices;
mesh->aTextures = textures;

mesh->vertex_count  = vertex_count;
mesh->index_count   = index_count;
mesh->texture_count = texture_count;

/* Set up the openGL objects */
GL_CALL( glGenVertexArrays( 1, &mesh->VAO ) );
GL_CALL( glGenBuffers( 1, &mesh->VBO ) );
GL_CALL( glGenBuffers( 1, &mesh->EBO ) );

GL_CALL( glBindVertexArray( mesh->VAO ) );

/* Set up the vertex and index data */
GL_CALL( glBindBuffer( GL_ARRAY_BUFFER, mesh->VBO ) );
GL_CALL( glBufferData
			( 
			GL_ARRAY_BUFFER, 
			mesh->vertex_count * sizeof( Vertex_3p3n2t ), 
			&mesh->aVertices[ 0 ],
			GL_STATIC_DRAW
			)
		);

GL_CALL( glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mesh->EBO ) );
GL_CALL( glBufferData
			( 
			GL_ELEMENT_ARRAY_BUFFER, 
			mesh->index_count * sizeof( unsigned int ), 
			&mesh->aIndices[ 0 ],
			GL_STATIC_DRAW
			)
		);

/* Set up the attributes */
GL_CALL( glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex_3p3n2t ), (void*)offsetof( Vertex_3p3n2t, position ) ) );
GL_CALL( glEnableVertexAttribArray( 0 ) );

GL_CALL( glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex_3p3n2t ), (void*)offsetof( Vertex_3p3n2t, normals ) ) );
GL_CALL( glEnableVertexAttribArray( 1 ) );

GL_CALL( glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex_3p3n2t ), (void*)offsetof( Vertex_3p3n2t, tex_coords) ) );
GL_CALL( glEnableVertexAttribArray( 2 ) );

GL_CALL( glBindVertexArray( 0 ) );
}


void mesh_draw
	(
	Mesh* mesh,
	unsigned int shader_program
	)
{
unsigned int _diff_tex_cnt = 0;
unsigned int _spec_tex_cnt = 0;
char		 _sampler_name[ 100 ];

/* The shader uniforms will be as such:
material.uDiffuseMap1
material.uSpecularMap2 */
for( int i = 0; i < mesh->texture_count; i++ )
	{
	memset(_sampler_name, 0, sizeof(_sampler_name) );

	GL_CALL( glActiveTexture( GL_TEXTURE0 + i ) );
	if( mesh->aTextures[ i ].type == TEXTURE_DIFFUSE_MAP )
		{
		_diff_tex_cnt++;
		snprintf( _sampler_name, sizeof(_sampler_name), "material.uDiffuseMap%d", _diff_tex_cnt );
		}
	else if(mesh->aTextures[i].type == TEXTURE_DIFFUSE_MAP )
		{
		_spec_tex_cnt++;
		snprintf( _sampler_name, sizeof(_sampler_name), "material.uSpecularMap%d", _spec_tex_cnt );
		}

	shdr_set_int_uniform( shader_program, _sampler_name, i );
	}

GL_CALL( glActiveTexture( GL_TEXTURE0 ) );

GL_CALL( glBindVertexArray( mesh->VAO ) );
GL_CALL( glUseProgram( shader_program ) );
GL_CALL( glDrawElements( GL_TRIANGLES, mesh->index_count, GL_UNSIGNED_INT, mesh->aIndices ) );
GL_CALL( glBindVertexArray( 0 ) );
GL_CALL( glUseProgram( 0 ) );

}
