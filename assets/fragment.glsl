varying vec2 texPosition;

uniform vec4 color;
uniform sampler2D texSampler;

void main()
{
    gl_FragColor = texture2D(texSampler, texPosition);
}
