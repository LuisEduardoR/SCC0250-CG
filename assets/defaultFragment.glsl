#version 420 core
// This is only available in version 4.30,
// but my 10 year old gpu only supports up to 4.20
#extension GL_ARB_explicit_uniform_location : require

////////////////////////////////////////
// Uniforms
////////////////////////////////////////

// Transformation
layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 projection;
// Base color
layout(location = 3) uniform vec4 color;
layout(location = 4) uniform sampler2D texSampler;
// Ambient Light
layout(location = 5) uniform vec3 ambientLightColor;
layout(location = 6) uniform float ambientReflection; //ka
// Point Light
layout(location = 7) uniform vec3 lightPosition;
layout(location = 8) uniform vec3 lightColor;
layout(location = 9) uniform float diffuseReflection; //kd
layout(location = 10) uniform float specularReflection; //ks
layout(location = 11) uniform float specularReflectionExp; //ns

////////////////////////////////////////
// Inputs
////////////////////////////////////////

layout(location = 0) in vec3 worldPosition;
layout(location = 1) in vec2 texPosition;
layout(location = 2) in vec3 worldNormal;

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

vec3 getDiffuseLight(vec3 lightDirection, vec3 worldNormal)
{
    float lightCosine = dot(worldNormal, lightDirection);
    // Angle must be between 0° and 90°,
    // so cosine must be between 0 and 1.
    lightCosine = max(0, lightCosine);

    // kd * Il * (N dot L)
    return diffuseReflection * lightColor * lightCosine;
}

vec3 getSpecularLight(vec3 lightDirection, vec3 worldNormal)
{
    vec3 cameraPosition = -view[3].xyz;
    vec3 cameraDirection = normalize(cameraPosition - worldPosition);

    vec3 reflectDirection = normalize(reflect(-lightDirection, worldNormal));
    float reflectCosine = dot(cameraDirection, reflectDirection);
    // Angle must be between 0° and 90°,
    // so cosine must be between 0 and 1.
    reflectCosine = max(0, reflectCosine);

    // ks * Il * (N dot H)^ns
    return specularReflection * lightColor * pow(reflectCosine, specularReflectionExp);
}

vec3 getLight()
{
    vec3 worldNormal = normalize(worldNormal);
    vec3 lightDirection = normalize(lightPosition - worldNormal);

    return getAmbientLight()
        + getDiffuseLight(lightDirection, worldNormal)
        + getSpecularLight(lightDirection, worldNormal);
}

void main()
{
    vec4 baseColor = texture(texSampler, texPosition);

    outColor = baseColor * vec4(getLight(), 1);
}
