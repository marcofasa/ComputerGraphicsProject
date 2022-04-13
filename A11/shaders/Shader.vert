#version 450
layout(set = 0, binding = 0) uniform UniformBufferObject {
	mat4 worldMat;
	mat4 viewMat;
	mat4 prjMat;
} ubo;
layout(location = 0) in vec3 inPosition;

void main() {
	gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
}