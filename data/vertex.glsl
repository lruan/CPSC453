#version 410 core

layout (location = 0) in vec3 modelPosition;
layout (location = 1) in vec2 modelUV;
layout (location = 2) in vec3 modelNormal;

out vec3 normal;
out vec3 fragment;
out vec2 uv;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main() {
    fragment = vec3(M * vec4(modelPosition, 1.0f));
    normal = mat3(transpose(inverse(M))) * modelNormal;
   
    gl_Position = P * V * vec4(fragment, 1.0f);
   
    uv = modelUV;
}