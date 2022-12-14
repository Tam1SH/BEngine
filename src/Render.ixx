module;
#include "MethodDefineMacros.hpp"

export module Render;
import Concepts;
import <variant>;
import CRender;
import RenderData;
import VulkanRenderProxy;
import VulkanRender;

namespace BEbraEngine {

	template<typename T>
	struct Concept : std::bool_constant<CRender<T>> {};

	template <class...Ts>
	constexpr bool AreRenders = AreSuitableToBe<Concept, Ts...>;

	export template<typename... RenderTypes>
		requires AreRenders<RenderTypes...>
	struct _Render {

		METHOD_DEFINE_0(update, CRender)
		METHOD_DEFINE_0(prepareDraw, CRender)
		METHOD_DEFINE_0(drawFrame, CRender)
		METHOD_DEFINE_1(updateState, CRender, data)
		

		template<typename RenderType>
		RenderType& get() {
			return std::get<RenderType>(self);
		}

		std::variant<RenderTypes...>& variant() {
			return self;
		}

		template<typename RenderType>
		_Render(RenderType&& render) requires CRender<RenderType> {

			//static_assert(
			//	are_same<remove_cvrefs<RenderTypes...>::type,
			//	remove_cvrefs<RenderType>::type>::value,
			//	"corresponds to the concept but does not correspond to the available types");

			self = std::forward<RenderType>(render);
		}

		template<int index = 0>
		_Render(std::in_place_index_t<index> i) {
			self = std::variant<RenderTypes...>(i);
		}
	private:
		std::variant<RenderTypes...> self;
	};
	export struct RenderType {
		static constexpr auto Vulkan = std::in_place_index<0>;
	};

	export using Render = _Render<VulkanRender>;

}