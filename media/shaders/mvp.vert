#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 vertexTexCoord;

out vec3 pos;
out vec2 texCoord;
//out vec3 cl;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
//uniform vec3 c;

void main(){

	// Output position of the vertex, in clip space : MVP * position
	//vertexPosition_modelspace.y += (c / 100.0);
	vec3 n_pos = vertexPosition_modelspace;
	/*vec3 n_c = c;
	if (c.x * 1.5 - 0.2 > n_pos.x){
		n_pos.y += c.y;
		n_c.x = (1 - c.x); 
	}
	if (c.z * 1.5 - 0.2 > n_pos.x){
		n_pos.y += c.y;
		n_c.z = (1 - c.z); 
	}*/
	gl_Position =  MVP * vec4(n_pos,1);
	//pos = vertexPosition_modelspace;
	pos = vertexColor;
	texCoord = vertexTexCoord;
	//cl = n_c;
}

