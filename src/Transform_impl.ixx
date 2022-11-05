export module Transform_impl;
import Transform;
import BEbraMath;

//import GameComponentDestroyer;

namespace BEbraEngine {

	void Transform::setPosition(const Vector3& position) noexcept
	{
		this->position = position;
	}
	void Transform::setScale(const Vector3& scale) noexcept
	{
		this->scale = scale;
	}
	void Transform::setRotation(const Quaternion& quat) noexcept
	{
		this->quat = quat;
	}
	Vector3 Transform::getPosition() const noexcept
	{
		return position;
	}
	Quaternion Transform::getRotation() const noexcept
	{
		return quat;
	}
	Matrix4 Transform::getBasis() const noexcept
	{

		auto model = Matrix4(1);

		model = BEbraMath::translate(model, position);
		model = BEbraMath::scale(model, scale);

		model *= BEbraMath::toMat4(quat);

		return Matrix4(model);
	}
	Transform::Transform(const Vector3& position)
	{
		this->position = position;
		scale = Vector3(1);
	}
}