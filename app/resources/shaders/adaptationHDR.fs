#version 430

#define GROUP_SIZE 1024

#define RGB_TO_LUM vec3(0.2126, 0.7152, 0.0722)

uniform sampler2D LDR_frame;
uniform float L_white;
uniform float dT;

in vec2 texCoord_interp;
layout(location = 0) out vec3 color;

layout(std430, binding = 2) buffer avgLum
{
    float L_current;
    float L_previous;
    float L_max;
};


void main()
{
    //uint counts = histogram[100]*9.6;

    // temporal smoothin of referenze Lum
    float alpha = 0.1*dT;

    float L_ref = alpha * L_current + (1 - alpha) * L_previous;
    L_previous = L_ref;

    vec3 HDR_Color = vec3(texture(LDR_frame, texCoord_interp)).xyz;

    float Lum = dot(RGB_TO_LUM, HDR_Color);
    float Lum_scaled = Lum/L_ref*0.2;
    float L_new =  Lum_scaled * (1.0 + Lum_scaled/L_max/L_max)/ (Lum_scaled + 1.0);
    

    color =  L_new/ Lum * HDR_Color;

    //color = HDR_Color;
    //color = LDR_Color;
    //color = color / (color + vec3(1.0));	// Reinhradt Tone Mapping
    //color = vec3(L_current*1.0, L_current*1.0, L_current*1.0);

    color = pow(color, vec3(1.0/2.2));	// gamma correction
    


}
