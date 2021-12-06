#pragma once
#include "IRenderBufferPool.hpp"
//Ну, я тупой еблан и я не представляю как можно обновлять части одного буфера и использовать его для рендера нескольких объектов
namespace BEbraEngine {

	class DXRenderBufferPool : public IRenderBufferPool
	{
	public:
		void allocate(uint32_t count, uint32_t sizeofData, AbstractRender::TypeBuffer type) override;
		void free(std::weak_ptr<RenderBufferView> obj) override;
		void deallocate(uint32_t count) override;
		void setContext(AbstractRender* render) override;
		std::shared_ptr<RenderBuffer> getBuffer() override;
		size_t getCount() override;
		std::optional<std::weak_ptr<RenderBufferView>> get() override;
		~DXRenderBufferPool();
	private:

		tbb::concurrent_vector<std::shared_ptr<RenderBuffer>> buffers;
		tbb::concurrent_queue<std::shared_ptr<RenderBufferView>> _pool;
		tbb::concurrent_hash_map<size_t, std::shared_ptr<RenderBufferView>> used_items;
		AbstractRender* _render;
		size_t totalCount;
	};
}

