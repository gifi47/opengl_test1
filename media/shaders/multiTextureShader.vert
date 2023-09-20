#version 420 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 vertexTexCoord;
layout(location = 3) in float vertexTextureId;

out VS_OUT{ 
	vec3 pos;
	vec2 texCoord;
	float textureId;
	float modifire;
} vs_out;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform float modifire;

void main(){
	vec3 n_pos = vertexPosition_modelspace;
	gl_Position = MVP * vec4(n_pos, 1);
	vs_out.pos = vertexColor;
	vs_out.texCoord = vertexTexCoord;
	vs_out.textureId = vertexTextureId;
	vs_out.modifire = modifire;
}