#pragma once
#include "stdafx.h"
#include "IRenderBufferPool.hpp"

using std::shared_ptr;
using std::optional;

namespace BEbraEngine {
	class RenderBufferView;
	class RenderBuffer;
	class AbstractRender;
}
namespace std {
	template<typename T>
	class shared_ptr;
	template<typename T>
	class weak_ptr;
}

namespace BEbraEngine {

	class VulkanRenderBufferPool final : public IRenderBufferPool {
	public:
		void allocate(uint32_t count, uint32_t sizeofData, AbstractRender::TypeBuffer type) override;
		void deallocate(uint32_t count) override;
		void free(shared_ptr<RenderBufferView> obj) override;
		void setContext(AbstractRender* render) override;
		shared_ptr<RenderBuffer> getBuffer() override { return _buffer; }
		size_t getCount() override;
		optional<shared_ptr<RenderBufferView>> get() override;
		~VulkanRenderBufferPool();
	private:
		shared_ptr<RenderBuffer> _buffer;
		tbb::concurrent_queue<shared_ptr<RenderBufferView>> _pool;
		tbb::concurrent_hash_map<size_t, shared_ptr<RenderBufferView>> used_items;
		AbstractRender* _render;
		size_t totalCount;
	};
}

