//#extension GL_KHR_vulkan_glsl : enable
#version 450

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
    vec3 lightPos;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec2 inUV;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragUV;

//const vec3 DIRECTION_TO_LIGHT = normalize(vec3(-5.0,3.0,2.0));
const float AMBIENT = 0.02;

void main() {
   gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);

   vec3 normalWorldSpace = normalize(mat3(ubo.model) * inNormal );//normalize((ubo.model *vec4(inNormal,0.0)).xyz);

   float lightIntensity = max(dot(normalWorldSpace,ubo.lightPos), 0);

   fragColor = AMBIENT + (lightIntensity * inColor);
   fragUV = inUV;
}