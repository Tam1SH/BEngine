module;
#include <Physics/LinearMath/btVector3.h>

export module Vector3;
import CVector3;

namespace BEbraEngine {

	export struct Vector3
	{
		constexpr Vector3(const CVector3 auto& v) {
			if constexpr (CVector3FromProperties1<decltype(v)>) {
				x = v.getX(), y = v.getY(), z = v.getZ();
			}
			else if constexpr (CVector3FromProperties2<decltype(v)>) {
				x = v.x(), y = v.y(), z = v.z();
			}
			else if constexpr (CVector3FromStructure<decltype(v)>) {
				x = v.x, y = v.y, z = v.z;
			}
			else if constexpr (CVector3FromArray<decltype(v)>) {
				constexpr bool is_true = std::tuple_size<std::decay_t<decltype(v)>>::value >= 3;
				if constexpr (is_true)
					x = v[0], y = v[1], z = v[2];
				else static_assert(is_true, "vector will not init");

			}
			else {
				static_assert(true, "vector will not init");
			}
		}
		constexpr Vector3() : x(0), y(0), z(0) {}

		constexpr Vector3(float x, float y, float z) : x(x), y(y), z(z) { }

		constexpr Vector3(float all) : x(all), y(all), z(all) { }

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

	public:
		float x, y, z;

	};
}
