#pragma once
#include "stdafx.h"
#include "IRenderBufferPool.hpp"

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

	class VulkanRenderBufferPool : public IRenderBufferPool {
	public:
		void allocate(size_t count, size_t sizeofData, AbstractRender::TypeBuffer type) override;
		void deallocate(size_t count) override;
		void free(std::weak_ptr<RenderBufferView> obj) override;
		void setContext(AbstractRender* render) override;
		std::shared_ptr<RenderBuffer> getBuffer() override { return _buffer; }
		size_t getCount() override;
		std::optional<std::weak_ptr<RenderBufferView>> get() override;
		~VulkanRenderBufferPool();
	private:
		std::shared_ptr<RenderBuffer> _buffer;
		tbb::concurrent_queue<std::shared_ptr<RenderBufferView>> _pool;
		tbb::concurrent_hash_map<size_t, std::shared_ptr<RenderBufferView>> used_items;
		AbstractRender* _render;
		size_t totalCount;
	};
}

