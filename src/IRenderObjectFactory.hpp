#pragma once
#include "stdafx.h"
//#include "RenderObject.hpp"
namespace BEbraEngine {
	class RenderObject;
	class RenderObjectInfo;
	class Transform;
	class PointLight;
	class Vector3;
	class DirectionLight;
	class AbstractRender;
	class IRenderBufferPool;
}

namespace BEbraEngine {
	class IRenderObjectFactory {
	public:
		virtual void BindTransform(std::shared_ptr<PointLight> light, std::shared_ptr<Transform> transform) = 0;

		virtual void BindTransform(std::shared_ptr<RenderObject> object, std::shared_ptr<Transform> transform) = 0;

		virtual RenderObject* createObject() = 0;

		virtual PointLight* createLight(const Vector3& color, const Vector3& position) = 0;

		virtual DirectionLight* createDirLight(const Vector3& color, const Vector3& direction) = 0;

		virtual void setContext(AbstractRender* render) = 0;

		virtual void destroyObject(std::shared_ptr<RenderObject> object) = 0;

		virtual void destroyPointLight(std::shared_ptr<PointLight> light) = 0;

		virtual void setModel(RenderObject* object, std::string& path) = 0;

	};
}