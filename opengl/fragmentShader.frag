#version 460 core

out vec4 FragColor;
// layout (binding = 1) uniform samplerBuffer controlPoints;

// in float fetchedValue;

void main() {
    FragColor = vec4(1.0, 0.0, 0.0, 1.0); // Grayscale output
}