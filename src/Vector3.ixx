module;
#include <concepts>
export module Vector3;

namespace BEbraEngine {

	export template<typename Vector, typename Scalar = float>
		concept CVector3FromStructure = requires(Vector & v)
	{
		{v.x} -> std::convertible_to<Scalar>;
		{v.y} -> std::convertible_to<Scalar>;
		{v.z} -> std::convertible_to<Scalar>;
	};

	export template<typename Vector, typename Scalar = float>
		concept CVector3FromProperties1 = requires(Vector & v)
	{
		{v.getX()} -> std::convertible_to<Scalar>;
		{v.getY()} -> std::convertible_to<Scalar>;
		{v.getZ()} -> std::convertible_to<Scalar>;
	};

	export template<typename Vector, typename Scalar = float>
		concept CVector3FromProperties2 = requires(Vector & v)
	{
		{v.x()} -> std::convertible_to<Scalar>;
		{v.y()} -> std::convertible_to<Scalar>;
		{v.z()} -> std::convertible_to<Scalar>;
	};
	export template<typename Vector, typename Scalar = float>
		concept CVector3FromArray = requires(Vector & v)
	{
		{v[0]} -> std::convertible_to<Scalar>;

	};
	export template<typename Vector, typename Scalar = float>
		concept CVector3FromInitList = requires(Vector & v)
	{
		{v} ->  std::same_as<std::initializer_list<Scalar>>;
	};

	export template<typename Vector>
		concept CVector3 = CVector3FromProperties1<Vector>
						|| CVector3FromProperties2<Vector>
						|| CVector3FromStructure<Vector>
						|| CVector3FromArray<Vector>
						|| CVector3FromInitList<Vector>;

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
				x = v[0], y = v[1], z = v[2];

			}
			else {
				static_assert(true, "vector will not init");
			}
		}

		template<CVector3 vec>
		vec toVec() const {
			return vec(x, y, z);
		}

		constexpr Vector3() : x(0), y(0), z(0) {}

		constexpr Vector3(float x, float y, float z) : x(x), y(y), z(z) { }

		constexpr Vector3(float all) : x(all), y(all), z(all) { }


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
