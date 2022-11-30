module;
//#include <memory>
export module RenderBuffer;

namespace BEbraEngine {

	export struct RenderBuffer
	{
		virtual void setData(const void* data, unsigned int range, unsigned int offset = 0) = 0;
		virtual void destroy() = 0;
	};


}