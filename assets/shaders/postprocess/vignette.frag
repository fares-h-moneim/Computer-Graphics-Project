#version 330

// Input: The texture holding the scene pixels
uniform sampler2D tex;

// Input: Read "assets/shaders/fullscreen.vert" to know what "tex_coord" holds;
in vec2 tex_coord;

// Output: The final color of the pixel
out vec4 frag_color;

// Vignette is a postprocessing effect that darkens the corners of the screen
// to grab the attention of the viewer towards the center of the screen

void main() {
    // Apply a stylized vignette effect to enhance focus on the center of the screen
    
    // Calculate the position of the pixel in normalized device coordinates (NDC)
    // NDC space ranges from -1 to 1, while the texture coordinate space ranges from 0 to 1
    vec2 ndcPosition = tex_coord * 2.0 - 1.0;

    // Compute the squared distance of the pixel from the center in NDC space
    float distanceSquared = dot(ndcPosition, ndcPosition);

    // Apply vignette by dividing the scene color by 1 + the squared distance
    vec3 sceneColor = texture(tex, tex_coord).rgb;
    vec3 vignetteColor = sceneColor / (1.0 + distanceSquared);

    // Output the final color with vignette applied
    frag_color = vec4(vignetteColor, 1.0);
}
