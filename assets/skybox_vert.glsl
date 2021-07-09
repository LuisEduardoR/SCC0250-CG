attribute vec3 position;

varying vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    TexCoords = position;
    gl_Position = projection * view * vec4(position, 1.0);
}  