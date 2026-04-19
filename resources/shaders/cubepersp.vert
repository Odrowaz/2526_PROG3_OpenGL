#version 460 core

layout (location = 0) in vec3 vert_pos;
layout (location = 1) in vec2 vert_uv;

out vec2 vert_uv_out;

vec4 perspective(vec3 pos)
{
    float aspect_ratio = 800.f / 600.f;
    float vertical_fov = 45.f;
    float fov = tan(radians(vertical_fov * 0.5f));

    float near = 0.01f;
    float far = 100.f;
    float range = far - near;

    vec4 result;

    result.x = pos.x * (1/(aspect_ratio * fov));
    result.y = pos.y * (1/fov);

    //RHS -> LHS (NDC)
    result.z =  (pos.z * -((far + near) / range)) - ((2.f * far * near) / range);
    result.w = -pos.z;
    return result;
}

vec3 rotate_on_y(vec3 pos, float degrees)
{
    float rads = radians(degrees);
    vec3 result;
    result.x = cos(rads) * pos.x - sin(rads) * pos.z;
    result.y = pos.y;
    result.z = sin(rads) * pos.x + cos(rads) * pos.z;
    return result;
}

uniform float angle;

void main() 
{
    vec3 fixed_vert = vert_pos;
    fixed_vert = rotate_on_y(fixed_vert, angle);
    fixed_vert.z -= 4.f; //translate;
    gl_Position = perspective(fixed_vert);
    vert_uv_out = vert_uv;
}
