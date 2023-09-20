#version 330 core

in vec3 pos; 
in vec2 texCoord;
//in vec3 cl;

// Output data
out vec4 color;

uniform sampler2D tex;

void main()
{

	// Output color = red
	//vec3 g = normalize(pos);
	//color = vec3(cl.x, cl.y, cl.z);
	//color = vec3(pos.x, pos.y, pos.z);
	vec4 color_tex = texture(tex, texCoord);
	if (color_tex.a < 0.1) discard;
	color = color_tex;
}
