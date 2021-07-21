#version 420 core
// This is only available in version 4.30,
// but my 10 year old gpu only supports up to 4.20
#extension GL_ARB_explicit_uniform_location : require

////////////////////////////////////////
// Uniforms
////////////////////////////////////////

layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 projection;

////////////////////////////////////////
// Inputs
////////////////////////////////////////

layout(location = 0) in vec3 position;

////////////////////////////////////////
// Outputs
////////////////////////////////////////

layout(location = 0) out vec3 TexCoords;

////////////////////////////////////////
// Code
////////////////////////////////////////

void main()
{
    TexCoords = position;
    vec4 pos = projection * view * vec4(position, 1.0);
    gl_Position = pos.xyww;
}
