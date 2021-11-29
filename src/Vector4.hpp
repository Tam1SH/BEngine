#pragma once
#define GLM_FORCE_XYZW_ONLY
#include <glm/vec3.hpp>
#include <Physics/LinearMath/btVector3.h>
#ifdef _WIN64
#include <DirectXMath.h>
#endif
namespace BEbraEngine {


	class Vector4
	{
	public:
		float x;
		float y;
		float z;
		float w;
	public:
		Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }
		Vector4(const Vector4& other) : x(other.x), y(other.y), z(other.z), w(other.w) { }
		Vector4(const glm::vec4& other) : x(other.x), y(other.y), z(other.z), w(other.w) { }

		Vector4(float x, float y, float z) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = 0;
		}

		Vector4(float x, float y) {
			this->x= x;
			this->y = y;
			this->z = 0;
			this->w = 0;
		}
		Vector4(float* array) {
			this->x = array[0];
			this->y = array[1];
			this->z = array[2];
			this->w = array[3];
		}
		Vector4(float all) {
			this->x = all;
			this->y = all;
			this->z = all;
			this->w = all;
		}

		Vector4(const glm::vec3& vec) {
			x = vec.x;
			y = vec.y;
			z = vec.z;
			w = 0;
		}
		Vector4(const glm::vec2& vec) {
			x = vec.x;
			y = vec.y;
			z = 0;
			w = 0;
		}

		Vector4(const btVector3& vec) {
			x = vec.x();
			y = vec.y();
			z = vec.z();
			w = 0;
		}

		Vector4(const btVector4& vec) {
			x = vec.x();
			y = vec.y();
			z = vec.z();
			w = vec.w();
		}

		Vector4() {
			x = 0;
			y = 0;
			z = 0;
			w = 0;
		}

		operator glm::vec4() const noexcept {
			return glm::vec4(x, y, z, w);
		}

		operator glm::vec3() const noexcept {
			return glm::vec3(x, y, z);
		}

		operator glm::vec2() const noexcept {
			return glm::vec2(x, y);
		}

		operator btVector4() const noexcept {
			return btVector4(x, y, z, w);
		}

		operator btVector3() const noexcept {
			return btVector3(x, y, z);
		}
#ifdef _WIN64
		Vector4(const DirectX::XMFLOAT4& vec) {
			x = vec.x;
			y = vec.y;
			z = vec.z;
			w = vec.w;
		}

		operator DirectX::XMFLOAT4() const noexcept {
			return DirectX::XMFLOAT4(x, y, z, w);
		}
#endif

		Vector4 operator+(const Vector4& other) const noexcept {
			glm::vec4 l = *this;
			glm::vec4 r = other;
			return Vector4(l + r);
		}

		Vector4 operator-(const Vector4& other) const noexcept {
			glm::vec4 l = *this;
			glm::vec4 r = other;
			return Vector4(l - r);
		}

		Vector4 operator*(const Vector4& other) const noexcept {
			glm::vec4 l = *this;
			glm::vec4 r = other;
			return Vector4(l * r);
		}

		Vector4 operator*(float scalar) const noexcept {
			glm::vec4 l = *this;
			return Vector4(l * scalar);
		}
		Vector4& operator*=(const Vector4& other) noexcept {
			auto xyu = *this * other;
			*this = xyu;
			return *this;
		}
		Vector4& operator*=(float other) noexcept {
			auto xyu = *this * other;
			*this = xyu;
			return *this;
		}
		Vector4& operator+=(const Vector4& other) noexcept {
			*this = *this + other;
			return *this;
		}
		Vector4& operator-=(const Vector4& other) noexcept {
			*this = *this - other;
			return *this;
		}
		bool operator==(const Vector4& other) noexcept {
			if(this->x == other.x
			&& this->y == other.y
			&& this->z == other.z
			&& this->w == other.w)
				return true;
			return false;
		}
		bool operator!=(const Vector4& other) noexcept {
			return !(*this == other);
		}
	};
	
}


