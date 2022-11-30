module;
#include "stdafx.h"
export module CVector3;


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
	concept CVector3FromArray = 
		std::tuple_size<std::decay_t<Vector>>::value >= 3 &&
		requires(Vector & v)
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
}