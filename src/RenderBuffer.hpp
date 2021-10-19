#pragma once
namespace BEbraEngine {

	struct RenderBuffer
	{
		virtual void setData(void* data, size_t size, size_t offset) = 0;
	};
}