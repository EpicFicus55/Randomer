#version 330 core

in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vFragPos;

uniform float	uAmbientStrength;
uniform vec4	uLightColor;
uniform vec3	uLightPosition;
uniform vec3	uCameraPos;

uniform sampler2D uTexture;

out vec4 FragColor;

void main()
{
vec4 _ambient_color = uLightColor * uAmbientStrength;
vec3 _normal		= normalize( vNormal );
vec3 _light_dir		= normalize( uLightPosition - vFragPos ); 
float _theta		= max( dot( _normal, _light_dir ), 0.0f );
vec4 _diffuse		= _theta *  uLightColor;

/* Calculate specular highlights */
vec3	_viewDir = normalize( uCameraPos - vFragPos );
vec3	_reflectDir = reflect( -_light_dir, _normal );
float	_spec = pow( max( dot( _viewDir, _reflectDir ), 0.0 ), 32 );
vec4	_specular = 0.5 * _spec * uLightColor;

vec4 _color_sum = _specular + _ambient_color + _diffuse;

FragColor = texture2D( uTexture, vTexCoord ) * _color_sum;

}  