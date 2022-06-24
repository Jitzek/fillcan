#version 450

layout(location = 0) in vec3 inColor;
layout(location = 1) in vec2 inTexCoordinate;

layout(binding = 1) uniform sampler2D textureSamplers[2];

layout(location = 0) out vec4 outColor;

layout(push_constant) uniform PushConstant {
    mat4 transform;
    vec3 color;
    int textureIndex;
}
push_constant;

void main() {
    // outColor = vec4(inColor, 1.0);
    // outColor = vec4(inTexCoordinate, 0.0, 1.0);
    // outColor = texture(textureSampler, inTexCoordinate);
    outColor = texture(textureSamplers[push_constant.textureIndex], inTexCoordinate);
}