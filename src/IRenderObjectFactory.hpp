#pragma once
#include "stdafx.h"
//#include "RenderObject.hpp"
namespace BEbraEngine {
	class RenderObject;
	class RenderObjectInfo;
	class Transform;
	class Light;
	class Vector3;
	class AbstractRender;
}
template<class T>
class std::shared_ptr;

namespace BEbraEngine {
	class IRenderObjectFactory {
	public:
		virtual void BindTransform(Light* light, Transform* transform) = 0;

		virtual void BindTransform(RenderObject* object, Transform* transform) = 0;

		virtual RenderObject* createObject() = 0;

		virtual Light* createLight(const Vector3& color, const Vector3& position) = 0;

		virtual void setContext(AbstractRender* render) = 0;

		virtual void destroyObject(RenderObject* object) = 0;
	};
}