#include <span>
#include <concepts>
export module CRenderAllocator;

import Vertex;
import RenderBuffer;
import RenderAllocatorTypeRenderBuffer;

namespace BEbraEngine {

	export template<typename T>
		concept CRenderAllocator = requires(

			/*RenderBuffer* createIndexBuffer*/ std::span<uint32_t> indices,

			/*RenderBuffer* createVertexBuffer*/ std::span<Vertex> vertices,

			/*RenderBuffer* createUniformBuffer*/ uint32_t size,

			/*RenderBuffer* alignmentBuffer*/ uint32_t originalSize, TypeRenderBuffer type,

			/*void destroyBuffer*/ RenderBuffer* buffer,

			/* this */
			T& self

			)
	{
		{ self.createIndexBuffer(indices) } -> std::same_as<RenderBuffer*>;
		{ self.createVertexBuffer(vertices) } -> std::same_as<RenderBuffer*>;
		{ self.createUniformBuffer(size) } -> std::same_as<RenderBuffer*>;
		{ self.createStorageBuffer(size) } -> std::same_as<RenderBuffer*>;
		{ self.alignmentBuffer(originalSize, type) } -> std::same_as<uint32_t>;
		{ self.destroyBuffer(buffer) } -> std::same_as<void>;
	};

}