#version 420 core

// Input data
in VS_OUT {
	vec3 color;
	vec2 texCoord;
	float textureId;
} fs_in;

// Output data
out vec4 color;

// Textures
layout(binding=0) uniform sampler2D tex0;
layout(binding=1) uniform sampler2D tex1;
layout(binding=2) uniform sampler2D tex2;
layout(binding=3) uniform sampler2D tex3;

void main()
{
	vec4 color_tex;
	if (fs_in.textureId == 0) color_tex = texture(tex0, fs_in.texCoord);
	else if (fs_in.textureId == 1) color_tex = texture(tex1, fs_in.texCoord);
	else if (fs_in.textureId == 2) color_tex = texture(tex2, fs_in.texCoord);
	if (fs_in.textureId == 3) color_tex = texture(tex3, fs_in.texCoord);
	color = color_tex;
}