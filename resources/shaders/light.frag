varying vec2 vert_uv_out;

uniform sampler2D box_tex;

void main()
{
    // Ambient
    vec4 box_color = texture2D(box_tex, vert_uv_out);
    gl_FragColor = box_color;
}