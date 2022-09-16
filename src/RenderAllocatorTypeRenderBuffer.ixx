export module RenderAllocatorTypeRenderBuffer;

namespace BEbraEngine {
	export enum class TypeRenderBuffer {
		Storage,
		Uniform,
		StorageDynamic, //only vulkan
		UniformDynamic //only vulkan
	};
}