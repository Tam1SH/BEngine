module;
#include <variant>
export module VulkanRenderAllocator;
import CRender;
import VulkanRender;
import RenderAllocatorTypeRenderBuffer;
import Vertex;
import RenderBuffer;
import <span>;
import <concepts>;

namespace BEbraEngine {

	export struct VulkanRenderAllocator {

		RenderBuffer* createIndexBuffer(std::span<uint32_t> indices);

		RenderBuffer* createVertexBuffer(std::span<Vertex> vertices);

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
	
	namespace create {

		using RenderAllocator = std::variant<VulkanRenderAllocator>;

		export RenderAllocator renderAllocator1(CRender auto& render) {
			static_assert("no implementation found");
		}

		export template<> RenderAllocator renderAllocator1(VulkanRender& render);
		
	}


}

module :private;
import CRenderAllocator;

namespace BEbraEngine {
	static_assert(CRenderAllocator<VulkanRenderAllocator>);

}