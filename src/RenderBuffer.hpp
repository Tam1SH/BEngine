#pragma once
namespace BEbraEngine {

	struct RenderBuffer
	{
		virtual void setData(void* data, size_t range, size_t offset) = 0;
	};

	struct RenderBufferView {
		RenderBuffer* buffer;
		size_t availableRange;
		size_t offset;
	};
}