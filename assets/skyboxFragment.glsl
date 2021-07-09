varying vec3 TexCoords;

uniform samplerCube texSampler;

void main()
{    
    gl_FragColor = textureCube(texSampler, TexCoords);
}
