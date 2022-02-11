#pragma once
#define GLM_FORCE_XYZW_ONLY

#include <glm/glm.hpp>
#include <array>
#include "Vector4.hpp"
#ifdef _WIN64
#include <DirectXMath.h>
#endif
namespace BEbraEngine {
	class Matrix4 {
	public:

		Vector4& operator[](size_t i) {
			return elements[i];
		}
#ifdef _WIN64
		 operator DirectX::XMMATRIX&() {
			auto& v0 = elements[0];
			auto& v1 = elements[1];
			auto& v2 = elements[2];
			auto& v3 = elements[3];
			auto _mat = DirectX::XMMATRIX(
				v0.x,v0.y, v0.z, v0.w,
				v1.x, v1.y, v1.z, v1.w,
				v2.x, v2.y, v2.z, v2.w,
				v3.x, v3.y, v3.z, v3.w
			);
			return _mat;
		}
#endif
		Matrix4() {}
		Matrix4(const glm::mat4& mat) {
			elements[0] = mat[0];
			elements[1] = mat[1];
			elements[2] = mat[2];
			elements[3] = mat[3];
		}
		Matrix4(float all) {
			elements[0] = Vector4(all);
			elements[1] = Vector4(all);
			elements[2] = Vector4(all);
			elements[3] = Vector4(all);
		}
		operator glm::mat4 () {
			return glm::mat4(
				elements[0], 
				elements[1], 
				elements[2], 
				elements[3]);
		}
		Matrix4 operator*(const Matrix4& other) {
			const glm::mat4& pizda = *this;
			//В чём смысл кастить? а мне похуй, по приколу
			glm::mat4 pizda1 = const_cast<Matrix4&>(other);
			auto pizda228_1337 = pizda * pizda1;
			return Matrix4(pizda228_1337);
		}
		Vector4 operator*(const Vector4& other) {
			const glm::mat4& pizda = *this;
			return Vector4(pizda * other);
		}
		bool operator==(const Matrix4& other) noexcept {
			if (this->elements[0] == other.elements[0]
				&& this->elements[1] == other.elements[1]
				&& this->elements[2] == other.elements[2]
				&& this->elements[3] == other.elements[3])
				return true;
			return false;
		}
		bool operator!=(const Matrix4& other) noexcept {
			return !(*this == other);
		}
	private:
		Vector4 elements[4];
	};
}