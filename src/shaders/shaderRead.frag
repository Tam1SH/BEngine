#version 450
#extension GL_KHR_vulkan_glsl : enable
layout (set = 4, input_attachment_index = 0, binding = 0) uniform subpassInput inputColor;
layout (set = 4, input_attachment_index = 1, binding = 1) uniform subpassInput inputDepth;

layout(location = 0) out vec4 outColor;

void main() {
	outColor = vec4(subpassLoad(inputColor).rgb,1.f);
	outColor *= vec4(0.1);
	float depth = subpassLoad(inputDepth).r;
	outColor.rgb += vec3((depth - 1) * 1.0 / (1 - 1.1));
}