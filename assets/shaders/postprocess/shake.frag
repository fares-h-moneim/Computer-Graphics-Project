#version 330

uniform sampler2D tex;
uniform float u_time; // The current time
uniform float u_shakeIntensity; // The intensity of the shake

in vec2 tex_coord;
out vec4 frag_color;

void main() {
    // Calculate the position of the pixel in normalized device coordinates (NDC)
    vec2 ndcPosition = tex_coord * 2.0 - 1.0;
    
    // Compute the squared distance of the pixel from the center in NDC space for vignette
    float distanceSquared = dot(ndcPosition, ndcPosition);

    float shakeX = sin(u_time * 15.0) * u_shakeIntensity; // Shake on the X-axis
    float shakeY = cos(u_time * 17.0) * u_shakeIntensity; // Shake on the Y-axis
    vec2 shakeOffset = vec2(shakeX, shakeY);
    vec3 sceneColor = texture(tex, tex_coord + shakeOffset).rgb;
    frag_color = vec4(sceneColor, 1.0);
}
