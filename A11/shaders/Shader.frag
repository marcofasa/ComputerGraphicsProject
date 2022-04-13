#version 450

layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 1) uniform GlobalUniformBufferObject {
	float time;
} gubo;

float rand(float time){
	return abs(sin(dot(time, 12.9898)));
	/*
	ORIGINAL
	float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
	}
	*/
}


void main() {
	//To have relaxing aspect is better using linear/sin/cos
	//functions to have a linearity in the change of colours
	// Another way but more chaotic is to use the rand function above
	outColor = vec4(gubo.time,abs(gubo.time-0.5), abs(0.5-gubo.time/2), 1.0f);
}