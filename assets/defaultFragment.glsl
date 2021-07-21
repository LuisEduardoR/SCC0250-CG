#version 420 core
// This is only available in version 4.30,
// but my 10 year old gpu only supports up to 4.20
#extension GL_ARB_explicit_uniform_location : require

////////////////////////////////////////
// Uniforms
////////////////////////////////////////

layout(location = 3) uniform vec4 color;
layout(location = 4) uniform sampler2D texSampler;
// Ambient Light
layout(location = 5) uniform vec3 ambientLightColor;
layout(location = 6) uniform float ambientReflection; //ka
// Point Light
layout(location = 7) uniform vec3 lightPosition;
layout(location = 8) uniform vec3 diffuseLightColor;
layout(location = 9) uniform float diffuseReflection; //kd

////////////////////////////////////////
// Inputs
////////////////////////////////////////

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texPosition;
layout(location = 2) in vec3 normal;

////////////////////////////////////////
// Outputs
////////////////////////////////////////

layout(location = 0) out vec4 outColor;

////////////////////////////////////////
// Code
////////////////////////////////////////

vec3 getAmbientLight()
{
    return ambientReflection * ambientLightColor;
}

vec3 getDiffuseLight()
{
    vec3 lightDirection = normalize(lightPosition - position);

    float lightCosine = dot(normal, lightDirection);
    // Angle must be between 0° and 90°,
    // so cosine must be between 0 and 1.
    lightCosine = max(0, lightCosine);

    return lightCosine * diffuseReflection * diffuseLightColor;
}

vec3 getLight()
{
    return getAmbientLight() + getDiffuseLight();
}

void main()
{
    vec4 baseColor = texture(texSampler, texPosition);

    outColor = baseColor * vec4(getLight(), 1);
}
