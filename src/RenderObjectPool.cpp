#include "stdafx.h"
#include "RenderObjectPool.hpp"
#include "RenderObject.hpp"
#include "RenderBuffer.hpp"
#include "tbb/blocked_range.h"
#include "Camera.hpp"
#include "BaseRenderWindow.hpp"
#include "AbstractRender.hpp"
#include "Vertex.hpp"
#include "matrix.hpp"
#include "CreateInfoStructures.hpp"
#include "IRenderObjectFactory.hpp"
#include "RenderObject.hpp"
#include "VulkanRender.hpp"
namespace BEbraEngine {
	void VulkanRenderObjectPool::allocate(size_t count, size_t sizeofData, AbstractRender::TypeBuffer type)
	{
		size_t 	new_size = totalCount + count;;

		size_t alignsizeofData = 0;

		if (type == AbstractRender::TypeBuffer::Uniform) {

			if (_usage == IRenderObjectPool::Usage::Default) {
				alignsizeofData = _render->pad_uniform_buffer_size(sizeofData);
				_buffer = std::shared_ptr<RenderBuffer>(_render->createUniformBuffer(alignsizeofData * new_size));
			}

			if (_usage == IRenderObjectPool::Usage::SeparateOneBuffer) {
				alignsizeofData = _render->pad_storage_buffer_size(sizeofData / count);
				_buffer = std::shared_ptr<RenderBuffer>(_render->createUniformBuffer(sizeofData));

			}

		}
		if (type == AbstractRender::TypeBuffer::Storage)
		{
			
			if (_usage == IRenderObjectPool::Usage::Default) {
				alignsizeofData = _render->pad_storage_buffer_size(sizeofData);
				_buffer = std::shared_ptr<RenderBuffer>(_render->createStorageBuffer(alignsizeofData * new_size));
			}
				
			if (_usage == IRenderObjectPool::Usage::SeparateOneBuffer) {
				alignsizeofData = _render->pad_storage_buffer_size(sizeofData / count);
				_buffer = std::shared_ptr<RenderBuffer>(_render->createStorageBuffer(sizeofData));
			}

		}

		
		for (int i = totalCount; i < new_size; i++) {
			auto bufferView = new RenderBufferView();
			bufferView->availableRange = alignsizeofData;
			bufferView->buffer = std::shared_ptr<RenderBuffer>(_buffer);
			bufferView->offset = i * alignsizeofData;
			_pool.emplace(std::shared_ptr<RenderBufferView>(bufferView));
		}

		totalCount += count;
	}
	void VulkanRenderObjectPool::deallocate(size_t count) {
		for (int i = 0; i < count; i++) {
			std::shared_ptr<RenderBufferView> pizda;
			_pool.try_pop(pizda);

		}
		totalCount -= count;
	}
	std::optional<std::weak_ptr<RenderBufferView>> VulkanRenderObjectPool::get()
	{

		std::shared_ptr<RenderBufferView> out;

		_pool.try_pop(out);
		used_items.emplace(std::make_pair(out->offset, out));

		auto opt_out = std::make_optional(std::weak_ptr<RenderBufferView>(out));
		return opt_out;
	}

	void VulkanRenderObjectPool::free(std::weak_ptr<RenderBufferView> obj)
	{
		if (!obj.expired()) {
			auto shared = obj.lock();
			used_items.erase(shared->offset);
			_pool.push(shared);
			
		}
	}

	void VulkanRenderObjectPool::setContext(AbstractRender* render)
	{
		_render = static_cast<VulkanRender*>(render);
	}

	size_t VulkanRenderObjectPool::getCount()
	{
		return _pool.unsafe_size();
	}


	VulkanRenderObjectPool::~VulkanRenderObjectPool()
	{
		_buffer->Destroy();
	}
}