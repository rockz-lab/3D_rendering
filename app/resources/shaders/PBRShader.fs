//version 330

// PBR based on this tutorial:
// https://learnopengl.com/PBR/Theory

#define PI 3.1415926538

in vec3 N;
in vec3 pos_interp;

layout(location = 0) out vec3 fragColor;

uniform vec3 cameraPos;

uniform vec3 lightDir[DIR_LIGHTS];
uniform vec3 lightSource[POINT_LIGHTS];
uniform vec3 lightColor[DIR_LIGHTS + POINT_LIGHTS];


uniform float roughness;
uniform float metalness;
uniform vec3 surfaceColor;



vec3 Fresnel(vec3 h, vec3 v, vec3 F0)
{	// Schlick Fresnel approximation
        float HdotV = max(dot(h, v), 0.0);
        return F0 + (1.0 - F0) * pow(1.0 - HdotV, 5.0);
}

float NDF(vec3 n, vec3 h, float alpha)
{	// Trowbridge-Reitz GGX
	float a2 = alpha*alpha;
        float NdotH = max(dot(n, h), 0.0);

	float num = a2;
        float denom = NdotH*NdotH * (a2 - 1.0) + 1.0;
	denom = PI * denom * denom;
	return num / denom;
}

float GSchlick(vec3 n, vec3 x, float k)
{
	float NdotX = max(dot(n, x), 0.0);			// needs max

	return NdotX/(NdotX * (1.0 - k) + k);
}

float Geometry(vec3 n, vec3 v, vec3 l, float k)
{
	return GSchlick(n, v, k) * GSchlick(n, l, k);
}

float Luminance(vec3 c)
{
	return 0.2126 * c.x + 0.7152 * c.y + 0.0722 * c.z;
}

void main()
{
	
	vec3 N = normalize(N);
	vec3 surfaceColor = pow(surfaceColor, vec3(2.2));

	// k for the direct case
	float k = (roughness + 1.0) * (roughness + 1.0) / 8.0;

	vec3 F0 = vec3(0.04);		// F0 for non-metallic / Dielectric
	F0 = mix(F0, surfaceColor, metalness);
	
        vec3 V = normalize(cameraPos - pos_interp);     // View vector (is independent of Light)

	// do all directional lights

	vec3 L0 = vec3(0.0);
	for (int i = 0; i < DIR_LIGHTS; i++)
	{
		vec3 L = -normalize(lightDir[i]);
		vec3 H = normalize(L + V);
		
		// radiance
		vec3 radiance = lightColor[i];

		float D = NDF(N, H, roughness*roughness); 
                vec3 F = Fresnel(H, V, F0);
		float G = Geometry(N, V, L, k);
		// reflectance equation
                vec3 numerator = D*F*G;
		float denomiator = 4.0* max(dot(V, N), 0.0) * max(dot(L, N), 0.0);		// prevent division by zero
                vec3 specular = numerator/max(denomiator, 0.0001);

		vec3 kS = F;
		vec3 kD = vec3(1.0) - kS;
		kD *= 1.0 - metalness;

		float cosTheta = max(dot(N, L), 0.0);
		L0 += (kD * surfaceColor /PI + specular) * radiance * cosTheta;
	}

	// do all point lights




	for (int j = 1; j < POINT_LIGHTS + DIR_LIGHTS; j++)
	{
                vec3 L = normalize(lightSource[j-DIR_LIGHTS] - pos_interp);
                vec3 H = normalize(L + V);
		
		// radiance
		float dist = length(pos_interp - lightSource[j-DIR_LIGHTS]);
		float attenuation = 1.0 / dist / dist;
		//float attenuation = 1.0;
		vec3 radiance = lightColor[j] * attenuation;


                float D = NDF(N, H, roughness*roughness);
		vec3 F = Fresnel(H, V, F0);
		float G = Geometry(N, V, L, k);
		// reflectance equation
		vec3 numerator = D*F*G;
		float denomiator = 4.0* max(dot(V, N), 0.0) * max(dot(L, N), 0.0);		// precent division by zero
                vec3 specular = numerator/max(denomiator, 0.001);
		vec3 kS = F;
		vec3 kD = vec3(1.0) - kS;
		kD *= 1.0 - metalness;

		float cosTheta = max(dot(N, L), 0.0);
		L0 += (kD * surfaceColor /PI + specular) * radiance * cosTheta;
	}

	//debug shading
//	vec3 L = normalize(lightSource[0] - pos_interp);
//	float cosTheta = max(dot(N, L), 0.0);
//	L0 = surfaceColor * cosTheta;

	// ambient term
	vec3 ambient = 0.03 * surfaceColor; // ( * aO )

	fragColor = L0 + ambient;

	// HDR / gamma correction
	//fragColor = vec3(1.0) - exp(-surfaceColor * 2.0);//
    //float L_old = Luminance(fragColor);
	//float numerator = L_old * (1.0f + (L_old / (100 * 100)));
    //float L_new = numerator / (1.0f + L_old);

    //fragColor *= L_old / L_new;
     //fragColor = vec3(1.0) - exp(-fragColor*exposure);
    //fragColor = fragColor / (fragColor + vec3(1.0));	// Reinhradt Tone Mapping

    //fragColor = pow(fragColor, vec3(1.0/2.2));	// gamma correction




	
}
