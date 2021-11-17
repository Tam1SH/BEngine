#pragma once
#include "Debug.h"
#include "Vector3.hpp"
namespace BEbraEngine {

	struct RenderBuffer
	{
		virtual void setData(void* data, size_t range, size_t offset) = 0;
		virtual void Destroy() = 0;
	};

	struct RenderBufferView {
		std::shared_ptr<RenderBuffer> buffer;
		size_t availableRange{};
		size_t offset{};
		void setData(void* data, size_t range, size_t offsetofData = 0) {
			if (range > availableRange) {
				Debug::Log("the range is higher than acceptable: " + std::to_string(range) + " > " +  std::to_string(availableRange));
			}
			buffer->setData(data, range, offset + offsetofData);
		}
	};
}