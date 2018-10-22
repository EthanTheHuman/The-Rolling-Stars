#version 450 core

in vec4 fragcolor;
in vec2 fragTexCoord;

out vec4 color;

uniform sampler2D SpriteTex;

void main(void)
{
	color = texture(SpriteTex, fragTexCoord);
}