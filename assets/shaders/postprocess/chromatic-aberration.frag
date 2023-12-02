#version 330

// Input: The texture holding the scene pixels
uniform sampler2D tex;

// Input: Read "assets/shaders/fullscreen.vert" to know what "tex_coord" holds;
in vec2 tex_coord;

// Output: The final color of the pixel
out vec4 frag_color;

// Constant: How far (in the texture space) is the distance (on the x-axis) between
// the pixels from which the red/green (or green/blue) channels are sampled
#define STRENGTH 0.005

// Chromatic aberration mimics some old cameras where the lens disperses light
// differently based on its wavelength. In this shader, we will implement a
// cheap version of that effect 

void main() {
    // Apply a simple chromatic aberration effect to simulate lens dispersion
    
    // Read the original color of the pixel at the given texture coordinate
    vec4 originalColor = texture(tex, tex_coord);

    // Extract individual color channels
    float greenChannel = originalColor.g;  // Green channel remains unchanged

    // To get the red channel, sample a pixel to the left
    float redChannel = texture(tex, vec2(tex_coord.x - STRENGTH, tex_coord.y)).r;

    // To get the blue channel, sample a pixel to the right
    float blueChannel = texture(tex, vec2(tex_coord.x + STRENGTH, tex_coord.y)).b;

    // Combine the color channels to form the final color with chromatic aberration
    vec4 finalColor = vec4(redChannel, greenChannel, blueChannel, originalColor.a);

    // Output the final color with chromatic aberration applied
    frag_color = finalColor;
}
