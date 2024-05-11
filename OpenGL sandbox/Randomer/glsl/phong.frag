#version 330 core

struct Material 
    {
    sampler2D   uDiffuseMap1;
    sampler2D   uSpecularMap1;
    }; 

in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vFragPos;

uniform float	    uAmbientStrength;
uniform vec4	    uLightColor;
uniform vec3	    uLightPosition;
uniform Material    uMaterial;
uniform vec3	    uCameraPos;

out vec4 FragColor;

void main()
{
// TODO: Clean all this mess up
vec4 _ambient_color = uLightColor * texture( uMaterial.uDiffuseMap1, vTexCoord ) * 0.2f;
vec3 _normal		= normalize( vNormal );
vec3 _light_dir		= normalize( uLightPosition - vFragPos ); 
float _theta		= max( dot( _normal, _light_dir ), 0.0f );
vec4 _diffuse		= _theta * ( uLightColor * texture( uMaterial.uDiffuseMap1, vTexCoord ) );

/* Calculate specular highlights */
vec3	_viewDir = normalize( uCameraPos - vFragPos );
vec3	_reflectDir = reflect( -_light_dir, _normal );
float	_spec = pow( max( dot( _viewDir, _reflectDir ), 0.0 ), 32 );
vec4	_specular = 0.5 * _spec * texture( uMaterial.uSpecularMap1, vTexCoord );

vec4 _color_sum = _specular + _ambient_color + _diffuse;

FragColor = _color_sum;

}  