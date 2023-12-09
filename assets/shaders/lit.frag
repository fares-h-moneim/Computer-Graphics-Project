#version 330 core

in Varyings {
    vec4 color;
    vec2 tex_coord;
    vec3 normal; //normalized btw
    vec3 Frag_position;
} fs_in;

out vec4 frag_color;

uniform vec4 tint;
uniform sampler2D tex;
//lighting
uniform vec3 light_pos;
uniform vec3 light_color;
uniform vec3 view_pos; //camera position
//more to be added later for more textures maps for stuff like albedo
//need to be modified for multiple lights


void main(){
    vec3 initial_color = vec3(tint * fs_in.color * texture(tex, fs_in.tex_coord)); //frag_color should have lights applied on it
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * light_color;
    // diffuse
    vec3 lightDir = normalize(light_pos - fs_in.Frag_position);
    float diff = max(dot(fs_in.normal, lightDir), 0.0);
    vec3 diffuse = diff * light_color;
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(view_pos - fs_in.Frag_position);
    vec3 reflectDir = reflect(-lightDir, fs_in.normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * light_color;
    // combine results
    vec3 result = (ambient + diffuse + specular) * initial_color;
    frag_color = vec4(result, 1.0);
}