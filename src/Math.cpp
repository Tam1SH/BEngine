#include "stdafx.h"
#include "Math.hpp"
#include <btBulletCollisionCommon.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
namespace BEbraEngine {
	namespace BEbraMath {
		
		Vector3 normalize(const Vector3& vec) noexcept
		{
			return glm::normalize(static_cast<glm::vec3>(vec));
		}

		Vector4 normalize(const Vector4& vec) noexcept
		{
			return glm::normalize(static_cast<glm::vec4>(vec));
		}

		Vector2 normalize(const Vector2& vec) noexcept
		{
			return glm::normalize(static_cast<glm::vec2>(vec));
		}

		float length(const Vector3& vec) noexcept
		{
			return glm::length(static_cast<glm::vec3>(vec));
		}

		float distance(const Vector2& left, const Vector2& right) noexcept
		{
			return glm::distance(static_cast<glm::vec2>(left), static_cast<glm::vec2>(right));
		}

		float distance(const Vector3& left, const Vector3& right) noexcept
		{
			return glm::distance(static_cast<glm::vec3>(left), static_cast<glm::vec3>(right));
		}

		float distance(const Vector4& left, const Vector4& right) noexcept
		{
			return glm::distance(static_cast<glm::vec4>(left), static_cast<glm::vec4>(right));
		}

		Vector4 clamp(const Vector4& x, const Vector4& minValue, const Vector4& maxValue)
		{
			return glm::clamp(static_cast<glm::vec4>(x), static_cast<glm::vec4>(minValue), static_cast<glm::vec4>(maxValue));
		}

		Vector3 clamp(const Vector3& x, const Vector3& minValue, const Vector3& maxValue)
		{
			return glm::clamp(static_cast<glm::vec3>(x), static_cast<glm::vec3>(minValue), static_cast<glm::vec3>(maxValue));
		}

		Vector2 clamp(const Vector2& x, const Vector2& minValue, const Vector2& maxValue)
		{
			return glm::clamp(static_cast<glm::vec2>(x), static_cast<glm::vec2>(minValue), static_cast<glm::vec2>(maxValue));
		}

		Vector4 clamp(const Vector4& x, float minValue, float maxValue)
		{
			return glm::clamp(static_cast<glm::vec4>(x), minValue, maxValue);
		}

		Vector2 clamp(const Vector2& x, float minValue, float maxValue)
		{
			return glm::clamp(static_cast<glm::vec2>(x), minValue, maxValue);
		}

		Vector3 cross(const Vector3& left, const Vector3& right)
		{
			return glm::cross(static_cast<glm::vec3>(left), static_cast<glm::vec3>(right));
		}
		Quaternion toQuat(const Matrix4& mat) {
			return glm::toQuat(static_cast<glm::mat4>(mat));
		}
		Matrix4 toMat4(const Quaternion& quat) {
			return glm::toMat4(static_cast<glm::quat>(quat));
		}
		Matrix4 scale(const Matrix4& mat, const Vector3& vec) {
			return glm::scale(static_cast<glm::mat4>(mat), static_cast<glm::vec3>(vec));
		}

		Matrix4 translate(const Matrix4& mat, const Vector3& vec)
		{
			return glm::translate(static_cast<glm::mat4>(mat), static_cast<glm::vec3>(vec));
		}

		float radians(float value)
		{
			return glm::radians(value);
		}

		Matrix4 rotate(const Matrix4& mat, float angle, const Vector3& vec)
		{
			return glm::rotate(static_cast<glm::mat4>(mat), angle, static_cast<glm::vec3>(vec));
		}

		Quaternion rotate(const Quaternion& quat, float angle, const Vector3& vec)
		{
			return glm::rotate(static_cast<glm::mat4>(toMat4(quat)), angle, static_cast<glm::vec3>(vec));
		}

	}
}

