module;
export module Render;
import RenderData;

namespace BEbraEngine {

	export struct Render {

		virtual void update() = 0;
		virtual void prepareDraw() = 0;
		virtual void drawFrame() = 0;
		virtual void updateState(RenderData& data) = 0;

	};

}