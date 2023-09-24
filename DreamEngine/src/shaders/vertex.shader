#version 450 core

layout(location = 0) in
vec3 a_Position;
layout(location = 1) in
vec2 a_TexCoord;
layout(location = 2) in
float a_TexIndex;
layout(location = 3) in
vec4 a_Color;

uniform mat4 pr_matrix;
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);

out DATA
{
vec4 position;
vec2 uv;
float tid;
vec4 color;
}
vs_out;

void main()
{
    gl_Position = pr_matrix * vw_matrix * ml_matrix * vec4(a_Position, 1.0);
    vs_out.position = ml_matrix * vec4(a_Position, 1.0);
    vs_out.uv = a_TexCoord;
    vs_out.tid = a_TexIndex;
    vs_out.color = a_Color;
}
