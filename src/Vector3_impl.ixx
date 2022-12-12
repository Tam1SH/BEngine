export module Vector3_impl;
import Vector3;
#define GLM_FORCE_XYZW_ONLY
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec3.hpp>
namespace BEbraEngine {

	Vector3& Vector3::operator*=(const Vector3& other) noexcept {
		*this = *this * other;
		return *this;
	}

	Vector3& Vector3::operator+=(const Vector3& other) noexcept
	{
		*this = *this + other;
		return *this;
	}

	Vector3& Vector3::operator-=(const Vector3& other) noexcept
	{
		*this = *this - other;
		return *this;
	}

	bool Vector3::operator==(const Vector3& other) const noexcept
	{
		return (this->x == other.x) &&
			(this->y == other.y) &&
			(this->z == other.z);
	}

	bool Vector3::operator!=(const Vector3& other) const noexcept
	{
		return !(*this == other);
	}

	Vector3 Vector3::operator*(float scalar) const noexcept {
		glm::vec3 l = glm::vec3(this->x, this->y, this->z);
		auto result = l * scalar;
		return Vector3(result.x, result.y, result.z);

	}
	Vector3 Vector3::operator-(const Vector3& other) const noexcept {
		glm::vec3 l = glm::vec3(this->x, this->y, this->z);
		glm::vec3 r = glm::vec3(other.x, other.y, other.z);
		auto result = l - r;
		return Vector3(result.x, result.y, result.z);
	}

	Vector3 Vector3::operator*(const Vector3& other) const noexcept {

		glm::vec3 l = glm::vec3(this->x, this->y, this->z);
		glm::vec3 r = glm::vec3(other.x, other.y, other.z);
		auto result = l * r;
		return Vector3(result.x, result.y, result.z);
	}

	Vector3 Vector3::operator+(const Vector3& other) const noexcept {
		glm::vec3 l = glm::vec3(this->x, this->y, this->z);
		glm::vec3 r = glm::vec3(other.x, other.y, other.z);
		auto result = l + r;
		return Vector3(result.x, result.y, result.z);
	}
}