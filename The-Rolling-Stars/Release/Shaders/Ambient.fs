#version 450 core

in vec2 fragTexCoords;

out vec4 color;

uniform sampler2D texture_diffuse1;

//Ranges from 0 to 1, 0 being unlit and 1 being lit
uniform float ambientStr = 0.5f;
uniform vec3 ambientColor = glm::vec3(1.0f, 1.0f, 1.0f);

void main(void)
{
	vec3 ambient = ambientStr * ambientColor;

	color = vec4(ambient, 1.0f) * texture(texture_diffuse1, fragTexCoords);
}