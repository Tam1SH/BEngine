module;
export module BEbraMath;
import Vector2;
import Matrix4;
import Vector4;
import Quaternion;
import Vector3;


namespace BEbraEngine {
	export namespace BEbraMath {

		Vector3 normalize(const Vector3& vec) noexcept;

		Vector4 normalize(const Vector4& vec) noexcept;

		Vector2 normalize(const Vector2& vec) noexcept;

		float length(const Vector3& vec) noexcept;

		float distance(const Vector2& left, const Vector2& right) noexcept;

		float distance(const Vector3& left, const Vector3& right) noexcept;

		float distance(const Vector4& left, const Vector4& right) noexcept;

		Vector4 clamp(const Vector4& x, const Vector4& minValue, const Vector4& maxValue) noexcept;

		Vector3 clamp(const Vector3& x, const Vector3& minValue, const Vector3& maxValue) noexcept;

		Vector2 clamp(const Vector2& x, const Vector2& minValue, const Vector2& maxValue) noexcept;

		Vector4 clamp(const Vector4& x, float minValue, float maxValue) noexcept;

		Vector2 clamp(const Vector2& x, float minValue, float maxValue) noexcept;

		Vector3 cross(const Vector3& left, const Vector3& right) noexcept;

		Quaternion toQuat(const Matrix4& mat) noexcept;

		Matrix4 toMat4(const Quaternion& quat) noexcept;

		Matrix4 scale(const Matrix4& mat, const Vector3& vec) noexcept;

		Matrix4 translate(const Matrix4& mat, const Vector3& vec) noexcept;

		float radians(float value) noexcept;

		Matrix4 rotate(const Matrix4& mat, float angle, const Vector3& vec) noexcept;

		Quaternion rotate(const Quaternion& quat, float angle, const Vector3& vec) noexcept;

	}
}