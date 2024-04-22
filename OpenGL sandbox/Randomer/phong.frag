#version 330 core

in vec2 vTexCoord;

uniform float uAmbientStrength;
uniform sampler2D uTexture;

void main()
{
vec3 ambient = uAmbientStrength * lightColor;

vec3 result = ambient * objectColor;
FragColor = vec4(result, 1.0);

}  