#pragma once
#include "stdafx.h"
#include "RenderObject.hpp"

using std::shared_ptr;

namespace BEbraEngine {
	class Transform;
	class PointLight;
	class Vector3;
	class DirectionLight;
	class AbstractRender;
	class IRenderBufferPool;
	class Camera; 
}

namespace BEbraEngine {
	class IRenderObjectFactory {
	public:
		virtual void bindTransform(std::shared_ptr<PointLight> light, std::shared_ptr<Transform> transform) = 0;

		virtual void bindTransform(std::shared_ptr<RenderObject> object, std::shared_ptr<Transform> transform) = 0;

		virtual void setTexture(shared_ptr<RenderObject> object, const boost::filesystem::path& path) = 0;

		virtual void setTexture(RenderObject* object, Texture const* path) = 0;

		virtual std::optional<RenderObject*> create(const RenderObject::RenderObjectCreateInfo& info) = 0;

		virtual PointLight* createLight(const Vector3& color, const Vector3& position) = 0;

		virtual Camera* createCamera(const Vector3& position) = 0;

		virtual DirectionLight* createDirLight(const Vector3& color, const Vector3& direction) = 0;

		virtual void setContext(AbstractRender* render) = 0;

		virtual void destroyObject(std::shared_ptr<RenderObject> object) = 0;

		virtual void destroyPointLight(std::shared_ptr<PointLight> light) = 0;

		virtual void destroyCamera(std::shared_ptr<Camera> camera) = 0;

		virtual void setModel(RenderObject* object, const std::string& path) = 0;

	};
}