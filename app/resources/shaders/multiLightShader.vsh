#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 texCoord;

uniform mat4 transform;
uniform mat4 tfMesh;
out vec3 N;
out vec3 pos_interp;


void main()
{
    gl_Position = transform * vec4(position, 1.0);
    
    N = (tfMesh * vec4(normal, 0.0)).xyz;

    // pass on interpolated position
    pos_interp = (tfMesh * vec4(position, 1.0)).xyz;

}
