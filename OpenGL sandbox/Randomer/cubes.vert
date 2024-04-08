#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;

uniform mat4 uProjMat;
uniform mat4 uViewMat;
uniform mat4 uModelMat;

out vec3 vCol;
out vec2 vTexCoord;

void main()
{
gl_Position = uProjMat * uViewMat * uModelMat * vec4( aPos.x, aPos.y, aPos.z, 1.0 );
vTexCoord = aTex;

}
