#version 450 core

layout(location = 0) out
vec4 outColor;

uniform sampler2D u_textures[32];

in DATA
{
  vec4 position;
  vec2 uv;
  flat float tid;
  vec4 color;
} fs_in;

vec4 sampleSlot(int id, vec2 uv)
{
  switch (id)
  {
    case 0: return texture(u_textures[0], uv);
    case 1: return texture(u_textures[1], uv);
    case 2: return texture(u_textures[2], uv);
    case 3: return texture(u_textures[3], uv);
    case 4: return texture(u_textures[4], uv);
    case 5: return texture(u_textures[5], uv);
    case 6: return texture(u_textures[6], uv);
    case 7: return texture(u_textures[7], uv);
    case 8: return texture(u_textures[8], uv);
    case 9: return texture(u_textures[9], uv);
    case 10: return texture(u_textures[10], uv);
    case 11: return texture(u_textures[11], uv);
    case 12: return texture(u_textures[12], uv);
    case 13: return texture(u_textures[13], uv);
    case 14: return texture(u_textures[14], uv);
    case 15: return texture(u_textures[15], uv);
    case 16: return texture(u_textures[16], uv);
    case 17: return texture(u_textures[17], uv);
    case 18: return texture(u_textures[18], uv);
    case 19: return texture(u_textures[19], uv);
    case 20: return texture(u_textures[20], uv);
    case 21: return texture(u_textures[21], uv);
    case 22: return texture(u_textures[22], uv);
    case 23: return texture(u_textures[23], uv);
    case 24: return texture(u_textures[24], uv);
    case 25: return texture(u_textures[25], uv);
    case 26: return texture(u_textures[26], uv);
    case 27: return texture(u_textures[27], uv);
    case 28: return texture(u_textures[28], uv);
    case 29: return texture(u_textures[29], uv);
    case 30: return texture(u_textures[30], uv);
    case 31: return texture(u_textures[31], uv);
  }
  
  return vec4(1.0, 0.0, 1.0, 1.0);
}

void main()
{
  if (fs_in.tid == 0.0)
  {
    outColor = fs_in.color;
  }
  else
  {
    int textureID = int(fs_in.tid - 0.5);
    vec4 sampled = sampleSlot(textureID, fs_in.uv);
    
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
}