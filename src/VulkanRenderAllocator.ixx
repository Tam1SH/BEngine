module;

export module VulkanRenderAllocator;
import CRender;
import Render;
import VulkanRender;
import RenderAllocatorTypeRenderBuffer;
import Vertex;
import RenderBuffer;
import CRenderAllocator;
import <variant>;
import <concepts>;
import <vector>;


namespace BEbraEngine {

	export struct VulkanRenderAllocator {
		

		RenderBuffer* createIndexBuffer(std::vector<uint32_t> indices);

		RenderBuffer* createVertexBuffer(std::vector<Vertex> vertices);

		RenderBuffer* createUniformBuffer(uint32_t size);

		RenderBuffer* createStorageBuffer(uint32_t size);

		uint32_t alignmentBuffer(uint32_t originalSize, TypeRenderBuffer type);

		void destroyBuffer(RenderBuffer* buffer);

		VulkanRenderAllocator(VulkanRender& render);

		VulkanRenderAllocator() {};

		VulkanRenderAllocator(VulkanRenderAllocator&&) noexcept = default;

		VulkanRenderAllocator& operator=(VulkanRenderAllocator&&) noexcept = default;

		VulkanRenderAllocator(const VulkanRenderAllocator&) noexcept = delete;

		VulkanRenderAllocator& operator=(const VulkanRenderAllocator&) noexcept = delete;

	private:
		VulkanRender* render;
	};
	static_assert(CRenderAllocator<VulkanRenderAllocator>);

}