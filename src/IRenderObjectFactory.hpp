#pragma once
#include "stdafx.h"

//#include "RenderObject.hpp"
namespace BEbraEngine {
	class RenderObject;
	class RenderObjectInfo;
	class Transform;
}

namespace BEbraEngine {
	class IRenderObjectFactory {
	public:
		virtual void BindTransform(RenderObject* object, Transform* transform) = 0;
		//Интерфейс для пулов.
		virtual RenderObject* create(RenderObjectInfo* info) = 0;
	protected:

	};
}