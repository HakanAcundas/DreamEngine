#version 450 core

layout(location = 0) in vec3 shader_Position;
layout(location = 1) in vec2 shader_TexCoord;
layout(location = 2) in float shader_TextureID;
layout(location = 3) in vec4 shader_Color;

uniform mat4 pr_matrix;
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);

out DATA
{
vec4 position;
vec2 uv;
float tid;
vec4 color;
} vs_out;

void main()
{
    gl_Position = pr_matrix * vw_matrix * ml_matrix * vec4(shader_Position, 1.0);
    vs_out.position = ml_matrix * vec4(shader_Position, 1.0);
    vs_out.uv = shader_TexCoord;
    vs_out.tid = shader_TextureID;
    vs_out.color = shader_Color;
}
