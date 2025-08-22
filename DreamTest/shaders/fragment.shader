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
    float intensity = clamp(1.0 / length(fs_in.position.xy - light_pos), 0.1, 1.0);
    vec4 textureColor = fs_in.color;
    int textureID = int(fs_in.tid - 0.5);
        textureColor = texture(textures[textureID], fs_in.uv);

    if (fs_in.color.a == 0.0) // Use this condition to differentiate text and image
    {
        color = vec4(fs_in.color.rgb * textureColor.r, textureColor.r);
    }
    else
    {
        // Use full color for images
        color = textureColor * fs_in.color;
    };
}
