#include "stdafx.h"
#include "AbstractRender.hpp"
#include "RenderBuffer.hpp"

using std::shared_ptr;
using std::optional;

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
		virtual void allocate(uint32_t count, uint32_t sizeofData, AbstractRender::TypeBuffer type) = 0;
		virtual void deallocate(uint32_t count) = 0;
		virtual void free(shared_ptr<RenderBufferView> obj) = 0;
		virtual void setContext(AbstractRender* render) = 0;
		virtual shared_ptr<RenderBuffer> getBuffer() = 0;
		virtual void setUsage(Usage usage) { _usage = usage; }
		virtual size_t getCount() = 0;
		virtual optional<shared_ptr<RenderBufferView>> get() = 0;
	protected:
		Usage _usage{};
	}; 

}