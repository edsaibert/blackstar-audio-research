#version 460 core

/*
    Shader for rendering a bezier curve
*/

layout(location = 0) in vec2 aPos;
layout (binding = 1) uniform samplerBuffer controlPoints;
out float fetchedValue;

// vec3 bezierFunction(float x1, float x2, float y1, float y2){
//     float t = 0.5;
//     float x = (1 - t) * ((1 - t) * x1 + t * x2) + t * ((1 - t) * x2 + t * x2);
//     float y = (1 - t) * ((1 - t) * y1 + t * y2) + t * ((1 - t) * y2 + t * y2);
//     return vec3(x, y, aPos.z);
// }


void main() {
    // int index = gl_VertexID; // Compute the index for the current vertex
    // float x1 = texelFetch(controlPoints, index * 2).r;       // Fetch X coordinate
    // float y1 = texelFetch(controlPoints, index * 2 + 1).r;   // Fetch Y coordinate

    // float x2 = texelFetch(controlPoints, (index + 1) * 2).r;   // Fetch X coordinate
    // float y2 = texelFetch(controlPoints, (index + 1) * 2 + 1).r;   // Fetch Y coordinate

    // fetchedValue = xValue; // Output one of the fetched values for testing

    // // Modify the position using the fetched control points
    // vec3 modifiedPosition = vec3(xValue, yValue, aPos.z);
    // gl_Position = vec4(bezierFunction(x1, x2, y1, y2), 1.0);
    gl_Position = vec4(aPos, 0.0, 1.0);
}