#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 tex_coord;
layout(location = 3) in vec3 anormal;

out Varyings {
    vec4 color;
    vec2 tex_coord;
    vec3 normal;
    vec3 Frag_position;
} vs_out;

uniform mat4 transform;
uniform mat4 model;

void main(){
    mat4 modelInvTranspose = transpose(inverse(model));
    vs_out.normal = normalize(mat3(modelInvTranspose) * anormal);
    vs_out.Frag_position = vec3(model * vec4(position, 1.0));
    gl_Position = transform * vec4(position, 1.0);
    vs_out.color = color;
    vs_out.tex_coord = tex_coord;
}