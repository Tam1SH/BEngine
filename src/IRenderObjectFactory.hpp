#pragma once
#include "stdafx.h"

//#include "RenderObject.hpp"
namespace BEbraEngine {
	class RenderObject;
	class VulkanRenderObjectInfo;
}

namespace BEbraEngine {
	class IRenderObjectFactory {
	public:
		virtual RenderObject* create(VulkanRenderObjectInfo* info) = 0;
	};
}