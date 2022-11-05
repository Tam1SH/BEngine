#define GLM_FORCE_XYZW_ONLY

#include <glm/vec4.hpp>
module Vector4;

namespace BEbraEngine {
	Vector4 Vector4::operator+(const Vector4& other) noexcept {
		glm::vec4 l = glm::vec4(this->x, this->y, this->z, this->w);
		glm::vec4 r = glm::vec4(other.x, other.y, other.z, other.w);
		auto result = l + r;
		return Vector4(result.x, result.y, result.z, result.w);
	}

	Vector4 Vector4::operator-(const Vector4& other) noexcept
	{
		glm::vec4 l = glm::vec4(this->x, this->y, this->z, this->w);
		glm::vec4 r = glm::vec4(other.x, other.y, other.z, other.w);
		auto result = l - r;
		return Vector4(result.x, result.y, result.z, result.w);
	}

	Vector4 Vector4::operator*(const Vector4& other) noexcept
	{
		glm::vec4 l = glm::vec4(this->x, this->y, this->z, this->w);
		glm::vec4 r = glm::vec4(other.x, other.y, other.z, other.w);
		auto result = l * r;
		return Vector4(result.x, result.y, result.z, result.w);
	}

	Vector4 Vector4::operator*(float scalar) noexcept
	{
		glm::vec4 l = glm::vec4(this->x, this->y, this->z, this->w);
		auto result = l * scalar;
		return Vector4(result.x, result.y, result.z, result.w);
	}

	Vector4& Vector4::operator*=(const Vector4& other) noexcept
	{
		auto xyu = *this * other;
		*this = xyu;
		return *this;
	}

	Vector4& Vector4::operator*=(float other) noexcept
	{
		auto xyu = *this * other;
		*this = xyu;
		return *this;
	}

	Vector4& Vector4::operator+=(const Vector4& other) noexcept
	{
		*this = *this + other;
		return *this;
	}

	Vector4& Vector4::operator-=(const Vector4& other) noexcept
	{
		*this = *this - other;
		return *this;
	}

	bool Vector4::operator==(const Vector4& other) const noexcept
	{
		return (this->x == other.x
			&& this->y == other.y
			&& this->z == other.z
			&& this->w == other.w);
	}

	bool Vector4::operator!=(const Vector4& other) const noexcept
	{
		return !(*this == other);
	}
}