#version 450 core

layout(location = 0) out
vec4 outColor;

uniform vec2 light_pos;
uniform sampler2D textures[32];

in DATA
{
vec4 position;
vec2 uv;
float tid;
vec4 color; // For text: text color | For image: tint color
}
fs_in;

void main()
{
    int textureID = int(fs_in.tid - 0.5);
    vec4 sampled = texture(textures[textureID], fs_in.uv);

    // TEXT PATH (GL_RED glyph texture)
    if (fs_in.color.a == 0.0)
    {
        float alpha = sampled.r; // glyph mask
        outColor = vec4(fs_in.color.rgb, alpha);
    }
    // IMAGE PATH (RGBA texture)
    else
    {
        outColor = sampled * fs_in.color;
    }
}
