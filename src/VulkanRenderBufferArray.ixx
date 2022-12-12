module;
#include <tbb.h>
#include <optional>
#include <vector>
#include <memory>

export module VulkanRenderBufferArray;
import RenderBufferArray;
import RenderAllocatorTypeRenderBuffer;

using std::shared_ptr;
using std::optional;
using std::vector;

namespace BEbraEngine {
	export struct RenderBuffer;
	export struct VulkanBuffer;
	export struct RenderBufferView;
	export struct VulkanRenderAllocator;
}

namespace BEbraEngine {

	export template<typename RenderData>
	class VulkanRenderBufferArray : public RenderBufferArray<RenderData> {
	public:

		void allocate(uint32_t count, uint32_t sizeofData, TypeRenderBuffer type) override;

		void deallocate(uint32_t count) override;

		void map() override;

		void reset(size_t count, size_t offset) override;

		void setCountToMap(size_t count) override;

		shared_ptr<RenderBuffer> getBuffer() override;
		
		size_t getCount() override;
		
		void bindData(const vector<RenderData>& data) override;

		void setUsage(RenderBufferPoolUsage usage) override;

		void free(shared_ptr<RenderBufferView> view) override;

		optional<shared_ptr<RenderBufferView>> get() override;

		VulkanRenderBufferArray(VulkanRenderBufferArray&&) noexcept = default;
		VulkanRenderBufferArray& operator=(VulkanRenderBufferArray&&) noexcept = default;

		VulkanRenderBufferArray(VulkanRenderAllocator& allocator) : allocator(&allocator) { }

		~VulkanRenderBufferArray();
	
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

