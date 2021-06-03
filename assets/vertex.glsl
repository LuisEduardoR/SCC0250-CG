attribute vec3 position;

uniform mat4 transform;
uniform mat4 view;

void main()
{
    gl_Position = view * transform * vec4(position, 1.0);
}