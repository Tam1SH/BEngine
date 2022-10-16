export module RenderAllocatorTypeRenderBuffer;

namespace BEbraEngine {
	export enum struct TypeRenderBuffer {
		Storage,
		Uniform,
		StorageDynamic, //only vulkan
		UniformDynamic //only vulkan
	};
}