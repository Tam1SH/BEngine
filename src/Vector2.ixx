export module Vector2;
namespace BEbraEngine {

	export class Vector2
	{
	public:
		float x{}, y{};
	public:
		constexpr Vector2(float x, float y) : x(x), y(y) { }

		constexpr Vector2(const Vector2& other) : x(other.x), y(other.y) { }

		constexpr Vector2(float all) : x(all), y(all) { }

		constexpr Vector2() { }


		Vector2 operator+(const Vector2& other) const noexcept;

		Vector2 operator-(const Vector2& other) const noexcept;

		Vector2 operator*(const Vector2& other) const noexcept;

		Vector2 operator*(float scalar) const noexcept;

		Vector2& operator*=(const Vector2& other) noexcept;

		Vector2& operator+=(const Vector2& other) noexcept;

		Vector2& operator-=(const Vector2& other) noexcept;

		bool operator==(const Vector2& other) const noexcept;

		bool operator!=(const Vector2& other) const noexcept;
	};
}