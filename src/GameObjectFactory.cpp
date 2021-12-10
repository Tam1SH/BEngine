#include "stdafx.h"
#define NOMINMAX
#include "GameObjectFactory.hpp"
#include "TransformFactory.hpp"
#include "VulkanRenderObjectFactory.hpp"
#include "GameObject.hpp"
#include "RigidBoby.hpp"
#include "RenderObject.hpp"
#include "Transform.hpp"
#include "VulkanRender.hpp"
#include "Physics.hpp"
#include "WorkSpace.hpp"
#include "Collider.hpp"
#include "AbstractRender.hpp"
#include "Camera.hpp"
namespace BEbraEngine {
	GameObjectFactory::GameObjectFactory(std::shared_ptr<AbstractRender> render, std::shared_ptr<Physics> physics)
		: render(render), physics(physics)
	{

		renderFactory = render->getRenderObjectFactory();
		renderFactory->setContext(render.get());

		colliderFactory = physics->getColliderFactory();
		rigidBodyFactory = physics->getRigidBodyFactory();
		transFactory = std::unique_ptr<TransformFactory>(new TransformFactory());
		Debug::enableAll();
		//Debug::disableLog(Debug::ObjectType::Collider);
		//Debug::disableLog(Debug::ObjectType::Transform);
		//Debug::disableLog(Debug::ObjectType::RigidBody);
		//Debug::disableLog(Debug::ObjectType::RenderObject);
	}
	std::shared_ptr<GameObject> GameObjectFactory::create(const Vector3& position)
	{
		auto opt_renderObj = renderFactory->createObject();
		if (opt_renderObj.has_value()) {
			auto obj = new GameObject();
			auto name = obj->getName();

			obj->setName(name + std::to_string(workspace->getSize()));

			ColliderInfo info;
			info.scale = Vector3(1);
			info.position = position;
			auto collider = std::shared_ptr<Collider>(colliderFactory->create(&info));
			auto transform = std::shared_ptr<Transform>(transFactory->create(position));
			auto renderObj = std::shared_ptr<RenderObject>(opt_renderObj.value());
			auto rigidbody = std::shared_ptr<RigidBody>(rigidBodyFactory->create(collider.get()));

			renderFactory->bindTransform(renderObj, transform);

			rigidbody->setTransform(transform);

			obj->addComponent(renderObj);
			obj->addComponent(rigidbody);
			obj->addComponent(transform);
			obj->addComponent(collider);
			btTransform trans;
			trans.setIdentity();
			trans.setOrigin(btVector3(position.x, position.y, position.z));
			rigidbody->getRigidBody()->setWorldTransform(trans);

			render->addObject(renderObj);
			physics->addRigidBody(rigidbody);

			return std::shared_ptr<GameObject>(obj);
		}
		else
			return std::shared_ptr<GameObject>();


	}

	std::shared_ptr<PointLight> GameObjectFactory::createLight(const Vector3& position)
	{
		auto transform = std::shared_ptr<Transform>(transFactory->create(position));
		auto light = std::shared_ptr<PointLight>(renderFactory->createLight(Vector3(1), position));
		light->addComponent(transform);

		auto name = light->getName();

		light->setName(name + std::to_string(workspace->getSize()));
		//workspace->addComponent(light);
		renderFactory->bindTransform(light, transform);

		light->update();
		render->addLight(light);
		return light;
	}

	std::shared_ptr<DirectionLight> GameObjectFactory::createDirLight(const Vector3& direction)
	{
		auto light = std::shared_ptr<DirectionLight>(renderFactory->createDirLight(Vector3(0.1f), direction));

		auto name = light->getName();

		light->setName(name + std::to_string(workspace->getSize()));
		workspace->addComponent(light);

		render->addGlobalLight(light);
		return light;
	}

	void GameObjectFactory::setModel(GameObject* object, const std::string& path)
	{
		renderFactory->setModel(object->getComponent<RenderObject>().get(), path);
	}

	void GameObjectFactory::destroyObject(GameObject* object)
	{
		renderFactory->destroyObject(object->getComponent<RenderObject>());
		physics->removeRigidBody(object->getComponent<RigidBody>());
	}

	void GameObjectFactory::destroyObject(std::shared_ptr<GameObject> object)
	{
		auto begin = workspace->GetList().begin();
		auto end = workspace->GetList().end();

		render->removeObject(object->getComponent<RenderObject>());
		physics->removeRigidBody(object->getComponent<RigidBody>());
		colliderFactory->destroyCollider(object->getComponent<Collider>());
#ifdef _DEBUG
		object->isDestroyed = true;
#endif // _DEBUG


	}

	void GameObjectFactory::destroyPointLight(std::shared_ptr<PointLight> light)
	{
		light->release();
		renderFactory->destroyPointLight(light);
	}

	void GameObjectFactory::SetWorkSpace(std::shared_ptr<WorkSpace> workspace)
	{
		this->workspace = workspace;
	}

	GameObjectFactory::~GameObjectFactory()
	{
	}
	std::shared_ptr<Camera> GameObjectFactory::createCamera(const Vector3& position)
	{
		auto camera = std::shared_ptr<Camera>(renderFactory->createCamera(position));
		render->addCamera(camera);
		render->selectMainCamera(camera.get());
		return camera;
	}
	void GameObjectFactory::destroyCamera(std::shared_ptr<Camera> camera)
	{
	}
}