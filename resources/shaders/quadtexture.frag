#version 460 core

in vec2 vert_uv_out;
in float time_out;

//uniform sampler2D smile_tex;
// layout (binding = 0) uniform sampler2D smile_tex;
// layout (binding = 1) uniform sampler2D box_tex;
layout (binding = 2) uniform sampler2D random_tex;

out vec4 frag_color;

void main() 
{

    // float noise = texture(random_tex, vert_uv_out + vec2(0, time_out)).r;
    // frag_color = vec4(vec3(noise), 1.0);

    vec2 offset = vec2(
        sin(time_out * 1.23) * 123.456,
        sin(time_out * 4.56) * 123.456
    );

    float noise = texture(random_tex, vert_uv_out + offset).r;

    frag_color = vec4(vec3(noise), 1.0);
}