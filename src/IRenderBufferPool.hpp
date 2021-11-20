#include "stdafx.h"
#include "AbstractRender.hpp"
#include "RenderBuffer.hpp"
namespace BEbraEngine {
	class IRenderBufferPool {
	public:
		enum class Usage {
			//Представляет поведение по умолчанию: один буфер - одно представление
			Default,
			//Создаёт представления одного буфера (пока только на вулкане)
			SeparateOneBuffer

		};
	public:
		virtual void allocate(size_t count, size_t sizeofData, AbstractRender::TypeBuffer type) = 0;
		virtual void free(std::weak_ptr<RenderBufferView> obj) = 0;
		virtual void deallocate(size_t count) = 0;
		virtual void setContext(AbstractRender* render) = 0;
		virtual std::shared_ptr<RenderBuffer> getBuffer() = 0;
		virtual void setUsage(Usage usage) { _usage = usage; }
		virtual size_t getCount() = 0;
		virtual std::optional<std::weak_ptr<RenderBufferView>> get() = 0;
	protected:
		Usage _usage{};
	}; 

}