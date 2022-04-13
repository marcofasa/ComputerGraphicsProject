#version 450

layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 1) uniform GlobalUniformBufferObject {
	float time;
} gubo;

float rand(float time){
	return abs(sin(dot(time, 12.9898)));
}

int k=0;

void main() {
		outColor = vec4(gubo.time,abs(gubo.time-1), abs(gubo.time), 1.0f);
}