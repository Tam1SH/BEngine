module;
#include <variant>
#include <boost/filesystem.hpp>
export module Render;
import VulkanRender;
import CRender;
import <tbb.h>;

namespace BEbraEngine {

	template <typename RenderType, typename... RenderTypes>
	struct _AreRenderStates : std::conditional_t<CRender<RenderType>, _AreRenderStates<RenderTypes...>, std::false_type> {};

	template <typename RenderType>
	struct _AreRenderStates<RenderType> : std::bool_constant<CRender<RenderType>> {};

	export template <typename RenderType, typename... RenderTypes>
	constexpr bool AreRenders = _AreRenderStates< RenderType, RenderTypes...>::value;

	export template<typename... RenderTypes>
		requires AreRenders<RenderTypes...>
	struct _Render : public std::variant<RenderTypes...> {
		
		//Юзать макросы????7 Не, не слышали?
		using Self = std::variant<RenderTypes...>&;

		constexpr void update() {
			return std::visit([](CRender auto& render) {
				return render.update();
			}, static_cast<Self>(*this));
		}

		constexpr void prepareDraw() {
			return std::visit([](CRender auto& render) {
				return render.prepareDraw();
			}, static_cast<Self>(*this));
		}

		constexpr void drawFrame() {
			return std::visit([](CRender auto& render) {
				return render.drawFrame();
			}, static_cast<Self>(*this));
		}

		constexpr void updateState(RenderData& data) {
			return std::visit([](CRender auto& render) {
				return render.updateState(data);
			}, static_cast<Self>(*this));
		}

		template<typename RenderType>
		constexpr _Render(RenderType&& render) requires CRender<RenderType> {
			//Не знаю, не является ли UB это. Ну по сути стейта у этого объекта нет, чё бы и нет.
			//Да если так подумать, то вызывается конструктор у родителя, не затрагивая текущий объект.
			static_cast<Self>(*this) = std::forward<RenderType>(render);
		}
		_Render() {}

	};

	export using Render = _Render<VulkanRender>;
}