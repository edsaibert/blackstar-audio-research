#version 460 core

out vec4 FragColor;
// layout (binding = 1) uniform samplerBuffer controlPoints;

// in float fetchedValue;

void main() {
    FragColor = vec4(0.98, 0.72, 0.01, 1.0); // Grayscale output
}