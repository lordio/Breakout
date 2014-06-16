#version 130

/*layout(location = 0)*/ in vec4 in_vertex;
/*layout(location = 1)*/ in vec4 in_color;

out vec4 vs_out_color;

uniform vec2 pos;

void main()
{
	gl_Position = in_vertex + vec4(pos, 0.0, 0.0);
	vs_out_color = in_color;
}