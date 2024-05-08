#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 tutColor;
out vec4 vertexColor02;
out vec3 UV;
uniform float hOffset;


void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	tutColor = aColor;
	vertexColor02 = -aPos.rgbr;
	UV = aPos.rgb;
}