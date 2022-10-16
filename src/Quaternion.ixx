module;
#include <glm/gtc/quaternion.hpp>
#include <btBulletCollisionCommon.h>
export module Quaternion;
import Vector4;

namespace BEbraEngine {
	export struct Quaternion {

		Quaternion() {}
		Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }
		Quaternion(const glm::quat& other) : x(other.x), y(other.y), z(other.z), w(other.w) { }
		Quaternion(const Quaternion& other) : x(other.x), y(other.y), z(other.z), w(other.w) { }
		Quaternion(const Vector4& other) : x(other.x), y(other.y), z(other.z), w(other.w) { }
		Quaternion(const btQuaternion& other) : x(other.x()), y(other.y()), z(other.z()), w(other.w()) { }
		operator glm::quat() const noexcept {
			return glm::quat(w, x, y, z);
		}

		operator btQuaternion() const noexcept {
			return btQuaternion(x, y, z, w);
		}
	public:
		float x{}, y{}, z{}, w{};
	};
}