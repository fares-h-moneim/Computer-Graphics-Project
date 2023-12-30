#version 330 core

in Varyings {
    vec4 color;
    vec2 tex_coord;
    vec3 normal; //normalized btw
    vec3 Frag_position;
} fs_in;
//set at material creation
struct Material {
    sampler2D diffuse; //TODO: taba3 el todo el t7t we will use these instead of constant numbers (i dont know if only diffuse and specular are needed)
    sampler2D specular;
    sampler2D ambient;
    float shininess;
}; 
struct Light {
    // 0 = directional, 1 = point, 2 = spot
    int type;
    // for point and spot lights
    vec3 position;
    // for directional and spot lights
    vec3 direction;
    // for point and spot lights
    float constant;
    float linear;
    float quadratic;
	//
    vec3 color;
    // for spot lights
    float cutOff;
    float outerCutOff;
};
// end of code 
out vec4 frag_color;
uniform vec4 tint; //color tint
uniform sampler2D tex; //texture to sample from
//lighting

uniform vec3 view_pos; //camera position
uniform Light lights[10]; //max of 10 lights increase if needed
uniform int number_of_lights;
uniform Material material;
//strengths
vec3 ambientStrength = vec3(0.1); //temporary till we have an ambient map
vec3 specularStrength = vec3(0.5); //temporary till we have a specular map
vec3 diffuseStrength = vec3(0.5); //temporary till we have a diffuse map
//add other maps
//uniform int number_of_point_lights;
vec3 CalcSpotLight(Light light)
{
    vec3 lightDir = normalize(light.position - fs_in.Frag_position);
    // diffuse shading
    float diff = max(dot(fs_in.normal, lightDir), 0.0);
    // specular shading
    vec3 viewDir = normalize(view_pos - fs_in.Frag_position);
    vec3 reflectDir = reflect(-lightDir, fs_in.normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); //shineniss of material instead of 32
    // attenuation
    float distance = length(light.position - fs_in.Frag_position);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));   
    // spotlight intensity
   float theta = dot(lightDir, normalize(-light.direction)); 
   float epsilon = light.cutOff - light.outerCutOff;
   float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.color * ambientStrength;
    vec3 diffuse = light.color * diff * diffuseStrength;
    vec3 specular = light.color * spec * specularStrength;
    ambient *= attenuation* intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation* intensity;
    return (ambient + diffuse + specular);
}
vec3 CalcPointLight(Light light)
{
    // ambient
    vec3 ambient = ambientStrength * light.color;
    // diffuse 
    vec3 lightDir = normalize(light.position - fs_in.Frag_position);
    float diff = max(dot(fs_in.normal, lightDir), 0.0);
    vec3 diffuse = diffuseStrength*diff * light.color;
    // specular
    vec3 viewDir = normalize(view_pos - fs_in.Frag_position);
    vec3 reflectDir = reflect(-lightDir, fs_in.normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = specularStrength * spec * light.color;  
    // attenuation
    float distance = length(light.position - fs_in.Frag_position);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}
vec3 CalcDirLight(Light light)
{
    // ambient
    vec3 ambient = ambientStrength * light.color;
    // diffuse 
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(fs_in.normal, lightDir), 0.0);
    vec3 diffuse = diffuseStrength*diff * light.color;
    // specular
    vec3 viewDir = normalize(view_pos - fs_in.Frag_position);
    vec3 reflectDir = reflect(-lightDir, fs_in.normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = specularStrength * spec * light.color;  
    // combine results
    return (ambient + diffuse + specular);
}

//
//
void main(){
    vec3 result = vec3(0.0);
    vec3 mycolor= vec3(texture(tex,fs_in.tex_coord));
    ambientStrength = vec3(texture(material.ambient, fs_in.tex_coord));
    diffuseStrength = vec3(texture(material.diffuse, fs_in.tex_coord));
    specularStrength = vec3(texture(material.specular, fs_in.tex_coord));
    for(int i = 0; i < number_of_lights; i++)
    {
       if(lights[i].type == 1)
        result+= CalcPointLight(lights[i]);
        //TODO: add other types of lights
        if(lights[i].type==2)
        {
            result+= CalcSpotLight(lights[i]);
        }
        if(lights[i].type==0)
        {
            result+= CalcDirLight(lights[i]);
        }

    }   
    
    frag_color = vec4(result*mycolor,1.0);
    //thats for debugging
}
//TODO: CHANGE spec&ambience&diffusion  to CORROSPONDING MAP of material
