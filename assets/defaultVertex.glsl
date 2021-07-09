attribute vec3 position;
attribute vec2 inTexPosition;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

varying vec2 texPosition;

void main()
{
    gl_Position = projection * view * transform * vec4(position, 1.0);
    texPosition = inTexPosition;
}
