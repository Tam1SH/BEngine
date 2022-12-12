module;
export module Concepts;
import <concepts>;

namespace BEbraEngine {
	export template<class T>
		concept OnlyMovable = (std::movable<T> && !std::copyable<T>);
	
	template <template<typename> typename Concept, class T, class... Ts>
	struct _AreSuitableToBe : std::conditional_t<
		/*if*/Concept<T>::value,
		/*then*/_AreSuitableToBe<Concept, Ts...>,
		/*else*/std::false_type>
	{};

	export template<typename T>
	struct remove_cvrefs;

	export template<typename T>
	struct remove_cvrefs {
		using type = typename std::remove_cvref<T>::type;
	};

	export template<typename T>
	struct remove_cvrefs<const T> {
		using type = typename remove_cvrefs<T>::type;
	};

	export template<typename T>
	struct remove_cvrefs<const T*> {
		using type = typename remove_cvrefs<T>::type*;
	};

	export template<typename T>
	struct remove_cvrefs<T* const> {
		using type = typename remove_cvrefs<T>::type*;
	};

	export template<template <typename...> class T, typename... Args>
	struct remove_cvrefs<T<Args...>> {
		using type = T<typename remove_cvrefs<Args>::type...>;
	};

	
	export template <class T, class... Ts>
	struct are_same : std::conjunction<std::is_same<T, Ts>...> {};

	//Низя сувать концепты в качестве шаблона:(99(((
	template <template<typename> class Concept, class T>
	struct _AreSuitableToBe<Concept, T> : std::bool_constant<Concept<T>::value> {
		static_assert(Concept<T>::value, "lol, suffer, not going to compile");
	};

	export template <template<typename> typename Concept, class... Ts>
		//Соотвествует ли каждый тип полученому концепту (читай компаратор).
		concept AreSuitableToBe = _AreSuitableToBe<Concept, Ts...>::value;

}