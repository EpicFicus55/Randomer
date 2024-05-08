#include <stdio.h>
#include <stdlib.h>
#include <assimp/cimport.h>

#include "model.h"

/* Static variable to help with the node traversals */
static int mesh_idx = 0;

void model_load
	(
	Model*	model,
	char*	path
	)
{
const struct aiScene* scene = aiImportFile
		(
		(const char*) path,
		aiProcess_Triangulate | aiProcess_FlipUVs
		);

if( !scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode )
	{
	printf( "Invalid model!\n" );
	return;
	}

/* Allocate memory for all meshes */
model->aMeshes = ( Mesh* )calloc( scene->mNumMeshes, sizeof( Mesh ) );

mesh_idx = 0;
model_node_process( model, scene->mRootNode, scene );

}


void model_draw
	(
	Model*			model,
	unsigned int	shader
	)
{
for( unsigned int i = 0; i < model->mesh_count; i++ )
	{
	mesh_draw( &model->aMeshes[ i ], shader );
	}

}



void model_node_process
	(
	Model*					model,
	struct aiNode*			node,
	const struct aiScene*	scene
	)
{
for( unsigned int i = 0; i < node->mNumMeshes; i++ )
	{
	Mesh _curr_mesh = model_process_mesh
							(
							scene->mMeshes[ node->mMeshes[ i ] ],
							scene
							);
	memcpy( &model->aMeshes[ mesh_idx ], &_curr_mesh, sizeof( Mesh ) );
	mesh_idx++;
	}

/* Recursively process the remaining nodes */
for( unsigned int i = 0; i < node->mNumChildren; i++ )
	{
	model_node_process( model, node->mChildren[ i ], scene );
	}

}


Mesh model_process_mesh
	(
	struct aiMesh*			mesh,
	const struct aiScene*	scene
	)
{
Mesh	_ret;

memset( &_ret, 0, sizeof(_ret) );

/* Allocate memory for every vertex */
_ret.aVertices = ( Vertex_3p3n2t* )malloc( mesh->mNumVertices * sizeof( Vertex_3p3n2t ) );

/* Process the vertex attributes - position, normals, texture coordinates */
for( unsigned int pos = 0; pos < mesh->mNumVertices; pos++ )
	{
	vec3 position;
	vec3 normals;
	vec2 tex_coords;

	/* Set the vertex positions */
	position[ 0 ] = mesh->mVertices[ pos ].x;
	position[ 1 ] = mesh->mVertices[ pos ].y;
	position[ 2 ] = mesh->mVertices[ pos ].z;
	memcpy( _ret.aVertices[ pos ].position, position, sizeof( vec3 ) );

	/* Set the vertex normals */
	normals[ 0 ] = mesh->mNormals[ pos ].x;
	normals[ 1 ] = mesh->mNormals[ pos ].y;
	normals[ 2 ] = mesh->mNormals[ pos ].z;
	memcpy( _ret.aVertices[ pos ].normals, normals, sizeof( vec3 ) );

	/* Set the vertex texture coordinates (if necessary) */
	if( mesh->mTextureCoords[ 0 ] )
		{
		tex_coords[ 0 ] = mesh->mTextureCoords[ 0 ][ pos ].x;
		tex_coords[ 1 ] = mesh->mTextureCoords[ 0 ][ pos ].y;
		memcpy( _ret.aVertices[ pos ].tex_coords, tex_coords, sizeof( vec2 ) );
		}
	else
		{
		tex_coords[ 0 ] = 0.0f;
		tex_coords[ 1 ] = 0.0f;
		}
	}

/* Process the indices */
unsigned int _mesh_curr_idx = 0;
for( unsigned int i = 0; i < mesh->mNumFaces; i++ )
	{
	struct aiFace _face = mesh->mFaces[ i ];
	for( unsigned int j = 0; j < _face.mNumIndices; j++ )
		{
		_ret.aIndices[ _mesh_curr_idx++ ] = _face.mIndices[ j ];
		}
	}


}
