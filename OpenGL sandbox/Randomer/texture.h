#pragma once

typedef struct
	{
	unsigned int	handle;
	} Texture;


/*
Loads a texture from a given file
*/
void texture_load
	(
	Texture*	texture,
	char*		path
	);