#version 330 core

// Output variable for the fragment color
out vec4 frag_color;

// In this shader, we want to draw a checkboard where the size of each tile is (size x size).
// The color of the top-left most tile should be "colors[0]" and the 2 tiles adjacent to it
// should have the color "colors[1]".

// TODO: (Req 1) Finish this shader.

// Uniforms for the checkerboard size and colors
uniform int size = 32;
uniform vec3 colors[2];

void main() {
    // Calculate the position of the fragment in terms of tiles
    ivec2 position = ivec2(gl_FragCoord.xy) / size; // Divide by size to get the position as a multiple of size

    // Determine the color based on the position using the modulo operator
    // This creates an alternating pattern of colors for adjacent tiles
    vec3 color = colors[(position.x + position.y) % 2];

    // Set the fragment color with alpha set to 1.0
    frag_color = vec4(color, 1.0);
}
