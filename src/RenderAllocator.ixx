export module RenderAllocator;
import RenderBuffer;
import Vertex;
import RenderAllocatorTypeRenderBuffer;
import <vector>;

namespace BEbraEngine {

	export struct RenderAllocator {

		virtual RenderBuffer* createIndexBuffer(const std::vector<uint32_t>& indices) = 0;

		virtual RenderBuffer* createVertexBuffer(const std::vector<Vertex>& vertices) = 0;

		virtual RenderBuffer* createUniformBuffer(uint32_t size) = 0;

		virtual RenderBuffer* createStorageBuffer(uint32_t size) = 0;

		virtual uint32_t alignmentBuffer(uint32_t originalSize, TypeRenderBuffer type) = 0;

		virtual void destroyBuffer(RenderBuffer* buffer) = 0;
	};
}
