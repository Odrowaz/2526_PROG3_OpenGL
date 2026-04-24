attribute vec3 vert_pos;
attribute vec2 vert_uv;
attribute vec3 vert_norm;

uniform mat4 mvp;

varying vec2 vert_uv_out;

void main()
{
    gl_Position = mvp * vec4(vert_pos, 1.0);
    vert_uv_out = vert_uv;
}