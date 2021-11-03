#pragma once
#include "Debug.h"
namespace BEbraEngine {

	struct RenderBuffer
	{
		virtual void setData(void* data, size_t range, size_t offset) = 0;
		virtual void Destroy() = 0;
	};

	struct RenderBufferView {
		RenderBuffer* buffer;
		size_t availableRange;
		size_t offset;
		void setData(void* data, size_t range) {
			if (range > availableRange) {
				Debug::Log("the range is higher than acceptable: " + std::to_string(range) + " > " +  std::to_string(availableRange));
			}
			buffer->setData(data, range, offset);
		}
	};
}