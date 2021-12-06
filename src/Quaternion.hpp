#pragma once
#include <glm/gtc/quaternion.hpp>
namespace BEbraEngine {
	class Quaternion {
	public:
		float x{}, y{}, z{}, w{};
		Quaternion(const glm::quat& other) : x(other.x), y(other.y), z(other.z), w(other.w) { }
		Quaternion(const Quaternion& other) : x(other.x), y(other.y), z(other.z), w(other.w) { }

	};
}