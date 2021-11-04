#include "stdafx.h"
#define NOMINMAX
#include "GameObjectFactory.hpp"
#include "TransformFactory.hpp"
#include "RenderObjectCreator.hpp"
#include "GameObject.hpp"
#include "RigidBoby.hpp"
#include "RenderObject.hpp"
#include "Transform.hpp"
#include "VulkanRender.hpp"
#include "Render.hpp"
#include "Physics.hpp"
#include "WorkSpace.hpp"
#include "AbstractRenderSystem.hpp"
//TODO: пересмотреть инициализацию объектов полностью.
namespace BEbraEngine {
	GameObjectFactory::GameObjectFactory(std::shared_ptr<AbstractRender> render, std::shared_ptr<Physics> physics)
		: render(render), physics(physics)
	{
		renderFactory = std::unique_ptr<VulkanRenderObjectFactory>(new VulkanRenderObjectFactory(std::static_pointer_cast<VulkanRender>(render)));
		transFactory = std::unique_ptr<TransformFactory>(new TransformFactory());

		GameObject::SetFactory(this);
	}
	std::shared_ptr<GameObject> GameObjectFactory::Create(const Vector3& position)
	{
		auto obj = std::shared_ptr<GameObject>(new GameObject());
		auto name = obj->GetName();

		obj->SetName(name + std::to_string(workspace->GetSize()));
		workspace->AddComponent(obj);


		auto transform = std::shared_ptr<Transform>(Transform::New());
		auto renderObj = std::shared_ptr<RenderObject>(renderFactory->createObject());
		auto rigidbody = std::shared_ptr<RigidBody>(new RigidBody());

		renderFactory->BindTransform(renderObj.get(), transform.get());

		rigidbody->SetTransform(transform);

		obj->AddComponent(renderObj);
		obj->AddComponent(rigidbody);
		obj->AddComponent(transform);

		btTransform trans;
		trans.setIdentity();
		trans.setOrigin(btVector3(position.x, position.y, position.z));
		rigidbody->GetRigidBody()->setWorldTransform(trans);
		render->AddObject(renderObj);
		physics->AddObject(rigidbody);

		return obj;
	}

	std::shared_ptr<Light> GameObjectFactory::createLight(const Vector3& position)
	{
		return std::shared_ptr<Light>(renderFactory->create(Vector3(1)));
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
					[&](std::shared_ptr<GameObjectComponent> component) {
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