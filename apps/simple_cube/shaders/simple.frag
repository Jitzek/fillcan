#version 450

layout(location = 0) in vec3 inColor;

layout(location = 0) out vec4 outColor;

layout(push_constant) uniform PushConstant {
    mat4 transform;
    vec3 color;
}
push_constant;

void main() {
    outColor = vec4(inColor, 1.0);
}