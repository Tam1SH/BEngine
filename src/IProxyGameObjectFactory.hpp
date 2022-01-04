#pragma once
#include "GameObject.hpp"

using std::shared_ptr;
using std::unique_ptr;
using std::optional;
using std::string;

namespace std {
	template<typename T>
	class shared_ptr;
	template<typename T>
	class optional;
}
namespace BEbraEngine {
	class GameObject;
	class PointLight;
	class DirectionLight;
	class Vector3;
	class Camera;
}
namespace BEbraEngine {
	class IProxyGameObjectFactory {
	public:
		virtual optional<shared_ptr<GameObject>> create(const GameObject::GameObjectCreateInfo& info) = 0;

		virtual shared_ptr<PointLight> createLight(const Vector3& position) = 0;

		virtual shared_ptr<DirectionLight> createDirLight(const Vector3& direction) = 0;

		virtual shared_ptr<Camera> createCamera(const Vector3& position) = 0;

		virtual void destroyCamera(shared_ptr<Camera> camera) = 0;

		virtual void destroyObject(shared_ptr<GameObject> object) = 0;

		virtual void setModel(GameObject* object, const string& path) = 0;

		virtual void destroyPointLight(std::shared_ptr<PointLight> light) = 0;

		virtual ~IProxyGameObjectFactory() {}
	};
}