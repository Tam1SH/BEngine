#pragma once
#include "stdafx.h"
#include "platform.hpp"

#include "IRenderBufferPool.hpp"
#include <VkBuffer.hpp>
#include "IRenderData.hpp"
#include "VulkanRender.hpp"
using BE_STD::shared_ptr;
using BE_STD::optional;

namespace BEbraEngine {
	class RenderBufferView;
	class RenderBuffer;
}
BE_NAMESPACE_STD_BEGIN
	template<typename T>
	class shared_ptr;
	template<typename T>
	class weak_ptr;
BE_NAMESPACE_STD_END

namespace BEbraEngine {

	template<typename RenderData>
	class VulkanRenderBufferPool : public IRenderBufferPool<RenderData> {
	public:

		void allocate(uint32_t count, uint32_t sizeofData, AbstractRender::TypeBuffer type) override;

		void deallocate(uint32_t count) override;

		void map() override;

		void setContext(AbstractRender* render) override;

		shared_ptr<RenderBuffer> getBuffer() override { return _buffer; }
		
		size_t getCount() override;
		
		void bindData(const vector<RenderData>& data) {
			if (data.size() * sizeof(RenderData) > dataSize) {
				DEBUG_LOG1(
					BE_STD::stringstream() << "The allocated memory in the pool is less than the memory located in the bound data | "
					<< "available size : " << dataSize << " byte"
					<< " | bound data size : " << data.size() * sizeof(RenderData) << " byte.");
			}

			_data = &data;
		}

		void setUsage(RenderBufferPoolUsage usage) override { _usage = usage; }

		void free(shared_ptr<RenderBufferView> view) override;

		optional<shared_ptr<RenderBufferView>> get() override;

		~VulkanRenderBufferPool();
	
	private:
		
		size_t dataSize;
		shared_ptr<RenderBuffer> _buffer;
		const vector<RenderData>* _data;
		tbb::concurrent_queue<shared_ptr<RenderBufferView>> _pool;
		AbstractRender* _render;
		size_t totalCount;
		RenderBufferPoolUsage _usage{};
	};


	template<typename RenderData>
	inline void VulkanRenderBufferPool<RenderData>::allocate(uint32_t count, uint32_t sizeofData, AbstractRender::TypeBuffer type)
	{
		uint32_t new_size = totalCount + count;
		uint32_t alignsizeofData = 0;
		dataSize = sizeofData * count;


		if (_usage == RenderBufferPoolUsage::SeparateOneBuffer) {
			alignsizeofData = _render->alignmentBuffer(sizeofData, type);
			if (type == AbstractRender::TypeBuffer::Storage)
				_buffer = shared_ptr<RenderBuffer>(_render->createStorageBuffer(sizeofData * count));
			if (type == AbstractRender::TypeBuffer::Uniform)
				_buffer = shared_ptr<RenderBuffer>(_render->createUniformBuffer(sizeofData * count));

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

	template<typename RenderData>
	inline void VulkanRenderBufferPool<RenderData>::deallocate(uint32_t count) {

		throw std::runtime_error("Not implemented");
		/*
		for (int i = 0; i < count; i++) {
			std::shared_ptr<RenderBufferView> pizda;
			_pool.try_pop(pizda);

		}
		totalCount -= count;
		*/
	}

	template<typename RenderData>
	inline void VulkanRenderBufferPool<RenderData>::map()
	{
		if(_data)
			_buffer->setData(_data->data(), dataSize, 0);

	}




	template<typename RenderData>
	inline optional<shared_ptr<RenderBufferView>> VulkanRenderBufferPool<RenderData>::get()
	{

		shared_ptr<RenderBufferView> out;
		optional<shared_ptr<RenderBufferView>> opt_out;
		if (_pool.try_pop(out)) {
			opt_out = optional<shared_ptr<RenderBufferView>>(out);
			return opt_out;
		}

		return optional<shared_ptr<RenderBufferView>>();
	}

	template<typename RenderData>
	inline void VulkanRenderBufferPool<RenderData>::setContext(AbstractRender* render)
	{
		_render = static_cast<VulkanRender*>(render);
	}

	template<typename RenderData>
	inline size_t VulkanRenderBufferPool<RenderData>::getCount()
	{
		return _pool.unsafe_size();
	}

	template<typename RenderData>
	inline void VulkanRenderBufferPool<RenderData>::free(shared_ptr<RenderBufferView> view)
	{
		if (view->buffer != _buffer) {
			DEBUG_LOG1("The view does not belong to this buffer");
			throw std::exception();
		}
		_pool.push(view);

	}

	template<typename RenderData>
	inline VulkanRenderBufferPool<RenderData>::~VulkanRenderBufferPool()
	{
		_buffer->destroy();
	}

}

