#pragma once
#include <glm/glm.hpp>
#include "btBulletCollisionCommon.h"
namespace BEbraEngine {

	class Vector3
	{
	public:
		float x;
		float y;
		float z;
	public:
		Vector3(float x, float y, float z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}

		Vector3(float x, float y) {
			this->x = x;
			this->y = y;
			this->z = 0;
		}

		Vector3(float all) {
			this->x = all;
			this->y = all;
			this->z = all;
		}

		Vector3(const glm::vec3& vec) {
			x = vec.x;
			y = vec.y;
			z = vec.z;
		}

		Vector3(const btVector3& vec) {
			x = vec.x();
			y = vec.y();
			z = vec.z();
		}

		Vector3() {
			x = 0;
			y = 0;
			z = 0;
		}

		operator glm::vec3() const noexcept {
			return glm::vec3(x, y, z);
		}

		operator btVector3() const noexcept {
			return btVector3(x, y, z);
		}

		Vector3 operator+(const Vector3& other) const noexcept {
			glm::vec3 l = *this;
			glm::vec3 r = other;
			return Vector3(l + r);
		}

		Vector3 operator-(const Vector3& other) const noexcept {
			glm::vec3 l = *this;
			glm::vec3 r = other;
			return Vector3(l - r);
		}

		Vector3 operator*(const Vector3& other) const noexcept {
			glm::vec3 l = *this;
			glm::vec3 r = other;
			return Vector3(l * r);
		}

		Vector3 operator*(float scalar) const noexcept {
			glm::vec3 l = *this;
			return Vector3(l * scalar);
		}

	};
}