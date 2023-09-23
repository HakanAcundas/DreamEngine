#version 450 core

layout(location = 0) out
vec4 color;

uniform vec2 light_pos;

in DATA
{
vec4 position;
vec2 uv;
float tid;
vec4 color;
}
fs_in;

uniform sampler2D textures[32];

void main()
{
    float intensity = 1.0 / length(fs_in.position.xy - light_pos);
    vec4 texColor = fs_in.color;
    if (fs_in.tid > 0.0)
    {
        int texID = int(fs_in.tid - 0.5);
        texColor = texture(textures[texID], fs_in.uv);
    }
    color = texColor * intensity;
    //if (texID == 1)
    //{
    //    color = vec4(texID, 0, 0, 1);
    //}
    //else if (texID == 2)
    //{
    //    color = vec4(0, 0, texID, 1);
    //}
}