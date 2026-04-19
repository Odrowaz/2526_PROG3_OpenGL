#version 460 core

in vec2 vert_uv_out;
in vec3 vert_world_norm_out;
in vec3 vert_world_pos_out;
in vec3 camera_pos_out;
in vec3 light_pos_out;

layout (binding = 0) uniform sampler2D trup_tex;
layout (binding = 1) uniform sampler2D box_tex;

out vec4 frag_color;

void main() 
{

    //Ambient
    vec4 trup_color = texture(box_tex, vert_uv_out);
    frag_color = trup_color;
    
}