#version 330 core

uniform sampler2D sampler;

out vec4 color;

in vec2 texCoord;

void main() {
    color = vec4(1.0f) * texture(sampler, texCoord);
}