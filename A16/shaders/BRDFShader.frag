#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

layout(binding = 1) uniform sampler2D texSampler;

layout(binding = 2) uniform GlobalUniformBufferObject {
	vec3 lightDir0;
	vec3 lightColor0;
	vec3 lightDir1;
	vec3 lightColor1;
	vec3 lightDir2;
	vec3 lightColor2;
	vec3 lightDir3;
	vec3 lightColor3;
	vec3 eyePos;
	vec4 selector;
} gubo;

/**** Modify from here *****/


vec3 Lambert_Diffuse_BRDF(vec3 L, vec3 N, vec3 V, vec3 C) {
	// Lambert Diffuse BRDF model
	// in all BRDF parameters are:
	// vec3 L : light direction  (d)
	// vec3 N : normal vector (nx)
	// vec3 V : view direction
	// vec3 C : main color (diffuse color, or specular color)
	float LdotN = max(0.0, dot(N, L));
	vec3 diffuseLambert = C * LdotN;


	return diffuseLambert;
}

vec3 Oren_Nayar_Diffuse_BRDF(vec3 L, vec3 N, vec3 V, vec3 C, float sigma) {
	// Directional light direction
	// additional parameter:
	// float sigma : roughness of the material
	float LdotN = max(0.0, dot(N, L));
	vec3 diffuseLambert = C * LdotN;
	float VdotN = max(0.0, dot(N, V));
	float theta_i = acos(LdotN);
	float theta_r = acos(VdotN);
	float alpha = max(theta_i, theta_r);
	float beta = min(min(theta_i, theta_r), 1.57);
	float A = 1.0 - 0.5 * sigma / (sigma + 0.33);
	float B = 0.45 * sigma / (sigma + 0.09);
	vec3 v_i = normalize(L - N * LdotN);
	vec3 v_r = normalize(V - N * VdotN);
	float G = max(0.0, dot(v_i, v_r));
	vec3 diffuseOrenNayar = diffuseLambert * (A + B * G * sin(alpha) * tan(beta));

	return diffuseOrenNayar;
}

vec3 Phong_Specular_BRDF(vec3 L, vec3 N, vec3 V, vec3 C, float gamma)  {
	// Phong Specular BRDF model
	// additional parameter:
	// float gamma : exponent of the cosine term

	// Specular
	float LdotN = max(0.0, dot(N, L));
	vec3 reflection = -reflect(L, N);
	float LdotR = max(dot(reflection, V), 0.0);

	vec3 LScol = C * max(sign(LdotN),0.0);

	vec3 specularPhong = LScol * pow(LdotR, gamma);

	return specularPhong;
}

vec3 Toon_Diffuse_BRDF(vec3 L, vec3 N, vec3 V, vec3 C, vec3 Cd, float thr) {
	// Toon Diffuse Brdf
	// additional parameters:
	// vec3 Cd : color to be used in dark areas
	// float thr : color threshold

	float LdotN = max(0.0, dot(N, L));

	//??
	vec3 diffuseToon = max(sign(LdotN- thr),0.0) * C ;
	return diffuseToon;
}

vec3 Toon_Specular_BRDF(vec3 L, vec3 N, vec3 V, vec3 C, float thr)  {
	// Directional light direction
	// additional parameter:
	// float thr : color threshold

	//calculating tangent and bitangent
	/*
	float tbf = max(0.0, sign(abs(N.y) - 0.707));
	vec3 t = normalize(cross(N, vec3(1,0,0)));
	vec3 b = normalize(cross(N, t));
	*/

	// Specular
	float LdotN = max(0.0, dot(N, L));
	vec3 reflection = -reflect(L, N);
	float LdotR = max(dot(reflection, V), 0.0);
	vec3 halfVec = normalize(L + V);
	float HdotN = max(dot(N, halfVec), 0.0);
	vec3 LScol = C * max(sign(LdotN),0.0);

	//specularToonP
	vec3 specularToonP = max(sign(LdotR - thr), 0.0) * LScol ;

	return specularToonP;
}


/**** To here *****/




vec3 BRDF_D(vec3 L, vec3 N, vec3 V, vec3 C) {
	return gubo.selector.x * Lambert_Diffuse_BRDF(L, N, V, C) +
		   (1.0 - gubo.selector.x) * (1.0 - gubo.selector.y) * 
		   			Toon_Diffuse_BRDF(L, N, V, C, 0.2f * C, 0.5) +
		   (1.0 - gubo.selector.x) * (gubo.selector.y) * 
		   			Oren_Nayar_Diffuse_BRDF(L, N, V, C, 1.5);
}

vec3 BRDF_S(vec3 L, vec3 N, vec3 V, vec3 C) {
	return Phong_Specular_BRDF(L, N, V, C, 200.0f) * gubo.selector.z +
		   (1.0 - gubo.selector.x) * (1.0 - gubo.selector.y) * 
		   			Toon_Specular_BRDF(L, N, V, vec3(1,1,1), 0.97f);
}

void main() {
	vec3 Norm = normalize(fragNorm);
	vec3 EyeDir = normalize(gubo.eyePos.xyz - fragPos);
	
	float AmbFact = 0.025;
	
	vec3 DiffColor = texture(texSampler, fragTexCoord).rgb * gubo.selector.w + vec3(1,1,1) * (1-gubo.selector.w);
	vec3 Diffuse = vec3(0,0,0);
	
	Diffuse += BRDF_D(gubo.lightDir0, Norm, EyeDir, DiffColor) * gubo.lightColor0;
	Diffuse += BRDF_D(gubo.lightDir1, Norm, EyeDir, DiffColor) * gubo.lightColor1;
	Diffuse += BRDF_D(gubo.lightDir2, Norm, EyeDir, DiffColor) * gubo.lightColor2;
	Diffuse += BRDF_D(gubo.lightDir3, Norm, EyeDir, DiffColor) * gubo.lightColor3;
	
	vec3 Specular = vec3(0,0,0);
	Specular += BRDF_S(gubo.lightDir0, Norm, EyeDir, vec3(1,1,1)) * gubo.lightColor0;
	Specular += BRDF_S(gubo.lightDir1, Norm, EyeDir, vec3(1,1,1)) * gubo.lightColor1;
	Specular += BRDF_S(gubo.lightDir2, Norm, EyeDir, vec3(1,1,1)) * gubo.lightColor2;
	Specular += BRDF_S(gubo.lightDir3, Norm, EyeDir, vec3(1,1,1)) * gubo.lightColor3;

	vec3 Ambient = AmbFact * DiffColor;
	
	outColor = vec4(Diffuse + Specular + Ambient, 1.0f);	
}