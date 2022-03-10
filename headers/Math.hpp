#pragma once

#include "Vector3.hpp"
#include "Vector2.hpp"
#include "Vector4.hpp"
#include "matrix.hpp"
#include "Quaternion.hpp"

namespace BEbraEngine {
	namespace BEbraMath {
		Vector3 normalize(const Vector3& vec) noexcept;
		Vector4 normalize(const Vector4& vec) noexcept;
		Vector2 normalize(const Vector2& vec) noexcept;
		float distance(const Vector2& left, const Vector2& right) noexcept;
		float distance(const Vector3& left, const Vector3& right) noexcept;
		float distance(const Vector4& left, const Vector4& right) noexcept;
		Vector4 clamp(const Vector4& x, const Vector4& minValue, const Vector4& maxValue);
		Vector3 clamp(const Vector3& x, const Vector3& minValue, const Vector3& maxValue);
		Vector2 clamp(const Vector2& x, const Vector2& minValue, const Vector2& maxValue);
		Vector4 clamp(const Vector4& x, float minValue, float maxValue);
		Vector2 clamp(const Vector2& x, float minValue, float maxValue);
		Vector3 cross(const Vector3& left, const Vector3& right);
		Quaternion toQuat(const Matrix4& mat);
		Matrix4 toMat4(const Quaternion& quat);
		Matrix4 scale(const Matrix4& mat, const Vector3& vec);
		Matrix4 translate(const Matrix4& mat, const Vector3& vec);
		float radians(float value);
		Matrix4 rotate(const Matrix4& mat, float angle, const Vector3& vec);
		Quaternion rotate(const Quaternion& quat, float angle, const Vector3& vec);
	}
}