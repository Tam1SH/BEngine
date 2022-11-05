module;
#include "platform.hpp"

#include <boost/filesystem.hpp>
export module VulkanRenderBufferArray;
import RenderBufferArray;
import VulkanBuffer;
import RenderBuffer;
import VulkanRender;
import VulkanRenderAllocator;
import <optional>;
import <tbb.h>;
import <vector>;
import <memory>;

using std::shared_ptr;
using std::optional;
using std::vector;


namespace BEbraEngine {

	export template<typename RenderData>
	class VulkanRenderBufferArray : public RenderBufferArray<RenderData> {
	public:

		void allocate(uint32_t count, uint32_t sizeofData, TypeRenderBuffer type) override
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

		void deallocate(uint32_t count) override {

			throw std::runtime_error("Not implemented");
			
			for (int i = 0; i < count; i++) {
				std::shared_ptr<RenderBufferView> pizda;
				_pool.try_pop(pizda);

			}
			totalCount -= count;
			
		} 

		void map() override
		{
			if (_data)
				_buffer->setData(_data->data(), dataSize, 0);

		} 

		void reset(size_t count, size_t offset) override
		{
			_buffer->setData(nullData.data(), count * sizeof(RenderData), offset * sizeof(RenderData));
		} 

		void setCountToMap(size_t count) override
		{
			countToMap = count;
		} 

		shared_ptr<RenderBuffer> getBuffer() override 
		{ return _buffer; }
		
		size_t getCount() override
		{
			return _pool.unsafe_size();
		}
		
		void bindData(const vector<RenderData>& data) override
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

		void setUsage(RenderBufferPoolUsage usage) override 
		{ _usage = usage; }

		void free(shared_ptr<RenderBufferView> view) override
		{
			if (view->buffer != _buffer) {
				//DEBUG_LOG1("The view does not belong to this buffer");
				throw std::exception();
			}
			_pool.push(view);

		} 

		optional<shared_ptr<RenderBufferView>> get() override
		{

			shared_ptr<RenderBufferView> out;
			optional<shared_ptr<RenderBufferView>> opt_out;
			if (_pool.try_pop(out)) {
				opt_out = optional<shared_ptr<RenderBufferView>>(out);
				return opt_out;
			}

			return optional<shared_ptr<RenderBufferView>>();
		} 

		VulkanRenderBufferArray(VulkanRenderBufferArray&&) noexcept = default;
		VulkanRenderBufferArray& operator=(VulkanRenderBufferArray&&) noexcept = default;

		VulkanRenderBufferArray(const VulkanRenderBufferArray& other) noexcept {
			dataSize = other.dataSize;
			_buffer = other._buffer;
			_data = other._data;
			nullData = other.nullData;
			std::copy(other._pool.unsafe_begin(), other._pool.unsafe_end(), _pool.unsafe_begin());

			allocator = other.allocator;
			totalCount = other.totalCount;
			countToMap = other.countToMap;
			_usage = other._usage;
		}

		VulkanRenderBufferArray& operator=(const VulkanRenderBufferArray& other) noexcept {
			dataSize = other.dataSize;
			_buffer = other._buffer;
			_data = other._data;
			nullData = other.nullData;
			std::copy(other._pool.unsafe_begin(), other._pool.unsafe_end(), _pool.unsafe_begin());

			allocator = other.allocator;
			totalCount = other.totalCount;
			countToMap = other.countToMap;
			_usage = other._usage;
			return *this;
		}


		VulkanRenderBufferArray(VulkanRenderAllocator& allocator) : allocator(&allocator) { }

		~VulkanRenderBufferArray()
		{
			_buffer->destroy();
		}
	
	private:
		
		size_t dataSize;
		shared_ptr<RenderBuffer> _buffer;
		const vector<RenderData>* _data;
		vector<RenderData> nullData;
		tbb::concurrent_queue<shared_ptr<RenderBufferView>> _pool;
		VulkanRenderAllocator* allocator;
		size_t totalCount;
		size_t countToMap;
		RenderBufferPoolUsage _usage{};
	};
}

