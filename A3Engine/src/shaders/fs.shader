#version 330 core
out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D albedo_texture;
uniform vec4 color;

void main() {
	//FragColor = color;
	//FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.2) * color;
	FragColor = texture(albedo_texture, texCoord) * color;
}