#pragma once
#define GLM_FORCE_XYZW_ONLY
#include <glm/vec3.hpp>
#ifdef _WIN64
#include <DirectXMath.h>
#endif
namespace BEbraEngine {

	class Vector2
	{
	public:
		float x{}, y{};
	public:
		Vector2(float x, float y) : x(x), y(y) { }

		Vector2(const Vector2& other) : x(other.x), y(other.y) { }

		Vector2(const glm::vec2& other) : x(other.x), y(other.y) { }

		Vector2(float all) : x(all), y(all) { }

		Vector2() { }

		operator glm::vec2() const noexcept { return glm::vec2(x, y); }
#ifdef _WIN64
		Vector2(const DirectX::XMFLOAT2& vec) : x(vec.x), y(vec.y) { }

		operator DirectX::XMFLOAT2() const noexcept { return DirectX::XMFLOAT2(x, y); }
#endif

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

		Vector2& operator*=(const Vector2& other) noexcept {
			*this = *this * other;
			return *this;
		}

		Vector2& operator+=(const Vector2& other) noexcept {
			*this = *this + other;
			return *this;
		}

		Vector2& operator-=(const Vector2& other) noexcept {
			*this = *this - other;
			return *this;
		}

		bool operator==(const Vector2& other) const noexcept {
			return (this->x == other.x) &&
				(this->y == other.y);
		}

		bool operator!=(const Vector2& other) const noexcept {
			return !(*this == other);
		}
	};
}