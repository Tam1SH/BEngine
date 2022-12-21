#include "MethodDefineMacros.hpp"
export module TextureFactory;
import <concepts>;
import <variant>;
import CTextureFactory;
import VulkanTextureFactory;
import Concepts;

namespace BEbraEngine {

	template<typename T>
	struct Concept : std::bool_constant<CTextureFactory<T>> {};

	template <class...Ts>
	constexpr bool AreTextureFactories = AreSuitableToBe<Concept, Ts...>;

	//Статически типизированный интерфейс для объектов, удовлетворяющими концепту CTextureFactory<T> 
	export template<typename... TextureFactories>
		requires AreTextureFactories<TextureFactories...>
	struct _TextureFactory {

		METHOD_DEFINE_1(createMaterialAsync, CTextureFactory, info)
		METHOD_DEFINE_1(createAsync, CTextureFactory, path)
		METHOD_DEFINE_1(destroyTextureAsync, CTextureFactory, texture)
		METHOD_DEFINE_0(createEmpty, CTextureFactory)

		_TextureFactory() {
			self = std::variant<TextureFactories...>(std::in_place_index<0>);
		}

		template<typename TextureFactory>
		TextureFactory& get() {
			return std::get<TextureFactory>(self);
		}

		std::variant<TextureFactories...>& variant() {
			return self;
		}

		template<int index = 0>
		_TextureFactory(std::in_place_index_t<index> i) {
			self = std::variant<TextureFactories...>(i);
		}

	private:
		std::variant<TextureFactories...> self;
	};

	export struct RenderAllocatorType {
		static constexpr auto Vulkan = std::in_place_index<0>;
	};

	export using TextureFactory = _TextureFactory<VulkanTextureFactory>;
	static_assert(CTextureFactory<VulkanTextureFactory>);

}
