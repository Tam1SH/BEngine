#include "stdafx.h"
#define NOMINMAX
#include "GameObjectFactory.hpp"
#include "TransformFactory.hpp"
#include "IRenderObjectFactory.hpp"
#include "GameObject.hpp"
#include "Physics.hpp"
#include "AbstractRender.hpp"



namespace BEbraEngine {

	GameObjectFactory::GameObjectFactory(shared_ptr<AbstractRender> render, shared_ptr<Physics> physics)
	{
		renderFactory = render->getRenderObjectFactory();
		colliderFactory = physics->getColliderFactory();
		rigidBodyFactory = physics->getRigidBodyFactory();
		transFactory = unique_ptr<TransformFactory>(new TransformFactory());
		Debug::enableAll();

	}

	optional<shared_ptr<GameComponent>> GameObjectFactory::create(const GameComponentCreateInfo& info)
	{
		shared_ptr<GameComponent> comp;

		optional<PointLight*> opt_light;
		optional<DirectionLight*> opt_dirLight;
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



		
		shared_ptr<RenderObject> renderObj;
		shared_ptr<Transform> transform;
		shared_ptr<Collider> collider;
		shared_ptr<RigidBody> rigidbody;



		comp = shared_ptr<GameComponent>(new GameObject());

		if (opt_renderObj.has_value()) {
			renderObj = shared_ptr<RenderObject>(opt_renderObj.value());
			comp->addComponent(renderObj);
		}

		if (opt_transform.has_value()) {
			transform = shared_ptr<Transform>(opt_transform.value());
			comp->addComponent(transform);
		}

		if (opt_renderObj.has_value() && opt_transform.has_value()) {
			renderFactory->bindTransform(renderObj, transform);
		}

		if (info.rigidBodyInfo) {
			collider = shared_ptr<Collider>(opt_collider.value());
			rigidbody = shared_ptr<RigidBody>(opt_rigidBody.value());
			rigidbody->setTransform(transform.get());
			comp->addComponent(collider);
			comp->addComponent(rigidbody);
		}

		if (opt_renderObj.has_value() && 
			opt_transform.has_value()) {

			return optional<shared_ptr<GameComponent>>(comp);
		}
		else {
			Debug::log("Can't create a object", 0, "Xyu znaet", Debug::ObjectType::GameObject, Debug::MessageType::Error);
			return optional<shared_ptr<GameComponent>>();
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

	void GameObjectFactory::destroy(GameComponent* object)
	{
		object->destroy(this);

		//renderFactory->destroyObject(object->getComponent<RenderObject>());
		//colliderFactory->destroyCollider(object->getComponent<Collider>().get());
		//rigidBodyFactory->destroy(object->getComponent<RigidBody>().get());


	}

	void GameObjectFactory::destroy(GameObject* object)
	{
		object->destroy(this);
	}

	void GameObjectFactory::destroyPointLight(PointLight* light)
	{
		light->release();
		renderFactory->destroyPointLight(light);
	}

	GameObjectFactory::~GameObjectFactory()
	{
	}

	void GameObjectFactory::destroyRenderComponent(RenderObject* comp)
	{
		renderFactory->destroyObject(comp);
#ifdef _DEBUG
		comp->isDestroyed = true;
#endif // _DEBUG
	}
	void GameObjectFactory::destroyRigidBodyComponent(RigidBody* comp)
	{
		rigidBodyFactory->destroy(comp);
#ifdef _DEBUG
		comp->isDestroyed = true;
#endif // _DEBUG
	}
	void GameObjectFactory::destroyColliderComponent(Collider* comp)
	{
		colliderFactory->destroyCollider(comp);
#ifdef _DEBUG
		comp->isDestroyed = true;
#endif // _DEBUG
	}
	void GameObjectFactory::destroyMaterialComponent(Texture* comp)
	{
#ifdef _DEBUG
		comp->isDestroyed = true;
#endif // _DEBUG
	}
	void GameObjectFactory::destroyTransformComponent(Transform* comp)
	{

	}
	void GameObjectFactory::destroyPointLightComponent(PointLight* comp)
	{
		renderFactory->destroyPointLight(comp);

	}
	void GameObjectFactory::destroyDirectionLightComponent(DirectionLight* comp)
	{
		//renderFactory->des

	}
	void GameObjectFactory::destroyCameraComponent(SimpleCamera* comp)
	{
		renderFactory->destroyCamera(comp);

	}
	void GameObjectFactory::destroyGameObject(GameObject* comp)
	{
#ifdef _DEBUG
		comp->isDestroyed = true;
#endif // _DEBUG
	}
	std::shared_ptr<SimpleCamera> GameObjectFactory::createCamera(const Vector3& position)
	{
		auto camera = shared_ptr<SimpleCamera>(renderFactory->createCamera(position));
	//	render->addCamera(camera);
	//	render->selectMainCamera(camera.get());
		return camera;
	}
	void GameObjectFactory::destroyCamera(SimpleCamera* camera)
	{
	}
}