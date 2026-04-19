#version 460 core

layout (location = 0) in vec3 vert_pos;
layout (location = 1) in vec2 vert_uv;

uniform float time;

uniform mat4 mvp;
uniform mat4 model;
out vec2 vert_uv_out;
out float time_out;

void main() 
{
    gl_Position = mvp * model * vec4(vert_pos, 1.f);
    vert_uv_out = vert_uv;
    time_out = time;

    // vert_uv_out.y = 1.f - vert_uv_out.y;
}
