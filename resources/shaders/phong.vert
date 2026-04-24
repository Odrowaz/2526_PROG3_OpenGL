#version 100

precision mediump float;

attribute vec3 vert_pos;
attribute vec2 vert_uv;
attribute vec3 vert_norm;

uniform mat4 mvp;
uniform mat4 model;
uniform vec3 camera_pos;
uniform vec3 light_pos;
uniform mat4 normal_matrix;

varying vec2 vert_uv_out;
varying vec3 vert_world_norm_out;
varying vec3 vert_world_pos_out;
varying vec3 camera_pos_out;
varying vec3 light_pos_out;

void main()
{
    gl_Position = mvp * vec4(vert_pos, 1.0);

    vert_uv_out = vert_uv;

    vert_world_pos_out = vec3(model * vec4(vert_pos, 1.0));

    //mat3 normal_matrix = mat3(model);
    vert_world_norm_out = mat3(normal_matrix) * vert_norm;

    camera_pos_out = camera_pos;
    light_pos_out = light_pos;
}