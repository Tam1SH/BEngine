#define GLM_FORCE_XYZW_ONLY
#include <glm/glm.hpp>
module Matrix4;

namespace BEbraEngine {

	//��-��, DRY ������ ���, ��.
	Matrix4 toMat4(glm::mat4 mat) {
		Vector4 v0 = Vector4(mat[0].x, mat[0].y, mat[0].z, mat[0].w);
		Vector4 v1 = Vector4(mat[1].x, mat[1].y, mat[1].z, mat[1].w);
		Vector4 v2 = Vector4(mat[2].x, mat[2].y, mat[2].z, mat[2].w);
		Vector4 v3 = Vector4(mat[3].x, mat[3].y, mat[3].z, mat[3].w);
		return Matrix4(v0, v1, v2, v3);
	}

	glm::mat4 gtoMat4(Matrix4 mat) {
		glm::vec4 v0 = glm::vec4(mat.elements[0].x, mat.elements[0].y, mat.elements[0].z, mat.elements[0].w);
		glm::vec4 v1 = glm::vec4(mat.elements[1].x, mat.elements[1].y, mat.elements[1].z, mat.elements[1].w);
		glm::vec4 v2 = glm::vec4(mat.elements[2].x, mat.elements[2].y, mat.elements[2].z, mat.elements[2].w);
		glm::vec4 v3 = glm::vec4(mat.elements[3].x, mat.elements[3].y, mat.elements[3].z, mat.elements[3].w);

		return glm::mat4(v0, v1, v2, v3);
	}

	constexpr Matrix4::Matrix4(Vector4 v0, Vector4 v1, Vector4 v2, Vector4 v3) noexcept
	{
		elements[0] = v0;
		elements[1] = v1;
		elements[2] = v2;
		elements[3] = v3;
	}

	Matrix4::Matrix4(float all) noexcept {
		elements[0] = Vector4(1, 0, 0, 0);
		elements[1] = Vector4(0, 1, 0, 0);
		elements[2] = Vector4(0, 0, 1, 0);
		elements[3] = Vector4(0, 0, 0, 1);
	}

	Matrix4& Matrix4::operator*=(const Matrix4& other) noexcept
	{
		*this = Matrix4(*this * other);
		return *this;
	}



	Matrix4 Matrix4::operator*(const Matrix4& other) const noexcept
	{
		const glm::mat4& lol = gtoMat4(*this);
		glm::mat4 lol1 = gtoMat4(other);
		auto lol2 = lol * lol1;
		return Matrix4(toMat4(lol2));
	}

	Vector4 Matrix4::operator*(const Vector4& other) const noexcept
	{
		const glm::mat4& lol = gtoMat4(*this);
		auto _other = glm::vec4(other.x, other.y, other.z, other.w);

		auto result = lol * _other;

		return Vector4(result.x, result.y, result.z, result.w);
	}

	bool Matrix4::operator==(const Matrix4& other) const noexcept
	{
		return (this->elements[0] == other.elements[0]
			&& this->elements[1] == other.elements[1]
			&& this->elements[2] == other.elements[2]
			&& this->elements[3] == other.elements[3]);

	}

	bool Matrix4::operator!=(const Matrix4& other) const noexcept
	{
		return !(*this == other);
	}

}