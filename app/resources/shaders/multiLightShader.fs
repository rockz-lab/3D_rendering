// this header is defined in the MULILIGHT class, depending on the lighting setup
//#version 330
//#define DIR_LIGHTS 1
//#define POINT_LIGHTS 2

in vec3 N;
in vec3 pos_interp;

//out vec4 fragColor;
layout(location = 0) out vec3 fragColor;

uniform vec3 lightDir[DIR_LIGHTS];
uniform vec3 lightSource[POINT_LIGHTS];
uniform vec3 lightColor[DIR_LIGHTS + POINT_LIGHTS];
uniform float attenuation;

uniform vec3 cameraPos;
uniform vec4 objColor;
uniform vec3 lightCoeffs;
uniform int nPhong;


float fallof(float dist, float a)
{
    return 1.0f/(1.0 + a*dist*dist);
}

void main()
{
    float amb = lightCoeffs[0];
    float diff = lightCoeffs[1];
    float spec = lightCoeffs[2];

    vec3 V = normalize(pos_interp - cameraPos);     // V is independent of Light



    // calculate directional lights
    vec3 diffuseDir;
    vec3 specularDir;
    vec3 diffContrib = vec3(0.0, 0.0, 0.0);
    vec3 specContrib = vec3(0.0, 0.0, 0.0);
    vec3 L;
    vec3 R;


    for (int i = 0; i < DIR_LIGHTS; i++)
    {
        L = normalize(lightDir[i]);
        diffuseDir = clamp(-dot(L, N), 0.0, 1.0) * lightColor[i];
        R = 2*dot(L, N)*N - L;       // R changes for directional light, V is the same
        specularDir = pow(clamp(dot(R,V), 0.0, 1.0), nPhong) * lightColor[i];
        diffContrib += diffuseDir;
        specContrib += specularDir;
    }
    vec3 result = diffContrib*diff + specContrib*spec;
    // calculate point lights
    vec3 sourceModel;   // vector form light source to model surface
    vec3 diffusePoint;
    vec3 specularPoint;
    vec3 singleColor;
    float dist;

    diffContrib = vec3(0.0, 0.0, 0.0);
    specContrib = vec3(0.0, 0.0, 0.0);
    for (int i = 0; i < POINT_LIGHTS; i++)
    {
        singleColor = lightColor[i+DIR_LIGHTS];
        sourceModel = pos_interp - lightSource[i];        // vector from surface point to light source
        dist = length(sourceModel);
        L = sourceModel/dist;
        R = 2*dot(L, N)*N - L;       // R changes for directional light, V is the same
        diffusePoint =  clamp(-dot(L, N), 0.0, 1.0) * singleColor;
        specularPoint = pow(clamp(dot(R,V), 0.0, 1.0), nPhong) * singleColor;
        diffContrib += diffusePoint*fallof(dist, attenuation);
        specContrib += specularPoint*fallof(dist, attenuation);;
    }

    result += vec3(amb) + diffContrib*diff + specContrib*spec;


    //gl_FragColor = vec4(lightSource[0], 1);
    fragColor = vec3(objColor * vec4(result, 1));
}
