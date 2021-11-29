#pragma once
#define GLM_FORCE_XYZW_ONLY
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec3.hpp>
#include <Physics/LinearMath/btVector3.h>
#ifdef _WIN64
#include <DirectXMath.h>
#endif
namespace BEbraEngine {

	class Vector3
	{
	public:
		float x, y, z;
	public:
		Vector3() {}

		Vector3(float x, float y, float z) : x(x), y(y), z(z) { }

		Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z) { }

		Vector3(const glm::vec3& other) : x(other.x), y(other.y), z(other.z) { }

		Vector3(float x, float y) : x(x), y(y), z(0) { }

		Vector3(float all) : x(all), y(all), z(all) { }

		Vector3(const btVector3& vec) : x(vec.x()), y(vec.y()), z(vec.z()) { }

		operator glm::vec3() const noexcept { return glm::vec3(x, y, z); }

		operator btVector3() const noexcept { return btVector3(x, y, z); }

#ifdef _WIN64
		Vector3(const DirectX::XMFLOAT3& vec) : x(vec.x), y(vec.y), z(vec.z) { } 

		operator DirectX::XMFLOAT3() const noexcept { return DirectX::XMFLOAT3(x, y, z); }
#endif

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

		Vector3& operator*=(const Vector3& other) noexcept {
			*this = *this * other;
			return *this;
		}

		Vector3& operator+=(const Vector3& other) noexcept {
			*this = *this + other;
			return *this;
		}

		Vector3& operator-=(const Vector3& other) noexcept {
			*this = *this - other;
			return *this;
		}

	};
}