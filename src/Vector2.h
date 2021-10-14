#pragma once
#include <glm/glm.hpp>
namespace BEbraEngine {

	class Vector2
	{
	public:
		float x;
		float y;
	public:

		Vector2(float x, float y) {
			this->x = x;
			this->y = y;
		}

		Vector2(float all) {
			this->x = all;
			this->y = all;
		}

		Vector2(const glm::vec2& vec) {
			x = vec.x;
			y = vec.y;
		}

		Vector2() {
			x = 0;
			y = 0;
		}

		operator glm::vec2() const noexcept {
			return glm::vec2(x, y);
		}

		Vector2 operator+(const Vector2& other) const noexcept {
			glm::vec2 l = *this;
			glm::vec2 r = other;
			return Vector2(l + r);
		}

		Vector2 operator-(const Vector2& other) const noexcept {
			glm::vec2 l = *this;
			glm::vec2 r = other;
			return Vector2(l - r);
		}

		Vector2 operator*(const Vector2& other) const noexcept {
			glm::vec2 l = *this;
			glm::vec2 r = other;
			return Vector2(l * r);
		}

		Vector2 operator*(float scalar) const noexcept {
			glm::vec2 l = *this;
			return Vector2(l * scalar);
		}

	};
}