#version 450

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTextureCoordinate;

layout(location = 0) out vec3 outColor;
layout(location = 1) out vec2 outTextureCoordinate;

layout(push_constant) uniform PushConstant {
    mat4 transform;
    vec3 color;
}
push_constant;

layout(set = 1, binding = 0) uniform ViewProjection {
    mat4 view;
    mat4 projection;
}
vp;

void main() {
    gl_Position = vp.projection * vp.view * push_constant.transform * vec4(inPosition, 1.0);

    outColor = inColor;
    outTextureCoordinate = inTextureCoordinate;
}