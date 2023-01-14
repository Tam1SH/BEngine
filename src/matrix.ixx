export module Matrix4;
import Vector4;

namespace BEbraEngine {

	export struct Matrix4 {
	public:

		constexpr Vector4& operator[](size_t i) {return elements[i];}

		Matrix4& operator*=(const Matrix4& other) noexcept;

		Matrix4 operator*(const Matrix4& other) const noexcept;

		Vector4 operator*(const Vector4& other) const noexcept;

		bool operator==(const Matrix4& other) const noexcept;

		bool operator!=(const Matrix4& other) const noexcept;

		Matrix4(const Matrix4&) noexcept = default;
		Matrix4& operator=(const Matrix4&) noexcept = default;

		Matrix4(Matrix4&&) noexcept = default;
		Matrix4& operator=(Matrix4&&) noexcept = default;

		constexpr Matrix4() noexcept {}

		constexpr Matrix4(Vector4 v0,Vector4 v1, Vector4 v2, Vector4 v3) noexcept;

		Matrix4(float all) noexcept;

	public:
		alignas(16) Vector4 elements[4];

	};
}