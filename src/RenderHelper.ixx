export module RenderHelper;
import Vector3;

namespace BEbraEngine {
	export struct RenderHelper {

		virtual void drawLine(
			const Vector3& from,
			const Vector3& to,
			const Vector3& color) = 0;
	};
}