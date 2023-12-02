#version 330

// This vertex shader should be used to render a triangle whose normalized device coordinates are:
// (-0.5, -0.5, 0.0), ( 0.5, -0.5, 0.0), ( 0.0,  0.5, 0.0)
// And it also should send the vertex color as a varying to the fragment shader where the colors are (in order):
// (1.0, 0.0, 0.0), (0.0, 1.0, 0.0), (0.0, 0.0, 1.0)

// Declare an output structure to pass data to the fragment shader
out Varyings {
    vec3 color; // Varying variable representing the color of the vertex
} vs_out;

// Declare two uniforms for translation and scale
uniform vec2 translation = vec2(0.0, 0.0); // Default translation is (0.0, 0.0)
uniform vec2 scale = vec2(1.0, 1.0); // Default scale is (1.0, 1.0)

void main() {
    vec2 pos;
    // Determine the position and color based on the vertex index
    if (gl_VertexID == 0) {
        pos = vec2(-0.5, -0.5);
        vs_out.color = vec3(1.0, 0.0, 0.0); // Red
    } else if (gl_VertexID == 1) {
        pos = vec2(0.5, -0.5);
        vs_out.color = vec3(0.0, 1.0, 0.0); // Green
    } else {
        pos = vec2(0.0, 0.5);
        vs_out.color = vec3(0.0, 0.0, 1.0); // Blue
    }
    
    // Calculate the final position by applying scale and translation
    gl_Position = vec4(scale * pos + translation, 0.0, 1.0);
}
