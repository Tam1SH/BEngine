#include "stdafx.h"
#include <optional>
namespace BEbraEngine {
	class RenderObject;
	class AbstractRender;
	class RenderBuffer;
	class IRenderObjectFactory;
}
namespace BEbraEngine {
	class IRenderObjectPool {
	public:
		virtual void allocate(size_t count) = 0;
		virtual void free(RenderObject* obj) = 0;
		virtual void setContext(AbstractRender* render) = 0;
		virtual void setFactory(IRenderObjectFactory* factory) = 0;
		virtual std::optional<RenderObject*> get() = 0;
	}; 
}