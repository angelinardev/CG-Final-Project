#version 430

layout(location = 0) in vec2 inUV;

layout(location = 0) out vec4 outColor;

uniform layout(binding = 0) sampler2D s_Image;
//uniform layout(binding = 1) sampler3D s_Lut;

//uniform float u_Strength;
uniform vec2 u_ScreenSize;
uniform vec2 u_mousePosition;

float getScale()
{
	return 0.5 * (u_mousePosition.x + 1) / u_ScreenSize.x;
}

vec2 pixelateUV(vec2 uv, float scale)
{
	return floor(uv / scale) * scale;
}


void main()
{
    float scale = getScale();

	vec2 uv = pixelateUV(inUV - 0.5, scale);

	outColor = texture(s_Image, uv);
}
