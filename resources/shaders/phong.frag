varying vec2 vert_uv_out;
varying vec3 vert_world_norm_out;
varying vec3 vert_world_pos_out;
varying vec3 camera_pos_out;
varying vec3 light_pos_out;

uniform sampler2D trup_tex;

void main()
{
    vec3 normal = normalize(vert_world_norm_out);

    // Ambient
    vec4 trup_color = texture2D(trup_tex, vert_uv_out);
    float ambient_intensity = 0.1;
    vec4 ambient = ambient_intensity * trup_color;

    // Diffuse
    vec3 dir_to_light = normalize(light_pos_out - vert_world_pos_out);
    float cosLN = dot(dir_to_light, normal);
    float lambert = clamp(cosLN, 0.0, 1.0);
    vec4 diffuse = lambert * trup_color;

    // Specular
    vec3 dir_to_eye = normalize(camera_pos_out - vert_world_pos_out);

    vec3 dir_light_to_point = -dir_to_light;
    vec3 light_refl = reflect(dir_light_to_point, normal);

    float cosER = dot(dir_to_eye, light_refl);
    float specular_value = clamp(cosER, 0.0, 1.0);

    vec4 specular_tint = vec4(1.0, 1.0, 1.0, 1.0);
    vec4 specular = specular_tint * pow(specular_value, 50.0);

    gl_FragColor = ambient + diffuse + specular;
}