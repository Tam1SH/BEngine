module;
export module VulkanRenderAllocator;
import RenderAllocatorTypeRenderBuffer;
import Vertex;
import RenderBuffer;
import RenderAllocator;
import <variant>;
import <concepts>;
import <vector>;

namespace BEbraEngine {
	export struct VulkanRender;
}

namespace BEbraEngine {
	
	export struct VulkanRenderAllocator : public RenderAllocator {
		
		RenderBuffer* createIndexBuffer(const std::vector<uint32_t>& indices) override;

		RenderBuffer* createVertexBuffer(const std::vector<Vertex>& vertices) override;

		RenderBuffer* createUniformBuffer(uint32_t size) override;

		RenderBuffer* createStorageBuffer(uint32_t size) override;

		uint32_t alignmentBuffer(uint32_t originalSize, TypeRenderBuffer type) override;

		void destroyBuffer(RenderBuffer* buffer) override;

		VulkanRenderAllocator(VulkanRender& render);

		VulkanRenderAllocator() {};

		VulkanRenderAllocator(VulkanRenderAllocator&&) noexcept = default;

		VulkanRenderAllocator& operator=(VulkanRenderAllocator&&) noexcept = default;

		VulkanRenderAllocator(const VulkanRenderAllocator&) noexcept = delete;

		VulkanRenderAllocator& operator=(const VulkanRenderAllocator&) noexcept = delete;

	private:
		VulkanRender* render;
	};


}