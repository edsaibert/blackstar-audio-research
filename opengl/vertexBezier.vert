#version 460 core

/*
    Shader for rendering a bezier curve
*/

layout(location = 0) in vec2 aPos;
layout (binding = 1) uniform samplerBuffer controlPoints;
out float fetchedValue;

void main() {
    gl_Position = vec4(aPos, 0.0, 1.0);
}