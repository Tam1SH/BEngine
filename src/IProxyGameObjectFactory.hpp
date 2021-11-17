#pragma once
namespace std {
	template<typename T>
	class shared_ptr;
}
namespace BEbraEngine {
	class GameObject;
	class PointLight;
	class DirLight;
	class Vector3;
}
namespace BEbraEngine {
	class IProxyGameObjectFactory {
	public:
		virtual std::shared_ptr<GameObject> create(const Vector3& position) = 0;

		virtual std::shared_ptr<PointLight> createLight(const Vector3& position) = 0;

		virtual std::shared_ptr<DirLight> createDirLight(const Vector3& direction) = 0;

		virtual void destroyObject(GameObject* object) = 0;

		virtual void destroyObject(std::shared_ptr<GameObject> object) = 0;

		virtual void destroyPointLight(std::shared_ptr<PointLight> light) = 0;

		virtual ~IProxyGameObjectFactory() {}
	};
}