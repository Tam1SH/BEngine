#include "platform.hpp"
#include <tbb.h>
export module VulkanRenderBufferArray;
import RenderBufferArray;
import VulkanBuffer;
import RenderBuffer;
import VulkanRender;
import Render;
import <optional>;
import <vector>;
import <memory>;
using std::shared_ptr;
using std::optional;
using std::vector;

namespace BEbraEngine {

}

namespace BEbraEngine {

	export template<class RenderData>
	class VulkanRenderBufferArray : public RenderBufferArray<RenderData> {
	public:
		
		void allocate(uint32_t count, uint32_t sizeofData, Render::TypeBuffer type)
		{

			uint32_t new_size = totalCount + count;
			uint32_t alignsizeofData = 0;
			dataSize = sizeofData * count;


			if (_usage == RenderBufferPoolUsage::SeparateOneBuffer) {
				alignsizeofData = _render->alignmentBuffer(sizeofData, type);
				if (type == Render::TypeBuffer::Storage)
					_buffer = shared_ptr<RenderBuffer>(_render->createStorageBuffer(sizeofData * count));
				if (type == Render::TypeBuffer::Uniform)
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

		void deallocate(uint32_t count) {

			throw std::runtime_error("Not implemented");
			
			for (int i = 0; i < count; i++) {
				std::shared_ptr<RenderBufferView> pizda;
				_pool.try_pop(pizda);

			}
			totalCount -= count;
			
		} //override;

		void map()
		{
			if (_data)
				_buffer->setData(_data->data(), dataSize, 0);

		} //override;

		void reset(size_t count, size_t offset)
		{
			_buffer->setData(nullData.data(), count * sizeof(RenderData), offset * sizeof(RenderData));
		} //override;

		void setCountToMap(size_t count)
		{
			countToMap = count;
		} //override;

		void setContext(Render* render)
		{
			_render = static_cast<VulkanRender*>(render);
		}//override;

		shared_ptr<RenderBuffer> getBuffer() //override 
		{ return _buffer; }
		
		size_t getCount()
		{
			return _pool.unsafe_size();
		}//override;
		
		void bindData(const vector<RenderData>& data)
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
		} //override;

		void setUsage(RenderBufferPoolUsage usage) //override 
		{ _usage = usage; }

		void free(shared_ptr<RenderBufferView> view)
		{
			if (view->buffer != _buffer) {
				//DEBUG_LOG1("The view does not belong to this buffer");
				throw std::exception();
			}
			_pool.push(view);

		}// override;

		optional<shared_ptr<RenderBufferView>> get()
		{

			shared_ptr<RenderBufferView> out;
			optional<shared_ptr<RenderBufferView>> opt_out;
			if (_pool.try_pop(out)) {
				opt_out = optional<shared_ptr<RenderBufferView>>(out);
				return opt_out;
			}

			return optional<shared_ptr<RenderBufferView>>();
		} //override;

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
		Render* _render;
		size_t totalCount;
		size_t countToMap;
		RenderBufferPoolUsage _usage{};
	};




}

