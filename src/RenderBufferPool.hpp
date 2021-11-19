#pragma once
#include "stdafx.h"
#include "IRenderObjectPool.hpp"

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

	class RenderBufferPool : public IRenderBufferPool {
	public:
		virtual void allocate(size_t count, size_t sizeofData, AbstractRender::TypeBuffer type) override;
		virtual void deallocate(size_t count) override;
		virtual void free(std::weak_ptr<RenderBufferView> obj) override;
		virtual void setContext(AbstractRender* render) override;
		virtual std::shared_ptr<RenderBuffer> getBuffer() override { return _buffer; }
		virtual size_t getCount() override;
		virtual std::optional<std::weak_ptr<RenderBufferView>> get() override;
		~RenderBufferPool();
	public:
		std::shared_ptr<RenderBuffer> _buffer;
		tbb::concurrent_queue<std::shared_ptr<RenderBufferView>> _pool;
		tbb::concurrent_hash_map<size_t, std::shared_ptr<RenderBufferView>> used_items;
		AbstractRender* _render;
		size_t totalCount;
	};
}

