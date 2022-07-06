module Collider;
namespace BEbraEngine {
	void Collider::setScale(const Vector3& size) noexcept
	{
		this->size = size;
		_collider->getCollisionShape()->setLocalScaling(size);
	}
	void Collider::setRotation(const Quaternion& quat) noexcept {
		btTransform trans;
		trans.setRotation(static_cast<btQuaternion>(quat));
		trans.setOrigin(position);
		_collider->setWorldTransform(trans);
	}

	void Collider::setPosition(const Vector3& position) noexcept
	{
		btTransform trans;
		trans.setOrigin(position);
		trans.setRotation(_collider->getWorldTransform().getRotation());
		_collider->setWorldTransform(trans);
	}

	void Collider::setMass(float mass) noexcept
	{
		//TODO: что это нахуй значит?
		auto vec = btVector3(0, 0, 0);
		_collider->getCollisionShape()->calculateLocalInertia(mass, vec);
	}

	Vector3 Collider::getPosition() const noexcept
	{
		return _collider->getWorldTransform().getOrigin();
	}

	void Collider::setRigidBody(RigidBody& body)
	{
		this->body = &body;
	}

	Collider::Collider() noexcept
	{
		name_ = "Collider";
	}

	Collider::~Collider()
	{
		//DEBUG_DESTROY_CHECK("Collider has not destroyed", this, "", Debug::ObjectType::Collider, Debug::MessageType::Info);
	}

	void Collider::destroy(IVisitorGameComponentDestroyer& destroyer)
	{
		//destroyer.destroyColliderComponent(*this);
	}
}