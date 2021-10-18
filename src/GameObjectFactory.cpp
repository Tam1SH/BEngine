#include "GameObjectFactory.hpp"
#include "TransformFactory.h"
#include "RenderObjectCreator.hpp"
#include "GameObject.hpp"
#include "RigidBoby.hpp"
#include "RenderObject.h"
#include "Transform.hpp"
#include "VulkanRender.h"
#include "Render.h"
#include "Physics.hpp"
#include "WorkSpace.h"
//TODO: пересмотреть инициализацию объектов полностью.
namespace BEbraEngine {
	GameObjectFactory::GameObjectFactory(std::shared_ptr<Render> render, std::shared_ptr<Physics> physics)
		: render(render), physics(physics)
	{
		renderFactory = std::unique_ptr<RenderObjectFactory>(new RenderObjectFactory(render->render));
		transFactory = std::unique_ptr<TransformFactory>(new TransformFactory());

		GameObject::SetFactory(this);
	}
	std::shared_ptr<GameObject> GameObjectFactory::Create(glm::vec3 position)
	{
		auto obj = std::shared_ptr<GameObject>(new GameObject());
		auto name = obj->GetName();

		obj->SetName(name + std::to_string(workspace->GetSize()));
		workspace->AddComponent(obj);


		auto transform = std::shared_ptr<Transform>(Transform::New());
		auto renderObj = std::shared_ptr<RenderObject>(RenderObject::New(transform));
		auto rigidbody = std::shared_ptr<RigidBody>(new RigidBody());

		rigidbody->SetTransform(transform);

		obj->AddComponent(renderObj);
		obj->AddComponent(rigidbody);
		obj->AddComponent(transform);

		btTransform trans;
		trans.setIdentity();
		trans.setOrigin(btVector3(position.x, position.y, position.z));
		rigidbody->GetRigidBody()->setWorldTransform(trans);

		render->AddRenderObject(renderObj);
		physics->AddObject(rigidbody);

		return obj;
	}

	void GameObjectFactory::Destroy(GameObject* object)
	{
	}

	void GameObjectFactory::Destroy(std::shared_ptr<GameObject> object)
	{
		auto begin = workspace->GetList().begin();
		auto end = workspace->GetList().end();

		if (workspace->GetSize() != 0) {
			workspace->GetList().erase(
				std::remove_if(begin, end,
					[&](std::shared_ptr<AbstractComponent> component) {
						if (component.get() == object.get()) {
							std::cout << "GAMEOBJECT FOUNDED" << std::endl;
							return true;
						}
						return false;
					})
			);
		}
	}

	void GameObjectFactory::SetWorkSpace(std::shared_ptr<WorkSpace> workspace)
	{
		this->workspace = workspace;
	}

	GameObjectFactory::~GameObjectFactory()
	{
	}
}