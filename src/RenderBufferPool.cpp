#include "stdafx.h"
#include "VulkanRenderBufferPool.hpp"
#include "RenderObject.hpp"
#include "RenderBuffer.hpp"
#include <oneapi/tbb/blocked_range.h>

#include "Camera.hpp"
#include "BaseRenderWindow.hpp"
#include "AbstractRender.hpp"
#include "Vertex.hpp"
#include "matrix.hpp"
#include "CreateInfoStructures.hpp"
#include "IRenderObjectFactory.hpp"
#include "VulkanRender.hpp"
namespace BEbraEngine {
	void VulkanRenderBufferPool::allocate(uint32_t count, uint32_t sizeofData, AbstractRender::TypeBuffer type)
	{
		uint32_t new_size = totalCount + count;
		uint32_t alignsizeofData = 0;


		if (_usage == IRenderBufferPool::Usage::Default) {
			alignsizeofData = _render->alignmentBuffer(sizeofData, type);
			if(type == AbstractRender::TypeBuffer::Storage)
				_buffer = shared_ptr<RenderBuffer>(_render->createStorageBuffer(alignsizeofData * new_size));
			if (type == AbstractRender::TypeBuffer::Uniform)
				_buffer = shared_ptr<RenderBuffer>(_render->createUniformBuffer(alignsizeofData * new_size));
		}

		if (_usage == IRenderBufferPool::Usage::SeparateOneBuffer) {
			alignsizeofData = _render->alignmentBuffer(sizeofData / count, type);
			if (type == AbstractRender::TypeBuffer::Storage)
				_buffer = shared_ptr<RenderBuffer>(_render->createStorageBuffer(sizeofData));
			if (type == AbstractRender::TypeBuffer::Uniform)
				_buffer = shared_ptr<RenderBuffer>(_render->createUniformBuffer(sizeofData));

		}

		
		for (uint32_t i = totalCount; i < new_size; i++) {
			auto bufferView = new RenderBufferView();
			bufferView->availableRange = alignsizeofData;
			bufferView->buffer = shared_ptr<RenderBuffer>(_buffer);
			bufferView->offset = i * alignsizeofData;
			_pool.emplace(shared_ptr<RenderBufferView>(bufferView));
		}

		totalCount += count;
	}
	void VulkanRenderBufferPool::deallocate(uint32_t count) {

		throw std::runtime_error("Not implemented");
		/*
		for (int i = 0; i < count; i++) {
			std::shared_ptr<RenderBufferView> pizda;
			_pool.try_pop(pizda);

		}
		totalCount -= count;
		*/
	}
	optional<shared_ptr<RenderBufferView>> VulkanRenderBufferPool::get()
	{

		shared_ptr<RenderBufferView> out;

		_pool.try_pop(out);
		used_items.emplace(std::make_pair(out->offset, out));

		auto opt_out = optional<shared_ptr<RenderBufferView>>(out);
		return opt_out;
	}

	void VulkanRenderBufferPool::free(shared_ptr<RenderBufferView> obj)
	{
		used_items.erase(obj->offset);
		_pool.push(obj);
		
	}

	void VulkanRenderBufferPool::setContext(AbstractRender* render)
	{
		_render = static_cast<VulkanRender*>(render);
	}

	size_t VulkanRenderBufferPool::getCount()
	{
		return _pool.unsafe_size();
	}


	VulkanRenderBufferPool::~VulkanRenderBufferPool()
	{
		_buffer->destroy();
	}
}