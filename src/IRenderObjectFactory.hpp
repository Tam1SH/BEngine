#pragma once
#include "stdafx.h"
#include "RenderObject.hpp"

using std::shared_ptr;
using std::unique_ptr;
using std::optional;

namespace BEbraEngine {
	class Transform;
	class PointLight;
	class Vector3;
	class DirectionLight;
	class AbstractRender;
	class IRenderBufferPool;
	class SimpleCamera; 
}

namespace BEbraEngine {
	class IRenderObjectFactory {
	public:

		virtual optional<RenderObject*> create(const RenderObject::RenderObjectCreateInfo& info) = 0;

		virtual void bindTransform(PointLight& light, Transform& transform) = 0;

		virtual void bindTransform(RenderObject& object, Transform& transform) = 0;

		virtual void setTexture(shared_ptr<RenderObject> object, const boost::filesystem::path& path) = 0;

		virtual void setTexture(shared_ptr<RenderObject> object, Texture const& path) = 0;


		virtual PointLight* createLight(const Vector3& color, const Vector3& position) = 0;

		virtual SimpleCamera* createCamera(const Vector3& position) = 0;

		virtual DirectionLight* createDirLight(const Vector3& color, const Vector3& direction) = 0;

		virtual void setContext(AbstractRender* render) = 0;

		virtual void destroyObject(RenderObject& object) = 0;

		virtual void destroyPointLight(PointLight& light) = 0;

		virtual void destroyCamera(SimpleCamera& camera) = 0;

		virtual void setModel(RenderObject& object, const std::string& path) = 0;

	};
}