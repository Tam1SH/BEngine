#include <concepts>
export module CRender;
namespace BEbraEngine {
	export class RenderData;
}
namespace BEbraEngine {

	export template<typename T>
		concept CRender = requires(

			/*void updateState*/ RenderData& data,

			/* this */
			T& self
			)
	{
		{ self.updateState(data) } -> std::same_as<void>;
		{ self.update() } -> std::same_as<void>;
		{ self.prepareDraw() } -> std::same_as<void>;
		{ self.drawFrame()  } -> std::same_as<void>;
	};
}