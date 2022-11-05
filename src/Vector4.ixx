module;

#include <Physics/LinearMath/btVector3.h>

export module Vector4;

namespace BEbraEngine {


	export class Vector4
	{
	public:
		float x{}, y{}, z{}, w{};
	public:
		constexpr Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }

		constexpr Vector4(const Vector4& other) : x(other.x), y(other.y), z(other.z), w(other.w) { }

		constexpr Vector4(float* array) : x(array[0]), y(array[1]), z(array[2]), w(array[3]) { }

		constexpr Vector4(float all) : x(all), y(all), z(all), w(all) { }

		Vector4(const btVector4& vec) : x(vec.x()), y(vec.y()), z(vec.z()), w(vec.w()) { }

		constexpr Vector4() : x(0), y(0), z(0), w(0) { }

		operator btVector4() noexcept { return btVector4(x, y, z, w); }


		Vector4 operator+(const Vector4& other) noexcept;

		Vector4 operator-(const Vector4& other) noexcept;

		Vector4 operator*(const Vector4& other) noexcept;

		Vector4 operator*(float scalar) noexcept;

		Vector4& operator*=(const Vector4& other) noexcept;

		Vector4& operator*=(float other) noexcept;

		Vector4& operator+=(const Vector4& other) noexcept;

		Vector4& operator-=(const Vector4& other) noexcept;

		bool operator==(const Vector4& other) const noexcept;

		bool operator!=(const Vector4& other) const noexcept;
	};

}
