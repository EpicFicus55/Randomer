#pragma once

/* Will be deprecated */
typedef struct
	{
	unsigned int	handle;
	} Texture_Type;


/*
Loads a texture from a given file
*/
void texture_load
	(
	unsigned int*	texture,
	char*			path
	);