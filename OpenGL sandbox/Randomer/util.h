#pragma once
#include <stdio.h>
#include <stdint.h>
#include <glad/glad.h>

#include "cglm/cglm.h"

#ifdef _DEBUG
    #define GL_CALL( glStmt ) do {																	\
			glGetError();																			\
			GLenum err;																				\
            glStmt;																					\
			err = glGetError();																		\
            if( err != GL_NO_ERROR )																\
				{																					\
				printf( "%08x Error caught in: %s (%s, %i)\n", err, #glStmt, __FILE__, __LINE__ );	\
				}																					\
        } while( 0 )
#else
    #define GL_CALL( stmt ) stmt
#endif

typedef struct
	{
	uint32_t width;
	uint32_t height;
	} window_size32_t;

typedef struct
	{
	vec3	ambient;
	vec3	diffuse;
	vec3	specular;
	float	shininess;
	} Material_Type;

typedef enum
	{
	VERTEX_POSITION_BIT = 1,
	COLOR_BIT			= 2,
	TEXTURE_COORDS_BIT	= 4,
	NORMAL_VEC_BIT		= 8
	} vertex_attrib_enum;