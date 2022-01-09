
#pragma once
//#include "AbstractComponent.hpp"
#include "stdafx.h"

#include "IVisitorGameComponentDestroyer.hpp"
#include "GameComponentCreateInfo.hpp"

using std::shared_ptr;
using std::unique_ptr;
using std::optional;
using std::string;

namespace std {
	 template<class T> 
	 class shared_ptr;
}
namespace BEbraEngine {
	class Physics;
	class Render;
	class TransformFactory;
	class VulkanRenderObjectFactory;
	class RigidBody;
	class WorkSpace;
	class AbstractRender;
	class ColliderFactory;
	class RigidBodyFactory;
	class IRenderObjectFactory;
	class GameComponentCreateInfo;
	class GameComponent;
	class SimpleCamera;
	class Vector3;
}

namespace BEbraEngine {


	class GameObjectFactory : public IVisitorGameComponentDestroyer {
	public:
		//TODO: бля, ну мне кажется это будем единственным хуем торчащим, 
		//т.к плодить методы на каждый новый объект в движке ну хуй знает
		//хотя по сути я делаю монструозным параметры конструктора... ну тип
		//хотя можно унифицировать создание этих объектов и плесать от одного единственного метода. хуй.(одно и тоже написал пока думал)
		optional<shared_ptr<GameComponent>> create(const GameComponentCreateInfo& info);

		void destroy(GameComponent* object);

		void destroy(GameObject* object);

		shared_ptr<PointLight> createLight(const Vector3& position);

		shared_ptr<DirectionLight> createDirLight(const Vector3& direction);

		shared_ptr<SimpleCamera> createCamera(const Vector3& position);

		void setModel(GameObject* object, const std::string& path);

		void destroyCamera(SimpleCamera* camera);

		void destroyPointLight(PointLight* light);

		GameObjectFactory(shared_ptr<AbstractRender> render, shared_ptr<Physics> physics);

		~GameObjectFactory();
	private:

		void destroyGameObject(GameObject* comp) override;

		void destroyRenderComponent(RenderObject* comp) override;

		void destroyRigidBodyComponent(RigidBody* comp) override;

		void destroyColliderComponent(Collider* comp) override;

		void destroyMaterialComponent(Texture* comp) override;

		void destroyTransformComponent(Transform* comp) override;

		void destroyPointLightComponent(PointLight* comp) override;

		void destroyDirectionLightComponent(DirectionLight* comp) override;

		void destroyCameraComponent(SimpleCamera* comp) override;

	private:
		unique_ptr<TransformFactory> transFactory;
		IRenderObjectFactory* renderFactory;
		ColliderFactory* colliderFactory;
		RigidBodyFactory* rigidBodyFactory;

	};

}