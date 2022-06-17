#version 450 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;

layout(location = 0) out vec3 outColor;

layout(push_constant) uniform PushConstant {
    int test;
    mat4 transform;
    vec3 color;
}
push_constant;

void main() {
    // gl_Position = vec4(inPosition, 1.0);
    gl_Position = push_constant.test * vec4(inPosition, 1.0);
    outColor = inColor;
}