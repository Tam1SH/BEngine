#pragma once
#include "stdafx.h"
//#include "RenderObject.hpp"
namespace BEbraEngine {
	class RenderObject;
	class RenderObjectInfo;
	class Transform;
	class PointLight;
	class Vector3;
	class DirLight;
	class AbstractRender;
}
template<class T>
class std::shared_ptr;

namespace BEbraEngine {
	class IRenderObjectFactory {
	public:
		virtual void BindTransform(PointLight* light, Transform* transform) = 0;

		virtual void BindTransform(RenderObject* object, Transform* transform) = 0;

		virtual RenderObject* createObject() = 0;

		virtual PointLight* createLight(const Vector3& color, const Vector3& position) = 0;

		virtual DirLight* createDirLight(const Vector3& color, const Vector3& direction) = 0;

		virtual void setContext(AbstractRender* render) = 0;

		virtual void destroyObject(RenderObject* object) = 0;
	};
}