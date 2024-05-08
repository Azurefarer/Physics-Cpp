#version 330 core
out vec4 FragColor;
in vec3 tutColor;
in vec3 UV;
uniform float colorScale;

void main()
{
    FragColor = vec4(colorScale) + vec4(UV, 1.0);
}