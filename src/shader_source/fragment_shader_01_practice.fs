#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
in vec3 UV;
in vec3 color;
uniform sampler2D texture01;
uniform sampler2D texture02;
uniform float time;

void main()
{
    FragColor = vec4(color, 1.0);
    // FragColor *= mix(texture(texture01, TexCoord), texture(texture02, TexCoord), 0.5);
}