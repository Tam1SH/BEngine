module;
#include "platform.hpp"
export module RenderBufferArray;
import <memory>;
import <optional>;
import <vector>;
import CRenderAllocator;
import RenderBuffer;
import RenderAllocatorTypeRenderBuffer;

using std::shared_ptr;
using std::optional;

namespace BEbraEngine {

	export enum class RenderBufferPoolUsage {
		SeparateOneBuffer

	};

	export template<typename RenderData>
	class RenderBufferArray {
	public:

		virtual ~RenderBufferArray() { }

		virtual void allocate(uint32_t count, uint32_t sizeofData, TypeRenderBuffer type) = 0;

		virtual void deallocate(uint32_t count) = 0;

		virtual void reset(size_t count, size_t offset) = 0;

		virtual void map() = 0;

		virtual void setCountToMap(size_t count) = 0;

		virtual void free(shared_ptr<RenderBufferView> view) = 0;

		virtual void bindData(const std::vector<RenderData>& data) = 0;

		virtual shared_ptr<RenderBuffer> getBuffer() = 0;

		virtual void setUsage(RenderBufferPoolUsage usage) = 0;

		virtual size_t getCount() = 0;

		virtual optional<shared_ptr<RenderBufferView>> get() = 0;
	};

}