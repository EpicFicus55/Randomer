#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

uniform bool u_use_color;

out vec3 vCol;

void main()
    {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    if( u_use_color )
        {
        vCol = aCol;
        }
    else
        {
        vCol = vec3( 0.25, 0.25, 0.75 );
        }
    }
