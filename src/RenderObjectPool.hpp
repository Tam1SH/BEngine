#pragma once
#include "stdafx.h"
#include "IRenderObjectPool.hpp"
#include <optional>
namespace BEbraEngine {
	class RenderObject;
	class AbstractRender;
	class RenderBuffer;
	class IRenderObjectFactory;
}
namespace BEbraEngine {


	class VulkanRenderObjectPool : public IRenderObjectPool {
	public:
		using RenderObjects = tbb::concurrent_queue<RenderObject*>;
	public:
		void allocate(size_t count) override;
		void free(RenderObject* obj) override;
		void setContext(AbstractRender* render) override;
		void setFactory(IRenderObjectFactory* factory) override;
		std::optional<RenderObject*> get() override;

		~VulkanRenderObjectPool();
	public:
		RenderBuffer* _bufferTransforms;
		AbstractRender* _render;
		IRenderObjectFactory* _factory;
		RenderObjects _pool;
		std::vector<bool> _poolCheckIsFree;
		std::vector<VkDescriptorSet> _sets;
		std::vector<uint32_t> offsets;
		std::mutex mutex_get;
	};
}

