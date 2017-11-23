#version 410 core

layout (location = 0) in vec4 modelPosition;
layout (location = 1) in vec3 modelNormal;
layout (location = 2) in vec3 modelTexture;

out vec3 normal;
out vec3 fragment;
out vec2 texture;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main() {
    gl_Position = P * V * M * modelPosition;
    normal = mat3(transpose(inverse(M))) * modelNormal;
    fragment = vec3(M * modelPosition);
    texture = modelTexture;
}