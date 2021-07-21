#version 420 core
// This is only available in version 4.30,
// but my 10 year old gpu only supports up to 4.20
#extension GL_ARB_explicit_uniform_location : require

////////////////////////////////////////
// Uniforms
////////////////////////////////////////

layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 projection;

////////////////////////////////////////
// Inputs
////////////////////////////////////////

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 inTexPosition;
layout(location = 2) in vec3 normal;

////////////////////////////////////////
// Outputs
////////////////////////////////////////

layout(location = 0) out vec3 outPosition;
layout(location = 1) out vec2 outTexPosition;
layout(location = 2) out vec3 outNormal;

////////////////////////////////////////
// Code
////////////////////////////////////////

void main()
{
    outPosition = vec3(model * vec4(position, 1.0));;
    outTexPosition = inTexPosition;
    outNormal = vec3(model * vec4(normal, 1.0));

    gl_Position = projection * view * model * vec4(position, 1.0);
}
