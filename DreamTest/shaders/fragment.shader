#version 450 core

layout(location = 0) out vec4 color;

uniform vec2 light_pos;

in DATA
{
    vec4 position;
    vec2 uv;
    float tid;
    vec4 color;
} fs_in;

uniform sampler2D textures[32];

void main()
{
    float intensity = 1.0 / length(fs_in.position.xy - light_pos);
    vec4 textureColor = fs_in.color;
    if (fs_in.tid > 0.0)
    {
        int textureID = int(fs_in.tid - 0.5);
        textureColor = texture(textures[textureID], fs_in.uv);
    }
    color = textureColor * intensity;
}
