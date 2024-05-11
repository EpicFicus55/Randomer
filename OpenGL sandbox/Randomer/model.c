#include <stdio.h>
#include <stdlib.h>
#include <assimp/cimport.h>

#include "model.h"
#include "texture.h"

/* Static variable to help with the node traversals */
static int mesh_idx = 0;


void model_init_position
	(
	Model*	model,
	vec3	pos
	)
{
/* Initialize the position and the model matrix*/
memcpy( model->pos, pos, sizeof(model->pos) );

glm_mat4_identity( model->model_mat );
glm_translate( model->model_mat, model->pos );

}

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

model->mesh_count = scene->mNumMeshes;

/* Allocate memory for all meshes */
 model->aMeshes = ( Mesh* )malloc( scene->mNumMeshes * sizeof( Mesh ) );

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
	model_process_mesh
		(
		&model->aMeshes[ mesh_idx ],
		scene->mMeshes[ node->mMeshes[ i ] ],
		scene
		);
	mesh_init( &model->aMeshes[ mesh_idx ], NULL, 0, NULL, 0, NULL, 0 );
	mesh_idx++;
	}

/* Recursively process the remaining nodes */
for( unsigned int i = 0; i < node->mNumChildren; i++ )
	{
	if( node->mChildren )
		{
		model_node_process( model, node->mChildren[ i ], scene );
		}
	}
}


void model_process_mesh
	(
	Mesh*					randomer_mesh,
	struct aiMesh*			assimp_mesh,
	const struct aiScene*	scene
	)
{
memset( randomer_mesh, 0, sizeof( Mesh ) );

/* Allocate memory for every vertex */
randomer_mesh->vertex_count = assimp_mesh->mNumVertices;
randomer_mesh->aVertices = ( Vertex_3p3n2t* )malloc( assimp_mesh->mNumVertices * sizeof( Vertex_3p3n2t ) );

/* Process the vertex attributes - position, normals, texture coordinates */
for( unsigned int vtx = 0; vtx < assimp_mesh->mNumVertices; vtx++ )
	{
	/* Set the vertex positions */
	randomer_mesh->aVertices[ vtx ].position[ 0 ] = assimp_mesh->mVertices[ vtx ].x;
	randomer_mesh->aVertices[ vtx ].position[ 1 ] = assimp_mesh->mVertices[ vtx ].y;
	randomer_mesh->aVertices[ vtx ].position[ 2 ] = assimp_mesh->mVertices[ vtx ].z;

	/* Set the vertex normals */
	randomer_mesh->aVertices[ vtx ].normals[ 0 ] = assimp_mesh->mNormals[ vtx ].x;
	randomer_mesh->aVertices[ vtx ].normals[ 1 ] = assimp_mesh->mNormals[ vtx ].y;
	randomer_mesh->aVertices[ vtx ].normals[ 2 ] = assimp_mesh->mNormals[ vtx ].z;
	
	/* Set the vertex texture coordinates (if necessary) */
	if( assimp_mesh->mTextureCoords[ 0 ] )
		{
		randomer_mesh->aVertices[ vtx ].tex_coords[ 0 ] = assimp_mesh->mTextureCoords[ 0 ][ vtx ].x;
		randomer_mesh->aVertices[ vtx ].tex_coords[ 1 ] = assimp_mesh->mTextureCoords[ 0 ][ vtx ].y;
		}
	else
		{
		randomer_mesh->aVertices[ vtx ].tex_coords[ 0 ] = 0.0f;
		randomer_mesh->aVertices[ vtx ].tex_coords[ 1 ] = 0.0f;
		}

	}

/* Allocate memory for every index */
randomer_mesh->index_count = assimp_mesh->mNumFaces * assimp_mesh->mFaces[ 0 ].mNumIndices;
randomer_mesh->aIndices = ( unsigned int* )malloc( assimp_mesh->mNumFaces * assimp_mesh->mFaces[ 0 ].mNumIndices * sizeof( unsigned int ) );

/* Process the indices */
unsigned int _mesh_curr_idx = 0;
for( unsigned int i = 0; i < assimp_mesh->mNumFaces; i++ )
	{
	struct aiFace _face = assimp_mesh->mFaces[ i ];
	for( unsigned int j = 0; j < _face.mNumIndices; j++ )
		{
		randomer_mesh->aIndices[ _mesh_curr_idx++ ] = _face.mIndices[ j ];
		}
	}

/* Process the material textures */
if( assimp_mesh->mMaterialIndex >= 0 )
	{
	struct aiMaterial* _material = scene->mMaterials[ assimp_mesh->mMaterialIndex ];
	unsigned int _diff_tex_cnt = 0; /* Diffuse map count */
	unsigned int _spec_tex_cnt = 0; /* Specular map count */
	unsigned int _curr_tex = 0;
	
	_diff_tex_cnt = aiGetMaterialTextureCount( _material, aiTextureType_DIFFUSE );
	_spec_tex_cnt = aiGetMaterialTextureCount( _material, aiTextureType_SPECULAR );
	
	/* Allocate memory for the textures */
	randomer_mesh->texture_count = _diff_tex_cnt + _spec_tex_cnt;
	randomer_mesh->aTextures = ( Mesh_Texture* )malloc( randomer_mesh->texture_count * sizeof( Mesh_Texture ) );

	if( !randomer_mesh->aTextures )
		{
		return;
		}

	/* Load the diffuse textures first */
	for( unsigned int i = 0; i < _diff_tex_cnt; i++ )
		{
		struct aiString _tex_name;
		aiGetMaterialTexture( _material, aiTextureType_DIFFUSE, i, &_tex_name, NULL, NULL, NULL, NULL, NULL, NULL );

		randomer_mesh->aTextures[ _curr_tex ].type = TEXTURE_DIFFUSE_MAP;
		randomer_mesh->aTextures[ _curr_tex ].path = "D:\\Stuff\\Randomer\\Assets\\Models\\backpack\\diffuse.jpg";
		texture_load( &randomer_mesh->aTextures[ _curr_tex ].handle, "D:\\Stuff\\Randomer\\Assets\\Models\\backpack\\diffuse.jpg" );

		_curr_tex++;
		}
//
	/* Load the specular textures next */
	for( unsigned int i = 0; i < _spec_tex_cnt; i++ )
		{
		struct aiString _tex_name;
		aiGetMaterialTexture( _material, aiTextureType_SPECULAR, i, &_tex_name, NULL, NULL, NULL, NULL, NULL, NULL );

		randomer_mesh->aTextures[ _curr_tex ].type = TEXTURE_SPECULAR_MAP;
		randomer_mesh->aTextures[ _curr_tex ].path = "D:\\Stuff\\Randomer\\Assets\\Models\\backpack\\specular.jpg";
		texture_load( &randomer_mesh->aTextures[ _curr_tex ].handle, "D:\\Stuff\\Randomer\\Assets\\Models\\backpack\\specular.jpg" );
		
		_curr_tex++;
		}
	}

return;
}
