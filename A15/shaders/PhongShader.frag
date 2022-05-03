#version 450
#extension GL_ARB_separate_shader_objects : enable
/*
gubo.lightDir->a vec3 containing the direction of the light (for spot and directional lights).  --> d
• gubo.lightPos->a vec3 containing the position of the light (for spot and point lights). --> p
• gubo.lightColor->avec3containingthebasiccolorofthelight. --> l
• gubo.coneInOutDecayExp.x->a float component containing the cosine of the outer
angle of a spot light. --> cos_outer
• gubo.coneInOutDecayExp.y->a float component containing the cosine of the inner
angle of a spot light. --> cos_inner
• gubo.coneInOutDecayExp.z->a float component containing the basic distance g for
both spot and point lights. --> g
• gubo.coneInOutDecayExp.w->a float component containing the denominator
exponent b for both spot and point lights: 0 for no decay, 1 for linear decay and 2 for quadratic
fading.
• Object gubo also contains fields eyePos and selector, which however are not meaningful for the exercise and
are required for other parts of the shader already implemented.
*/
layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

layout(binding = 1) uniform sampler2D texSampler;

layout(binding = 2) uniform GlobalUniformBufferObject {
	vec3 lightDir; //d
	vec3 lightPos; //p
	vec3 lightColor; //l
	vec3 eyePos;
	vec4 coneInOutDecayExp;
	vec4 selector;
} gubo;




/**** Modify from here *****/

vec3 direct_light_dir(vec3 pos) {
	// Directional light direction (d)
	return gubo.lightDir;
}

vec3 direct_light_color(vec3 pos) {
	// Directional light color (l)
	return gubo.lightColor;
}

vec3 point_light_dir(vec3 pos) {
	vec3 dif=normalize(gubo.lightPos-pos);
	// Point light direction
	return dif;
}

//TODO is part 3 correct?  --> MODIFIED line 3083
vec3 point_light_color(vec3 pos) {
	// Point light color
	return gubo.lightColor * pow(gubo.coneInOutDecayExp.z / length(gubo.lightPos-pos),gubo.coneInOutDecayExp.w);
}

vec3 spot_light_dir(vec3 pos) {
	// Spot light direction
	vec3 dif=vec3(normalize(gubo.lightPos-pos));
	return dif;
}

vec3 spot_light_color(vec3 pos) {
	// Spot light color
	vec3 spotDir=vec3(normalize(gubo.lightPos-pos));
	float CosAngle = dot(spotDir,gubo.lightDir);
	return gubo.lightColor * pow(gubo.coneInOutDecayExp.z / length(gubo.lightPos-pos),gubo.coneInOutDecayExp.w ) *
	clamp((CosAngle - gubo.coneInOutDecayExp.x) / (gubo.coneInOutDecayExp.y-gubo.coneInOutDecayExp.x), 0.0, 1.0);
}

/**** To from here *****/





void main() {
	vec3 Norm = normalize(fragNorm);
	vec3 EyeDir = normalize(gubo.eyePos.xyz - fragPos);
	
	vec3 lD;	// light direction from the light model
	vec3 lC;	// light color and intensity from the light model
	
	lD = direct_light_dir(fragPos) * gubo.selector.x +
	     point_light_dir(fragPos)  * gubo.selector.y +
	     spot_light_dir(fragPos)   * gubo.selector.z;
	lC = direct_light_color(fragPos) * gubo.selector.x +
	     point_light_color(fragPos)  * gubo.selector.y +
	     spot_light_color(fragPos)   * gubo.selector.z;

	vec3 Diffuse = (texture(texSampler, fragTexCoord).rgb * gubo.selector.w + vec3(1,1,1) * (1-gubo.selector.w)) * (max(dot(Norm, lD),0.0f) );
	vec3 Specular = vec3(pow(max(dot(EyeDir, -reflect(lD, Norm)),0.0f), 64.0f));
	
	outColor = vec4((Diffuse + Specular) * lC, 1.0f);	
}