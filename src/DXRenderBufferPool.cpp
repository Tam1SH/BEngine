#include "stdafx.h"
#include "DXRenderBufferPool.hpp"
namespace BEbraEngine {


    void DXRenderBufferPool::allocate(size_t count, size_t sizeofData, AbstractRender::TypeBuffer type)
    {
        size_t 	new_size = totalCount + count;

        buffers.reserve(new_size);
        buffers.resize(new_size);


        for (int i = totalCount; i < new_size; i++) {
            buffers[i] = std::shared_ptr<RenderBuffer>(_render->createUniformBuffer(sizeofData));
            auto bufferView = new RenderBufferView();
            bufferView->availableRange = sizeofData;
            bufferView->buffer = std::shared_ptr<RenderBuffer>(buffers[i]);
            bufferView->offset = i * sizeofData;
            _pool.emplace(std::shared_ptr<RenderBufferView>(bufferView));
        }

        totalCount += count;
    }

    void DXRenderBufferPool::free(std::weak_ptr<RenderBufferView> obj)
    {
        if (!obj.expired()) {
            auto shared = obj.lock();
            used_items.erase(shared->offset);
            _pool.push(shared);

        }
    }

    void DXRenderBufferPool::deallocate(size_t count)
    {

    }

    void DXRenderBufferPool::setContext(AbstractRender* render)
    {
        _render = render;
    }

    std::shared_ptr<RenderBuffer> DXRenderBufferPool::getBuffer()
    {
        return std::shared_ptr<RenderBuffer>();
    }

    size_t DXRenderBufferPool::getCount()
    {
        return _pool.unsafe_size();
    }

    std::optional<std::weak_ptr<RenderBufferView>> DXRenderBufferPool::get()
    {

        std::shared_ptr<RenderBufferView> out;

        _pool.try_pop(out);
        used_items.emplace(std::make_pair(out->offset, out));

        auto opt_out = std::make_optional(std::weak_ptr<RenderBufferView>(out));
        return opt_out;
    }
    DXRenderBufferPool::~DXRenderBufferPool()
    {
        for (auto& buffer : buffers) {
            buffer->Destroy();
        }
    }
}
