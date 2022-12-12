#include <optional>
#include <vector>
#include <memory>
export module VulkanRenderBufferArray_impl;
import VulkanRenderBufferArray;
import RenderBufferView;

using std::shared_ptr;
using std::optional;
using std::vector;

namespace BEbraEngine {

	template<typename RenderData>
	void VulkanRenderBufferArray<RenderData>::map()
	{
		if (_data)
			_buffer->setData(_data->data(), dataSize, 0);

	}

	template<typename RenderData>
	void VulkanRenderBufferArray<RenderData>::reset(size_t count, size_t offset)
	{
		_buffer->setData(nullData.data(), count * sizeof(RenderData), offset * sizeof(RenderData));
	}

	template<typename RenderData>
	void VulkanRenderBufferArray<RenderData>::setCountToMap(size_t count)
	{
		countToMap = count;
	}

	template<typename RenderData>
	shared_ptr<RenderBuffer> VulkanRenderBufferArray<RenderData>::getBuffer()
	{
		return _buffer;
	}

	template<typename RenderData>
	size_t VulkanRenderBufferArray<RenderData>::getCount()
	{
		return _pool.unsafe_size();
	}

	template<typename RenderData>
	void VulkanRenderBufferArray<RenderData>::bindData(const vector<RenderData>& data)
	{

		if (data.size() * sizeof(RenderData) > dataSize) {
			//DEBUG_LOG1(
			//	BE_STD::stringstream() << "The allocated memory in the pool is less than the memory located in the bound data | "
			//	<< "available size : " << dataSize << " byte"
			//	<< " | bound data size : " << data.size() * sizeof(RenderData) << " byte.");
		}

		_data = &data;
		nullData.reserve(data.size());
		nullData.resize(data.size());
	}

	template<typename RenderData>
	void VulkanRenderBufferArray<RenderData>::setUsage(RenderBufferPoolUsage usage)
	{
		_usage = usage;
	}

	template<typename RenderData>
	void VulkanRenderBufferArray<RenderData>::free(shared_ptr<RenderBufferView> view)
	{
		if (view->buffer != _buffer) {
			//DEBUG_LOG1("The view does not belong to this buffer");
			throw std::exception();
		}
		_pool.push(view);

	}

	template<typename RenderData>
	optional<shared_ptr<RenderBufferView>> VulkanRenderBufferArray<RenderData>::get()
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
	VulkanRenderBufferArray<RenderData>::~VulkanRenderBufferArray()
	{
		_buffer->destroy();
	}

	template<typename RenderData>
	void VulkanRenderBufferArray<RenderData>::deallocate(uint32_t count)
	{

		//throw std::runtime_error("Not implemented");

		for (int i = 0; i < count; i++) {
			std::shared_ptr<RenderBufferView> pizda;
			_pool.try_pop(pizda);

		}
		totalCount -= count;

	}

	template<typename RenderData>
	void VulkanRenderBufferArray<RenderData>::allocate(uint32_t count, uint32_t sizeofData, TypeRenderBuffer type)
	{

		uint32_t new_size = totalCount + count;
		uint32_t alignsizeofData = 0;
		dataSize = sizeofData * count;


		if (_usage == RenderBufferPoolUsage::SeparateOneBuffer) {
			alignsizeofData = allocator->alignmentBuffer(sizeofData, type);
			if (type == TypeRenderBuffer::Storage)
				_buffer = shared_ptr<RenderBuffer>(allocator->createStorageBuffer(sizeofData * count));
			if (type == TypeRenderBuffer::Uniform)
				_buffer = shared_ptr<RenderBuffer>(allocator->createUniformBuffer(sizeofData * count));

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
}