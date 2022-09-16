export module Matrix4;
import Vector4;
import <array>;

namespace BEbraEngine {

	export class Matrix4 {
	public:
		alignas(16) Vector4 elements[4];

	public:

		constexpr Vector4& operator[](size_t i) {
			return elements[i];
		}

		constexpr Matrix4() noexcept {}

		constexpr Matrix4(
			Vector4 v0,
			Vector4 v1,
			Vector4 v2,
			Vector4 v3) noexcept;

		Matrix4(float all) noexcept;

		Matrix4& operator*=(const Matrix4& other) noexcept;

		Matrix4 operator*(const Matrix4& other) const noexcept;

		Vector4 operator*(const Vector4& other) const noexcept;

		bool operator==(const Matrix4& other) const noexcept;

		bool operator!=(const Matrix4& other) const noexcept;


	};
}