#version 430

layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texCoord;

out vec2 texCoord_interp;

void main()
{
    texCoord_interp = texCoord;
    gl_Position = vec4(position, 1.0);
}
