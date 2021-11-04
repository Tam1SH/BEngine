#include "stdafx.h"
#include "RenderObjectPool.hpp"
#include "RenderObject.hpp"
#include "RenderBuffer.hpp"
#include "tbb/blocked_range.h"
#include "Camera.hpp"
#include "BaseRenderWindow.hpp"
#include "AbstractRenderSystem.hpp"
#include "Vertex.hpp"
#include "matrix.hpp"
#include "CreateInfoStructures.hpp"
#include "IRenderObjectFactory.hpp"
namespace BEbraEngine {
	void VulkanRenderObjectPool::allocate(size_t count)
	{
		auto new_size = count;

		_bufferTransforms = _render->CreateUniformBuffer((sizeof(Matrix4) + sizeof(Vector4)) * new_size);
		for (int i = 0; i < new_size; i++) {
			auto bufferView = new RenderBufferView();
			bufferView->availableRange = sizeof(Matrix4) + sizeof(Vector4);
			bufferView->buffer = _bufferTransforms;
			bufferView->offset = i * (sizeof(Matrix4) + sizeof(Vector4));

			RenderObjectInfo info{};
			info.bufferView = bufferView;
			//_pool.push(_factory->createObject(&info));
		}
	}
	std::optional<RenderObject*> VulkanRenderObjectPool::get()
	{
		RenderObject* out;
		_pool.try_pop(out);
		auto opt_out = std::make_optional(out);
		return opt_out;
	}

	void VulkanRenderObjectPool::free(RenderObject* obj)
	{
		_pool.push(obj);
	}

	void VulkanRenderObjectPool::setContext(AbstractRender* render)
	{
		_render = render;
	}

	void VulkanRenderObjectPool::setFactory(IRenderObjectFactory* factory)
	{
		_factory = factory;
	}

	VulkanRenderObjectPool::~VulkanRenderObjectPool()
	{
		_bufferTransforms->Destroy();
	}
}