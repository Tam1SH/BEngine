#include <span>
module VulkanRenderAllocator;
import <variant>;

import Vertex;
import Render;
import CRender;
import CRenderAllocator;
import VulkanRender;
namespace BEbraEngine {
	
	RenderBuffer* VulkanRenderAllocator::createIndexBuffer(std::vector<uint32_t> indices) {
		return render->createIndexBuffer(indices);
	}

	RenderBuffer* VulkanRenderAllocator::createVertexBuffer(std::vector<Vertex> vertices) {
		return render->createVertexBuffer(vertices);
	}

	RenderBuffer* VulkanRenderAllocator::createUniformBuffer(uint32_t size) {
		return render->createUniformBuffer(size);
	}

	RenderBuffer* VulkanRenderAllocator::createStorageBuffer(uint32_t size) {
		return render->createStorageBuffer(size);
	}

	uint32_t VulkanRenderAllocator::alignmentBuffer(uint32_t originalSize, TypeRenderBuffer type) {
		return render->alignmentBuffer(originalSize, type);
	}

	void VulkanRenderAllocator::destroyBuffer(RenderBuffer* buffer) {
		return render->destroyBuffer(buffer);
	}

	VulkanRenderAllocator::VulkanRenderAllocator(VulkanRender& render)
	{
		this->render = static_cast<VulkanRender*>(&render);
	}
}

