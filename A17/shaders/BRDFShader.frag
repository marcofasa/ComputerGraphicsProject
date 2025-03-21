#version 450
#extension GL_ARB_separate_shader_objects : enable

vec3 Blinn_Specular_BRDF(vec3 L, vec3 N, vec3 V, vec3 C, float gamma)  {
	vec3 h = normalize(L + V);
	float alpha = dot(N,h); // angle between the half vector h and the normal vector n
	float intensity = pow(clamp(alpha,0.0f,1.0f),gamma); // cos^gamma(alpha) positive values

	return C * intensity;
}

layout(binding = 1) uniform sampler2D texSampler;

layout(binding = 2) uniform GlobalUniformBufferObject {
	// Direct lights parameters (for diffuse and specular)
	vec3 lightDir0;
	vec3 lightColor0;
	vec3 lightDir1;
	vec3 lightColor1;
	vec3 lightDir2;
	vec3 lightColor2;
	vec3 lightDir3;
	vec3 lightColor3;

	// Ambient light parameters
	vec3 AmbColor; // lA	// also Bottom color for Hemispheric light,
					//      Constant term for Spherical Harmonics light
	vec3 TopColor;	// also DyColor for Spherical Harmonics light
	vec3 DzColor;
	vec3 DxColor;
	
	// Other parameters (not relevant for the exercise)
	vec3 eyePos;
	vec4 selector;
} gubo;

/**** Modify from here *****/
layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

vec3 Case1_Color(vec3 N, vec3 V, vec3 Cd, vec3 Ca, float sigma) {
	// Oren Nayar Diffuse + Ambient
	// No Specular
	// One directional light (lightDir0 and lightColor0)
	//
	// Parameters are:
	//
	// vec3 N : normal vector
	// vec3 V : view direction
	// vec3 Cd : main color (diffuse color)
	// vec3 Ca : ambient color -- mA
	// float sigma : roughness of the material


	//	vec4 ambientAmbient = ambientLightColor * ambColor;


	float LdotN = max(0.0, dot(N, gubo.lightDir0));
	vec3 diffuseLambert = Cd * LdotN;

	float VdotN = max(0.0, dot(N, V));
	float theta_i = acos(LdotN);
	float theta_r = acos(VdotN);
	float alpha = max(theta_i, theta_r);
	float beta = min(min(theta_i, theta_r), 1.57);
	float A = 1.0 - 0.5 * sigma / (sigma + 0.33);
	float B = 0.45 * sigma / (sigma + 0.09);
	vec3 v_i = normalize(gubo.lightDir0 - N * LdotN);
	vec3 v_r = normalize(V - N * VdotN);
	float G = max(0.0, dot(v_i, v_r));
	vec3 diffuseOrenNayar = diffuseLambert * (A + B * G * sin(alpha) * tan(beta));

      vec3 res=(diffuseOrenNayar)*gubo.lightColor0 +Ca*gubo.AmbColor;
	return  res;
}

vec3 Case2_Color(vec3 N, vec3 V, vec3 Cd, vec3 Ca) {
	// Lambert Diffuse + Hemispheric
	// No Specular
	// One directional light (lightDir0 and lightColor0)
	// Hemispheric light oriented along the y-axis
	//
	// Parameters are:
	//
	// vec3 N : normal vector
	// vec3 V : view direction
	// vec3 Cd : main color (diffuse color)
	// vec3 Ca : ambient color
   //gubo.AmbColor-> the bottom color
	//gubo.TopColor-> the top ambient color
	/*
     float amBlend = (dot(normalVec, ADir) + 1.0) / 2.0;
	vec4 ambientHemi = (ambientLightColor * amBlend + ambientLightLowColor * (1.0 - amBlend)) * ambColor;
	*/

	float LdotN = max(0.0, dot(N, gubo.lightDir0));
	vec3 diffuseLambert = Cd * LdotN;
	vec3 HemiDir = vec3(0.0f, 1.0f, 0.0f);
	float amBlend = (dot(N,HemiDir) + 1.0) / 2.0;
	vec3 ambientHemi =diffuseLambert * gubo.lightColor0 + (gubo.TopColor* amBlend + gubo.AmbColor * (1.0 - amBlend)) *Ca;


	
	return ambientHemi;
}

//TODO is a bit darker than solution?
vec3 Case3_Color(vec3 N, vec3 V, vec3 Cs, vec3 Ca, float gamma)  {
	// Spherical Harmonics
	// Blinn Specular
	// Four directional lights (lightDir0 to lightDir3, and lightColor0 to lightColor3)
	//
	// Parameters are:
	//
	// vec3 N : normal vector
	// vec3 V : view direction
	// vec3 Cs : specular color
	// vec3 Ca : ambient color
	// float gamma : Blinn exponent
    //gubo.AmbColor->the constant component for Spherical Harmonics lighting
	//gubo.TopColor-> difference related to the y component of the normal direction for Spherical Harmonics lighting
	//gubo.DzColor,gubo.DxColor->two vec 3 containing the difference related to the z and x components of the normal direction for Spherical Harmonics lighting

	/*
	const mat4 McInv = mat4(vec4(0.25,0.0,-0.25,0.7071),vec4(0.25,0.6124,-0.25,-0.3536),vec4(0.25,-0.6124,-0.25,-0.3536),vec4(0.25,0.0,0.75,0.0));
	mat4 InCols = transpose(mat4(ambientLightLowColor, SHRightLightColor, SHLeftLightColor, ambientLightColor));
	mat4 OutCols = McInv * InCols;
	vec4 ambientSH = vec4((vec4(1,normalVec) * OutCols).rgb, 1.0) * ambColor;
	*/

	// direct light influence (4 sources)
	vec3 D0 = gubo.lightColor0 * Blinn_Specular_BRDF(gubo.lightDir0,N,V,Cs,gamma);
	vec3 D1 = gubo.lightColor1 * Blinn_Specular_BRDF(gubo.lightDir1,N,V,Cs,gamma);
	vec3 D2 = gubo.lightColor2 * Blinn_Specular_BRDF(gubo.lightDir2,N,V,Cs,gamma);
	vec3 D3 = gubo.lightColor3 * Blinn_Specular_BRDF(gubo.lightDir3,N,V,Cs,gamma);
	vec3 D = D0 + D1 + D2 + D3;

	// ambiental light influence (spherical harmonics)
	vec3 A = Ca * (gubo.AmbColor + N.x*gubo.DxColor + N.y*gubo.TopColor + N.z*gubo.DzColor);

	return D + A;

}



/**** To here *****/




void main() {
	vec3 Norm = normalize(fragNorm);
	vec3 EyeDir = normalize(gubo.eyePos.xyz - fragPos);
	
	float AmbFact = 0.025;
	
	vec3 DifCol = texture(texSampler, fragTexCoord).rgb * gubo.selector.w +
				  vec3(1,1,1) * (1-gubo.selector.w);

	vec3 CompColor = gubo.selector.x *
						Case1_Color(Norm, EyeDir, DifCol, DifCol, 1.2f) +
					 gubo.selector.y *
						Case2_Color(Norm, EyeDir, DifCol, DifCol) +
					 gubo.selector.z *
						Case3_Color(Norm, EyeDir, vec3(1.0f,1.0f,1.0f), DifCol, 200.0f);
	
	outColor = vec4(CompColor, 1.0f);	
}