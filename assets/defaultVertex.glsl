#version 420 core
// This is only available in version 4.30,
// but my 10 year old gpu only supports up to 4.20
#extension GL_ARB_explicit_uniform_location : require

////////////////////////////////////////
// Uniforms
////////////////////////////////////////

layout(location = 0) uniform mat4 transform;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 projection;

////////////////////////////////////////
// Inputs
////////////////////////////////////////

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 inTexPosition;

////////////////////////////////////////
// Outputs
////////////////////////////////////////

layout(location = 0) out vec2 texPosition;

////////////////////////////////////////
// Code
////////////////////////////////////////

void main()
{
    gl_Position = projection * view * transform * vec4(position, 1.0);
    texPosition = inTexPosition;
}
