#pragma once
#include "stdafx.h"

//#include "RenderObject.hpp"
namespace BEbraEngine {
	class RenderObject;
	class RenderObjectInfo;
	class Transform;
	class Light;
	class LightInfo;
	class Vector3;
}

namespace BEbraEngine {
	class IRenderObjectFactory {
	public:
		virtual void BindTransform(RenderObject* object, Transform* transform) = 0;
		//Интерфейс для пулов.
		virtual RenderObject* create(RenderObjectInfo* info) = 0;

		virtual Light* create(const Vector3& color) = 0;
	protected:

	};
}