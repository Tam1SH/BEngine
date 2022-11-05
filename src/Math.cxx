#include <glm/ext/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
module BEbraMath;
import Vector3;
import Vector4;
import Matrix4;
import Vector2;
import Quaternion;

namespace BEbraEngine {

	Vector3 toVec3(glm::vec3 v) { return Vector3(v.x, v.y, v.z);}

	Vector2 toVec2(glm::vec2 v) { return Vector2(v.x, v.y); }

	Vector4 toVec4(glm::vec4 v) { return Vector4(v.x, v.y, v.z, v.w); }
	
	glm::vec3 gtoVec3(Vector3 v) { return glm::vec3(v.x, v.y, v.z); }
	
	glm::vec2 gtoVec2(Vector2 v) { return glm::vec2(v.x, v.y); }
	
	glm::vec4 gtoVec4(Vector4 v) { return glm::vec4(v.x, v.y, v.z, v.w); }

	Matrix4 toMat4(const glm::mat4& mat) {
		Vector4 v0 = Vector4(mat[0].x, mat[0].y, mat[0].z, mat[0].w);
		Vector4 v1 = Vector4(mat[1].x, mat[1].y, mat[1].z, mat[1].w);
		Vector4 v2 = Vector4(mat[2].x, mat[2].y, mat[2].z, mat[2].w);
		Vector4 v3 = Vector4(mat[3].x, mat[3].y, mat[3].z, mat[3].w);
		return Matrix4(v0, v1, v2, v3);
	}

	glm::mat4 gtoMat4(const Matrix4& mat) {
		glm::vec4 v0 = glm::vec4(mat.elements[0].x, mat.elements[0].y, mat.elements[0].z, mat.elements[0].w);
		glm::vec4 v1 = glm::vec4(mat.elements[1].x, mat.elements[1].y, mat.elements[1].z, mat.elements[1].w);
		glm::vec4 v2 = glm::vec4(mat.elements[2].x, mat.elements[2].y, mat.elements[2].z, mat.elements[2].w);
		glm::vec4 v3 = glm::vec4(mat.elements[3].x, mat.elements[3].y, mat.elements[3].z, mat.elements[3].w);

		return glm::mat4(v0, v1, v2, v3);
	}

	namespace BEbraMath {
		Vector3 normalize(const Vector3& vec) noexcept
		{
			return toVec3(glm::normalize(gtoVec3(vec)));
		}
		
		Vector4 normalize(const Vector4& vec) noexcept
		{
			return toVec4(glm::normalize(gtoVec4(vec)));
		}

		Vector2 normalize(const Vector2& vec) noexcept
		{
			return toVec2(glm::normalize(gtoVec2(vec)));
		}

		float length(const Vector3& vec) noexcept
		{
			return glm::length(gtoVec3(vec));
		}

		float distance(const Vector2& left, const Vector2& right) noexcept
		{
			return glm::distance(gtoVec2(left), gtoVec2(right));
		}

		float distance(const Vector3& left, const Vector3& right) noexcept
		{
			return glm::distance(gtoVec3(left), gtoVec3(right));
		}

		float distance(const Vector4& left, const Vector4& right) noexcept
		{

			return glm::distance(gtoVec4(left), gtoVec4(right));
		}

		Vector4 clamp(const Vector4& x, const Vector4& minValue, const Vector4& maxValue) noexcept
		{

			return toVec4(glm::clamp(gtoVec4(x), gtoVec4(minValue), gtoVec4(maxValue)));
		}

		Vector3 clamp(const Vector3& x, const Vector3& minValue, const Vector3& maxValue) noexcept
		{

			return toVec3(glm::clamp(gtoVec3(x), gtoVec3(minValue), gtoVec3(maxValue)));
		}

		Vector2 clamp(const Vector2& x, const Vector2& minValue, const Vector2& maxValue) noexcept
		{

			return toVec2(glm::clamp(gtoVec2(x), gtoVec2(minValue), gtoVec2(maxValue)));
		}

		Vector4 clamp(const Vector4& x, float minValue, float maxValue) noexcept
		{
			return toVec4(glm::clamp(gtoVec4(x), minValue, maxValue));
		}

		Vector2 clamp(const Vector2& x, float minValue, float maxValue) noexcept
		{
			return toVec2(glm::clamp(gtoVec2(x), minValue, maxValue));
		}

		Vector3 cross(const Vector3& left, const Vector3& right) noexcept
		{
			return toVec3(glm::cross(gtoVec3(left), gtoVec3(right)));
		}

		Quaternion toQuat(const Matrix4& mat) noexcept
		{
			return glm::toQuat(gtoMat4(mat));
		}

		Matrix4 toMat4(const Quaternion& quat) noexcept
		{
			glm::quat q = glm::quat(quat.x, quat.y, quat.z, quat.w);
			glm::mat4x4 mat = glm::toMat4(q);
			return BEbraEngine::toMat4(mat);
		}

		Matrix4 scale(const Matrix4& mat, const Vector3& vec) noexcept
		{
			return BEbraEngine::toMat4(glm::scale(BEbraEngine::gtoMat4(mat), gtoVec3(vec)));
		}

		Matrix4 translate(const Matrix4& mat, const Vector3& vec) noexcept
		{

			return BEbraEngine::toMat4(glm::translate(BEbraEngine::gtoMat4(mat), gtoVec3(vec)));
		}

		Matrix4 perspective(float fovy, float aspect, float zNear, float zFar) noexcept
		{
			return BEbraEngine::toMat4(glm::perspective(fovy, aspect, zNear, zFar));
		}

		Matrix4 lookAt(const Vector3& eye, const Vector3& center, const Vector3& up) noexcept
		{
			return BEbraEngine::toMat4(glm::lookAt(gtoVec3(eye), gtoVec3(center), gtoVec3(up)));
		}

		float radians(float value) noexcept
		{
			return glm::radians(value);
		}

		Matrix4 rotate(const Matrix4& mat, float angle, const Vector3& vec) noexcept
		{
			return BEbraEngine::toMat4(glm::rotate(BEbraEngine::gtoMat4(mat), angle, gtoVec3(vec)));
		}
		Quaternion rotate(const Quaternion& quat, float angle, const Vector3& vec) noexcept
		{
			auto _quat = glm::toQuat(glm::rotate(BEbraEngine::gtoMat4(toMat4(quat)), angle, gtoVec3(vec)));
			return Quaternion(_quat.x, _quat.y, _quat.z, _quat.w);
		}
	}
}