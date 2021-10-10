#pragma once
#include <glm/glm.hpp>
#include "Physics/btBulletCollisionCommon.h"
//#include "btBulletCollisionCommon.h"
namespace BEbraEngine {


	class Vector
	{
	public:
		float x;
		float y;
		float z;
		float w;
	public:
		Vector(float x, float y, float z, float w) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		Vector(float x, float y, float z) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = 0;
		}
		Vector(float all) {
			this->x = all;
			this->y = all;
			this->z = all;
			this->w = all;
		}
		Vector(float x, float y) {
			this->x = x;
			this->y = y;
			this->z = 0;
			this->w = 0;
		}
		Vector(const glm::vec3& vec) {
			x = vec.x;
			y = vec.y;
			z = vec.z;
			w = 0;
		}
		Vector(const glm::vec2& vec) {
			x = vec.x;
			y = vec.y;
			z = 0;
			w = 0;
		}
		Vector(const glm::vec4& vec) {
			x = vec.x;
			y = vec.y;
			z = vec.z;
			w = vec.w;
		}
		Vector(const btVector3& vec) {
			x = vec.x();
			y = vec.y();
			z = vec.z();
			w = 0;
		}
		Vector(const btVector4& vec) {
			x = vec.x();
			y = vec.y();
			z = vec.z();
			w = vec.w();
		}
		Vector() {
			x = 0;
			y = 0;
			z = 0;
			w = 0;
		}
		operator glm::vec3() const noexcept {
			return glm::vec3(x, y, z);
		}
		operator glm::vec4() const noexcept {
			return glm::vec4(x, y, z, w);
		}
		operator glm::vec2() const noexcept {
			return glm::vec2(x, y);
		}
		operator btVector3() const noexcept {
			return btVector3(x, y, z);
		}
		operator btVector4() const noexcept {
			return btVector4(x, y, z, w);
		}
		Vector operator+(const Vector& other) const noexcept {
			glm::vec4 l = *this;
			glm::vec4 r = other;
			return Vector(l + r);
		}
		Vector operator-(const Vector& other) const noexcept {
			glm::vec4 l = *this;
			glm::vec4 r = other;
			return Vector(l - r);
		}
		Vector operator*(const Vector& other) const noexcept {
			glm::vec4 l = *this;
			glm::vec4 r = other;
			return Vector(l * r);
		}
		Vector operator*(float scalar) const noexcept {
			glm::vec4 l = *this;
			return Vector(l * scalar);
		}

	};
}


