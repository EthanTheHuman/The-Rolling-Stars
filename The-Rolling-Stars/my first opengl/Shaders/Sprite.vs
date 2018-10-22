#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec4 fragcolor;
out vec2 fragTexCoord;

uniform mat4 MVP;

void main(void)
{
	gl_Position = (MVP * vec4(position, 1.0));
	//gl_Position = vec4(position, 1.0);
	fragcolor = vec4(color,1.0);
	//fragcolor = color;
 	fragTexCoord = texCoord;
}