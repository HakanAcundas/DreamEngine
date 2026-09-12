#version 450 core

layout(location = 0) in vec2 shaderPosition;
layout(location = 1) in vec2 shaderTexCoord;
layout(location = 2) in float shaderTextureID;
layout(location = 3) in vec4 shaderColor;

uniform mat4 u_view_projection;

out DATA
{
  vec4 position;
  vec2 uv;
  flat float tid;
  vec4 color;
} vs_out;

void main()
{
  gl_Position = u_view_projection * vec4(shaderPosition, 0.0, 1.0);
  vs_out.position = vec4(shaderPosition, 0.0, 1.0);
  vs_out.uv = shaderTexCoord;
  vs_out.tid = shaderTextureID;
  vs_out.color = shaderColor;
}