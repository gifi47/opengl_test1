#version 420 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 vertexTexCoord;
layout(location = 3) in float vertexTextureId;
layout(location = 4) in mat4 instanceModelMatrix;

out VS_OUT{ 
	vec3 color;
	vec2 texCoord;
	float textureId;
} vs_out;

// Values that stay constant for the whole mesh.
uniform mat4 projView;

void main(){
	vec3 n_pos = vertexPosition_modelspace;
	gl_Position = projView * instanceModelMatrix * vec4(n_pos, 1);
	vs_out.color = vertexColor;
	vs_out.texCoord = vertexTexCoord;
	vs_out.textureId = vertexTextureId;
}