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

using std::shared_ptr;
using std::unique_ptr;
using std::optional;
using std::string;

namespace BEbraEngine {

	GameObjectFactory::GameObjectFactory(shared_ptr<AbstractRender> render, shared_ptr<Physics> physics)
	{
		renderFactory = render->getRenderObjectFactory();
		colliderFactory = physics->getColliderFactory();
		rigidBodyFactory = physics->getRigidBodyFactory();
		transFactory = unique_ptr<TransformFactory>(new TransformFactory());
		Debug::enableAll();

	}

	optional<shared_ptr<GameObject>> GameObjectFactory::create(const GameObject::GameObjectCreateInfo& info)
	{
		optional<RenderObject*> opt_renderObj;
		optional<Collider*> opt_collider;
		optional<RigidBody*> opt_rigidBody;
		optional<Transform*> opt_transform;
		if (info.colliderInfo) {
	//		Collider::ColliderCreateInfo cinfo{};
		//	cinfo.scale = info.transformInfo->scale;
		///	cinfo.position = info.transformInfo->position;
		//	opt_collider = colliderFactory->create(cinfo);
		}
		if (info.rigidBodyInfo) {

			Collider::ColliderCreateInfo cinfo{};
			cinfo.scale = info.transformInfo->scale;
			cinfo.position = info.transformInfo->position;
			opt_collider = colliderFactory->create(cinfo);
			RigidBody::RigidBodyCreateInfo RigidBodyInfo{};
			RigidBodyInfo.position = info.transformInfo->position;
			if (opt_collider.has_value()) {
				RigidBodyInfo.collider = opt_collider.value();
			}

			opt_rigidBody = rigidBodyFactory->create(RigidBodyInfo);
		}

		if (info.renderInfo)
			opt_renderObj = renderFactory->create(*info.renderInfo);
		else {
			RenderObject::RenderObjectCreateInfo info{};
			opt_renderObj = renderFactory->create(info);
			Debug::log("renderInfo doesn't exist in GameObjectCreateInfo");
		}


		if (info.transformInfo)
			opt_transform = transFactory->create(*info.transformInfo);
		else {
			Transform::TransformCreateInfo info{};
			opt_transform = transFactory->create(info);
			Debug::log("transformInfo doesn't exist in GameObjectCreateInfo");
		}



		shared_ptr<GameObject> obj;
		shared_ptr<RenderObject> renderObj;
		shared_ptr<Transform> transform;
		shared_ptr<Collider> collider;
		shared_ptr<RigidBody> rigidbody;



		obj = shared_ptr<GameObject>(new GameObject());

		if (opt_renderObj.has_value()) {
			renderObj = shared_ptr<RenderObject>(opt_renderObj.value());
			obj->addComponent(renderObj);
		}

		if (opt_transform.has_value()) {
			transform = shared_ptr<Transform>(opt_transform.value());
			obj->addComponent(transform);
		}

		if (opt_renderObj.has_value() && opt_transform.has_value()) {
			renderFactory->bindTransform(renderObj, transform);

		}

		if (info.rigidBodyInfo) {
			collider = shared_ptr<Collider>(opt_collider.value());
			rigidbody = shared_ptr<RigidBody>(opt_rigidBody.value());
			rigidbody->setTransform(transform.get());
			obj->addComponent(collider);
			obj->addComponent(rigidbody);
		}

		if (opt_renderObj.has_value() && 
			opt_transform.has_value()) {

			return optional<shared_ptr<GameObject>>(obj);
		}
		else {
			Debug::log("Can't create a object", 0, "Xyu znaet", Debug::ObjectType::GameObject, Debug::MessageType::Error);
			return optional<shared_ptr<GameObject>>();
		}

	}

	shared_ptr<PointLight> GameObjectFactory::createLight(const Vector3& position)
	{
		Transform::TransformCreateInfo info{};
		info.position = position;
		auto transform = shared_ptr<Transform>(transFactory->create(info).value());
		auto light = shared_ptr<PointLight>(renderFactory->createLight(Vector3(1), position));
		light->addComponent(transform);

		auto name = light->getName();

		//light->setName(name + std::to_string(workspace->getSize()));
		//workspace->addComponent(light);
		renderFactory->bindTransform(light, transform);

		//light->update();
		//render->addLight(light);
		return light;
	}

	shared_ptr<DirectionLight> GameObjectFactory::createDirLight(const Vector3& direction)
	{
		auto light = shared_ptr<DirectionLight>(renderFactory->createDirLight(Vector3(0.1f), direction));

		auto name = light->getName();

		light->update();
		return light;
	}

	void GameObjectFactory::setModel(GameObject* object, const string& path)
	{
		renderFactory->setModel(object->getComponent<RenderObject>().get(), path);
	}

	void GameObjectFactory::destroyObject(shared_ptr<GameObject> object)
	{
		renderFactory->destroyObject(object->getComponent<RenderObject>());
		colliderFactory->destroyCollider(object->getComponent<Collider>().get());
		rigidBodyFactory->destroy(object->getComponent<RigidBody>().get());

#ifdef _DEBUG
		object->isDestroyed = true;
#endif // _DEBUG

	}

	void GameObjectFactory::destroyPointLight(shared_ptr<PointLight> light)
	{
		light->release();
		renderFactory->destroyPointLight(light);
	}

	void GameObjectFactory::SetWorkSpace(shared_ptr<WorkSpace> workspace)
	{
		//this->workspace = workspace;
	}

	GameObjectFactory::~GameObjectFactory()
	{
	}
	std::shared_ptr<Camera> GameObjectFactory::createCamera(const Vector3& position)
	{
		auto camera = shared_ptr<Camera>(renderFactory->createCamera(position));
	//	render->addCamera(camera);
	//	render->selectMainCamera(camera.get());
		return camera;
	}
	void GameObjectFactory::destroyCamera(shared_ptr<Camera> camera)
	{
	}
}