#version 450 core

layout(location = 0) out
vec4 outColor;

uniform vec2 u_light_pos;
uniform sampler2D u_textures[32];

in DATA
{
  vec4 position;
  vec2 uv;
  float tid;
  vec4 color;
} fs_in;

void main()
{
  int textureID = int(fs_in.tid - 0.5);
  vec4 sampled = texture(u_textures[textureID], fs_in.uv);

  if (fs_in.color.a == 0.0)
  {
    float alpha = sampled.r;
    outColor = vec4(fs_in.color.rgb, alpha);
  }
  else
  {
    outColor = sampled * fs_in.color;
  }
}