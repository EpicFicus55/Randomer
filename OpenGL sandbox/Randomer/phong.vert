#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;
layout (location = 3) in vec3 aNormal;

uniform mat4 uProjMat;
uniform mat4 uViewMat;
uniform mat4 uModelMat;

out vec2 vTexCoord;
out vec3 vNormal;

/*
We need a vertex position that is in world space
but not in view / screen space 
*/
out vec3 vFragPos;

void main()
{
gl_Position = uProjMat * uViewMat * uModelMat * vec4( aPos.x, aPos.y, aPos.z, 1.0 );

vFragPos = vec3( uModelMat * vec4( aPos, 1.0f ) );

vTexCoord = aTex;

vNormal = aNormal;

}
