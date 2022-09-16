#define GLM_FORCE_XYZW_ONLY
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

module Vector2;

namespace BEbraEngine {

	Vector2 Vector2::operator+(const Vector2& other) const noexcept {
		glm::vec2 l = glm::vec2(this->x, this->y);
		glm::vec2 r = glm::vec2(other.x, other.y);
		auto result = l + r;
		return Vector2(result.x, result.y);
	}

	Vector2 Vector2::operator-(const Vector2& other) const noexcept
	{
		glm::vec2 l = glm::vec2(this->x, this->y);
		glm::vec2 r = glm::vec2(other.x, other.y);
		auto result = l - r;
		return Vector2(result.x, result.y);
	}

	Vector2 Vector2::operator*(const Vector2& other) const noexcept
	{
		glm::vec2 l = glm::vec2(this->x, this->y);
		glm::vec2 r = glm::vec2(other.x, other.y);
		auto result = l * r;
		return Vector2(result.x, result.y);
	}

	Vector2 Vector2::operator*(float scalar) const noexcept
	{
		glm::vec2 l = glm::vec2(this->x, this->y);
		auto result = l * scalar;
		return Vector2(result.x, result.y);
	}

	Vector2& Vector2::operator*=(const Vector2& other) noexcept
	{
		*this = *this * other;
		return *this;
	}

	Vector2& Vector2::operator+=(const Vector2& other) noexcept
	{
		*this = *this + other;
		return *this;
	}

	Vector2& Vector2::operator-=(const Vector2& other) noexcept
	{
		*this = *this - other;
		return *this;
	}

	bool Vector2::operator==(const Vector2& other) const noexcept
	{
		return (this->x == other.x) &&
				(this->y == other.y);
	}

	bool Vector2::operator!=(const Vector2& other) const noexcept
	{
		return !(*this == other);
	}

}