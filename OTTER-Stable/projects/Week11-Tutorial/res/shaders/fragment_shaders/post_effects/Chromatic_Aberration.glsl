#version 430
#include "../../fragments/frame_uniforms.glsl"

layout(location = 0) in vec2 inUV;
layout(location = 0) out vec4 outColor;

uniform layout(binding = 0) sampler2D s_Image;

uniform float u_Strength;

void main() {
    
    float rValue = texture(s_Image, inUV - u_Strength*0.00019).r;  
    float gValue = texture(s_Image, inUV - u_Strength*0.00006).g;
    float bValue = texture(s_Image, inUV - u_Strength*-0.00026).b;  

    // Combine the offset colors.
    outColor = vec4(rValue, gValue, bValue, 1.0);
}