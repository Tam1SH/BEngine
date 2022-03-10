#pragma once
#include "stdafx.h"
#include "platform.hpp"
#include "RenderObject.hpp"

using BE_STD::shared_ptr;
using BE_STD::unique_ptr;
using BE_STD::optional;

namespace BEbraEngine {
	class Transform;
	class Light;
	class Vector3;
	class DirectionLight;
	class AbstractRender;

	class SimpleCamera; 
}

namespace BEbraEngine {
	class IRenderObjectFactory {
	public:

		virtual optional<RenderObject*> create(const RenderObject::RenderObjectCreateInfo& info) = 0;

		virtual void bindTransform(Light& light, Transform& transform) = 0;

		virtual void bindTransform(RenderObject& object, Transform& transform) = 0;

		virtual void setTexture(RenderObject& object, const boost::filesystem::path& path) = 0;

		virtual void setTexture(shared_ptr<RenderObject> object, Texture const& path) = 0;


		virtual Light* createLight(const Vector3& color, const Vector3& position) = 0;

		virtual SimpleCamera* createCamera(const Vector3& position) = 0;

		virtual DirectionLight* createDirLight(const Vector3& color, const Vector3& direction) = 0;

		virtual void setContext(AbstractRender* render) = 0;

		virtual void destroyObject(RenderObject& object) = 0;

		virtual void destroyPointLight(Light& light) = 0;

		virtual void destroyCamera(SimpleCamera& camera) = 0;

		virtual void setModel(RenderObject& object, const std::string& path) = 0;

	};
}