#version 330 core

// input vertex, UV coordinates and normal
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexNormal_modelspace;
layout(location = 2) in vec2 vertexUV;

// Output data ; will be interpolated for each fragment.
out vec3 vertex_position_worldspace;
out vec3 vertex_position_cameraspace;
out vec3 vertex_normal_cameraspace;
out vec2 vertex_UV;

// Values that stay constant for the whole mesh.
uniform mat4 V;
uniform mat4 M;
uniform mat4 P;

void main() {
    // vertex position
    gl_Position =  P * V * M * vec4(vertexPosition_modelspace, 1);
    gl_PointSize = 10;

    // FS
    vertex_position_worldspace = (M * vec4(vertexPosition_modelspace, 1)).xyz;
    vertex_position_cameraspace = (V * M * vec4(vertexPosition_modelspace, 1)).xyz;
    vertex_normal_cameraspace = (V * M * vec4(vertexNormal_modelspace, 0)).xyz;
    vertex_UV = vertexUV;
}
