#pragma once
#define GLM_FORCE_XYZW_ONLY
#include <glm/glm.hpp>
#include "btBulletCollisionCommon.h"
#ifdef _WIN64
#include <DirectXMath.h>
#endif
namespace BEbraEngine {


	class Vector4
	{
	public:
		float f[4];
	public:
		Vector4(float x, float y, float z, float w) {
			this->f[0]= x;
			this->f[1] = y;
			this->f[2] = z;
			this->f[3] = w;
		}

		Vector4(float x, float y, float z) {
			this->f[0] = x;
			this->f[1] = y;
			this->f[2] = z;
			this->f[3] = 0;
		}

		Vector4(float x, float y) {
			this->f[0] = x;
			this->f[1] = y;
			this->f[2] = 0;
			this->f[3] = 0;
		}
		Vector4(float* array) {
			this->f[0] = array[0];
			this->f[1] = array[1];
			this->f[2] = array[2];
			this->f[3] = array[3];
		}
		Vector4(float all) {
			this->f[0] = all;
			this->f[1] = all;
			this->f[2] = all;
			this->f[3] = all;
		}

		Vector4(const glm::vec4& vec) {
			f[0] = vec.x;
			f[1] = vec.y;
			f[2] = vec.z;
			f[3] = vec.w;
		}

		Vector4(const glm::vec3& vec) {
			f[0] = vec.x;
			f[1] = vec.y;
			f[2] = vec.z;
			f[3] = 0;
		}
		Vector4(const glm::vec2& vec) {
			f[0] = vec.x;
			f[1] = vec.y;
			f[2] = 0;
			f[3] = 0;
		}

		Vector4(const btVector3& vec) {
			f[0] = vec.x();
			f[1] = vec.y();
			f[2] = vec.z();
			f[3] = 0;
		}

		Vector4(const btVector4& vec) {
			f[0] = vec.x();
			f[1] = vec.y();
			f[2] = vec.z();
			f[3] = vec.w();
		}

		Vector4() {
			f[0] = 0;
			f[1] = 0;
			f[2] = 0;
			f[3] = 0;
		}

		operator glm::vec4() const noexcept {
			return glm::vec4(f[0], f[1], f[2], f[3]);
		}

		operator glm::vec3() const noexcept {
			return glm::vec3(f[0], f[1], f[2]);
		}

		operator glm::vec2() const noexcept {
			return glm::vec2(f[0], f[1]);
		}

		operator btVector4() const noexcept {
			return btVector4(f[0], f[1], f[2], f[3]);
		}

		operator btVector3() const noexcept {
			return btVector3(f[0], f[1], f[2]);
		}
#ifdef _WIN64
		Vector4(const DirectX::XMFLOAT4& vec) {
			f[0] = vec.x;
			f[1] = vec.y;
			f[2] = vec.z;
			f[3] = vec.w;
		}

		operator DirectX::XMFLOAT4() const noexcept {
			return DirectX::XMFLOAT4(f);
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
			auto& xyu = *this * other;
			*this = xyu;
			return *this;
		}
		Vector4& operator*=(float other) noexcept {
			auto& xyu = *this * other;
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
		float& operator[](const size_t i) {
			return f[i];
		}
		bool operator==(const Vector4& other) noexcept {
			if(this->f[0] == other.f[0]
			&& this->f[1] == other.f[1]
			&& this->f[2] == other.f[2]
			&& this->f[3] == other.f[3])
				return true;
			return false;
		}
		bool operator!=(const Vector4& other) noexcept {
			return !(*this == other);
		}
	};
	
}


