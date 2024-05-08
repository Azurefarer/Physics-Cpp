#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
in vec3 UV;
uniform sampler2D texture01;
uniform sampler2D texture02;

void main()
{
    FragColor = vec4(0.8157, 0.5333, 0.8275, 1.0);
    FragColor *= mix(texture(texture01, TexCoord), texture(texture02, TexCoord), 0.5);
}