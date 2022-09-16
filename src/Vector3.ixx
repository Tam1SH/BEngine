#include <Physics/LinearMath/btVector3.h>
#include <concepts>

export module Vector3;


namespace BEbraEngine {


	export class Vector3
	{
	public:
		float x{}, y{}, z{};
	public:
		constexpr Vector3() {}

		constexpr Vector3(float x, float y, float z) : x(x), y(y), z(z) { }

		constexpr Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z) { }

		constexpr Vector3(float all) : x(all), y(all), z(all) { }

		Vector3(const btVector3& vec) : x(vec.x()), y(vec.y()), z(vec.z()) { }

		operator btVector3() noexcept { return btVector3(x, y, z); }

		Vector3 operator+(const Vector3& other) const noexcept;

		Vector3 operator-(const Vector3& other) const noexcept;

		Vector3 operator*(const Vector3& other) const noexcept;

		Vector3 operator*(float scalar) const noexcept;

		Vector3& operator*=(const Vector3& other) noexcept;

		Vector3& operator+=(const Vector3& other) noexcept;

		Vector3& operator-=(const Vector3& other) noexcept;

		bool operator==(const Vector3& other) const noexcept;

		bool operator!=(const Vector3& other) const noexcept;

	};

}
