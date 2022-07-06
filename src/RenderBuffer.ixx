#include <memory>
#include <string>

#define DEBUG_LOG1(msg) BEbraEngine::Debug::log(__LINE__, __FILE__, msg);
#define DEBUG_LOG2(msg, pointer, name, oType, mType) BEbraEngine::Debug::log(__LINE__, __FILE__, msg, pointer, name, oType, mType)
#define DEBUG_LOG3(msg, pointer) BEbraEngine::Debug::log(__LINE__, __FILE__, msg, pointer);

#ifdef _DEBUG
#define DEBUG_DESTROY_CHECK_DECL() public: bool isDestroyed; private:
#define DEBUG_DESTROY_CHECK(msg, pointer, name, oType, mType) if(!isDestroyed) BEbraEngine::Debug::log(__LINE__, __FILE__, msg, pointer, name, oType, mType)	

#else
#define DEBUG_DESTROY_CHECK(msg, pointer, name, oType, mType) 
#define DEBUG_DESTROY_CHECK_DECL()
#endif

export module RenderBuffer;
import Debug;
import Vector3;
namespace BEbraEngine {

	export class RenderBuffer
	{
	public:
		virtual void setData(const void* data, uint32_t range, uint32_t offset = 0) = 0;
		virtual void destroy() = 0;
	};

	export class RenderBufferView {
	public:
		std::shared_ptr<RenderBuffer> buffer;
		uint32_t availableRange{};
		uint32_t offset{};
		void setData(const void* data, uint32_t range, uint32_t offsetofData = 0) {
			if (range > availableRange) {
				DEBUG_LOG1("the range is higher than acceptable: " + std::to_string(range) + " > " + std::to_string(availableRange));
			}
			else
				buffer->setData(data, range, offset + offsetofData);
		}
	};
}