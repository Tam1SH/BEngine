#pragma once
#include "stdafx.h"
#include "IRenderObjectPool.hpp"
#include <optional>


namespace BEbraEngine {
	class VulkanRender;
}
namespace BEbraEngine {

	class VulkanRenderObjectPool : public IRenderObjectPool {
	public:
		void allocate(size_t count, size_t sizeofData, AbstractRender::TypeBuffer type) override;
		void deallocate(size_t count) override;
		void free(std::weak_ptr<RenderBufferView> obj) override;
		void setContext(AbstractRender* render) override;
		std::shared_ptr<RenderBuffer> getBuffer() override { return _buffer; }
		size_t getCount() override;
		std::optional<std::weak_ptr<RenderBufferView>> get() override;
		~VulkanRenderObjectPool();
	public:
		std::shared_ptr<RenderBuffer> _buffer;
		tbb::concurrent_queue<std::shared_ptr<RenderBufferView>> _pool;
		tbb::concurrent_hash_map<size_t, std::shared_ptr<RenderBufferView>> used_items;
		VulkanRender* _render;
		size_t totalCount;
	};
}

