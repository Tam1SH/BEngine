#pragma once
#include <glm/gtc/quaternion.hpp>
#include "Vector4.hpp"
#include <btBulletCollisionCommon.h>
namespace BEbraEngine {
	class Quaternion {
	public:
		float x{}, y{}, z{}, w{};
		Quaternion() {}
		Quaternion(const glm::quat& other) : x(other.x), y(other.y), z(other.z), w(other.w) { }
		Quaternion(const Quaternion& other) : x(other.x), y(other.y), z(other.z), w(other.w) { }
		Quaternion(const Vector4& other) : x(other.x), y(other.y), z(other.z), w(other.w) { }

		operator glm::quat() const noexcept {
			return glm::quat(w, x, y, z);
		}

		operator btQuaternion() const noexcept {
			return btQuaternion(x, y, z, w);
		}
	};
}