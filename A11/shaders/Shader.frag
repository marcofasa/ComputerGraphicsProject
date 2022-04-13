#version 450
layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 1) uniform GlobalUniformBufferObject {
	float time;
} gubo;

void main() {
	outColor = vec4(1.0, 0.0, 0.0, 1.0f);
}