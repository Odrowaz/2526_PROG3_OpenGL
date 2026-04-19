#version 460 core

layout (location = 0) in vec3 vert_pos;
layout (location = 1) in vec2 vert_uv;
layout (location = 2) in vec3 vert_norm;

uniform mat4 mvp;
uniform mat4 model;
uniform vec3 camera_pos;
uniform vec3 light_pos;

out vec2 vert_uv_out;
out vec3 vert_world_norm_out;
out vec3 vert_world_pos_out;
out vec3 camera_pos_out;
out vec3 light_pos_out;

void main() 
{

    gl_Position = mvp * vec4(vert_pos, 1.0);

    vert_uv_out = vert_uv;

    vert_world_pos_out = vec3(model * vec4(vert_pos, 1.0));
    vert_world_norm_out = mat3(transpose(inverse(model))) * vert_norm;

    camera_pos_out = camera_pos;
    light_pos_out = light_pos;
}